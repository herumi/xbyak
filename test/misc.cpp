#include <stdio.h>
#include <string.h>
#include <string>
#include <xbyak/xbyak.h>
#include <cybozu/inttype.hpp>
#include <cybozu/test.hpp>

using namespace Xbyak;

CYBOZU_TEST_AUTO(setSize)
{
	struct Code : Xbyak::CodeGenerator {
		Code() : Xbyak::CodeGenerator(4096)
		{
			setSize(4095);
			db(1);
			size_t size = getSize();
			CYBOZU_TEST_EQUAL(size, 4096);
			CYBOZU_TEST_NO_EXCEPTION(setSize(size));
			CYBOZU_TEST_EXCEPTION(db(1), Xbyak::Error);
		}
	} code;
}

CYBOZU_TEST_AUTO(compOperand)
{
	using namespace Xbyak::util;
	CYBOZU_TEST_ASSERT(eax == eax);
	CYBOZU_TEST_ASSERT(ecx != xmm0);
	CYBOZU_TEST_ASSERT(ptr[eax] == ptr[eax]);
	CYBOZU_TEST_ASSERT(dword[eax] != ptr[eax]);
	CYBOZU_TEST_ASSERT(ptr[eax] != ptr[eax+3]);
}

#ifdef XBYAK64
CYBOZU_TEST_AUTO(mov_const)
{
	struct Code : Xbyak::CodeGenerator {
		Code()
		{
			CYBOZU_TEST_NO_EXCEPTION(mov(dword[eax], -1));
			CYBOZU_TEST_NO_EXCEPTION(mov(dword[eax], 0x7fffffff));
			CYBOZU_TEST_NO_EXCEPTION(mov(dword[eax], -0x7fffffff));
			CYBOZU_TEST_NO_EXCEPTION(mov(dword[eax], 0xabcd1234));
			CYBOZU_TEST_NO_EXCEPTION(mov(dword[eax], 0xffffffff));
			CYBOZU_TEST_EXCEPTION(mov(dword[eax], 0x100000000ull), Xbyak::Error);
			CYBOZU_TEST_EXCEPTION(mov(dword[eax], -0x80000000ull), Xbyak::Error);
		}
	} code;
}
#endif
