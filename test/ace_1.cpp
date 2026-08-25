#include <stdio.h>
#include <string.h>
#include <xbyak/xbyak.h>
#include <xbyak/xbyak_util.h>
#include <cybozu/test.hpp>

#ifndef XBYAK64
	#error "only 64-bit mode"
#endif

using namespace Xbyak;

// Positive encoding tests for ACE 1.15 are in dataset/ace_1.txt (run by test_by_xed.sh).
// This file keeps only the checks xed cannot cover: operand-guard exceptions.

// negative tests for the operand guards (opCvt1/opCvt7/opX_XM)
CYBOZU_TEST_AUTO(ace_1_bad_combination)
{
	struct Code : Xbyak::CodeGenerator {
		Code()
		{
			// vcvt{bf,hf}82ps : src is xmm or mem regardless of dst width
			CYBOZU_TEST_EXCEPTION(vcvtbf82ps(zm1, ym2), std::exception);
			CYBOZU_TEST_EXCEPTION(vcvthf82ps(xm1, zm2), std::exception);
			// vcvtbf42hf8 : (x|y, x/m), (z, y/m)
			CYBOZU_TEST_EXCEPTION(vcvtbf42hf8(zm1, xm2), std::exception);
			CYBOZU_TEST_EXCEPTION(vcvtbf42hf8(xm1, ym2), std::exception);
			// vcvtbiasps2* : dst is fixed xmm and bias/src widths must match
			CYBOZU_TEST_EXCEPTION(vcvtbiasps2bf8(ym1, zm2, zm3), std::exception);
			CYBOZU_TEST_EXCEPTION(vcvtbiasps2bf8(xm1, ym2, zm3), std::exception);
			CYBOZU_TEST_EXCEPTION(vcvtbiasps2hf8s(xm1, zm2, ym3), std::exception);
			// vcvt{bf,hf}82bf4s : (x, x), (x, y), (y, z) only
			CYBOZU_TEST_EXCEPTION(vcvtbf82bf4s(ym1, ym2), std::exception);
			CYBOZU_TEST_EXCEPTION(vcvthf82bf4s(xm1, zm2), std::exception);
			// vpmovssdb : dst is xmm or mem
			CYBOZU_TEST_EXCEPTION(vpmovssdb(ym1, ym2), std::exception);
		}
	} c;
}
