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
			CYBOZU_TEST_EQUAL(size, 4096u);
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

CYBOZU_TEST_AUTO(align)
{
	struct Code : Xbyak::CodeGenerator {
		Code()
		{
			const size_t alignSize = 16;
			for (int padding = 0; padding < 20; padding++) {
				for (int i = 0; i < padding; i++) {
					db(1);
				}
				align(alignSize);
				CYBOZU_TEST_EQUAL(size_t(getCurr()) % alignSize, 0u);
			}
			align(alignSize);
			const uint8 *p = getCurr();
			// do nothing if aligned
			align(alignSize);
			CYBOZU_TEST_EQUAL(p, getCurr());
		}
	} c;
}

#ifdef XBYAK64
CYBOZU_TEST_AUTO(vfmaddps)
{
	struct Code : Xbyak::CodeGenerator {
		Code()
		{
			v4fmaddps(zmm1, zmm8, ptr [rdx + 64]);
			v4fmaddss(xmm15, xmm8, ptr [rax + 64]);
			v4fnmaddps(zmm5 | k5, zmm2, ptr [rcx + 0x80]);
			v4fnmaddss(xmm31, xmm2, ptr [rsp + 0x80]);
			vp4dpwssd(zmm23 | k7 | T_z, zmm1, ptr [rax + 64]);
			vp4dpwssds(zmm10 | k4, zmm3, ptr [rsp + rax * 4 + 64]);
		}
	} c;
	const uint8_t tbl[] = {
		0x62, 0xf2, 0x3f, 0x48, 0x9a, 0x4a, 0x04,
		0x62, 0x72, 0x3f, 0x08, 0x9b, 0x78, 0x04,
		0x62, 0xf2, 0x6f, 0x4d, 0xaa, 0x69, 0x08,
		0x62, 0x62, 0x6f, 0x08, 0xab, 0x7c, 0x24, 0x08,
		0x62, 0xe2, 0x77, 0xcf, 0x52, 0x78, 0x04,
		0x62, 0x72, 0x67, 0x4c, 0x53, 0x54, 0x84, 0x04,
	};
	const size_t n = sizeof(tbl) / sizeof(tbl[0]);
	CYBOZU_TEST_EQUAL(c.getSize(), n);
	CYBOZU_TEST_EQUAL_ARRAY(c.getCode(), tbl, n);
}
#endif
