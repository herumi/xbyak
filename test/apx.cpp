#include <stdio.h>
#include <string.h>
#include <xbyak/xbyak.h>
#include <xbyak/xbyak_util.h>
#include <cybozu/test.hpp>

#ifndef XBYAK64
	#error "only 64-bit mode"
#endif

using namespace Xbyak;

// Encoding tests (including T_nf/T_zu and dfv) are in test/dataset/apx.txt
// (checked by test_by_xed.sh). This file keeps only the operand-guard
// exception tests, which test_by_xed.sh cannot cover.

CYBOZU_TEST_AUTO(push_pop_bad_combination)
{
	struct Code : Xbyak::CodeGenerator {
		Code()
		{
			CYBOZU_TEST_EXCEPTION(push(r16b), std::exception);
			CYBOZU_TEST_EXCEPTION(push(r16d), std::exception);
			CYBOZU_TEST_EXCEPTION(pop(r20b), std::exception);
			CYBOZU_TEST_EXCEPTION(pop(r20d), std::exception);
			// same guard as the classic registers
			CYBOZU_TEST_EXCEPTION(push(al), std::exception);
			CYBOZU_TEST_EXCEPTION(push(eax), std::exception);
			CYBOZU_TEST_EXCEPTION(pop(cl), std::exception);
			CYBOZU_TEST_EXCEPTION(pop(edx), std::exception);
		}
	} c;
}

// push2/pop2 cause #UD if one of the registers is rsp, or if the two
// registers of pop2 are the same.
CYBOZU_TEST_AUTO(push2_pop2_bad_combination)
{
	struct Code : Xbyak::CodeGenerator {
		Code()
		{
			CYBOZU_TEST_NO_EXCEPTION(push2(rax, rcx));
			CYBOZU_TEST_NO_EXCEPTION(push2(rax, rax));
			CYBOZU_TEST_NO_EXCEPTION(push2p(r20, r20));
			CYBOZU_TEST_NO_EXCEPTION(push2(r12, r20)); // r12 and r20 are not rsp
			CYBOZU_TEST_NO_EXCEPTION(pop2(rax, rcx));
			CYBOZU_TEST_NO_EXCEPTION(pop2p(r12, r20));
			CYBOZU_TEST_EXCEPTION(push2(rsp, rax), std::exception);
			CYBOZU_TEST_EXCEPTION(push2(rax, rsp), std::exception);
			CYBOZU_TEST_EXCEPTION(push2p(rsp, rax), std::exception);
			CYBOZU_TEST_EXCEPTION(push2p(r16, rsp), std::exception);
			CYBOZU_TEST_EXCEPTION(pop2(rsp, rax), std::exception);
			CYBOZU_TEST_EXCEPTION(pop2(rax, rsp), std::exception);
			CYBOZU_TEST_EXCEPTION(pop2p(rsp, rax), std::exception);
			CYBOZU_TEST_EXCEPTION(pop2p(rax, rsp), std::exception);
			CYBOZU_TEST_EXCEPTION(pop2(rax, rax), std::exception);
			CYBOZU_TEST_EXCEPTION(pop2(r20, r20), std::exception);
			CYBOZU_TEST_EXCEPTION(pop2p(r8, r8), std::exception);
		}
	} c;
}

// ccmp(op, imm) is 80/81/83 /7 and does not use EVEX.R3/R4, so they must be
// logical 0. test_by_xed.sh can't detect it because xed accepts both.
CYBOZU_TEST_AUTO(ccmp_imm_canonical)
{
	struct Code : Xbyak::CodeGenerator {
		Code()
		{
			const struct {
				uint8_t code[12];
				size_t n;
			} tbl[] = {
				{ { 0x62, 0xF4, 0x84, 0x02, 0x83, 0xF8, 0x05 }, 7 }, // ccmpb(rax, 5)
				{ { 0x62, 0xF4, 0x04, 0x02, 0x80, 0x38, 0x05 }, 7 }, // ccmpb(byte [rax], 5)
				{ { 0x62, 0xDC, 0x1C, 0x02, 0x81, 0xFF, 0x78, 0x56, 0x34, 0x12 }, 10 }, // ccmpb(r31d, 0x12345678, 3)
				{ { 0x62, 0xF4, 0x7D, 0x0F, 0x83, 0x38, 0x05 }, 7 }, // ccmpg(word [rax], 5, 15)
			};
			const uint8_t *begin = getCurr();
			ccmpb(rax, 5);
			ccmpb(byte [rax], 5);
			ccmpb(r31d, 0x12345678, 3);
			ccmpg(word [rax], 5, 15);
			const uint8_t *p = begin;
			for (size_t i = 0; i < sizeof(tbl) / sizeof(tbl[0]); i++) {
				CYBOZU_TEST_EQUAL_ARRAY(p, tbl[i].code, tbl[i].n);
				p += tbl[i].n;
			}
			CYBOZU_TEST_EQUAL(p, getCurr());
		}
	} c;
}

// operands of ccmp/ctest must be GPR or mem with the same size
CYBOZU_TEST_AUTO(ccmp_ctest_bad_combination)
{
	struct Code : Xbyak::CodeGenerator {
		Code()
		{
			CYBOZU_TEST_NO_EXCEPTION(ccmpb(rax, rcx, 3));
			CYBOZU_TEST_NO_EXCEPTION(ccmpb(eax, ptr[rcx], 3));
			CYBOZU_TEST_NO_EXCEPTION(ccmpb(ptr[rcx], ax, 3));
			CYBOZU_TEST_NO_EXCEPTION(ccmpb(dword[rcx], eax, 3));
			CYBOZU_TEST_NO_EXCEPTION(ccmpb(rax, 5));
			CYBOZU_TEST_NO_EXCEPTION(ccmpb(byte[rax], 5));
			CYBOZU_TEST_NO_EXCEPTION(ctestb(rax, rcx));
			CYBOZU_TEST_NO_EXCEPTION(ctestb(ptr[rax], ecx));
			CYBOZU_TEST_NO_EXCEPTION(ctestb(rax, 5));
			CYBOZU_TEST_NO_EXCEPTION(ctestb(word[rax], 5));
			// not GPR
			CYBOZU_TEST_EXCEPTION(ccmpb(xmm1, 0x12), std::exception);
			CYBOZU_TEST_EXCEPTION(ccmpb(zmm1, 0x12), std::exception);
			CYBOZU_TEST_EXCEPTION(ccmpb(mm1, 0x12), std::exception);
			CYBOZU_TEST_EXCEPTION(ccmpb(k1, 0x12), std::exception);
			CYBOZU_TEST_EXCEPTION(ccmpb(xmm1, xmm2), std::exception);
			CYBOZU_TEST_EXCEPTION(ccmpb(xmm1, eax), std::exception);
			CYBOZU_TEST_EXCEPTION(ccmpb(eax, xmm1), std::exception);
			CYBOZU_TEST_EXCEPTION(ccmpb(xmm1, ptr[rax]), std::exception);
			CYBOZU_TEST_EXCEPTION(ccmpb(ptr[rax], xmm1), std::exception);
			CYBOZU_TEST_EXCEPTION(ccmpb(k1, k2), std::exception);
			CYBOZU_TEST_EXCEPTION(ctestb(xmm1, 3), std::exception);
			CYBOZU_TEST_EXCEPTION(ctestb(zmm1, 3), std::exception);
			CYBOZU_TEST_EXCEPTION(ctestb(k1, 3), std::exception);
			CYBOZU_TEST_EXCEPTION(ctestb(xmm1, edx), std::exception);
			CYBOZU_TEST_EXCEPTION(ctestb(rax, xmm1), std::exception);
			CYBOZU_TEST_EXCEPTION(ctestb(ptr[rax], xmm1), std::exception);
			// size mismatch
			CYBOZU_TEST_EXCEPTION(ccmpb(eax, cx), std::exception);
			CYBOZU_TEST_EXCEPTION(ccmpb(rax, ecx), std::exception);
			CYBOZU_TEST_EXCEPTION(ccmpb(dword[rax], rcx), std::exception);
			CYBOZU_TEST_EXCEPTION(ccmpb(rcx, dword[rax]), std::exception);
			CYBOZU_TEST_EXCEPTION(ctestb(eax, rcx), std::exception);
			CYBOZU_TEST_EXCEPTION(ctestb(dword[rax], rcx), std::exception);
		}
	} c;
}

CYBOZU_TEST_AUTO(aeskl)
{
	struct Code : Xbyak::CodeGenerator {
		Code()
		{
			CYBOZU_TEST_EXCEPTION(aesdec128kl(xmm15, ptr[r30+r29*8+0x34]), std::exception);
			CYBOZU_TEST_EXCEPTION(aesdec256kl(xmm15, ptr[r30+r29*8+0x34]), std::exception);
			CYBOZU_TEST_EXCEPTION(aesdecwide128kl(ptr[r30+r29*8+0x34]), std::exception);
			CYBOZU_TEST_EXCEPTION(aesdecwide256kl(ptr[r30+r29*8+0x34]), std::exception);
			CYBOZU_TEST_EXCEPTION(aesenc128kl(xmm15, ptr[r30+r29*8+0x34]), std::exception);
			CYBOZU_TEST_EXCEPTION(aesenc256kl(xmm15, ptr[r30+r29*8+0x34]), std::exception);
			CYBOZU_TEST_EXCEPTION(aesencwide128kl(ptr[r30+r29*8+0x34]), std::exception);
			CYBOZU_TEST_EXCEPTION(aesencwide256kl(ptr[r30+r29*8+0x34]), std::exception);
		}
	} c;
}

// Key Locker is not promoted by APX (no REX2/EVEX form), so EGPR is invalid

CYBOZU_TEST_AUTO(encodekey)
{
	struct Code : Xbyak::CodeGenerator {
		Code()
		{
			CYBOZU_TEST_EXCEPTION(encodekey128(r30d, r29d), std::exception);
			CYBOZU_TEST_EXCEPTION(encodekey256(r30d, r29d), std::exception);
		}
	} c;
}

// SHA-NI is not promoted by APX (no EVEX form), so an EGPR address is invalid

CYBOZU_TEST_AUTO(sha)
{
	struct Code : Xbyak::CodeGenerator {
		Code()
		{
			CYBOZU_TEST_EXCEPTION(sha1msg1(xmm15, ptr [r30+r29*8+0x12]), std::exception);
			CYBOZU_TEST_EXCEPTION(sha1msg2(xmm15, ptr [r30+r29*8+0x12]), std::exception);
			CYBOZU_TEST_EXCEPTION(sha1nexte(xmm15, ptr [r30+r29*8+0x12]), std::exception);
			CYBOZU_TEST_EXCEPTION(sha256msg1(xmm15, ptr [r30+r29*8+0x12]), std::exception);
			CYBOZU_TEST_EXCEPTION(sha256msg2(xmm15, ptr [r30+r29*8+0x12]), std::exception);
			CYBOZU_TEST_EXCEPTION(sha256rnds2(xmm15, ptr [r30+r29*8+0x12]), std::exception);
			CYBOZU_TEST_EXCEPTION(sha1rnds4(xmm15, ptr [r30+r29*8+0x12], 0x23), std::exception);
		}
	} c;
}
