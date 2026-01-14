#ifndef XBYAK_XBYAK_UTIL_H_
#define XBYAK_XBYAK_UTIL_H_

#ifdef XBYAK_ONLY_CLASS_CPU
#include <stdint.h>
#include <stdlib.h>
#include <assert.h>
#ifndef XBYAK_THROW
	#define XBYAK_THROW(x) ;
	#define XBYAK_THROW_RET(x, y) return y;
#endif
#ifndef XBYAK_CONSTEXPR
#if ((__cplusplus >= 201402L) && !(!defined(__clang__) && defined(__GNUC__) && (__GNUC__ <= 5))) || (defined(_MSC_VER) && _MSC_VER >= 1910)
	#define XBYAK_CONSTEXPR constexpr
#else
	#define XBYAK_CONSTEXPR
#endif
#endif
#else
#include <string.h>

/**
	utility class and functions for Xbyak
	Xbyak::util::Clock ; rdtsc timer
	Xbyak::util::Cpu ; detect CPU
*/
#include "xbyak.h"
#endif // XBYAK_ONLY_CLASS_CPU

#if defined(__i386__) || (defined(__x86_64__) && !defined(__arm64ec__)) || defined(_M_IX86) || (defined(_M_X64) && !defined(_M_ARM64EC))
	#define XBYAK_INTEL_CPU_SPECIFIC
#endif

#ifdef XBYAK_INTEL_CPU_SPECIFIC
#ifdef _WIN32
	#if defined(_MSC_VER) && (_MSC_VER < 1400) && defined(XBYAK32)
		static inline __declspec(naked) void __cpuid(int[4], int)
		{
			__asm {
				push	ebx
				push	esi
				mov		eax, dword ptr [esp + 4 * 2 + 8] // eaxIn
				cpuid
				mov		esi, dword ptr [esp + 4 * 2 + 4] // data
				mov		dword ptr [esi], eax
				mov		dword ptr [esi + 4], ebx
				mov		dword ptr [esi + 8], ecx
				mov		dword ptr [esi + 12], edx
				pop		esi
				pop		ebx
				ret
			}
		}
	#else
		#include <intrin.h> // for __cpuid
	#endif
#else
	#ifndef __GNUC_PREREQ
    	#define __GNUC_PREREQ(major, minor) ((((__GNUC__) << 16) + (__GNUC_MINOR__)) >= (((major) << 16) + (minor)))
	#endif
	#if __GNUC_PREREQ(4, 3) && !defined(__APPLE__)
		#include <cpuid.h>
	#else
		#if defined(__APPLE__) && defined(XBYAK32) // avoid err : can't find a register in class `BREG' while reloading `asm'
			#define __cpuid(eaxIn, a, b, c, d) __asm__ __volatile__("pushl %%ebx\ncpuid\nmovl %%ebp, %%esi\npopl %%ebx" : "=a"(a), "=S"(b), "=c"(c), "=d"(d) : "0"(eaxIn))
			#define __cpuid_count(eaxIn, ecxIn, a, b, c, d) __asm__ __volatile__("pushl %%ebx\ncpuid\nmovl %%ebp, %%esi\npopl %%ebx" : "=a"(a), "=S"(b), "=c"(c), "=d"(d) : "0"(eaxIn), "2"(ecxIn))
		#else
			#define __cpuid(eaxIn, a, b, c, d) __asm__ __volatile__("cpuid\n" : "=a"(a), "=b"(b), "=c"(c), "=d"(d) : "0"(eaxIn))
			#define __cpuid_count(eaxIn, ecxIn, a, b, c, d) __asm__ __volatile__("cpuid\n" : "=a"(a), "=b"(b), "=c"(c), "=d"(d) : "0"(eaxIn), "2"(ecxIn))
		#endif
	#endif
#endif
#endif

#ifdef XBYAK_USE_VTUNE
	// -I /opt/intel/vtune_amplifier/include/ -L /opt/intel/vtune_amplifier/lib64 -ljitprofiling -ldl
	#include <jitprofiling.h>
	#ifdef _MSC_VER
		#pragma comment(lib, "libittnotify.lib")
	#endif
	#ifdef __linux__
		#include <dlfcn.h>
	#endif
#endif
#ifdef __linux__
	#define XBYAK_USE_PERF
	#include <sched.h>
#endif

namespace Xbyak { namespace util {

typedef enum {
   SmtLevel = 1,
   CoreLevel = 2
} CpuTopologyLevel;
typedef CpuTopologyLevel IntelCpuTopologyLevel; // for backward compatibility

typedef enum {
	Pcore = 0, // Performance core
	Ecore =1   // Efficiency core
} HybridCoreType;

namespace local {

template<uint64_t L, uint64_t H = 0>
struct TypeT {
};

template<uint64_t L1, uint64_t H1, uint64_t L2, uint64_t H2>
XBYAK_CONSTEXPR TypeT<L1 | L2, H1 | H2> operator|(TypeT<L1, H1>, TypeT<L2, H2>) { return TypeT<L1 | L2, H1 | H2>(); }

template<typename T>
inline T max_(T x, T y) { return x >= y ? x : y; }
template<typename T>
inline T min_(T x, T y) { return x < y ? x : y; }

} // local

/**
	CPU detection class
	@note static inline const member is supported by c++17 or later, so use template hack
*/
#ifdef _MSC_VER
	#pragma warning(push)
	#pragma warning(disable : 4459)
#endif
class Cpu {
public:
	class Type {
		uint64_t L;
		uint64_t H;
	public:
		Type(uint64_t L = 0, uint64_t H = 0) : L(L), H(H) { }
		template<uint64_t L_, uint64_t H_>
		Type(local::TypeT<L_, H_>) : L(L_), H(H_) {}
		Type& operator&=(const Type& rhs) { L &= rhs.L; H &= rhs.H; return *this; }
		Type& operator|=(const Type& rhs) { L |= rhs.L; H |= rhs.H; return *this; }
		Type operator&(const Type& rhs) const { Type t = *this; t &= rhs; return t; }
		Type operator|(const Type& rhs) const { Type t = *this; t |= rhs; return t; }
		bool operator==(const Type& rhs) const { return H == rhs.H && L == rhs.L; }
		bool operator!=(const Type& rhs) const { return !operator==(rhs); }
		// without explicit because backward compatilibity
		operator bool() const { return (H | L) != 0; }
		uint64_t getL() const { return L; }
		uint64_t getH() const { return H; }
	};
private:
	Type type_;
	//system topology
	static const size_t maxTopologyLevels = 2;
	static const size_t maxCoreTypes = 2;
	uint32_t numCores_[maxCoreTypes * maxTopologyLevels];

	static const uint32_t maxNumberCacheLevels = 10;
	uint32_t dataCacheSize_[maxCoreTypes * maxNumberCacheLevels];
	uint32_t coresSharingDataCache_[maxCoreTypes * maxNumberCacheLevels];
	uint32_t dataCacheLevels_[maxCoreTypes];
	uint32_t avx10version_;

	uint32_t get32bitAsBE(const char *x) const
	{
		return x[0] | (x[1] << 8) | (x[2] << 16) | (x[3] << 24);
	}
	uint32_t mask(int n) const
	{
		return (1U << n) - 1;
	}
	// [ebx:ecx:edx] == s?
	bool isEqualStr(uint32_t ebx, uint32_t ecx, uint32_t edx, const char s[12]) const
	{
		return get32bitAsBE(&s[0]) == ebx && get32bitAsBE(&s[4]) == edx && get32bitAsBE(&s[8]) == ecx;
	}
	uint32_t extractBit(uint32_t val, uint32_t base, uint32_t end) const
	{
		return (val >> base) & ((1u << (end + 1 - base)) - 1);
	}
	void setFamily()
	{
		uint32_t data[4] = {};
		getCpuid(1, data);
		stepping = extractBit(data[0], 0, 3);
		model = extractBit(data[0], 4, 7);
		family = extractBit(data[0], 8, 11);
		//type = extractBit(data[0], 12, 13);
		extModel = extractBit(data[0], 16, 19);
		extFamily = extractBit(data[0], 20, 27);
		if (family == 0x0f) {
			displayFamily = family + extFamily;
		} else {
			displayFamily = family;
		}
		if ((has(tINTEL) && family == 6) || family == 0x0f) {
			displayModel = (extModel << 4) + model;
		} else {
			displayModel = model;
		}
	}

	HybridCoreType getCoreType()
	{
		// if hybrid is not supported default to Pcore
		if (!has(tHYBRID)) return HybridCoreType::Pcore;

		// These correspond to values returned in CPUID leaf 0x1A core-type field.
		constexpr uint32_t CPUID_CORE_TYPE_ATOM = 0x20; // Intel Atom / E-core
		constexpr uint32_t CPUID_CORE_TYPE_CORE = 0x40; // Intel Core / P-core
		uint32_t data[4] = {};

		// Get max basic CPUID leaf
		getCpuidEx(0x0, 0, data);
		uint32_t max_basic_leaf = data[0];
		// If 0x1A is not supported, default to P-core
		if (max_basic_leaf < 0x1A) return HybridCoreType::Pcore;

		getCpuidEx(0x1A, 0, data);
		uint32_t coreTypeField = (data[0] >> 24) & 0xFF;
		switch (coreTypeField) {
			case CPUID_CORE_TYPE_ATOM: return HybridCoreType::Ecore;
			case CPUID_CORE_TYPE_CORE: return HybridCoreType::Pcore;
			default: return HybridCoreType::Pcore;
		}

	}

	// Start setNumCores using CPUID
	void setNumCoresCpuid(HybridCoreType coreType)
	{
		if (!has(tINTEL) && !has(tAMD)) return;

		size_t coreTypeIndex = coreType * maxCoreTypes;
		uint32_t data[4] = {};
		getCpuid(0x0, data);
		if (data[0] >= 0xB) {
			// Check if "Extended Topology Enumeration" is implemented.
			getCpuidEx(0xB, 0, data);
			if (data[0] != 0 || data[1] != 0) {
				/*
					if leaf 11 exists(x2APIC is supported),
					we use it to get the number of smt cores and cores on socket

					leaf 0xB can be zeroed-out by a hypervisor
				*/
				for (uint32_t i = 0; i < maxTopologyLevels; i++) {
					getCpuidEx(0xB, i, data);
					CpuTopologyLevel level = (CpuTopologyLevel)extractBit(data[2], 8, 15);
					if (level == SmtLevel || level == CoreLevel) {
						numCores_[coreTypeIndex + level - 1] = extractBit(data[1], 0, 15);
					}
				}
				/*
					Fallback values in case a hypervisor has the leaf zeroed-out.
				*/
				numCores_[coreTypeIndex + SmtLevel - 1] = local::max_(1u, numCores_[coreTypeIndex + SmtLevel - 1]);
				numCores_[coreTypeIndex + CoreLevel - 1] = local::max_(numCores_[coreTypeIndex + SmtLevel - 1], numCores_[coreTypeIndex + CoreLevel - 1]);
				return;
			}
		}
		// "Extended Topology Enumeration" is not supported.
		if (has(tAMD)) {
			/*
				AMD - Legacy Method
			*/
			int physicalThreadCount = 0;
			getCpuid(0x1, data);
			int logicalProcessorCount = extractBit(data[1], 16, 23);
			int htt = extractBit(data[3], 28, 28); // Hyper-threading technology.
			getCpuid(0x80000000, data);
			uint32_t highestExtendedLeaf = data[0];
			if (highestExtendedLeaf >= 0x80000008) {
				getCpuid(0x80000008, data);
				physicalThreadCount = extractBit(data[2], 0, 7) + 1;
			}
			if (htt == 0) {
				numCores_[coreTypeIndex + SmtLevel - 1] = 1;
				numCores_[coreTypeIndex + CoreLevel - 1] = 1;
			} else if (physicalThreadCount > 1) {
				if ((displayFamily >= 0x17) && (highestExtendedLeaf >= 0x8000001E)) {
					// Zen overreports its core count by a factor of two.
					getCpuid(0x8000001E, data);
					int threadsPerComputeUnit = extractBit(data[1], 8, 15) + 1;
					physicalThreadCount /= threadsPerComputeUnit;
				}
				numCores_[coreTypeIndex + SmtLevel - 1] = logicalProcessorCount / physicalThreadCount;
				numCores_[coreTypeIndex + CoreLevel - 1] = logicalProcessorCount;
			} else {
				numCores_[coreTypeIndex + SmtLevel - 1] = 1;
				numCores_[coreTypeIndex + CoreLevel - 1] = logicalProcessorCount > 1 ? logicalProcessorCount : 2;
			}
		} else {
			/*
				Intel - Legacy Method
			*/
			int physicalThreadCount = 0;
			getCpuid(0x1, data);
			int logicalProcessorCount = extractBit(data[1], 16, 23);
			int htt = extractBit(data[3], 28, 28); // Hyper-threading technology.
			getCpuid(0, data);
			if (data[0] >= 0x4) {
				getCpuid(0x4, data);
				physicalThreadCount = extractBit(data[0], 26, 31) + 1;
			}
			if (htt == 0) {
				numCores_[coreTypeIndex + SmtLevel - 1] = 1;
				numCores_[coreTypeIndex + CoreLevel - 1] = 1;
			} else if (physicalThreadCount > 1) {
				numCores_[coreTypeIndex + SmtLevel - 1] = logicalProcessorCount / physicalThreadCount;
				numCores_[coreTypeIndex + CoreLevel - 1] = logicalProcessorCount;
			} else {
				numCores_[coreTypeIndex + SmtLevel - 1] = 1;
				numCores_[coreTypeIndex + CoreLevel - 1] = logicalProcessorCount > 0 ? logicalProcessorCount : 1;
			}
		}
	}

	void setNumCoresCpuid()
	{
		if (!has(tHYBRID)) {
			setNumCoresCpuid(Pcore);
		} else {
#if defined(_WIN32)
			SYSTEM_INFO sysinfo;
			GetSystemInfo(&sysinfo);
			int pcore_count = 0;
			int ecore_count = 0;

			DWORD num_processors = sysinfo.dwNumberOfProcessors;
			for (DWORD cpu = 0; cpu < num_processors; cpu++) {
				HANDLE current_thread = GetCurrentThread();
				DWORD_PTR cpu_mask = 1ULL << cpu;
				DWORD_PTR oldMask = SetThreadAffinityMask(current_thread, cpu_mask);

				if (oldMask != 0) {
					auto ct = getCoreType();
					if (ct == Pcore) { pcore_count++; }
					else if (ct == Ecore) { ecore_count++; }
					setNumCoresCpuid(getCoreType());
				}
				SetThreadAffinityMask(current_thread, oldMask);
			}
#elif defined(__linux__)
			int num_processors = (int)sysconf(_SC_NPROCESSORS_CONF);
			if (num_processors < 1) num_processors = 1;

			cpu_set_t orignal_mask;
			CPU_ZERO(&orignal_mask);
			sched_getaffinity(0, sizeof(cpu_set_t), &orignal_mask);

			for (int cpu =0; cpu < num_processors; cpu++) {
				cpu_set_t cpu_mask;
				CPU_ZERO(&cpu_mask);
				CPU_SET(cpu, &cpu_mask);
				if (sched_setaffinity(0, sizeof(cpu_set_t), &cpu_mask) == 0) {
					setNumCoresCpuid(getCoreType());
				}
			}
			// Restore original affinity mask
			sched_setaffinity(0, sizeof(cpu_set_t), &orignal_mask);
#else
			setNumCoresCpuid(Pcore);
#endif
		}
	}
	// End setNumCores using CPUID
	// Start setNumCores using Windows
	#if defined(_WIN32)
	// inline helper to coun bits in the KAFFINITY processor mask
	inline unsigned countBitsInMask(KAFFINITY mask)
	{
		return static_cast<unsigned>(__popcnt64(mask));
	}

	HybridCoreType getCoreTypeFromProcessorInfo(const SYSTEM_LOGICAL_PROCESSOR_INFORMATION_EX& procInfo)
	{
		// For hybrid CPUs, we need to distinguish between P-cores and E-cores
		// On Intel 12th gen+, EfficiencyClass in PROCESSOR_RELATIONSHIP indicates core type:
		//   0 = E-core (efficiency)
		//   1 = P-core (performance)
		if ( has(tHYBRID) && procInfo.Relationship == RelationProcessorCore) {
			const auto &proc = procInfo.Processor;
			// EfficiencyClass is only available on Windows 10 1903+ / Windows 11
#if defined(NTDDI_WIN10_VB) && NTDDI_VERSION >= NTDDI_WIN10_VB
			if (proc.EfficiencyClass == 0)
				return Ecore;
			else if (proc.EfficiencyClass == 1)
				return Pcore;
#endif
		}
		// Default to p_core if we can't determine the core_type
		return Pcore;
	}
	// 1. Use GetLogicalProcessorInformationEx to enumerate all processor cores
	//    and find their core type (P-core or E-core)
	void setNumCoresWin()
	{
		// Query buffer size
		DWORD bufferSize = 0;
		GetLogicalProcessorInformationEx(RelationAll, nullptr, &bufferSize);
		if (bufferSize == 0)
		{
			// Fallback to CPUID-based method if Windows API fails
			setNumCoresCpuid();
			return;
		}

		//allocate buffer
		LPBYTE buffer = new BYTE[bufferSize];
		if (!buffer) {
			// Fallback to CPUID-based method if memory allocation fails
			setNumCoresCpuid();
			return;
		}

		// Retrieve processor information
		if (!GetLogicalProcessorInformationEx(RelationAll, (PSYSTEM_LOGICAL_PROCESSOR_INFORMATION_EX)buffer, &bufferSize)) {
			// Fallback to CPUID-based method if Windows API fails
			delete[] buffer;
			setNumCoresCpuid();
			return;
		}

		// First pass: collect all processor cores with their types and masks
		// this will create a list of all cores with their core type and group affinity mask
		// std::vector<std::pair<HybridCoreType, GROUP_AFFINITY>> core_info;

		uint32_t pcoreCount = 0;
		uint32_t ecoreCount = 0;
		GROUP_AFFINITY pCoreAffinity = {};
		GROUP_AFFINITY eCoreAffinity = {};

		// Process the processor information here
		DWORD offset = 0;
		while(offset < bufferSize)
		{
			auto *info = (PSYSTEM_LOGICAL_PROCESSOR_INFORMATION_EX)(buffer + offset);
			if (info->Relationship == RelationProcessorCore)
			{
				HybridCoreType coreType = getCoreTypeFromProcessorInfo(*info);

				if ( coreType == Pcore ) {
					pcoreCount++;
					// Combine group masks for all P-cores
					for (WORD i = 0; i < info->Processor.GroupCount; i++) {
						pCoreAffinity.Mask |= info->Processor.GroupMask[i].Mask;
						pCoreAffinity.Group |= info->Processor.GroupMask[i].Group;
					}
				} else if ( coreType == Ecore ) {
					ecoreCount++;
					// Combine group masks for all E-cores
					for (WORD i = 0; i < info->Processor.GroupCount; i++) {
						eCoreAffinity.Mask |= info->Processor.GroupMask[i].Mask;
						eCoreAffinity.Group |= info->Processor.GroupMask[i].Group;
					}
				}
			}
			offset += info->Size;
		}

		// Set the number of cores for each core type
		numCores_[Pcore * maxCoreTypes + SmtLevel - 1] = countBitsInMask(pCoreAffinity.Mask) / pcoreCount;
		numCores_[Pcore * maxCoreTypes + CoreLevel - 1] = pcoreCount * numCores_[Pcore * maxCoreTypes + SmtLevel - 1];
		numCores_[Ecore * maxCoreTypes + SmtLevel - 1] = countBitsInMask(eCoreAffinity.Mask) / ecoreCount;
		numCores_[Ecore * maxCoreTypes + CoreLevel - 1] = ecoreCount * numCores_[Ecore * maxCoreTypes + SmtLevel - 1];

		// Free the allocated buffer
		delete[] buffer;
	}
	#endif // _WIN32
	// End setNumCores using Windows
	// Start setNumCores using Linux
	#if defined(__linux__)
	void setNumCoresLinux()
	{
		uint32_t data[4] = {};
		char node_path[] = "/sys/devices/system/node/online";
		uint32_t num_nodes = 0; // Default to 1 NUMA node
		FILE* f = fopen(node_path, "r");
		if (f) {
			char buf[256];
			if (fgets(buf, sizeof(buf), f)) {
				char buf_copy[256];
				strcpy(buf_copy, buf);
				char *token = strtok(buf_copy, ",\n");
				while (token) {
					// Trim whitespace
					while (*token == ' ')
						token++;
					if (strchr(token, '-')) {
						// Range format like "0-3"
						int start, end;
						if (sscanf(token, "%d-%d", &start, &end) == 2) {
							num_nodes += (end - start + 1);
						}
					} else {
						// Single Node
						num_nodes++;
					}
					token = strtok(nullptr, ",\n");
				}
			}
			fclose(f);
		}

		if (num_nodes == 0) num_nodes = 1; // Fallback to 1 if parsing failed
		int num_processors = (int)sysconf(_SC_NPROCESSORS_CONF);
		if (num_processors < 1) num_processors = 1;
		if (!has(tHYBRID) ) {
			// If hybrid is not supported, set all cores as P-cores
			// Get SMT level core count from CPUID
			getCpuid(0x1, data);
			int logicalProcessorCount = extractBit(data[1], 16, 23);
			// For SMT level, we need logical processors per physical core
			// This requires checking if hyper-threading is enabled
			int htt = extractBit(data[3], 28, 28);
			uint32_t smtCount = 1; // Default to 1 (no SMT)
			if (htt) {
				// Get physical core count to calculate SMT count
				getCpuid(0x4, data);
				int physicalCores = extractBit(data[0], 26, 31) + 1;
				if (physicalCores > 0) {
					smtCount = logicalProcessorCount / physicalCores;
				}
			}
			numCores_[Pcore * maxCoreTypes + SmtLevel - 1] = smtCount; // Assume no hyperthreading
			numCores_[Pcore * maxCoreTypes + CoreLevel - 1] = num_processors / num_nodes;

			// E-cores are set to 0 as they are not present
			numCores_[Ecore * maxCoreTypes + SmtLevel - 1] = 0;
			numCores_[Ecore * maxCoreTypes + CoreLevel - 1] = 0;
		} else {
			// Hybrid CPU handling
			uint32_t pcoreCount = 0;
			uint32_t ecoreCount = 0;

			cpu_set_t original_mask;
			CPU_ZERO(&original_mask);
			sched_getaffinity(0, sizeof(cpu_set_t), &original_mask);

			for (int cpu = 0; cpu < num_processors; cpu++) {
				cpu_set_t cpu_mask;
				CPU_ZERO(&cpu_mask);
				CPU_SET(cpu, &cpu_mask);
				if (sched_setaffinity(0, sizeof(cpu_set_t), &cpu_mask) == 0) {
					HybridCoreType coreType = getCoreType();
					if (coreType == Pcore) pcoreCount++;
					else if (coreType == Ecore) ecoreCount++;
				}
			}
			// Restore original affinity mask
			sched_setaffinity(0, sizeof(cpu_set_t), &original_mask);

			// Get SMT level core count from CPUID for P-cores
			getCpuid(0x1, data);
			int logicalProcessorCount = extractBit(data[1], 16, 23);
			int htt = extractBit(data[3], 28, 28);
			uint32_t smtCount = 1; // Default to 1 (no SMT)
			if (htt) {
				getCpuid(0x4, data);
				int physicalCores = extractBit(data[0], 26, 31) + 1;
				if (physicalCores > 0) {
					smtCount = logicalProcessorCount / physicalCores;
				}
			}

			numCores_[Pcore * maxCoreTypes + SmtLevel - 1] = smtCount;
			numCores_[Pcore * maxCoreTypes + CoreLevel - 1] = pcoreCount;

			numCores_[Ecore * maxCoreTypes + SmtLevel - 1] = 1; // E-cores don't have SMT cores, so set to 1
			numCores_[Ecore * maxCoreTypes + CoreLevel - 1] = ecoreCount;
		}
	}
	#endif // __linux__
	// End setNumCores using Linux

	void setNumCores()
	{
		// initialize all numCores_ to 0.
		for (size_t i = 0; i < maxCoreTypes * maxTopologyLevels; i++) {
					numCores_[i] = 1;
		}
		#if defined(_WIN32)
		setNumCoresWin();
		//setNumCoresCpuid();
#elif defined(__linux__)
		setNumCoresLinux();
		//setNumCoresCpuid();
#else
		// Fallback: use CPUID-based method
		setNumCoresCpuid();
#endif
	}

	// Start setCacheHierarchy using CPUID
	void setCacheHierarchyCpuid(HybridCoreType coreType)
	{
		if (!has(tHYBRID) ){
			coreType = Pcore;
		}
		uint32_t data[4] = {};
		dataCacheLevels_[coreType] = 0;
		if (has(tAMD)) {
			getCpuid(0x80000000, data);
			if (data[0] >= 0x8000001D) {
				// For modern AMD CPUs.
				dataCacheLevels_[coreType] = 0;
				for (uint32_t subLeaf = 0; dataCacheLevels_[coreType] < maxNumberCacheLevels; subLeaf++) {
					getCpuidEx(0x8000001D, subLeaf, data);
					int cacheType = extractBit(data[0], 0, 4);
					/*
					  cacheType
						00h - Null; no more caches
						01h - Data cache
						02h - Instrution cache
						03h - Unified cache
						04h-1Fh - Reserved
					*/
					if (cacheType == 0) break; // No more caches.
					if (cacheType == 0x2) continue; // Skip instruction cache.
					int fullyAssociative = extractBit(data[0], 9, 9);
					int numSharingCache = extractBit(data[0], 14, 25) + 1;
					int cacheNumWays = extractBit(data[1], 22, 31) + 1;
					int cachePhysPartitions = extractBit(data[1], 12, 21) + 1;
					int cacheLineSize = extractBit(data[1], 0, 11) + 1;
					int cacheNumSets = data[2] + 1;
					dataCacheSize_[dataCacheLevels_[coreType]] =
						cacheLineSize * cachePhysPartitions * cacheNumWays;
					if (fullyAssociative == 0) {
						dataCacheSize_[dataCacheLevels_[coreType]] *= cacheNumSets;
					}
					if (subLeaf > 0) {
						numSharingCache = local::min_(numSharingCache, (int)numCores_[1]);
						numSharingCache /= local::max_(1u, coresSharingDataCache_[0]);
					}
					coresSharingDataCache_[dataCacheLevels_[coreType]] = numSharingCache;
					dataCacheLevels_[coreType] += 1;
				}
				coresSharingDataCache_[0] = local::min_(1u, coresSharingDataCache_[0]);
			} else if (data[0] >= 0x80000006) {
				// For legacy AMD CPUs, use leaf 0x80000005 for L1 cache
				// and 0x80000006 for L2 and L3 cache.
				dataCacheLevels_[coreType] = 1;
				getCpuid(0x80000005, data);
				int l1dc_size = extractBit(data[2], 24, 31);
				dataCacheSize_[0] = l1dc_size * 1024;
				coresSharingDataCache_[0] = 1;
				getCpuid(0x80000006, data);
				// L2 cache
				int l2_assoc = extractBit(data[2], 12, 15);
				if (l2_assoc > 0) {
					dataCacheLevels_[coreType] = 2;
					int l2_size = extractBit(data[2], 16, 31);
					dataCacheSize_[1] = l2_size * 1024;
					coresSharingDataCache_[1] = 1;
				}
				// L3 cache
				int l3_assoc = extractBit(data[3], 12, 15);
				if (l3_assoc > 0) {
					dataCacheLevels_[coreType] = 3;
					int l3_size = extractBit(data[3], 18, 31);
					dataCacheSize_[2] = l3_size * 512 * 1024;
					coresSharingDataCache_[2] = numCores_[1];
				}
			}
		} else if (has(tINTEL)) {
			// Use the "Deterministic Cache Parameters" leaf is supported.
			const uint32_t NO_CACHE = 0;
			const uint32_t DATA_CACHE = 1;
			//const uint32_t INSTRUCTION_CACHE = 2;
			const uint32_t UNIFIED_CACHE = 3;
			uint32_t smt_width = 0;
			uint32_t logical_cores = 0;

			smt_width = numCores_[0];
			logical_cores = numCores_[1];

			/*
				Assumptions:
				the first level of data cache is not shared (which is the
				case for every existing architecture) and use this to
				determine the SMT width for arch not supporting leaf 11.
				when leaf 4 reports a number of core less than numCores_
				on socket reported by leaf 11, then it is a correct number
				of cores not an upperbound.
			*/
			for (int i = 0; dataCacheLevels_[coreType] < maxNumberCacheLevels; i++) {
				getCpuidEx(0x4, i, data);
				uint32_t cacheType = extractBit(data[0], 0, 4);
				if (cacheType == NO_CACHE) break;
				if (cacheType == DATA_CACHE || cacheType == UNIFIED_CACHE) {
					uint32_t actual_logical_cores = extractBit(data[0], 14, 25) + 1;
					if (logical_cores != 0) { // true only if leaf 0xB is supported and valid
						actual_logical_cores = local::min_(actual_logical_cores, logical_cores);
					}
					assert(actual_logical_cores != 0);
					dataCacheSize_[dataCacheLevels_[coreType]] =
						(extractBit(data[1], 22, 31) + 1)
						* (extractBit(data[1], 12, 21) + 1)
						* (extractBit(data[1], 0, 11) + 1)
						* (data[2] + 1);
					if (cacheType == DATA_CACHE && smt_width == 0) smt_width = actual_logical_cores;
					assert(smt_width != 0);
					coresSharingDataCache_[dataCacheLevels_[coreType]] = local::max_(actual_logical_cores / smt_width, 1u);
					dataCacheLevels_[coreType]++;
				}
			}
		}
	}

	void setCacheHierarchyCpuid()
	{
		if (!has(tHYBRID) ){
			setCacheHierarchyCpuid(Pcore);
		} else {
#if defined(_WIN32)
			SYSTEM_INFO sysinfo;
			GetSystemInfo(&sysinfo);

			DWORD num_processors = sysinfo.dwNumberOfProcessors;
			for (DWORD cpu = 0; cpu < num_processors; cpu++) {
				HANDLE current_thread = GetCurrentThread();
				DWORD_PTR cpu_mask = 1ULL << cpu;
				DWORD_PTR oldMask = SetThreadAffinityMask(current_thread, cpu_mask);

				if (oldMask != 0) {
					auto ct = getCoreType();
					setCacheHierarchyCpuid(getCoreType());
				}
				SetThreadAffinityMask(current_thread, oldMask);
			}
#elif defined(__linux__)
			int num_processors = (int)sysconf(_SC_NPROCESSORS_CONF);
			if (num_processors < 1) num_processors = 1;

			cpu_set_t orignal_mask;
			CPU_ZERO(&orignal_mask);
			sched_getaffinity(0, sizeof(cpu_set_t), &orignal_mask);

			for (int cpu =0; cpu < num_processors; cpu++) {
				cpu_set_t cpu_mask;
				CPU_ZERO(&cpu_mask);
				CPU_SET(cpu, &cpu_mask);
				if (sched_setaffinity(0, sizeof(cpu_set_t), &cpu_mask) == 0) {
					setCacheHierarchyCpuid(getCoreType());
				}
			}
			// Restore original affinity mask
			sched_setaffinity(0, sizeof(cpu_set_t), &orignal_mask);
#else
			setNumCoresCpuid(Pcore);
#endif
		}
	}
	// End setCacheHierarchy using CPUID
	// Start setCacheHierarchy using Windows
#if defined(_WIN32)
	void setCacheHierarchyWin()
	{
		// Query buffer size
		DWORD bufferSize = 0;
		GetLogicalProcessorInformationEx(RelationAll, nullptr, &bufferSize);
		if (bufferSize == 0) {
			// Fallback to CPUID-based method if Windows API fails
			setCacheHierarchyCpuid();
			return;
		}

		//allocate buffer
		LPBYTE buffer = new BYTE[bufferSize];
		if (!buffer) {
			// Fallback to CPUID-based method if memory allocation fails
			setCacheHierarchyCpuid();
			return;
		}

		// Retrieve processor information
		if (!GetLogicalProcessorInformationEx(RelationAll, (PSYSTEM_LOGICAL_PROCESSOR_INFORMATION_EX)buffer, &bufferSize)) {
			// Fallback to CPUID-based method if Windows API fails
			delete[] buffer;
			setCacheHierarchyCpuid();
			return;
		}

		// collect all the processor cores with their types and GROUP_AFFINITY masks
		// The core type is stored in the RelationProcessorCore info structures,
		// while the cache size and sharing information is stored in the RlationCache structures.
		// this will be used to indirectly map caches from the RelationCache structures
		// to core types by checking which core types intersect with the cache's processor affinity mask
		std::vector<std::pair<HybridCoreType, GROUP_AFFINITY>> core_info;

		DWORD offset = 0;
		while(offset < bufferSize)
		{
			auto *info = (PSYSTEM_LOGICAL_PROCESSOR_INFORMATION_EX)(buffer + offset);
			if (info->Relationship == RelationProcessorCore)
			{
				HybridCoreType coreType = getCoreTypeFromProcessorInfo(*info);

				for (WORD i = 0; i < info->Processor.GroupCount; i++) {
					core_info.emplace_back(coreType, info->Processor.GroupMask[i]);
				}
			}
			offset += info->Size;
		}

		offset = 0;
		while(offset < bufferSize)
		{
			auto *info = (PSYSTEM_LOGICAL_PROCESSOR_INFORMATION_EX)(buffer + offset);
			if (info->Relationship == RelationCache)
			{
				const auto &cache = info->Cache;
				bool cacheUsedByPcore = false;
				bool cacheUsedByEcore = false;
				for (size_t i = 0; i < core_info.size(); i++) {
					const auto& ct = core_info[i].first;
					const auto& ga = core_info[i].second;
					// Check if this core type's group affinity intersects with
					// the cache's group affinity mask.  The mask can
					// intersect with multiple core types since some cache's are
					// shared with cores of different types.
					if (ga.Group == cache.GroupMask.Group &&
						(ga.Mask & cache.GroupMask.Mask) != 0) {
						if (ct == Pcore) {
							cacheUsedByPcore = true;
						} else if (ct == Ecore) {
							cacheUsedByEcore = true;
						}
					}
				}

				if ( cache.Type == CacheData || cache.Type == CacheUnified ) {
					size_t level = cache.Level - 1;
					if (cacheUsedByPcore) {
						size_t pcoreIndex = Pcore * maxNumberCacheLevels;
						dataCacheSize_[pcoreIndex + level] = cache.CacheSize;
						coresSharingDataCache_[pcoreIndex + level] = countBitsInMask(cache.GroupMask.Mask);
						if (dataCacheLevels_[Pcore] < cache.Level) {
							dataCacheLevels_[Pcore] = cache.Level;
						}
					}
					if (cacheUsedByEcore) {
						size_t ecoreIndex = Ecore * maxNumberCacheLevels;
						dataCacheSize_[ecoreIndex + level] = cache.CacheSize;
						coresSharingDataCache_[ecoreIndex + level] = countBitsInMask(cache.GroupMask.Mask);
						if (dataCacheLevels_[Ecore] < cache.Level) {
							dataCacheLevels_[Ecore] = cache.Level;
						}
					}
				}
			}
			offset += info->Size;
		}
		// Free the allocated buffer
		delete[] buffer;
	}
#endif // _WIN32
#if defined(__linux__)
	// Helper function to parse cache information from sysfs for a specific CPU and core type
	bool parseCacheFromSysfs(int cpu, HybridCoreType coreType) {
		bool success = false;
		char cache_base_path[64];
		snprintf(cache_base_path, sizeof(cache_base_path), "/sys/devices/system/cpu/cpu%d/cache", cpu);

		// Try to read cache information from sysfs
		for (int cache_idx = 0; cache_idx < 10; cache_idx++) {
			char cache_path[96];
			snprintf(cache_path, sizeof(cache_path), "%s/index%d", cache_base_path, cache_idx);
			// Read cache type - skip if not Data or Unified
			char type_path[128];
			snprintf(type_path, sizeof(type_path), "%s/type", cache_path);
			FILE* type_file = fopen(type_path, "r");
			if (!type_file) continue;

			char cache_type_str[64] = {0};
			bool valid_type = false;
			if (fgets(cache_type_str, sizeof(cache_type_str), type_file)) {
				// Remove newline
				char* newline = strchr(cache_type_str, '\n');
				if (newline) *newline = '\0';
				// Only process Data and Unified caches (skip Instruction)
				if (strstr(cache_type_str, "Instruction") == nullptr) {
					valid_type = true;
				}
			}
			fclose(type_file);
			if (!valid_type) continue;

			// Read cache level
			char level_path[128];
			snprintf(level_path, sizeof(level_path), "%s/level", cache_path);
			FILE* level_file = fopen(level_path, "r");
			int cache_level = 0;
			if (level_file) {
				if (fscanf(level_file, "%d", &cache_level) == 1) {
					if (cache_level > 0 && cache_level <= (int)maxNumberCacheLevels) {
						// Valid level
					} else {
						cache_level = 0;
					}
				}
				fclose(level_file);
			}
			if (cache_level == 0) continue;

			// Read cache size
			char size_path[128];
			snprintf(size_path, sizeof(size_path), "%s/size", cache_path);
			FILE* size_file = fopen(size_path, "r");
			uint32_t cache_size = 0;
			if (size_file) {
				char size_str[64];
				if (fgets(size_str, sizeof(size_str), size_file)) {
					int size_val;
					char size_unit = ' ';
					if (sscanf(size_str, "%d%c", &size_val, &size_unit) >= 1) {
						cache_size = size_val;
						if (size_unit == 'K' || size_unit == 'k') {
							cache_size *= 1024;
						} else if (size_unit == 'M' || size_unit == 'm') {
							cache_size *= 1024 * 1024;
						}
					}
				}
				fclose(size_file);
			}
			if (cache_size == 0) continue;

			// Read shared CPU list to determine sharing count
			char shared_path[128];
			snprintf(shared_path, sizeof(shared_path), "%s/shared_cpu_list", cache_path);
			uint32_t num_sharing_cores = 1;
			FILE* shared_file = fopen(shared_path, "r");
			if (shared_file) {
				char shared_str[256];
				if (fgets(shared_str, sizeof(shared_str), shared_file)) {
					// Count logical processors in the shared list
					num_sharing_cores = 0;
					char shared_str_copy[256];
					strncpy(shared_str_copy, shared_str, sizeof(shared_str_copy) - 1);
					shared_str_copy[sizeof(shared_str_copy) - 1] = '\0';
					char* token = strtok(shared_str_copy, ",\n");
					while (token) {
						// Trim whitespace
						while (*token == ' ') token++;
						if (strchr(token, '-')) {
							// Range format like "0-3"
							int start, end;
							if (sscanf(token, "%d-%d", &start, &end) == 2) {
								num_sharing_cores += (end - start + 1);
							}
						} else {
							// Single CPU
							num_sharing_cores++;
						}
						token = strtok(nullptr, ",\n");
					}
					if (num_sharing_cores == 0) num_sharing_cores = 1;
				}
				fclose(shared_file);
			}

			// Store the cache information for the specified core type
			size_t idx = coreType * maxNumberCacheLevels + (cache_level - 1);
			dataCacheSize_[idx] = cache_size;

			// Work around solution for a way to determin the number of physical cores sharing
			// the L3 cache on hybrid CPUs. This solution assumes the L3 cache is shared by all
			// the P-cores and if the core is an SMT (hyperthreaded) core this will subtract
			// the number of SMT P-cores from the total number of cores sharing the cache to get
			// the number of physical cores sharing the cache.
			if (cache_level == 3 && getNumCores(SmtLevel, Pcore) > 1) {
				coresSharingDataCache_[idx] = num_sharing_cores - getNumCores(CoreLevel, Pcore);
			} else {
				coresSharingDataCache_[idx] = num_sharing_cores;
			}
			if (dataCacheLevels_[coreType] < (uint32_t)cache_level) {
				dataCacheLevels_[coreType] = (uint32_t)cache_level;
			}
			success = true;
		}
		
		return success;
	}

	inline bool setCpuAffinityLinux(int cpu) {
	#ifdef __linux__
		cpu_set_t cpuset;
		CPU_ZERO(&cpuset);
		CPU_SET(cpu, &cpuset);
	return sched_setaffinity(0, sizeof(cpu_set_t), &cpuset) == 0;
	#else
		return false;
	#endif
	}

	// Helper function to restore original CPU affinity
	inline void restoreCpuAffinityLinux(const cpu_set_t *original_affinity_mask) {
	#ifdef __linux__
		sched_setaffinity(0, sizeof(cpu_set_t), original_affinity_mask);
	#endif
	}

	void setCacheHierarchyLinux()
	{
		// Linux implementation to set cache hierarchy per core type
		// For simplicity, we will assume all cores are P-cores in this example
		// A more complete implementation would parse /sys/devices/system/cpu/cpu*/cache/index*/ files
		if (!has(tHYBRID) ) {
			// Parse cache information from sysfs for cpu0 as P-core
			bool success = parseCacheFromSysfs(0, Pcore);

			// If we couldn't read any cache info from sysfs, fall back to CPUID
			if (!success || dataCacheLevels_[Pcore] == 0) {
				setCacheHierarchyCpuid(Pcore);
			}
		} else {
			// Hybrid CPU handling - iterate through CPUs to detect cache for each core type
			int num_processors = (int)sysconf(_SC_NPROCESSORS_CONF);
			if (num_processors < 1) num_processors = 1;
			
			// Save original affinity to restore later
			cpu_set_t original_mask;
			CPU_ZERO(&original_mask);
			sched_getaffinity(0, sizeof(cpu_set_t), &original_mask);

			// Track which core types have been processed
			bool pcore_found = false;
			bool ecore_found = false;
			bool pcore_success = false;
			bool ecore_success = false;

			// Iterate through all CPUs until all core types are found
			for (int cpu = 0; cpu < num_processors && !(pcore_found && ecore_found); cpu++) {
				// Set affinity to this CPU
				if (!setCpuAffinityLinux(cpu)) {
					continue; // Skip if affinity setting fails
				}

				// Get the core type for this CPU
				HybridCoreType coreType = getCoreType();

				// Check if we've already processed this core type
				if (coreType == Pcore && !pcore_found) {
					if (parseCacheFromSysfs(cpu, Pcore)) {
						pcore_found = true;
						pcore_success = true;
					}
				} else if (coreType == Ecore && !ecore_found) {
					if (parseCacheFromSysfs(cpu, Ecore)) {
						ecore_found = true;
						ecore_success = true;
					}
				}
			}

			// Restore original affinity
			restoreCpuAffinityLinux(&original_mask);

			// If we couldn't read cache info from sysfs, fall back to CPUID
			if (!pcore_success || dataCacheLevels_[Pcore] == 0) {
				setCacheHierarchyCpuid(Pcore);
			}
			if (!ecore_success || dataCacheLevels_[Ecore] == 0) {
				setCacheHierarchyCpuid(Ecore);
			}
		}
	}
#endif // __linux__

	void setCacheHierarchy()
	{
		// Initialize all cache hierarchy arrays to 0
		for (size_t i = 0; i < maxCoreTypes * maxNumberCacheLevels; i++) {
			dataCacheSize_[i] = 0;
			coresSharingDataCache_[i] = 0;
		}
		for (size_t i = 0; i < maxCoreTypes; i++) {
			dataCacheLevels_[i] = 0;
		}
		#if defined(_WIN32)
		setCacheHierarchyWin();
		//setCacheHierarchyCpuid();
#elif defined(__linux__)
		setCacheHierarchyLinux();
		// setCacheHierarchyCpuid();
#else
		// Fallback: use CPUID-based method
		setCacheHierarchyCpuid();
#endif
	}
public:
	int model;
	int family;
	int stepping;
	int extModel;
	int extFamily;
	int displayFamily; // family + extFamily
	int displayModel; // model + extModel

		uint32_t getNumCores(CpuTopologyLevel level, HybridCoreType coreType) const {
		if (!has(tHYBRID)) {
			coreType = Pcore;
		}
		size_t coreTypeIndex = coreType * maxCoreTypes;
			switch (level) {
			case SmtLevel: return numCores_[coreTypeIndex + level - 1];
			case CoreLevel: return numCores_[coreTypeIndex + level - 1] / numCores_[coreTypeIndex + SmtLevel - 1];
			default: XBYAK_THROW_RET(ERR_X2APIC_IS_NOT_SUPPORTED, 0)

		}
	}

	uint32_t getNumCores(CpuTopologyLevel level) {
		if (has(tHYBRID)) {
			switch (level) {
			case SmtLevel: return local::max_(getNumCores(SmtLevel, Pcore), getNumCores(SmtLevel, Ecore));
			case CoreLevel: return getNumCores(CoreLevel, Pcore) + getNumCores(CoreLevel, Ecore);
			default: XBYAK_THROW_RET(ERR_X2APIC_IS_NOT_SUPPORTED, 0)
			}
		} else {
			switch (level) {
			case SmtLevel: return numCores_[Pcore * maxCoreTypes + level - 1];
			case CoreLevel: return numCores_[Pcore * maxCoreTypes + level - 1] / numCores_[Pcore * maxCoreTypes + SmtLevel - 1];
			default: XBYAK_THROW_RET(ERR_X2APIC_IS_NOT_SUPPORTED, 0)
			}
		}
	}

	uint32_t getDataCacheLevels(HybridCoreType coreType) const {
		if (!has(tHYBRID)) {
			coreType = Pcore;
		}
		return dataCacheLevels_[coreType];
	}
	uint32_t getDataCacheLevels() const { return dataCacheLevels_[Pcore]; }
	uint32_t getCoresSharingDataCache(uint32_t i) const
	{
		if (i >= dataCacheLevels_[Pcore]) XBYAK_THROW_RET(ERR_BAD_PARAMETER, 0)
		return coresSharingDataCache_[i];
	}

	uint32_t getCoresSharingDataCache(uint32_t i, HybridCoreType coreType) const
	{
		if (!has(tHYBRID)) {
			coreType = Pcore;
		}
		if (i >= dataCacheLevels_[coreType]) XBYAK_THROW_RET(ERR_BAD_PARAMETER, 0)
		return coresSharingDataCache_[coreType * maxNumberCacheLevels + i];
	}

	uint32_t getDataCacheSize(uint32_t i) const
	{
		if (i >= dataCacheLevels_[Pcore]) XBYAK_THROW_RET(ERR_BAD_PARAMETER, 0)
		return dataCacheSize_[i];
	}

	uint32_t getDataCacheSize(uint32_t i, HybridCoreType coreType) const
	{
		if (!has(tHYBRID)) {
			coreType = Pcore;
		}
		if (i >= dataCacheLevels_[coreType]) XBYAK_THROW_RET(ERR_BAD_PARAMETER, 0)
		return dataCacheSize_[coreType * maxNumberCacheLevels + i];
	}

	/*
		data[] = { eax, ebx, ecx, edx }
	*/
	static inline void getCpuidEx(uint32_t eaxIn, uint32_t ecxIn, uint32_t data[4])
	{
#ifdef XBYAK_INTEL_CPU_SPECIFIC
	#ifdef _WIN32
		__cpuidex(reinterpret_cast<int*>(data), eaxIn, ecxIn);
	#else
		__cpuid_count(eaxIn, ecxIn, data[0], data[1], data[2], data[3]);
	#endif
#else
		(void)eaxIn;
		(void)ecxIn;
		(void)data;
#endif
	}
	static inline void getCpuid(uint32_t eaxIn, uint32_t data[4])
	{
		getCpuidEx(eaxIn, 0, data);
	}
	static inline uint64_t getXfeature()
	{
#ifdef XBYAK_INTEL_CPU_SPECIFIC
	#ifdef _MSC_VER
		return _xgetbv(0);
	#else
		uint32_t eax, edx;
		// xgetvb is not support on gcc 4.2
//		__asm__ volatile("xgetbv" : "=a"(eax), "=d"(edx) : "c"(0));
		__asm__ volatile(".byte 0x0f, 0x01, 0xd0" : "=a"(eax), "=d"(edx) : "c"(0));
		return ((uint64_t)edx << 32) | eax;
	#endif
#else
		return 0;
#endif
	}

#define XBYAK_SPLIT_ID(id) ((0 <= id && id < 64) ? (1ull << (id % 64)) : 0), (id >= 64 ? (1ull << (id % 64)) : 0)
#if (__cplusplus >= 201103) || (defined(_MSC_VER) && (_MSC_VER >= 1700)) /* VS2012 */
	#define XBYAK_DEFINE_TYPE(id, NAME) static const constexpr local::TypeT<XBYAK_SPLIT_ID(id)> NAME{}
#else
	#define XBYAK_DEFINE_TYPE(id, NAME) static const local::TypeT<XBYAK_SPLIT_ID(id)> NAME
#endif
	XBYAK_DEFINE_TYPE(0, tMMX);
	XBYAK_DEFINE_TYPE(1, tMMX2);
	XBYAK_DEFINE_TYPE(2, tCMOV);
	XBYAK_DEFINE_TYPE(3, tSSE);
	XBYAK_DEFINE_TYPE(4, tSSE2);
	XBYAK_DEFINE_TYPE(5, tSSE3);
	XBYAK_DEFINE_TYPE(6, tSSSE3);
	XBYAK_DEFINE_TYPE(7, tSSE41);
	XBYAK_DEFINE_TYPE(8, tSSE42);
	XBYAK_DEFINE_TYPE(9, tPOPCNT);
	XBYAK_DEFINE_TYPE(10, tAESNI);
	XBYAK_DEFINE_TYPE(11, tAVX512_FP16);
	XBYAK_DEFINE_TYPE(12, tOSXSAVE);
	XBYAK_DEFINE_TYPE(13, tPCLMULQDQ);
	XBYAK_DEFINE_TYPE(14, tAVX);
	XBYAK_DEFINE_TYPE(15, tFMA);
	XBYAK_DEFINE_TYPE(16, t3DN);
	XBYAK_DEFINE_TYPE(17, tE3DN);
	XBYAK_DEFINE_TYPE(18, tWAITPKG);
	XBYAK_DEFINE_TYPE(19, tRDTSCP);
	XBYAK_DEFINE_TYPE(20, tAVX2);
	XBYAK_DEFINE_TYPE(21, tBMI1); // andn, bextr, blsi, blsmsk, blsr, tzcnt
	XBYAK_DEFINE_TYPE(22, tBMI2); // bzhi, mulx, pdep, pext, rorx, sarx, shlx, shrx
	XBYAK_DEFINE_TYPE(23, tLZCNT);
	XBYAK_DEFINE_TYPE(24, tINTEL);
	XBYAK_DEFINE_TYPE(25, tAMD);
	XBYAK_DEFINE_TYPE(26, tENHANCED_REP); // enhanced rep movsb/stosb
	XBYAK_DEFINE_TYPE(27, tRDRAND);
	XBYAK_DEFINE_TYPE(28, tADX); // adcx, adox
	XBYAK_DEFINE_TYPE(29, tRDSEED); // rdseed
	XBYAK_DEFINE_TYPE(30, tSMAP); // stac
	XBYAK_DEFINE_TYPE(31, tHLE); // xacquire, xrelease, xtest
	XBYAK_DEFINE_TYPE(32, tRTM); // xbegin, xend, xabort
	XBYAK_DEFINE_TYPE(33, tF16C); // vcvtph2ps, vcvtps2ph
	XBYAK_DEFINE_TYPE(34, tMOVBE); // mobve
	XBYAK_DEFINE_TYPE(35, tAVX512F);
	XBYAK_DEFINE_TYPE(36, tAVX512DQ);
	XBYAK_DEFINE_TYPE(37, tAVX512_IFMA);
	XBYAK_DEFINE_TYPE(37, tAVX512IFMA);// = tAVX512_IFMA;
	XBYAK_DEFINE_TYPE(38, tAVX512PF);
	XBYAK_DEFINE_TYPE(39, tAVX512ER);
	XBYAK_DEFINE_TYPE(40, tAVX512CD);
	XBYAK_DEFINE_TYPE(41, tAVX512BW);
	XBYAK_DEFINE_TYPE(42, tAVX512VL);
	XBYAK_DEFINE_TYPE(43, tAVX512_VBMI);
	XBYAK_DEFINE_TYPE(43, tAVX512VBMI); // = tAVX512_VBMI; // changed by Intel's manual
	XBYAK_DEFINE_TYPE(44, tAVX512_4VNNIW);
	XBYAK_DEFINE_TYPE(45, tAVX512_4FMAPS);
	XBYAK_DEFINE_TYPE(46, tPREFETCHWT1);
	XBYAK_DEFINE_TYPE(47, tPREFETCHW);
	XBYAK_DEFINE_TYPE(48, tSHA);
	XBYAK_DEFINE_TYPE(49, tMPX);
	XBYAK_DEFINE_TYPE(50, tAVX512_VBMI2);
	XBYAK_DEFINE_TYPE(51, tGFNI);
	XBYAK_DEFINE_TYPE(52, tVAES);
	XBYAK_DEFINE_TYPE(53, tVPCLMULQDQ);
	XBYAK_DEFINE_TYPE(54, tAVX512_VNNI);
	XBYAK_DEFINE_TYPE(55, tAVX512_BITALG);
	XBYAK_DEFINE_TYPE(56, tAVX512_VPOPCNTDQ);
	XBYAK_DEFINE_TYPE(57, tAVX512_BF16);
	XBYAK_DEFINE_TYPE(58, tAVX512_VP2INTERSECT);
	XBYAK_DEFINE_TYPE(59, tAMX_TILE);
	XBYAK_DEFINE_TYPE(60, tAMX_INT8);
	XBYAK_DEFINE_TYPE(61, tAMX_BF16);
	XBYAK_DEFINE_TYPE(62, tAVX_VNNI);
	XBYAK_DEFINE_TYPE(63, tCLFLUSHOPT);
	XBYAK_DEFINE_TYPE(64, tCLDEMOTE);
	XBYAK_DEFINE_TYPE(65, tMOVDIRI);
	XBYAK_DEFINE_TYPE(66, tMOVDIR64B);
	XBYAK_DEFINE_TYPE(67, tCLZERO); // AMD Zen
	XBYAK_DEFINE_TYPE(68, tAMX_FP16);
	XBYAK_DEFINE_TYPE(69, tAVX_VNNI_INT8);
	XBYAK_DEFINE_TYPE(70, tAVX_NE_CONVERT);
	XBYAK_DEFINE_TYPE(71, tAVX_IFMA);
	XBYAK_DEFINE_TYPE(72, tRAO_INT);
	XBYAK_DEFINE_TYPE(73, tCMPCCXADD);
	XBYAK_DEFINE_TYPE(74, tPREFETCHITI);
	XBYAK_DEFINE_TYPE(75, tSERIALIZE);
	XBYAK_DEFINE_TYPE(76, tUINTR);
	XBYAK_DEFINE_TYPE(77, tXSAVE);
	XBYAK_DEFINE_TYPE(78, tSHA512);
	XBYAK_DEFINE_TYPE(79, tSM3);
	XBYAK_DEFINE_TYPE(80, tSM4);
	XBYAK_DEFINE_TYPE(81, tAVX_VNNI_INT16);
	XBYAK_DEFINE_TYPE(82, tAPX_F);
	XBYAK_DEFINE_TYPE(83, tAVX10);
	XBYAK_DEFINE_TYPE(84, tAESKLE);
	XBYAK_DEFINE_TYPE(85, tWIDE_KL);
	XBYAK_DEFINE_TYPE(86, tKEYLOCKER);
	XBYAK_DEFINE_TYPE(87, tKEYLOCKER_WIDE);
	XBYAK_DEFINE_TYPE(88, tSSE4a);
	XBYAK_DEFINE_TYPE(89, tCLWB);
	XBYAK_DEFINE_TYPE(90, tTSXLDTRK);
	XBYAK_DEFINE_TYPE(91, tAMX_TRANSPOSE);
	XBYAK_DEFINE_TYPE(92, tAMX_TF32);
	XBYAK_DEFINE_TYPE(93, tAMX_AVX512);
	XBYAK_DEFINE_TYPE(94, tAMX_MOVRS);
	XBYAK_DEFINE_TYPE(95, tAMX_FP8);
	XBYAK_DEFINE_TYPE(96, tMOVRS);
	XBYAK_DEFINE_TYPE(97, tHYBRID);

#undef XBYAK_SPLIT_ID
#undef XBYAK_DEFINE_TYPE

	Cpu()
		: type_()
		, numCores_()
		, dataCacheSize_()
		, coresSharingDataCache_()
		, dataCacheLevels_()
		, avx10version_(0)
	{
		uint32_t data[4] = {};
		const uint32_t& eax = data[0];
		const uint32_t& ebx = data[1];
		const uint32_t& ecx = data[2];
		const uint32_t& edx = data[3];
		getCpuid(0, data);
		const uint32_t maxNum = eax;
		if (isEqualStr(ebx, ecx, edx, "AuthenticAMD")) {
			type_ |= tAMD;
			getCpuid(0x80000001, data);
			if (edx & (1U << 31)) {
				type_ |= t3DN;
				// 3DNow! implies support for PREFETCHW on AMD
				type_ |= tPREFETCHW;
			}

			if (edx & (1U << 29)) {
				// Long mode implies support for PREFETCHW on AMD
				type_ |= tPREFETCHW;
			}
		} else if (isEqualStr(ebx, ecx, edx, "GenuineIntel")) {
			type_ |= tINTEL;
		}

		// Extended flags information
		getCpuid(0x80000000, data);
		const uint32_t maxExtendedNum = eax;
		if (maxExtendedNum >= 0x80000001) {
			getCpuid(0x80000001, data);

			if (ecx & (1U << 5)) type_ |= tLZCNT;
			if (ecx & (1U << 6)) type_ |= tSSE4a;
			if (ecx & (1U << 8)) type_ |= tPREFETCHW;
			if (edx & (1U << 15)) type_ |= tCMOV;
			if (edx & (1U << 22)) type_ |= tMMX2;
			if (edx & (1U << 27)) type_ |= tRDTSCP;
			if (edx & (1U << 30)) type_ |= tE3DN;
			if (edx & (1U << 31)) type_ |= t3DN;
		}

		if (maxExtendedNum >= 0x80000008) {
			getCpuid(0x80000008, data);
			if (ebx & (1U << 0)) type_ |= tCLZERO;
		}

		getCpuid(1, data);
		if (ecx & (1U << 0)) type_ |= tSSE3;
		if (ecx & (1U << 1)) type_ |= tPCLMULQDQ;
		if (ecx & (1U << 9)) type_ |= tSSSE3;
		if (ecx & (1U << 19)) type_ |= tSSE41;
		if (ecx & (1U << 20)) type_ |= tSSE42;
		if (ecx & (1U << 22)) type_ |= tMOVBE;
		if (ecx & (1U << 23)) type_ |= tPOPCNT;
		if (ecx & (1U << 25)) type_ |= tAESNI;
		if (ecx & (1U << 26)) type_ |= tXSAVE;
		if (ecx & (1U << 27)) type_ |= tOSXSAVE;
		if (ecx & (1U << 29)) type_ |= tF16C;
		if (ecx & (1U << 30)) type_ |= tRDRAND;

		if (edx & (1U << 15)) type_ |= tCMOV;
		if (edx & (1U << 23)) type_ |= tMMX;
		if (edx & (1U << 25)) type_ |= tMMX2 | tSSE;
		if (edx & (1U << 26)) type_ |= tSSE2;

		if (type_ & tOSXSAVE) {
			// check XFEATURE_ENABLED_MASK[2:1] = '11b'
			uint64_t bv = getXfeature();
			if ((bv & 6) == 6) {
				if (ecx & (1U << 12)) type_ |= tFMA;
				if (ecx & (1U << 28)) type_ |= tAVX;
				// do *not* check AVX-512 state on macOS because it has on-demand AVX-512 support
#if !defined(__APPLE__)
				if (((bv >> 5) & 7) == 7)
#endif
				{
					getCpuidEx(7, 0, data);
					if (ebx & (1U << 16)) type_ |= tAVX512F;
					if (type_ & tAVX512F) {
						if (ebx & (1U << 17)) type_ |= tAVX512DQ;
						if (ebx & (1U << 21)) type_ |= tAVX512_IFMA;
						if (ebx & (1U << 26)) type_ |= tAVX512PF;
						if (ebx & (1U << 27)) type_ |= tAVX512ER;
						if (ebx & (1U << 28)) type_ |= tAVX512CD;
						if (ebx & (1U << 30)) type_ |= tAVX512BW;
						if (ebx & (1U << 31)) type_ |= tAVX512VL;
						if (ecx & (1U << 1)) type_ |= tAVX512_VBMI;
						if (ecx & (1U << 6)) type_ |= tAVX512_VBMI2;
						if (ecx & (1U << 11)) type_ |= tAVX512_VNNI;
						if (ecx & (1U << 12)) type_ |= tAVX512_BITALG;
						if (ecx & (1U << 14)) type_ |= tAVX512_VPOPCNTDQ;
						if (edx & (1U << 2)) type_ |= tAVX512_4VNNIW;
						if (edx & (1U << 3)) type_ |= tAVX512_4FMAPS;
						if (edx & (1U << 8)) type_ |= tAVX512_VP2INTERSECT;
						if ((type_ & tAVX512BW) && (edx & (1U << 23))) type_ |= tAVX512_FP16;
					}
				}
			}
		}
		if (maxNum >= 7) {
			getCpuidEx(7, 0, data);
			const uint32_t maxNumSubLeaves = eax;
			if (type_ & tAVX && (ebx & (1U << 5))) type_ |= tAVX2;
			if (ebx & (1U << 3)) type_ |= tBMI1;
			if (ebx & (1U << 4)) type_ |= tHLE;
			if (ebx & (1U << 8)) type_ |= tBMI2;
			if (ebx & (1U << 9)) type_ |= tENHANCED_REP;
			if (ebx & (1U << 11)) type_ |= tRTM;
			if (ebx & (1U << 14)) type_ |= tMPX;
			if (ebx & (1U << 18)) type_ |= tRDSEED;
			if (ebx & (1U << 19)) type_ |= tADX;
			if (ebx & (1U << 20)) type_ |= tSMAP;
			if (ebx & (1U << 23)) type_ |= tCLFLUSHOPT;
			if (ebx & (1U << 24)) type_ |= tCLWB;
			if (ebx & (1U << 29)) type_ |= tSHA;
			if (ecx & (1U << 0)) type_ |= tPREFETCHWT1;
			if (ecx & (1U << 5)) type_ |= tWAITPKG;
			if (ecx & (1U << 8)) type_ |= tGFNI;
			if (ecx & (1U << 9)) type_ |= tVAES;
			if (ecx & (1U << 10)) type_ |= tVPCLMULQDQ;
			if (ecx & (1U << 23)) type_ |= tKEYLOCKER;
			if (ecx & (1U << 25)) type_ |= tCLDEMOTE;
			if (ecx & (1U << 27)) type_ |= tMOVDIRI;
			if (ecx & (1U << 28)) type_ |= tMOVDIR64B;
			if (edx & (1U << 5)) type_ |= tUINTR;
			if (edx & (1U << 14)) type_ |= tSERIALIZE;
			if (edx & (1U << 15)) type_ |= tHYBRID;
			if (edx & (1U << 16)) type_ |= tTSXLDTRK;
			if (edx & (1U << 22)) type_ |= tAMX_BF16;
			if (edx & (1U << 24)) type_ |= tAMX_TILE;
			if (edx & (1U << 25)) type_ |= tAMX_INT8;
			if (maxNumSubLeaves >= 1) {
				getCpuidEx(7, 1, data);
				if (eax & (1U << 0)) type_ |= tSHA512;
				if (eax & (1U << 1)) type_ |= tSM3;
				if (eax & (1U << 2)) type_ |= tSM4;
				if (eax & (1U << 3)) type_ |= tRAO_INT;
				if (eax & (1U << 4)) type_ |= tAVX_VNNI;
				if (type_ & tAVX512F) {
					if (eax & (1U << 5)) type_ |= tAVX512_BF16;
				}
				if (eax & (1U << 7)) type_ |= tCMPCCXADD;
				if (eax & (1U << 21)) type_ |= tAMX_FP16;
				if (eax & (1U << 23)) type_ |= tAVX_IFMA;
				if (eax & (1U << 31)) type_ |= tMOVRS;
				if (edx & (1U << 4)) type_ |= tAVX_VNNI_INT8;
				if (edx & (1U << 5)) type_ |= tAVX_NE_CONVERT;
				if (edx & (1U << 10)) type_ |= tAVX_VNNI_INT16;
				if (edx & (1U << 14)) type_ |= tPREFETCHITI;
				if (edx & (1U << 19)) type_ |= tAVX10;
				if (edx & (1U << 21)) type_ |= tAPX_F;

				getCpuidEx(0x1e, 1, data);
				if (eax & (1U << 4)) type_ |= tAMX_FP8;
				if (eax & (1U << 5)) type_ |= tAMX_TRANSPOSE;
				if (eax & (1U << 6)) type_ |= tAMX_TF32;
				if (eax & (1U << 7)) type_ |= tAMX_AVX512;
				if (eax & (1U << 8)) type_ |= tAMX_MOVRS;
			}
		}
		if (maxNum >= 0x19) {
			getCpuidEx(0x19, 0, data);
			if (ebx & (1U << 0)) type_ |= tAESKLE;
			if (ebx & (1U << 2)) type_ |= tWIDE_KL;
			if (type_ & (tKEYLOCKER|tAESKLE|tWIDE_KL)) type_ |= tKEYLOCKER_WIDE;
		}
		if (has(tAVX10) && maxNum >= 0x24) {
			getCpuidEx(0x24, 0, data);
			avx10version_ = ebx & mask(7);
		}
		setFamily();
		setNumCores();
		setCacheHierarchy();
	}
	void putFamily() const
	{
#ifndef XBYAK_ONLY_CLASS_CPU
		printf("family=%d, model=%X, stepping=%d, extFamily=%d, extModel=%X\n",
			family, model, stepping, extFamily, extModel);
		printf("display:family=%X, model=%X\n", displayFamily, displayModel);
#endif
	}
	bool has(const Type& type) const
	{
		return (type & type_) == type;
	}
	int getAVX10version() const { return avx10version_; }
};
#ifdef _MSC_VER
	#pragma warning(pop)
#endif

#ifndef XBYAK_ONLY_CLASS_CPU
class Clock {
public:
	static inline uint64_t getRdtsc()
	{
#ifdef XBYAK_INTEL_CPU_SPECIFIC
	#ifdef _MSC_VER
		return __rdtsc();
	#else
		uint32_t eax, edx;
		__asm__ volatile("rdtsc" : "=a"(eax), "=d"(edx));
		return ((uint64_t)edx << 32) | eax;
	#endif
#else
		// TODO: Need another impl of Clock or rdtsc-equivalent for non-x86 cpu
		return 0;
#endif
	}
	Clock()
		: clock_(0)
		, count_(0)
	{
	}
	void begin()
	{
		clock_ -= getRdtsc();
	}
	void end()
	{
		clock_ += getRdtsc();
		count_++;
	}
	int getCount() const { return count_; }
	uint64_t getClock() const { return clock_; }
	void clear() { count_ = 0; clock_ = 0; }
private:
	uint64_t clock_;
	int count_;
};

#ifdef XBYAK64
const int UseRCX = 1 << 6;
const int UseRDX = 1 << 7;

class Pack {
	static const size_t maxTblNum = 15;
	Xbyak::Reg64 tbl_[maxTblNum];
	size_t n_;
public:
	Pack() : tbl_(), n_(0) {}
	Pack(const Xbyak::Reg64 *tbl, size_t n) { init(tbl, n); }
	Pack(const Pack& rhs)
		: n_(rhs.n_)
	{
		for (size_t i = 0; i < n_; i++) tbl_[i] = rhs.tbl_[i];
	}
	Pack& operator=(const Pack& rhs)
	{
		n_ = rhs.n_;
		for (size_t i = 0; i < n_; i++) tbl_[i] = rhs.tbl_[i];
		return *this;
	}
	Pack(const Xbyak::Reg64& t0)
	{ n_ = 1; tbl_[0] = t0; }
	Pack(const Xbyak::Reg64& t1, const Xbyak::Reg64& t0)
	{ n_ = 2; tbl_[0] = t0; tbl_[1] = t1; }
	Pack(const Xbyak::Reg64& t2, const Xbyak::Reg64& t1, const Xbyak::Reg64& t0)
	{ n_ = 3; tbl_[0] = t0; tbl_[1] = t1; tbl_[2] = t2; }
	Pack(const Xbyak::Reg64& t3, const Xbyak::Reg64& t2, const Xbyak::Reg64& t1, const Xbyak::Reg64& t0)
	{ n_ = 4; tbl_[0] = t0; tbl_[1] = t1; tbl_[2] = t2; tbl_[3] = t3; }
	Pack(const Xbyak::Reg64& t4, const Xbyak::Reg64& t3, const Xbyak::Reg64& t2, const Xbyak::Reg64& t1, const Xbyak::Reg64& t0)
	{ n_ = 5; tbl_[0] = t0; tbl_[1] = t1; tbl_[2] = t2; tbl_[3] = t3; tbl_[4] = t4; }
	Pack(const Xbyak::Reg64& t5, const Xbyak::Reg64& t4, const Xbyak::Reg64& t3, const Xbyak::Reg64& t2, const Xbyak::Reg64& t1, const Xbyak::Reg64& t0)
	{ n_ = 6; tbl_[0] = t0; tbl_[1] = t1; tbl_[2] = t2; tbl_[3] = t3; tbl_[4] = t4; tbl_[5] = t5; }
	Pack(const Xbyak::Reg64& t6, const Xbyak::Reg64& t5, const Xbyak::Reg64& t4, const Xbyak::Reg64& t3, const Xbyak::Reg64& t2, const Xbyak::Reg64& t1, const Xbyak::Reg64& t0)
	{ n_ = 7; tbl_[0] = t0; tbl_[1] = t1; tbl_[2] = t2; tbl_[3] = t3; tbl_[4] = t4; tbl_[5] = t5; tbl_[6] = t6; }
	Pack(const Xbyak::Reg64& t7, const Xbyak::Reg64& t6, const Xbyak::Reg64& t5, const Xbyak::Reg64& t4, const Xbyak::Reg64& t3, const Xbyak::Reg64& t2, const Xbyak::Reg64& t1, const Xbyak::Reg64& t0)
	{ n_ = 8; tbl_[0] = t0; tbl_[1] = t1; tbl_[2] = t2; tbl_[3] = t3; tbl_[4] = t4; tbl_[5] = t5; tbl_[6] = t6; tbl_[7] = t7; }
	Pack(const Xbyak::Reg64& t8, const Xbyak::Reg64& t7, const Xbyak::Reg64& t6, const Xbyak::Reg64& t5, const Xbyak::Reg64& t4, const Xbyak::Reg64& t3, const Xbyak::Reg64& t2, const Xbyak::Reg64& t1, const Xbyak::Reg64& t0)
	{ n_ = 9; tbl_[0] = t0; tbl_[1] = t1; tbl_[2] = t2; tbl_[3] = t3; tbl_[4] = t4; tbl_[5] = t5; tbl_[6] = t6; tbl_[7] = t7; tbl_[8] = t8; }
	Pack(const Xbyak::Reg64& t9, const Xbyak::Reg64& t8, const Xbyak::Reg64& t7, const Xbyak::Reg64& t6, const Xbyak::Reg64& t5, const Xbyak::Reg64& t4, const Xbyak::Reg64& t3, const Xbyak::Reg64& t2, const Xbyak::Reg64& t1, const Xbyak::Reg64& t0)
	{ n_ = 10; tbl_[0] = t0; tbl_[1] = t1; tbl_[2] = t2; tbl_[3] = t3; tbl_[4] = t4; tbl_[5] = t5; tbl_[6] = t6; tbl_[7] = t7; tbl_[8] = t8; tbl_[9] = t9; }
	Pack(const Xbyak::Reg64& ta, const Xbyak::Reg64& t9, const Xbyak::Reg64& t8, const Xbyak::Reg64& t7, const Xbyak::Reg64& t6, const Xbyak::Reg64& t5, const Xbyak::Reg64& t4, const Xbyak::Reg64& t3, const Xbyak::Reg64& t2, const Xbyak::Reg64& t1, const Xbyak::Reg64& t0)
	{ n_ = 11; tbl_[0] = t0; tbl_[1] = t1; tbl_[2] = t2; tbl_[3] = t3; tbl_[4] = t4; tbl_[5] = t5; tbl_[6] = t6; tbl_[7] = t7; tbl_[8] = t8; tbl_[9] = t9; tbl_[10] = ta; }
	Pack(const Xbyak::Reg64& tb, const Xbyak::Reg64& ta, const Xbyak::Reg64& t9, const Xbyak::Reg64& t8, const Xbyak::Reg64& t7, const Xbyak::Reg64& t6, const Xbyak::Reg64& t5, const Xbyak::Reg64& t4, const Xbyak::Reg64& t3, const Xbyak::Reg64& t2, const Xbyak::Reg64& t1, const Xbyak::Reg64& t0)
	{ n_ = 12; tbl_[0] = t0; tbl_[1] = t1; tbl_[2] = t2; tbl_[3] = t3; tbl_[4] = t4; tbl_[5] = t5; tbl_[6] = t6; tbl_[7] = t7; tbl_[8] = t8; tbl_[9] = t9; tbl_[10] = ta; tbl_[11] = tb; }
	Pack& append(const Xbyak::Reg64& t)
	{
		if (n_ == maxTblNum) {
			fprintf(stderr, "ERR Pack::can't append\n");
			XBYAK_THROW_RET(ERR_BAD_PARAMETER, *this)
		}
		tbl_[n_++] = t;
		return *this;
	}
	void init(const Xbyak::Reg64 *tbl, size_t n)
	{
		if (n > maxTblNum) {
			fprintf(stderr, "ERR Pack::init bad n=%d\n", (int)n);
			XBYAK_THROW(ERR_BAD_PARAMETER)
		}
		n_ = n;
		for (size_t i = 0; i < n; i++) {
			tbl_[i] = tbl[i];
		}
	}
	const Xbyak::Reg64& operator[](size_t n) const
	{
		if (n >= n_) {
			fprintf(stderr, "ERR Pack bad n=%d(%d)\n", (int)n, (int)n_);
			XBYAK_THROW_RET(ERR_BAD_PARAMETER, rax)
		}
		return tbl_[n];
	}
	size_t size() const { return n_; }
	/*
		get tbl[pos, pos + num)
	*/
	Pack sub(size_t pos, size_t num = size_t(-1)) const
	{
		if (num == size_t(-1)) num = n_ - pos;
		if (pos + num > n_) {
			fprintf(stderr, "ERR Pack::sub bad pos=%d, num=%d\n", (int)pos, (int)num);
			XBYAK_THROW_RET(ERR_BAD_PARAMETER, Pack())
		}
		Pack pack;
		pack.n_ = num;
		for (size_t i = 0; i < num; i++) {
			pack.tbl_[i] = tbl_[pos + i];
		}
		return pack;
	}
	void put() const
	{
		for (size_t i = 0; i < n_; i++) {
			printf("%s ", tbl_[i].toString());
		}
		printf("\n");
	}
};

class StackFrame {
#ifdef XBYAK64_WIN
	static const int noSaveNum = 6;
	static const int rcxPos = 0;
	static const int rdxPos = 1;
#else
	static const int noSaveNum = 8;
	static const int rcxPos = 3;
	static const int rdxPos = 2;
#endif
	static const int maxRegNum = 14; // maxRegNum = 16 - rsp - rax
	Xbyak::CodeGenerator *code_;
	Xbyak::Reg64 pTbl_[4];
	Xbyak::Reg64 tTbl_[maxRegNum];
	Pack p_;
	Pack t_;
	int pNum_;
	int tNum_;
	int saveNum_;
	int P_;
	bool useRcx_;
	bool useRdx_;
	bool makeEpilog_;
	StackFrame(const StackFrame&);
	void operator=(const StackFrame&);
public:
	const Pack& p;
	const Pack& t;
	/*
		make stack frame
		@param sf [in] this
		@param pNum [in] num of function parameter(0 <= pNum <= 4)
		@param tNum [in] num of temporary register(0 <= tNum, with UseRCX, UseRDX) #{pNum + tNum [+rcx] + [rdx]} <= 14
		@param stackSizeByte [in] local stack size
		@param makeEpilog [in] automatically call close() if true

		you can use
		rax
		gp0, ..., gp(pNum - 1)
		gt0, ..., gt(tNum-1)
		rcx if tNum & UseRCX
		rdx if tNum & UseRDX
		rsp[0..stackSizeByte - 1]
	*/
	StackFrame(Xbyak::CodeGenerator *code, int pNum, int tNum = 0, int stackSizeByte = 0, bool makeEpilog = true)
		: code_(code)
		, pNum_(pNum)
		, tNum_(tNum & ~(UseRCX | UseRDX))
		, saveNum_(0)
		, P_(0)
		, useRcx_((tNum & UseRCX) != 0)
		, useRdx_((tNum & UseRDX) != 0)
		, makeEpilog_(makeEpilog)
		, p(p_)
		, t(t_)
	{
		using namespace Xbyak;
		if (pNum < 0 || pNum > 4) XBYAK_THROW(ERR_BAD_PNUM)
		const int allRegNum = pNum + tNum_ + (useRcx_ ? 1 : 0) + (useRdx_ ? 1 : 0);
		if (tNum_ < 0 || allRegNum > maxRegNum) XBYAK_THROW(ERR_BAD_TNUM)
		const Reg64& _rsp = code->rsp;
		saveNum_ = local::max_(0, allRegNum - noSaveNum);
		const int *tbl = getOrderTbl() + noSaveNum;
		for (int i = 0; i < saveNum_; i++) {
			code->push(Reg64(tbl[i]));
		}
		P_ = (stackSizeByte + 7) / 8;
		if (P_ > 0 && (P_ & 1) == (saveNum_ & 1)) P_++; // (rsp % 16) == 8, then increment P_ for 16 byte alignment
		P_ *= 8;
		if (P_ > 0) code->sub(_rsp, P_);
		int pos = 0;
		for (int i = 0; i < pNum; i++) {
			pTbl_[i] = Xbyak::Reg64(getRegIdx(pos));
		}
		for (int i = 0; i < tNum_; i++) {
			tTbl_[i] = Xbyak::Reg64(getRegIdx(pos));
		}
		if (useRcx_ && rcxPos < pNum) code_->mov(code_->r10, code_->rcx);
		if (useRdx_ && rdxPos < pNum) code_->mov(code_->r11, code_->rdx);
		p_.init(pTbl_, pNum);
		t_.init(tTbl_, tNum_);
	}
	/*
		make epilog manually
		@param callRet [in] call ret() if true
	*/
	void close(bool callRet = true)
	{
		using namespace Xbyak;
		const Reg64& _rsp = code_->rsp;
		const int *tbl = getOrderTbl() + noSaveNum;
		if (P_ > 0) code_->add(_rsp, P_);
		for (int i = 0; i < saveNum_; i++) {
			code_->pop(Reg64(tbl[saveNum_ - 1 - i]));
		}

		if (callRet) code_->ret();
	}
	~StackFrame()
	{
		if (!makeEpilog_) return;
		close();
	}
private:
	const int *getOrderTbl() const
	{
		using namespace Xbyak;
		static const int tbl[] = {
#ifdef XBYAK64_WIN
			Operand::RCX, Operand::RDX, Operand::R8, Operand::R9, Operand::R10, Operand::R11, Operand::RDI, Operand::RSI,
#else
			Operand::RDI, Operand::RSI, Operand::RDX, Operand::RCX, Operand::R8, Operand::R9, Operand::R10, Operand::R11,
#endif
			Operand::RBX, Operand::RBP, Operand::R12, Operand::R13, Operand::R14, Operand::R15
		};
		return &tbl[0];
	}
	int getRegIdx(int& pos) const
	{
		assert(pos < maxRegNum);
		using namespace Xbyak;
		const int *tbl = getOrderTbl();
		int r = tbl[pos++];
		if (useRcx_) {
			if (r == Operand::RCX) { return Operand::R10; }
			if (r == Operand::R10) { r = tbl[pos++]; }
		}
		if (useRdx_) {
			if (r == Operand::RDX) { return Operand::R11; }
			if (r == Operand::R11) { return tbl[pos++]; }
		}
		return r;
	}
};
#endif

class Profiler {
	int mode_;
	const char *suffix_;
	const void *startAddr_;
#ifdef XBYAK_USE_PERF
	FILE *fp_;
#endif
public:
	enum {
		None = 0,
		Perf = 1,
		VTune = 2
	};
	Profiler()
		: mode_(None)
		, suffix_("")
		, startAddr_(0)
#ifdef XBYAK_USE_PERF
		, fp_(0)
#endif
	{
	}
	// append suffix to funcName
	void setNameSuffix(const char *suffix)
	{
		suffix_ = suffix;
	}
	void setStartAddr(const void *startAddr)
	{
		startAddr_ = startAddr;
	}
	void init(int mode)
	{
		mode_ = None;
		switch (mode) {
		default:
		case None:
			return;
		case Perf:
#ifdef XBYAK_USE_PERF
			close();
			{
				const int pid = getpid();
				char name[128];
				snprintf(name, sizeof(name), "/tmp/perf-%d.map", pid);
				fp_ = fopen(name, "a+");
				if (fp_ == 0) {
					fprintf(stderr, "can't open %s\n", name);
					return;
				}
			}
			mode_ = Perf;
#endif
			return;
		case VTune:
#ifdef XBYAK_USE_VTUNE
			dlopen("dummy", RTLD_LAZY); // force to load dlopen to enable jit profiling
			if (iJIT_IsProfilingActive() != iJIT_SAMPLING_ON) {
				fprintf(stderr, "VTune profiling is not active\n");
				return;
			}
			mode_ = VTune;
#endif
			return;
		}
	}
	~Profiler()
	{
		close();
	}
	void close()
	{
#ifdef XBYAK_USE_PERF
		if (fp_ == 0) return;
		fclose(fp_);
		fp_ = 0;
#endif
	}
	void set(const char *funcName, const void *startAddr, size_t funcSize) const
	{
		if (mode_ == None) return;
#if !defined(XBYAK_USE_PERF) && !defined(XBYAK_USE_VTUNE)
		(void)funcName;
		(void)startAddr;
		(void)funcSize;
#endif
#ifdef XBYAK_USE_PERF
		if (mode_ == Perf) {
			if (fp_ == 0) return;
			fprintf(fp_, "%llx %zx %s%s", (long long)startAddr, funcSize, funcName, suffix_);
			/*
				perf does not recognize the function name which is less than 3,
				so append '_' at the end of the name if necessary
			*/
			size_t n = strlen(funcName) + strlen(suffix_);
			for (size_t i = n; i < 3; i++) {
				fprintf(fp_, "_");
			}
			fprintf(fp_, "\n");
			fflush(fp_);
		}
#endif
#ifdef XBYAK_USE_VTUNE
		if (mode_ != VTune) return;
		char className[] = "";
		char fileName[] = "";
		iJIT_Method_Load jmethod = {};
		jmethod.method_id = iJIT_GetNewMethodID();
		jmethod.class_file_name = className;
		jmethod.source_file_name = fileName;
		jmethod.method_load_address = const_cast<void*>(startAddr);
		jmethod.method_size = funcSize;
		jmethod.line_number_size = 0;
		char buf[128];
		snprintf(buf, sizeof(buf), "%s%s", funcName, suffix_);
		jmethod.method_name = buf;
		iJIT_NotifyEvent(iJVM_EVENT_TYPE_METHOD_LOAD_FINISHED, (void*)&jmethod);
#endif
	}
	/*
		for continuous set
		funcSize = endAddr - <previous set endAddr>
	*/
	void set(const char *funcName, const void *endAddr)
	{
		set(funcName, startAddr_, (size_t)endAddr - (size_t)startAddr_);
		startAddr_ = endAddr;
	}
};
#endif // XBYAK_ONLY_CLASS_CPU

} } // end of util

#endif
