#include <stdio.h>
#include <string.h>
#include <xbyak/xbyak.h>
#include <xbyak/xbyak_util.h>
#include <cybozu/test.hpp>

#ifndef XBYAK64
	#error "only 64-bit mode"
#endif

using namespace Xbyak;

CYBOZU_TEST_AUTO(ace_1_bsr)
{
	struct Code : Xbyak::CodeGenerator {
		Code()
		{
			bsrinit(bsr0);
			bsrmovf(bsr0, zmm1, zmm2);
			bsrmovf(bsr0, zmm17, ptr[r20+r21*4+0x40]);
			bsrmovh(bsr0, zmm3);
			bsrmovh(zmm20, bsr0);
			bsrmovh(bsr0, ptr[rax+rcx*1+0x10]);
			bsrmovh(ptr[rbx+rdx*2+0x18], bsr0);
			bsrmovl(bsr0, zmm9);
			bsrmovl(zmm25, bsr0);
			bsrmovl(bsr0, ptr[r16+r17*8+0x20]);
			bsrmovl(ptr[rsi+rdi*1+0x8], bsr0);
		}
	} c;
	const uint8_t tbl[] = {
		0xC4, 0xE2, 0xFB, 0x49, 0xC0, // bsrinit(bsr0)
		0x62, 0xF6, 0xF4, 0x48, 0x95, 0xC2, // bsrmovf(bsr0, zmm1, zmm2)
		0x62, 0xFE, 0xF0, 0x40, 0x95, 0x44, 0xAC, 0x40, // bsrmovf(bsr0, zmm17, ptr[r20+r21*4+0x40])
		0x62, 0xF6, 0xFF, 0x48, 0x95, 0xC3, // bsrmovh(bsr0, zmm3) load
		0x62, 0xB6, 0x7F, 0x48, 0x95, 0xC4, // bsrmovh(zmm20, bsr0) store
		0x62, 0xF6, 0xFF, 0x48, 0x95, 0x44, 0x08, 0x10, // bsrmovh(bsr0, ptr[rax+rcx*1+0x10]) load
		0x62, 0xF6, 0x7F, 0x48, 0x95, 0x44, 0x53, 0x18, // bsrmovh(ptr[rbx+rdx*2+0x18], bsr0) store
		0x62, 0xD6, 0xFE, 0x48, 0x95, 0xC1, // bsrmovl(bsr0, zmm9) load
		0x62, 0x96, 0x7E, 0x48, 0x95, 0xC1, // bsrmovl(zmm25, bsr0) store
		0x62, 0xFE, 0xFA, 0x48, 0x95, 0x44, 0xC8, 0x20, // bsrmovl(bsr0, ptr[r16+r17*8+0x20]) load
		0x62, 0xF6, 0x7E, 0x48, 0x95, 0x44, 0x3E, 0x08, // bsrmovl(ptr[rsi+rdi*1+0x8], bsr0) store
	};
	const size_t n = sizeof(tbl);
	CYBOZU_TEST_EQUAL(c.getSize(), n);
	CYBOZU_TEST_EQUAL_ARRAY(c.getCode(), tbl, n);
}

CYBOZU_TEST_AUTO(ace_1_tilemov)
{
	struct Code : Xbyak::CodeGenerator {
		Code()
		{
			tilemovcol(tmm1, zmm2, uint8_t(3));
			tilemovcol(tmm3, zmm18, eax);
			tilemovcol(tmm5, zmm7, r20d);
			tilemovrow(zmm1, tmm2, uint8_t(3));
			tilemovrow(zmm20, tmm4, eax);
			tilemovrow(tmm1, zmm2, uint8_t(5));
			tilemovrow(tmm3, zmm22, r24d);
		}
	} c;
	const uint8_t tbl[] = {
		0x62, 0xF3, 0xFD, 0x48, 0x2F, 0xCA, 0x03, // tilemovcol(tmm1, zmm2, 3)
		0x62, 0xB2, 0xFD, 0x48, 0x4B, 0xDA, // tilemovcol(tmm3, zmm18, eax)
		0x62, 0xF2, 0xDD, 0x40, 0x4B, 0xEF, // tilemovcol(tmm5, zmm7, r20d)
		0x62, 0xF3, 0x7D, 0x48, 0x07, 0xCA, 0x03, // tilemovrow(zmm1, tmm2, 3) extract-imm
		0x62, 0xE2, 0x7D, 0x48, 0x4A, 0xE4, // tilemovrow(zmm20, tmm4, eax) extract-r32
		0x62, 0xF3, 0xFD, 0x48, 0x07, 0xCA, 0x05, // tilemovrow(tmm1, zmm2, 5) load-imm
		0x62, 0xB2, 0xBD, 0x40, 0x4A, 0xDE, // tilemovrow(tmm3, zmm22, r24d) load-r32
	};
	const size_t n = sizeof(tbl);
	CYBOZU_TEST_EQUAL(c.getSize(), n);
	CYBOZU_TEST_EQUAL_ARRAY(c.getCode(), tbl, n);
}

CYBOZU_TEST_AUTO(ace_1_fp8_from_ps)
{
	struct Code : Xbyak::CodeGenerator {
		Code()
		{
			vcvtps2bf8(xm1, xm2);
			vcvtps2bf8(xm1, xword[rax]);
			vcvtps2bf8(xm1, xword_b[rax]);
			vcvtps2bf8s(xm3, ym4);
			vcvtps2hf8(xm5|k3, zm6);
			vcvtps2hf8s(xm7|k4|T_z, xword[rax+rcx*4+0x20]);
			vcvtrops2hf8(xm1, xm2);
			vcvtrops2hf8s(xm3, zm5);
		}
	} c;
	const uint8_t tbl[] = {
		0x62, 0xF5, 0x7E, 0x08, 0x39, 0xCA, // vcvtps2bf8(xm1, xm2)
		0x62, 0xF5, 0x7E, 0x08, 0x39, 0x08, // vcvtps2bf8(xm1, xword[rax])
		0x62, 0xF5, 0x7E, 0x18, 0x39, 0x08, // vcvtps2bf8(xm1, xword_b[rax])
		0x62, 0xF5, 0x7E, 0x28, 0x3B, 0xDC, // vcvtps2bf8s(xm3, ym4)
		0x62, 0xF5, 0x7E, 0x4B, 0x38, 0xEE, // vcvtps2hf8(xm5|k3, zm6)
		0x62, 0xF5, 0x7E, 0x8C, 0x3A, 0x7C, 0x88, 0x02, // vcvtps2hf8s(xm7|k4|T_z, xword[rax+rcx*4+0x20])
		0x62, 0xF5, 0x7D, 0x08, 0x38, 0xCA, // vcvtrops2hf8(xm1, xm2)
		0x62, 0xF5, 0x7D, 0x48, 0x3A, 0xDD, // vcvtrops2hf8s(xm3, zm5)
	};
	const size_t n = sizeof(tbl);
	CYBOZU_TEST_EQUAL(c.getSize(), n);
	CYBOZU_TEST_EQUAL_ARRAY(c.getCode(), tbl, n);
}

CYBOZU_TEST_AUTO(ace_1_fp8_biased_from_ps)
{
	struct Code : Xbyak::CodeGenerator {
		Code()
		{
			vcvtbiasps2bf8(xm1, xm2, xm3);
			vcvtbiasps2bf8(xm1, ym2, ym3);
			vcvtbiasps2bf8s(xm1, zm2, zm3);
			vcvtbiasps2hf8(xm4|k5, xm6, xword[rax+rcx*2+0x10]);
			vcvtbiasps2hf8s(xm7|k2|T_z, zm8, zm9);
			vcvtbiasps2bf8(xm1, xm2, xword_b[rax]);
		}
	} c;
	const uint8_t tbl[] = {
		0x62, 0xF5, 0x6C, 0x08, 0x39, 0xCB, // vcvtbiasps2bf8(xm1, xm2, xm3)
		0x62, 0xF5, 0x6C, 0x28, 0x39, 0xCB, // vcvtbiasps2bf8(xm1, ym2, ym3)
		0x62, 0xF5, 0x6C, 0x48, 0x3B, 0xCB, // vcvtbiasps2bf8s(xm1, zm2, zm3)
		0x62, 0xF5, 0x4C, 0x0D, 0x38, 0x64, 0x48, 0x01, // vcvtbiasps2hf8(xm4|k5, xm6, xword[rax+rcx*2+0x10])
		0x62, 0xD5, 0x3C, 0xCA, 0x3A, 0xF9, // vcvtbiasps2hf8s(xm7|k2|T_z, zm8, zm9)
		0x62, 0xF5, 0x6C, 0x18, 0x39, 0x08, // vcvtbiasps2bf8(xm1, xm2, xword_b[rax])
	};
	const size_t n = sizeof(tbl);
	CYBOZU_TEST_EQUAL(c.getSize(), n);
	CYBOZU_TEST_EQUAL_ARRAY(c.getCode(), tbl, n);
}

CYBOZU_TEST_AUTO(ace_1_fp8_to_ps)
{
	struct Code : Xbyak::CodeGenerator {
		Code()
		{
			vcvtbf82ps(xm1, xm2);
			vcvtbf82ps(ym3, xm4);
			vcvtbf82ps(zm5|k6, xm7);
			vcvtbf82ps(xm1, dword[rax]);
			vcvthf82ps(xm1, xm2);
			vcvthf82ps(ym3|k4|T_z, qword[rax+rcx*2+0x8]);
			vcvthf82ps(zm5, xword[rax]);
		}
	} c;
	const uint8_t tbl[] = {
		0x62, 0xF5, 0xFC, 0x08, 0x36, 0xCA, // vcvtbf82ps(xm1, xm2)
		0x62, 0xF5, 0xFC, 0x28, 0x36, 0xDC, // vcvtbf82ps(ym3, xm4)
		0x62, 0xF5, 0xFC, 0x4E, 0x36, 0xEF, // vcvtbf82ps(zm5|k6, xm7)
		0x62, 0xF5, 0xFC, 0x08, 0x36, 0x08, // vcvtbf82ps(xm1, dword[rax])
		0x62, 0xF5, 0x7C, 0x08, 0x36, 0xCA, // vcvthf82ps(xm1, xm2)
		0x62, 0xF5, 0x7C, 0xAC, 0x36, 0x5C, 0x48, 0x01, // vcvthf82ps(ym3|k4|T_z, qword[rax+rcx*2+0x8])
		0x62, 0xF5, 0x7C, 0x48, 0x36, 0x28, // vcvthf82ps(zm5, xword[rax])
	};
	const size_t n = sizeof(tbl);
	CYBOZU_TEST_EQUAL(c.getSize(), n);
	CYBOZU_TEST_EQUAL_ARRAY(c.getCode(), tbl, n);
}

CYBOZU_TEST_AUTO(ace_1_top)
{
	struct Code : Xbyak::CodeGenerator {
		Code()
		{
			top2bf16ps(tmm1, zmm2, zmm3);
			top2bf16ps(tmm2, zmm17, zmm30);
			top4bssd(tmm1, zmm2, zmm3);
			top4bsud(tmm2, zmm4, zmm5);
			top4busd(tmm3, zmm6, zmm7);
			top4buud(tmm4, zmm18, zmm19);
			top4mxbf8ps(tmm1, zmm2, zmm3, 0x0);
			top4mxbhf8ps(tmm2, zmm20, zmm21, 0x5);
			top4mxhbf8ps(tmm3, zmm4, zmm5, 0xA);
			top4mxhf8ps(tmm4, zmm6, zmm7, 0xF);
			top4mxbssps(tmm5, zmm22, zmm23, 0x3);
		}
	} c;
	const uint8_t tbl[] = {
		0x62, 0xF2, 0x66, 0x48, 0x5C, 0xCA, // top2bf16ps(tmm1, zmm2, zmm3)
		0x62, 0xB2, 0x0E, 0x40, 0x5C, 0xD1, // top2bf16ps(tmm2, zmm17, zmm30)
		0x62, 0xF2, 0x67, 0x48, 0x5E, 0xCA, // top4bssd(tmm1, zmm2, zmm3)
		0x62, 0xF2, 0x56, 0x48, 0x5E, 0xD4, // top4bsud(tmm2, zmm4, zmm5)
		0x62, 0xF2, 0x45, 0x48, 0x5E, 0xDE, // top4busd(tmm3, zmm6, zmm7)
		0x62, 0xB2, 0x64, 0x40, 0x5E, 0xE2, // top4buud(tmm4, zmm18, zmm19)
		0x62, 0xF3, 0x64, 0x48, 0x8D, 0xCA, 0x00, // top4mxbf8ps(tmm1, zmm2, zmm3, 0x0)
		0x62, 0xB3, 0x57, 0x40, 0x8D, 0xD4, 0x05, // top4mxbhf8ps(tmm2, zmm20, zmm21, 0x5)
		0x62, 0xF3, 0x56, 0x48, 0x8D, 0xDC, 0x0A, // top4mxhbf8ps(tmm3, zmm4, zmm5, 0xA)
		0x62, 0xF3, 0x45, 0x48, 0x8D, 0xE6, 0x0F, // top4mxhf8ps(tmm4, zmm6, zmm7, 0xF)
		0x62, 0xB3, 0x47, 0x40, 0x8F, 0xEE, 0x03, // top4mxbssps(tmm5, zmm22, zmm23, 0x3)
	};
	const size_t n = sizeof(tbl);
	CYBOZU_TEST_EQUAL(c.getSize(), n);
	CYBOZU_TEST_EQUAL_ARRAY(c.getCode(), tbl, n);
}

CYBOZU_TEST_AUTO(ace_1_fp4_to_fp8)
{
	struct Code : Xbyak::CodeGenerator {
		Code()
		{
			vcvtbf42hf8(xm1, xm2);
			vcvtbf42hf8(ym3, xm4);
			vcvtbf42hf8(zm5|k6, ym7);
			vcvtbf42hf8(xm1, qword[rax]);
			vcvtbf42hf8(ym3|k4|T_z, xword[rax+rcx*2+0x10]);
		}
	} c;
	const uint8_t tbl[] = {
		0x62, 0xF5, 0x7C, 0x08, 0x37, 0xCA, // vcvtbf42hf8(xm1, xm2)
		0x62, 0xF5, 0x7C, 0x28, 0x37, 0xDC, // vcvtbf42hf8(ym3, xm4)
		0x62, 0xF5, 0x7C, 0x4E, 0x37, 0xEF, // vcvtbf42hf8(zm5|k6, ym7)
		0x62, 0xF5, 0x7C, 0x08, 0x37, 0x08, // vcvtbf42hf8(xm1, qword[rax])
		0x62, 0xF5, 0x7C, 0xAC, 0x37, 0x5C, 0x48, 0x01, // vcvtbf42hf8(ym3|k4|T_z, xword[rax+rcx*2+0x10])
	};
	const size_t n = sizeof(tbl);
	CYBOZU_TEST_EQUAL(c.getSize(), n);
	CYBOZU_TEST_EQUAL_ARRAY(c.getCode(), tbl, n);
}

CYBOZU_TEST_AUTO(ace_1_fp6_fp8_reg_only)
{
	// vcvtbf82bf6s/vcvthf82hf6s encode with ModRM.reg=source, ModRM.rm=dest -- reversed from
	// vcvtbf62hf8/vcvthf62hf8 above.
	struct Code : Xbyak::CodeGenerator {
		Code()
		{
			vcvtbf62hf8(xm1, xm2);
			vcvtbf62hf8(ym3|k4, ym5);
			vcvthf62hf8(zm6|k7|T_z, zm8);
			vcvtbf82bf6s(xm1, xm2);
			vcvtbf82bf6s(ym3, ym4);
			vcvthf82hf6s(zm5, zm6);
		}
	} c;
	const uint8_t tbl[] = {
		0x62, 0xF5, 0xFD, 0x08, 0x37, 0xCA, // vcvtbf62hf8(xm1, xm2)
		0x62, 0xF5, 0xFD, 0x2C, 0x37, 0xDD, // vcvtbf62hf8(ym3|k4, ym5)
		0x62, 0xD5, 0x7D, 0xCF, 0x37, 0xF0, // vcvthf62hf8(zm6|k7|T_z, zm8)
		0x62, 0xF5, 0xFE, 0x08, 0x3E, 0xD1, // vcvtbf82bf6s(xm1, xm2)
		0x62, 0xF5, 0xFE, 0x28, 0x3E, 0xE3, // vcvtbf82bf6s(ym3, ym4)
		0x62, 0xF5, 0x7E, 0x48, 0x3C, 0xF5, // vcvthf82hf6s(zm5, zm6)
	};
	const size_t n = sizeof(tbl);
	CYBOZU_TEST_EQUAL(c.getSize(), n);
	CYBOZU_TEST_EQUAL_ARRAY(c.getCode(), tbl, n);
}

CYBOZU_TEST_AUTO(ace_1_fp8_to_fp4)
{
	struct Code : Xbyak::CodeGenerator {
		Code()
		{
			vcvtbf82bf4s(xm1, xm2);
			vcvtbf82bf4s(xm3, ym4);
			vcvthf82bf4s(ym5, zm6);
			vcvtbf82bf4s(qword[rax], xm1);
			vcvthf82bf4s(xword[rax+rcx*2+0x10], ym2);
		}
	} c;
	const uint8_t tbl[] = {
		0x62, 0xF5, 0xFE, 0x08, 0x3D, 0xD1, // vcvtbf82bf4s(xm1, xm2)
		0x62, 0xF5, 0xFE, 0x28, 0x3D, 0xE3, // vcvtbf82bf4s(xm3, ym4)
		0x62, 0xF5, 0x7E, 0x48, 0x3D, 0xF5, // vcvthf82bf4s(ym5, zm6)
		0x62, 0xF5, 0xFE, 0x08, 0x3D, 0x08, // vcvtbf82bf4s(qword[rax], xm1)
		0x62, 0xF5, 0x7E, 0x28, 0x3D, 0x54, 0x48, 0x01, // vcvthf82bf4s(xword[rax+rcx*2+0x10], ym2)
	};
	const size_t n = sizeof(tbl);
	CYBOZU_TEST_EQUAL(c.getSize(), n);
	CYBOZU_TEST_EQUAL_ARRAY(c.getCode(), tbl, n);
}

CYBOZU_TEST_AUTO(ace_1_unpackb)
{
	struct Code : Xbyak::CodeGenerator {
		Code()
		{
			vunpackb(xm1, xm2, 3);
			vunpackb(ym3|k4, ym5, 5);
			vunpackb(zm6|k7|T_z, zm8, 0xA);
			vunpackb(zm1, zword[rax+rcx*4+0x40], 2);
		}
	} c;
	const uint8_t tbl[] = {
		0x62, 0xF3, 0x7C, 0x08, 0x3D, 0xCA, 0x03, // vunpackb(xm1, xm2, 3)
		0x62, 0xF3, 0x7C, 0x2C, 0x3D, 0xDD, 0x05, // vunpackb(ym3|k4, ym5, 5)
		0x62, 0xD3, 0x7C, 0xCF, 0x3D, 0xF0, 0x0A, // vunpackb(zm6|k7|T_z, zm8, 0xA)
		0x62, 0xF3, 0x7C, 0x48, 0x3D, 0x4C, 0x88, 0x01, 0x02, // vunpackb(zm1, zword[rax+rcx*4+0x40], 2)
	};
	const size_t n = sizeof(tbl);
	CYBOZU_TEST_EQUAL(c.getSize(), n);
	CYBOZU_TEST_EQUAL_ARRAY(c.getCode(), tbl, n);
}

CYBOZU_TEST_AUTO(ace_1_pmovssdb)
{
	struct Code : Xbyak::CodeGenerator {
		Code()
		{
			vpmovssdb(xm1, xm2);
			vpmovssdb(xm3, ym4);
			vpmovssdb(xm5|k6, zm7);
			vpmovssdb(dword[rax], xm1);
			vpmovssdb(xword[rax+rcx*4+0x20]|k4, zm5);
		}
	} c;
	const uint8_t tbl[] = {
		0x62, 0xF2, 0x7E, 0x08, 0x41, 0xD1, // vpmovssdb(xm1, xm2)
		0x62, 0xF2, 0x7E, 0x28, 0x41, 0xE3, // vpmovssdb(xm3, ym4)
		0x62, 0xF2, 0x7E, 0x4E, 0x41, 0xFD, // vpmovssdb(xm5|k6, zm7)
		0x62, 0xF2, 0x7E, 0x08, 0x41, 0x08, // vpmovssdb(dword[rax], xm1)
		0x62, 0xF2, 0x7E, 0x4C, 0x41, 0x6C, 0x88, 0x02, // vpmovssdb(xword[rax+rcx*4+0x20]|k4, zm5)
	};
	const size_t n = sizeof(tbl);
	CYBOZU_TEST_EQUAL(c.getSize(), n);
	CYBOZU_TEST_EQUAL_ARRAY(c.getCode(), tbl, n);
}
