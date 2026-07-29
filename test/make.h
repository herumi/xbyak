/*
	common part of make_nm.cpp and make_512.cpp
	usage:
	#include "make.h"                // top level : common headers and bit-flag constants
	<file specific constants>
	class Test {
	#define MAKE_H_MEMBERS
	#include "make.h"                // members of class Test
	...
	};
*/
#ifndef MAKE_H_MEMBERS

#include <stdio.h>
#include "xbyak/xbyak.h"
#include <stdlib.h>
#include <string.h>
#include "cybozu/inttype.hpp"
#define NUM_OF_ARRAY(x) (sizeof(x) / sizeof(x[0]))

using namespace Xbyak;

const int bitEnd = 64;

/*
	bit-flag constants shared by make_nm.cpp and make_512.cpp
	bits 0, 9, 10, 11, 19, 20, 22, 23, 32, 36, 37 and the derived
	constants XMM, REG64, REG32e are file specific
*/
const uint64_t _XMM = 1ULL << 1;
const uint64_t _MEM = 1ULL << 2;
const uint64_t _REG32 = 1ULL << 3;
const uint64_t EAX = 1ULL << 4;
const uint64_t IMM32 = 1ULL << 5;
const uint64_t IMM8 = 1ULL << 6;
const uint64_t _REG8 = 1ULL << 7;
const uint64_t _REG16 = 1ULL << 8;
const uint64_t AX = 1ULL << 12;
const uint64_t AL = 1ULL << 13;
const uint64_t IMM_1 = 1ULL << 14;
const uint64_t MEM8 = 1ULL << 15;
const uint64_t MEM16 = 1ULL << 16;
const uint64_t MEM32 = 1ULL << 17;
const uint64_t MEM_ONLY_DISP = 1ULL << 21;
const uint64_t _YMM = 1ULL << 24;
const uint64_t VM32X_32 = 1ULL << 39;
const uint64_t VM32X_64 = 1ULL << 40;
const uint64_t VM32Y_32 = 1ULL << 41;
const uint64_t VM32Y_64 = 1ULL << 42;
#ifdef XBYAK64
const uint64_t _MEMe = 1ULL << 25;
const uint64_t REG32_2 = 1ULL << 26; // r8d, ...
const uint64_t REG16_2 = 1ULL << 27; // r8w, ...
const uint64_t REG8_2 = 1ULL << 28; // r8b, ...
const uint64_t REG8_3 = 1ULL << 29; // spl, ...
const uint64_t _REG64 = 1ULL << 30; // rax, ...
const uint64_t _REG64_2 = 1ULL << 31; // r8, ...
const uint64_t _XMM2 = 1ULL << 33;
const uint64_t _YMM2 = 1ULL << 34;
const uint64_t VM32X = VM32X_32 | VM32X_64;
const uint64_t VM32Y = VM32Y_32 | VM32Y_64;
#else
const uint64_t _MEMe = 0;
const uint64_t REG32_2 = 0;
const uint64_t REG16_2 = 0;
const uint64_t REG8_2 = 0;
const uint64_t REG8_3 = 0;
const uint64_t _REG64 = 0;
const uint64_t _REG64_2 = 0;
const uint64_t _XMM2 = 0;
const uint64_t _YMM2 = 0;
const uint64_t VM32X = VM32X_32;
const uint64_t VM32Y = VM32Y_32;
#endif
const uint64_t REG32 = _REG32 | REG32_2 | EAX;
const uint64_t REG16 = _REG16 | REG16_2 | AX;
const uint64_t REG8 = _REG8 | REG8_2|AL;
const uint64_t MEM = _MEM | _MEMe;
const uint64_t MEM64 = 1ULL << 35;
const uint64_t IMM_2 = 1ULL << 38;
const uint64_t IMM = IMM_1 | IMM_2;
const uint64_t YMM = _YMM | _YMM2;
const uint64_t K = 1ULL << 43;
const uint64_t _ZMM = 1ULL << 44;
const uint64_t _ZMM2 = 1ULL << 45;
#ifdef XBYAK64
const uint64_t ZMM = _ZMM | _ZMM2;
const uint64_t _YMM3 = 1ULL << 46;
#else
const uint64_t ZMM = _ZMM;
const uint64_t _YMM3 = 0;
#endif
const uint64_t K2 = 1ULL << 47;
const uint64_t ZMM_SAE = 1ULL << 48;
const uint64_t ZMM_ER = 1ULL << 49;
#ifdef XBYAK64
const uint64_t _XMM3 = 1ULL << 50;
#else
const uint64_t _XMM3 = 0;
#endif
const uint64_t XMM_SAE = 1ULL << 51;
#ifdef XBYAK64
const uint64_t XMM_KZ = 1ULL << 52;
const uint64_t YMM_KZ = 1ULL << 53;
const uint64_t ZMM_KZ = 1ULL << 54;
#else
const uint64_t XMM_KZ = 0;
const uint64_t YMM_KZ = 0;
const uint64_t ZMM_KZ = 0;
#endif
const uint64_t MEM_K = 1ULL << 55;
const uint64_t M_1to2 = 1ULL << 56;
const uint64_t M_1to4 = 1ULL << 57;
const uint64_t M_1to8 = 1ULL << 58;
const uint64_t M_1to16 = 1ULL << 59;
const uint64_t XMM_ER = 1ULL << 60;
const uint64_t M_xword = 1ULL << 61;
const uint64_t M_yword = 1ULL << 62;
const uint64_t MY_1to4 = 1ULL << 18;

const uint64_t NOPARA = 1ULL << (bitEnd - 1);

#else // MAKE_H_MEMBERS

	Test(const Test&);
	void operator=(const Test&);
	const bool isXbyak_;
	int funcNum_;

	// check all op1, op2, op3
	void put(const std::string& nm, uint64_t op1 = NOPARA, uint64_t op2 = NOPARA, uint64_t op3 = NOPARA, uint64_t op4 = NOPARA) const
	{
		for (int i = 0; i < bitEnd; i++) {
			if ((op1 & (1ULL << i)) == 0) continue;
			for (int j = 0; j < bitEnd; j++) {
				if ((op2 & (1ULL << j)) == 0) continue;
				for (int k = 0; k < bitEnd; k++) {
					if ((op3 & (1ULL << k)) == 0) continue;
					for (int s = 0; s < bitEnd; s++) {
						if ((op4 & (1ULL << s)) == 0) continue;
						printf("%s ", nm.c_str());
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
	void put(const char *nm, uint64_t op, const char *xbyak, const char *nasm) const
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
	void put(const char *nm, const char *xbyak, const char *nasm = 0, uint64_t op = NOPARA) const
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
#ifdef USE_AVX512
	void putOpmask()
	{
		{
			const char *tbl[] = {
				"kadd",
				"kand",
				"kandn",
				"kor",
				"kxnor",
				"kxor",
			};
			for (size_t i = 0; i < NUM_OF_ARRAY(tbl); i++) {
				std::string name = tbl[i];
				put(name + "b", K, K, K);
				put(name + "w", K, K, K);
				put(name + "q", K, K, K);
				put(name + "d", K, K, K);
			}
			put("kunpckbw", K, K, K);
			put("kunpckwd", K, K, K);
			put("kunpckdq", K, K, K);
		}
		{
			const char *tbl[] = {
				"knot",
				"kortest",
				"ktest",
			};
			for (size_t i = 0; i < NUM_OF_ARRAY(tbl); i++) {
				std::string name = tbl[i];
				put(name + "b", K, K);
				put(name + "w", K, K);
				put(name + "q", K, K);
				put(name + "d", K, K);
			}
		}
		{
			const char *tbl[] = {
				"kshiftl",
				"kshiftr",
			};
			for (size_t i = 0; i < NUM_OF_ARRAY(tbl); i++) {
				std::string name = tbl[i];
				put(name + "b", K, K, IMM8);
				put(name + "w", K, K, IMM8);
				put(name + "q", K, K, IMM8);
				put(name + "d", K, K, IMM8);
			}
		}
		put("kmovw", K, K | MEM | REG32);
		put("kmovq", K, K | MEM);
		put("kmovb", K, K | MEM | REG32);
		put("kmovd", K, K | MEM | REG32);

		put("kmovw", MEM | REG32, K);
		put("kmovq", MEM, K);
		put("kmovb", MEM | REG32, K);
		put("kmovd", MEM | REG32, K);
#ifdef XBYAK64
		put("kmovq", K, REG64);
		put("kmovq", REG64, K);
#endif
	}
	void put_vaddpd(const char *r1, const char *r2, const char *r3, int kIdx = 0, bool z = false, int sae = 0)
	{
		std::string modifier;
		char pk[16] = "";
		const char *pz = "";
		const char *saeTblXbyak[] = { "", "|T_rn_sae", "|T_rd_sae", "|T_ru_sae", "|T_rz_sae" };
		const char *saeTblNASM[] = { "", ",{rn-sae}", ",{rd-sae}", ",{ru-sae}", ",{rz-sae}" };
		if (isXbyak_) {
			if (kIdx) CYBOZU_SNPRINTF(pk, sizeof(pk), "|k%d", kIdx);
			if (z) pz = "|T_z";
			printf("vaddpd(%s%s%s, %s, %s%s); dump();\n", r1, pk, pz, r2, r3, saeTblXbyak[sae]);
		} else {
			if (kIdx) CYBOZU_SNPRINTF(pk, sizeof(pk), "{k%d}", kIdx);
			if (z && kIdx) pz = "{z}";
			printf("vaddpd %s%s%s, %s, %s%s\n", r1, pk, pz, r2, r3, saeTblNASM[sae]);
		}
	}
	void putCombi()
	{
		const char *xTbl[] = {
			"xmm2",
#ifdef XBYAK64
			"xmm8", "xmm31"
#else
			"xmm5", "xmm6"
#endif
		};
		const char *yTbl[] = {
			"ymm0",
#ifdef XBYAK64
			"ymm15", "ymm31"
#else
			"ymm4", "ymm2"
#endif
		};
		const char *zTbl[] = {
			"zmm1",
#ifdef XBYAK64
			"zmm9", "zmm30"
#else
			"zmm3", "zmm7"
#endif
		};
		const size_t N = NUM_OF_ARRAY(zTbl);
		for (size_t i = 0; i < N; i++) {
			for (size_t j = 0; j < N; j++) {
				separateFunc();
				for (size_t k = 0; k < N; k++) {
#ifdef XBYAK64
					for (int kIdx = 0; kIdx < 8; kIdx++) {
						put_vaddpd(xTbl[i], xTbl[j], xTbl[k], kIdx);
						put_vaddpd(yTbl[i], yTbl[j], yTbl[k], kIdx);
						for (int z = 0; z < 2; z++) {
							for (int sae = 0; sae < 5; sae++) {
								put_vaddpd(zTbl[i], zTbl[j], zTbl[k], kIdx, z == 1, sae);
							}
						}
					}
#else
					put_vaddpd(xTbl[i], xTbl[j], xTbl[k]);
					put_vaddpd(yTbl[i], yTbl[j], yTbl[k]);
					for (int sae = 0; sae < 5; sae++) {
						put_vaddpd(zTbl[i], zTbl[j], zTbl[k], sae);
					}
#endif
				}
			}
		}
		put("vaddpd", XMM, XMM, _MEM);
		put("vaddpd", YMM, YMM, _MEM);
		put("vaddpd", ZMM, ZMM, _MEM);
	}
	void putBroadcastSub(int idx, int disp)
	{
#ifdef XBYAK64
		const char *a = "rax";
#else
		const char *a = "eax";
#endif
		if (isXbyak_) {
			printf("vaddpd(zmm%d, zmm1, ptr_b[%s+%d]);dump();\n", idx, a, disp);
			printf("vaddpd(ymm%d, ymm1, ptr_b[%s+%d]);dump();\n", idx, a, disp);
			printf("vaddpd(xmm%d, xmm1, ptr_b[%s+%d]);dump();\n", idx, a, disp);
		} else {
			printf("vaddpd zmm%d, zmm1, [%s+%d]{1to8}\n", idx, a, disp);
			printf("vaddpd ymm%d, ymm1, [%s+%d]{1to4}\n", idx, a, disp);
			printf("vaddpd xmm%d, xmm1, [%s+%d]{1to2}\n", idx, a, disp);
		}
	}
#endif // USE_AVX512

#endif // MAKE_H_MEMBERS
