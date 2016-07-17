#define XBYAK_DONT_READ_LIST
#include <stdio.h>
#include <string.h>
#include "../xbyak/xbyak.h"
#define NUM_OF_ARRAY(x) (sizeof(x) / sizeof(x[0]))

using namespace Xbyak;
#ifdef _MSC_VER
	#pragma warning(disable : 4996) // scanf
	#define snprintf _snprintf_s
#endif

#include "avx_type.hpp"

void putOpmask()
{
	{
		const struct Tbl {
			const char *name;
			uint8 code;
		} tbl[] = {
			{ "kadd", 0x4A },
			{ "kand", 0x41 },
			{ "kandn", 0x42 },
			{ "kor", 0x45 },
			{ "kxnor", 0x46 },
			{ "kxor", 0x47 },
		};
		for (size_t i = 0; i < NUM_OF_ARRAY(tbl); i++) {
			const Tbl& p = tbl[i];
			printf("void %sw(const Opmask& r1, const Opmask& r2, const Opmask& r3) { opVex(r1, &r2, r3, T_L1 | T_0F | T_W0, 0x%02X); }\n", p.name, p.code);
			printf("void %sq(const Opmask& r1, const Opmask& r2, const Opmask& r3) { opVex(r1, &r2, r3, T_L1 | T_0F | T_W1, 0x%02X); }\n", p.name, p.code);
			printf("void %sb(const Opmask& r1, const Opmask& r2, const Opmask& r3) { opVex(r1, &r2, r3, T_L1 | T_0F | T_66 | T_W0, 0x%02X); }\n", p.name, p.code);
			printf("void %sd(const Opmask& r1, const Opmask& r2, const Opmask& r3) { opVex(r1, &r2, r3, T_L1 | T_0F | T_66 | T_W1, 0x%02X); }\n", p.name, p.code);
		}
		printf("void kunpckbw(const Opmask& r1, const Opmask& r2, const Opmask& r3) { opVex(r1, &r2, r3, T_L1 | T_0F | T_66 | T_W0, 0x4B); }\n");
		printf("void kunpckwd(const Opmask& r1, const Opmask& r2, const Opmask& r3) { opVex(r1, &r2, r3, T_L1 | T_0F | T_W0, 0x4B); }\n");
		printf("void kunpckdq(const Opmask& r1, const Opmask& r2, const Opmask& r3) { opVex(r1, &r2, r3, T_L1 | T_0F | T_W1, 0x4B); }\n");
	}
	{
		const struct Tbl {
			const char *name;
			uint8 code;
		} tbl[] = {
			{ "knot", 0x44 },
			{ "kortest", 0x98 },
			{ "ktest", 0x99 },
		};
		for (size_t i = 0; i < NUM_OF_ARRAY(tbl); i++) {
			const Tbl& p = tbl[i];
			printf("void %sw(const Opmask& r1, const Opmask& r2) { opVex(r1, 0, r2, T_0F | T_W0, 0x%02X); }\n", p.name, p.code);
			printf("void %sq(const Opmask& r1, const Opmask& r2) { opVex(r1, 0, r2, T_0F | T_W1, 0x%02X); }\n", p.name, p.code);
			printf("void %sb(const Opmask& r1, const Opmask& r2) { opVex(r1, 0, r2, T_0F | T_66 | T_W0, 0x%02X); }\n", p.name, p.code);
			printf("void %sd(const Opmask& r1, const Opmask& r2) { opVex(r1, 0, r2, T_0F | T_66 | T_W1, 0x%02X); }\n", p.name, p.code);
		}
	}
	{
		const struct Tbl {
			const char *name;
			uint8 code;
		} tbl[] = {
			{ "kshiftl", 0x32 },
			{ "kshiftr", 0x30 },
		};
		for (size_t i = 0; i < NUM_OF_ARRAY(tbl); i++) {
			const Tbl& p = tbl[i];
			printf("void %sw(const Opmask& r1, const Opmask& r2, uint8 imm) { opVex(r1, 0, r2, T_66 | T_0F3A | T_W1, 0x%02X, imm); }\n", p.name, p.code);
			printf("void %sq(const Opmask& r1, const Opmask& r2, uint8 imm) { opVex(r1, 0, r2, T_66 | T_0F3A | T_W1, 0x%02X, imm); }\n", p.name, p.code + 1);
			printf("void %sb(const Opmask& r1, const Opmask& r2, uint8 imm) { opVex(r1, 0, r2, T_66 | T_0F3A | T_W0, 0x%02X, imm); }\n", p.name, p.code);
			printf("void %sd(const Opmask& r1, const Opmask& r2, uint8 imm) { opVex(r1, 0, r2, T_66 | T_0F3A | T_W0, 0x%02X, imm); }\n", p.name, p.code + 1);
		}
	}
	puts("void kmovw(const Opmask& k, const Operand& op) { opVex(k, 0, op, T_L0 | T_0F | T_W0, 0x90); }");
	puts("void kmovq(const Opmask& k, const Operand& op) { opVex(k, 0, op, T_L0 | T_0F | T_W1, 0x90); }");
	puts("void kmovb(const Opmask& k, const Operand& op) { opVex(k, 0, op, T_L0 | T_0F | T_66 | T_W0, 0x90); }");
	puts("void kmovd(const Opmask& k, const Operand& op) { opVex(k, 0, op, T_L0 | T_0F | T_66 | T_W1, 0x90); }");

	puts("void kmovw(const Address& addr, const Opmask& k) { opVex(k, 0, addr, T_L0 | T_0F | T_W0, 0x91); }");
	puts("void kmovq(const Address& addr, const Opmask& k) { opVex(k, 0, addr, T_L0 | T_0F | T_W1, 0x91); }");
	puts("void kmovb(const Address& addr, const Opmask& k) { opVex(k, 0, addr, T_L0 | T_0F | T_66 | T_W0, 0x91); }");
	puts("void kmovd(const Address& addr, const Opmask& k) { opVex(k, 0, addr, T_L0 | T_0F | T_66 | T_W1, 0x91); }");

	puts("void kmovw(const Opmask& k, const Reg32& r) { opVex(k, 0, r, T_L0 | T_0F | T_W0, 0x92); }");
	puts("void kmovw(const Reg32& r, const Opmask& k) { opVex(r, 0, k, T_L0 | T_0F | T_W0, 0x93); }");
	puts("#ifdef XBYAK64");
	puts("void kmovq(const Opmask& k, const Reg64& r) { opVex(k, 0, r, T_L0 | T_0F | T_F2 | T_W1, 0x92); }");
	puts("void kmovq(const Reg64& r, const Opmask& k) { opVex(r, 0, k, T_L0 | T_0F | T_F2 | T_W1, 0x93); }");
	puts("#endif");
	puts("void kmovb(const Opmask& k, const Reg32& r) { opVex(k, 0, r, T_L0 | T_0F | T_66 | T_W0, 0x92); }");
	puts("void kmovb(const Reg32& r, const Opmask& k) { opVex(r, 0, k, T_L0 | T_0F | T_66 | T_W0, 0x93); }");
	puts("void kmovd(const Opmask& k, const Reg32& r) { opVex(k, 0, r, T_L0 | T_0F | T_F2 | T_W0, 0x92); }");
	puts("void kmovd(const Reg32& r, const Opmask& k) { opVex(r, 0, k, T_L0 | T_0F | T_F2 | T_W0, 0x93); }");
}

// vcmppd(k, x, op)
void putVcmp()
{
	const struct Tbl {
		uint8 code;
		const char *name;
		int type;
		bool hasIMM;
	} tbl[] = {
		{ 0xC2, "vcmppd", T_0F | T_MUST_EVEX | T_EW1 | T_SAE_Z | T_YMM | T_66 | T_N16 | T_N_VL, true },
		{ 0xC2, "vcmpps", T_0F | T_MUST_EVEX | T_EW0 | T_SAE_Z | T_YMM | T_N16 | T_N_VL, true },
		{ 0xC2, "vcmpsd", T_0F | T_MUST_EVEX | T_EW1 | T_SAE_Z | T_F2 | T_N8, true },
		{ 0xC2, "vcmpss", T_0F | T_MUST_EVEX | T_EW0 | T_SAE_Z | T_F3 | T_N4, true },

		{ 0x74, "vpcmpeqb", T_66 | T_0F | T_MUST_EVEX | T_YMM | T_N16 | T_N_VL, false },
		{ 0x75, "vpcmpeqw", T_66 | T_0F | T_MUST_EVEX | T_YMM | T_N16 | T_N_VL, false },
		{ 0x76, "vpcmpeqd", T_66 | T_0F | T_MUST_EVEX | T_YMM | T_B32 | T_N16 | T_N_VL, false },
		{ 0x29, "vpcmpeqq", T_66 | T_0F38 | T_MUST_EVEX | T_YMM | T_EW1 | T_B64 | T_N16 | T_N_VL, false },

		{ 0x64, "vpcmpgtb", T_66 | T_0F | T_MUST_EVEX | T_YMM | T_N16 | T_N_VL, false },
		{ 0x65, "vpcmpgtw", T_66 | T_0F | T_MUST_EVEX | T_YMM | T_N16 | T_N_VL, false },
		{ 0x66, "vpcmpgtd", T_66 | T_0F | T_MUST_EVEX | T_YMM | T_EW0 | T_B32 | T_N16 | T_N_VL, false },
		{ 0x37, "vpcmpgtq", T_66 | T_0F38 | T_MUST_EVEX | T_YMM | T_EW1 | T_B64 | T_N16 | T_N_VL, false },
	};
	for (size_t i = 0; i < NUM_OF_ARRAY(tbl); i++) {
		const Tbl *p = &tbl[i];
		std::string type = type2String(p->type);
		printf("void %s(const Opmask& k, const Xmm& x, const Operand& op%s) { opAVX_K_X_XM(k, x, op, %s, 0x%02X%s); }\n"
			, p->name, p->hasIMM ? ", uint8 imm" : "", type.c_str(), p->code, p->hasIMM ? ", imm" : "");
	}
}

// XM_X
void putX_XM()
{
	const struct Tbl {
		uint8 code;
		const char *name;
		int type;
	} tbl[] = {
		{ 0x6F, "vmovdqa32", T_66 | T_0F | T_MUST_EVEX | T_YMM | T_EW0 | T_ER_X | T_ER_Y | T_ER_Z },
		{ 0x6F, "vmovdqa64", T_66 | T_0F | T_MUST_EVEX | T_YMM | T_EW1 | T_ER_X | T_ER_Y | T_ER_Z },
		{ 0x6F, "vmovdqu8", T_F2 | T_0F | T_MUST_EVEX | T_YMM | T_EW0 | T_ER_X | T_ER_Y | T_ER_Z },
		{ 0x6F, "vmovdqu16", T_F2 | T_0F | T_MUST_EVEX | T_YMM | T_EW1 | T_ER_X | T_ER_Y | T_ER_Z },
		{ 0x6F, "vmovdqu32", T_F3 | T_0F | T_MUST_EVEX | T_YMM | T_EW0 | T_ER_X | T_ER_Y | T_ER_Z },
		{ 0x6F, "vmovdqu64", T_F3 | T_0F | T_MUST_EVEX | T_YMM | T_EW1 | T_ER_X | T_ER_Y | T_ER_Z },
	};
	for (size_t i = 0; i < NUM_OF_ARRAY(tbl); i++) {
		const Tbl *p = &tbl[i];
		std::string type = type2String(p->type);
		printf("void %s(const Xmm& x, const Operand& op) { opAVX_X_XM_IMM(x, op, %s, 0x%02X); }\n", p->name, type.c_str(), p->code);
	}
	puts("void vpabsq(const Xmm& x, const Operand& op) { opAVX_X_XM_IMM(x, op, T_66 | T_0F38 | T_MUST_EVEX | T_EW1 | T_B64 | T_YMM, 0x1F); }");
}

void putM_X()
{
	const struct Tbl {
		uint8 code;
		const char *name;
		int type;
	} tbl[] = {
		{ 0x7F, "vmovdqa32", T_66 | T_0F | T_MUST_EVEX | T_YMM | T_EW0 | T_ER_X | T_ER_Y | T_ER_Z },
		{ 0x7F, "vmovdqa64", T_66 | T_0F | T_MUST_EVEX | T_YMM | T_EW1 | T_ER_X | T_ER_Y | T_ER_Z },
		{ 0x7F, "vmovdqu8", T_F2 | T_0F | T_MUST_EVEX | T_YMM | T_EW0 | T_ER_X | T_ER_Y | T_ER_Z },
		{ 0x7F, "vmovdqu16", T_F2 | T_0F | T_MUST_EVEX | T_YMM | T_EW1 | T_ER_X | T_ER_Y | T_ER_Z },
		{ 0x7F, "vmovdqu32", T_F3 | T_0F | T_MUST_EVEX | T_YMM | T_EW0 | T_ER_X | T_ER_Y | T_ER_Z },
		{ 0x7F, "vmovdqu64", T_F3 | T_0F | T_MUST_EVEX | T_YMM | T_EW1 | T_ER_X | T_ER_Y | T_ER_Z },
	};
	for (size_t i = 0; i < NUM_OF_ARRAY(tbl); i++) {
		const Tbl *p = &tbl[i];
		std::string type = type2String(p->type);
		printf("void %s(const Address& addr, const Xmm& x) { opAVX_X_XM_IMM(x, addr, %s, 0x%02X); }\n", p->name, type.c_str(), p->code);
	}
}

void putX_X_XM_IMM()
{
	const struct Tbl {
		uint8 code;
		const char *name;
		int type;
		bool hasIMM;
	} tbl[] = {
		{ 0x03, "valignd", T_MUST_EVEX | T_66 | T_0F3A | T_EW0 | T_YMM | T_N16 | T_N_VL, true },
		{ 0x03, "valignq", T_MUST_EVEX | T_66 | T_0F3A | T_EW1 | T_YMM | T_N16 | T_N_VL, true },
		{ 0xDB, "vpandd", T_MUST_EVEX | T_YMM | T_66 | T_0F | T_EW0 | T_B32, false },
		{ 0xDB, "vpandq", T_MUST_EVEX | T_YMM | T_66 | T_0F | T_EW1 | T_B64, false },
		{ 0xDF, "vpandnd", T_MUST_EVEX | T_YMM | T_66 | T_0F | T_EW0 | T_B32, false },
		{ 0xDF, "vpandnq", T_MUST_EVEX | T_YMM | T_66 | T_0F | T_EW1 | T_B64, false },
		{ 0x3D, "vpmaxsq", T_66 | T_0F38 | T_MUST_EVEX | T_YMM | T_EW1 | T_B64, false },
		{ 0x3F, "vpmaxuq", T_66 | T_0F38 | T_MUST_EVEX | T_YMM | T_EW1 | T_B64, false },
		{ 0x39, "vpminsq", T_66 | T_0F38 | T_MUST_EVEX | T_YMM | T_EW1 | T_B64, false },
		{ 0x3B, "vpminuq", T_66 | T_0F38 | T_MUST_EVEX | T_YMM | T_EW1 | T_B64, false },
		{ 0xE2, "vpsraq", T_66 | T_0F | T_MUST_EVEX | T_YMM | T_EW1, false },
		{ 0x46, "vpsravq", T_66 | T_0F38 | T_MUST_EVEX | T_YMM | T_EW1 | T_B64, false },
		{ 0x11, "vpsravw", T_66 | T_0F38 | T_MUST_EVEX | T_YMM | T_EW1, false },
		{ 0x12, "vpsllvw", T_66 | T_0F38 | T_MUST_EVEX | T_YMM | T_EW1, false },
		{ 0x10, "vpsrlvw", T_66 | T_0F38 | T_MUST_EVEX | T_YMM | T_EW1, false },
		{ 0xEB, "vpord", T_66 | T_0F | T_MUST_EVEX | T_YMM | T_EW0 | T_B32, false },
		{ 0xEB, "vporq", T_66 | T_0F | T_MUST_EVEX | T_YMM | T_EW1 | T_B64, false },

		{ 0xEF, "vpxord", T_66 | T_0F | T_MUST_EVEX | T_YMM | T_EW0 | T_B32, false },
		{ 0xEF, "vpxorq", T_66 | T_0F | T_MUST_EVEX | T_YMM | T_EW1 | T_B64, false },

		{ 0x40, "vpmullq", T_66 | T_0F38 | T_MUST_EVEX | T_YMM | T_EW1 | T_B64, false },

		{ 0x8D, "vpermb", T_66 | T_0F38 | T_MUST_EVEX | T_YMM | T_EW0, false },
		{ 0x8D, "vpermw", T_66 | T_0F38 | T_MUST_EVEX | T_YMM | T_EW1, false },
	};
	for (size_t i = 0; i < NUM_OF_ARRAY(tbl); i++) {
		const Tbl *p = &tbl[i];
		std::string type = type2String(p->type);
		printf("void %s(const Xmm& x1, const Xmm& x2, const Operand& op%s) { opAVX_X_X_XM(x1, x2, op, %s, 0x%02X%s); }\n"
			, p->name, p->hasIMM ? ", uint8 imm" : "", type.c_str(), p->code, p->hasIMM ? ", imm" : "");
	}
}

void putShift()
{
	const struct Tbl {
		const char *name;
		uint8 code;
		int idx;
		int type;
	} tbl[] = {
		{ "vpsraq", 0x72, 4, T_0F | T_66 | T_YMM | T_MUST_EVEX |T_EW1 | T_B64 },
	};
	for (size_t i = 0; i < NUM_OF_ARRAY(tbl); i++) {
		const Tbl& p = tbl[i];
		std::string type = type2String(p.type);
		printf("void %s(const Xmm& x, const Operand& op, uint8 imm) { opAVX_X_X_XM(x.copyAndSetIdx(%d), x, op, %s, 0x%02X, imm); }\n", p.name, p.idx, type.c_str(), p.code);
	}
}

void putExtractInsert()
{
	{
		const struct Tbl {
			const char *name;
			uint8 code;
			int type;
			bool isZMM;
		} tbl[] = {
			{ "vextractf32x4", 0x19, T_66 | T_0F3A | T_MUST_EVEX | T_EW0 | T_YMM, false },
			{ "vextractf64x2", 0x19, T_66 | T_0F3A | T_MUST_EVEX | T_EW1 | T_YMM, false },
			{ "vextractf32x8", 0x1B, T_66 | T_0F3A | T_MUST_EVEX | T_EW0 | T_YMM, true },
			{ "vextractf64x4", 0x1B, T_66 | T_0F3A | T_MUST_EVEX | T_EW1 | T_YMM, true },

			{ "vextracti32x4", 0x39, T_66 | T_0F3A | T_MUST_EVEX | T_EW0 | T_YMM, false },
			{ "vextracti64x2", 0x39, T_66 | T_0F3A | T_MUST_EVEX | T_EW1 | T_YMM, false },
			{ "vextracti32x8", 0x3B, T_66 | T_0F3A | T_MUST_EVEX | T_EW0 | T_YMM, true },
			{ "vextracti64x4", 0x3B, T_66 | T_0F3A | T_MUST_EVEX | T_EW1 | T_YMM, true },
		};
		for (size_t i = 0; i < NUM_OF_ARRAY(tbl); i++) {
			const Tbl& p = tbl[i];
			std::string type = type2String(p.type);
			printf("void %s(const Operand& op, const %s& r, uint8 imm) { opAVX_X_X_XMcvt(r, true, cvtIdx0(r), op, op.isXMM(), Operand::YMM, %s, 0x%2X, imm); }\n", p.name, p.isZMM ? "Zmm" : "Ymm", type.c_str(), p.code);
		}
	}
	{
		const struct Tbl {
			const char *name;
			uint8 code;
			int type;
			bool isZMM;
		} tbl[] = {
			{ "vinsertf32x4", 0x18, T_66 | T_0F3A | T_MUST_EVEX | T_EW0 | T_YMM, false },
			{ "vinsertf64x2", 0x18, T_66 | T_0F3A | T_MUST_EVEX | T_EW1 | T_YMM, false },
			{ "vinsertf32x8", 0x1A, T_66 | T_0F3A | T_MUST_EVEX | T_EW0 | T_YMM, true },
			{ "vinsertf64x4", 0x1A, T_66 | T_0F3A | T_MUST_EVEX | T_EW1 | T_YMM, true },

			{ "vinserti32x4", 0x38, T_66 | T_0F3A | T_MUST_EVEX | T_EW0 | T_YMM, false },
			{ "vinserti64x2", 0x38, T_66 | T_0F3A | T_MUST_EVEX | T_EW1 | T_YMM, false },
			{ "vinserti32x8", 0x3A, T_66 | T_0F3A | T_MUST_EVEX | T_EW0 | T_YMM, true },
			{ "vinserti64x4", 0x3A, T_66 | T_0F3A | T_MUST_EVEX | T_EW1 | T_YMM, true },
		};
		for (size_t i = 0; i < NUM_OF_ARRAY(tbl); i++) {
			const Tbl& p = tbl[i];
			std::string type = type2String(p.type);
			const char *x = p.isZMM ? "Zmm" : "Ymm";
			printf("void %s(const %s& r1, const %s& r2, const Operand& op, uint8 imm) { opAVX_X_X_XMcvt(r1, false, r2, op, op.isXMM(), Operand::YMM, %s, 0x%2X, imm); }\n", p.name, x, x, type.c_str(), p.code);
		}
	}
}

void putBroadcast()
{
	puts("void vbroadcastf32x2(const Ymm& y, const Operand& op) { opAVX_X_XM_IMM(y, op, T_66 | T_0F38 | T_YMM | T_MUST_EVEX | T_EW0 | T_N8, 0x19); }");
	puts("void vbroadcastf32x4(const Ymm& y, const Address& addr) { opAVX_X_XM_IMM(y, addr, T_66 | T_0F38 | T_YMM | T_MUST_EVEX | T_EW0 | T_N16, 0x1A); }");
	puts("void vbroadcastf64x2(const Ymm& y, const Address& addr) { opAVX_X_XM_IMM(y, addr, T_66 | T_0F38 | T_YMM | T_MUST_EVEX | T_EW1 | T_N16, 0x1A); }");
	puts("void vbroadcastf64x4(const Zmm& y, const Address& addr) { opAVX_X_XM_IMM(y, addr, T_66 | T_0F38 | T_YMM | T_MUST_EVEX | T_EW1 | T_N32, 0x1B); }");
	{
		const struct Tbl {
			uint8 code;
			const char *name;
			int type;
			int reg;
		} tbl[] = {
			{ 0x7A, "vpbroadcastb", T_66 | T_0F38 | T_YMM | T_MUST_EVEX | T_EW0 | T_N4, 8 },
			{ 0x7B, "vpbroadcastw", T_66 | T_0F38 | T_YMM | T_MUST_EVEX | T_EW0 | T_N4, 16 },
			{ 0x7C, "vpbroadcastd", T_66 | T_0F38 | T_YMM | T_MUST_EVEX | T_EW0 | T_N4, 32 },
			{ 0x7C, "vpbroadcastq", T_66 | T_0F38 | T_YMM | T_MUST_EVEX | T_EW1 | T_N8, 64},
		};
		for (size_t i = 0; i < NUM_OF_ARRAY(tbl); i++) {
			const Tbl& p = tbl[i];
			std::string type = type2String(p.type);
			if (p.reg == 64) puts("#ifdef XBYAK64");
			printf("void %s(const Xmm& x, const Reg%d& r) { opVex(x, &cvtIdx0(x), r, %s, 0x%02X); }\n", p.name, p.reg, type.c_str(), p.code);
			if (p.reg == 64) puts("#endif");
		}
	}
	puts("void vbroadcasti32x2(const Xmm& x, const Operand& op) { opAVX_X_XM_IMM(x, op, T_66 | T_0F38 | T_YMM | T_MUST_EVEX | T_EW0 | T_N8, 0x59); }");
	puts("void vbroadcasti32x4(const Ymm& y, const Operand& op) { opAVX_X_XM_IMM(y, op, T_66 | T_0F38 | T_YMM | T_MUST_EVEX | T_EW0 | T_N16, 0x5A); }");
	puts("void vbroadcasti64x2(const Ymm& y, const Operand& op) { opAVX_X_XM_IMM(y, op, T_66 | T_0F38 | T_YMM | T_MUST_EVEX | T_EW1 | T_N16, 0x5A); }");
	puts("void vbroadcasti32x8(const Zmm& z, const Operand& op) { opAVX_X_XM_IMM(z, op, T_66 | T_0F38 | T_YMM | T_MUST_EVEX | T_EW0 | T_N32, 0x5B); }");
	puts("void vbroadcasti64x4(const Zmm& z, const Operand& op) { opAVX_X_XM_IMM(z, op, T_66 | T_0F38 | T_YMM | T_MUST_EVEX | T_EW1 | T_N32, 0x5B); }");
}

int main()
{
	puts("#ifndef XBYAK_DISABLE_AVX512");
	putOpmask();
	putVcmp();
	putX_XM();
	putM_X();
	putX_X_XM_IMM();
	putShift();
	putExtractInsert();
#ifdef XBYAK64
	putBroadcast();
#endif
	puts("#endif");
}
