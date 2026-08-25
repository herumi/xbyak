#include <assert.h>
#include <stdio.h>
#include <stdlib.h>
#include "avx_type_def.h"

const int NONE = 256; // same as Xbyak::CodeGenerator::NONE

std::string type2String(uint64_t type)
{
	if (type == 0) return "T_NONE";
	std::string str;
	int low = type & T_NX_MASK;
	if (0 < low && low < 7) {
		const char *tbl[8] = {
			"T_N1", "T_N2", "T_N4", "T_N8", "T_N16", "T_N32"
		};
		assert(low < int(sizeof(tbl) / sizeof(tbl[0])));
		str = tbl[low - 1];
	}
	if (type & T_N_VL) str += "|T_N_VL";
	if (type & T_APX) str += "|T_APX";
	if ((type & T_NX_MASK) == T_DUP) str += "|T_DUP";
	if (type & T_66) str += "|T_66";
	if (type & T_F3) str += "|T_F3";
	if (type & T_F2) str += "|T_F2";
	const uint64_t map = type & T_MAP_MASK;
	if (map == T_MAP5) str += "|T_MAP5";
	if (map == T_0F) str += "|T_0F";
	if (map == T_MAP6) str += "|T_MAP6";
	if (map == T_0F38) str += "|T_0F38";
	if (map == T_0F3A) str += "|T_0F3A";
	if (type & T_L1) str += "|T_L1";
	if (type & T_W0) str += "|T_W0";
	if (type & T_W1) str += "|T_W1";
	if (type & T_EW1) str += "|T_EW1";
	if (type & T_YMM) str += "|T_YMM";
	const uint64_t evex = type & T_EVEX_MASK;
	if (evex == T_EVEX) str += "|T_EVEX";
	if (evex == T_EVEX_IF_MEM) str += "|T_EVEX_IF_MEM";
	const uint64_t erSae = type & T_ER_SAE_MASK;
	if (erSae == T_ER_X) str += "|T_ER_X";
	if (erSae == T_ER_Y) str += "|T_ER_Y";
	if (erSae == T_ER_Z) str += "|T_ER_Z";
	if (erSae == T_ER_R) str += "|T_ER_R";
	if (erSae == T_SAE_X) str += "|T_SAE_X";
	if (erSae == T_SAE_Y) str += "|T_SAE_Y";
	if (erSae == T_SAE_Z) str += "|T_SAE_Z";
	if (evex == T_MUST_EVEX) str += "|T_MUST_EVEX";

	switch (type & T_B16) { // T_B16 = T_B32 | T_B64
	case T_B16: str += "|T_B16"; break;
	case T_B32: str += "|T_B32"; break;
	case T_B64: str += "|T_B64"; break;
	default: break;
	}
	if (type & T_M_K) str += "|T_M_K";
	if (type & T_VSIB) str += "|T_VSIB";
	if (type & T_NF) str += "|T_NF";
	if (type & T_CODE1_IF1) str += "|T_CODE1_IF1";
	if (type & T_NO_CODE1) str += "|T_NO_CODE1";
	if (type & T_ND1) str += "|T_ND1";
	if (type & T_ZU) str += "|T_ZU";

	if (str[0] == '|') str = str.substr(1);
	return str;
}

/*
	verify that a | b does not corrupt a packed field (N, map, er/sae, broadcast) :
	each field must not have different non-zero values in a and b.
	call this wherever the generator emits code that or-merges two type values at runtime
	(opEncoding, opCvt3, ...).
*/
void checkTypeMergeable(uint64_t a, uint64_t b, const char *name)
{
	static const uint64_t maskTbl[] = { T_NX_MASK, T_MAP_MASK, T_ER_SAE_MASK, T_EVEX_MASK, T_B16 };
	for (size_t i = 0; i < sizeof(maskTbl) / sizeof(maskTbl[0]); i++) {
		uint64_t x = a & maskTbl[i];
		uint64_t y = b & maskTbl[i];
		if (x && y && x != y) {
			fprintf(stderr, "%s: type field conflict between (%s) and (%s)\n", name, type2String(a).c_str(), type2String(b).c_str());
			exit(1);
		}
	}
}
