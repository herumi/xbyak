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
