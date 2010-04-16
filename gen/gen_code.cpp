#define XBYAK_DONT_READ_LIST
#include <stdio.h>
#include <string.h>
#include "xbyak.h"
#define NUM_OF_ARRAY(x) (sizeof(x) / sizeof(x[0]))

using namespace Xbyak;

void put()
{
	const int NO = CodeGenerator::NONE;
	{
		char buf[16];
		unsigned int v = VERSION;
		if (v & 0xF) {
			sprintf(buf, "%d.%02X%x", v >> 12, (v >> 4) & 0xFF, v & 0xF);
		} else {
			sprintf(buf, "%d.%02X", v >> 12, (v >> 4) & 0xFF);
		}
		printf("const char *getVersionString() const { return \"%s\"; }\n", buf);
	}
	const int B = 1 << 0;
	const int W = 1 << 1;
	const int D = 1 << 2;
	const int Q = 1 << 3;
	{
		const struct Tbl {
			uint8 code;
			const char *name;
		} tbl[] = {
			// MMX
			{ B01101011, "packssdw" },
			{ B01100011, "packsswb" },
			{ B01100111, "packuswb" },

			{ B11011011, "pand" },
			{ B11011111, "pandn" },

			{ B11110101, "pmaddwd" },
			{ B11100100, "pmulhuw" },
			{ B11100101, "pmulhw" },
			{ B11010101, "pmullw" },

			{ B11101011, "por" },

			{ B01101000, "punpckhbw" },
			{ B01101001, "punpckhwd" },
			{ B01101010, "punpckhdq" },

			{ B01100000, "punpcklbw" },
			{ B01100001, "punpcklwd" },
			{ B01100010, "punpckldq" },

			{ B11101111, "pxor" },

			// MMX2
			{ B11100000, "pavgb" },
			{ B11100011, "pavgw" },
			{ B11101110, "pmaxsw" },
			{ B11011110, "pmaxub" },
			{ B11101010, "pminsw" },
			{ B11011010, "pminub" },
			{ B11110110, "psadbw" },
			//
			{ B11010100, "paddq" },
			{ B11110100, "pmuludq" },
			{ B11111011, "psubq" },
		};
		for (int i = 0; i < NUM_OF_ARRAY(tbl); i++) {
			const Tbl *p = &tbl[i];
			printf("void %s(const Mmx& mmx, const Operand& op) { opMMX(mmx, op, 0x%02X); }\n"
				, p->name, p->code);
		}
	}

	{
		const struct Tbl {
			uint8 code;
			int mode;
			const char *name;
		} tbl[] = {
			{ B11111100, B|W|D, "padd" },
			{ B11101100, B|W  , "padds" },
			{ B11011100, B|W  , "paddus" },
			{ B01110100, B|W|D, "pcmpeq" },
			{ B01100100, B|W|D, "pcmpgt" },
			{ B11110000, W|D|Q, "psll" },
			{ B11100000, W|D  , "psra" },
			{ B11010000, W|D|Q, "psrl" },
			{ B11111000, B|W|D, "psub" },
			{ B11101000, B|W  , "psubs" },
			{ B11011000, B|W  , "psubus" },
		};
		for (int i = 0; i < NUM_OF_ARRAY(tbl); i++) {
			const Tbl *p = &tbl[i];
			static const char modTbl[][4] = {
				"b", "w", "d", "q"
			};
			for (int j = 0; j < 4; j++) {
				// B(0), W(1), D(2), Q(3)
				if (!(p->mode & (1 << j))) continue;
				printf("void %s%s(const Mmx& mmx, const Operand& op) { opMMX(mmx, op, 0x%02X); }\n"
					, p->name, modTbl[j]
					, p->code | j
				);
			}
		}
	}

	{
		const struct Tbl {
			uint8 code;
			int ext;
			int mode;
			const char *name;
		} tbl[] = {
			{ B01110000, 6, W|D|Q, "psll" },
			{ B01110000, 4, W|D  , "psra" },
			{ B01110000, 2, W|D|Q, "psrl" },
		};
		for (int i = 0; i < NUM_OF_ARRAY(tbl); i++) {
			const Tbl *p = &tbl[i];
			static const char modTbl[][4] = {
				"b", "w", "d", "q"
			};
			for (int j = 0; j < 4; j++) {
				// B(0), W(1), D(2), Q(3)
				if (!(p->mode & (1 << j))) continue;
				printf("void %s%s(const Mmx& mmx, int imm8) { opMMX_IMM(mmx, imm8, 0x%02X, %d); }\n"
					, p->name, modTbl[j]
					, p->code | j
					, p->ext
				);
			}
		}
		printf("void pslldq(const Xmm& xmm, int imm8) { opMMX_IMM(xmm, imm8, 0x%02X, %d); }\n", B01110011, 7);
		printf("void psrldq(const Xmm& xmm, int imm8) { opMMX_IMM(xmm, imm8, 0x%02X, %d); }\n", B01110011, 3);
	}

	{
		const struct Tbl {
			uint8 code;
			uint8 pref;
			const char *name;
		} tbl[] = {
			{ B01110000, 0, "pshufw" },
			{ B01110000, 0xF2, "pshuflw" },
			{ B01110000, 0xF3, "pshufhw" },
			{ B01110000, 0x66, "pshufd" },
		};
		for (int i = 0; i < NUM_OF_ARRAY(tbl); i++) {
			const Tbl *p = &tbl[i];
			printf("void %s(const Mmx& mmx, const Operand& op, uint8 imm8) { opMMX(mmx, op, 0x%02X, 0x%02X, imm8); }\n" , p->name, p->code, p->pref);
		}
	}
	{
		const struct MmxTbl6 {
			uint8 code; // for (reg, reg/[mem])
			uint8 code2; // for ([mem], reg)
			int pref;
			const char *name;
		} mmxTbl6[] = {
			{ B01101111, B01111111, 0x66, "movdqa" },
			{ B01101111, B01111111, 0xF3, "movdqu" },
			// SSE2
			{ B00101000, B00101001, NO, "movaps" },
			{ B00010000, B00010001, 0xF3, "movss" },
			{ B00010000, B00010001, NO, "movups" },
			{ B00101000, B00101001, 0x66, "movapd" },
			{ B00010000, B00010001, 0xF2, "movsd" },
			{ B00010000, B00010001, 0x66, "movupd" },
		};
		for (int i = 0; i < NUM_OF_ARRAY(mmxTbl6); i++) {
			const MmxTbl6 *p = &mmxTbl6[i];
			printf("void %s(const Xmm& xmm, const Operand& op) { opMMX(xmm, op, 0x%02X, 0x%02X); }\n" , p->name, p->code, p->pref);
			printf("void %s(const Address& addr, const Xmm& xmm) { ", p->name);
			if (p->pref != NO) printf("db(0x%02X); ", p->pref);
			printf("opModM(addr, xmm, 0x0F, 0x%02X); }\n" , p->code2);
		}
	}
	{
		enum {
			PS = 1 << 0,
			SS = 1 << 1,
			PD = 1 << 2,
			SD = 1 << 3
		};
		const struct {
			int code;
			const char *name;
		} sufTbl[] = {
			{ NO, "ps" },
			{ 0xF3, "ss" },
			{ 0x66, "pd" },
			{ 0xF2, "sd" },
		};
		const struct Tbl {
			uint8 code;
			int mode;
			const char *name;
			bool hasImm;
		} tbl[] = {
			{ B01011000, PS|SS|PD|SD, "add" },
			{ B01010101, PS|PD      , "andn" },
			{ B01010100, PS|PD      , "and" },
			{ B11000010, PS|SS|PD|SD, "cmp", true },
			{ B01011110, PS|SS|PD|SD, "div" },
			{ B01011111, PS|SS|PD|SD, "max" },
			{ B01011101, PS|SS|PD|SD, "min" },
			{ B01011001, PS|SS|PD|SD, "mul" },
			{ B01010110, PS|PD      , "or" },
			{ B01010011, PS|SS      , "rcp" },
			{ B01010010, PS|SS      , "rsqrt" },
			{ B11000110, PS|PD      , "shuf", true },
			{ B01010001, PS|SS|PD|SD, "sqrt" },
			{ B01011100, PS|SS|PD|SD, "sub" },
			{ B00010101, PS|PD      , "unpckh" },
			{ B00010100, PS|PD      , "unpckl" },
			{ B01010111, PS|PD      , "xor" },
			//
		};
		for (int i = 0; i < NUM_OF_ARRAY(tbl); i++) {
			const Tbl *p = &tbl[i];
			for (int j = 0; j < NUM_OF_ARRAY(sufTbl); j++) {
				if (!(p->mode & (1 << j))) continue;
				if (p->hasImm) {
					// don't change uint8 to int because NO is not in byte
					printf("void %s%s(const Xmm& xmm, const Operand& op, uint8 imm8) { opGen(xmm, op, 0x%2X, 0x%02X, isXMM_XMMorMEM, imm8); }\n", p->name, sufTbl[j].name, p->code, sufTbl[j].code);
				} else {
					printf("void %s%s(const Xmm& xmm, const Operand& op) { opGen(xmm, op, 0x%2X, 0x%02X, isXMM_XMMorMEM); }\n", p->name, sufTbl[j].name, p->code, sufTbl[j].code);
				}
			}
		}
	}
	{
		// (XMM, XMM)
		const struct Tbl {
			uint8 code;
			uint8 pref;
			const char *name;
		} tbl[] = {
			{ B11110111, 0x66, "maskmovdqu" },
			{ B00010010, 0   , "movhlps" },
			{ B00010110, 0   , "movlhps" },
		};
		for (int i = 0; i < NUM_OF_ARRAY(tbl); i++) {
			const Tbl *p = &tbl[i];
			printf("void %s(const Xmm& reg1, const Xmm& reg2) { ", p->name);
			if (p->pref) printf("db(0x%02X); ", p->pref);
			printf(" opModR(reg1, reg2, 0x0F, 0x%02X); }\n", p->code);
		}
	}
	{
		// (XMM, XMM|MEM)
		const struct Tbl {
			uint8 code;
			int pref;
			const char *name;
		} tbl[] = {
			{ B01101101, 0x66, "punpckhqdq" },
			{ B01101100, 0x66, "punpcklqdq" },

			{ B00101111, NO  , "comiss" },
			{ B00101110, NO  , "ucomiss" },
			{ B00101111, 0x66, "comisd" },
			{ B00101110, 0x66, "ucomisd" },

			{ B01011010, 0x66, "cvtpd2ps" },
			{ B01011010, NO  , "cvtps2pd" },
			{ B01011010, 0xF2, "cvtsd2ss" },
			{ B01011010, 0xF3, "cvtss2sd" },
			{ B11100110, 0xF2, "cvtpd2dq" },
			{ B11100110, 0x66, "cvttpd2dq" },
			{ B11100110, 0xF3, "cvtdq2pd" },
			{ B01011011, 0x66, "cvtps2dq" },
			{ B01011011, 0xF3, "cvttps2dq" },
			{ B01011011, NO  , "cvtdq2ps" },

			// SSE3
			{ B11010000, 0x66, "addsubpd" },
			{ B11010000, 0xF2, "addsubps" },
			{ B01111100, 0x66, "haddpd" },
			{ B01111100, 0xF2, "haddps" },
			{ B01111101, 0x66, "hsubpd" },
			{ B01111101, 0xF2, "hsubps" },

			{ B00010010, 0xF2, "movddup" },
			{ B00010110, 0xF3, "movshdup" },
			{ B00010010, 0xF3, "movsldup" },
		};
		for (int i = 0; i < NUM_OF_ARRAY(tbl); i++) {
			const Tbl *p = &tbl[i];
			printf("void %s(const Xmm& xmm, const Operand& op) { opGen(xmm, op, 0x%02X, 0x%02X, isXMM_XMMorMEM); }\n", p->name, p->code, p->pref);
		}
	}

	{
		// special type
		const struct Tbl {
			uint8 code;
			int pref;
			const char *name;
			const char *cond;
		} tbl[] = {
			{ B00101010, NO  , "cvtpi2ps",  "isXMM_MMXorMEM" },
			{ B00101101, NO  , "cvtps2pi",  "isMMX_XMMorMEM" },
			{ B00101010, 0xF3, "cvtsi2ss",  "isXMM_REG32orMEM" },
			{ B00101101, 0xF3, "cvtss2si",  "isREG32_XMMorMEM" },
			{ B00101100, NO  , "cvttps2pi", "isMMX_XMMorMEM" },
			{ B00101100, 0xF3, "cvttss2si", "isREG32_XMMorMEM" },
			{ B00101010, 0x66, "cvtpi2pd",  "isXMM_MMXorMEM" },
			{ B00101101, 0x66, "cvtpd2pi",  "isMMX_XMMorMEM" },
			{ B00101010, 0xF2, "cvtsi2sd",  "isXMM_REG32orMEM" },
			{ B00101101, 0xF2, "cvtsd2si",  "isREG32_XMMorMEM" },
			{ B00101100, 0x66, "cvttpd2pi", "isMMX_XMMorMEM" },
			{ B00101100, 0xF2, "cvttsd2si", "isREG32_XMMorMEM" },
		};
		for (int i = 0; i < NUM_OF_ARRAY(tbl); i++) {
			const Tbl *p = &tbl[i];
			printf("void %s(const Operand& reg, const Operand& op) { opGen(reg, op, 0x%02X, 0x%02X, %s); }\n", p->name, p->code, p->pref, p->cond);
		}
	}
	{
		// prefetch
		const struct Tbl {
			int ext;
			const char *name;
		} tbl[] = {
			{ 1, "t0" },
			{ 2, "t1" },
			{ 3, "t2" },
			{ 0, "nta" },
		};
		for (int i = 0; i < NUM_OF_ARRAY(tbl); i++) {
			const Tbl *p = &tbl[i];
			printf("void prefetch%s(const Address& addr) { opModM(addr, Reg32(%d), 0x0F, B00011000); }\n", p->name, p->ext);
		}
	}
	{
		const struct Tbl {
			uint8 code;
			int pref;
			const char *name;
		} tbl[] = {
			{ B00010110, NO,   "movhps" },
			{ B00010010, NO,   "movlps" },
			{ B00010110, 0x66, "movhpd" },
			{ B00010010, 0x66, "movlpd" },
		};
		for (int i = 0; i < NUM_OF_ARRAY(tbl); i++) {
			const Tbl *p = &tbl[i];
			printf("void %s(const Operand& op1, const Operand& op2) { opMovXMM(op1, op2, 0x%02X, 0x%02X); }\n", p->name, p->code, p->pref);
		}
	}
	{
		// cmov
		const struct Tbl {
			uint8 ext;
			const char *name;
		} tbl[] = {
			{ 0, "o" },
			{ 1, "no" },
			{ 2, "b" },
			{ 2, "nae" },
			{ 3, "nb" },
			{ 3, "ae" },
			{ 4, "e" },
			{ 4, "z" },
			{ 5, "ne" },
			{ 5, "nz" },
			{ 6, "be" },
			{ 6, "na" },
			{ 7, "nbe" },
			{ 7, "a" },
			{ 8, "s" },
			{ 9, "ns" },
			{ 10, "p" },
			{ 10, "pe" },
			{ 11, "np" },
			{ 11, "po" },
			{ 12, "l" },
			{ 12, "nge" },
			{ 13, "nl" },
			{ 13, "ge" },
			{ 14, "le" },
			{ 14, "ng" },
			{ 15, "nle" },
			{ 15, "g" },
		};
		for (int i = 0; i < NUM_OF_ARRAY(tbl); i++) {
			const Tbl *p = &tbl[i];
			printf("void cmov%s(const Reg32e& reg, const Operand& op) { opModRM(reg, op, op.isREG(i32e), op.isMEM(), 0x0F, B01000000 | %d); }\n", p->name, p->ext);
			printf("void j%s(const char *label, LabelType type = T_AUTO) { opJmp(label, type, 0x%02X, 0x%02X, 0x%02X); }\n", p->name, p->ext | B01110000, p->ext | B10000000, 0x0F);
			printf("void set%s(const Operand& op) { opR_ModM(op, 8, 3, 0, 0x0F, B10010000 | %d); }\n", p->name, p->ext);
		}
	}
	////////////////////////////////////////////////////////////////
	{
		const struct Tbl {
			const char *name;
			uint8 code1;
			uint8 code2;
			uint8 code3;
		} tbl[] = {
			// only 64-bit mode(from)
			{ "cdqe", B01001000, B10011000 },
			{ "@@@" }, /// here
			// only 32-bit mode(from)
			{ "aaa", B00110111 },
			{ "aad", B11010101, B00001010 },
			{ "aam", B11010100, B00001010 },
			{ "aas", B00111111 },
			{ "daa", B00100111 },
			{ "das", B00101111 },
			{ "popad", B01100001 },
			{ "popfd", B10011101 },
			{ "pusha", B01100000 },
			{ "pushad", B01100000 },
			{ "pushfd", B10011100 },
			{ "popa", B01100001 },
			{ "@@@" }, /// here

			{ "cbw", 0x66, B10011000 },
			{ "cdq", B10011001 },
			{ "clc", B11111000 },
			{ "cld", B11111100 },
			{ "cli", B11111010 },
			{ "cmc", B11110101 },

			{ "cpuid", 0x0F, B10100010 },
			{ "cwd", 0x66, B10011001 },
			{ "cwde", B10011000 },

			{ "lahf", B10011111 },
			{ "lock", B11110000 },
			{ "nop", B10010000 },

			{ "sahf", B10011110 },
			{ "stc", B11111001 },
			{ "std", B11111101 },
			{ "sti", B11111011 },

			{ "emms", 0x0F, B01110111 },
			{ "pause", 0xF3, B10010000 },
			{ "sfence", 0x0F, B10101110, B11111000 },
			{ "lfence", 0x0F, B10101110, B11101000 },
			{ "mfence", 0x0F, B10101110, B11110000 },
			{ "monitor", 0x0F, B00000001, B11001000 },
			{ "mwait", 0x0F, B00000001, B11001001 },

			{ "rdmsr", 0x0F, B00110010 },
			{ "rdpmc", 0x0F, B00110011 },
			{ "rdtsc", 0x0F, B00110001 },
			{ "wait", B10011011 },
			{ "wbinvd", 0x0F, B00001001 },
			{ "wrmsr", 0x0F, B00110000 },
			{ "xlatb", 0xD7 },

			{ "popf", B10011101 },
			{ "pushf", B10011100 },

			// FPU
			{ "f2xm1", 0xD9, 0xF0 },
			{ "fabs", 0xD9, 0xE1 },
			{ "faddp", 0xDE, 0xC1 },
			{ "fchs", 0xD9, 0xE0 },

			{ "fcom", 0xD8, 0xD1 },
			{ "fcomp", 0xD8, 0xD9 },
			{ "fcompp", 0xDE, 0xD9 },
			{ "fcos", 0xD9, 0xFF },
			{ "fdecstp", 0xD9, 0xF6 },
			{ "fdivp", 0xDE, 0xF9 },
			{ "fdivrp", 0xDE, 0xF1 },
			{ "fincstp", 0xD9, 0xF7 },
			{ "fld1", 0xD9, 0xE8 },
			{ "fldl2t", 0xD9, 0xE9 },
			{ "fldl2e", 0xD9, 0xEA },
			{ "fldpi", 0xD9, 0xEB },
			{ "fldlg2", 0xD9, 0xEC },
			{ "fldln2", 0xD9, 0xED },
			{ "fldz", 0xD9, 0xEE },
			{ "fmulp", 0xDE, 0xC9 },
			{ "fnop", 0xD9, 0xD0 },
			{ "fpatan", 0xD9, 0xF3 },
			{ "fprem", 0xD9, 0xF8 },
			{ "fprem1", 0xD9, 0xF5 },
			{ "fptan", 0xD9, 0xF2 },
			{ "frndint", 0xD9, 0xFC },
			{ "fscale", 0xD9, 0xFD },
			{ "fsin", 0xD9, 0xFE },
			{ "fsincos", 0xD9, 0xFB },
			{ "fsqrt", 0xD9, 0xFA },
			{ "fsubp", 0xDE, 0xE9 },
			{ "fsubrp", 0xDE, 0xE1 },
			{ "ftst", 0xD9, 0xE4 },
			{ "fucom", 0xDD, 0xE1 },
			{ "fucomp", 0xDD, 0xE9 },
			{ "fucompp", 0xDA, 0xE9 },
			{ "fxam", 0xD9, 0xE5 },
			{ "fxch", 0xD9, 0xC9 },
			{ "fxtract", 0xD9, 0xF4 },
			{ "fyl2x", 0xD9, 0xF1 },
			{ "fyl2xp1", 0xD9, 0xF9 },
		};
		printf("#ifdef XBYAK64\n");
		bool inOnly64Bit = true;
		for (int i = 0; i < NUM_OF_ARRAY(tbl); i++) {
			const Tbl *p = &tbl[i];
			if (strcmp(p->name, "@@@") == 0) {
				if (inOnly64Bit) {
					printf("#else\n");
					inOnly64Bit = false;
				} else {
					printf("#endif\n");
				}
				continue;
			}
			printf("void %s() { db(0x%02X); ", p->name, p->code1);
			if (p->code2) printf("db(0x%02X); ", p->code2);
			if (p->code3) printf("db(0x%02X); ", p->code3);
			printf("}\n");
		}
	}
	{
		const struct Tbl {
			uint8 code; // (reg, reg)
			uint8 ext; // (reg, imm)
			const char *name;
		} tbl[] = {
			{ B00010000, 2, "adc" },
			{ B00000000, 0, "add" },
			{ B00100000, 4, "and" },
			{ B00111000, 7, "cmp" },
			{ B00001000, 1, "or" },
			{ B00011000, 3, "sbb" },
			{ B00101000, 5, "sub" },
			{ B00110000, 6, "xor" },
		};
		for (int i = 0; i < NUM_OF_ARRAY(tbl); i++) {
			const Tbl *p = &tbl[i];
			printf("void %s(const Operand& op1, const Operand& op2) { opRM_RM(op1, op2, 0x%02X); }\n", p->name, p->code);
			printf("void %s(const Operand& op, uint32 imm) { opRM_I(op, imm, 0x%02X, %d); }\n", p->name, p->code, p->ext);
		}
	}

	{
		const struct Tbl {
			uint8 code;
			uint8 ext;
			const char *name;
		} tbl[] = {
			{ B01001000, 1, "dec" },
			{ B01000000, 0, "inc" },
		};
		for (int i = 0; i < NUM_OF_ARRAY(tbl); i++) {
			const Tbl *p = &tbl[i];
			printf("void %s(const Operand& op) { opIncDec(op, 0x%02X, %d); }\n", p->name, p->code, p->ext);
		}
	}
	{
		const struct Tbl {
			uint8 code;
			uint8 ext;
			const char *name;
		} tbl[] = {
			{ B11110110, 6, "div" },
			{ B11110110, 7, "idiv" },
			{ B11110110, 5, "imul" },
			{ B11110110, 4, "mul" },
			{ B11110110, 3, "neg" },
			{ B11110110, 2, "not" },
		};
		for (int i = 0; i < NUM_OF_ARRAY(tbl); i++) {
			const Tbl *p = &tbl[i];
			printf("void %s(const Operand& op) { opR_ModM(op, 0, 3, %d, 0x%02X); }\n", p->name, p->ext, p->code);
		}
	}
	{
		const struct Tbl {
			const char *name;
			uint8 ext;
		} tbl[] = {
			{ "rcl", 2 },
			{ "rcr", 3 },
			{ "rol", 0 },
			{ "ror", 1 },
			{ "sar", 7 },
			{ "shl", 4 },
			{ "shr", 5 },

			{ "sal", 4 },
		};
		for (int i = 0; i < NUM_OF_ARRAY(tbl); i++) {
			const Tbl *p = &tbl[i];
			printf("void %s(const Operand& op, int imm) { opShift(op, imm, %d); }\n", p->name, p->ext);
			printf("void %s(const Operand& op, const Reg8& cl) { opShift(op, cl, %d); }\n", p->name, p->ext);
		}
	}
	{
		const struct Tbl {
			const char *name;
			uint8 code;
		} tbl[] = {
			{ "shld", B10100100 },
			{ "shrd", B10101100 },
		};
		for (int i = 0; i < NUM_OF_ARRAY(tbl); i++) {
			const Tbl *p = &tbl[i];
			printf("void %s(const Operand& op, const Reg& reg, uint8 imm) { opShxd(op, reg, imm, 0x%02X); }\n", p->name, p->code);
			printf("void %s(const Operand& op, const Reg& reg, const Reg8& cl) { opShxd(op, reg, 0, 0x%02X, &cl); }\n", p->name, p->code);
		}
	}
	{
		const struct Tbl {
			const char *name;
			uint8 code;
		} tbl[] = {
			{ "bsf", B10111100 },
			{ "bsr", B10111101 },
		};
		for (int i = 0; i < NUM_OF_ARRAY(tbl); i++) {
			const Tbl *p = &tbl[i];
			printf("void %s(const Reg&reg, const Operand& op) { opModRM(reg, op, op.isREG(16 | i32e), op.isMEM(), 0x0F, 0x%02X); }\n", p->name, p->code);
		}
	}
	// SSSE3
	{
		const struct Tbl {
			uint8 code;
			const char *name;
		} tbl[] = {
			{ 0x00, "pshufb" },
			{ 0x01, "phaddw" },
			{ 0x02, "phaddd" },
			{ 0x03, "phaddsw" },
			{ 0x04, "pmaddubsw" },
			{ 0x05, "phsubw" },
			{ 0x06, "phsubd" },
			{ 0x07, "phsubsw" },
			{ 0x08, "psignb" },
			{ 0x09, "psignw" },
			{ 0x0a, "psignd" },
			{ 0x0b, "pmulhrsw" },
			{ 0x1c, "pabsb" },
			{ 0x1d, "pabsw" },
			{ 0x1e, "pabsd" },
		};
		for (int i = 0; i < NUM_OF_ARRAY(tbl); i++) {
			const Tbl *p = &tbl[i];
			int preCode = 0x38;
			printf("void %s(const Mmx& mmx, const Operand& op) { opMMX(mmx, op, 0x%02X, 0x66, %d, 0x38); }\n", p->name, p->code, NO);
		}
		printf("void palignr(const Mmx& mmx, const Operand& op, int imm) { opMMX(mmx, op, 0x0f, 0x66, static_cast<uint8>(imm), 0x3a); }\n");
	}
	// SSE4
	{
		const struct Tbl {
			uint8 code;
			const char *name;
		} tbl[] = {
			// SSE4.1
			{ 0x15, "blendvpd" },
			{ 0x14, "blendvps" },
			{ 0x2B, "packusdw" },
			{ 0x10, "pblendvb" },
			{ 0x29, "pcmpeqq" },
			{ 0x17, "ptest" },
			{ 0x20, "pmovsxbw" },
			{ 0x21, "pmovsxbd" },
			{ 0x22, "pmovsxbq" },
			{ 0x23, "pmovsxwd" },
			{ 0x24, "pmovsxwq" },
			{ 0x25, "pmovsxdq" },
			{ 0x30, "pmovzxbw" },
			{ 0x31, "pmovzxbd" },
			{ 0x32, "pmovzxbq" },
			{ 0x33, "pmovzxwd" },
			{ 0x34, "pmovzxwq" },
			{ 0x35, "pmovzxdq" },
			{ 0x38, "pminsb" },
			{ 0x39, "pminsd" },
			{ 0x3A, "pminuw" },
			{ 0x3B, "pminud" },
			{ 0x3C, "pmaxsb" },
			{ 0x3D, "pmaxsd" },
			{ 0x3E, "pmaxuw" },
			{ 0x3F, "pmaxud" },
			{ 0x28, "pmuldq" },
			{ 0x40, "pmulld" },
			{ 0x41, "phminposuw"},
			// SSE4.2
			{ 0x37, "pcmpgtq" },
		};
		for (int i = 0; i < NUM_OF_ARRAY(tbl); i++) {
			const Tbl *p = &tbl[i];
			printf("void %s(const Xmm& xmm, const Operand& op) { opGen(xmm, op, 0x%02X, 0x66, isXMM_XMMorMEM, %d, 0x38); }\n", p->name, p->code, NO);
		}
	}
	{
		const struct Tbl {
			uint8 code;
			const char *name;
		} tbl[] = {
			// SSE4.1
			{ 0x0D, "blendpd" },
			{ 0x0C, "blendps" },
			{ 0x41, "dppd" },
			{ 0x40, "dpps" },
			{ 0x42, "mpsadbw" },
			{ 0x0E, "pblendw" },
			{ 0x08, "roundps" },
			{ 0x09, "roundpd" },
			{ 0x0A, "roundss" },
			{ 0x0B, "roundsd" },
			// SSE4.2
			{ 0x60, "pcmpestrm" },
			{ 0x61, "pcmpestri" },
			{ 0x62, "pcmpistrm" },
			{ 0x63, "pcmpistri" },
		};
		for (int i = 0; i < NUM_OF_ARRAY(tbl); i++) {
			const Tbl *p = &tbl[i];
			printf("void %s(const Xmm& xmm, const Operand& op, int imm) { opGen(xmm, op, 0x%02X, 0x66, isXMM_XMMorMEM, static_cast<uint8>(imm), 0x3A); }\n", p->name, p->code);
		}
	}
	{
		const struct Tbl {
			uint8 code;
			uint8 ext;
			const char *name;
		} tbl[] = {
			{ B10101110, 2, "ldmxcsr" },
			{ B10101110, 3, "stmxcsr" },
			{ B10101110, 7, "clflush" }, // 0x80 is bug of nasm ?
//			{ B10000000, 7, "clflush" }, // 0x80 is bug of nasm ?
		};
		for (int i = 0; i < NUM_OF_ARRAY(tbl); i++) {
			const Tbl *p = &tbl[i];
			printf("void %s(const Address& addr) { opModM(addr, Reg32(%d), 0x0F, 0x%02X); }\n", p->name, p->ext, p->code);
		}
	}
	{
		const struct Tbl {
			uint8 code;
			const char *name;
		} tbl[] = {
			{ B00101011, "movntpd" },
			{ B11100111, "movntdq" },
		};
		for (int i = 0; i < NUM_OF_ARRAY(tbl); i++) {
			const Tbl *p = &tbl[i];
			// cast xmm register to 16bit register to put 0x66
			printf("void %s(const Address& addr, const Xmm& reg) { opModM(addr, Reg16(reg.getIdx()), 0x0F, 0x%02X); }\n", p->name, p->code);
		}
	}
	{
		const struct Tbl {
			uint8 code;
			const char *name;
		} tbl[] = {
			{ B10111110, "movsx" },
			{ B10110110, "movzx" },
		};
		for (int i = 0; i < NUM_OF_ARRAY(tbl); i++) {
			const Tbl *p = &tbl[i];
			printf("void %s(const Reg& reg, const Operand& op) { opMovxx(reg, op, 0x%02X); }\n", p->name, p->code);
		}
	}
	{
		const struct Tbl {
			uint8 m16;
			uint8 m32;
			uint8 m64;
			uint8 ext;
			const char *name;
			uint8 m64ext;
		} tbl[] = {
			{ 0x00, 0xD8, 0xDC, 0, "fadd" },
			{ 0xDE, 0xDA, 0x00, 0, "fiadd" },
			{ 0x00, 0xD8, 0xDC, 2, "fcom" },
			{ 0x00, 0xD8, 0xDC, 3, "fcomp" },
			{ 0x00, 0xD8, 0xDC, 6, "fdiv" },
			{ 0xDE, 0xDA, 0x00, 6, "fidiv" },
			{ 0x00, 0xD8, 0xDC, 7, "fdivr" },
			{ 0xDE, 0xDA, 0x00, 7, "fidivr" },
			{ 0xDE, 0xDA, 0x00, 2, "ficom" },
			{ 0xDE, 0xDA, 0x00, 3, "ficomp" },
			{ 0xDF, 0xDB, 0xDF, 0, "fild", 5 },
			{ 0xDF, 0xDB, 0x00, 2, "fist" },
			{ 0xDF, 0xDB, 0xDF, 3, "fistp", 7 },
			{ 0xDF, 0xDB, 0xDD, 1, "fisttp" },
			{ 0x00, 0xD9, 0xDD, 0, "fld" },
			{ 0x00, 0xD8, 0xDC, 1, "fmul" },
			{ 0xDE, 0xDA, 0x00, 1, "fimul" },
			{ 0x00, 0xD9, 0xDD, 2, "fst" },
			{ 0x00, 0xD9, 0xDD, 3, "fstp" },
			{ 0x00, 0xD8, 0xDC, 4, "fsub" },
			{ 0xDE, 0xDA, 0x00, 4, "fisub" },
			{ 0x00, 0xD8, 0xDC, 5, "fsubr" },
			{ 0xDE, 0xDA, 0x00, 5, "fisubr" },
		};
		for (int i = 0; i < NUM_OF_ARRAY(tbl); i++) {
			const Tbl *p = &tbl[i];
			printf("void %s(const Address& addr) { opFpuMem(addr, 0x%02X, 0x%02X, 0x%02X, %d, %d); }\n", p->name, p->m16, p->m32, p->m64, p->ext, p->m64ext);
		}
	}
	{
		const struct Tbl {
			uint32 code1;
			uint32 code2;
			const char *name;
		} tbl[] = {
			{ 0xD8C0, 0xDCC0, "fadd" },
			{ 0x0000, 0xDEC0, "faddp" },

			{ 0xDAC0, 0x00C0, "fcmovb" },
			{ 0xDAC8, 0x00C8, "fcmove" },
			{ 0xDAD0, 0x00D0, "fcmovbe" },
			{ 0xDAD8, 0x00D8, "fcmovu" },
			{ 0xDBC0, 0x00C0, "fcmovnb" },
			{ 0xDBC8, 0x00C8, "fcmovne" },
			{ 0xDBD0, 0x00D0, "fcmovnbe" },
			{ 0xDBD8, 0x00D8, "fcmovnu" },

			{ 0xDBF0, 0x00F0, "fcomi" },
			{ 0xDFF0, 0x00F0, "fcomip" },
			{ 0xDBE8, 0x00E8, "fucomi" },
			{ 0xDFE8, 0x00E8, "fucomip" },

			{ 0xD8F0, 0xDCF8, "fdiv" },
			{ 0x0000, 0xDEF8, "fdivp" },
			{ 0xD8F8, 0xDCF0, "fdivr" },
			{ 0x0000, 0xDEF0, "fdivrp" },
			{ 0xD8C8, 0xDCC8, "fmul" },
			{ 0x0000, 0xDEC8, "fmulp" },
			{ 0xD8E0, 0xDCE8, "fsub" },
			{ 0x0000, 0xDEE8, "fsubp" },
			{ 0xD8E8, 0xDCE0, "fsubr" },
			{ 0x0000, 0xDEE0, "fsubrp" },
		};
		for (int i = 0; i < NUM_OF_ARRAY(tbl); i++) {
			const Tbl *p = &tbl[i];
			printf("void %s(const Fpu& reg1, const Fpu& reg2) { opFpuFpu(reg1, reg2, 0x%04X, 0x%04X); }\n", p->name, p->code1, p->code2);
		}
	}
	{
		const struct Tbl {
			uint8 code1;
			uint8 code2;
			const char *name;
		} tbl[] = {
			{ 0xD8, 0xD0, "fcom" },
			{ 0xD8, 0xD8, "fcomp" },
			{ 0xDD, 0xC0, "ffree" },
			{ 0xD9, 0xC0, "fld" },
			{ 0xDD, 0xD0, "fst" },
			{ 0xDD, 0xD8, "fstp" },
			{ 0xDD, 0xE0, "fucom" },
			{ 0xDD, 0xE8, "fucomp" },
			{ 0xD9, 0xC8, "fxch" },
		};
		for (int i = 0; i < NUM_OF_ARRAY(tbl); i++) {
			const Tbl *p = &tbl[i];
			printf("void %s(const Fpu& reg) { opFpu(reg, 0x%02X, 0x%02X); }\n", p->name, p->code1, p->code2);
		}
	}
}

int main()
{
	put();
	return 0;
}
