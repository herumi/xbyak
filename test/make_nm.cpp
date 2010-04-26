#include <stdio.h>
#include "xbyak/xbyak.h"
#include <stdlib.h>
#define NUM_OF_ARRAY(x) (sizeof(x) / sizeof(x[0]))

using namespace Xbyak;

const int bitEnd = 64;

const uint64 MMX = 1ULL << 0;
const uint64 XMM = 1ULL << 1;
const uint64 _MEM = 1ULL << 2;
const uint64 _REG32 = 1ULL << 3;
const uint64 EAX = 1ULL << 4;
const uint64 IMM32 = 1ULL << 5;
const uint64 IMM8 = 1ULL << 6;
const uint64 _REG8 = 1ULL << 7;
const uint64 _REG16 = 1ULL << 8;
const uint64 NEG8 = 1ULL << 9;
const uint64 IMM16 = 1ULL << 10;
const uint64 NEG16 = 1ULL << 11;
const uint64 AX = 1ULL << 12;
const uint64 AL = 1ULL << 13;
const uint64 IMM = 1ULL << 14;
const uint64 MEM8 = 1ULL << 15;
const uint64 MEM16 = 1ULL << 16;
const uint64 MEM32 = 1ULL << 17;
const uint64 NEG = 1ULL << 18;
const uint64 ONE = 1ULL << 19;
const uint64 CL = 1ULL << 20;
const uint64 MEM_ONLY_DISP = 1ULL << 21;
const uint64 NEG32 = 1ULL << 23;
#ifdef XBYAK64
const uint64 _MEMe = 1ULL << 22;
const uint64 REG32_2 = 1ULL << 24; // r8d, ...
const uint64 REG16_2 = 1ULL << 25; // r8w, ...
const uint64 REG8_2 = 1ULL << 26; // r8b, ...
const uint64 REG8_3 = 1ULL << 27; // spl, ...
const uint64 _REG64 = 1ULL << 28; // rax, ...
const uint64 _REG64_2 = 1ULL << 29; // r8, ...
const uint64 RAX = 1ULL << 30;
#else
const uint64 _MEMe = 0;
const uint64 REG32_2 = 0;
const uint64 REG16_2 = 0;
const uint64 REG8_2 = 0;
const uint64 REG8_3 = 0;
const uint64 _REG64 = 0;
const uint64 _REG64_2 = 0;
const uint64 RAX = 0;
#endif
const uint64 REG64 = _REG64 | _REG64_2 | RAX;
const uint64 REG32 = _REG32 | REG32_2 | EAX;
const uint64 REG16 = _REG16 | REG16_2 | AX;
const uint64 REG32e = REG32 | REG64;
const uint64 REG8 = _REG8 | REG8_2|AL;
const uint64 MEM = _MEM | _MEMe;
const uint64 MEM64 = 1ULL << 31;
const uint64 ST0 = 1ULL << 32;
const uint64 STi = 1ULL << 33;
const uint64 NOPARA = 1ULL << (bitEnd - 1);

class Test {
	const bool isXbyak_;
	// check all op1, op2, op3
	void put(const char *nm, uint64 op1 = NOPARA, uint64 op2 = NOPARA, uint64 op3 = NOPARA) const
	{
		for (int i = 0; i < bitEnd; i++) {
			if ((op1 & (1ULL << i)) == 0) continue;
			for (int j = 0; j < bitEnd; j++) {
				if ((op2 & (1ULL << j)) == 0) continue;
				for (int k = 0; k < bitEnd; k++) {
					if ((op3 & (1ULL << k)) == 0) continue;
					printf("%s ", nm);
					if (isXbyak_) printf("(");
					if (!(op1 & NOPARA)) printf("%s", get(1ULL << i));
					if (!(op2 & NOPARA)) printf(", %s", get(1ULL << j));
					if (!(op3 & NOPARA)) printf(", %s", get(1ULL << k));
					if (isXbyak_) printf("); dump();");
					printf("\n");
				}
			}
		}
	}
	void put(const char *nm, uint64 op, const char *xbyak, const char *nasm) const
	{
		for (int i = 0; i < bitEnd; i++) {
			if ((op & (1ULL << i)) == 0) continue;
			printf("%s ", nm);
			if (isXbyak_) printf("(");
			if (!(op & NOPARA)) printf("%s", get(1ULL << i));
			printf(", %s", isXbyak_ ? xbyak : nasm);
			if (isXbyak_) printf("); dump();");
			printf("\n");
		}
	}
	void put(const char *nm, const char *xbyak, const char *nasm = 0, uint64 op = NOPARA) const
	{
		if (nasm == 0) nasm = xbyak;
		for (int i = 0; i < bitEnd; i++) {
			if ((op & (1ULL << i)) == 0) continue;
			printf("%s ", nm);
			if (isXbyak_) printf("(");
			printf("%s ", isXbyak_ ? xbyak : nasm);
			if (!(op & NOPARA)) printf(", %s", get(1ULL << i));
			if (isXbyak_) printf("); dump();");
			printf("\n");
		}
	}
	const char *get(uint64 type) const
	{
		int idx = (rand() / 31) & 7;
		if (type == ST0) {
			return "st0";
		}
		if (type == STi) {
			return "st2";
		}
		switch (type) {
		case MMX:
			{
				static const char MmxTbl[][4] = {
					"mm0", "mm1", "mm2", "mm3", "mm4", "mm5", "mm6", "mm7"
				};
				return MmxTbl[idx];
			}
		case XMM:
			{
				static const char XmmTbl[][6] = {
					"xmm0", "xmm1", "xmm2", "xmm3", "xmm4", "xmm5", "xmm6", "xmm7",
					"xmm8", "xmm9", "xmm10", "xmm11", "xmm12", "xmm13", "xmm14", "xmm15"
				};
				static const char MyXmmTbl[][6] = {
					"xm0", "xm1", "xm2", "xm3", "xm4", "xm5", "xm6", "xm7",
					"xm8", "xm9", "xm10", "xm11", "xm12", "xm13", "xm14", "xm15"
				};
#ifdef XBYAK64
				const int adj = 4;
#else
				const int adj = 0;
#endif
				return isXbyak_ ? MyXmmTbl[idx + adj] : XmmTbl[idx + adj];
			}
		case _MEM:
			return isXbyak_ ? "ptr[eax+ecx+3]" : "[eax+ecx+3]";
		case _MEMe:
			{
				static int ccc = 1;
#ifdef USE_YASM
				ccc++;
#endif
				if (ccc & 1) {
					return isXbyak_ ? "ptr[rdx+r15+0x12]" : "[rdx+r15+0x12]";
				} else {
					return isXbyak_ ? "ptr[rip - 0x13456]" : "[rip - 0x13456]";
				}
			}
		case MEM8:
			return "byte [eax+edx]";
		case MEM16:
			return "word [esi]";
		case MEM32:
			return "dword [ebp*2]";
		case MEM64:
			return "qword [eax+ecx*8]";
		case MEM_ONLY_DISP:
			return isXbyak_ ? "ptr[(void*)0x123]" : "[0x123]";
		case _REG16: // not ax
			{
				static const char Reg16Tbl[][4] = {
					"ax", "cx", "dx", "bx", "sp", "bp", "si", "di"
				};
				return Reg16Tbl[(idx % 7) + 1];
			}
		case _REG8: // not al
			{
				static const char Reg8Tbl[][4] = {
#ifdef XBYAK64 // QQQ
					"al", "cl", "dl", "bl", "al", "cl", "dl", "bl"
#else
					"al", "cl", "dl", "bl", "ah", "ch", "dh", "bh"
#endif
				};
				return Reg8Tbl[(idx % 7) + 1];
			}
		case _REG32: // not eax
			{
				static const char Reg32Tbl[][4] = {
					"eax", "ecx", "edx", "ebx", "esp", "ebp", "esi", "edi"
				};
				return Reg32Tbl[(idx % 7) + 1];
			}
#ifdef XBYAK64
		case _REG64: // not rax
			{
				static const char Reg64Tbl[][4] = {
					"rax", "rcx", "rdx", "rbx", "rsp", "rbp", "rsi", "rdi"
				};
				return Reg64Tbl[(idx % 7) + 1];
			}
		case _REG64_2:
			{
				static const char Reg64_2Tbl[][4] = {
					"r8", "r9", "r10", "r11", "r12", "r13", "r14", "r15"
				};
				return Reg64_2Tbl[idx];
			}
		case REG32_2:
			{
				static const char Reg32eTbl[][5] = {
					"r8d", "r9d", "r10d", "r11d", "r12d", "r13d", "r14d", "r15d"
				};
				return Reg32eTbl[idx];
			}
		case REG16_2:
			{
				static const char Reg16eTbl[][5] = {
					"r8w", "r9w", "r10w", "r11w", "r12w", "r13w", "r14w", "r15w"
				};
				return Reg16eTbl[idx];
			}
		case REG8_2:
			{
				static const char Reg8_2Tbl[][5] = {
					"r8b", "r9b", "r10b", "r11b", "r12b", "r13b", "r14b", "r15b"
				};
				return Reg8_2Tbl[idx];
			}
		case REG8_3:
			{
				static const char Reg8_3Tbl[][5] = {
					"spl", "bpl", "sil", "dil", "spl", "bpl", "sil", "dil"
				};
				return Reg8_3Tbl[idx];
			}
		case RAX:
			return "rax";
#endif
		case EAX:
			return "eax";
		case AX:
			return "ax";
		case AL:
			return "al";
		case CL:
			return "cl";
		case ONE:
			return "1";
		case IMM32:
			return isXbyak_ ? "12345678" : "dword 12345678";
		case IMM16:
			return isXbyak_ ? "1000" : "word 1000";
		case IMM8:
			return isXbyak_ ? "4" : "byte 4";
		case NEG8:
			return isXbyak_ ? "-30" : "byte -30";
		case NEG16:
			return isXbyak_ ? "-1000" : "word -1000";
		case NEG32:
			return isXbyak_ ? "-100000" : "dword -100000";
		case IMM:
			return "4";
		case NEG:
			return "-5";
		}
		return 0;
	}
	void putSIMPLE() const
	{
		const char tbl[][10] = {
#ifdef XBYAK64
			"cdqe",
#else
			"aaa",
			"aad",
			"aam",
			"aas",
			"daa",
			"das",
			"popad",
			"popfd",
			"pusha",
			"pushad",
			"pushfd",
			"popa",
#endif

			"cbw",
			"cdq",
			"clc",
			"cld",
			"cli",
			"cmc",

			"cpuid",
			"cwd",
			"cwde",

			"lahf",
			"lock",
			"nop",

			"sahf",
			"stc",
			"std",
			"sti",

			"emms",
			"pause",
			"sfence",
			"lfence",
			"mfence",
			"monitor",
			"mwait",

			"rdmsr",
			"rdpmc",
			"rdtsc",
			"wait",
			"wbinvd",
			"wrmsr",
			"xlatb",

			"popf",
			"pushf",

			"f2xm1",
			"fabs",
			"faddp",
			"fchs",
			"fcom",
			"fcomp",
			"fcompp",
			"fcos",
			"fdecstp",
			"fdivp",
			"fdivrp",
			"fincstp",
			"fld1",
			"fldl2t",
			"fldl2e",
			"fldpi",
			"fldlg2",
			"fldln2",
			"fldz",
			"fmulp",
			"fnop",
			"fpatan",
            "fprem",
            "fprem1",
            "fptan",
            "frndint",
            "fscale",
			"fsin",
            "fsincos",
            "fsqrt",
            "fsubp",
            "fsubrp",
            "ftst",
            "fucom",
            "fucomp",
            "fucompp",
            "fxam",
            "fxch",
            "fxtract",
            "fyl2x",
            "fyl2xp1",
		};
		for (size_t i = 0; i < NUM_OF_ARRAY(tbl); i++) {
			put(tbl[i]);
		}

		put("bswap", REG32e);
		put("lea", REG32e, MEM);
#ifdef XBYAK64
		put("jmp", REG64);
		put("call", REG64);
#else
		put("jmp", REG32);
		put("call", REG32);
#endif
		put("jmp", MEM);
		put("call", REG16|MEM|MEM_ONLY_DISP);
		put("call", "getCode() + 5", "$ + 5");
	}
	void putMMX1() const
	{
		// emms etc
		put("ldmxcsr", MEM);
		put("movmskps", REG32e, XMM);
		put("movmskpd", REG32e, XMM);
		put("stmxcsr", MEM);
		put("maskmovq", MMX, MMX);
		put("movntps", MEM, XMM);
		put("movntq", MEM, MMX);
		put("prefetcht0", MEM);
		put("prefetcht1", MEM);
		put("prefetcht2", MEM);
		put("prefetchnta", MEM);

		// SSE2 misc
		put("maskmovdqu", XMM, XMM);
		put("movntpd", MEM, XMM);
		put("movntdq", MEM, XMM);
		put("movnti", MEM, REG32); // QQQ:REG32e?

		put("movhlps", XMM, XMM);
		put("movlhps", XMM, XMM);

		// movd for MMX, XMM
		put("movd", MEM|MEM32|REG32, MMX|XMM);
		put("movd", MMX|XMM, MEM|REG32|MEM32);

		// movq for MMX
		put("movq", MMX, MMX|MEM);
		put("movq", MEM, MMX);
		// movq for XMM
		put("movq", XMM, XMM|MEM);
		put("movq", MEM, XMM);
		put("movq", XMM|MMX, "qword[eax]", "qword[eax]");
		put("movq", XMM|MMX, "ptr[eax]", "qword[eax]");
		put("movq", "qword[eax]", "qword[eax]", XMM|MMX);
		put("movq", "ptr[eax]", "qword[eax]", XMM|MMX);
#ifdef XBYAK64
		put("movq", REG64, XMM|MMX);
		put("movq", XMM|MMX, REG64);
#endif

		// SSE3 int
		put("lddqu", XMM, MEM);
	}
	void putMMX2() const
	{
		static const char nmTbl[][16] = {
			// MMX
			"packssdw",
			"packsswb",
			"packuswb",
			"pand",
			"pandn",
			"pmaddwd",
			"pmulhuw",
			"pmulhw",
			"pmullw",
			"por",
			"punpckhbw",
			"punpckhwd",
			"punpckhdq",
			"punpcklbw",
			"punpcklwd",
			"punpckldq",
			"pxor",
			"paddb",
			"paddw",
			"paddd",
			"paddsb",
			"paddsw",
			"paddusb",
			"paddusw",
			"pcmpeqb",
			"pcmpeqw",
			"pcmpeqd",
			"pcmpgtb",
			"pcmpgtw",
			"pcmpgtd",
			"psllw",
			"pslld",
			"psllq",
			"psraw",
			"psrad",
			"psrlw",
			"psrld",
			"psrlq",
			"psubb",
			"psubw",
			"psubd",
			"psubsb",
			"psubsw",
			"psubusb",
			"psubusw",
			// MMX2
			"pavgb",
			"pavgw",
			"pmaxsw",
			"pmaxub",
			"pminsw",
			"pminub",
			"psadbw",
			//
			"paddq",
			"pmuludq",
			"psubq",
		};
		for (size_t i = 0; i < NUM_OF_ARRAY(nmTbl); i++) {
			put(nmTbl[i], MMX, MMX|MEM);
			put(nmTbl[i], XMM, XMM|MEM);
		}
	}
	void putMMX3() const
	{
		static const char nmTbl[][16] = {
			"psllw",
			"pslld",
			"psllq",
			"psraw",
			"psrad",
			"psrlw",
			"psrld",
			"psrlq",
		};
		for (size_t i = 0; i < NUM_OF_ARRAY(nmTbl); i++) {
			put(nmTbl[i], MMX|XMM, IMM);
		}
		put("pslldq", XMM, IMM);
		put("psrldq", XMM, IMM);
		put("pmovmskb", REG32, MMX|XMM); // QQQ
		put("pextrw", REG32, MMX|XMM, IMM); // QQQ
		put("pinsrw", MMX|XMM, REG32|MEM, IMM); // QQQ
	}
	void putMMX4() const
	{
		put("pshufw", MMX, MMX|MEM, IMM);
		put("pshuflw", XMM, XMM|MEM, IMM);
		put("pshufhw", XMM, XMM|MEM, IMM);
		put("pshufd", XMM, XMM|MEM, IMM);
	}
	void putMMX5() const
	{
		static const char nmTbl[][16] = {
			"movdqa",
			"movdqu",
			"movaps",
			"movss",
			"movups",
			"movapd",
			"movsd",
			"movupd",
		};
		for (size_t i = 0; i < NUM_OF_ARRAY(nmTbl); i++) {
			put(nmTbl[i], XMM, XMM|MEM);
			put(nmTbl[i], MEM, XMM);
		}
		put("movq2dq", XMM, MMX);
		put("movdq2q", MMX, XMM);
	}

	void putXMM1() const
	{
		enum {
			PS = 1 << 0,
			SS = 1 << 1,
			PD = 1 << 2,
			SD = 1 << 3
		};
		const struct {
			uint8 code;
			const char *name;
		} sufTbl[] = {
			{ 0, "ps" },
			{ 0xF3, "ss" },
			{ 0x66, "pd" },
			{ 0xF2, "sd" },
		};
		static const struct XmmTbl1 {
			uint8 code;
			int mode;
			const char *name;
			bool hasImm;
		} xmmTbl1[] = {
			{ B01011000, PS|SS|PD|SD, "add", false },
			{ B01010101, PS|PD      , "andn", false },
			{ B01010100, PS|PD      , "and", false },
			{ B11000010, PS|SS|PD|SD, "cmp", true },
			{ B01011110, PS|SS|PD|SD, "div", false },
			{ B01011111, PS|SS|PD|SD, "max", false },
			{ B01011101, PS|SS|PD|SD, "min", false },
			{ B01011001, PS|SS|PD|SD, "mul", false },
			{ B01010110, PS|PD      , "or", false },
			{ B01010011, PS|SS      , "rcp", false },
			{ B01010010, PS|SS      , "rsqrt", false },
			{ B11000110, PS|PD      , "shuf", true },
			{ B01010001, PS|SS|PD|SD, "sqrt", false },
			{ B01011100, PS|SS|PD|SD, "sub", false },
			{ B00010101, PS|PD      , "unpckh", false },
			{ B00010100, PS|PD      , "unpckl", false },
			{ B01010111, PS|PD      , "xor", false },
			//
		};
		for (size_t i = 0; i < NUM_OF_ARRAY(xmmTbl1); i++) {
			const XmmTbl1 *p = &xmmTbl1[i];
			for (size_t j = 0; j < NUM_OF_ARRAY(sufTbl); j++) {
				if (!(p->mode & (1 << j))) continue;
				char buf[16];
				sprintf(buf, "%s%s", p->name, sufTbl[j].name);
				if (p->hasImm) {
					put(buf, XMM, XMM|MEM, IMM);
				} else {
					put(buf, XMM, XMM|MEM);
				}
			}
		}
	}
	void putXMM2() const
	{
		// (XMM, XMM|MEM)
		static const char tbl[][16] = {
			"punpckhqdq",
			"punpcklqdq",

			"comiss",
			"ucomiss",
			"comisd",
			"ucomisd",

			"cvtpd2ps",
			"cvtps2pd",
			"cvtsd2ss",
			"cvtss2sd",
			"cvtpd2dq",
			"cvttpd2dq",
			"cvtdq2pd",
			"cvtps2dq",
			"cvttps2dq",
			"cvtdq2ps",

			"addsubpd",
			"addsubps",
			"haddpd",
			"haddps",
			"hsubpd",
			"hsubps",
			"movddup",
			"movshdup",
			"movsldup",
		};
		for (size_t i = 0; i < NUM_OF_ARRAY(tbl); i++) {
			put(tbl[i], XMM, XMM|MEM);
		}
	}
	void putXMM3() const
	{
		static const struct Tbl {
			const char *name;
			int op1;
			int op2;
		} tbl[] = {
			{ "cvtpi2ps", XMM, MMX|MEM },
			{ "cvtps2pi", MMX, XMM|MEM },
			{ "cvtsi2ss", XMM, REG32|MEM },
			{ "cvtss2si", REG32, XMM|MEM },
			{ "cvttps2pi", MMX, XMM|MEM },
			{ "cvttss2si", REG32, XMM|MEM },
			{ "cvtpi2pd", XMM, MMX|MEM },
			{ "cvtpd2pi", MMX, XMM|MEM },
			{ "cvtsi2sd", XMM, REG32|MEM },
			{ "cvtsd2si", REG32, XMM|MEM },
			{ "cvttpd2pi", MMX, XMM|MEM },
			{ "cvttsd2si", REG32, XMM|MEM },
		};
		for (size_t i = 0; i < NUM_OF_ARRAY(tbl); i++) {
			const Tbl *p = &tbl[i];
			put(p->name, p->op1, p->op2);
		}
	}
	void putXMM4() const
	{
		static const char tbl[][16] = {
			"movhps",
			"movlps",
			"movhpd",
			"movlpd",
		};
		for (size_t i = 0; i < NUM_OF_ARRAY(tbl); i++) {
			const char *p = tbl[i];
			put(p, XMM, MEM);
			put(p, MEM, XMM);
		}
	}
	void putCmov() const
	{
		const char tbl[][4] = {
			"o",
			"no",
			"b",
			"c",
			"nae",
			"nb",
			"nc",
			"ae",
			"e",
			"z",
			"ne",
			"nz",
			"be",
			"na",
			"nbe",
			"a",
			"s",
			"ns",
			"p",
			"pe",
			"np",
			"po",
			"l",
			"nge",
			"nl",
			"ge",
			"le",
			"ng",
			"nle",
			"g",
		};
		for (size_t i = 0; i < NUM_OF_ARRAY(tbl); i++) {
			char buf[16];
			sprintf(buf, "cmov%s", tbl[i]);
			put(buf, REG32, REG32|MEM);
			put(buf, REG64, REG64|MEM);
			sprintf(buf, "set%s", tbl[i]);
			put(buf, REG8|REG8_3|MEM);
		}
	}
	void putReg1() const
	{
		// (REG, REG|MEM)
		static const char tbl[][16] = {
			"adc",
			"add",
			"and",
			"cmp",
			"or",
			"sbb",
			"sub",
			"xor",
		};
		for (size_t i = 0; i < NUM_OF_ARRAY(tbl); i++) {
			const char *p = tbl[i];
			put(p, REG32, REG32|MEM);
			put(p, REG64, REG64|MEM);
			put(p, REG16, REG16|MEM);
			put(p, REG8|REG8_3, REG8|MEM);
			put(p, MEM, REG32e|REG16|REG8|REG8_3);

			put(p, MEM8, IMM8|NEG8);
			put(p, MEM16, IMM8|IMM16|NEG8|NEG16);
			put(p, MEM32, IMM8|IMM32|NEG8|NEG32);

			put(p, REG64|RAX, IMM8|NEG8);
			put(p, REG64|RAX, "0x12345678", "0x12345678");
			put(p, REG32|EAX, IMM8|IMM32|NEG8);
			put(p, REG16|AX, IMM8|IMM16|NEG8|NEG16);
			put(p, REG8|REG8_3|AL, IMM|NEG8);
		}
	}
	void putRorM() const
	{
		static const char tbl[][16] = {
			"inc",
			"dec",
			"div",
			"idiv",
			"imul",
			"mul",
			"neg",
			"not",
		};
		for (size_t i = 0; i < NUM_OF_ARRAY(tbl); i++) {
			const char *p = tbl[i];
			put(p, REG32e|REG16|REG8|REG8_3);
			put(p, MEM32|MEM16|MEM8);
		}
		const char *p = "imul";
		put(p, REG16, REG16|MEM16);
		put(p, REG32, REG32|MEM32);
		put(p, REG64, REG64|MEM);
		put(p, REG16, REG16|MEM, IMM8|IMM16);
		put(p, REG32, REG32|MEM, IMM8|IMM32);
		put(p, REG64, REG64|MEM, IMM8|IMM32);
	}
	void putPushPop() const
	{
		/*
			QQQ:
			push byte 2
			push dword 2
			はstackを4byte減らすが
			push word 2
			はstackを2byte減らすのでサポートしない
		*/
		const char *p = "push";
		put(p, REG16);
		put(p, IMM8); // IMM16 decrease -2 from esp
		put(p, MEM16);

		put("pop", REG16|MEM16);
#ifdef XBYAK64
		put("push", REG64);
		put("pop", REG64);
#else
		put("push", REG32|IMM32|MEM32);
		put("pop", REG32|MEM32);
#endif
	}
	void putTest() const
	{
		const char *p = "test";
		put(p, REG32|MEM, REG32);
		put(p, REG64|MEM, REG64);
		put(p, REG16|MEM, REG16);
		put(p, REG8|REG8_3|MEM, REG8|REG8_3);
		put(p, REG32e|REG16|REG8|REG8_3|EAX|AX|AL|MEM32|MEM16|MEM8, IMM);
	}
	void putEtc() const
	{
		const char *p = "ret";
		put(p);
		put(p, IMM);
		p = "mov";
		put(p, EAX|REG32|MEM|MEM_ONLY_DISP, REG32|EAX);
		put(p, REG64|MEM|MEM_ONLY_DISP, REG64|RAX);
		put(p, AX|REG16|MEM|MEM_ONLY_DISP, REG16|AX);
		put(p, AL|REG8|REG8_3|MEM|MEM_ONLY_DISP, REG8|REG8_3|AL);
		put(p, REG32e|REG16|REG8|RAX|EAX|AX|AL, MEM|IMM|MEM_ONLY_DISP);
		put(p, MEM32|MEM16|MEM8, IMM);
		put(p, REG64, "0x1234567890abcdefLL", "0x1234567890abcdef");
#ifdef XBYAK64
		put(p, RAX|EAX|AX|AL, "ptr [0x1234567890abcdefLL]", "[qword 0x1234567890abcdef]");
		put(p, "ptr [0x1234567890abcdefLL]", "[qword 0x1234567890abcdef]", RAX|EAX|AX|AL);
		put(p, "qword [rax], 0");
		put(p, "qword [rax], 0x12");
		put(p, "qword [rax], 0x1234");
		put(p, "qword [rax], 0x12345678");
//		put(p, "qword [rax], 0x123456789ab");
		put(p, "qword [rax], 1000000");
		put(p, "rdx, qword [rax]");
#endif

		const char tbl[][8] = {
			"movsx",
			"movzx",
		};
		for (size_t i = 0; i < NUM_OF_ARRAY(tbl); i++) {
			const char *p = tbl[i];
			put(p, REG64, REG16|REG8|MEM8|MEM16);
			put(p, REG32, REG16|REG8|MEM8|MEM16);
			put(p, REG16, REG8|MEM8);
		}
		put("cmpxchg8b", MEM);
#ifdef XBYAK64
		put("cmpxchg16b", MEM);
#endif
		put("xadd", REG8|MEM, REG8);
		put("xadd", REG16|MEM, REG16);
		put("xadd", REG32|MEM, REG32);
		put("xadd", REG64|MEM, REG64);

		put("xchg", AL|REG8, AL|REG8|MEM);
		put("xchg", MEM, AL|REG8);
		put("xchg", AX|REG16, AX|REG16|MEM);
		put("xchg", MEM, AX|REG16);
		put("xchg", EAX|REG32, EAX|REG32|MEM);
		put("xchg", MEM, EAX|REG32);
		put("xchg", REG64, REG64|MEM);
	}
	void putShift() const
	{
		const char tbl[][8] = {
			"rcl",
			"rcr",
			"rol",
			"ror",
			"sar",
			"shl",
			"shr",

			"sal",
		};
		for (size_t i = 0; i < NUM_OF_ARRAY(tbl); i++) {
			const char *p = tbl[i];
			put(p, REG32e|REG16|REG8|MEM32|MEM16|MEM8, ONE|CL|IMM);
		}
	}
	void putShxd() const
	{
		const char tbl[][8] = {
			"shld",
			"shrd",
		};
		for (size_t i = 0; i < NUM_OF_ARRAY(tbl); i++) {
			const char *p = tbl[i];
			put(p, REG64|MEM, REG64, IMM|CL);
			put(p, REG32|MEM, REG32, IMM|CL);
			put(p, REG16|MEM, REG16, IMM|CL);
		}
	}
	void putBs() const
	{
		const char tbl[][8] = {
			"bsr",
			"bsf",
		};
		for (size_t i = 0; i < NUM_OF_ARRAY(tbl); i++) {
			const char *p = tbl[i];
			put(p, REG64, REG64|MEM);
			put(p, REG32, REG32|MEM);
			put(p, REG16, REG16|MEM);
		}
	}
	void putSSSE3() const
	{
		const char tbl[][16] = {
			"pshufb",
			"phaddw",
			"phaddd",
			"phaddsw",
			"pmaddubsw",
			"phsubw",
			"phsubd",
			"phsubsw",
			"psignb",
			"psignw",
			"psignd",
			"pmulhrsw",
			"pabsb",
			"pabsw",
			"pabsd",
		};
		for (size_t i = 0; i < NUM_OF_ARRAY(tbl); i++) {
			const char *p = tbl[i];
			put(p, XMM, XMM|MEM);
			put(p, MMX, MMX|MEM);
		}
		put("palignr", XMM, XMM|MEM, IMM8);
		put("palignr", MMX, MMX|MEM, IMM8);
	}
	void putSSE4_1() const
	{
		const char tbl[][16] = {
			"blendvpd",
			"blendvps",
			"packusdw",
			"pblendvb",
			"pcmpeqq",
			"ptest",
			"pmovsxbw",
			"pmovsxbd",
			"pmovsxbq",
			"pmovsxwd",
			"pmovsxwq",
			"pmovsxdq",
			"pmovzxbw",
			"pmovzxbd",
			"pmovzxbq",
			"pmovzxwd",
			"pmovzxwq",
			"pmovzxdq",
			"pminsb",
			"pminsd",
			"pminuw",
			"pminud",
			"pmaxsb",
			"pmaxsd",
			"pmaxuw",
			"pmaxud",
			"pmuldq",
			"pmulld",
			"phminposuw",
			"pcmpgtq",
		};
		for (size_t i = 0; i < NUM_OF_ARRAY(tbl); i++) {
			const char *p = tbl[i];
			put(p, XMM, XMM|MEM);
		}
	}
	void putSSE4_2() const
	{
		const char tbl[][16] = {
			"blendpd",
			"blendps",
			"dppd",
			"dpps",
			"mpsadbw",
			"pblendw",
			"roundps",
			"roundpd",
			"roundss",
			"roundsd",
			"pcmpestrm",
			"pcmpestri",
			"pcmpistrm",
			"pcmpistri",
		};
		for (size_t i = 0; i < NUM_OF_ARRAY(tbl); i++) {
			const char *p = tbl[i];
			put(p, XMM, XMM|MEM, IMM);
		}
		put("extractps", REG32e|MEM, XMM, IMM);
		put("pextrw", REG32e|MEM, XMM, IMM); // pextrw for REG32 is for MMX2
		put("pextrb", REG32e|MEM, XMM, IMM);
		put("pextrd", REG32|MEM, XMM, IMM);

		put("insertps", XMM, XMM|MEM, IMM);
		put("pinsrb", XMM, REG32|MEM, IMM);
		put("pinsrd", XMM, REG32|MEM, IMM);
		put("movntdqa", XMM, MEM);
		put("popcnt", REG16, REG16|MEM);
		put("popcnt", REG32, REG32|MEM);
		put("popcnt", REG64, REG64|MEM);
		put("crc32", REG32, REG8|REG16|REG32|MEM8|MEM16|MEM32);
		put("crc32", REG64, REG64|REG8|MEM8);
	}
	void putFpuMem16_32() const
	{
		const char tbl[][8] = {
			"fiadd",
			"fidiv",
			"fidivr",
			"ficom",
			"ficomp",
			"fimul",
			"fist",
			"fisub",
			"fisubr",
		};
		for (size_t i = 0; i < NUM_OF_ARRAY(tbl); i++) {
			const char *p = tbl[i];
			put(p, MEM16|MEM32);
		}
	}
	void putFpuMem32_64() const
	{
		const char tbl[][8] = {
			"fadd",
			"fcom",
			"fcomp",
			"fdiv",
			"fdivr",
			"fld",
			"fmul",
			"fst",
			"fstp",
			"fsub",
			"fsubr",
		};
		for (size_t i = 0; i < NUM_OF_ARRAY(tbl); i++) {
			const char *p = tbl[i];
			put(p, MEM32|MEM64);
		}
	}
	void putFpuMem16_32_64() const
	{
		const char tbl[][8] = {
			"fild",
			"fistp",
			"fisttp",
		};
		for (size_t i = 0; i < NUM_OF_ARRAY(tbl); i++) {
			const char *p = tbl[i];
			put(p, MEM16|MEM32|MEM64);
		}
	}
	void putFpuFpu() const
	{
		const struct Tbl {
			const char *name;
			int mode; /* 1:only (st0, sti), 2: only (sti, st0), 3: both */
		} tbl[] = {
			{ "fadd", 3 },
			{ "faddp", 2 },
			{ "fcmovb", 1 },
			{ "fcmove", 1 },
			{ "fcmovbe", 1 },
			{ "fcmovu", 1 },
			{ "fcmovnb", 1 },
			{ "fcmovne", 1 },
			{ "fcmovnbe", 1 },
			{ "fcmovnu", 1 },
			{ "fcomi", 1 },
			{ "fcomip", 1 },
			{ "fucomi", 1 },
			{ "fucomip", 1 },
			{ "fdiv", 3 },
			{ "fdivp", 2 },
			{ "fdivr", 3 },
			{ "fdivrp", 2 },
			{ "fmul", 3 },
			{ "fmulp", 2 },
			{ "fsub", 3 },
			{ "fsubp", 2 },
			{ "fsubr", 3 },
			{ "fsubrp", 2 },
		};
		for (size_t i = 0; i < NUM_OF_ARRAY(tbl); i++) {
			const Tbl *p = &tbl[i];
			if (p->mode & 1) put(p->name, ST0, STi);
			if (p->mode & 2) put(p->name, STi, ST0);
		}
	}
	void putFpu() const
	{
		const char tbl[][16] = {
			"fcom",
			"fcomp",
			"ffree",
			"fld",
			"fst",
			"fstp",
			"fucom",
			"fucomp",
			"fxch",
		};
		for (size_t i = 0; i < NUM_OF_ARRAY(tbl); i++) {
			put(tbl[i], STi);
		}
	}
public:
	Test(bool isXbyak)
		: isXbyak_(isXbyak)
	{
	}
	void put() const
	{
#ifndef USE_YASM
		putSIMPLE();
		putReg1();
		putRorM();
		putPushPop();
		putTest();
		putEtc();
		putShift();
		putShxd();
		putBs();
		putMMX1();
		putMMX2();
		putMMX3();
		putMMX4();
		putMMX5();
		putXMM1();
		putXMM2();
		putXMM3();
		putXMM4();
		putCmov();
		putFpuMem16_32();
		putFpuMem32_64();
		putFpuMem16_32_64();
		put("clflush", MEM); // current nasm is ok
		putFpu();
#else
		putFpuFpu();
		putSSSE3();
		putSSE4_1();
		putSSE4_2();
#endif
	}
};

int main(int argc, char *[])
{
	Test test(argc > 1);
	test.put();
}

