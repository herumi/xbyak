#include <stdio.h>
#include "xbyak/xbyak.h"
#include <stdlib.h>
#include <string.h>
#define NUM_OF_ARRAY(x) (sizeof(x) / sizeof(x[0]))

using namespace Xbyak;

const int bitEnd = 64;

const uint64 MMX = 1ULL << 0;
const uint64 _XMM = 1ULL << 1;
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
const uint64 IMM_1 = 1ULL << 14;
const uint64 MEM8 = 1ULL << 15;
const uint64 MEM16 = 1ULL << 16;
const uint64 MEM32 = 1ULL << 17;
const uint64 NEG = 1ULL << 18;
const uint64 ONE = 1ULL << 19;
const uint64 CL = 1ULL << 20;
const uint64 MEM_ONLY_DISP = 1ULL << 21;
const uint64 NEG32 = 1ULL << 23;
const uint64 _YMM = 1ULL << 24;
const uint64 VM32X_32 = 1ULL << 39;
const uint64 VM32X_64 = 1ULL << 40;
const uint64 VM32Y_32 = 1ULL << 41;
const uint64 VM32Y_64 = 1ULL << 42; // max value
#ifdef XBYAK64
const uint64 _MEMe = 1ULL << 25;
const uint64 REG32_2 = 1ULL << 26; // r8d, ...
const uint64 REG16_2 = 1ULL << 27; // r8w, ...
const uint64 REG8_2 = 1ULL << 28; // r8b, ...
const uint64 REG8_3 = 1ULL << 29; // spl, ...
const uint64 _REG64 = 1ULL << 30; // rax, ...
const uint64 _REG64_2 = 1ULL << 31; // r8, ...
const uint64 RAX = 1ULL << 32;
const uint64 _XMM2 = 1ULL << 33;
const uint64 _YMM2 = 1ULL << 34;
const uint64 VM32X = VM32X_32 | VM32X_64;
const uint64 VM32Y = VM32Y_32 | VM32Y_64;
#else
const uint64 _MEMe = 0;
const uint64 REG32_2 = 0;
const uint64 REG16_2 = 0;
const uint64 REG8_2 = 0;
const uint64 REG8_3 = 0;
const uint64 _REG64 = 0;
const uint64 _REG64_2 = 0;
const uint64 RAX = 0;
const uint64 _XMM2 = 0;
const uint64 _YMM2 = 0;
const uint64 VM32X = VM32X_32;
const uint64 VM32Y = VM32Y_32;
#endif
const uint64 REG64 = _REG64 | _REG64_2 | RAX;
const uint64 REG32 = _REG32 | REG32_2 | EAX;
const uint64 REG16 = _REG16 | REG16_2 | AX;
const uint64 REG32e = REG32 | REG64;
const uint64 REG8 = _REG8 | REG8_2|AL;
const uint64 MEM = _MEM | _MEMe;
const uint64 MEM64 = 1ULL << 35;
const uint64 ST0 = 1ULL << 36;
const uint64 STi = 1ULL << 37;
const uint64 IMM_2 = 1ULL << 38;
const uint64 IMM = IMM_1 | IMM_2;
const uint64 XMM = _XMM | _XMM2;
const uint64 YMM = _YMM | _YMM2;
const uint64 NOPARA = 1ULL << (bitEnd - 1);

class Test {
	Test(const Test&);
	void operator=(const Test&);
	const bool isXbyak_;
	int funcNum_;
	// check all op1, op2, op3
	void put(const char *nm, uint64 op1 = NOPARA, uint64 op2 = NOPARA, uint64 op3 = NOPARA, uint64 op4 = NOPARA) const
	{
		for (int i = 0; i < bitEnd; i++) {
			if ((op1 & (1ULL << i)) == 0) continue;
			for (int j = 0; j < bitEnd; j++) {
				if ((op2 & (1ULL << j)) == 0) continue;
				for (int k = 0; k < bitEnd; k++) {
					if ((op3 & (1ULL << k)) == 0) continue;
					for (int s = 0; s < bitEnd; s++) {
						if ((op4 & (1ULL << s)) == 0) continue;
						printf("%s ", nm);
						if (isXbyak_) printf("(");
						if (!(op1 & NOPARA)) printf("%s", get(1ULL << i));
						if (!(op2 & NOPARA)) printf(", %s", get(1ULL << j));
						if (!(op3 & NOPARA)) printf(", %s", get(1ULL << k));
						if (!(op4 & NOPARA)) printf(", %s", get(1ULL << s));
						if (isXbyak_) printf("); dump();");
						printf("\n");
					}
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
		case _XMM:
			{
				static const char tbl[][6] = {
					"xmm0", "xmm1", "xmm2", "xmm3", "xmm4", "xmm5", "xmm6", "xmm7",
				};
				return tbl[idx];
			}
		case _YMM:
			{
				static const char tbl[][6] = {
					"ymm0", "ymm1", "ymm2", "ymm3", "ymm4", "ymm5", "ymm6", "ymm7"
				};
				return tbl[idx];
			}
#ifdef XBYAK64
		case _XMM2:
			{
				static const char tbl[][6] = {
					"xmm8", "xmm9", "xmm10", "xmm11", "xmm12", "xmm13", "xmm14", "xmm15"
				};
				return tbl[idx];
			}
		case _YMM2:
			{
				static const char tbl[][6] = {
					"ymm0", "ymm1", "ymm2", "ymm3", "ymm4", "ymm5", "ymm6", "ymm7",
				};
				return tbl[idx];
			}
#endif
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
					return isXbyak_ ? "ptr[rip - 0x13456+1-3]" : "[rip - 0x13456+1-3]";
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
		case IMM_1:
			return "4";
		case IMM_2:
			return isXbyak_ ? "0xda" : "0xda";
		case NEG:
			return "-5";
		case VM32X_32:
			return isXbyak_ ? "ptr [ebp+4+xmm1*8]" : "[ebp+4+xmm1*8]";
		case VM32X_64:
			return isXbyak_ ? "ptr [12345+xmm13*2]" : "[12345+xmm13*2]";
		case VM32Y_32:
			return isXbyak_ ? "ptr [ymm4]" : "[ymm4]";
		case VM32Y_64:
			return isXbyak_ ? "ptr [12345+ymm13*2+r13]" : "[12345+ymm13*2+r13]";
		}
		return 0;
	}
	void putSIMPLE() const
	{
		const char tbl[][20] = {
#ifdef XBYAK64
			"cdqe",
			"cqo",
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
//			"lock",
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
			"rdtscp",
			"ud2",
			"wait",
			"fwait",
			"wbinvd",
			"wrmsr",
			"xlatb",

			"popf",
			"pushf",
			"stac",

			"xgetbv",
			"vzeroall",
			"vzeroupper",

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
			"finit",
			"fninit",
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
		put("lea", REG32e|REG16, MEM);
		put("fldcw", MEM);
		put("fstcw", MEM);
	}
	void putJmp() const
	{
#ifdef XBYAK64
		put("jmp", REG64);
		put("call", REG64);
#else
		put("jmp", REG32);
		put("call", REG16|REG32);
#endif
		put("jmp", MEM);
		put("jmp", MEM);
		put("jmp", MEM);
		put("call", MEM|MEM_ONLY_DISP);
#ifndef USE_YASM
		// call(ptr [getCode() + 5]); means to construct the opecode of "call"
		// after calling getCode().
		// Its behavior is same as NASM(MASM). YASM makes different opecode.
		put("call", "getCode() + 5", "$ + 5");
#endif

#ifdef XBYAK64
		put("jmp", "ptr[(void*)0x12345678]", "[0x12345678]");
		put("call", "ptr[(void*)0x12345678]", "[0x12345678]");
#ifdef USE_YASM
		put("jmp", "ptr[rip + 0x12345678]", "[rip+0x12345678]");
		put("call", "ptr[rip + 0x12345678]", "[rip+0x12345678]");
		put("call", "ptr[rip -23]", "[rip-23]");
		put("call", "ptr[rip -23+56]", "[rip-23+56]");
#else
		// bug of yasm?
		if (isXbyak_) {
			puts("{ Label label0;");
			puts("L(label0);");
			puts("pshufb (xmm14, ptr [rip+label0]); dump();");
			puts("}");
		} else {
			puts("label0:");
			puts("pshufb xmm14, [rel label0]");
		}
#endif
#endif
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
			uint64 op1;
			uint64 op2;
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
			put(buf, REG16, REG16|MEM);
			put(buf, REG32, REG32|MEM);
			put(buf, REG64, REG64|MEM);
			sprintf(buf, "set%s", tbl[i]);
			put(buf, REG8|REG8_3|MEM);
		}
	}
	void putReg1() const
	{
		// (REG, REG|MEM)
		{
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
				put(p, REG64|RAX, "192", "192");
				put(p, REG64|RAX, "0x1234", "0x1234");
				put(p, REG32|EAX, IMM8|IMM32|NEG8);
				put(p, REG16|AX, IMM8|IMM16|NEG8|NEG16);
				put(p, REG8|REG8_3|AL, IMM|NEG8);
			}
		}
		{
			const char tbl[][8] = {
				"adcx",
				"adox",
			};
			for (size_t i = 0; i < NUM_OF_ARRAY(tbl); i++) {
				const char *p = tbl[i];
				put(p, REG32, REG32|MEM);
				put(p, REG64, REG64|MEM);
			}
		}
	}
	void putBt() const
	{
		static const char tbl[][16] = {
			"bt",
			"bts",
			"btr",
			"btc",
		};
		for (size_t i = 0; i < NUM_OF_ARRAY(tbl); i++) {
			const char *p = tbl[i];
			put(p, MEM|REG16, REG16);
			put(p, MEM|REG32, REG32);
			put(p, MEM|REG64, REG64);
			put(p, MEM16|REG16, IMM);
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
			reduce 4-byte stack
			push word 2
			reduce 2-byte stack, so I can't support it
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
	void putMov64() const
	{
		const struct {
			const char *a;
			const char *b;
		} tbl[] = {
			{ "0", "0" },
			{ "0x123", "0x123" },
			{ "0x12345678", "0x12345678" },
			{ "0x7fffffff", "0x7fffffff" },
			{ "0xffffffff", "0xffffffff" },
			{ "0x80000000", "0x80000000" },
			{ "2147483648U", "2147483648" },
			{ "0x80000001", "0x80000001" },
			{ "0xffffffffffffffff", "0xffffffffffffffff" },
			{ "-1", "-1" },
			{ "0xffffffff80000000", "0xffffffff80000000" },
			{ "0xffffffff80000001", "0xffffffff80000001" },
			{ "0xffffffff12345678", "0xffffffff12345678" },
		};
		for (size_t i = 0; i < NUM_OF_ARRAY(tbl); i++) {
			put("mov", REG64, tbl[i].a, tbl[i].b);
		}
	}
	// only nasm
	void putMovImm64() const
	{
		put("mov", REG64, "0x1234567890abcdefLL", "0x1234567890abcdef");
		put("mov", REG64, "0x12345678", "0x12345678");
		put("mov", REG64, "0xffffffff12345678LL", "0xffffffff12345678");
		put("mov", REG32e|REG16|REG8|RAX|EAX|AX|AL, IMM);
	}
	void putEtc() const
	{
		{
			const char *p = "ret";
			put(p);
			put(p, IMM);
			p = "mov";
			put(p, EAX|REG32|MEM|MEM_ONLY_DISP, REG32|EAX);
			put(p, REG64|MEM|MEM_ONLY_DISP, REG64|RAX);
			put(p, AX|REG16|MEM|MEM_ONLY_DISP, REG16|AX);
			put(p, AL|REG8|REG8_3|MEM|MEM_ONLY_DISP, REG8|REG8_3|AL);
			put(p, REG32e|REG16|REG8|RAX|EAX|AX|AL, MEM|MEM_ONLY_DISP);
			put(p, MEM32|MEM16|MEM8, IMM);
			put(p, REG64, "0x1234567890abcdefLL", "0x1234567890abcdef");
			put("movbe", REG16|REG32e, MEM);
			put("movbe", MEM, REG16|REG32e);
#ifdef XBYAK64
			put(p, RAX|EAX|AX|AL, "ptr [0x1234567890abcdefLL]", "[qword 0x1234567890abcdef]");
			put(p, "ptr [0x1234567890abcdefLL]", "[qword 0x1234567890abcdef]", RAX|EAX|AX|AL);
			put(p, "qword [rax], 0");
			put(p, "qword [rax], 0x12");
			put(p, "qword [rax], 0x1234");
			put(p, "qword [rax], 0x12345678");
//			put(p, "qword [rax], 0x123456789ab");
			put(p, "qword [rax], 1000000");
			put(p, "rdx, qword [rax]");
#endif
		}
		{
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
		}
#ifdef XBYAK64
		put("movsxd", REG64, REG32|MEM32);
#endif
		put("cmpxchg8b", MEM);
#ifdef XBYAK64
		put("cmpxchg16b", MEM);
#endif
		{
			const char tbl[][8] = {
				"xadd",
				"cmpxchg"
			};
			for (size_t i = 0; i < NUM_OF_ARRAY(tbl); i++) {
				const char *p = tbl[i];
				put(p, REG8|MEM, REG8);
				put(p, REG16|MEM, REG16);
				put(p, REG32|MEM, REG32);
				put(p, REG64|MEM, REG64);
			}
		}

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
			"lzcnt",
			"tzcnt",
			"popcnt",
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
			"aesdec",
			"aesdeclast",
			"aesenc",
			"aesenclast",
			"aesimc",
		};
		for (size_t i = 0; i < NUM_OF_ARRAY(tbl); i++) {
			const char *p = tbl[i];
			put(p, XMM, XMM|MEM);
		}
	}
	void putSSE4_2() const
	{
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
				"pclmulqdq",
				"aeskeygenassist",
			};
			for (size_t i = 0; i < NUM_OF_ARRAY(tbl); i++) {
				const char *p = tbl[i];
				put(p, XMM, XMM|MEM, IMM);
			}
		}
		{
			const char tbl[][16] = {
				"pclmullqlqdq",
				"pclmulhqlqdq",
//				"pclmullqhdq", // QQQ : not supported by nasm/yasm
//				"pclmulhqhdq",
			};
			for (size_t i = 0; i < NUM_OF_ARRAY(tbl); i++) {
				const char *p = tbl[i];
				put(p, XMM, XMM|MEM);
			}
		}
		put("extractps", REG32e|MEM, XMM, IMM);
		put("pextrw", REG32e|MEM, XMM, IMM); // pextrw for REG32 is for MMX2
		put("pextrb", REG32e|MEM, XMM, IMM);
		put("pextrd", REG32|MEM, XMM, IMM);

		put("insertps", XMM, XMM|MEM, IMM);
		put("pinsrb", XMM, REG32|MEM, IMM);
		put("pinsrd", XMM, REG32|MEM, IMM);
		put("movntdqa", XMM, MEM);
		put("crc32", REG32, REG8|REG16|REG32|MEM8|MEM16|MEM32);
		put("crc32", REG64, REG64|REG8|MEM8);
#ifdef XBYAK64
		put("pextrq", REG64|MEM, XMM, IMM);
		put("pinsrq", XMM, REG64|MEM, IMM);
#endif
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
			if (p->mode) put(p->name, STi);
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
	void putAVX1()
	{
		const struct Tbl {
			const char *name;
			bool only_pd_ps;
		} tbl[] = {
			{ "add", false },
			{ "sub", false },
			{ "mul", false },
			{ "div", false },
			{ "max", false },
			{ "min", false },
			{ "and", true },
			{ "andn", true },
			{ "or", true },
			{ "xor", true },

			{ "addsub", true },
			{ "hadd", true },
			{ "hsub", true },
		};
		for (size_t i = 0; i < NUM_OF_ARRAY(tbl); i++) {
			const struct Suf {
				const char *suf;
				bool supportYMM;
			} suf[] = {
				{ "pd", true },
				{ "ps", true },
				{ "sd", false },
				{ "ss", false },
			};
			for (size_t j = 0; j < NUM_OF_ARRAY(suf); j++) {
				if (tbl[i].only_pd_ps && j == 2) break;
				std::string name = std::string("v") + tbl[i].name + suf[j].suf;
				const char *p = name.c_str();
				put(p, XMM, XMM | MEM);
				put(p, XMM, XMM, XMM | MEM);
				if (!suf[j].supportYMM) continue;
				put(p, YMM, YMM | MEM);
				put(p, YMM, YMM, YMM | MEM);
			}
		}
	}
	void putAVX_X_X_XM_omit()
	{
		const struct Tbl {
			const char *name;
			bool supportYMM;
		} tbl[] = {
			{ "vaesenc", false },
			{ "vaesenclast", false },
			{ "vaesdec", false },
			{ "vaesdeclast", false },
			{ "vcvtsd2ss", false },
			{ "vcvtss2sd", false },
			{ "vpacksswb", true },
			{ "vpackssdw", true },
			{ "vpackuswb", true },
			{ "vpackusdw", true },

			{ "vpaddb", true },
			{ "vpaddw", true },
			{ "vpaddd", true },
			{ "vpaddq", true },

			{ "vpaddsb", true },
			{ "vpaddsw", true },

			{ "vpaddusb", true },
			{ "vpaddusw", true },

			{ "vpand", true },
			{ "vpandn", true },
			{ "vpavgb", true },
			{ "vpavgw", true },

			{ "vpcmpeqb", true },
			{ "vpcmpeqw", true },
			{ "vpcmpeqd", true },
			{ "vpcmpeqq", true },

			{ "vpcmpgtb", true },
			{ "vpcmpgtw", true },
			{ "vpcmpgtd", true },
			{ "vpcmpgtq", true },

			{ "vphaddw", true },
			{ "vphaddd", true },
			{ "vphaddsw", true },

			{ "vphsubw", true },
			{ "vphsubd", true },
			{ "vphsubsw", true },
			{ "vpmaddwd", true },
			{ "vpmaddubsw", true },

			{ "vpmaxsb", true },
			{ "vpmaxsw", true },
			{ "vpmaxsd", true },

			{ "vpmaxub", true },
			{ "vpmaxuw", true },
			{ "vpmaxud", true },

			{ "vpminsb", true },
			{ "vpminsw", true },
			{ "vpminsd", true },

			{ "vpminub", true },
			{ "vpminuw", true },
			{ "vpminud", true },

			{ "vpmulhuw", true },
			{ "vpmulhrsw", true },
			{ "vpmulhw", true },
			{ "vpmullw", true },
			{ "vpmulld", true },

			{ "vpmuludq", false },
			{ "vpmuldq", true },

			{ "vpor", true },
			{ "vpsadbw", true },

			{ "vpsignb", true },
			{ "vpsignw", true },
			{ "vpsignd", true },

			{ "vpsllw", false },
			{ "vpslld", false },
			{ "vpsllq", false },

			{ "vpsraw", false },
			{ "vpsrad", false },
			{ "vpsrlw", false },
			{ "vpsrld", false },
			{ "vpsrlq", false },

			{ "vpsubb", true },
			{ "vpsubw", true },
			{ "vpsubd", true },
			{ "vpsubq", true },

			{ "vpsubsb", true },
			{ "vpsubsw", true },

			{ "vpsubusb", true },
			{ "vpsubusw", true },

			{ "vpunpckhbw", true },
			{ "vpunpckhwd", true },
			{ "vpunpckhdq", true },
			{ "vpunpckhqdq", true },

			{ "vpunpcklbw", true },
			{ "vpunpcklwd", true },
			{ "vpunpckldq", true },
			{ "vpunpcklqdq", true },

			{ "vpxor", true },
			{ "vsqrtsd", false },
			{ "vsqrtss", false },

			{ "vunpckhpd", true },
			{ "vunpckhps", true },
			{ "vunpcklpd", true },
			{ "vunpcklps", true },
		};
		for (size_t i = 0; i < NUM_OF_ARRAY(tbl); i++) {
			const Tbl *p = &tbl[i];
			put(p->name, XMM, XMM | MEM);
			put(p->name, XMM, XMM, XMM | MEM);
			if (!p->supportYMM) continue;
			put(p->name, YMM, YMM | MEM);
			put(p->name, YMM, YMM, YMM | MEM);
		}
	}
	void putAVX_X_X_XM_IMM()
	{
		const struct Tbl {
			const char *name;
			bool supportYMM;
		} tbl[] = {
			{ "vblendpd", true },
			{ "vblendps", true },
			{ "vdppd", false },
			{ "vdpps", true },
			{ "vmpsadbw", true },
			{ "vpblendw", true },
			{ "vpblendd", true },
			{ "vroundsd", false },
			{ "vroundss", false },
			{ "vpclmulqdq", false },
			{ "vcmppd", true },
			{ "vcmpps", true },
			{ "vcmpsd", false },
			{ "vcmpss", false },
			{ "vinsertps", false },
			{ "vpalignr", true },
			{ "vshufpd", true },
			{ "vshufps", true },
		};
		for (size_t i = 0; i < NUM_OF_ARRAY(tbl); i++) {
			const Tbl *p = &tbl[i];
			put(p->name, XMM, XMM, XMM | MEM, IMM);
			put(p->name, XMM, XMM | MEM, IMM);
			if (!p->supportYMM) continue;
			put(p->name, YMM, YMM, YMM | MEM, IMM);
			put(p->name, YMM, YMM | MEM, IMM);
		}
	}
	void putAVX_X_XM_IMM()
	{
		const struct Tbl {
			const char *name;
			bool supportYMM;
		} tbl[] = {
			{ "vroundpd", true },
			{ "vroundps", true },
			{ "vpcmpestri", false },
			{ "vpcmpestrm", false },
			{ "vpcmpistri", false },
			{ "vpcmpistrm", false },
			{ "vpermilpd", true },
			{ "vpermilps", true },
			{ "vaeskeygenassist", false },
			{ "vpshufd", true },
			{ "vpshufhw", true },
			{ "vpshuflw", true },
		};
		for (size_t i = 0; i < NUM_OF_ARRAY(tbl); i++) {
			const Tbl *p = &tbl[i];
			put(p->name, XMM, XMM | MEM, IMM);
			if (!p->supportYMM) continue;
			put(p->name, YMM, YMM | MEM, IMM);
		}
	}
	void putAVX_X_X_XM()
	{
		const struct Tbl {
			const char *name;
			bool supportYMM;
		} tbl[] = {
			{ "vpermilpd", true },
			{ "vpermilps", true },
			{ "vpshufb", true },

			{ "vpsllvd", true },
			{ "vpsllvq", true },
			{ "vpsravd", true },
			{ "vpsrlvd", true },
			{ "vpsrlvq", true },
		};
		for (size_t i = 0; i < NUM_OF_ARRAY(tbl); i++) {
			const Tbl *p = &tbl[i];
			put(p->name, XMM, XMM, XMM | MEM);
			if (!p->supportYMM) continue;
			put(p->name, YMM, YMM, YMM | MEM);
		}
	}
	void putAVX_X_XM()
	{
		const struct Tbl {
			const char *name;
			bool supportYMM;
		} tbl[] = {
			{ "vaesimc", false },
			{ "vtestps", true },
			{ "vtestpd", true },
			{ "vcomisd", false },
			{ "vcomiss", false },
			{ "vcvtdq2ps", true },
			{ "vcvtps2dq", true },
			{ "vcvttps2dq", true },
			{ "vmovapd", true },
			{ "vmovaps", true },
			{ "vmovddup", true },
			{ "vmovdqa", true },
			{ "vmovdqu", true },
			{ "vmovupd", true },
			{ "vmovups", true },

			{ "vpabsb", true },
			{ "vpabsw", true },
			{ "vpabsd", true },
			{ "vphminposuw", false },

			{ "vpmovsxbw", false },
			{ "vpmovsxbd", false },
			{ "vpmovsxbq", false },
			{ "vpmovsxwd", false },
			{ "vpmovsxwq", false },
			{ "vpmovsxdq", false },

			{ "vpmovzxbw", false },
			{ "vpmovzxbd", false },
			{ "vpmovzxbq", false },
			{ "vpmovzxwd", false },
			{ "vpmovzxwq", false },
			{ "vpmovzxdq", false },

			{ "vptest", false },
			{ "vrcpps", true },
			{ "vrcpss", false },

			{ "vrsqrtps", true },
			{ "vrsqrtss", false },

			{ "vsqrtpd", true },
			{ "vsqrtps", true },
			{ "vucomisd", false },
			{ "vucomiss", false },
		};
		for (size_t i = 0; i < NUM_OF_ARRAY(tbl); i++) {
			const Tbl *p = &tbl[i];
			put(p->name, XMM, XMM | MEM);
			if (!p->supportYMM) continue;
			put(p->name, YMM, YMM | MEM);
		}
	}
	void putAVX_Y_XM()
	{
		const char *tbl[] = {
			"vpmovsxbw",
			"vpmovsxbd",
			"vpmovsxbq",
			"vpmovsxwd",
			"vpmovsxwq",
			"vpmovsxdq",
			"vpmovzxbw",
			"vpmovzxbd",
			"vpmovzxbq",
			"vpmovzxwd",
			"vpmovzxwq",
			"vpmovzxdq",
		};
		for (size_t i = 0; i < NUM_OF_ARRAY(tbl); i++) {
			const char *name = tbl[i];
			put(name, YMM, XMM);
		}
	}
	void putAVX_M_X()
	{
		const struct Tbl {
			const char *name;
			bool supportYMM;
		} tbl[] = {
			{ "vmovapd", true },
			{ "vmovaps", true },
			{ "vmovdqa", true },
			{ "vmovdqu", true },
			{ "vmovupd", true },
			{ "vmovups", true },
		};
		for (size_t i = 0; i < NUM_OF_ARRAY(tbl); i++) {
			const Tbl *p = &tbl[i];
			put(p->name, MEM, XMM);
			if (!p->supportYMM) continue;
			put(p->name, MEM, YMM);
		}
	}
	void putAVX_X_X_IMM_omit()
	{
		const struct Tbl {
			const char *name;
			bool support_Y_Y_X;
		} tbl[] = {
			{ "vpslldq", false },
			{ "vpsrldq", false },
			{ "vpsllw", true },
			{ "vpslld", true },
			{ "vpsllq", true },
			{ "vpsraw", true },
			{ "vpsrad", true },
			{ "vpsrlw", true },
			{ "vpsrld", true },
			{ "vpsrlq", true },
		};
		for (size_t i = 0; i < NUM_OF_ARRAY(tbl); i++) {
			const Tbl& p = tbl[i];
			put(p.name, XMM, XMM, IMM);
			put(p.name, YMM, YMM, IMM);
			put(p.name, YMM, IMM);
			if (p.support_Y_Y_X) {
				put(p.name, YMM, YMM, XMM);
			}
		}
	}
	void putFMA()
	{
		const struct Tbl {
			const char *name;
			bool supportYMM;
		} tbl[] = {
			{ "vfmadd", true },
			{ "vfmadd", false },
			{ "vfmaddsub", true },
			{ "vfmsubadd", true },
			{ "vfmsub", true },
			{ "vfmsub", false },
			{ "vfnmadd", true },
			{ "vfnmadd", false },
			{ "vfnmsub", true },
			{ "vfnmsub", false },
		};
		for (size_t i = 0; i < NUM_OF_ARRAY(tbl); i++) {
			const Tbl& p = tbl[i];
			const struct Ord {
				const char *name;
			} ord[] = {
				{ "132" },
				{ "213" },
				{ "231" },
			};
			for (size_t j = 0; j < NUM_OF_ARRAY(ord); j++) {
				const char suf[][2][8] = {
					{ "pd", "ps" },
					{ "sd", "ss" },
				};
				for (size_t k = 0; k < 2; k++) {
					std::string name = std::string(p.name) + ord[j].name + suf[p.supportYMM ? 0 : 1][k];
					const char *q = name.c_str();
					put(q, XMM, XMM, XMM | MEM);
					if (!p.supportYMM) continue;
					put(q, YMM, YMM, YMM | MEM);
				}
			}
		}
	}
	void putAVX2()
	{
		put("vextractps", REG32 | MEM, XMM, IMM);
		put("vldmxcsr", MEM);
		put("vstmxcsr", MEM);
		put("vmaskmovdqu", XMM, XMM);

		put("vmovd", XMM, REG32 | MEM);
		put("vmovd", REG32 | MEM, XMM);

		put("vmovq", XMM, XMM | MEM);
		put("vmovq", MEM, XMM);

		put("vmovhlps", XMM, XMM);
		put("vmovhlps", XMM, XMM, XMM);
		put("vmovlhps", XMM, XMM);
		put("vmovlhps", XMM, XMM, XMM);

		{
			const char tbl[][16] = {
				"vmovhpd",
				"vmovhps",
				"vmovlpd",
				"vmovlps",
			};
			for (size_t i = 0; i < NUM_OF_ARRAY(tbl); i++) {
				put(tbl[i], XMM, XMM, MEM);
				put(tbl[i], XMM, MEM);
				put(tbl[i], MEM, XMM);
			}
		}
		put("vmovmskpd", REG32e, XMM | YMM);
		put("vmovmskps", REG32e, XMM | YMM);

		put("vmovntdq", MEM, XMM | YMM);
		put("vmovntpd", MEM, XMM | YMM);
		put("vmovntdqa", XMM | YMM, MEM);

		{
			const char tbl[][8] = { "vmovsd", "vmovss" };
			for (size_t i = 0; i < NUM_OF_ARRAY(tbl); i++) {
				put(tbl[i], XMM, XMM, XMM);
				put(tbl[i], XMM, XMM | MEM);
				put(tbl[i], MEM, XMM);
			}
		}
		put("vpextrb", REG32e|MEM, XMM, IMM);
		put("vpextrd", REG32|MEM, XMM, IMM);

		for (int i = 0; i < 3; i++) {
			const char tbl[][8] = { "vpinsrb", "vpinsrw", "vpinsrd" };
			put(tbl[i], XMM, XMM, REG32|MEM, IMM);
			put(tbl[i], XMM, REG32|MEM, IMM);
		}

		put("vpmovmskb", REG32e, XMM|YMM);

		{
			const struct Tbl {
				const char *name;
				bool supportYMM;
			} tbl[] = {
				{ "vblendvpd", true },
				{ "vblendvps", true },
				{ "vpblendvb", true },
			};
			for (size_t i = 0; i < NUM_OF_ARRAY(tbl); i++) {
				const Tbl& p = tbl[i];
				put(p.name, XMM, XMM, XMM | MEM, XMM);
				put(p.name, XMM, XMM | MEM, XMM);
				if (!p.supportYMM) continue;
				put(p.name, YMM, YMM, YMM | MEM, YMM);
				put(p.name, YMM, YMM | MEM, YMM);
			}
		}
		// cvt
		{
			put("vcvtss2si", REG32e, XMM | MEM);
			put("vcvttss2si", REG32e, XMM | MEM);
			put("vcvtsd2si", REG32e, XMM | MEM);
			put("vcvttsd2si", REG32e, XMM | MEM);

			put("vcvtsi2ss", XMM, XMM, REG32e | MEM);
			put("vcvtsi2ss", XMM, REG32e | MEM);

			put("vcvtsi2sd", XMM, XMM, REG32e | MEM);
			put("vcvtsi2sd", XMM, REG32e | MEM);

			put("vcvtps2pd", XMM | YMM, XMM | MEM);
			put("vcvtdq2pd", XMM | YMM, XMM | MEM);

			put("vcvtpd2ps", XMM, XMM | YMM | MEM);
			put("vcvtpd2dq", XMM, XMM | YMM | MEM);
			put("vcvttpd2dq", XMM, XMM | YMM | MEM);

			put("vcvtph2ps", XMM | YMM, XMM | MEM);
			put("vcvtps2ph", XMM | MEM, XMM | YMM, IMM8);
		}
#ifdef XBYAK64
		put("vmovq", XMM, REG64);
		put("vmovq", REG64, XMM);

		put("vpextrq", REG64|MEM, XMM, IMM);

		put("vpinsrq", XMM, XMM, REG64|MEM, IMM);
		put("vpinsrq", XMM, REG64|MEM, IMM);

#endif
	}
	void putFMA2()
	{
#ifndef USE_YASM
		put("vmaskmovps", XMM, XMM, MEM);
		put("vmaskmovps", YMM, YMM, MEM);

		put("vmaskmovpd", YMM, YMM, MEM);
		put("vmaskmovpd", XMM, XMM, MEM);

		put("vmaskmovps", MEM, XMM, XMM);
		put("vmaskmovpd", MEM, XMM, XMM);

		put("vbroadcastf128", YMM, MEM);
		put("vbroadcasti128", YMM, MEM);
		put("vbroadcastsd", YMM, XMM|MEM);
		{
			const char *tbl[] = {
				"vbroadcastss",
				"vpbroadcastb",
				"vpbroadcastw",
				"vpbroadcastd",
				"vpbroadcastq",
			};
			for (size_t i = 0; i < NUM_OF_ARRAY(tbl); i++) {
				put(tbl[i], XMM | YMM, XMM|MEM);
			}
		}

		put("vinsertf128", YMM, YMM, XMM | MEM, IMM8);
		put("vinserti128", YMM, YMM, XMM | MEM, IMM8);
		put("vperm2f128", YMM, YMM, YMM | MEM, IMM8);
		put("vperm2i128", YMM, YMM, YMM | MEM, IMM8);

		{
			const char *tbl[] = {
				"vpmaskmovd", "vpmaskmovq"
			};
			for (size_t i = 0; i < NUM_OF_ARRAY(tbl); i++) {
				const char *name = tbl[i];
				put(name, XMM, XMM, MEM);
				put(name, YMM, YMM, MEM);
				put(name, MEM, XMM, XMM);
				put(name, MEM, YMM, YMM);
			}
		}
		{
			const char *tbl[] = {
				"vpermd", "vpermps",
			};
			for (size_t i = 0; i < NUM_OF_ARRAY(tbl); i++) {
				const char *name = tbl[i];
				put(name, YMM, YMM, YMM | MEM);
			}
		}
		{
			const char *tbl[] = {
				"vpermq", "vpermpd",
			};
			for (size_t i = 0; i < NUM_OF_ARRAY(tbl); i++) {
				const char *name = tbl[i];
				put(name, YMM, YMM | MEM, IMM8);
			}
		}
#else
		put("vextractf128", XMM | MEM, YMM, IMM);
		put("vextracti128", XMM | MEM, YMM, IMM);
		put("vmaskmovps", MEM, YMM, YMM);
		put("vmaskmovpd", MEM, YMM, YMM);
		put("vlddqu", XMM | YMM, MEM);

		put("vmovshdup", XMM, XMM | MEM);
		put("vmovshdup", YMM, YMM | MEM);
		put("vmovsldup", XMM, XMM | MEM);
		put("vmovsldup", YMM, YMM | MEM);

		// QQQ:nasm is wrong
		put("vpcmpeqq", XMM, XMM | MEM);
		put("vpcmpeqq", XMM, XMM, XMM | MEM);
		put("vpcmpgtq", XMM, XMM | MEM);
		put("vpcmpgtq", XMM, XMM, XMM | MEM);

		put("vpextrw", REG32e | MEM, XMM, IMM); // nasm iw wrong?
		put("vmovntps", MEM, XMM | YMM); // nasm error
#endif
	}
	void putCmp()
	{
		const char pred[32][16] = {
			"eq", "lt", "le", "unord", "neq", "nlt", "nle", "ord",
			"eq_uq", "nge", "ngt", "false", "neq_oq", "ge", "gt",
			"true", "eq_os", "lt_oq", "le_oq", "unord_s", "neq_us", "nlt_uq", "nle_uq", "ord_s",
			"eq_us", "nge_uq", "ngt_uq", "false_os", "neq_os", "ge_oq", "gt_oq", "true_us"
		};
		const char suf[][4] = { "pd", "ps", "sd", "ss" };
		for (int i = 0; i < 4; i++) {
			for (int j = 0; j < 32; j++) {
				if (j < 8) {
					put((std::string("cmp") + pred[j] + suf[i]).c_str(), XMM, XMM | MEM);
				}
				std::string str = std::string("vcmp") + pred[j] + suf[i];
				const char *p = str.c_str();
				put(p, XMM, XMM | MEM);
				put(p, XMM, XMM, XMM | MEM);
				if (i >= 2) continue;
				put(p, YMM, YMM | MEM);
				put(p, YMM, YMM, YMM | MEM);
			}
		}
	}
	void putRip()
	{
		const char tbl[][2][64] = {
			{ "mov(byte [rip - 10], 3);dump();", "mov byte [rip - 10], 3" },
			{ "mov(word [rip - 10], 3);dump();", "mov word [rip - 10], 3" },
			{ "mov(dword[rip - 10], 3);dump();", "mov dword [rip - 10], 3" },
			{ "mov(qword [rip - 10], 3);dump();", "mov qword [rip - 10], 3" },
			{ "mov(ptr [rip - 10], al);dump();", "mov byte [rip - 10], al" },
			{ "mov(ptr [rip - 10], ax);dump();", "mov word [rip - 10], ax" },
			{ "mov(ptr [rip - 10], eax);dump();", "mov dword [rip - 10], eax" },
			{ "mov(ptr [rip - 10], rax);dump();", "mov qword [rip - 10], rax" },
		};
		for (size_t i = 0; i < NUM_OF_ARRAY(tbl); i++) {
			puts(tbl[i][isXbyak_ ? 0 : 1]);
		}
	}
public:
	Test(bool isXbyak)
		: isXbyak_(isXbyak)
		, funcNum_(1)
	{
		if (!isXbyak_) return;
		printf("%s",
			"    void gen0()\n"
			"    {\n");
	}
	/*
		gcc and vc give up to compile this source,
		so I split functions.
	*/
	void separateFunc()
	{
		if (!isXbyak_) return;
		printf(
			"    }\n"
			"    void gen%d()\n"
			"    {\n", funcNum_++);
	}
	~Test()
	{
		if (!isXbyak_) return;
		printf("%s",
			"    }\n"
			"    void gen()\n"
			"    {\n");
		for (int i = 0; i < funcNum_; i++) {
			printf(
			"        gen%d();\n", i);
		}
		printf(
			"    }\n");
	}
	void putGprR_R_RM()
	{
		const char *tbl[] = {
			"andn",
			"mulx",
			"pdep",
			"pext",
		};
		for (size_t i = 0; i < NUM_OF_ARRAY(tbl); i++) {
			const char *name = tbl[i];
			put(name, REG32, REG32, REG32 | MEM);
#ifdef XBYAK64
			put(name, REG64, REG64, REG64 | MEM);
#endif
		}
	}
	void putGprR_RM_R()
	{
		const char *tbl[] = {
			"bextr",
			"bzhi",
			"sarx",
			"shlx",
			"shrx",
		};
		for (size_t i = 0; i < NUM_OF_ARRAY(tbl); i++) {
			const char *name = tbl[i];
			put(name, REG32, REG32 | MEM, REG32);
#ifdef XBYAK64
			put(name, REG64, REG64 | MEM, REG64);
#endif
		}
	}
	void putGprR_RM()
	{
		const char *tbl[] = {
			"blsi",
			"blsmsk",
			"blsr",
		};
		for (size_t i = 0; i < NUM_OF_ARRAY(tbl); i++) {
			const char *name = tbl[i];
			put(name, REG32, REG32 | MEM);
#ifdef XBYAK64
			put(name, REG64, REG64 | MEM);
#endif
		}
	}
	void putGprOtherwise()
	{
		put("rdrand", REG16 | REG32e);
		put("rdseed", REG16 | REG32e);
		put("rorx", REG32, REG32 | MEM, IMM8);
#ifdef XBYAK64
		put("rorx", REG64, REG64 | MEM, IMM8);
#endif
	}
	void putGather()
	{
		const int y_vx_y = 0;
		const int y_vy_y = 1;
		const int x_vy_x = 2;
		const struct Tbl {
			const char *name;
			int mode;
		} tbl[] = {
			{ "vgatherdpd", y_vx_y },
			{ "vgatherqpd", y_vy_y },
			{ "vgatherdps", y_vy_y },
			{ "vgatherqps", x_vy_x },
			{ "vpgatherdd", y_vy_y },
			{ "vpgatherqd", x_vy_x },
			{ "vpgatherdq", y_vx_y },
			{ "vpgatherqq", y_vy_y },
		};
		for (size_t i = 0; i < NUM_OF_ARRAY(tbl); i++) {
			const Tbl& p = tbl[i];
			const char *name = p.name;
			put(name, XMM, VM32X, XMM);
			switch (p.mode) {
			case y_vx_y:
				put(name, YMM, VM32X, YMM);
				break;
			case y_vy_y:
				put(name, YMM, VM32Y, YMM);
				break;
			case x_vy_x:
				put(name, XMM, VM32Y, XMM);
				break;
			default:
				printf("ERR mode=%d\n", p.mode);
				exit(1);
			}
		}
	}
	void putGath(const std::string& vsib)
	{
		std::string x = "xmm1, ";
		std::string a = std::string("[") + vsib + "], xmm3";
		put("vgatherdpd", (x + "ptr" + a).c_str(), (x + a).c_str());
	}

	void putGatherAll()
	{
		const char *xmmTbl[] = {
			"xmm2",
			"xmm4",
			"xmm2*1",
			"xmm2*4",
		};
		for (size_t i = 0; i < NUM_OF_ARRAY(xmmTbl); i++) {
			std::string s = xmmTbl[i];
			putGath(s);
			putGath(s + "+3");
			putGath(s + "+eax");
			putGath("3+" + s);
			putGath("eax+" + s);
		}
		for (size_t i = 0; i < NUM_OF_ARRAY(xmmTbl); i++) {
			int ord[] = { 0, 1, 2 };
			do {
				std::string s;
				for (int j = 0; j < 3; j++) {
					if (j > 0) s += '+';
					switch (ord[j]) {
					case 0: s += xmmTbl[i]; break;
					case 1: s += "123"; break;
					case 2: s += "ebp"; break;
					}
				}
				putGath(s);
			} while (std::next_permutation(ord, ord + 3));
		}
	}
	void putSeg()
	{
		const char *segTbl[] = {
			"es",
			"cs",
			"ss",
			"ds",
			"fs",
			"gs",
		};
		for (size_t i = 0; i < NUM_OF_ARRAY(segTbl); i++) {
			const char *seg = segTbl[i];
			const char *op1Tbl[] = {
				"ax",
				"edx",
				(isXbyak_ ? "ptr [eax]" : "[eax]"),
#ifdef XBYAK64
				"r9",
#endif
			};
			for (size_t j = 0; j < NUM_OF_ARRAY(op1Tbl); j++) {
				const char *op1 = op1Tbl[j];
				if (isXbyak_) {
					printf("mov(%s, %s); dump();\n", op1, seg);
					printf("mov(%s, %s); dump();\n", seg, op1);
				} else {
					printf("mov %s, %s\n", op1, seg);
					printf("mov %s, %s\n", seg, op1);
				}
			}
		}
		{
			const char *segTbl[] = {
#ifdef XBYAK32
				"es",
				"ss",
				"ds",
#endif
				"fs",
				"gs",
			};
			for (size_t i = 0; i < NUM_OF_ARRAY(segTbl); i++) {
				const char *seg = segTbl[i];
				if (isXbyak_) {
					printf("push(%s); dump();\n", seg);
					printf("pop(%s); dump();\n", seg);
				} else {
					printf("push %s\n", seg);
					printf("pop %s\n", seg);
				}
			}
		}
	}
	void put()
	{
#ifdef USE_AVX

		putFMA2();

#ifdef USE_YASM
		putGprR_R_RM();
		putGprR_RM_R();
		putGprR_RM();
		putGprOtherwise();
		putGather();
		putGatherAll();
#else
		putAVX1();
		putAVX2();
		putAVX_X_X_XM_omit();
		putAVX_X_X_XM_IMM();
		putAVX_X_XM_IMM();
		putAVX_X_X_XM();
		putAVX_X_XM();
		putAVX_M_X();
		putAVX_X_X_IMM_omit();
		putAVX_Y_XM();
		putFMA();
#endif

#else // USE_AVX

		putJmp();

#ifdef USE_YASM

		putSSSE3();
		putSSE4_1();
		separateFunc();
		putSSE4_2();
		putSeg(); // same behavior as yasm for mov rax, cx
#else
		putSIMPLE();
		putReg1();
		putBt();
		putRorM();
		separateFunc();
		putPushPop();
		putTest();
		separateFunc();
		putEtc();
		putShift();
		putShxd();

		separateFunc();

		putBs();
		putMMX1();
		putMMX2();
		separateFunc();
		putMMX3();
		putMMX4();
		putMMX5();
		separateFunc();
		putXMM1();
		putXMM2();
		putXMM3();
		putXMM4();
		separateFunc();
		putCmov();
		putFpuMem16_32();
		putFpuMem32_64();
		separateFunc();
		putFpuMem16_32_64();
		put("clflush", MEM); // current nasm is ok
		putFpu();
		putFpuFpu();
		putCmp();
#endif

#ifdef XBYAK64

#ifdef USE_YASM
		putRip();
#else
		putMov64();
		putMovImm64();
#endif

#endif // XBYAK64

#endif // USE_AVX
	}
};

int main(int argc, char *[])
{
	Test test(argc > 1);
	test.put();
}
