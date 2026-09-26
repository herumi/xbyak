#include <stdio.h>
#include <string.h>
#include <xbyak/xbyak.h>
#include <cybozu/test.hpp>

#ifndef XBYAK64
	#error "only 64-bit mode"
#endif

using namespace Xbyak;

#ifdef XBYAK_USE_MMAP_ALLOCATOR

CYBOZU_TEST_AUTO(freeUnknownPointer)
{
	MmapAllocator alloc;
	uint8_t dummy = 0;
	CYBOZU_TEST_EXCEPTION(alloc.free(&dummy), Xbyak::Error);
}

CYBOZU_TEST_AUTO(freeNullptr)
{
	MmapAllocator alloc;
	CYBOZU_TEST_NO_EXCEPTION(alloc.free(0));
}

CYBOZU_TEST_AUTO(doubleFree)
{
	MmapAllocator alloc;
	uint8_t *p = alloc.alloc(64);
	CYBOZU_TEST_NO_EXCEPTION(alloc.free(p));
	CYBOZU_TEST_EXCEPTION(alloc.free(p), Xbyak::Error);
}

CYBOZU_TEST_AUTO(freeOnlyElement)
{
	MmapAllocator alloc;
	uint8_t *p = alloc.alloc(64);
	CYBOZU_TEST_NO_EXCEPTION(alloc.free(p));
	CYBOZU_TEST_EXCEPTION(alloc.free(p), Xbyak::Error);
}

CYBOZU_TEST_AUTO(freeLastElement)
{
	MmapAllocator alloc;
	uint8_t *p0 = alloc.alloc(64);
	uint8_t *p1 = alloc.alloc(64);
	CYBOZU_TEST_NO_EXCEPTION(alloc.free(p1));
	CYBOZU_TEST_NO_EXCEPTION(alloc.free(p0));
	CYBOZU_TEST_EXCEPTION(alloc.free(p0), Xbyak::Error);
	CYBOZU_TEST_EXCEPTION(alloc.free(p1), Xbyak::Error);
}

CYBOZU_TEST_AUTO(freeNonLifoOrder)
{
	MmapAllocator alloc;
	uint8_t *p0 = alloc.alloc(64);
	uint8_t *p1 = alloc.alloc(64);
	uint8_t *p2 = alloc.alloc(64);
	CYBOZU_TEST_NO_EXCEPTION(alloc.free(p0));
	CYBOZU_TEST_NO_EXCEPTION(alloc.free(p1));
	CYBOZU_TEST_NO_EXCEPTION(alloc.free(p2));
	CYBOZU_TEST_EXCEPTION(alloc.free(p0), Xbyak::Error);
	CYBOZU_TEST_EXCEPTION(alloc.free(p1), Xbyak::Error);
	CYBOZU_TEST_EXCEPTION(alloc.free(p2), Xbyak::Error);
}

CYBOZU_TEST_AUTO(twoInstancesAreIsolated)
{
	MmapAllocator a;
	MmapAllocator b;
	uint8_t *p = a.alloc(64);
	CYBOZU_TEST_EXCEPTION(b.free(p), Xbyak::Error);
	CYBOZU_TEST_NO_EXCEPTION(a.free(p));
}

#if defined(XBYAK_USE_MEMFD)
CYBOZU_TEST_AUTO(memfdSurvivorAfterSwap)
{
	MmapAllocator alloc;
	uint8_t *p0 = alloc.alloc(64);
	uint8_t *p1 = alloc.alloc(64);
	CYBOZU_TEST_NO_EXCEPTION(alloc.free(p0));
	CYBOZU_TEST_NO_EXCEPTION(alloc.free(p1));
}
#endif

#endif
