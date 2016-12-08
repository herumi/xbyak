// copy CodeGenerator::AVXtype
	enum AVXtype {
		T_66 = 1 << 0,
		T_F3 = 1 << 1,
		T_F2 = 1 << 2,
		T_0F = 1 << 3,
		T_0F38 = 1 << 4,
		T_0F3A = 1 << 5,
		T_L0 = 1 << 6,
		T_L1 = 1 << 7,
		T_W0 = 1 << 8,
		T_W1 = 1 << 9,
		T_EW0 = 1 << 10,
		T_EW1 = 1 << 11,
		T_YMM = 1 << 12, // support YMM, ZMM
		T_EVEX = 1 << 13,
		T_ER_X = 1 << 14, // xmm{er}
		T_ER_Y = 1 << 15, // ymm{er}
		T_ER_Z = 1 << 16, // zmm{er}
		T_SAE_X = 1 << 17, // xmm{sae}
		T_SAE_Y = 1 << 18, // ymm{sae}
		T_SAE_Z = 1 << 19, // zmm{sae}
		T_MUST_EVEX = 1 << 20, // contains T_EVEX
		T_B32 = 1 << 21, // m32bcst
		T_B64 = 1 << 22, // m64bcst
		T_M_K = 1 << 23, // mem{k}
		T_N1 = 1 << 24,
		T_N2 = 1 << 25,
		T_N4 = 1 << 26,
		T_N8 = 1 << 27,
		T_N16 = 1 << 28,
		T_N32 = 1 << 29,
		T_N_VL = 1 << 30, // N * (1, 2, 4) for VL
		T_DUP = 1 << 31, // N = (8, 32, 64)
		T_XXX
	};

const int NONE = 256; // same as Xbyak::CodeGenerator::NONE

std::string type2String(int type)
{
	std::string str;
	if (type & T_66) {
		if (!str.empty()) str += " | ";
		str += "T_66";
	}
	if (type & T_F3) {
		if (!str.empty()) str += " | ";
		str += "T_F3";
	}
	if (type & T_F2) {
		if (!str.empty()) str += " | ";
		str += "T_F2";
	}
	if (type & T_0F) {
		if (!str.empty()) str += " | ";
		str += "T_0F";
	}
	if (type & T_0F38) {
		if (!str.empty()) str += " | ";
		str += "T_0F38";
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
		str += "T_B32";
	}
	if (type & T_B64) {
		if (!str.empty()) str += " | ";
		str += "T_B64";
	}
	if (type & T_M_K) {
		if (!str.empty()) str += " | ";
		str += "T_M_K";
	}
	if (type & T_N1) {
		if (!str.empty()) str += " | ";
		str += "T_N1";
	}
	if (type & T_N2) {
		if (!str.empty()) str += " | ";
		str += "T_N2";
	}
	if (type & T_N4) {
		if (!str.empty()) str += " | ";
		str += "T_N4";
	}
	if (type & T_N8) {
		if (!str.empty()) str += " | ";
		str += "T_N8";
	}
	if (type & T_N16) {
		if (!str.empty()) str += " | ";
		str += "T_N16";
	}
	if (type & T_N32) {
		if (!str.empty()) str += " | ";
		str += "T_N32";
	}
	if (type & T_N_VL) {
		if (!str.empty()) str += " | ";
		str += "T_N_VL";
	}
	if (type & T_DUP) {
		if (!str.empty()) str += " | ";
		str += "T_DUP";
	}
	return str;
}