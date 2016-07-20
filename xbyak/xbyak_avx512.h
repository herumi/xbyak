#ifndef XBYAK_DISABLE_AVX512
void kaddw(const Opmask& r1, const Opmask& r2, const Opmask& r3) { opVex(r1, &r2, r3, T_L1 | T_0F | T_W0, 0x4A); }
void kaddq(const Opmask& r1, const Opmask& r2, const Opmask& r3) { opVex(r1, &r2, r3, T_L1 | T_0F | T_W1, 0x4A); }
void kaddb(const Opmask& r1, const Opmask& r2, const Opmask& r3) { opVex(r1, &r2, r3, T_L1 | T_0F | T_66 | T_W0, 0x4A); }
void kaddd(const Opmask& r1, const Opmask& r2, const Opmask& r3) { opVex(r1, &r2, r3, T_L1 | T_0F | T_66 | T_W1, 0x4A); }
void kandw(const Opmask& r1, const Opmask& r2, const Opmask& r3) { opVex(r1, &r2, r3, T_L1 | T_0F | T_W0, 0x41); }
void kandq(const Opmask& r1, const Opmask& r2, const Opmask& r3) { opVex(r1, &r2, r3, T_L1 | T_0F | T_W1, 0x41); }
void kandb(const Opmask& r1, const Opmask& r2, const Opmask& r3) { opVex(r1, &r2, r3, T_L1 | T_0F | T_66 | T_W0, 0x41); }
void kandd(const Opmask& r1, const Opmask& r2, const Opmask& r3) { opVex(r1, &r2, r3, T_L1 | T_0F | T_66 | T_W1, 0x41); }
void kandnw(const Opmask& r1, const Opmask& r2, const Opmask& r3) { opVex(r1, &r2, r3, T_L1 | T_0F | T_W0, 0x42); }
void kandnq(const Opmask& r1, const Opmask& r2, const Opmask& r3) { opVex(r1, &r2, r3, T_L1 | T_0F | T_W1, 0x42); }
void kandnb(const Opmask& r1, const Opmask& r2, const Opmask& r3) { opVex(r1, &r2, r3, T_L1 | T_0F | T_66 | T_W0, 0x42); }
void kandnd(const Opmask& r1, const Opmask& r2, const Opmask& r3) { opVex(r1, &r2, r3, T_L1 | T_0F | T_66 | T_W1, 0x42); }
void korw(const Opmask& r1, const Opmask& r2, const Opmask& r3) { opVex(r1, &r2, r3, T_L1 | T_0F | T_W0, 0x45); }
void korq(const Opmask& r1, const Opmask& r2, const Opmask& r3) { opVex(r1, &r2, r3, T_L1 | T_0F | T_W1, 0x45); }
void korb(const Opmask& r1, const Opmask& r2, const Opmask& r3) { opVex(r1, &r2, r3, T_L1 | T_0F | T_66 | T_W0, 0x45); }
void kord(const Opmask& r1, const Opmask& r2, const Opmask& r3) { opVex(r1, &r2, r3, T_L1 | T_0F | T_66 | T_W1, 0x45); }
void kxnorw(const Opmask& r1, const Opmask& r2, const Opmask& r3) { opVex(r1, &r2, r3, T_L1 | T_0F | T_W0, 0x46); }
void kxnorq(const Opmask& r1, const Opmask& r2, const Opmask& r3) { opVex(r1, &r2, r3, T_L1 | T_0F | T_W1, 0x46); }
void kxnorb(const Opmask& r1, const Opmask& r2, const Opmask& r3) { opVex(r1, &r2, r3, T_L1 | T_0F | T_66 | T_W0, 0x46); }
void kxnord(const Opmask& r1, const Opmask& r2, const Opmask& r3) { opVex(r1, &r2, r3, T_L1 | T_0F | T_66 | T_W1, 0x46); }
void kxorw(const Opmask& r1, const Opmask& r2, const Opmask& r3) { opVex(r1, &r2, r3, T_L1 | T_0F | T_W0, 0x47); }
void kxorq(const Opmask& r1, const Opmask& r2, const Opmask& r3) { opVex(r1, &r2, r3, T_L1 | T_0F | T_W1, 0x47); }
void kxorb(const Opmask& r1, const Opmask& r2, const Opmask& r3) { opVex(r1, &r2, r3, T_L1 | T_0F | T_66 | T_W0, 0x47); }
void kxord(const Opmask& r1, const Opmask& r2, const Opmask& r3) { opVex(r1, &r2, r3, T_L1 | T_0F | T_66 | T_W1, 0x47); }
void kunpckbw(const Opmask& r1, const Opmask& r2, const Opmask& r3) { opVex(r1, &r2, r3, T_L1 | T_0F | T_66 | T_W0, 0x4B); }
void kunpckwd(const Opmask& r1, const Opmask& r2, const Opmask& r3) { opVex(r1, &r2, r3, T_L1 | T_0F | T_W0, 0x4B); }
void kunpckdq(const Opmask& r1, const Opmask& r2, const Opmask& r3) { opVex(r1, &r2, r3, T_L1 | T_0F | T_W1, 0x4B); }
void knotw(const Opmask& r1, const Opmask& r2) { opVex(r1, 0, r2, T_0F | T_W0, 0x44); }
void knotq(const Opmask& r1, const Opmask& r2) { opVex(r1, 0, r2, T_0F | T_W1, 0x44); }
void knotb(const Opmask& r1, const Opmask& r2) { opVex(r1, 0, r2, T_0F | T_66 | T_W0, 0x44); }
void knotd(const Opmask& r1, const Opmask& r2) { opVex(r1, 0, r2, T_0F | T_66 | T_W1, 0x44); }
void kortestw(const Opmask& r1, const Opmask& r2) { opVex(r1, 0, r2, T_0F | T_W0, 0x98); }
void kortestq(const Opmask& r1, const Opmask& r2) { opVex(r1, 0, r2, T_0F | T_W1, 0x98); }
void kortestb(const Opmask& r1, const Opmask& r2) { opVex(r1, 0, r2, T_0F | T_66 | T_W0, 0x98); }
void kortestd(const Opmask& r1, const Opmask& r2) { opVex(r1, 0, r2, T_0F | T_66 | T_W1, 0x98); }
void ktestw(const Opmask& r1, const Opmask& r2) { opVex(r1, 0, r2, T_0F | T_W0, 0x99); }
void ktestq(const Opmask& r1, const Opmask& r2) { opVex(r1, 0, r2, T_0F | T_W1, 0x99); }
void ktestb(const Opmask& r1, const Opmask& r2) { opVex(r1, 0, r2, T_0F | T_66 | T_W0, 0x99); }
void ktestd(const Opmask& r1, const Opmask& r2) { opVex(r1, 0, r2, T_0F | T_66 | T_W1, 0x99); }
void kshiftlw(const Opmask& r1, const Opmask& r2, uint8 imm) { opVex(r1, 0, r2, T_66 | T_0F3A | T_W1, 0x32, imm); }
void kshiftlq(const Opmask& r1, const Opmask& r2, uint8 imm) { opVex(r1, 0, r2, T_66 | T_0F3A | T_W1, 0x33, imm); }
void kshiftlb(const Opmask& r1, const Opmask& r2, uint8 imm) { opVex(r1, 0, r2, T_66 | T_0F3A | T_W0, 0x32, imm); }
void kshiftld(const Opmask& r1, const Opmask& r2, uint8 imm) { opVex(r1, 0, r2, T_66 | T_0F3A | T_W0, 0x33, imm); }
void kshiftrw(const Opmask& r1, const Opmask& r2, uint8 imm) { opVex(r1, 0, r2, T_66 | T_0F3A | T_W1, 0x30, imm); }
void kshiftrq(const Opmask& r1, const Opmask& r2, uint8 imm) { opVex(r1, 0, r2, T_66 | T_0F3A | T_W1, 0x31, imm); }
void kshiftrb(const Opmask& r1, const Opmask& r2, uint8 imm) { opVex(r1, 0, r2, T_66 | T_0F3A | T_W0, 0x30, imm); }
void kshiftrd(const Opmask& r1, const Opmask& r2, uint8 imm) { opVex(r1, 0, r2, T_66 | T_0F3A | T_W0, 0x31, imm); }
void kmovw(const Opmask& k, const Operand& op) { opVex(k, 0, op, T_L0 | T_0F | T_W0, 0x90); }
void kmovq(const Opmask& k, const Operand& op) { opVex(k, 0, op, T_L0 | T_0F | T_W1, 0x90); }
void kmovb(const Opmask& k, const Operand& op) { opVex(k, 0, op, T_L0 | T_0F | T_66 | T_W0, 0x90); }
void kmovd(const Opmask& k, const Operand& op) { opVex(k, 0, op, T_L0 | T_0F | T_66 | T_W1, 0x90); }
void kmovw(const Address& addr, const Opmask& k) { opVex(k, 0, addr, T_L0 | T_0F | T_W0, 0x91); }
void kmovq(const Address& addr, const Opmask& k) { opVex(k, 0, addr, T_L0 | T_0F | T_W1, 0x91); }
void kmovb(const Address& addr, const Opmask& k) { opVex(k, 0, addr, T_L0 | T_0F | T_66 | T_W0, 0x91); }
void kmovd(const Address& addr, const Opmask& k) { opVex(k, 0, addr, T_L0 | T_0F | T_66 | T_W1, 0x91); }
void kmovw(const Opmask& k, const Reg32& r) { opVex(k, 0, r, T_L0 | T_0F | T_W0, 0x92); }
void kmovw(const Reg32& r, const Opmask& k) { opVex(r, 0, k, T_L0 | T_0F | T_W0, 0x93); }
#ifdef XBYAK64
void kmovq(const Opmask& k, const Reg64& r) { opVex(k, 0, r, T_L0 | T_0F | T_F2 | T_W1, 0x92); }
void kmovq(const Reg64& r, const Opmask& k) { opVex(r, 0, k, T_L0 | T_0F | T_F2 | T_W1, 0x93); }
#endif
void kmovb(const Opmask& k, const Reg32& r) { opVex(k, 0, r, T_L0 | T_0F | T_66 | T_W0, 0x92); }
void kmovb(const Reg32& r, const Opmask& k) { opVex(r, 0, k, T_L0 | T_0F | T_66 | T_W0, 0x93); }
void kmovd(const Opmask& k, const Reg32& r) { opVex(k, 0, r, T_L0 | T_0F | T_F2 | T_W0, 0x92); }
void kmovd(const Reg32& r, const Opmask& k) { opVex(r, 0, k, T_L0 | T_0F | T_F2 | T_W0, 0x93); }
void vcmppd(const Opmask& k, const Xmm& x, const Operand& op, uint8 imm) { opAVX_K_X_XM(k, x, op, T_66 | T_0F | T_EW1 | T_YMM | T_SAE_Z | T_MUST_EVEX, 0xC2, imm); }
void vcmpps(const Opmask& k, const Xmm& x, const Operand& op, uint8 imm) { opAVX_K_X_XM(k, x, op, T_0F | T_EW0 | T_YMM | T_SAE_Z | T_MUST_EVEX, 0xC2, imm); }
void vcmpsd(const Opmask& k, const Xmm& x, const Operand& op, uint8 imm) { opAVX_K_X_XM(k, x, op, T_F2 | T_0F | T_EW1 | T_SAE_Z | T_MUST_EVEX | T_N8, 0xC2, imm); }
void vcmpss(const Opmask& k, const Xmm& x, const Operand& op, uint8 imm) { opAVX_K_X_XM(k, x, op, T_F3 | T_0F | T_EW0 | T_SAE_Z | T_MUST_EVEX | T_N4, 0xC2, imm); }
void vpcmpeqb(const Opmask& k, const Xmm& x, const Operand& op) { opAVX_K_X_XM(k, x, op, T_66 | T_0F | T_YMM | T_MUST_EVEX, 0x74); }
void vpcmpeqw(const Opmask& k, const Xmm& x, const Operand& op) { opAVX_K_X_XM(k, x, op, T_66 | T_0F | T_YMM | T_MUST_EVEX, 0x75); }
void vpcmpeqd(const Opmask& k, const Xmm& x, const Operand& op) { opAVX_K_X_XM(k, x, op, T_66 | T_0F | T_YMM | T_MUST_EVEX | T_B32, 0x76); }
void vpcmpeqq(const Opmask& k, const Xmm& x, const Operand& op) { opAVX_K_X_XM(k, x, op, T_66 | T_0F38 | T_EW1 | T_YMM | T_MUST_EVEX | T_B64, 0x29); }
void vpcmpgtb(const Opmask& k, const Xmm& x, const Operand& op) { opAVX_K_X_XM(k, x, op, T_66 | T_0F | T_YMM | T_MUST_EVEX, 0x64); }
void vpcmpgtw(const Opmask& k, const Xmm& x, const Operand& op) { opAVX_K_X_XM(k, x, op, T_66 | T_0F | T_YMM | T_MUST_EVEX, 0x65); }
void vpcmpgtd(const Opmask& k, const Xmm& x, const Operand& op) { opAVX_K_X_XM(k, x, op, T_66 | T_0F | T_EW0 | T_YMM | T_MUST_EVEX | T_B32, 0x66); }
void vpcmpgtq(const Opmask& k, const Xmm& x, const Operand& op) { opAVX_K_X_XM(k, x, op, T_66 | T_0F38 | T_EW1 | T_YMM | T_MUST_EVEX | T_B64, 0x37); }
void vpcmpb(const Opmask& k, const Xmm& x, const Operand& op, uint8 imm) { opAVX_K_X_XM(k, x, op, T_66 | T_0F3A | T_EW0 | T_YMM | T_MUST_EVEX, 0x3F, imm); }
void vpcmpub(const Opmask& k, const Xmm& x, const Operand& op, uint8 imm) { opAVX_K_X_XM(k, x, op, T_66 | T_0F3A | T_EW0 | T_YMM | T_MUST_EVEX, 0x3E, imm); }
void vpcmpw(const Opmask& k, const Xmm& x, const Operand& op, uint8 imm) { opAVX_K_X_XM(k, x, op, T_66 | T_0F3A | T_EW1 | T_YMM | T_MUST_EVEX, 0x3F, imm); }
void vpcmpuw(const Opmask& k, const Xmm& x, const Operand& op, uint8 imm) { opAVX_K_X_XM(k, x, op, T_66 | T_0F3A | T_EW1 | T_YMM | T_MUST_EVEX, 0x3E, imm); }
void vpcmpd(const Opmask& k, const Xmm& x, const Operand& op, uint8 imm) { opAVX_K_X_XM(k, x, op, T_66 | T_0F3A | T_EW0 | T_YMM | T_MUST_EVEX | T_B32, 0x1F, imm); }
void vpcmpud(const Opmask& k, const Xmm& x, const Operand& op, uint8 imm) { opAVX_K_X_XM(k, x, op, T_66 | T_0F3A | T_EW0 | T_YMM | T_MUST_EVEX | T_B32, 0x1E, imm); }
void vpcmpq(const Opmask& k, const Xmm& x, const Operand& op, uint8 imm) { opAVX_K_X_XM(k, x, op, T_66 | T_0F3A | T_EW1 | T_YMM | T_MUST_EVEX | T_B64, 0x1F, imm); }
void vpcmpuq(const Opmask& k, const Xmm& x, const Operand& op, uint8 imm) { opAVX_K_X_XM(k, x, op, T_66 | T_0F3A | T_EW1 | T_YMM | T_MUST_EVEX | T_B64, 0x1E, imm); }
void vptestmb(const Opmask& k, const Xmm& x, const Operand& op) { opAVX_K_X_XM(k, x, op, T_66 | T_0F38 | T_EW0 | T_YMM | T_MUST_EVEX, 0x26); }
void vptestmw(const Opmask& k, const Xmm& x, const Operand& op) { opAVX_K_X_XM(k, x, op, T_66 | T_0F38 | T_EW1 | T_YMM | T_MUST_EVEX, 0x26); }
void vptestmd(const Opmask& k, const Xmm& x, const Operand& op) { opAVX_K_X_XM(k, x, op, T_66 | T_0F38 | T_EW0 | T_YMM | T_MUST_EVEX | T_B32, 0x27); }
void vptestmq(const Opmask& k, const Xmm& x, const Operand& op) { opAVX_K_X_XM(k, x, op, T_66 | T_0F38 | T_EW1 | T_YMM | T_MUST_EVEX | T_B64, 0x27); }
void vptestnmb(const Opmask& k, const Xmm& x, const Operand& op) { opAVX_K_X_XM(k, x, op, T_F3 | T_0F38 | T_EW0 | T_YMM | T_MUST_EVEX, 0x26); }
void vptestnmw(const Opmask& k, const Xmm& x, const Operand& op) { opAVX_K_X_XM(k, x, op, T_F3 | T_0F38 | T_EW1 | T_YMM | T_MUST_EVEX, 0x26); }
void vptestnmd(const Opmask& k, const Xmm& x, const Operand& op) { opAVX_K_X_XM(k, x, op, T_F3 | T_0F38 | T_EW0 | T_YMM | T_MUST_EVEX | T_B32, 0x27); }
void vptestnmq(const Opmask& k, const Xmm& x, const Operand& op) { opAVX_K_X_XM(k, x, op, T_F3 | T_0F38 | T_EW1 | T_YMM | T_MUST_EVEX | T_B64, 0x27); }
void vmovdqa32(const Xmm& x, const Operand& op) { opAVX_X_XM_IMM(x, op, T_66 | T_0F | T_EW0 | T_YMM | T_ER_X | T_ER_Y | T_ER_Z | T_MUST_EVEX, 0x6F); }
void vmovdqa64(const Xmm& x, const Operand& op) { opAVX_X_XM_IMM(x, op, T_66 | T_0F | T_EW1 | T_YMM | T_ER_X | T_ER_Y | T_ER_Z | T_MUST_EVEX, 0x6F); }
void vmovdqu8(const Xmm& x, const Operand& op) { opAVX_X_XM_IMM(x, op, T_F2 | T_0F | T_EW0 | T_YMM | T_ER_X | T_ER_Y | T_ER_Z | T_MUST_EVEX, 0x6F); }
void vmovdqu16(const Xmm& x, const Operand& op) { opAVX_X_XM_IMM(x, op, T_F2 | T_0F | T_EW1 | T_YMM | T_ER_X | T_ER_Y | T_ER_Z | T_MUST_EVEX, 0x6F); }
void vmovdqu32(const Xmm& x, const Operand& op) { opAVX_X_XM_IMM(x, op, T_F3 | T_0F | T_EW0 | T_YMM | T_ER_X | T_ER_Y | T_ER_Z | T_MUST_EVEX, 0x6F); }
void vmovdqu64(const Xmm& x, const Operand& op) { opAVX_X_XM_IMM(x, op, T_F3 | T_0F | T_EW1 | T_YMM | T_ER_X | T_ER_Y | T_ER_Z | T_MUST_EVEX, 0x6F); }
void vcvtpd2qq(const Xmm& x, const Operand& op) { opAVX_X_XM_IMM(x, op, T_66 | T_0F | T_EW1 | T_YMM | T_ER_Z | T_MUST_EVEX | T_B64, 0x7B); }
void vcvtpd2uqq(const Xmm& x, const Operand& op) { opAVX_X_XM_IMM(x, op, T_66 | T_0F | T_EW1 | T_YMM | T_ER_Z | T_MUST_EVEX | T_B64, 0x79); }
void vcvtps2udq(const Xmm& x, const Operand& op) { opAVX_X_XM_IMM(x, op, T_0F | T_EW0 | T_YMM | T_ER_Z | T_MUST_EVEX | T_B32, 0x79); }
void vcvtqq2pd(const Xmm& x, const Operand& op) { opAVX_X_XM_IMM(x, op, T_F3 | T_0F | T_EW1 | T_YMM | T_ER_Z | T_MUST_EVEX | T_B64, 0xE6); }
void vcvttpd2qq(const Xmm& x, const Operand& op) { opAVX_X_XM_IMM(x, op, T_66 | T_0F | T_EW1 | T_YMM | T_SAE_Z | T_MUST_EVEX | T_B64, 0x7A); }
void vcvttpd2uqq(const Xmm& x, const Operand& op) { opAVX_X_XM_IMM(x, op, T_66 | T_0F | T_EW1 | T_YMM | T_SAE_Z | T_MUST_EVEX | T_B64, 0x78); }
void vcvttps2udq(const Xmm& x, const Operand& op) { opAVX_X_XM_IMM(x, op, T_0F | T_EW0 | T_YMM | T_SAE_Z | T_MUST_EVEX | T_B32, 0x78); }
void vcvtudq2ps(const Xmm& x, const Operand& op) { opAVX_X_XM_IMM(x, op, T_F2 | T_0F | T_EW0 | T_YMM | T_ER_Z | T_MUST_EVEX | T_B32, 0x7A); }
void vcvtuqq2pd(const Xmm& x, const Operand& op) { opAVX_X_XM_IMM(x, op, T_F3 | T_0F | T_EW1 | T_YMM | T_ER_Z | T_MUST_EVEX | T_B64, 0x7A); }
void vexpandpd(const Xmm& x, const Operand& op) { opAVX_X_XM_IMM(x, op, T_66 | T_0F38 | T_EW1 | T_YMM | T_MUST_EVEX | T_N8, 0x88); }
void vexpandps(const Xmm& x, const Operand& op) { opAVX_X_XM_IMM(x, op, T_66 | T_0F38 | T_EW0 | T_YMM | T_MUST_EVEX | T_N4, 0x88); }
void vpexpandd(const Xmm& x, const Operand& op) { opAVX_X_XM_IMM(x, op, T_66 | T_0F38 | T_EW0 | T_YMM | T_MUST_EVEX | T_N4, 0x89); }
void vpexpandq(const Xmm& x, const Operand& op) { opAVX_X_XM_IMM(x, op, T_66 | T_0F38 | T_EW1 | T_YMM | T_MUST_EVEX | T_N8, 0x89); }
void vpabsq(const Xmm& x, const Operand& op) { opAVX_X_XM_IMM(x, op, T_66 | T_0F38 | T_MUST_EVEX | T_EW1 | T_B64 | T_YMM, 0x1F); }
void vmovdqa32(const Address& addr, const Xmm& x) { opAVX_X_XM_IMM(x, addr, T_66 | T_0F | T_EW0 | T_YMM | T_ER_X | T_ER_Y | T_ER_Z | T_MUST_EVEX, 0x7F); }
void vmovdqa64(const Address& addr, const Xmm& x) { opAVX_X_XM_IMM(x, addr, T_66 | T_0F | T_EW1 | T_YMM | T_ER_X | T_ER_Y | T_ER_Z | T_MUST_EVEX, 0x7F); }
void vmovdqu8(const Address& addr, const Xmm& x) { opAVX_X_XM_IMM(x, addr, T_F2 | T_0F | T_EW0 | T_YMM | T_ER_X | T_ER_Y | T_ER_Z | T_MUST_EVEX, 0x7F); }
void vmovdqu16(const Address& addr, const Xmm& x) { opAVX_X_XM_IMM(x, addr, T_F2 | T_0F | T_EW1 | T_YMM | T_ER_X | T_ER_Y | T_ER_Z | T_MUST_EVEX, 0x7F); }
void vmovdqu32(const Address& addr, const Xmm& x) { opAVX_X_XM_IMM(x, addr, T_F3 | T_0F | T_EW0 | T_YMM | T_ER_X | T_ER_Y | T_ER_Z | T_MUST_EVEX, 0x7F); }
void vmovdqu64(const Address& addr, const Xmm& x) { opAVX_X_XM_IMM(x, addr, T_F3 | T_0F | T_EW1 | T_YMM | T_ER_X | T_ER_Y | T_ER_Z | T_MUST_EVEX, 0x7F); }
void vcompresspd(const Operand& op, const Xmm& x) { opAVX_X_XM_IMM(x, op, T_66 | T_0F38 | T_EW1 | T_YMM | T_MUST_EVEX | T_N8, 0x8A); }
void vcompressps(const Operand& op, const Xmm& x) { opAVX_X_XM_IMM(x, op, T_66 | T_0F38 | T_EW0 | T_YMM | T_MUST_EVEX | T_N4, 0x8A); }
void vpcompressd(const Operand& op, const Xmm& x) { opAVX_X_XM_IMM(x, op, T_66 | T_0F38 | T_EW0 | T_YMM | T_MUST_EVEX | T_N4, 0x8B); }
void vpcompressq(const Operand& op, const Xmm& x) { opAVX_X_XM_IMM(x, op, T_66 | T_0F38 | T_EW1 | T_YMM | T_MUST_EVEX | T_N8, 0x8B); }
void valignd(const Xmm& x1, const Xmm& x2, const Operand& op, uint8 imm) { opAVX_X_X_XM(x1, x2, op, T_66 | T_0F3A | T_EW0 | T_YMM | T_MUST_EVEX, 0x03, imm); }
void valignq(const Xmm& x1, const Xmm& x2, const Operand& op, uint8 imm) { opAVX_X_X_XM(x1, x2, op, T_66 | T_0F3A | T_EW1 | T_YMM | T_MUST_EVEX, 0x03, imm); }
void vpandd(const Xmm& x1, const Xmm& x2, const Operand& op) { opAVX_X_X_XM(x1, x2, op, T_66 | T_0F | T_EW0 | T_YMM | T_MUST_EVEX | T_B32, 0xDB); }
void vpandq(const Xmm& x1, const Xmm& x2, const Operand& op) { opAVX_X_X_XM(x1, x2, op, T_66 | T_0F | T_EW1 | T_YMM | T_MUST_EVEX | T_B64, 0xDB); }
void vpandnd(const Xmm& x1, const Xmm& x2, const Operand& op) { opAVX_X_X_XM(x1, x2, op, T_66 | T_0F | T_EW0 | T_YMM | T_MUST_EVEX | T_B32, 0xDF); }
void vpandnq(const Xmm& x1, const Xmm& x2, const Operand& op) { opAVX_X_X_XM(x1, x2, op, T_66 | T_0F | T_EW1 | T_YMM | T_MUST_EVEX | T_B64, 0xDF); }
void vpmaxsq(const Xmm& x1, const Xmm& x2, const Operand& op) { opAVX_X_X_XM(x1, x2, op, T_66 | T_0F38 | T_EW1 | T_YMM | T_MUST_EVEX | T_B64, 0x3D); }
void vpmaxuq(const Xmm& x1, const Xmm& x2, const Operand& op) { opAVX_X_X_XM(x1, x2, op, T_66 | T_0F38 | T_EW1 | T_YMM | T_MUST_EVEX | T_B64, 0x3F); }
void vpminsq(const Xmm& x1, const Xmm& x2, const Operand& op) { opAVX_X_X_XM(x1, x2, op, T_66 | T_0F38 | T_EW1 | T_YMM | T_MUST_EVEX | T_B64, 0x39); }
void vpminuq(const Xmm& x1, const Xmm& x2, const Operand& op) { opAVX_X_X_XM(x1, x2, op, T_66 | T_0F38 | T_EW1 | T_YMM | T_MUST_EVEX | T_B64, 0x3B); }
void vpsraq(const Xmm& x1, const Xmm& x2, const Operand& op) { opAVX_X_X_XM(x1, x2, op, T_66 | T_0F | T_EW1 | T_YMM | T_MUST_EVEX | T_N16, 0xE2); }
void vpsravq(const Xmm& x1, const Xmm& x2, const Operand& op) { opAVX_X_X_XM(x1, x2, op, T_66 | T_0F38 | T_EW1 | T_YMM | T_MUST_EVEX | T_B64, 0x46); }
void vpsravw(const Xmm& x1, const Xmm& x2, const Operand& op) { opAVX_X_X_XM(x1, x2, op, T_66 | T_0F38 | T_EW1 | T_YMM | T_MUST_EVEX, 0x11); }
void vpsllvw(const Xmm& x1, const Xmm& x2, const Operand& op) { opAVX_X_X_XM(x1, x2, op, T_66 | T_0F38 | T_EW1 | T_YMM | T_MUST_EVEX, 0x12); }
void vpsrlvw(const Xmm& x1, const Xmm& x2, const Operand& op) { opAVX_X_X_XM(x1, x2, op, T_66 | T_0F38 | T_EW1 | T_YMM | T_MUST_EVEX, 0x10); }
void vpord(const Xmm& x1, const Xmm& x2, const Operand& op) { opAVX_X_X_XM(x1, x2, op, T_66 | T_0F | T_EW0 | T_YMM | T_MUST_EVEX | T_B32, 0xEB); }
void vporq(const Xmm& x1, const Xmm& x2, const Operand& op) { opAVX_X_X_XM(x1, x2, op, T_66 | T_0F | T_EW1 | T_YMM | T_MUST_EVEX | T_B64, 0xEB); }
void vpxord(const Xmm& x1, const Xmm& x2, const Operand& op) { opAVX_X_X_XM(x1, x2, op, T_66 | T_0F | T_EW0 | T_YMM | T_MUST_EVEX | T_B32, 0xEF); }
void vpxorq(const Xmm& x1, const Xmm& x2, const Operand& op) { opAVX_X_X_XM(x1, x2, op, T_66 | T_0F | T_EW1 | T_YMM | T_MUST_EVEX | T_B64, 0xEF); }
void vpmullq(const Xmm& x1, const Xmm& x2, const Operand& op) { opAVX_X_X_XM(x1, x2, op, T_66 | T_0F38 | T_EW1 | T_YMM | T_MUST_EVEX | T_B64, 0x40); }
void vpermb(const Xmm& x1, const Xmm& x2, const Operand& op) { opAVX_X_X_XM(x1, x2, op, T_66 | T_0F38 | T_EW0 | T_YMM | T_MUST_EVEX, 0x8D); }
void vpermw(const Xmm& x1, const Xmm& x2, const Operand& op) { opAVX_X_X_XM(x1, x2, op, T_66 | T_0F38 | T_EW1 | T_YMM | T_MUST_EVEX, 0x8D); }
void vblendmpd(const Xmm& x1, const Xmm& x2, const Operand& op) { opAVX_X_X_XM(x1, x2, op, T_66 | T_0F38 | T_EW1 | T_YMM | T_MUST_EVEX | T_B64, 0x65); }
void vblendmps(const Xmm& x1, const Xmm& x2, const Operand& op) { opAVX_X_X_XM(x1, x2, op, T_66 | T_0F38 | T_EW0 | T_YMM | T_MUST_EVEX | T_B32, 0x65); }
void vpblendmb(const Xmm& x1, const Xmm& x2, const Operand& op) { opAVX_X_X_XM(x1, x2, op, T_66 | T_0F38 | T_EW0 | T_YMM | T_MUST_EVEX, 0x66); }
void vpblendmw(const Xmm& x1, const Xmm& x2, const Operand& op) { opAVX_X_X_XM(x1, x2, op, T_66 | T_0F38 | T_EW1 | T_YMM | T_MUST_EVEX, 0x66); }
void vpblendmd(const Xmm& x1, const Xmm& x2, const Operand& op) { opAVX_X_X_XM(x1, x2, op, T_66 | T_0F38 | T_EW0 | T_YMM | T_MUST_EVEX | T_B32, 0x64); }
void vpblendmq(const Xmm& x1, const Xmm& x2, const Operand& op) { opAVX_X_X_XM(x1, x2, op, T_66 | T_0F38 | T_EW1 | T_YMM | T_MUST_EVEX | T_B64, 0x64); }
void vpsraq(const Xmm& x, const Operand& op, uint8 imm) { opAVX_X_X_XM(Xmm(x.getKind(), 4), x, op, T_66 | T_0F | T_EW1 | T_YMM | T_MUST_EVEX | T_B64, 0x72, imm); }
void vextractf32x4(const Operand& op, const Ymm& r, uint8 imm) { opAVX_X_X_XMcvt(r, true, cvtIdx0(r), op, op.isXMM(), Operand::YMM, T_66 | T_0F3A | T_EW0 | T_YMM | T_MUST_EVEX | T_N16, 0x19, imm); }
void vextractf64x2(const Operand& op, const Ymm& r, uint8 imm) { opAVX_X_X_XMcvt(r, true, cvtIdx0(r), op, op.isXMM(), Operand::YMM, T_66 | T_0F3A | T_EW1 | T_YMM | T_MUST_EVEX | T_N16, 0x19, imm); }
void vextractf32x8(const Operand& op, const Zmm& r, uint8 imm) { opAVX_X_X_XMcvt(r, true, cvtIdx0(r), op, op.isXMM(), Operand::YMM, T_66 | T_0F3A | T_EW0 | T_YMM | T_MUST_EVEX | T_N32, 0x1B, imm); }
void vextractf64x4(const Operand& op, const Zmm& r, uint8 imm) { opAVX_X_X_XMcvt(r, true, cvtIdx0(r), op, op.isXMM(), Operand::YMM, T_66 | T_0F3A | T_EW1 | T_YMM | T_MUST_EVEX | T_N32, 0x1B, imm); }
void vextracti32x4(const Operand& op, const Ymm& r, uint8 imm) { opAVX_X_X_XMcvt(r, true, cvtIdx0(r), op, op.isXMM(), Operand::YMM, T_66 | T_0F3A | T_EW0 | T_YMM | T_MUST_EVEX | T_N16, 0x39, imm); }
void vextracti64x2(const Operand& op, const Ymm& r, uint8 imm) { opAVX_X_X_XMcvt(r, true, cvtIdx0(r), op, op.isXMM(), Operand::YMM, T_66 | T_0F3A | T_EW1 | T_YMM | T_MUST_EVEX | T_N16, 0x39, imm); }
void vextracti32x8(const Operand& op, const Zmm& r, uint8 imm) { opAVX_X_X_XMcvt(r, true, cvtIdx0(r), op, op.isXMM(), Operand::YMM, T_66 | T_0F3A | T_EW0 | T_YMM | T_MUST_EVEX | T_N32, 0x3B, imm); }
void vextracti64x4(const Operand& op, const Zmm& r, uint8 imm) { opAVX_X_X_XMcvt(r, true, cvtIdx0(r), op, op.isXMM(), Operand::YMM, T_66 | T_0F3A | T_EW1 | T_YMM | T_MUST_EVEX | T_N32, 0x3B, imm); }
void vinsertf32x4(const Ymm& r1, const Ymm& r2, const Operand& op, uint8 imm) { opAVX_X_X_XMcvt(r1, false, r2, op, op.isXMM(), Operand::YMM, T_66 | T_0F3A | T_EW0 | T_YMM | T_MUST_EVEX | T_N16, 0x18, imm); }
void vinsertf64x2(const Ymm& r1, const Ymm& r2, const Operand& op, uint8 imm) { opAVX_X_X_XMcvt(r1, false, r2, op, op.isXMM(), Operand::YMM, T_66 | T_0F3A | T_EW1 | T_YMM | T_MUST_EVEX | T_N16, 0x18, imm); }
void vinsertf32x8(const Zmm& r1, const Zmm& r2, const Operand& op, uint8 imm) { opAVX_X_X_XMcvt(r1, false, r2, op, op.isXMM(), Operand::YMM, T_66 | T_0F3A | T_EW0 | T_YMM | T_MUST_EVEX | T_N32, 0x1A, imm); }
void vinsertf64x4(const Zmm& r1, const Zmm& r2, const Operand& op, uint8 imm) { opAVX_X_X_XMcvt(r1, false, r2, op, op.isXMM(), Operand::YMM, T_66 | T_0F3A | T_EW1 | T_YMM | T_MUST_EVEX | T_N32, 0x1A, imm); }
void vinserti32x4(const Ymm& r1, const Ymm& r2, const Operand& op, uint8 imm) { opAVX_X_X_XMcvt(r1, false, r2, op, op.isXMM(), Operand::YMM, T_66 | T_0F3A | T_EW0 | T_YMM | T_MUST_EVEX | T_N16, 0x38, imm); }
void vinserti64x2(const Ymm& r1, const Ymm& r2, const Operand& op, uint8 imm) { opAVX_X_X_XMcvt(r1, false, r2, op, op.isXMM(), Operand::YMM, T_66 | T_0F3A | T_EW1 | T_YMM | T_MUST_EVEX | T_N16, 0x38, imm); }
void vinserti32x8(const Zmm& r1, const Zmm& r2, const Operand& op, uint8 imm) { opAVX_X_X_XMcvt(r1, false, r2, op, op.isXMM(), Operand::YMM, T_66 | T_0F3A | T_EW0 | T_YMM | T_MUST_EVEX | T_N32, 0x3A, imm); }
void vinserti64x4(const Zmm& r1, const Zmm& r2, const Operand& op, uint8 imm) { opAVX_X_X_XMcvt(r1, false, r2, op, op.isXMM(), Operand::YMM, T_66 | T_0F3A | T_EW1 | T_YMM | T_MUST_EVEX | T_N32, 0x3A, imm); }
void vbroadcastf32x2(const Ymm& y, const Operand& op) { opAVX_X_XM_IMM(y, op, T_66 | T_0F38 | T_YMM | T_MUST_EVEX | T_EW0 | T_N8, 0x19); }
void vbroadcastf32x4(const Ymm& y, const Address& addr) { opAVX_X_XM_IMM(y, addr, T_66 | T_0F38 | T_YMM | T_MUST_EVEX | T_EW0 | T_N16, 0x1A); }
void vbroadcastf64x2(const Ymm& y, const Address& addr) { opAVX_X_XM_IMM(y, addr, T_66 | T_0F38 | T_YMM | T_MUST_EVEX | T_EW1 | T_N16, 0x1A); }
void vbroadcastf64x4(const Zmm& y, const Address& addr) { opAVX_X_XM_IMM(y, addr, T_66 | T_0F38 | T_YMM | T_MUST_EVEX | T_EW1 | T_N32, 0x1B); }
void vpbroadcastb(const Xmm& x, const Reg8& r) { opVex(x, &cvtIdx0(x), r, T_66 | T_0F38 | T_EW0 | T_YMM | T_MUST_EVEX | T_N4, 0x7A); }
void vpbroadcastw(const Xmm& x, const Reg16& r) { opVex(x, &cvtIdx0(x), r, T_66 | T_0F38 | T_EW0 | T_YMM | T_MUST_EVEX | T_N4, 0x7B); }
void vpbroadcastd(const Xmm& x, const Reg32& r) { opVex(x, &cvtIdx0(x), r, T_66 | T_0F38 | T_EW0 | T_YMM | T_MUST_EVEX | T_N4, 0x7C); }
#ifdef XBYAK64
void vpbroadcastq(const Xmm& x, const Reg64& r) { opVex(x, &cvtIdx0(x), r, T_66 | T_0F38 | T_EW1 | T_YMM | T_MUST_EVEX | T_N8, 0x7C); }
#endif
void vbroadcasti32x2(const Xmm& x, const Operand& op) { opAVX_X_XM_IMM(x, op, T_66 | T_0F38 | T_YMM | T_MUST_EVEX | T_EW0 | T_N8, 0x59); }
void vbroadcasti32x4(const Ymm& y, const Operand& op) { opAVX_X_XM_IMM(y, op, T_66 | T_0F38 | T_YMM | T_MUST_EVEX | T_EW0 | T_N16, 0x5A); }
void vbroadcasti64x2(const Ymm& y, const Operand& op) { opAVX_X_XM_IMM(y, op, T_66 | T_0F38 | T_YMM | T_MUST_EVEX | T_EW1 | T_N16, 0x5A); }
void vbroadcasti32x8(const Zmm& z, const Operand& op) { opAVX_X_XM_IMM(z, op, T_66 | T_0F38 | T_YMM | T_MUST_EVEX | T_EW0 | T_N32, 0x5B); }
void vbroadcasti64x4(const Zmm& z, const Operand& op) { opAVX_X_XM_IMM(z, op, T_66 | T_0F38 | T_YMM | T_MUST_EVEX | T_EW1 | T_N32, 0x5B); }
void vcvtpd2udq(const Xmm& x, const Operand& op) { opCvt2(x, op, T_0F | T_YMM | T_MUST_EVEX | T_EW1 | T_B64 | T_ER_Z, 0x79); }
void vcvtps2qq(const Xmm& x, const Operand& op) { checkCvt1(x, op); opVex(x, 0, op, T_66 | T_0F | T_YMM | T_MUST_EVEX | T_EW0 | T_B32 | T_N8 | T_N_VL | T_ER_Y, 0x7B); }
void vcvtps2uqq(const Xmm& x, const Operand& op) { checkCvt1(x, op); opVex(x, 0, op, T_66 | T_0F | T_YMM | T_MUST_EVEX | T_EW0 | T_B32 | T_N8 | T_N_VL | T_ER_Y, 0x79); }
void vcvtqq2ps(const Xmm& x, const Operand& op) { opCvt2(x, op, T_0F | T_YMM | T_MUST_EVEX | T_EW1 | T_B64 | T_ER_Z, 0x5B); }
void vcvttpd2udq(const Xmm& x, const Operand& op) { opCvt2(x, op, T_0F | T_YMM | T_MUST_EVEX | T_EW1 | T_B64 | T_SAE_Z, 0x78); }
void vcvttps2qq(const Xmm& x, const Operand& op) { checkCvt1(x, op); opVex(x, 0, op, T_66 | T_0F | T_YMM | T_MUST_EVEX | T_EW0 | T_B32 | T_N8 | T_N_VL | T_SAE_Y, 0x7A); }
void vcvttps2uqq(const Xmm& x, const Operand& op) { checkCvt1(x, op); opVex(x, 0, op, T_66 | T_0F | T_YMM | T_MUST_EVEX | T_EW0 | T_B32 | T_N8 | T_N_VL | T_SAE_Y, 0x78); }
void vcvtudq2pd(const Xmm& x, const Operand& op) { checkCvt1(x, op); opVex(x, 0, op, T_F3 | T_0F | T_YMM | T_MUST_EVEX | T_EW0 | T_B32 | T_N8 | T_N_VL, 0x7A); }
void vcvtsd2usi(const Reg32& r, const Operand& op) { opAVX_X_X_XM(Xmm(r.getIdx()), xm0, op, T_F2 | T_0F | T_MUST_EVEX | T_EW0 | T_N8 | T_ER_X, 0x79); }
void vcvtss2usi(const Reg32& r, const Operand& op) { opAVX_X_X_XM(Xmm(r.getIdx()), xm0, op, T_F3 | T_0F | T_MUST_EVEX | T_EW0 | T_N4 | T_ER_X, 0x79); }
void vcvttsd2usi(const Reg32& r, const Operand& op) { opAVX_X_X_XM(Xmm(r.getIdx()), xm0, op, T_F2 | T_0F | T_MUST_EVEX | T_EW0 | T_N8 | T_SAE_X, 0x78); }
void vcvttss2usi(const Reg32& r, const Operand& op) { opAVX_X_X_XM(Xmm(r.getIdx()), xm0, op, T_F3 | T_0F | T_MUST_EVEX | T_EW0 | T_N4 | T_SAE_X, 0x78); }
void vcvtuqq2ps(const Xmm& x, const Operand& op) { opCvt2(x, op, T_F2 | T_0F | T_YMM | T_MUST_EVEX | T_EW1 | T_B64 | T_ER_Z, 0x7A); }
void vcvtusi2sd(const Xmm& x1, const Xmm& x2, const Operand& op) {if (!(op.isREG(i32e) || op.isMEM())) throw Error(ERR_BAD_COMBINATION);int type = T_F2 | T_0F | T_MUST_EVEX;type |= op.isBit(64) ? T_W1 | T_EW1 | T_ER_X | T_N8 : T_W0 | T_EW0 | T_N4;opAVX_X_X_XMcvt(x1, false, x2, op, op.isREG(), Operand::XMM, type, 0x7B); }
void vcvtusi2ss(const Xmm& x1, const Xmm& x2, const Operand& op) {if (!(op.isREG(i32e) || op.isMEM())) throw Error(ERR_BAD_COMBINATION);int type = T_F3 | T_0F | T_MUST_EVEX | T_ER_X;type |= op.isBit(64) ? T_W1 | T_EW1 | T_N8 : T_W0 | T_EW0 | T_N4;opAVX_X_X_XMcvt(x1, false, x2, op, op.isREG(), Operand::XMM, type, 0x7B); }
#ifdef XBYAK64
void vcvtsd2usi(const Reg64& r, const Operand& op) { opAVX_X_X_XM(Xmm(r.getIdx()), xm0, op, T_F2 | T_0F | T_MUST_EVEX | T_EW1 | T_N8 | T_ER_X, 0x79); }
void vcvtss2usi(const Reg64& r, const Operand& op) { opAVX_X_X_XM(Xmm(r.getIdx()), xm0, op, T_F3 | T_0F | T_MUST_EVEX | T_EW1 | T_N4 | T_ER_X, 0x79); }
void vcvttsd2usi(const Reg64& r, const Operand& op) { opAVX_X_X_XM(Xmm(r.getIdx()), xm0, op, T_F2 | T_0F | T_MUST_EVEX | T_EW1 | T_N8 | T_SAE_X, 0x78); }
void vcvttss2usi(const Reg64& r, const Operand& op) { opAVX_X_X_XM(Xmm(r.getIdx()), xm0, op, T_F3 | T_0F | T_MUST_EVEX | T_EW1 | T_N4 | T_SAE_X, 0x78); }
#endif
void vpgatherdd(const Xmm& x, const Address& addr) { opGather2(x, addr, T_66 | T_0F38 | T_EW0 | T_YMM | T_MUST_EVEX | T_N4, 0x90, 0); }
void vpgatherdq(const Xmm& x, const Address& addr) { opGather2(x, addr, T_66 | T_0F38 | T_EW1 | T_YMM | T_MUST_EVEX | T_N8, 0x90, 1); }
void vpgatherqd(const Xmm& x, const Address& addr) { opGather2(x, addr, T_66 | T_0F38 | T_EW0 | T_YMM | T_MUST_EVEX | T_N4, 0x91, 2); }
void vpgatherqq(const Xmm& x, const Address& addr) { opGather2(x, addr, T_66 | T_0F38 | T_EW1 | T_YMM | T_MUST_EVEX | T_N8, 0x91, 0); }
void vgatherdps(const Xmm& x, const Address& addr) { opGather2(x, addr, T_66 | T_0F38 | T_EW0 | T_YMM | T_MUST_EVEX | T_N4, 0x92, 0); }
void vgatherdpd(const Xmm& x, const Address& addr) { opGather2(x, addr, T_66 | T_0F38 | T_EW1 | T_YMM | T_MUST_EVEX | T_N8, 0x92, 1); }
void vgatherqps(const Xmm& x, const Address& addr) { opGather2(x, addr, T_66 | T_0F38 | T_EW0 | T_YMM | T_MUST_EVEX | T_N4, 0x93, 2); }
void vgatherqpd(const Xmm& x, const Address& addr) { opGather2(x, addr, T_66 | T_0F38 | T_EW1 | T_YMM | T_MUST_EVEX | T_N8, 0x93, 0); }
#endif
