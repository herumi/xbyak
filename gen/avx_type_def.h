	// @@@begin of avx_type_def.h
	enum AVXtype {
		T_NONE = 0,
		// low 3 bit
		T_N1 = 1,
		T_N2 = 2,
		T_N4 = 3,
		T_N8 = 4,
		T_N16 = 5,
		T_N32 = 6,
		T_NX_MASK = 7,
		T_DUP = T_NX_MASK,//1 << 4, // N = (8, 32, 64)
		T_N_VL = 1 << 3, // N * (1, 2, 4) for VL
		T_VEX = 1 << 4,
		T_66 = 1 << 5, // pp = 1
		T_F3 = 1 << 6, // pp = 2
		T_F2 = T_66 | T_F3, // pp = 3
		T_ER_R = 1 << 7, // reg{er}
		T_0F = 1 << 8,
		T_0F38 = 1 << 9,
		T_0F3A = 1 << 10,
		T_L0 = 1 << 11,
		T_L1 = 1 << 12,
		T_W0 = 1 << 13,
		T_W1 = 1 << 14,
		T_EW0 = 1 << 15,
		T_EW1 = 1 << 16,
		T_YMM = 1 << 17, // support YMM, ZMM
		T_EVEX = 1 << 18,
		T_ER_X = 1 << 19, // xmm{er}
		T_ER_Y = 1 << 20, // ymm{er}
		T_ER_Z = 1 << 21, // zmm{er}
		T_SAE_X = 1 << 22, // xmm{sae}
		T_SAE_Y = 1 << 23, // ymm{sae}
		T_SAE_Z = 1 << 24, // zmm{sae}
		T_MUST_EVEX = 1 << 25, // contains T_EVEX
		T_B32 = 1 << 26, // m32bcst
		T_B64 = 1 << 27, // m64bcst
		T_B16 = T_B32 | T_B64, // m16bcst (Be careful)
		T_M_K = 1 << 28, // mem{k}
		T_VSIB = 1 << 29,
		T_MEM_EVEX = 1u << 30, // use evex if mem
		T_FP16 = 1u << 31, // avx512-fp16
		T_MAP5 = T_FP16 | T_0F,
		T_MAP6 = T_FP16 | T_0F38,
		T_NF = 1ull << 32, // T_nf
		T_XXX
	};
	// T_66 = 1, T_F3 = 2, T_F2 = 3
	static inline uint32_t getPP(uint64_t type) { return (type >> 5) & 3; }
	// @@@end of avx_type_def.h
