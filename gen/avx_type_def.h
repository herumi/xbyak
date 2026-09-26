	// @@@begin of avx_type_def.h
	static const uint64_t T_NONE = 0ull;
	// N field (bit0-2) : disp8N = 1 << (value - 1), T_DUP is a sentinel
	static const uint64_t T_N1 = 1ull;
	static const uint64_t T_N2 = 2ull;
	static const uint64_t T_N4 = 3ull;
	static const uint64_t T_N8 = 4ull;
	static const uint64_t T_N16 = 5ull;
	static const uint64_t T_N32 = 6ull;
	static const uint64_t T_NX_MASK = 7ull;
	static const uint64_t T_DUP = T_NX_MASK; // N = (8, 32, 64)
	static const uint64_t T_N_VL = 1ull << 3; // N * (1, 2, 4) for VL
	static const uint64_t T_APX = 1ull << 4;
	// pp : one bit each (not a 2-bit field) because rex() emits 0x66 and 0xF2/0xF3 independently (e.g. crc32 uses T_66|T_F2)
	static const uint64_t T_66 = 1ull << 5; // pp = 1
	static const uint64_t T_F3 = 1ull << 6; // pp = 2
	static const uint64_t T_F2 = 1ull << 7; // pp = 3
	// map field (bit8-10) : the value is the same as the EVEX mmm field
	static const uint64_t T_0F = 1ull << 8;
	static const uint64_t T_0F38 = 2ull << 8;
	static const uint64_t T_0F3A = 3ull << 8;
	static const uint64_t T_MAP5 = 5ull << 8;
	static const uint64_t T_MAP6 = 6ull << 8;
	static const uint64_t T_MAP_MASK = 7ull << 8;
	// er/sae field (bit11-13) : an insn has at most one of these
	static const uint64_t T_ER_X = 1ull << 11; // xmm{er}
	static const uint64_t T_ER_Y = 2ull << 11; // ymm{er}
	static const uint64_t T_ER_Z = 3ull << 11; // zmm{er}
	static const uint64_t T_ER_R = 4ull << 11; // reg{er}
	static const uint64_t T_SAE_X = 5ull << 11; // xmm{sae}
	static const uint64_t T_SAE_Y = 6ull << 11; // ymm{sae}
	static const uint64_t T_SAE_Z = 7ull << 11; // zmm{sae}
	static const uint64_t T_ER_SAE_MASK = 7ull << 11;
	static const uint64_t T_W0 = 1ull << 14; // T_EW0 = T_W0
	static const uint64_t T_W1 = 1ull << 15; // for VEX
	static const uint64_t T_EW1 = 1ull << 16; // for EVEX
	static const uint64_t T_L1 = 1ull << 17;
	static const uint64_t T_YMM = 1ull << 18; // support YMM, ZMM
	// evex field (bit19-20) : which encodings the insn has
	static const uint64_t T_EVEX = 1ull << 19; // both VEX and EVEX
	static const uint64_t T_MUST_EVEX = 2ull << 19; // EVEX only
	static const uint64_t T_EVEX_IF_MEM = 3ull << 19; // both, but the mem operand form exists only in EVEX
	static const uint64_t T_EVEX_MASK = 3ull << 19;
	// broadcast field (bit21-22)
	static const uint64_t T_B32 = 1ull << 21; // m32bcst
	static const uint64_t T_B64 = 2ull << 21; // m64bcst
	static const uint64_t T_B16 = T_B32 | T_B64; // m16bcst
	static const uint64_t T_M_K = 1ull << 23; // mem{k}
	static const uint64_t T_VSIB = 1ull << 24;
	static const uint64_t T_NF = 1ull << 25; // T_nf
	static const uint64_t T_OP_W1 = 1ull << 26; // opcode bit0 is the w (operand-size) bit; code|=1 unless the operand is 8-bit
	static const uint64_t T_ND1 = 1ull << 27; // ND=1
	static const uint64_t T_ZU = 1ull << 28; // ND=ZU
	static const uint64_t T_ALLOW_DIFF_SIZE = 1ull << 29; // allow difference reg size
	static const uint64_t T_ALLOW_ABCDH = 1ull << 30; // allow [abcd]h reg
	// T_66 = 1, T_F3 = 2, T_F2 = 3
	static inline uint32_t getPP(uint64_t type) { return (type & T_66) ? 1 : (type & T_F3) ? 2 : (type & T_F2) ? 3 : 0; }
	// @@@end of avx_type_def.h
