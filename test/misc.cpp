#include <stdio.h>
#include <string.h>
#include <string>
#include <xbyak/xbyak.h>
#include <xbyak/xbyak_util.h>
#include <cybozu/inttype.hpp>
#include <cybozu/test.hpp>
#include <algorithm>

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

#ifdef XBYAK64
CYBOZU_TEST_AUTO(badSSE)
{
	struct Code : Xbyak::CodeGenerator {
		Code()
		{
			CYBOZU_TEST_EXCEPTION(paddd(xm16, xm1), Xbyak::Error);
			CYBOZU_TEST_EXCEPTION(pslld(xm16, 1), Xbyak::Error);
			CYBOZU_TEST_EXCEPTION(movapd(xm16, xm1), Xbyak::Error);
			CYBOZU_TEST_EXCEPTION(movhpd(xm16, ptr[eax]), Xbyak::Error);
			CYBOZU_TEST_EXCEPTION(pextrb(eax, xm16, 1), Xbyak::Error);

			CYBOZU_TEST_EXCEPTION(lddqu(xm16, ptr[rax]), Error);
			CYBOZU_TEST_EXCEPTION(maskmovdqu(xm16, xm1), Error);
			CYBOZU_TEST_EXCEPTION(maskmovq(xm16, xm1), Error);
			CYBOZU_TEST_EXCEPTION(movapd(ptr[rax], xm16), Error);
			CYBOZU_TEST_EXCEPTION(movaps(ptr[rax], xm16), Error);
			CYBOZU_TEST_EXCEPTION(movd(ptr[rax], xm16), Error);
			CYBOZU_TEST_EXCEPTION(movd(xm16, ptr[rax]), Error);
			CYBOZU_TEST_EXCEPTION(movd(eax, xm16), Error);
			CYBOZU_TEST_EXCEPTION(movd(xm16, eax), Error);
			CYBOZU_TEST_EXCEPTION(movdq2q(mm1, xm16), Error);
			CYBOZU_TEST_EXCEPTION(movdqa(ptr[rax], xm16), Error);
			CYBOZU_TEST_EXCEPTION(movdqu(ptr[rax], xm16), Error);
			CYBOZU_TEST_EXCEPTION(movhlps(xm16, xm1), Error);
			CYBOZU_TEST_EXCEPTION(movlhps(xm16, xm1), Error);
			CYBOZU_TEST_EXCEPTION(movmskpd(rax, xm16), Error);
			CYBOZU_TEST_EXCEPTION(movmskps(rax, xm16), Error);
			CYBOZU_TEST_EXCEPTION(movntdq(ptr[rax], xmm16), Error);
			CYBOZU_TEST_EXCEPTION(movntdqa(xm16, ptr[rax]), Error);
			CYBOZU_TEST_EXCEPTION(movntpd(ptr[rax], xmm16), Error);
			CYBOZU_TEST_EXCEPTION(movntps(ptr[rax], xm16), Error);
			CYBOZU_TEST_EXCEPTION(movntq(ptr[rax], xm16), Error);
			CYBOZU_TEST_EXCEPTION(movq(ptr[rax], xm16), Error);
			CYBOZU_TEST_EXCEPTION(movq(xm16, ptr[rax]), Error);
			CYBOZU_TEST_EXCEPTION(movq(rax, xm16), Error);
			CYBOZU_TEST_EXCEPTION(movq(xm16, rax), Error);
			CYBOZU_TEST_EXCEPTION(movq2dq(xm16, mm1), Error);
			CYBOZU_TEST_EXCEPTION(movsd(ptr[rax], xm16), Error);
			CYBOZU_TEST_EXCEPTION(movss(ptr[rax], xm16), Error);
			CYBOZU_TEST_EXCEPTION(movupd(ptr[rax], xm16), Error);
			CYBOZU_TEST_EXCEPTION(movups(ptr[rax], xm16), Error);
			CYBOZU_TEST_EXCEPTION(extractps(ptr[rax], xm16, 3), Error);
			CYBOZU_TEST_EXCEPTION(pextrb(ptr[rax], xm16, 3), Error);
			CYBOZU_TEST_EXCEPTION(pextrd(ptr[rax], xm16, 3), Error);
			CYBOZU_TEST_EXCEPTION(pextrw(ptr[rax], xm16, 3), Error);
			CYBOZU_TEST_EXCEPTION(pmovmskb(eax, xm16), Error);
		}
	} code;
}
#endif

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
			CYBOZU_TEST_EXCEPTION(mov(cx, al), Xbyak::Error);
			CYBOZU_TEST_EXCEPTION(mov(al, cx), Xbyak::Error);
			CYBOZU_TEST_EXCEPTION(mov(eax, cx), Xbyak::Error);
			CYBOZU_TEST_EXCEPTION(mov(eax, byte[eax]), Xbyak::Error);
			CYBOZU_TEST_EXCEPTION(mov(word[eax], al), Xbyak::Error);
#ifdef XBYAK64
			CYBOZU_TEST_EXCEPTION(mov(word[rax], rax), Xbyak::Error);
			CYBOZU_TEST_NO_EXCEPTION(mov(rax, ptr[(void*)0x7fffffff]));
			for (int i = 4; i < 8; i++) {
				CYBOZU_TEST_EXCEPTION(add(ah, Reg8(i, true)), Xbyak::Error);
				CYBOZU_TEST_EXCEPTION(add(Reg8(i, true), dh), Xbyak::Error);
			}
			for (int i = 8; i < 32; i++) {
				CYBOZU_TEST_EXCEPTION(add(ah, Reg8(i)), Xbyak::Error);
				CYBOZU_TEST_EXCEPTION(add(Reg8(i), dh), Xbyak::Error);
			}
			CYBOZU_TEST_EXCEPTION(mov(ah, cx), Xbyak::Error);
			CYBOZU_TEST_EXCEPTION(mov(al, cx), Xbyak::Error);
#ifdef XBYAK_OLD_DISP_CHECK
			CYBOZU_TEST_NO_EXCEPTION(mov(rax, ptr[(void*)0x80000000]));
			CYBOZU_TEST_NO_EXCEPTION(mov(rax, ptr[(void*)0xffffffff]));
#endif
#endif
		}
	} code;
}

CYBOZU_TEST_AUTO(RegExp)
{
	using namespace Xbyak::util;
	Address defaultAddr; // default constructor
	(void)defaultAddr;
	int x = 0;
	eax + 0;
	0 + eax;
	eax + &x;
}

#ifdef XBYAK64
CYBOZU_TEST_AUTO(mov_8byte)
{
	struct Code : Xbyak::CodeGenerator {
		Code()
		{
			mov(rax, ptr[(void*)0x17fffffff]);
			mov(rax, ptr[(void*)0x80000000ull]);
			mov(rax, ptr[(void*)0xffffffffull]);

			mov(rax, ptr[0x17fffffff]);
			mov(rax, ptr[0x80000000ull]);
			mov(rax, ptr[0xffffffffull]);
		}
	} c;
	const uint8_t tbl[] = {
		0x48, 0xa1, 0xff, 0xff, 0xff, 0x7f, 0x01, 0x00, 0x00, 0x00,
		0x48, 0xa1, 0x00, 0x00, 0x00, 0x80, 0x00, 0x00, 0x00, 0x00,
		0x48, 0xa1, 0xff, 0xff, 0xff, 0xff, 0x00, 0x00, 0x00, 0x00,

		0x48, 0xa1, 0xff, 0xff, 0xff, 0x7f, 0x01, 0x00, 0x00, 0x00,
		0x48, 0xa1, 0x00, 0x00, 0x00, 0x80, 0x00, 0x00, 0x00, 0x00,
		0x48, 0xa1, 0xff, 0xff, 0xff, 0xff, 0x00, 0x00, 0x00, 0x00,
	};
	const size_t n = sizeof(tbl) / sizeof(tbl[0]);
	CYBOZU_TEST_EQUAL(c.getSize(), n);
	CYBOZU_TEST_EQUAL_ARRAY(c.getCode(), tbl, n);
}
#endif

CYBOZU_TEST_AUTO(const_addressing)
{
	struct Code : Xbyak::CodeGenerator {
		Code()
		{
			mov(dword[0x7fffffff], edx);
		}
	} c;
	const uint8_t tbl[] = {
#ifdef XBYAK64
		0x89, 0x14, 0x25, 0xff, 0xff, 0xff, 0x7f
#else
		0x89, 0x15, 0xff, 0xff, 0xff, 0x7f
#endif
	};
	const size_t n = sizeof(tbl) / sizeof(tbl[0]);
	CYBOZU_TEST_EQUAL(c.getSize(), n);
	CYBOZU_TEST_EQUAL_ARRAY(c.getCode(), tbl, n);
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
			const uint8_t *p = getCurr();
			// do nothing if aligned
			align(alignSize);
			CYBOZU_TEST_EQUAL(p, getCurr());
		}
	} c;
}
CYBOZU_TEST_AUTO(kmask)
{
	struct Code : Xbyak::CodeGenerator {
		Code()
		{
			CYBOZU_TEST_EXCEPTION(kmovb(k1, ax), std::exception);
			CYBOZU_TEST_EXCEPTION(kmovw(k1, ax), std::exception);
			CYBOZU_TEST_EXCEPTION(kmovd(k1, ax), std::exception);
			CYBOZU_TEST_EXCEPTION(kmovq(k1, eax), std::exception);
#ifdef XBYAK64
			CYBOZU_TEST_EXCEPTION(kmovb(k1, rax), std::exception);
			CYBOZU_TEST_EXCEPTION(kmovw(k1, rax), std::exception);
			CYBOZU_TEST_EXCEPTION(kmovd(k1, rax), std::exception);
			CYBOZU_TEST_NO_EXCEPTION(kmovq(k1, rax));
#endif
			CYBOZU_TEST_NO_EXCEPTION(vmovaps(xm0|k0, ptr[eax]));
			checkT_z();
		}
		// T_z is dropped when no mask register is specified because
		// EVEX.z=1 with EVEX.aaa=000 is an invalid encoding (#UD),
		// so the encoded bytes are the same as without T_z.
		void checkT_z()
		{
			const uint8_t *p1 = getCurr();
			vmovaps(zm0, ptr[eax]);
			vaddpd(zm1, zm1, zm1);
			vaddpd(zm1, zm1, zm1|T_rn_sae);
			vaddpd(zm1, zm1, zm1|T_rz_sae);
			vmpsadbw(xm1, xm4, ptr[eax+64], 5);
			vcvt2ph2bf8(xm1, xm2, ptr_b[eax+64]);
			vcvt2ph2bf8s(ym1, ym2, ptr_b[eax+64]);
			vcvt2ph2hf8(zm1, zm2, ptr_b[eax+64]);
			vcvt2ph2hf8s(xm1, xm2, ptr_b[eax+64]);
			const uint8_t *p2 = getCurr();
			vmovaps(zm0|T_z, ptr[eax]);
			vaddpd(zm1|T_z, zm1, zm1);
			vaddpd(zm1|T_z, zm1, zm1|T_rn_sae);
			vaddpd(zm1|T_z, zm1, zm1|T_rz_sae);
			vmpsadbw(xm1|T_z, xm4, ptr[eax+64], 5);
			vcvt2ph2bf8(xm1|T_z, xm2, ptr_b[eax+64]);
			vcvt2ph2bf8s(ym1|T_z, ym2, ptr_b[eax+64]);
			vcvt2ph2hf8(zm1|T_z, zm2, ptr_b[eax+64]);
			vcvt2ph2hf8s(xm1|T_z, xm2, ptr_b[eax+64]);
			const uint8_t *end = getCurr();
			CYBOZU_TEST_EQUAL(p2 - p1, end - p2);
			CYBOZU_TEST_EQUAL_ARRAY(p1, p2, end - p2);
		}
	} c;
}

// {z} (zeroing-masking) has no architectural meaning when the destination of a
// store-form instruction is memory; only merge-masking ({k} without {z}) is
// valid there.
CYBOZU_TEST_AUTO(store_zero)
{
	struct Code : Xbyak::CodeGenerator {
		Code()
		{
			// mode=false family (narrow dest is byte-sized relative to source)
			CYBOZU_TEST_NO_EXCEPTION(vpmovdb(ptr[eax], xmm3|k4));
			CYBOZU_TEST_EXCEPTION(vpmovdb(ptr[eax], xmm3|k4|T_z), std::exception);
			// mode=true family (narrow dest is word/dword-sized relative to source)
			CYBOZU_TEST_NO_EXCEPTION(vpmovqd(ptr[eax], xmm3|k4));
			CYBOZU_TEST_EXCEPTION(vpmovqd(ptr[eax], xmm3|k4|T_z), std::exception);
			// store forms dispatched via opVex with T_M_K
			CYBOZU_TEST_NO_EXCEPTION(vmovaps(ptr[eax], zmm3|k4));
			CYBOZU_TEST_EXCEPTION(vmovaps(ptr[eax], zmm3|k4|T_z), std::exception);
			CYBOZU_TEST_EXCEPTION(vmovaps(ptr[eax]|k4|T_z, zmm3), std::exception);
			CYBOZU_TEST_NO_EXCEPTION(vmovdqu8(ptr[eax], zmm3|k4));
			CYBOZU_TEST_EXCEPTION(vmovdqu8(ptr[eax], zmm3|k4|T_z), std::exception);
			CYBOZU_TEST_NO_EXCEPTION(vcompressps(ptr[eax], zmm3|k4));
			CYBOZU_TEST_EXCEPTION(vcompressps(ptr[eax], zmm3|k4|T_z), std::exception);
			CYBOZU_TEST_NO_EXCEPTION(vpcompressd(ptr[eax], zmm3|k4));
			CYBOZU_TEST_EXCEPTION(vpcompressd(ptr[eax], zmm3|k4|T_z), std::exception);
			CYBOZU_TEST_NO_EXCEPTION(vextractf32x4(ptr[eax], zmm3|k4, 1));
			CYBOZU_TEST_EXCEPTION(vextractf32x4(ptr[eax], zmm3|k4|T_z, 1), std::exception);
			CYBOZU_TEST_NO_EXCEPTION(vcvtps2ph(ptr[eax], zmm3|k4, 0));
			CYBOZU_TEST_EXCEPTION(vcvtps2ph(ptr[eax], zmm3|k4|T_z, 0), std::exception);
			// register destination still accepts {z}
			CYBOZU_TEST_NO_EXCEPTION(vmovaps(zmm1|k4|T_z, ptr[eax]));
			CYBOZU_TEST_NO_EXCEPTION(vpmovdb(xmm1|k4|T_z, xmm3));
			CYBOZU_TEST_NO_EXCEPTION(vpcompressd(xmm1|k4|T_z, xmm3));
			CYBOZU_TEST_NO_EXCEPTION(vextractf32x4(xmm1|k4|T_z, zmm3, 1));
		}
	} c;
}

CYBOZU_TEST_AUTO(gather)
{
	struct Code : Xbyak::CodeGenerator {
		Code()
		{
			CYBOZU_TEST_NO_EXCEPTION(vgatherdpd(xmm1, ptr[eax+xmm2], xmm3));
			CYBOZU_TEST_EXCEPTION(vgatherdpd(xmm1, ptr[eax+xmm1], xmm2), std::exception);
			CYBOZU_TEST_EXCEPTION(vgatherdpd(xmm1, ptr[eax+xmm2], xmm1), std::exception);
			CYBOZU_TEST_EXCEPTION(vgatherdpd(xmm2, ptr[eax+xmm1], xmm1), std::exception);

			CYBOZU_TEST_NO_EXCEPTION(vgatherdpd(xmm1|k2, ptr[eax+xmm2]));
			CYBOZU_TEST_EXCEPTION(vgatherdpd(xmm1, ptr[eax+xmm2]), std::exception);
			CYBOZU_TEST_EXCEPTION(vgatherdpd(xmm1|k2, ptr[eax+xmm1]), std::exception);

			CYBOZU_TEST_NO_EXCEPTION(vpscatterdd(ptr[eax+xmm2]|k2, xmm1));
			CYBOZU_TEST_NO_EXCEPTION(vpscatterdd(ptr[eax+xmm2], xmm1|k2));
			CYBOZU_TEST_NO_EXCEPTION(vpscatterdd(ptr[eax+xmm2]|k3, xmm2));

			CYBOZU_TEST_EXCEPTION(vpscatterdd(ptr[eax+xmm2], xmm1), std::exception);
		}
	} c;
}

#ifdef XBYAK64
CYBOZU_TEST_AUTO(bf16)
{
	struct Code : Xbyak::CodeGenerator {
		Code()
		{
			// AVX_NE_CONVERT
			vcvtneps2bf16(xmm15, xmm2, VexEncoding);
			vcvtneps2bf16(xmm15, xword[rax], VexEncoding);
			vcvtneps2bf16(xmm15, ymm2, VexEncoding);
			vcvtneps2bf16(xmm15, yword[rax], VexEncoding);
		}
	} c;
	const uint8_t tbl[] = {
		0xc4, 0x62, 0x7a, 0x72, 0xfa,
		0xc4, 0x62, 0x7a, 0x72, 0x38,
		0xc4, 0x62, 0x7e, 0x72, 0xfa,
		0xc4, 0x62, 0x7e, 0x72, 0x38,
	};
	const size_t n = sizeof(tbl) / sizeof(tbl[0]);
	CYBOZU_TEST_EQUAL(c.getSize(), n);
	CYBOZU_TEST_EQUAL_ARRAY(c.getCode(), tbl, n);
}

CYBOZU_TEST_AUTO(util_tmm)
{
	const uint8_t b[] = {
		0xC4, 0xE2, 0x7B, 0x49, 0xD0,  // TILEZERO TMM2
	};
	const size_t n = sizeof(b) / sizeof(b[0]);

	Xbyak::CodeGenerator code;
	code.tilezero(Xbyak::util::tmm2);

	CYBOZU_TEST_EQUAL(code.getSize(), n);
	CYBOZU_TEST_EQUAL_ARRAY(code.getCode(), b, n);
}

CYBOZU_TEST_AUTO(segment)
{
	struct Code : Xbyak::CodeGenerator {
		Code()
		{
			putSeg(es); mov(eax, ptr[eax]);
			putSeg(cs); mov(eax, ptr[eax]);
			putSeg(ss); mov(eax, ptr[eax]);
			putSeg(ds); mov(eax, ptr[eax]);
		}
	} c;
	const uint8_t tbl[] = {
		0x26, 0x67, 0x8B, 0x00, // es
		0x2E, 0x67, 0x8B, 0x00, // cs
		0x36, 0x67, 0x8B, 0x00, // ss
		0x3E, 0x67, 0x8B, 0x00, // ds
	};
	const size_t n = sizeof(tbl) / sizeof(tbl[0]);
	CYBOZU_TEST_EQUAL(c.getSize(), n);
	CYBOZU_TEST_EQUAL_ARRAY(c.getCode(), tbl, n);
}

CYBOZU_TEST_AUTO(tileloadd)
{
	struct Code : Xbyak::CodeGenerator {
		void notSupported()
		{
			tileloadd(tmm1, ptr[r8]);
		}
		void notSupported2()
		{
			tileloadd(tmm1, ptr[r8*2]);
		}
	} c;
	// current version does not support this sibmem format
	CYBOZU_TEST_EXCEPTION(c.notSupported(), std::exception);
	CYBOZU_TEST_EXCEPTION(c.notSupported2(), std::exception);
}

CYBOZU_TEST_AUTO(vnni)
{
	struct Code : Xbyak::CodeGenerator {
		Code()
		{
			// default encoding is EVEX
			vpdpbusd(xm0, xm1, xm2);
			vpdpbusd(xm0, xm1, xm2, EvexEncoding); // EVEX
			vpdpbusd(xm0, xm1, xm2, VexEncoding); // VEX
			setDefaultEncoding(VexEncoding);
			vpdpbusd(xm0, xm1, xm2); // VEX
			setDefaultEncoding(EvexEncoding);
			vpdpbusd(xm0, xm1, xm2); // EVEX
		}
		void badVex()
		{
			vpdpbusd(xm0, xm1, xm31, VexEncoding);
		}
	} c;
	const uint8_t tbl[] = {
		0x62, 0xF2, 0x75, 0x08, 0x50, 0xC2,
		0x62, 0xF2, 0x75, 0x08, 0x50, 0xC2,
		0xC4, 0xE2, 0x71, 0x50, 0xC2,
		0xC4, 0xE2, 0x71, 0x50, 0xC2,
		0x62, 0xF2, 0x75, 0x08, 0x50, 0xC2,
	};
	const size_t n = sizeof(tbl) / sizeof(tbl[0]);
	CYBOZU_TEST_EQUAL(c.getSize(), n);
	CYBOZU_TEST_EQUAL_ARRAY(c.getCode(), tbl, n);

	CYBOZU_TEST_EXCEPTION(c.badVex(), std::exception);
}
#endif

#ifdef XBYAK32
CYBOZU_TEST_AUTO(waitpkg)
{
	struct Code : Xbyak::CodeGenerator {
		Code()
		{
			tpause(eax);
			tpause(ebx);
			umonitor(cx);
			umonitor(ecx);
			umwait(eax);
			umwait(ebx);
		}
	} c;
	const uint8_t tbl[] = {
		// tpause
		0x66, 0x0f, 0xae, 0xf0,
		0x66, 0x0f, 0xae, 0xf3,
		// umonitor
		0x67, 0xf3, 0x0f, 0xae, 0xf1,
		0xf3, 0x0f, 0xae, 0xf1,
		// umwait
		0xf2, 0x0f, 0xae, 0xf0,
		0xf2, 0x0f, 0xae, 0xf3,
	};
	const size_t n = sizeof(tbl) / sizeof(tbl[0]);
	CYBOZU_TEST_EQUAL(c.getSize(), n);
	CYBOZU_TEST_EQUAL_ARRAY(c.getCode(), tbl, n);
}
#endif

#ifdef XBYAK32
CYBOZU_TEST_AUTO(misc)
{
	struct Code : Xbyak::CodeGenerator {
		Code()
		{
			cldemote(ptr[eax+esi*4+0x12]);
			movdiri(ptr[edx+esi*2+4], eax);
			movdir64b(eax, ptr[edx]);
			xresldtrk();
			xsusldtrk();
		}
	} c;
	const uint8_t tbl[] = {
		0x0f, 0x1c, 0x44, 0xb0, 0x12, // cldemote
		0x0f, 0x38, 0xf9, 0x44, 0x72, 0x04, // movdiri
		0x66, 0x0f, 0x38, 0xf8, 0x02, // movdir64b
		0xf2, 0x0f, 0x01, 0xe9, // xresldtrk
		0xf2, 0x0f, 0x01, 0xe8, // xsusldtrk
	};
	const size_t n = sizeof(tbl) / sizeof(tbl[0]);
	CYBOZU_TEST_EQUAL(c.getSize(), n);
	CYBOZU_TEST_EQUAL_ARRAY(c.getCode(), tbl, n);
}
#endif

CYBOZU_TEST_AUTO(cpu)
{
	// https://github.com/herumi/xbyak/issues/148
	using namespace Xbyak::util;
	Cpu cpu;
	CYBOZU_TEST_EQUAL(cpu.has(Cpu::tINTEL) && cpu.has(Cpu::tAMD), cpu.has(Cpu::tINTEL | Cpu::tAMD));
}

CYBOZU_TEST_AUTO(minmax)
{
	using namespace Xbyak::util;
	CYBOZU_TEST_EQUAL((std::min)(3, 4), local::min_(3, 4));
	CYBOZU_TEST_EQUAL((std::max)(3, 4), local::max_(3, 4));
}

#ifdef XBYAK32
CYBOZU_TEST_AUTO(rao_int)
{
	struct Code : Xbyak::CodeGenerator {
		Code()
		{
			aadd(ptr[eax], ecx);
			aand(ptr[eax], ecx);
			aor(ptr[eax], ecx);
			axor(ptr[eax], ecx);
		}
	} c;
	const uint8_t tbl[] = {
		// aadd
		0x0f, 0x38, 0xfc, 0x08,
		// aand
		0x66, 0x0f, 0x38, 0xfc, 0x08,
		// aor
		0xf2, 0x0f, 0x38, 0xfc, 0x08,
		// axor
		0xf3, 0x0f, 0x38, 0xfc, 0x08,
	};
	const size_t n = sizeof(tbl) / sizeof(tbl[0]);
	CYBOZU_TEST_EQUAL(c.getSize(), n);
	CYBOZU_TEST_EQUAL_ARRAY(c.getCode(), tbl, n);
}
#endif

#ifdef XBYAK64
CYBOZU_TEST_AUTO(vmovd)
{
	struct Code : Xbyak::CodeGenerator {
		Code()
		{
			setDefaultEncodingAVX10(PreAVX10v2Encoding);
			vmovd(eax, xm1); // always AVX10.1
			vmovd(xm1, eax); // always AVX10.1
			vmovd(xm3, xm1); // always AVX10.2
			// AVX-512 (AVX10.1)
			vmovd(ptr[rax+128], xm1);
			vmovd(xm1, ptr[rax+128]);
			vmovd(ptr[rax+128], xm30);
			vmovd(xm30, ptr[rax+128]);

			setDefaultEncodingAVX10(AVX10v2Encoding);
			vmovd(eax, xm1); // always AVX10.1
			vmovd(xm1, eax); // always AVX10.1
			vmovd(xm3, xm1); // always AVX10.2
			// AVX10.2
			vmovd(ptr[rax+128], xm1);
			vmovd(xm1, ptr[rax+128]);
			vmovd(ptr[rax+128], xm30);
			vmovd(xm30, ptr[rax+128]);
		}
	} c;
	const uint8_t tbl[] = {
		0xc5, 0xf9, 0x7e, 0xc8, // avx10.1
		0xc5, 0xf9, 0x6e, 0xc8, // avx10.1
		0x62, 0xf1, 0x7e, 0x08, 0x7e, 0xd9, // avx10.2
		0xc5, 0xf9, 0x7e, 0x88, 0x80, 0x00, 0x00, 0x00, // avx
		0xc5, 0xf9, 0x6e, 0x88, 0x80, 0x00, 0x00, 0x00, // avx
		0x62, 0x61, 0x7d, 0x08, 0x7e, 0x70, 0x20, // avx10.1
		0x62, 0x61, 0x7d, 0x08, 0x6e, 0x70, 0x20, // avx10.1

		0xc5, 0xf9, 0x7e, 0xc8, // avx10.1
		0xc5, 0xf9, 0x6e, 0xc8, // avx10.1
		0x62, 0xf1, 0x7e, 0x08, 0x7e, 0xd9, // avx10.2
		0x62, 0xf1, 0x7d, 0x08, 0xd6, 0x48, 0x20, // avx10.2
		0x62, 0xf1, 0x7e, 0x08, 0x7e, 0x48, 0x20, // avx10.2
		0x62, 0x61, 0x7d, 0x08, 0xd6, 0x70, 0x20, // avx10.2
		0x62, 0x61, 0x7e, 0x08, 0x7e, 0x70, 0x20, // avx10.2
	};
	const size_t n = sizeof(tbl) / sizeof(tbl[0]);
	CYBOZU_TEST_EQUAL(c.getSize(), n);
	CYBOZU_TEST_EQUAL_ARRAY(c.getCode(), tbl, n);
}

CYBOZU_TEST_AUTO(vmovw)
{
	struct Code : Xbyak::CodeGenerator {
		Code()
		{
			setDefaultEncodingAVX10(PreAVX10v2Encoding);
			vmovw(eax, xm1); // always avx10.1
			vmovw(xm1, eax); // always avx10.1
			vmovw(xm3, xm1); // always avx10.2
			// AVX10.1
			vmovw(ptr[rax+128], xm1);
			vmovw(xm1, ptr[rax+128]);
			vmovw(ptr[rax+128], xm30);
			vmovw(xm30, ptr[rax+128]);

			setDefaultEncodingAVX10(AVX10v2Encoding);
			vmovw(eax, xm1); // always avx10.1
			vmovw(xm1, eax); // always avx10.1
			vmovw(xm3, xm1); // always avx10.2
			// AVX10.2
			vmovw(ptr[rax+128], xm1);
			vmovw(xm1, ptr[rax+128]);
			vmovw(ptr[rax+128], xm30);
			vmovw(xm30, ptr[rax+128]);
		}
	} c;
	const uint8_t tbl[] = {
		0x62, 0xf5, 0x7d, 0x08, 0x7e, 0xc8,
		0x62, 0xf5, 0x7d, 0x08, 0x6e, 0xc8,
		0x62, 0xf5, 0x7e, 0x08, 0x6e, 0xd9,
		0x62, 0xf5, 0x7d, 0x08, 0x7e, 0x48, 0x40,
		0x62, 0xf5, 0x7d, 0x08, 0x6e, 0x48, 0x40,
		0x62, 0x65, 0x7d, 0x08, 0x7e, 0x70, 0x40,
		0x62, 0x65, 0x7d, 0x08, 0x6e, 0x70, 0x40,

		0x62, 0xf5, 0x7d, 0x08, 0x7e, 0xc8,
		0x62, 0xf5, 0x7d, 0x08, 0x6e, 0xc8,
		0x62, 0xf5, 0x7e, 0x08, 0x6e, 0xd9,
		0x62, 0xf5, 0x7e, 0x08, 0x7e, 0x48, 0x40,
		0x62, 0xf5, 0x7e, 0x08, 0x6e, 0x48, 0x40,
		0x62, 0x65, 0x7e, 0x08, 0x7e, 0x70, 0x40,
		0x62, 0x65, 0x7e, 0x08, 0x6e, 0x70, 0x40,
	};
	const size_t n = sizeof(tbl) / sizeof(tbl[0]);
	CYBOZU_TEST_EQUAL(c.getSize(), n);
	CYBOZU_TEST_EQUAL_ARRAY(c.getCode(), tbl, n);
}

// a plain EGPR operand selects REX2 (shorter than EVEX); NF and ND forms still select EVEX
CYBOZU_TEST_AUTO(egpr_rex2)
{
	struct Code : Xbyak::CodeGenerator {
		Code()
		{
			neg(r16);
			neg(r16d);
			neg(r16w);
			neg(r16b);
			not_(r20);
			mul(r20);
			imul(r20);
			div(r20);
			idiv(r20);
			neg(qword [r20+r30*2+8]);
			not_(word [r16]);
			shl(r16, 3);
			shr(r16w, 1);
			sar(r16d, cl);
			rol(r20b, 2);
			rcl(r16, 1);
			ror(r16, cl);
			neg(rax|T_nf);
			shl(rax|T_nf, 3);
			neg(rcx, rax);
			shl(rcx, rax, 3);
		}
	} c;
	const uint8_t tbl[] = {
		// neg r16
		0xd5, 0x18, 0xf7, 0xd8,
		// neg r16d
		0xd5, 0x10, 0xf7, 0xd8,
		// neg r16w
		0x66, 0xd5, 0x10, 0xf7, 0xd8,
		// neg r16b
		0xd5, 0x10, 0xf6, 0xd8,
		// not r20
		0xd5, 0x18, 0xf7, 0xd4,
		// mul r20
		0xd5, 0x18, 0xf7, 0xe4,
		// imul r20
		0xd5, 0x18, 0xf7, 0xec,
		// div r20
		0xd5, 0x18, 0xf7, 0xf4,
		// idiv r20
		0xd5, 0x18, 0xf7, 0xfc,
		// neg qword [r20+r30*2+8]
		0xd5, 0x3a, 0xf7, 0x5c, 0x74, 0x08,
		// not word [r16]
		0x66, 0xd5, 0x10, 0xf7, 0x10,
		// shl r16, 3
		0xd5, 0x18, 0xc1, 0xe0, 0x03,
		// shr r16w, 1
		0x66, 0xd5, 0x10, 0xd1, 0xe8,
		// sar r16d, cl
		0xd5, 0x10, 0xd3, 0xf8,
		// rol r20b, 2
		0xd5, 0x10, 0xc0, 0xc4, 0x02,
		// rcl r16, 1
		0xd5, 0x18, 0xd1, 0xd0,
		// ror r16, cl
		0xd5, 0x18, 0xd3, 0xc8,
		// {nf} neg rax
		0x62, 0xf4, 0xfc, 0x0c, 0xf7, 0xd8,
		// {nf} shl rax, 3
		0x62, 0xf4, 0xfc, 0x0c, 0xc1, 0xe0, 0x03,
		// neg rcx, rax
		0x62, 0xf4, 0xf4, 0x18, 0xf7, 0xd8,
		// shl rcx, rax, 3
		0x62, 0xf4, 0xf4, 0x18, 0xc1, 0xe0, 0x03,
	};
	const size_t n = sizeof(tbl) / sizeof(tbl[0]);
	CYBOZU_TEST_EQUAL(c.getSize(), n);
	CYBOZU_TEST_EQUAL_ARRAY(c.getCode(), tbl, n);
}

#endif
