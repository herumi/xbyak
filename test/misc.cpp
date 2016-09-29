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

CYBOZU_TEST_AUTO(mov_const)
{
	struct Code : Xbyak::CodeGenerator {
		Code()
		{
			const struct {
				uint64_t v;
				int bit;
				bool error;
			} tbl[] = {
				{ uint64_t(-1), 8, false },
				{ 0x12, 8, false },
				{ 0x80, 8, false },
				{ 0xff, 8, false },
				{ 0x100, 8, true },

				{ 1, 16, false },
				{ uint64_t(-1), 16, false },
				{ 0x7fff, 16, false },
				{ 0xffff, 16, false },
				{ 0x10000, 16, true },

				{ uint64_t(-1), 32, false },
				{ 0x7fffffff, 32, false },
				{ uint64_t(-0x7fffffff), 32, false },
				{ 0xffffffff, 32, false },
				{ 0x100000000ull, 32, true },

#ifdef XBYAK64
				{ uint64_t(-1), 64, false },
				{ 0x7fffffff, 64, false },
				{ 0xffffffffffffffffull, 64, false },
				{ 0x80000000, 64, true },
				{ 0xffffffff, 64, true },
#endif
			};
			for (size_t i = 0; i < CYBOZU_NUM_OF_ARRAY(tbl); i++) {
				const int bit = tbl[i].bit;
				const uint64_t v = tbl[i].v;
				const Xbyak::AddressFrame& af = bit == 8 ? byte : bit == 16 ? word : bit == 32 ? dword : qword;
				if (tbl[i].error) {
					CYBOZU_TEST_EXCEPTION(mov(af[eax], v), Xbyak::Error);
				} else {
					CYBOZU_TEST_NO_EXCEPTION(mov(af[eax], v));
				}
			}
		}
	} code;
}
