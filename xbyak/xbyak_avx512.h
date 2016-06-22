#ifdef XBYAK_AVX512
void kaddw(const Opmask& r1, const Opmask& r2, const Opmask& r3) { opVex(r1, &r2, r3, VEX_L1 | MM_0F, 0x4A, 0); }
void kaddq(const Opmask& r1, const Opmask& r2, const Opmask& r3) { opVex(r1, &r2, r3, VEX_L1 | MM_0F, 0x4A, 1); }
void kaddb(const Opmask& r1, const Opmask& r2, const Opmask& r3) { opVex(r1, &r2, r3, VEX_L1 | MM_0F | PP_66, 0x4A, 0); }
void kaddd(const Opmask& r1, const Opmask& r2, const Opmask& r3) { opVex(r1, &r2, r3, VEX_L1 | MM_0F | PP_66, 0x4A, 1); }
void kandw(const Opmask& r1, const Opmask& r2, const Opmask& r3) { opVex(r1, &r2, r3, VEX_L1 | MM_0F, 0x41, 0); }
void kandq(const Opmask& r1, const Opmask& r2, const Opmask& r3) { opVex(r1, &r2, r3, VEX_L1 | MM_0F, 0x41, 1); }
void kandb(const Opmask& r1, const Opmask& r2, const Opmask& r3) { opVex(r1, &r2, r3, VEX_L1 | MM_0F | PP_66, 0x41, 0); }
void kandd(const Opmask& r1, const Opmask& r2, const Opmask& r3) { opVex(r1, &r2, r3, VEX_L1 | MM_0F | PP_66, 0x41, 1); }
void kandnw(const Opmask& r1, const Opmask& r2, const Opmask& r3) { opVex(r1, &r2, r3, VEX_L1 | MM_0F, 0x42, 0); }
void kandnq(const Opmask& r1, const Opmask& r2, const Opmask& r3) { opVex(r1, &r2, r3, VEX_L1 | MM_0F, 0x42, 1); }
void kandnb(const Opmask& r1, const Opmask& r2, const Opmask& r3) { opVex(r1, &r2, r3, VEX_L1 | MM_0F | PP_66, 0x42, 0); }
void kandnd(const Opmask& r1, const Opmask& r2, const Opmask& r3) { opVex(r1, &r2, r3, VEX_L1 | MM_0F | PP_66, 0x42, 1); }
void korw(const Opmask& r1, const Opmask& r2, const Opmask& r3) { opVex(r1, &r2, r3, VEX_L1 | MM_0F, 0x45, 0); }
void korq(const Opmask& r1, const Opmask& r2, const Opmask& r3) { opVex(r1, &r2, r3, VEX_L1 | MM_0F, 0x45, 1); }
void korb(const Opmask& r1, const Opmask& r2, const Opmask& r3) { opVex(r1, &r2, r3, VEX_L1 | MM_0F | PP_66, 0x45, 0); }
void kord(const Opmask& r1, const Opmask& r2, const Opmask& r3) { opVex(r1, &r2, r3, VEX_L1 | MM_0F | PP_66, 0x45, 1); }
void kxnorw(const Opmask& r1, const Opmask& r2, const Opmask& r3) { opVex(r1, &r2, r3, VEX_L1 | MM_0F, 0x46, 0); }
void kxnorq(const Opmask& r1, const Opmask& r2, const Opmask& r3) { opVex(r1, &r2, r3, VEX_L1 | MM_0F, 0x46, 1); }
void kxnorb(const Opmask& r1, const Opmask& r2, const Opmask& r3) { opVex(r1, &r2, r3, VEX_L1 | MM_0F | PP_66, 0x46, 0); }
void kxnord(const Opmask& r1, const Opmask& r2, const Opmask& r3) { opVex(r1, &r2, r3, VEX_L1 | MM_0F | PP_66, 0x46, 1); }
void kxorw(const Opmask& r1, const Opmask& r2, const Opmask& r3) { opVex(r1, &r2, r3, VEX_L1 | MM_0F, 0x47, 0); }
void kxorq(const Opmask& r1, const Opmask& r2, const Opmask& r3) { opVex(r1, &r2, r3, VEX_L1 | MM_0F, 0x47, 1); }
void kxorb(const Opmask& r1, const Opmask& r2, const Opmask& r3) { opVex(r1, &r2, r3, VEX_L1 | MM_0F | PP_66, 0x47, 0); }
void kxord(const Opmask& r1, const Opmask& r2, const Opmask& r3) { opVex(r1, &r2, r3, VEX_L1 | MM_0F | PP_66, 0x47, 1); }
void kunpckbw(const Opmask& r1, const Opmask& r2, const Opmask& r3) { opVex(r1, &r2, r3, VEX_L1 | MM_0F | PP_66, 0x4B, 0); }
void kunpckwd(const Opmask& r1, const Opmask& r2, const Opmask& r3) { opVex(r1, &r2, r3, VEX_L1 | MM_0F, 0x4B, 0); }
void kunpckdq(const Opmask& r1, const Opmask& r2, const Opmask& r3) { opVex(r1, &r2, r3, VEX_L1 | MM_0F, 0x4B, 1); }
void knotw(const Opmask& r1, const Opmask& r2) { opVex(r1, 0, r2, MM_0F, 0x44, 0); }
void knotq(const Opmask& r1, const Opmask& r2) { opVex(r1, 0, r2, MM_0F, 0x44, 1); }
void knotb(const Opmask& r1, const Opmask& r2) { opVex(r1, 0, r2, MM_0F | PP_66, 0x44, 0); }
void knotd(const Opmask& r1, const Opmask& r2) { opVex(r1, 0, r2, MM_0F | PP_66, 0x44, 1); }
void kortestw(const Opmask& r1, const Opmask& r2) { opVex(r1, 0, r2, MM_0F, 0x98, 0); }
void kortestq(const Opmask& r1, const Opmask& r2) { opVex(r1, 0, r2, MM_0F, 0x98, 1); }
void kortestb(const Opmask& r1, const Opmask& r2) { opVex(r1, 0, r2, MM_0F | PP_66, 0x98, 0); }
void kortestd(const Opmask& r1, const Opmask& r2) { opVex(r1, 0, r2, MM_0F | PP_66, 0x98, 1); }
void ktestw(const Opmask& r1, const Opmask& r2) { opVex(r1, 0, r2, MM_0F, 0x99, 0); }
void ktestq(const Opmask& r1, const Opmask& r2) { opVex(r1, 0, r2, MM_0F, 0x99, 1); }
void ktestb(const Opmask& r1, const Opmask& r2) { opVex(r1, 0, r2, MM_0F | PP_66, 0x99, 0); }
void ktestd(const Opmask& r1, const Opmask& r2) { opVex(r1, 0, r2, MM_0F | PP_66, 0x99, 1); }
void kshiftlw(const Opmask& r1, const Opmask& r2, uint8 imm) { opVex(r1, 0, r2, PP_66 | MM_0F3A, 0x32, 1, imm); }
void kshiftlq(const Opmask& r1, const Opmask& r2, uint8 imm) { opVex(r1, 0, r2, PP_66 | MM_0F3A, 0x33, 1, imm); }
void kshiftlb(const Opmask& r1, const Opmask& r2, uint8 imm) { opVex(r1, 0, r2, PP_66 | MM_0F3A, 0x32, 0, imm); }
void kshiftld(const Opmask& r1, const Opmask& r2, uint8 imm) { opVex(r1, 0, r2, PP_66 | MM_0F3A, 0x33, 0, imm); }
void kshiftrw(const Opmask& r1, const Opmask& r2, uint8 imm) { opVex(r1, 0, r2, PP_66 | MM_0F3A, 0x30, 1, imm); }
void kshiftrq(const Opmask& r1, const Opmask& r2, uint8 imm) { opVex(r1, 0, r2, PP_66 | MM_0F3A, 0x31, 1, imm); }
void kshiftrb(const Opmask& r1, const Opmask& r2, uint8 imm) { opVex(r1, 0, r2, PP_66 | MM_0F3A, 0x30, 0, imm); }
void kshiftrd(const Opmask& r1, const Opmask& r2, uint8 imm) { opVex(r1, 0, r2, PP_66 | MM_0F3A, 0x31, 0, imm); }
void kmovw(const Opmask& k, const Operand& op) { opVex(k, 0, op, VEX_L0 | MM_0F, 0x90, 0); }
void kmovq(const Opmask& k, const Operand& op) { opVex(k, 0, op, VEX_L0 | MM_0F, 0x90, 1); }
void kmovb(const Opmask& k, const Operand& op) { opVex(k, 0, op, VEX_L0 | MM_0F | PP_66, 0x90, 0); }
void kmovd(const Opmask& k, const Operand& op) { opVex(k, 0, op, VEX_L0 | MM_0F | PP_66, 0x90, 1); }
void kmovw(const Address& addr, const Opmask& k) { opVex(k, 0, addr, VEX_L0 | MM_0F, 0x91, 0); }
void kmovq(const Address& addr, const Opmask& k) { opVex(k, 0, addr, VEX_L0 | MM_0F, 0x91, 1); }
void kmovb(const Address& addr, const Opmask& k) { opVex(k, 0, addr, VEX_L0 | MM_0F | PP_66, 0x91, 0); }
void kmovd(const Address& addr, const Opmask& k) { opVex(k, 0, addr, VEX_L0 | MM_0F | PP_66, 0x91, 1); }
void kmovw(const Opmask& k, const Reg32& r) { opVex(k, 0, r, VEX_L0 | MM_0F, 0x92, 0); }
void kmovw(const Reg32& r, const Opmask& k) { opVex(r, 0, k, VEX_L0 | MM_0F, 0x93, 0); }
#ifdef XBYAK64
void kmovq(const Opmask& k, const Reg64& r) { opVex(k, 0, r, VEX_L0 | MM_0F | PP_F2, 0x92, 1); }
void kmovq(const Reg64& r, const Opmask& k) { opVex(r, 0, k, VEX_L0 | MM_0F | PP_F2, 0x93, 1); }
#endif
void kmovb(const Opmask& k, const Reg32& r) { opVex(k, 0, r, VEX_L0 | MM_0F | PP_66, 0x92, 0); }
void kmovb(const Reg32& r, const Opmask& k) { opVex(r, 0, k, VEX_L0 | MM_0F | PP_66, 0x93, 0); }
void kmovd(const Opmask& k, const Reg32& r) { opVex(k, 0, r, VEX_L0 | MM_0F | PP_F2, 0x92, 0); }
void kmovd(const Reg32& r, const Opmask& k) { opVex(r, 0, k, VEX_L0 | MM_0F | PP_F2, 0x93, 0); }
#endif
