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
	CYBOZU_TEST_ASSERT(ptr[eax] != ptr[eax+3]);
}