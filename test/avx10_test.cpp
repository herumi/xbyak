#include <stdio.h>
#include <string.h>
#include <string>
#include <xbyak/xbyak.h>
#include <xbyak/xbyak_util.h>
#include <cybozu/inttype.hpp>
#include <cybozu/test.hpp>
#include <algorithm>

using namespace Xbyak;

// ymm with sae is not supported from avx10.2 rev 4.0.
CYBOZU_TEST_AUTO(ymm_with_sae)
{
	struct Code : Xbyak::CodeGenerator {
		Code()
		{
			CYBOZU_TEST_EXCEPTION(vaddpd(ymm1, ymm2, ymm3 |T_rn_sae), std::exception);
			CYBOZU_TEST_EXCEPTION(vcvtph2ibs(xmm1, xmm31 | T_rd_sae), std::exception);
			CYBOZU_TEST_EXCEPTION(vcvtph2ibs(ymm1, ymm31 | T_rd_sae), std::exception);
			CYBOZU_TEST_EXCEPTION(vcvt2ps2phx(ymm1, ymm2, ymm3 | T_rd_sae), std::exception);
			CYBOZU_TEST_EXCEPTION(vminmaxpd(ymm1, ymm2, ymm3 | T_sae, 1), std::exception);
			CYBOZU_TEST_EXCEPTION(vminmaxph(ymm1, ymm2, ymm3 | T_sae, 2), std::exception);
			CYBOZU_TEST_EXCEPTION(vminmaxps(ymm1, ymm2, ymm3 | T_sae, 3), std::exception);
			CYBOZU_TEST_EXCEPTION(vcvtps2ibs(ym1, ym2|T_rd_sae), std::exception);
			CYBOZU_TEST_EXCEPTION(vcvtps2ibs(xm1, xm2|T_rd_sae), std::exception);
		}
	} c;
}

CYBOZU_TEST_AUTO(vmpsadbw)
{
	struct Code : Xbyak::CodeGenerator {
		Code()
		{
			setDefaultEncodingAVX10();
			vmpsadbw(xm1, xm3, xm15, 3); // vex(avx)
			vmpsadbw(ym1, ym3, ptr[rax+128], 3); // vex(avx2)
			setDefaultEncodingAVX10(AVX10v2Encoding);
			vmpsadbw(ym1, ym3, ym15, 3); // evex(avx10.2)
			vmpsadbw(ym1, ym3, ptr[rax+128], 3); // evex(avx10.2)
		}
	} c;
	const uint8_t tbl[] = {
		0xc4, 0xc3, 0x61, 0x42, 0xcf, 0x03,
		0xc4, 0xe3, 0x65, 0x42, 0x88, 0x80, 0x00, 0x00, 0x00, 0x03,
		0x62, 0xd3, 0x66, 0x28, 0x42, 0xcf, 0x03,
		0x62, 0xf3, 0x66, 0x28, 0x42, 0x48, 0x04, 0x03,
	};
	const size_t n = sizeof(tbl) / sizeof(tbl[0]);
	CYBOZU_TEST_EQUAL(c.getSize(), n);
	CYBOZU_TEST_EQUAL_ARRAY(c.getCode(), tbl, n);
}
