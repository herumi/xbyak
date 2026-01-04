#pragma once
#include <stdint.h>
#include <stdio.h>

namespace Xbyak { namespace util { namespace intel {

enum CoreType {
	Ecore,
	Pcore,
	MAX_CORE_TYPE = 2
};

enum CacheType {
	L1i = 0,
	L1d = 1,
	L2 = 2,
	L3 = 3,
	MAX_CACHE_TYPE = 4
};

struct CacheSize {
	uint32_t byteSize;
	uint32_t sharedNum;
	CacheSize() : byteSize(0), sharedNum(0) {}
};

struct Cache {
	CacheSize v_[MAX_CACHE_TYPE]; // L1i, L1d, L2, L3
};

struct CpuCache {
	int PcoreIdx_ = -1;
	int EcoreIdx_ = -1;
	int PcoreNum_ = 0;
	int EcoreNum_ = 0;
	int physicalCoreNum_ = 0;
	int logicalCoreNum_ = 0;
	Cache cpuType_[MAX_CORE_TYPE]; // Ecore, Pcore
	void put() const {
		printf("Physical cores: %d, Logical cores: %d\n", physicalCoreNum_, logicalCoreNum_);
		printf("P-cores: %d, E-cores: %d\n", PcoreNum_, EcoreNum_);
		const char* coreNameTbl[] = { "E-core", "P-core" };
		const char* cacheNameTbl[] = { "L1i", "L1d", "L2", "L3" };
		for (int cti = 0; cti < MAX_CORE_TYPE; cti++) {
			printf("%s:\n", coreNameTbl[cti]);
			for (int cci = 0; cci < MAX_CACHE_TYPE; cci++) {
				const CacheSize& cs = cpuType_[cti].v_[cci];
				printf("  %s: %u bytes, shared=%u\n",
					   cacheNameTbl[cci],
					   cs.byteSize,
					   cs.sharedNum);
			}
		}
	}
	bool init();
};

}}} // namespace Xbyak::util::intel

#ifdef _WIN32
#define WIN32_LEAN_AND_MEAN
#include <windows.h>
#include <stdio.h>
#include <stdint.h>
#include <vector>

namespace Xbyak { namespace util { namespace intel { namespace impl {

static inline int getIdx(uint64_t mask) {
	for (int i = 0; i < 64; i++) {
		if (mask & (uint64_t(1) << i)) {
			return i;
		}
	}
	return -1;
}
static inline bool maskHasIdx(uint64_t mask, int idx) {
	return idx >= 0 && ((mask >> idx) & 1) != 0;
}

// return true if success
// PcoreIdx, EcoreIdx(or old CPU): -1 if not found
bool getCoreIdx(int *PcoreIdx, int *EcoreIdx, int *physicalCoreNum, int *logicalCoreNum, int *PcoreNum, int *EcoreNum) {
	typedef SYSTEM_LOGICAL_PROCESSOR_INFORMATION_EX Info;
	DWORD len = 0;
	GetLogicalProcessorInformationEx(RelationProcessorCore, nullptr, &len);
	std::vector<char> buf(len);
	if (!GetLogicalProcessorInformationEx(RelationProcessorCore, reinterpret_cast<Info*>(buf.data()), &len)) return false;
	// get core indices
	*PcoreIdx = -1;
	*EcoreIdx = -1;
	const char *ptr = buf.data();
	const char *end = ptr + len;
	*physicalCoreNum = 0;
	*logicalCoreNum = 0;
	*PcoreNum = 0;
	*EcoreNum = 0;
	while (ptr < end) {
		const auto& entry = *reinterpret_cast<const Info*>(ptr);
		const PROCESSOR_RELATIONSHIP& core = entry.Processor;
		uint64_t mask = core.GroupMask[0].Mask;
		if (core.EfficiencyClass > 0) {
			if (*PcoreIdx == -1) *PcoreIdx = getIdx(mask);
			(*EcoreNum)++;
		} else {
			if (*EcoreIdx == -1) *EcoreIdx = getIdx(mask);
			(*PcoreNum)++;
		}
		ptr += entry.Size;
		(*physicalCoreNum)++;
		(*logicalCoreNum) += int(__popcnt64(mask));
	}
	return *PcoreIdx >= 0 || *EcoreIdx >= 0;
}

} // Xbyak::util::intel::impl

// return true if success
bool CpuCache::init() {
	typedef SYSTEM_LOGICAL_PROCESSOR_INFORMATION_EX Info;
	using namespace impl;
	if (!getCoreIdx(&PcoreIdx_, &EcoreIdx_, &physicalCoreNum_, &logicalCoreNum_, &PcoreNum_, &EcoreNum_)) return false;
	DWORD len = 0;
	GetLogicalProcessorInformationEx(RelationCache, nullptr, &len);
	std::vector<char> buf(len);
	if (!GetLogicalProcessorInformationEx(RelationCache, reinterpret_cast<Info*>(buf.data()), &len)) return false;
	const char *ptr = buf.data();
	const char *end = ptr + len;
	while (ptr < end) {
		const auto& entry = *reinterpret_cast<const Info*>(ptr);
		if (entry.Relationship == RelationCache) {
			const CACHE_RELATIONSHIP& cache = entry.Cache;
			uint64_t mask = cache.GroupMask.Mask;
			if (maskHasIdx(mask, PcoreIdx_) || maskHasIdx(mask, EcoreIdx_)) {
				int cacheType = -1;
				if (cache.Level == 1) {
					if (cache.Type == CacheInstruction) {
						cacheType = L1i;
					} else if (cache.Type == CacheData) {
						cacheType = L1d;
					}
				} else if (cache.Level == 2) {
					cacheType = L2;
				} else if (cache.Level == 3) {
					cacheType = L3;
				}
				if (cacheType >= 0) {
					CacheSize cs;
					cs.byteSize = cache.CacheSize;
					cs.sharedNum = uint32_t(__popcnt64(mask));
					if (maskHasIdx(mask, PcoreIdx_)) {
						cpuType_[Pcore].v_[cacheType] = cs;
					}
					if (maskHasIdx(mask, EcoreIdx_)) {
						cpuType_[Ecore].v_[cacheType] = cs;
					}
				}
			}
		}
		ptr += entry.Size;
	}
	return true;
}

}}} // namespace Xbyak::util::intel

#endif
