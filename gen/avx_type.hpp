#include <assert.h>
#include "avx_type_def.h"

const int NONE = 256; // same as Xbyak::CodeGenerator::NONE

std::string type2String(int type)
{
	std::string str;
	int low = type & T_NX_MASK;
	if (0 < low && low < 7) {
		const char *tbl[8] = {
			"T_N1", "T_N2", "T_N4", "T_N8", "T_N16", "T_N32"
		};
		assert(low < int(sizeof(tbl) / sizeof(tbl[0])));
		str = tbl[low - 1];
	}
	if (type & T_N_VL) {
		if (!str.empty()) str += " | ";
		str += "T_N_VL";
	}
	if (type & T_VEX) {
		if (!str.empty()) str += " | ";
		str += "T_VEX";
	}
	if ((type & T_NX_MASK) == T_DUP) {
		if (!str.empty()) str += " | ";
		str += "T_DUP";
	}
	if (type & T_F2) {
		if (!str.empty()) str += " | ";
		switch (type & T_F2) {
		case T_66: str += "T_66"; break;
		case T_F3: str += "T_F3"; break;
		case T_F2: str += "T_F2"; break;
		default: break;
		}
	}
	if (type & T_0F) {
		if (!str.empty()) str += " | ";
		if (type & T_FP16) {
			str += "T_MAP5";
		} else {
			str += "T_0F";
		}
	}
	if (type & T_0F38) {
		if (!str.empty()) str += " | ";
		if (type & T_FP16) {
			str += "T_MAP6";
		} else {
			str += "T_0F38";
		}
	}
	if (type & T_0F3A) {
		if (!str.empty()) str += " | ";
		str += "T_0F3A";
	}
	if (type & T_L0) {
		if (!str.empty()) str += " | ";
		str += "VEZ_L0";
	}
	if (type & T_L1) {
		if (!str.empty()) str += " | ";
		str += "VEZ_L1";
	}
	if (type & T_W0) {
		if (!str.empty()) str += " | ";
		str += "T_W0";
	}
	if (type & T_W1) {
		if (!str.empty()) str += " | ";
		str += "T_W1";
	}
	if (type & T_EW0) {
		if (!str.empty()) str += " | ";
		str += "T_EW0";
	}
	if (type & T_EW1) {
		if (!str.empty()) str += " | ";
		str += "T_EW1";
	}
	if (type & T_YMM) {
		if (!str.empty()) str += " | ";
		str += "T_YMM";
	}
	if (type & T_EVEX) {
		if (!str.empty()) str += " | ";
		str += "T_EVEX";
	}
	if (type & T_ER_X) {
		if (!str.empty()) str += " | ";
		str += "T_ER_X";
	}
	if (type & T_ER_Y) {
		if (!str.empty()) str += " | ";
		str += "T_ER_Y";
	}
	if (type & T_ER_Z) {
		if (!str.empty()) str += " | ";
		str += "T_ER_Z";
	}
	if (type & T_ER_R) {
		if (!str.empty()) str += " | ";
		str += "T_ER_R";
	}
	if (type & T_SAE_X) {
		if (!str.empty()) str += " | ";
		str += "T_SAE_X";
	}
	if (type & T_SAE_Y) {
		if (!str.empty()) str += " | ";
		str += "T_SAE_Y";
	}
	if (type & T_SAE_Z) {
		if (!str.empty()) str += " | ";
		str += "T_SAE_Z";
	}
	if (type & T_MUST_EVEX) {
		if (!str.empty()) str += " | ";
		str += "T_MUST_EVEX";
	}
	if (type & T_B32) {
		if (!str.empty()) str += " | ";
		if (type & T_B64) {
			str += "T_B16"; // T_B16 = T_B32 | T_B64
		} else {
			str += "T_B32";
		}
	} else if (type & T_B64) {
		if (!str.empty()) str += " | ";
		str += "T_B64";
	}
	if (type & T_M_K) {
		if (!str.empty()) str += " | ";
		str += "T_M_K";
	}
	if (type & T_VSIB) {
		if (!str.empty()) str += " | ";
		str += "T_VSIB";
	}
	if (type & T_MEM_EVEX) {
		if (!str.empty()) str += " | ";
		str += "T_MEM_EVEX";
	}
	return str;
}
