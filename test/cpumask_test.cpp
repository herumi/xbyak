//#define XBYAK_CPUMASK_COMPACT 0
#define XBYAK_NO_EXCEPTION
#define XBYAK_CPUMASK_N 8
#define XBYAK_CPUMASK_BITN 3
#include <xbyak/xbyak_util.h>
#include <cybozu/test.hpp>

using namespace Xbyak::util;

CYBOZU_TEST_AUTO(append)
{
	CpuMask m;
	CYBOZU_TEST_ASSERT(m.empty());
	CYBOZU_TEST_EQUAL(m.size(), 0);
	CYBOZU_TEST_EQUAL(m.getStr(), "");

	CYBOZU_TEST_ASSERT(m.append(2));
	CYBOZU_TEST_ASSERT(!m.empty());
	CYBOZU_TEST_EQUAL(m.size(), 1u);
	CYBOZU_TEST_EQUAL(m.get(0), 2u);
	CYBOZU_TEST_EQUAL(m.getStr(), "2");

	CYBOZU_TEST_ASSERT(m.append(4));
	CYBOZU_TEST_EQUAL(m.size(), 2u);
	CYBOZU_TEST_EQUAL(m.get(0), 2u);
	CYBOZU_TEST_EQUAL(m.get(1), 4u);
	CYBOZU_TEST_EQUAL(m.getStr(), "2,4");

	CYBOZU_TEST_ASSERT(!m.append(3)); // not monotonically increasing
	CYBOZU_TEST_ASSERT(m.append(7));
	CYBOZU_TEST_EQUAL(m.size(), 3u);
	CYBOZU_TEST_EQUAL(m.get(0), 2u);
	CYBOZU_TEST_EQUAL(m.get(1), 4u);
	CYBOZU_TEST_EQUAL(m.get(2), 7u);
	CYBOZU_TEST_EQUAL(m.getStr(), "2,4,7");

	m.clear();
	CYBOZU_TEST_ASSERT(m.append(1));
	CYBOZU_TEST_ASSERT(m.append(2));
	CYBOZU_TEST_ASSERT(m.append(3));
	CYBOZU_TEST_EQUAL(m.getStr(), "1-3");
	CYBOZU_TEST_ASSERT(m.append(5));
	CYBOZU_TEST_ASSERT(m.append(6));
	CYBOZU_TEST_ASSERT(m.append(7));
	CYBOZU_TEST_EQUAL(m.getStr(), "1-3,5-7");

	m.clear();
	CYBOZU_TEST_ASSERT(m.appendRange(1, 3));
	CYBOZU_TEST_EQUAL(m.getStr(), "1-3");
	CYBOZU_TEST_ASSERT(m.appendRange(5, 7));
	CYBOZU_TEST_EQUAL(m.getStr(), "1-3,5-7");
}

CYBOZU_TEST_AUTO(str)
{
	const char *s = "0-1,3,4-7";
	CpuMask m, m2;

	CYBOZU_TEST_ASSERT(m.setStr(s));
	CYBOZU_TEST_ASSERT(m2.setStr(m.getStr()));
	CYBOZU_TEST_EQUAL(m.getStr(), m2.getStr());
	CYBOZU_TEST_ASSERT(m == m2);
}

CYBOZU_TEST_AUTO(errStr)
{
	const char *s[] = {
		",",
		",,",
		"1,",
		"1,,",
		"-8",
		"3-",
		"0-8",
		"0--2",
		"2-0",
		"2,1",
		"0-1-2",
		"0,a",
		"0-2,",
		",0-2",
		"0-2,,4",
	};
	for (size_t i = 0; i < sizeof(s) / sizeof(s[0]); i++) {
		CpuMask m;
//		printf("errStr test %s\n", s[i]);
		CYBOZU_TEST_ASSERT(!m.setStr(s[i]));
	}
}

CYBOZU_TEST_AUTO(pattern)
{
	const uint32_t bitN = XBYAK_CPUMASK_BITN;
	const uint32_t bit = 1 << bitN;
	for (uint32_t i = 0; i < (1 << bit); i++) {
		CpuMask m;
		uint32_t cnt = 0;
		for (uint32_t j = 0; j < bit; j++) {
			if (i & (1 << j)) {
				cnt++;
				CYBOZU_TEST_ASSERT(m.append(j));
			}
		}
		CYBOZU_TEST_EQUAL(m.size(), cnt);
#if 0
		printf("pattern (%3u) ", i);
		for (int j = int(bit) - 1; j >= 0; j--) {
			if (i & (uint64_t(1) << j)) printf("%d ", j);
		}
		printf("\n");
#endif
		uint32_t idx = 0;
		for (const auto& v : m) {
			CYBOZU_TEST_ASSERT(i & (1 << v));
			idx++;
		}
		CYBOZU_TEST_EQUAL(idx, cnt);
		CpuMask m2;
		std::string mstr = m.getStr();
		CYBOZU_TEST_ASSERT(m2.setStr(mstr));
		CYBOZU_TEST_ASSERT(m == m2);
		CYBOZU_TEST_EQUAL(mstr, m2.getStr());
	}
}
