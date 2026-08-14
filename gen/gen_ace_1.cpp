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

void putBsr()
{
	// bsr0 is passed through as a real operand: xed64 requires it visible in the disassembly.
	puts("void bsrinit(const Bsr& b) { vex(b, b, 0, T_F2|T_0F38|T_W1, 0x49); setModRM(3, b.getIdx(), 0); }");

	// T_N1 (no T_N_VL): memory-form disp8N is unscaled, per xed64 decode.
	puts("void bsrmovf(const Bsr& b, const Zmm& z1, const Operand& op) { opVex(b, &z1, op, T_MUST_EVEX|T_MAP6|T_EW1|T_N1, 0x95); }");

	// EVEX.W alone selects load (W1) vs. store (W0); same map/prefix/opcode otherwise.
	const struct Tbl {
		const char *name;
		uint64_t prefix;
	} tbl[] = {
		{ "bsrmovh", T_F2 },
		{ "bsrmovl", T_F3 },
	};
	for (size_t i = 0; i < NUM_OF_ARRAY(tbl); i++) {
		const Tbl& t = tbl[i];
		std::string load = type2String(T_MUST_EVEX|T_MAP6|T_EW1|T_N1|t.prefix);
		std::string store = type2String(T_MUST_EVEX|T_MAP6|T_W0|T_N1|t.prefix);
		printf("void %s(const Bsr& b, const Operand& op) { opVex(b, 0, op, %s, 0x95); }\n", t.name, load.c_str());
		printf("void %s(const Operand& op, const Bsr& b) { opVex(b, 0, op, %s, 0x95); }\n", t.name, store.c_str());
	}
}

void putTileMovCol()
{
	// Reg-only, one-directional (zmm column -> tile); no "extract" sibling.
	const struct Tbl {
		uint64_t type;
		uint8_t code;
		bool imm;
	} tbl[] = {
		{ T_66|T_0F3A|T_MUST_EVEX|T_EW1, 0x2F, true },
		{ T_66|T_0F38|T_MUST_EVEX|T_EW1, 0x4B, false },
	};
	for (size_t i = 0; i < NUM_OF_ARRAY(tbl); i++) {
		const Tbl& t = tbl[i];
		std::string s = type2String(t.type);
		if (t.imm) {
			printf("void tilemovcol(const Tmm& t1, const Zmm& z2, uint8_t imm) { opVex(t1, 0, z2, %s, 0x%02X, imm); }\n", s.c_str(), t.code);
		} else {
			printf("void tilemovcol(const Tmm& t1, const Zmm& z2, const Reg32& r) { opVex(t1, &r, z2, %s, 0x%02X); }\n", s.c_str(), t.code);
		}
	}
}

void putTop()
{
	// Reg-only; vvvv/rm swap matches tdpbssd. TOP4MX* does not expose bsr0 as an operand (xed64
	// decode shows only tmm1/zmm2/zmm3/imm8), unlike the BSR-family mnemonics above.
	const struct Tbl {
		const char *name;
		uint64_t type;
		uint8_t code;
		bool imm;
	} tbl[] = {
		{ "top2bf16ps", T_F3|T_0F38|T_MUST_EVEX|T_W0, 0x5C, false },
		{ "top4bssd",   T_F2|T_0F38|T_MUST_EVEX|T_W0, 0x5E, false },
		{ "top4bsud",   T_F3|T_0F38|T_MUST_EVEX|T_W0, 0x5E, false },
		{ "top4busd",   T_66|T_0F38|T_MUST_EVEX|T_W0, 0x5E, false },
		{ "top4buud",   T_0F38|T_MUST_EVEX|T_W0,      0x5E, false },

		{ "top4mxbf8ps",  T_0F3A|T_MUST_EVEX|T_W0,      0x8D, true },
		{ "top4mxbhf8ps", T_F2|T_0F3A|T_MUST_EVEX|T_W0, 0x8D, true },
		{ "top4mxhbf8ps", T_F3|T_0F3A|T_MUST_EVEX|T_W0, 0x8D, true },
		{ "top4mxhf8ps",  T_66|T_0F3A|T_MUST_EVEX|T_W0, 0x8D, true },
		{ "top4mxbssps",  T_F2|T_0F3A|T_MUST_EVEX|T_W0, 0x8F, true },
	};
	for (size_t i = 0; i < NUM_OF_ARRAY(tbl); i++) {
		const Tbl& t = tbl[i];
		std::string s = type2String(t.type);
		if (t.imm) {
			printf("void %s(const Tmm& t1, const Zmm& z2, const Zmm& z3, uint8_t imm) { opVex(t1, &z3, z2, %s, 0x%02X, imm); }\n", t.name, s.c_str(), t.code);
		} else {
			printf("void %s(const Tmm& t1, const Zmm& z2, const Zmm& z3) { opVex(t1, &z3, z2, %s, 0x%02X); }\n", t.name, s.c_str(), t.code);
		}
	}
}

void putFp8()
{
	{
		const struct Tbl {
			const char *name;
			uint64_t prefix;
			uint8_t code;
		} tbl[] = {
			{ "vcvtps2bf8",    T_F3, 0x39 },
			{ "vcvtps2bf8s",   T_F3, 0x3B },
			{ "vcvtps2hf8",    T_F3, 0x38 },
			{ "vcvtps2hf8s",   T_F3, 0x3A },
			{ "vcvtrops2hf8",  T_66, 0x38 },
			{ "vcvtrops2hf8s", T_66, 0x3A },
		};
		for (size_t i = 0; i < NUM_OF_ARRAY(tbl); i++) {
			const Tbl& p = tbl[i];
			std::string s = type2String(T_MUST_EVEX | T_MAP5 | T_W0 | T_YMM | T_B32 | p.prefix);
			printf("void %s(const Xmm& x, const Operand& op) { opCvt5(x, op, %s, 0x%02X); }\n", p.name, s.c_str(), p.code);
		}
	}

	// dst is fixed XMM regardless of VL; only bias/src grow together. No existing helper shape
	// fits (they all let dst track the other operands' width), so the guard is hand-written here.
	{
		const struct Tbl {
			const char *name;
			uint8_t code;
		} tbl[] = {
			{ "vcvtbiasps2bf8",  0x39 },
			{ "vcvtbiasps2bf8s", 0x3B },
			{ "vcvtbiasps2hf8",  0x38 },
			{ "vcvtbiasps2hf8s", 0x3A },
		};
		std::string s = type2String(T_MUST_EVEX | T_MAP5 | T_W0 | T_YMM | T_B32);
		for (size_t i = 0; i < NUM_OF_ARRAY(tbl); i++) {
			const Tbl& p = tbl[i];
			printf("void %s(const Xmm& x1, const Xmm& x2, const Operand& op) "
				"{ if (!(x1.isXMM() && (op.isMEM() || op.getBit() == x2.getBit()))) XBYAK_THROW(ERR_BAD_COMBINATION) "
				"opVex(x1, &x2, op, %s, 0x%02X); }\n", p.name, s.c_str(), p.code);
		}
	}

	{
		const struct Tbl {
			const char *name;
			uint64_t w;
		} tbl[] = {
			{ "vcvtbf82ps", T_EW1 },
			{ "vcvthf82ps", T_W0 },
		};
		for (size_t i = 0; i < NUM_OF_ARRAY(tbl); i++) {
			const Tbl& p = tbl[i];
			std::string s = type2String(T_MUST_EVEX | T_MAP5 | T_YMM | T_N4 | T_N_VL | p.w);
			printf("void %s(const Xmm& x, const Operand& op) "
				"{ if (!op.isXMM() && !op.isMEM()) XBYAK_THROW(ERR_BAD_MEM_SIZE) "
				"opVex(x, 0, op, %s, 0x36); }\n", p.name, s.c_str());
		}
	}

	// dst/src pairing is (xmm,xmm), (ymm,xmm), (zmm,ymm) -- not a fixed ratio the standard
	// opCvt helpers assume, so each dst kind gets its own explicit src-kind check.
	{
		std::string s = type2String(T_MUST_EVEX | T_MAP5 | T_YMM | T_N8 | T_N_VL | T_W0);
		printf("void vcvtbf42hf8(const Xmm& x, const Operand& op) "
			"{ if (x.isXMM()) { if (!(op.isXMM() || op.isMEM())) XBYAK_THROW(ERR_BAD_COMBINATION) } "
			"else if (x.isYMM()) { if (!(op.isXMM() || op.isMEM())) XBYAK_THROW(ERR_BAD_COMBINATION) } "
			"else if (x.isZMM()) { if (!(op.isYMM() || op.isMEM())) XBYAK_THROW(ERR_BAD_COMBINATION) } "
			"else { XBYAK_THROW(ERR_BAD_COMBINATION) } "
			"opVex(x, 0, op, %s, 0x37); }\n", s.c_str());
	}

	{
		const struct Tbl {
			const char *name;
			uint64_t w;
		} tbl[] = {
			{ "vcvtbf62hf8", T_EW1 },
			{ "vcvthf62hf8", T_W0 },
		};
		for (size_t i = 0; i < NUM_OF_ARRAY(tbl); i++) {
			const Tbl& p = tbl[i];
			std::string s = type2String(T_MUST_EVEX | T_MAP5 | T_66 | T_YMM | p.w);
			printf("void %s(const Xmm& x, const Xmm& op) { opVex(x, 0, op, %s, 0x37); }\n", p.name, s.c_str());
		}
	}

	// ModRM.reg carries the source and ModRM.rm the destination here -- reversed from the plain
	// RM shape used by VCVTBF62HF8/VCVTHF62HF8 above, hence opVex(op, 0, x, ...) with x and op
	// swapped relative to that call.
	{
		const struct Tbl {
			const char *name;
			uint64_t w;
			uint8_t code;
		} tbl[] = {
			{ "vcvtbf82bf6s", T_EW1, 0x3E },
			{ "vcvthf82hf6s", T_W0,  0x3C },
		};
		for (size_t i = 0; i < NUM_OF_ARRAY(tbl); i++) {
			const Tbl& p = tbl[i];
			std::string s = type2String(T_MUST_EVEX | T_MAP5 | T_F3 | T_YMM | p.w);
			printf("void %s(const Xmm& x, const Xmm& op) { opVex(op, 0, x, %s, 0x%02X); }\n", p.name, s.c_str(), p.code);
		}
	}

	// opVmov mode=true (dst grows with src, unlike vpmovssdb below); T_M_K intentionally
	// omitted here since this family has no masked-memory-destination form.
	{
		const struct Tbl {
			const char *name;
			uint64_t w;
		} tbl[] = {
			{ "vcvtbf82bf4s", T_EW1 },
			{ "vcvthf82bf4s", T_W0 },
		};
		for (size_t i = 0; i < NUM_OF_ARRAY(tbl); i++) {
			const Tbl& p = tbl[i];
			std::string s = type2String(T_MUST_EVEX | T_MAP5 | T_F3 | T_YMM | T_N8 | T_N_VL | p.w);
			printf("void %s(const Operand& op, const Xmm& x) { opVmov(op, x, %s, 0x3D, true); }\n", p.name, s.c_str());
		}
	}

	{
		std::string s = type2String(T_MUST_EVEX | T_0F3A | T_YMM | T_W0);
		printf("void vunpackb(const Xmm& x, const Operand& op, uint8_t imm) { opAVX_X_XM_IMM(x, op, %s, 0x3D, imm); }\n", s.c_str());
	}

	{
		std::string s = type2String(T_MUST_EVEX | T_F3 | T_0F38 | T_YMM | T_W0 | T_N4 | T_N_VL | T_M_K);
		printf("void vpmovssdb(const Operand& op, const Xmm& x) { opVmov(op, x, %s, 0x41, false); }\n", s.c_str());
	}
}

int main()
{
	putBsr();
	putTileMovCol();
	putTop();
	putFp8();
}
