const char *getVersionString() const { return "7.35.3"; }
void aadd(const Address& addr, Reg32e reg) { opMR(addr, reg, T_0F38, 0x0FC, T_APX); }
void aand(const Address& addr, Reg32e reg) { opMR(addr, reg, T_0F38|T_66, 0x0FC, T_APX|T_66); }
void adc(const Operand& op, uint32_t imm) { opOI(op, imm, 0x10, 2); }
void adc(const Operand& op1, const Operand& op2) { opRO_MR(op1, op2, 0x10); }
void adc(Reg d, const Operand& op, uint32_t imm) { opROI(d, op, imm, T_NONE, 2); }
void adc(Reg d, const Operand& op1, const Operand& op2) { opROO(d, op1, op2, T_NONE, 0x10); }
void adcx(Reg32e d, Reg32e reg, const Operand& op) { opROO(d, op, reg, T_66, 0x66); }
void adcx(Reg32e reg, const Operand& op) { if (!reg.isREG(16|i32e) && reg.getBit() == op.getBit()) XBYAK_THROW(ERR_BAD_SIZE_OF_REGISTER) if (opROO(Reg(), op, reg, T_66, 0x66)) return; opRO(reg, op, T_66 | T_0F38, 0xF6); }
void add(const Operand& op, uint32_t imm) { opOI(op, imm, 0x00, 0); }
void add(const Operand& op1, const Operand& op2) { opRO_MR(op1, op2, 0x00); }
void add(Reg d, const Operand& op, uint32_t imm) { opROI(d, op, imm, T_NF|T_CODE1_IF1, 0); }
void add(Reg d, const Operand& op1, const Operand& op2) { opROO(d, op1, op2, T_NF|T_CODE1_IF1, 0x00); }
void addpd(Xmm xmm, const Operand& op) { opSSE(xmm, op, T_0F | T_66, 0x58, isXMM_XMMorMEM); }
void addps(Xmm xmm, const Operand& op) { opSSE(xmm, op, T_0F, 0x58, isXMM_XMMorMEM); }
void addsd(Xmm xmm, const Operand& op) { opSSE(xmm, op, T_0F | T_F2, 0x58, isXMM_XMMorMEM); }
void addss(Xmm xmm, const Operand& op) { opSSE(xmm, op, T_0F | T_F3, 0x58, isXMM_XMMorMEM); }
void addsubpd(Xmm xmm, const Operand& op) { opSSE(xmm, op, T_66|T_0F|T_YMM, 0xD0, isXMM_XMMorMEM); }
void addsubps(Xmm xmm, const Operand& op) { opSSE(xmm, op, T_F2|T_0F|T_YMM, 0xD0, isXMM_XMMorMEM); }
void adox(Reg32e d, Reg32e reg, const Operand& op) { opROO(d, op, reg, T_F3, 0x66); }
void adox(Reg32e reg, const Operand& op) { if (!reg.isREG(16|i32e) && reg.getBit() == op.getBit()) XBYAK_THROW(ERR_BAD_SIZE_OF_REGISTER) if (opROO(Reg(), op, reg, T_F3, 0x66)) return; opRO(reg, op, T_F3 | T_0F38, 0xF6); }
void aesdec(Xmm xmm, const Operand& op) { opSSE(xmm, op, T_66|T_0F38|T_YMM|T_EVEX, 0xDE, isXMM_XMMorMEM); }
void aesdeclast(Xmm xmm, const Operand& op) { opSSE(xmm, op, T_66|T_0F38|T_YMM|T_EVEX, 0xDF, isXMM_XMMorMEM); }
void aesenc(Xmm xmm, const Operand& op) { opSSE(xmm, op, T_66|T_0F38|T_YMM|T_EVEX, 0xDC, isXMM_XMMorMEM); }
void aesenclast(Xmm xmm, const Operand& op) { opSSE(xmm, op, T_66|T_0F38|T_YMM|T_EVEX, 0xDD, isXMM_XMMorMEM); }
void aesimc(Xmm xmm, const Operand& op) { opSSE(xmm, op, T_66|T_0F38|T_W0, 0xDB, isXMM_XMMorMEM, NONE); }
void aeskeygenassist(Xmm xmm, const Operand& op, uint8_t imm) { opSSE(xmm, op, T_66|T_0F3A, 0xDF, isXMM_XMMorMEM, imm); }
void and_(const Operand& op, uint32_t imm) { opOI(op, imm, 0x20, 4); }
void and_(const Operand& op1, const Operand& op2) { opRO_MR(op1, op2, 0x20); }
void and_(Reg d, const Operand& op, uint32_t imm) { opROI(d, op, imm, T_NF|T_CODE1_IF1, 4); }
void and_(Reg d, const Operand& op1, const Operand& op2) { opROO(d, op1, op2, T_NF|T_CODE1_IF1, 0x20); }
void andn(Reg32e r1, Reg32e r2, const Operand& op) { opRRO(r1, r2, op, T_APX|T_0F38|T_NF, 0xf2); }
void andnpd(Xmm xmm, const Operand& op) { opSSE(xmm, op, T_0F | T_66, 0x55, isXMM_XMMorMEM); }
void andnps(Xmm xmm, const Operand& op) { opSSE(xmm, op, T_0F, 0x55, isXMM_XMMorMEM); }
void andpd(Xmm xmm, const Operand& op) { opSSE(xmm, op, T_0F | T_66, 0x54, isXMM_XMMorMEM); }
void andps(Xmm xmm, const Operand& op) { opSSE(xmm, op, T_0F, 0x54, isXMM_XMMorMEM); }
void aor(const Address& addr, Reg32e reg) { opMR(addr, reg, T_0F38|T_F2, 0x0FC, T_APX|T_F2); }
void axor(const Address& addr, Reg32e reg) { opMR(addr, reg, T_0F38|T_F3, 0x0FC, T_APX|T_F3); }
void bextr(Reg32e r1, const Operand& op, Reg32e r2) { opRRO(r1, r2, op, T_APX|T_0F38|T_NF, 0xf7); }
void blendpd(Xmm xmm, const Operand& op, int imm) { opSSE(xmm, op, T_66 | T_0F3A, 0x0D, isXMM_XMMorMEM, static_cast<uint8_t>(imm)); }
void blendps(Xmm xmm, const Operand& op, int imm) { opSSE(xmm, op, T_66 | T_0F3A, 0x0C, isXMM_XMMorMEM, static_cast<uint8_t>(imm)); }
void blendvpd(Xmm xmm, const Operand& op) { opSSE(xmm, op, T_66|T_0F38, 0x15, isXMM_XMMorMEM, NONE); }
void blendvps(Xmm xmm, const Operand& op) { opSSE(xmm, op, T_66|T_0F38, 0x14, isXMM_XMMorMEM, NONE); }
void blsi(Reg32e r, const Operand& op) { opRRO(Reg32e(3, r.getBit()), r, op, T_APX|T_0F38|T_NF, 0xf3); }
void blsmsk(Reg32e r, const Operand& op) { opRRO(Reg32e(2, r.getBit()), r, op, T_APX|T_0F38|T_NF, 0xf3); }
void blsr(Reg32e r, const Operand& op) { opRRO(Reg32e(1, r.getBit()), r, op, T_APX|T_0F38|T_NF, 0xf3); }
void bnd() { db(0xF2); }
void bndcl(const BoundsReg& bnd, const Operand& op) { opRext(op, i32e, bnd.getIdx(), T_F3 | T_0F, 0x1A, !op.isMEM()); }
void bndcn(const BoundsReg& bnd, const Operand& op) { opRext(op, i32e, bnd.getIdx(), T_F2 | T_0F, 0x1B, !op.isMEM()); }
void bndcu(const BoundsReg& bnd, const Operand& op) { opRext(op, i32e, bnd.getIdx(), T_F2 | T_0F, 0x1A, !op.isMEM()); }
void bndldx(const BoundsReg& bnd, const Address& addr) { opMIB(addr, bnd, T_0F, 0x1A); }
void bndmk(const BoundsReg& bnd, const Address& addr) { opMR(addr, bnd, T_F3 | T_0F, 0x1B); }
void bndmov(const Address& addr, const BoundsReg& bnd) { opMR(addr, bnd, T_66 | T_0F, 0x1B); }
void bndmov(const BoundsReg& bnd, const Operand& op) { opRO(bnd, op, T_66 | T_0F, 0x1A, op.isBNDREG()); }
void bndstx(const Address& addr, const BoundsReg& bnd) { opMIB(addr, bnd, T_0F, 0x1B); }
void bsf(Reg reg, const Operand& op) { opRO(reg, op, T_0F, 0xBC, op.isREG(16|i32e)); }
void bsr(Reg reg, const Operand& op) { opRO(reg, op, T_0F, 0xBD, op.isREG(16|i32e)); }
void bt(const Operand& op, Reg reg) { opRO(reg, op, T_0F, 0xA3, op.isREG(16|i32e) && op.getBit() == reg.getBit()); }
void bt(const Operand& op, uint8_t imm) { opRext(op, 16|i32e, 4, T_0F, 0xba, false, 1); db(imm); }
void btc(const Operand& op, Reg reg) { opRO(reg, op, T_0F, 0xBB, op.isREG(16|i32e) && op.getBit() == reg.getBit()); }
void btc(const Operand& op, uint8_t imm) { opRext(op, 16|i32e, 7, T_0F, 0xba, false, 1); db(imm); }
void btr(const Operand& op, Reg reg) { opRO(reg, op, T_0F, 0xB3, op.isREG(16|i32e) && op.getBit() == reg.getBit()); }
void btr(const Operand& op, uint8_t imm) { opRext(op, 16|i32e, 6, T_0F, 0xba, false, 1); db(imm); }
void bts(const Operand& op, Reg reg) { opRO(reg, op, T_0F, 0xAB, op.isREG(16|i32e) && op.getBit() == reg.getBit()); }
void bts(const Operand& op, uint8_t imm) { opRext(op, 16|i32e, 5, T_0F, 0xba, false, 1); db(imm); }
void bzhi(Reg32e r1, const Operand& op, Reg32e r2) { opRRO(r1, r2, op, T_APX|T_0F38|T_NF, 0xf5); }
void cbw() { db(0x66); db(0x98); }
void ccmpa(const Operand& op, int imm, int dfv = 0) { opCcmpi(op, imm, dfv, 7); }
void ccmpa(const Operand& op1, const Operand& op2, int dfv = 0) { opCcmp(op1, op2, dfv, 0x38, 7); }
void ccmpae(const Operand& op, int imm, int dfv = 0) { opCcmpi(op, imm, dfv, 3); }
void ccmpae(const Operand& op1, const Operand& op2, int dfv = 0) { opCcmp(op1, op2, dfv, 0x38, 3); }
void ccmpb(const Operand& op, int imm, int dfv = 0) { opCcmpi(op, imm, dfv, 2); }
void ccmpb(const Operand& op1, const Operand& op2, int dfv = 0) { opCcmp(op1, op2, dfv, 0x38, 2); }
void ccmpbe(const Operand& op, int imm, int dfv = 0) { opCcmpi(op, imm, dfv, 6); }
void ccmpbe(const Operand& op1, const Operand& op2, int dfv = 0) { opCcmp(op1, op2, dfv, 0x38, 6); }
void ccmpc(const Operand& op, int imm, int dfv = 0) { opCcmpi(op, imm, dfv, 2); }
void ccmpc(const Operand& op1, const Operand& op2, int dfv = 0) { opCcmp(op1, op2, dfv, 0x38, 2); }
void ccmpe(const Operand& op, int imm, int dfv = 0) { opCcmpi(op, imm, dfv, 4); }
void ccmpe(const Operand& op1, const Operand& op2, int dfv = 0) { opCcmp(op1, op2, dfv, 0x38, 4); }
void ccmpf(const Operand& op, int imm, int dfv = 0) { opCcmpi(op, imm, dfv, 11); }
void ccmpf(const Operand& op1, const Operand& op2, int dfv = 0) { opCcmp(op1, op2, dfv, 0x38, 11); }
void ccmpg(const Operand& op, int imm, int dfv = 0) { opCcmpi(op, imm, dfv, 15); }
void ccmpg(const Operand& op1, const Operand& op2, int dfv = 0) { opCcmp(op1, op2, dfv, 0x38, 15); }
void ccmpge(const Operand& op, int imm, int dfv = 0) { opCcmpi(op, imm, dfv, 13); }
void ccmpge(const Operand& op1, const Operand& op2, int dfv = 0) { opCcmp(op1, op2, dfv, 0x38, 13); }
void ccmpl(const Operand& op, int imm, int dfv = 0) { opCcmpi(op, imm, dfv, 12); }
void ccmpl(const Operand& op1, const Operand& op2, int dfv = 0) { opCcmp(op1, op2, dfv, 0x38, 12); }
void ccmple(const Operand& op, int imm, int dfv = 0) { opCcmpi(op, imm, dfv, 14); }
void ccmple(const Operand& op1, const Operand& op2, int dfv = 0) { opCcmp(op1, op2, dfv, 0x38, 14); }
void ccmpna(const Operand& op, int imm, int dfv = 0) { opCcmpi(op, imm, dfv, 6); }
void ccmpna(const Operand& op1, const Operand& op2, int dfv = 0) { opCcmp(op1, op2, dfv, 0x38, 6); }
void ccmpnae(const Operand& op, int imm, int dfv = 0) { opCcmpi(op, imm, dfv, 2); }
void ccmpnae(const Operand& op1, const Operand& op2, int dfv = 0) { opCcmp(op1, op2, dfv, 0x38, 2); }
void ccmpnb(const Operand& op, int imm, int dfv = 0) { opCcmpi(op, imm, dfv, 3); }
void ccmpnb(const Operand& op1, const Operand& op2, int dfv = 0) { opCcmp(op1, op2, dfv, 0x38, 3); }
void ccmpnbe(const Operand& op, int imm, int dfv = 0) { opCcmpi(op, imm, dfv, 7); }
void ccmpnbe(const Operand& op1, const Operand& op2, int dfv = 0) { opCcmp(op1, op2, dfv, 0x38, 7); }
void ccmpnc(const Operand& op, int imm, int dfv = 0) { opCcmpi(op, imm, dfv, 3); }
void ccmpnc(const Operand& op1, const Operand& op2, int dfv = 0) { opCcmp(op1, op2, dfv, 0x38, 3); }
void ccmpne(const Operand& op, int imm, int dfv = 0) { opCcmpi(op, imm, dfv, 5); }
void ccmpne(const Operand& op1, const Operand& op2, int dfv = 0) { opCcmp(op1, op2, dfv, 0x38, 5); }
void ccmpng(const Operand& op, int imm, int dfv = 0) { opCcmpi(op, imm, dfv, 14); }
void ccmpng(const Operand& op1, const Operand& op2, int dfv = 0) { opCcmp(op1, op2, dfv, 0x38, 14); }
void ccmpnge(const Operand& op, int imm, int dfv = 0) { opCcmpi(op, imm, dfv, 12); }
void ccmpnge(const Operand& op1, const Operand& op2, int dfv = 0) { opCcmp(op1, op2, dfv, 0x38, 12); }
void ccmpnl(const Operand& op, int imm, int dfv = 0) { opCcmpi(op, imm, dfv, 13); }
void ccmpnl(const Operand& op1, const Operand& op2, int dfv = 0) { opCcmp(op1, op2, dfv, 0x38, 13); }
void ccmpnle(const Operand& op, int imm, int dfv = 0) { opCcmpi(op, imm, dfv, 15); }
void ccmpnle(const Operand& op1, const Operand& op2, int dfv = 0) { opCcmp(op1, op2, dfv, 0x38, 15); }
void ccmpno(const Operand& op, int imm, int dfv = 0) { opCcmpi(op, imm, dfv, 1); }
void ccmpno(const Operand& op1, const Operand& op2, int dfv = 0) { opCcmp(op1, op2, dfv, 0x38, 1); }
void ccmpns(const Operand& op, int imm, int dfv = 0) { opCcmpi(op, imm, dfv, 9); }
void ccmpns(const Operand& op1, const Operand& op2, int dfv = 0) { opCcmp(op1, op2, dfv, 0x38, 9); }
void ccmpnz(const Operand& op, int imm, int dfv = 0) { opCcmpi(op, imm, dfv, 5); }
void ccmpnz(const Operand& op1, const Operand& op2, int dfv = 0) { opCcmp(op1, op2, dfv, 0x38, 5); }
void ccmpo(const Operand& op, int imm, int dfv = 0) { opCcmpi(op, imm, dfv, 0); }
void ccmpo(const Operand& op1, const Operand& op2, int dfv = 0) { opCcmp(op1, op2, dfv, 0x38, 0); }
void ccmps(const Operand& op, int imm, int dfv = 0) { opCcmpi(op, imm, dfv, 8); }
void ccmps(const Operand& op1, const Operand& op2, int dfv = 0) { opCcmp(op1, op2, dfv, 0x38, 8); }
void ccmpt(const Operand& op, int imm, int dfv = 0) { opCcmpi(op, imm, dfv, 10); }
void ccmpt(const Operand& op1, const Operand& op2, int dfv = 0) { opCcmp(op1, op2, dfv, 0x38, 10); }
void ccmpz(const Operand& op, int imm, int dfv = 0) { opCcmpi(op, imm, dfv, 4); }
void ccmpz(const Operand& op1, const Operand& op2, int dfv = 0) { opCcmp(op1, op2, dfv, 0x38, 4); }
void cdq() { db(0x99); }
void cfcmovb(const Operand& op1, const Operand& op2) { opCfcmov(Reg(), op1, op2, 0x42); }
void cfcmovb(Reg d, Reg r, const Operand& op) { opCfcmov(d|T_nf, op, r, 0x42); }
void cfcmovbe(const Operand& op1, const Operand& op2) { opCfcmov(Reg(), op1, op2, 0x46); }
void cfcmovbe(Reg d, Reg r, const Operand& op) { opCfcmov(d|T_nf, op, r, 0x46); }
void cfcmovl(const Operand& op1, const Operand& op2) { opCfcmov(Reg(), op1, op2, 0x4C); }
void cfcmovl(Reg d, Reg r, const Operand& op) { opCfcmov(d|T_nf, op, r, 0x4C); }
void cfcmovle(const Operand& op1, const Operand& op2) { opCfcmov(Reg(), op1, op2, 0x4E); }
void cfcmovle(Reg d, Reg r, const Operand& op) { opCfcmov(d|T_nf, op, r, 0x4E); }
void cfcmovnb(const Operand& op1, const Operand& op2) { opCfcmov(Reg(), op1, op2, 0x43); }
void cfcmovnb(Reg d, Reg r, const Operand& op) { opCfcmov(d|T_nf, op, r, 0x43); }
void cfcmovnbe(const Operand& op1, const Operand& op2) { opCfcmov(Reg(), op1, op2, 0x47); }
void cfcmovnbe(Reg d, Reg r, const Operand& op) { opCfcmov(d|T_nf, op, r, 0x47); }
void cfcmovnl(const Operand& op1, const Operand& op2) { opCfcmov(Reg(), op1, op2, 0x4D); }
void cfcmovnl(Reg d, Reg r, const Operand& op) { opCfcmov(d|T_nf, op, r, 0x4D); }
void cfcmovnle(const Operand& op1, const Operand& op2) { opCfcmov(Reg(), op1, op2, 0x4F); }
void cfcmovnle(Reg d, Reg r, const Operand& op) { opCfcmov(d|T_nf, op, r, 0x4F); }
void cfcmovno(const Operand& op1, const Operand& op2) { opCfcmov(Reg(), op1, op2, 0x41); }
void cfcmovno(Reg d, Reg r, const Operand& op) { opCfcmov(d|T_nf, op, r, 0x41); }
void cfcmovnp(const Operand& op1, const Operand& op2) { opCfcmov(Reg(), op1, op2, 0x4B); }
void cfcmovnp(Reg d, Reg r, const Operand& op) { opCfcmov(d|T_nf, op, r, 0x4B); }
void cfcmovns(const Operand& op1, const Operand& op2) { opCfcmov(Reg(), op1, op2, 0x49); }
void cfcmovns(Reg d, Reg r, const Operand& op) { opCfcmov(d|T_nf, op, r, 0x49); }
void cfcmovnz(const Operand& op1, const Operand& op2) { opCfcmov(Reg(), op1, op2, 0x45); }
void cfcmovnz(Reg d, Reg r, const Operand& op) { opCfcmov(d|T_nf, op, r, 0x45); }
void cfcmovo(const Operand& op1, const Operand& op2) { opCfcmov(Reg(), op1, op2, 0x40); }
void cfcmovo(Reg d, Reg r, const Operand& op) { opCfcmov(d|T_nf, op, r, 0x40); }
void cfcmovp(const Operand& op1, const Operand& op2) { opCfcmov(Reg(), op1, op2, 0x4A); }
void cfcmovp(Reg d, Reg r, const Operand& op) { opCfcmov(d|T_nf, op, r, 0x4A); }
void cfcmovs(const Operand& op1, const Operand& op2) { opCfcmov(Reg(), op1, op2, 0x48); }
void cfcmovs(Reg d, Reg r, const Operand& op) { opCfcmov(d|T_nf, op, r, 0x48); }
void cfcmovz(const Operand& op1, const Operand& op2) { opCfcmov(Reg(), op1, op2, 0x44); }
void cfcmovz(Reg d, Reg r, const Operand& op) { opCfcmov(d|T_nf, op, r, 0x44); }
void clc() { db(0xF8); }
void cld() { db(0xFC); }
void cldemote(const Address& addr) { opMR(addr, eax, T_0F, 0x1C); }
void clflush(const Address& addr) { opMR(addr, Reg32(7), T_0F, 0xAE); }
void clflushopt(const Address& addr) { opMR(addr, Reg32(7), T_66 | T_0F, 0xAE); }
void cli() { db(0xFA); }
void clwb(const Address& addr) { opMR(addr, esi, T_66 | T_0F, 0xAE); }
void clzero() { db(0x0F); db(0x01); db(0xFC); }
void cmc() { db(0xF5); }
void cmova(Reg d, Reg reg, const Operand& op) { opROO(d, op, reg, T_APX|T_ND1, 0x40 | 7); }//-V524
void cmova(Reg reg, const Operand& op) { opRO(reg, op, T_0F, 0x40 | 7, op.isREG(16|i32e)); }//-V524
void cmovae(Reg d, Reg reg, const Operand& op) { opROO(d, op, reg, T_APX|T_ND1, 0x40 | 3); }//-V524
void cmovae(Reg reg, const Operand& op) { opRO(reg, op, T_0F, 0x40 | 3, op.isREG(16|i32e)); }//-V524
void cmovb(Reg d, Reg reg, const Operand& op) { opROO(d, op, reg, T_APX|T_ND1, 0x40 | 2); }//-V524
void cmovb(Reg reg, const Operand& op) { opRO(reg, op, T_0F, 0x40 | 2, op.isREG(16|i32e)); }//-V524
void cmovbe(Reg d, Reg reg, const Operand& op) { opROO(d, op, reg, T_APX|T_ND1, 0x40 | 6); }//-V524
void cmovbe(Reg reg, const Operand& op) { opRO(reg, op, T_0F, 0x40 | 6, op.isREG(16|i32e)); }//-V524
void cmovc(Reg d, Reg reg, const Operand& op) { opROO(d, op, reg, T_APX|T_ND1, 0x40 | 2); }//-V524
void cmovc(Reg reg, const Operand& op) { opRO(reg, op, T_0F, 0x40 | 2, op.isREG(16|i32e)); }//-V524
void cmove(Reg d, Reg reg, const Operand& op) { opROO(d, op, reg, T_APX|T_ND1, 0x40 | 4); }//-V524
void cmove(Reg reg, const Operand& op) { opRO(reg, op, T_0F, 0x40 | 4, op.isREG(16|i32e)); }//-V524
void cmovg(Reg d, Reg reg, const Operand& op) { opROO(d, op, reg, T_APX|T_ND1, 0x40 | 15); }//-V524
void cmovg(Reg reg, const Operand& op) { opRO(reg, op, T_0F, 0x40 | 15, op.isREG(16|i32e)); }//-V524
void cmovge(Reg d, Reg reg, const Operand& op) { opROO(d, op, reg, T_APX|T_ND1, 0x40 | 13); }//-V524
void cmovge(Reg reg, const Operand& op) { opRO(reg, op, T_0F, 0x40 | 13, op.isREG(16|i32e)); }//-V524
void cmovl(Reg d, Reg reg, const Operand& op) { opROO(d, op, reg, T_APX|T_ND1, 0x40 | 12); }//-V524
void cmovl(Reg reg, const Operand& op) { opRO(reg, op, T_0F, 0x40 | 12, op.isREG(16|i32e)); }//-V524
void cmovle(Reg d, Reg reg, const Operand& op) { opROO(d, op, reg, T_APX|T_ND1, 0x40 | 14); }//-V524
void cmovle(Reg reg, const Operand& op) { opRO(reg, op, T_0F, 0x40 | 14, op.isREG(16|i32e)); }//-V524
void cmovna(Reg d, Reg reg, const Operand& op) { opROO(d, op, reg, T_APX|T_ND1, 0x40 | 6); }//-V524
void cmovna(Reg reg, const Operand& op) { opRO(reg, op, T_0F, 0x40 | 6, op.isREG(16|i32e)); }//-V524
void cmovnae(Reg d, Reg reg, const Operand& op) { opROO(d, op, reg, T_APX|T_ND1, 0x40 | 2); }//-V524
void cmovnae(Reg reg, const Operand& op) { opRO(reg, op, T_0F, 0x40 | 2, op.isREG(16|i32e)); }//-V524
void cmovnb(Reg d, Reg reg, const Operand& op) { opROO(d, op, reg, T_APX|T_ND1, 0x40 | 3); }//-V524
void cmovnb(Reg reg, const Operand& op) { opRO(reg, op, T_0F, 0x40 | 3, op.isREG(16|i32e)); }//-V524
void cmovnbe(Reg d, Reg reg, const Operand& op) { opROO(d, op, reg, T_APX|T_ND1, 0x40 | 7); }//-V524
void cmovnbe(Reg reg, const Operand& op) { opRO(reg, op, T_0F, 0x40 | 7, op.isREG(16|i32e)); }//-V524
void cmovnc(Reg d, Reg reg, const Operand& op) { opROO(d, op, reg, T_APX|T_ND1, 0x40 | 3); }//-V524
void cmovnc(Reg reg, const Operand& op) { opRO(reg, op, T_0F, 0x40 | 3, op.isREG(16|i32e)); }//-V524
void cmovne(Reg d, Reg reg, const Operand& op) { opROO(d, op, reg, T_APX|T_ND1, 0x40 | 5); }//-V524
void cmovne(Reg reg, const Operand& op) { opRO(reg, op, T_0F, 0x40 | 5, op.isREG(16|i32e)); }//-V524
void cmovng(Reg d, Reg reg, const Operand& op) { opROO(d, op, reg, T_APX|T_ND1, 0x40 | 14); }//-V524
void cmovng(Reg reg, const Operand& op) { opRO(reg, op, T_0F, 0x40 | 14, op.isREG(16|i32e)); }//-V524
void cmovnge(Reg d, Reg reg, const Operand& op) { opROO(d, op, reg, T_APX|T_ND1, 0x40 | 12); }//-V524
void cmovnge(Reg reg, const Operand& op) { opRO(reg, op, T_0F, 0x40 | 12, op.isREG(16|i32e)); }//-V524
void cmovnl(Reg d, Reg reg, const Operand& op) { opROO(d, op, reg, T_APX|T_ND1, 0x40 | 13); }//-V524
void cmovnl(Reg reg, const Operand& op) { opRO(reg, op, T_0F, 0x40 | 13, op.isREG(16|i32e)); }//-V524
void cmovnle(Reg d, Reg reg, const Operand& op) { opROO(d, op, reg, T_APX|T_ND1, 0x40 | 15); }//-V524
void cmovnle(Reg reg, const Operand& op) { opRO(reg, op, T_0F, 0x40 | 15, op.isREG(16|i32e)); }//-V524
void cmovno(Reg d, Reg reg, const Operand& op) { opROO(d, op, reg, T_APX|T_ND1, 0x40 | 1); }//-V524
void cmovno(Reg reg, const Operand& op) { opRO(reg, op, T_0F, 0x40 | 1, op.isREG(16|i32e)); }//-V524
void cmovnp(Reg d, Reg reg, const Operand& op) { opROO(d, op, reg, T_APX|T_ND1, 0x40 | 11); }//-V524
void cmovnp(Reg reg, const Operand& op) { opRO(reg, op, T_0F, 0x40 | 11, op.isREG(16|i32e)); }//-V524
void cmovns(Reg d, Reg reg, const Operand& op) { opROO(d, op, reg, T_APX|T_ND1, 0x40 | 9); }//-V524
void cmovns(Reg reg, const Operand& op) { opRO(reg, op, T_0F, 0x40 | 9, op.isREG(16|i32e)); }//-V524
void cmovnz(Reg d, Reg reg, const Operand& op) { opROO(d, op, reg, T_APX|T_ND1, 0x40 | 5); }//-V524
void cmovnz(Reg reg, const Operand& op) { opRO(reg, op, T_0F, 0x40 | 5, op.isREG(16|i32e)); }//-V524
void cmovo(Reg d, Reg reg, const Operand& op) { opROO(d, op, reg, T_APX|T_ND1, 0x40 | 0); }//-V524
void cmovo(Reg reg, const Operand& op) { opRO(reg, op, T_0F, 0x40 | 0, op.isREG(16|i32e)); }//-V524
void cmovp(Reg d, Reg reg, const Operand& op) { opROO(d, op, reg, T_APX|T_ND1, 0x40 | 10); }//-V524
void cmovp(Reg reg, const Operand& op) { opRO(reg, op, T_0F, 0x40 | 10, op.isREG(16|i32e)); }//-V524
void cmovpe(Reg d, Reg reg, const Operand& op) { opROO(d, op, reg, T_APX|T_ND1, 0x40 | 10); }//-V524
void cmovpe(Reg reg, const Operand& op) { opRO(reg, op, T_0F, 0x40 | 10, op.isREG(16|i32e)); }//-V524
void cmovpo(Reg d, Reg reg, const Operand& op) { opROO(d, op, reg, T_APX|T_ND1, 0x40 | 11); }//-V524
void cmovpo(Reg reg, const Operand& op) { opRO(reg, op, T_0F, 0x40 | 11, op.isREG(16|i32e)); }//-V524
void cmovs(Reg d, Reg reg, const Operand& op) { opROO(d, op, reg, T_APX|T_ND1, 0x40 | 8); }//-V524
void cmovs(Reg reg, const Operand& op) { opRO(reg, op, T_0F, 0x40 | 8, op.isREG(16|i32e)); }//-V524
void cmovz(Reg d, Reg reg, const Operand& op) { opROO(d, op, reg, T_APX|T_ND1, 0x40 | 4); }//-V524
void cmovz(Reg reg, const Operand& op) { opRO(reg, op, T_0F, 0x40 | 4, op.isREG(16|i32e)); }//-V524
void cmp(const Operand& op, uint32_t imm) { opOI(op, imm, 0x38, 7); }
void cmp(const Operand& op1, const Operand& op2) { opRO_MR(op1, op2, 0x38); }
void cmpeqpd(Xmm x, const Operand& op) { cmppd(x, op, 0); }
void cmpeqps(Xmm x, const Operand& op) { cmpps(x, op, 0); }
void cmpeqsd(Xmm x, const Operand& op) { cmpsd(x, op, 0); }
void cmpeqss(Xmm x, const Operand& op) { cmpss(x, op, 0); }
void cmplepd(Xmm x, const Operand& op) { cmppd(x, op, 2); }
void cmpleps(Xmm x, const Operand& op) { cmpps(x, op, 2); }
void cmplesd(Xmm x, const Operand& op) { cmpsd(x, op, 2); }
void cmpless(Xmm x, const Operand& op) { cmpss(x, op, 2); }
void cmpltpd(Xmm x, const Operand& op) { cmppd(x, op, 1); }
void cmpltps(Xmm x, const Operand& op) { cmpps(x, op, 1); }
void cmpltsd(Xmm x, const Operand& op) { cmpsd(x, op, 1); }
void cmpltss(Xmm x, const Operand& op) { cmpss(x, op, 1); }
void cmpneqpd(Xmm x, const Operand& op) { cmppd(x, op, 4); }
void cmpneqps(Xmm x, const Operand& op) { cmpps(x, op, 4); }
void cmpneqsd(Xmm x, const Operand& op) { cmpsd(x, op, 4); }
void cmpneqss(Xmm x, const Operand& op) { cmpss(x, op, 4); }
void cmpnlepd(Xmm x, const Operand& op) { cmppd(x, op, 6); }
void cmpnleps(Xmm x, const Operand& op) { cmpps(x, op, 6); }
void cmpnlesd(Xmm x, const Operand& op) { cmpsd(x, op, 6); }
void cmpnless(Xmm x, const Operand& op) { cmpss(x, op, 6); }
void cmpnltpd(Xmm x, const Operand& op) { cmppd(x, op, 5); }
void cmpnltps(Xmm x, const Operand& op) { cmpps(x, op, 5); }
void cmpnltsd(Xmm x, const Operand& op) { cmpsd(x, op, 5); }
void cmpnltss(Xmm x, const Operand& op) { cmpss(x, op, 5); }
void cmpordpd(Xmm x, const Operand& op) { cmppd(x, op, 7); }
void cmpordps(Xmm x, const Operand& op) { cmpps(x, op, 7); }
void cmpordsd(Xmm x, const Operand& op) { cmpsd(x, op, 7); }
void cmpordss(Xmm x, const Operand& op) { cmpss(x, op, 7); }
void cmppd(Xmm xmm, const Operand& op, uint8_t imm8) { opSSE(xmm, op, T_0F | T_66, 0xC2, isXMM_XMMorMEM, imm8); }
void cmpps(Xmm xmm, const Operand& op, uint8_t imm8) { opSSE(xmm, op, T_0F, 0xC2, isXMM_XMMorMEM, imm8); }
void cmpsb() { db(0xA6); }
void cmpsd() { db(0xA7); }
void cmpsd(Xmm xmm, const Operand& op, uint8_t imm8) { opSSE(xmm, op, T_0F | T_F2, 0xC2, isXMM_XMMorMEM, imm8); }
void cmpss(Xmm xmm, const Operand& op, uint8_t imm8) { opSSE(xmm, op, T_0F | T_F3, 0xC2, isXMM_XMMorMEM, imm8); }
void cmpsw() { db(0x66); db(0xA7); }
void cmpunordpd(Xmm x, const Operand& op) { cmppd(x, op, 3); }
void cmpunordps(Xmm x, const Operand& op) { cmpps(x, op, 3); }
void cmpunordsd(Xmm x, const Operand& op) { cmpsd(x, op, 3); }
void cmpunordss(Xmm x, const Operand& op) { cmpss(x, op, 3); }
void cmpxchg(const Operand& op, Reg reg) { opRO(reg, op, T_0F, 0xB0 | (reg.isBit(8) ? 0 : 1), op.getBit() == reg.getBit()); }
void cmpxchg8b(const Address& addr) { opMR(addr, Reg32(1), T_0F, 0xC7); }
void comisd(Xmm xmm, const Operand& op) { opSSE(xmm, op, T_66|T_0F, 0x2F, isXMM_XMMorMEM); }
void comiss(Xmm xmm, const Operand& op) { opSSE(xmm, op, T_0F, 0x2F, isXMM_XMMorMEM); }
void cpuid() { db(0x0F); db(0xA2); }
void crc32(Reg32e r, const Operand& op) { if (!((r.isBit(32) && op.isBit(8|16|32)) || (r.isBit(64) && op.isBit(8|64)))) XBYAK_THROW(ERR_BAD_SIZE_OF_REGISTER) int code = 0xF0 | (op.isBit(8) ? 0 : 1); uint64_t type = op.isBit(16) ? T_66:0; type |= T_ALLOW_DIFF_SIZE; if (opROO(Reg(), op, static_cast<Reg >(r), T_APX|type, code)) return; opRO(r, op, T_F2|T_0F38|type, code); }
void ctesta(const Operand& op, Reg r, int dfv = 0) { opCcmp(op, r, dfv, 0x84, 7); }
void ctesta(const Operand& op, int imm, int dfv = 0) { opTesti(op, imm, dfv, 7); }
void ctestae(const Operand& op, Reg r, int dfv = 0) { opCcmp(op, r, dfv, 0x84, 3); }
void ctestae(const Operand& op, int imm, int dfv = 0) { opTesti(op, imm, dfv, 3); }
void ctestb(const Operand& op, Reg r, int dfv = 0) { opCcmp(op, r, dfv, 0x84, 2); }
void ctestb(const Operand& op, int imm, int dfv = 0) { opTesti(op, imm, dfv, 2); }
void ctestbe(const Operand& op, Reg r, int dfv = 0) { opCcmp(op, r, dfv, 0x84, 6); }
void ctestbe(const Operand& op, int imm, int dfv = 0) { opTesti(op, imm, dfv, 6); }
void ctestc(const Operand& op, Reg r, int dfv = 0) { opCcmp(op, r, dfv, 0x84, 2); }
void ctestc(const Operand& op, int imm, int dfv = 0) { opTesti(op, imm, dfv, 2); }
void cteste(const Operand& op, Reg r, int dfv = 0) { opCcmp(op, r, dfv, 0x84, 4); }
void cteste(const Operand& op, int imm, int dfv = 0) { opTesti(op, imm, dfv, 4); }
void ctestf(const Operand& op, Reg r, int dfv = 0) { opCcmp(op, r, dfv, 0x84, 11); }
void ctestf(const Operand& op, int imm, int dfv = 0) { opTesti(op, imm, dfv, 11); }
void ctestg(const Operand& op, Reg r, int dfv = 0) { opCcmp(op, r, dfv, 0x84, 15); }
void ctestg(const Operand& op, int imm, int dfv = 0) { opTesti(op, imm, dfv, 15); }
void ctestge(const Operand& op, Reg r, int dfv = 0) { opCcmp(op, r, dfv, 0x84, 13); }
void ctestge(const Operand& op, int imm, int dfv = 0) { opTesti(op, imm, dfv, 13); }
void ctestl(const Operand& op, Reg r, int dfv = 0) { opCcmp(op, r, dfv, 0x84, 12); }
void ctestl(const Operand& op, int imm, int dfv = 0) { opTesti(op, imm, dfv, 12); }
void ctestle(const Operand& op, Reg r, int dfv = 0) { opCcmp(op, r, dfv, 0x84, 14); }
void ctestle(const Operand& op, int imm, int dfv = 0) { opTesti(op, imm, dfv, 14); }
void ctestna(const Operand& op, Reg r, int dfv = 0) { opCcmp(op, r, dfv, 0x84, 6); }
void ctestna(const Operand& op, int imm, int dfv = 0) { opTesti(op, imm, dfv, 6); }
void ctestnae(const Operand& op, Reg r, int dfv = 0) { opCcmp(op, r, dfv, 0x84, 2); }
void ctestnae(const Operand& op, int imm, int dfv = 0) { opTesti(op, imm, dfv, 2); }
void ctestnb(const Operand& op, Reg r, int dfv = 0) { opCcmp(op, r, dfv, 0x84, 3); }
void ctestnb(const Operand& op, int imm, int dfv = 0) { opTesti(op, imm, dfv, 3); }
void ctestnbe(const Operand& op, Reg r, int dfv = 0) { opCcmp(op, r, dfv, 0x84, 7); }
void ctestnbe(const Operand& op, int imm, int dfv = 0) { opTesti(op, imm, dfv, 7); }
void ctestnc(const Operand& op, Reg r, int dfv = 0) { opCcmp(op, r, dfv, 0x84, 3); }
void ctestnc(const Operand& op, int imm, int dfv = 0) { opTesti(op, imm, dfv, 3); }
void ctestne(const Operand& op, Reg r, int dfv = 0) { opCcmp(op, r, dfv, 0x84, 5); }
void ctestne(const Operand& op, int imm, int dfv = 0) { opTesti(op, imm, dfv, 5); }
void ctestng(const Operand& op, Reg r, int dfv = 0) { opCcmp(op, r, dfv, 0x84, 14); }
void ctestng(const Operand& op, int imm, int dfv = 0) { opTesti(op, imm, dfv, 14); }
void ctestnge(const Operand& op, Reg r, int dfv = 0) { opCcmp(op, r, dfv, 0x84, 12); }
void ctestnge(const Operand& op, int imm, int dfv = 0) { opTesti(op, imm, dfv, 12); }
void ctestnl(const Operand& op, Reg r, int dfv = 0) { opCcmp(op, r, dfv, 0x84, 13); }
void ctestnl(const Operand& op, int imm, int dfv = 0) { opTesti(op, imm, dfv, 13); }
void ctestnle(const Operand& op, Reg r, int dfv = 0) { opCcmp(op, r, dfv, 0x84, 15); }
void ctestnle(const Operand& op, int imm, int dfv = 0) { opTesti(op, imm, dfv, 15); }
void ctestno(const Operand& op, Reg r, int dfv = 0) { opCcmp(op, r, dfv, 0x84, 1); }
void ctestno(const Operand& op, int imm, int dfv = 0) { opTesti(op, imm, dfv, 1); }
void ctestns(const Operand& op, Reg r, int dfv = 0) { opCcmp(op, r, dfv, 0x84, 9); }
void ctestns(const Operand& op, int imm, int dfv = 0) { opTesti(op, imm, dfv, 9); }
void ctestnz(const Operand& op, Reg r, int dfv = 0) { opCcmp(op, r, dfv, 0x84, 5); }
void ctestnz(const Operand& op, int imm, int dfv = 0) { opTesti(op, imm, dfv, 5); }
void ctesto(const Operand& op, Reg r, int dfv = 0) { opCcmp(op, r, dfv, 0x84, 0); }
void ctesto(const Operand& op, int imm, int dfv = 0) { opTesti(op, imm, dfv, 0); }
void ctests(const Operand& op, Reg r, int dfv = 0) { opCcmp(op, r, dfv, 0x84, 8); }
void ctests(const Operand& op, int imm, int dfv = 0) { opTesti(op, imm, dfv, 8); }
void ctestt(const Operand& op, Reg r, int dfv = 0) { opCcmp(op, r, dfv, 0x84, 10); }
void ctestt(const Operand& op, int imm, int dfv = 0) { opTesti(op, imm, dfv, 10); }
void ctestz(const Operand& op, Reg r, int dfv = 0) { opCcmp(op, r, dfv, 0x84, 4); }
void ctestz(const Operand& op, int imm, int dfv = 0) { opTesti(op, imm, dfv, 4); }
void cvtdq2pd(Xmm xmm, const Operand& op) { opSSE(xmm, op, T_F3|T_0F, 0xE6, isXMM_XMMorMEM); }
void cvtdq2ps(Xmm xmm, const Operand& op) { opSSE(xmm, op, T_0F, 0x5B, isXMM_XMMorMEM); }
void cvtpd2dq(Xmm xmm, const Operand& op) { opSSE(xmm, op, T_F2|T_0F, 0xE6, isXMM_XMMorMEM); }
void cvtpd2pi(Reg reg, const Operand& op) { opSSE(reg, op, T_66|T_0F, 0x2D, isMMX_XMMorMEM); }
void cvtpd2ps(Xmm xmm, const Operand& op) { opSSE(xmm, op, T_66|T_0F, 0x5A, isXMM_XMMorMEM); }
void cvtpi2pd(Reg reg, const Operand& op) { opSSE(reg, op, T_66|T_0F, 0x2A, isXMM_MMXorMEM); }
void cvtpi2ps(Reg reg, const Operand& op) { opSSE(reg, op, T_0F, 0x2A, isXMM_MMXorMEM); }
void cvtps2dq(Xmm xmm, const Operand& op) { opSSE(xmm, op, T_66|T_0F, 0x5B, isXMM_XMMorMEM); }
void cvtps2pd(Xmm xmm, const Operand& op) { opSSE(xmm, op, T_0F, 0x5A, isXMM_XMMorMEM); }
void cvtps2pi(Reg reg, const Operand& op) { opSSE(reg, op, T_0F, 0x2D, isMMX_XMMorMEM); }
void cvtsd2si(Reg reg, const Operand& op) { opSSE(reg, op, T_F2|T_0F, 0x2D, isREG32_XMMorMEM); }
void cvtsd2ss(Xmm xmm, const Operand& op) { opSSE(xmm, op, T_F2|T_0F, 0x5A, isXMM_XMMorMEM); }
void cvtsi2sd(Reg reg, const Operand& op) { opSSE(reg, op, T_F2|T_0F, 0x2A, isXMM_REG32orMEM); }
void cvtsi2ss(Reg reg, const Operand& op) { opSSE(reg, op, T_F3|T_0F, 0x2A, isXMM_REG32orMEM); }
void cvtss2sd(Xmm xmm, const Operand& op) { opSSE(xmm, op, T_F3|T_0F, 0x5A, isXMM_XMMorMEM); }
void cvtss2si(Reg reg, const Operand& op) { opSSE(reg, op, T_F3|T_0F, 0x2D, isREG32_XMMorMEM); }
void cvttpd2dq(Xmm xmm, const Operand& op) { opSSE(xmm, op, T_66|T_0F, 0xE6, isXMM_XMMorMEM); }
void cvttpd2pi(Reg reg, const Operand& op) { opSSE(reg, op, T_66|T_0F, 0x2C, isMMX_XMMorMEM); }
void cvttps2dq(Xmm xmm, const Operand& op) { opSSE(xmm, op, T_F3|T_0F, 0x5B, isXMM_XMMorMEM); }
void cvttps2pi(Reg reg, const Operand& op) { opSSE(reg, op, T_0F, 0x2C, isMMX_XMMorMEM); }
void cvttsd2si(Reg reg, const Operand& op) { opSSE(reg, op, T_F2|T_0F, 0x2C, isREG32_XMMorMEM); }
void cvttss2si(Reg reg, const Operand& op) { opSSE(reg, op, T_F3|T_0F, 0x2C, isREG32_XMMorMEM); }
void cwd() { db(0x66); db(0x99); }
void cwde() { db(0x98); }
void dec(const Operand& op) { opIncDec(Reg(), op, 1); }
void dec(Reg d, const Operand& op) { opIncDec(d, op, 1); }
void div(const Operand& op) { opRext(op, 0, 6, T_APX|T_NF|T_CODE1_IF1, 0xF6); }
void divpd(Xmm xmm, const Operand& op) { opSSE(xmm, op, T_0F | T_66, 0x5E, isXMM_XMMorMEM); }
void divps(Xmm xmm, const Operand& op) { opSSE(xmm, op, T_0F, 0x5E, isXMM_XMMorMEM); }
void divsd(Xmm xmm, const Operand& op) { opSSE(xmm, op, T_0F | T_F2, 0x5E, isXMM_XMMorMEM); }
void divss(Xmm xmm, const Operand& op) { opSSE(xmm, op, T_0F | T_F3, 0x5E, isXMM_XMMorMEM); }
void dppd(Xmm xmm, const Operand& op, int imm) { opSSE(xmm, op, T_66 | T_0F3A, 0x41, isXMM_XMMorMEM, static_cast<uint8_t>(imm)); }
void dpps(Xmm xmm, const Operand& op, int imm) { opSSE(xmm, op, T_66 | T_0F3A, 0x40, isXMM_XMMorMEM, static_cast<uint8_t>(imm)); }
void emms() { db(0x0F); db(0x77); }
void endbr32() { db(0xF3); db(0x0F); db(0x1E); db(0xFB); }
void endbr64() { db(0xF3); db(0x0F); db(0x1E); db(0xFA); }
void enter(uint16_t x, uint8_t y) { db(0xC8); dw(x); db(y); }
void extractps(const Operand& op, Xmm xmm, uint8_t imm) { opExt(op, xmm, 0x17, imm); }
void f2xm1() { db(0xD9); db(0xF0); }
void fabs() { db(0xD9); db(0xE1); }
void fadd(const Address& addr) { opFpuMem(addr, 0x00, 0xD8, 0xDC, 0, 0); }
void fadd(Fpu reg1) { opFpuFpu(st0, reg1, 0xD8C0, 0xDCC0); }
void fadd(Fpu reg1, Fpu reg2) { opFpuFpu(reg1, reg2, 0xD8C0, 0xDCC0); }
void faddp() { db(0xDE); db(0xC1); }
void faddp(Fpu reg1) { opFpuFpu(reg1, st0, 0x0000, 0xDEC0); }
void faddp(Fpu reg1, Fpu reg2) { opFpuFpu(reg1, reg2, 0x0000, 0xDEC0); }
void fbld(const Address& addr) { opMR(addr, Reg32(4), 0, 0xDF); }
void fbstp(const Address& addr) { opMR(addr, Reg32(6), 0, 0xDF); }
void fchs() { db(0xD9); db(0xE0); }
void fclex() { db(0x9B); db(0xDB); db(0xE2); }
void fcmovb(Fpu reg1) { opFpuFpu(st0, reg1, 0xDAC0, 0x00C0); }
void fcmovb(Fpu reg1, Fpu reg2) { opFpuFpu(reg1, reg2, 0xDAC0, 0x00C0); }
void fcmovbe(Fpu reg1) { opFpuFpu(st0, reg1, 0xDAD0, 0x00D0); }
void fcmovbe(Fpu reg1, Fpu reg2) { opFpuFpu(reg1, reg2, 0xDAD0, 0x00D0); }
void fcmove(Fpu reg1) { opFpuFpu(st0, reg1, 0xDAC8, 0x00C8); }
void fcmove(Fpu reg1, Fpu reg2) { opFpuFpu(reg1, reg2, 0xDAC8, 0x00C8); }
void fcmovnb(Fpu reg1) { opFpuFpu(st0, reg1, 0xDBC0, 0x00C0); }
void fcmovnb(Fpu reg1, Fpu reg2) { opFpuFpu(reg1, reg2, 0xDBC0, 0x00C0); }
void fcmovnbe(Fpu reg1) { opFpuFpu(st0, reg1, 0xDBD0, 0x00D0); }
void fcmovnbe(Fpu reg1, Fpu reg2) { opFpuFpu(reg1, reg2, 0xDBD0, 0x00D0); }
void fcmovne(Fpu reg1) { opFpuFpu(st0, reg1, 0xDBC8, 0x00C8); }
void fcmovne(Fpu reg1, Fpu reg2) { opFpuFpu(reg1, reg2, 0xDBC8, 0x00C8); }
void fcmovnu(Fpu reg1) { opFpuFpu(st0, reg1, 0xDBD8, 0x00D8); }
void fcmovnu(Fpu reg1, Fpu reg2) { opFpuFpu(reg1, reg2, 0xDBD8, 0x00D8); }
void fcmovu(Fpu reg1) { opFpuFpu(st0, reg1, 0xDAD8, 0x00D8); }
void fcmovu(Fpu reg1, Fpu reg2) { opFpuFpu(reg1, reg2, 0xDAD8, 0x00D8); }
void fcom() { db(0xD8); db(0xD1); }
void fcom(const Address& addr) { opFpuMem(addr, 0x00, 0xD8, 0xDC, 2, 0); }
void fcom(Fpu reg) { opFpu(reg, 0xD8, 0xD0); }
void fcomi(Fpu reg1) { opFpuFpu(st0, reg1, 0xDBF0, 0x00F0); }
void fcomi(Fpu reg1, Fpu reg2) { opFpuFpu(reg1, reg2, 0xDBF0, 0x00F0); }
void fcomip(Fpu reg1) { opFpuFpu(st0, reg1, 0xDFF0, 0x00F0); }
void fcomip(Fpu reg1, Fpu reg2) { opFpuFpu(reg1, reg2, 0xDFF0, 0x00F0); }
void fcomp() { db(0xD8); db(0xD9); }
void fcomp(const Address& addr) { opFpuMem(addr, 0x00, 0xD8, 0xDC, 3, 0); }
void fcomp(Fpu reg) { opFpu(reg, 0xD8, 0xD8); }
void fcompp() { db(0xDE); db(0xD9); }
void fcos() { db(0xD9); db(0xFF); }
void fdecstp() { db(0xD9); db(0xF6); }
void fdiv(const Address& addr) { opFpuMem(addr, 0x00, 0xD8, 0xDC, 6, 0); }
void fdiv(Fpu reg1) { opFpuFpu(st0, reg1, 0xD8F0, 0xDCF8); }
void fdiv(Fpu reg1, Fpu reg2) { opFpuFpu(reg1, reg2, 0xD8F0, 0xDCF8); }
void fdivp() { db(0xDE); db(0xF9); }
void fdivp(Fpu reg1) { opFpuFpu(reg1, st0, 0x0000, 0xDEF8); }
void fdivp(Fpu reg1, Fpu reg2) { opFpuFpu(reg1, reg2, 0x0000, 0xDEF8); }
void fdivr(const Address& addr) { opFpuMem(addr, 0x00, 0xD8, 0xDC, 7, 0); }
void fdivr(Fpu reg1) { opFpuFpu(st0, reg1, 0xD8F8, 0xDCF0); }
void fdivr(Fpu reg1, Fpu reg2) { opFpuFpu(reg1, reg2, 0xD8F8, 0xDCF0); }
void fdivrp() { db(0xDE); db(0xF1); }
void fdivrp(Fpu reg1) { opFpuFpu(reg1, st0, 0x0000, 0xDEF0); }
void fdivrp(Fpu reg1, Fpu reg2) { opFpuFpu(reg1, reg2, 0x0000, 0xDEF0); }
void ffree(Fpu reg) { opFpu(reg, 0xDD, 0xC0); }
void fiadd(const Address& addr) { opFpuMem(addr, 0xDE, 0xDA, 0x00, 0, 0); }
void ficom(const Address& addr) { opFpuMem(addr, 0xDE, 0xDA, 0x00, 2, 0); }
void ficomp(const Address& addr) { opFpuMem(addr, 0xDE, 0xDA, 0x00, 3, 0); }
void fidiv(const Address& addr) { opFpuMem(addr, 0xDE, 0xDA, 0x00, 6, 0); }
void fidivr(const Address& addr) { opFpuMem(addr, 0xDE, 0xDA, 0x00, 7, 0); }
void fild(const Address& addr) { opFpuMem(addr, 0xDF, 0xDB, 0xDF, 0, 5); }
void fimul(const Address& addr) { opFpuMem(addr, 0xDE, 0xDA, 0x00, 1, 0); }
void fincstp() { db(0xD9); db(0xF7); }
void finit() { db(0x9B); db(0xDB); db(0xE3); }
void fist(const Address& addr) { opFpuMem(addr, 0xDF, 0xDB, 0x00, 2, 0); }
void fistp(const Address& addr) { opFpuMem(addr, 0xDF, 0xDB, 0xDF, 3, 7); }
void fisttp(const Address& addr) { opFpuMem(addr, 0xDF, 0xDB, 0xDD, 1, 0); }
void fisub(const Address& addr) { opFpuMem(addr, 0xDE, 0xDA, 0x00, 4, 0); }
void fisubr(const Address& addr) { opFpuMem(addr, 0xDE, 0xDA, 0x00, 5, 0); }
void fld(const Address& addr) { opFpuMem(addr, 0x00, 0xD9, 0xDD, 0, 0); }
void fld(Fpu reg) { opFpu(reg, 0xD9, 0xC0); }
void fld1() { db(0xD9); db(0xE8); }
void fldcw(const Address& addr) { opMR(addr, Reg32(5), 0, 0xD9); }
void fldenv(const Address& addr) { opMR(addr, Reg32(4), 0, 0xD9); }
void fldl2e() { db(0xD9); db(0xEA); }
void fldl2t() { db(0xD9); db(0xE9); }
void fldlg2() { db(0xD9); db(0xEC); }
void fldln2() { db(0xD9); db(0xED); }
void fldpi() { db(0xD9); db(0xEB); }
void fldz() { db(0xD9); db(0xEE); }
void fmul(const Address& addr) { opFpuMem(addr, 0x00, 0xD8, 0xDC, 1, 0); }
void fmul(Fpu reg1) { opFpuFpu(st0, reg1, 0xD8C8, 0xDCC8); }
void fmul(Fpu reg1, Fpu reg2) { opFpuFpu(reg1, reg2, 0xD8C8, 0xDCC8); }
void fmulp() { db(0xDE); db(0xC9); }
void fmulp(Fpu reg1) { opFpuFpu(reg1, st0, 0x0000, 0xDEC8); }
void fmulp(Fpu reg1, Fpu reg2) { opFpuFpu(reg1, reg2, 0x0000, 0xDEC8); }
void fnclex() { db(0xDB); db(0xE2); }
void fninit() { db(0xDB); db(0xE3); }
void fnop() { db(0xD9); db(0xD0); }
void fnsave(const Address& addr) { opMR(addr, Reg32(6), 0, 0xDD); }
void fnstcw(const Address& addr) { opMR(addr, Reg32(7), 0, 0xD9); }
void fnstenv(const Address& addr) { opMR(addr, Reg32(6), 0, 0xD9); }
void fnstsw(const Address& addr) { opMR(addr, Reg32(7), 0, 0xDD); }
void fnstsw(Reg16 r) { if (r.getIdx() != Operand::AX) XBYAK_THROW(ERR_BAD_PARAMETER) db(0xDF); db(0xE0); }
void fpatan() { db(0xD9); db(0xF3); }
void fprem() { db(0xD9); db(0xF8); }
void fprem1() { db(0xD9); db(0xF5); }
void fptan() { db(0xD9); db(0xF2); }
void frndint() { db(0xD9); db(0xFC); }
void frstor(const Address& addr) { opMR(addr, Reg32(4), 0, 0xDD); }
void fsave(const Address& addr) { db(0x9B); opMR(addr, Reg32(6), 0, 0xDD); }
void fscale() { db(0xD9); db(0xFD); }
void fsin() { db(0xD9); db(0xFE); }
void fsincos() { db(0xD9); db(0xFB); }
void fsqrt() { db(0xD9); db(0xFA); }
void fst(const Address& addr) { opFpuMem(addr, 0x00, 0xD9, 0xDD, 2, 0); }
void fst(Fpu reg) { opFpu(reg, 0xDD, 0xD0); }
void fstcw(const Address& addr) { db(0x9B); opMR(addr, Reg32(7), 0, 0xD9); }
void fstenv(const Address& addr) { db(0x9B); opMR(addr, Reg32(6), 0, 0xD9); }
void fstp(const Address& addr) { opFpuMem(addr, 0x00, 0xD9, 0xDD, 3, 0); }
void fstp(Fpu reg) { opFpu(reg, 0xDD, 0xD8); }
void fstsw(const Address& addr) { db(0x9B); opMR(addr, Reg32(7), 0, 0xDD); }
void fstsw(Reg16 r) { if (r.getIdx() != Operand::AX) XBYAK_THROW(ERR_BAD_PARAMETER) db(0x9B); db(0xDF); db(0xE0); }
void fsub(const Address& addr) { opFpuMem(addr, 0x00, 0xD8, 0xDC, 4, 0); }
void fsub(Fpu reg1) { opFpuFpu(st0, reg1, 0xD8E0, 0xDCE8); }
void fsub(Fpu reg1, Fpu reg2) { opFpuFpu(reg1, reg2, 0xD8E0, 0xDCE8); }
void fsubp() { db(0xDE); db(0xE9); }
void fsubp(Fpu reg1) { opFpuFpu(reg1, st0, 0x0000, 0xDEE8); }
void fsubp(Fpu reg1, Fpu reg2) { opFpuFpu(reg1, reg2, 0x0000, 0xDEE8); }
void fsubr(const Address& addr) { opFpuMem(addr, 0x00, 0xD8, 0xDC, 5, 0); }
void fsubr(Fpu reg1) { opFpuFpu(st0, reg1, 0xD8E8, 0xDCE0); }
void fsubr(Fpu reg1, Fpu reg2) { opFpuFpu(reg1, reg2, 0xD8E8, 0xDCE0); }
void fsubrp() { db(0xDE); db(0xE1); }
void fsubrp(Fpu reg1) { opFpuFpu(reg1, st0, 0x0000, 0xDEE0); }
void fsubrp(Fpu reg1, Fpu reg2) { opFpuFpu(reg1, reg2, 0x0000, 0xDEE0); }
void ftst() { db(0xD9); db(0xE4); }
void fucom() { db(0xDD); db(0xE1); }
void fucom(Fpu reg) { opFpu(reg, 0xDD, 0xE0); }
void fucomi(Fpu reg1) { opFpuFpu(st0, reg1, 0xDBE8, 0x00E8); }
void fucomi(Fpu reg1, Fpu reg2) { opFpuFpu(reg1, reg2, 0xDBE8, 0x00E8); }
void fucomip(Fpu reg1) { opFpuFpu(st0, reg1, 0xDFE8, 0x00E8); }
void fucomip(Fpu reg1, Fpu reg2) { opFpuFpu(reg1, reg2, 0xDFE8, 0x00E8); }
void fucomp() { db(0xDD); db(0xE9); }
void fucomp(Fpu reg) { opFpu(reg, 0xDD, 0xE8); }
void fucompp() { db(0xDA); db(0xE9); }
void fwait() { db(0x9B); }
void fxam() { db(0xD9); db(0xE5); }
void fxch() { db(0xD9); db(0xC9); }
void fxch(Fpu reg) { opFpu(reg, 0xD9, 0xC8); }
void fxrstor(const Address& addr) { opMR(addr, Reg32(1), T_0F, 0xAE); }
void fxtract() { db(0xD9); db(0xF4); }
void fyl2x() { db(0xD9); db(0xF1); }
void fyl2xp1() { db(0xD9); db(0xF9); }
void gf2p8affineinvqb(Xmm xmm, const Operand& op, int imm) { opSSE(xmm, op, T_66 | T_0F3A, 0xCF, isXMM_XMMorMEM, static_cast<uint8_t>(imm)); }
void gf2p8affineqb(Xmm xmm, const Operand& op, int imm) { opSSE(xmm, op, T_66 | T_0F3A, 0xCE, isXMM_XMMorMEM, static_cast<uint8_t>(imm)); }
void gf2p8mulb(Xmm xmm, const Operand& op) { opSSE(xmm, op, T_66 | T_0F38, 0xCF, isXMM_XMMorMEM); }
void haddpd(Xmm xmm, const Operand& op) { opSSE(xmm, op, T_66|T_0F|T_YMM, 0x7C, isXMM_XMMorMEM); }
void haddps(Xmm xmm, const Operand& op) { opSSE(xmm, op, T_F2|T_0F|T_YMM, 0x7C, isXMM_XMMorMEM); }
void hlt() { db(0xF4); }
void hsubpd(Xmm xmm, const Operand& op) { opSSE(xmm, op, T_66|T_0F|T_YMM, 0x7D, isXMM_XMMorMEM); }
void hsubps(Xmm xmm, const Operand& op) { opSSE(xmm, op, T_F2|T_0F|T_YMM, 0x7D, isXMM_XMMorMEM); }
void idiv(const Operand& op) { opRext(op, 0, 7, T_APX|T_NF|T_CODE1_IF1, 0xF6); }
void imul(const Operand& op) { opRext(op, 0, 5, T_APX|T_NF|T_CODE1_IF1, 0xF6); }
void imul(Reg d, Reg reg, const Operand& op) { opROO(d, op, reg, T_APX|T_ND1|T_NF, 0xAF); }
void imul(Reg reg, const Operand& op) { if (opROO(Reg(), op, reg, T_APX|T_NF, 0xAF)) return; opRO(reg, op, T_0F, 0xAF, reg.getKind() == op.getKind()); }
void in_(Reg a, Reg d) { opInOut(a, d, 0xEC); }
void in_(Reg a, uint8_t v) { opInOut(a, 0xE4, v); }
void inc(const Operand& op) { opIncDec(Reg(), op, 0); }
void inc(Reg d, const Operand& op) { opIncDec(d, op, 0); }
void insertps(Xmm xmm, const Operand& op, uint8_t imm) { opSSE(xmm, op, T_66 | T_0F3A, 0x21, isXMM_XMMorMEM, imm); }
void int3() { db(0xCC); }
void int_(uint8_t x) { db(0xCD); db(x); }
void ja(const Label& label, LabelType type = T_AUTO) { opJmp(label, type, 0x77, 0x87, 0x0F); }//-V524
void ja(const char *label, LabelType type = T_AUTO) { ja(std::string(label), type); }//-V524
void ja(const void *addr) { opJmpAbs(addr, T_NEAR, 0x77, 0x87, 0x0F); }//-V524
void ja(std::string label, LabelType type = T_AUTO) { opJmp(label, type, 0x77, 0x87, 0x0F); }//-V524
void jae(const Label& label, LabelType type = T_AUTO) { opJmp(label, type, 0x73, 0x83, 0x0F); }//-V524
void jae(const char *label, LabelType type = T_AUTO) { jae(std::string(label), type); }//-V524
void jae(const void *addr) { opJmpAbs(addr, T_NEAR, 0x73, 0x83, 0x0F); }//-V524
void jae(std::string label, LabelType type = T_AUTO) { opJmp(label, type, 0x73, 0x83, 0x0F); }//-V524
void jb(const Label& label, LabelType type = T_AUTO) { opJmp(label, type, 0x72, 0x82, 0x0F); }//-V524
void jb(const char *label, LabelType type = T_AUTO) { jb(std::string(label), type); }//-V524
void jb(const void *addr) { opJmpAbs(addr, T_NEAR, 0x72, 0x82, 0x0F); }//-V524
void jb(std::string label, LabelType type = T_AUTO) { opJmp(label, type, 0x72, 0x82, 0x0F); }//-V524
void jbe(const Label& label, LabelType type = T_AUTO) { opJmp(label, type, 0x76, 0x86, 0x0F); }//-V524
void jbe(const char *label, LabelType type = T_AUTO) { jbe(std::string(label), type); }//-V524
void jbe(const void *addr) { opJmpAbs(addr, T_NEAR, 0x76, 0x86, 0x0F); }//-V524
void jbe(std::string label, LabelType type = T_AUTO) { opJmp(label, type, 0x76, 0x86, 0x0F); }//-V524
void jc(const Label& label, LabelType type = T_AUTO) { opJmp(label, type, 0x72, 0x82, 0x0F); }//-V524
void jc(const char *label, LabelType type = T_AUTO) { jc(std::string(label), type); }//-V524
void jc(const void *addr) { opJmpAbs(addr, T_NEAR, 0x72, 0x82, 0x0F); }//-V524
void jc(std::string label, LabelType type = T_AUTO) { opJmp(label, type, 0x72, 0x82, 0x0F); }//-V524
void je(const Label& label, LabelType type = T_AUTO) { opJmp(label, type, 0x74, 0x84, 0x0F); }//-V524
void je(const char *label, LabelType type = T_AUTO) { je(std::string(label), type); }//-V524
void je(const void *addr) { opJmpAbs(addr, T_NEAR, 0x74, 0x84, 0x0F); }//-V524
void je(std::string label, LabelType type = T_AUTO) { opJmp(label, type, 0x74, 0x84, 0x0F); }//-V524
void jg(const Label& label, LabelType type = T_AUTO) { opJmp(label, type, 0x7F, 0x8F, 0x0F); }//-V524
void jg(const char *label, LabelType type = T_AUTO) { jg(std::string(label), type); }//-V524
void jg(const void *addr) { opJmpAbs(addr, T_NEAR, 0x7F, 0x8F, 0x0F); }//-V524
void jg(std::string label, LabelType type = T_AUTO) { opJmp(label, type, 0x7F, 0x8F, 0x0F); }//-V524
void jge(const Label& label, LabelType type = T_AUTO) { opJmp(label, type, 0x7D, 0x8D, 0x0F); }//-V524
void jge(const char *label, LabelType type = T_AUTO) { jge(std::string(label), type); }//-V524
void jge(const void *addr) { opJmpAbs(addr, T_NEAR, 0x7D, 0x8D, 0x0F); }//-V524
void jge(std::string label, LabelType type = T_AUTO) { opJmp(label, type, 0x7D, 0x8D, 0x0F); }//-V524
void jl(const Label& label, LabelType type = T_AUTO) { opJmp(label, type, 0x7C, 0x8C, 0x0F); }//-V524
void jl(const char *label, LabelType type = T_AUTO) { jl(std::string(label), type); }//-V524
void jl(const void *addr) { opJmpAbs(addr, T_NEAR, 0x7C, 0x8C, 0x0F); }//-V524
void jl(std::string label, LabelType type = T_AUTO) { opJmp(label, type, 0x7C, 0x8C, 0x0F); }//-V524
void jle(const Label& label, LabelType type = T_AUTO) { opJmp(label, type, 0x7E, 0x8E, 0x0F); }//-V524
void jle(const char *label, LabelType type = T_AUTO) { jle(std::string(label), type); }//-V524
void jle(const void *addr) { opJmpAbs(addr, T_NEAR, 0x7E, 0x8E, 0x0F); }//-V524
void jle(std::string label, LabelType type = T_AUTO) { opJmp(label, type, 0x7E, 0x8E, 0x0F); }//-V524
void jna(const Label& label, LabelType type = T_AUTO) { opJmp(label, type, 0x76, 0x86, 0x0F); }//-V524
void jna(const char *label, LabelType type = T_AUTO) { jna(std::string(label), type); }//-V524
void jna(const void *addr) { opJmpAbs(addr, T_NEAR, 0x76, 0x86, 0x0F); }//-V524
void jna(std::string label, LabelType type = T_AUTO) { opJmp(label, type, 0x76, 0x86, 0x0F); }//-V524
void jnae(const Label& label, LabelType type = T_AUTO) { opJmp(label, type, 0x72, 0x82, 0x0F); }//-V524
void jnae(const char *label, LabelType type = T_AUTO) { jnae(std::string(label), type); }//-V524
void jnae(const void *addr) { opJmpAbs(addr, T_NEAR, 0x72, 0x82, 0x0F); }//-V524
void jnae(std::string label, LabelType type = T_AUTO) { opJmp(label, type, 0x72, 0x82, 0x0F); }//-V524
void jnb(const Label& label, LabelType type = T_AUTO) { opJmp(label, type, 0x73, 0x83, 0x0F); }//-V524
void jnb(const char *label, LabelType type = T_AUTO) { jnb(std::string(label), type); }//-V524
void jnb(const void *addr) { opJmpAbs(addr, T_NEAR, 0x73, 0x83, 0x0F); }//-V524
void jnb(std::string label, LabelType type = T_AUTO) { opJmp(label, type, 0x73, 0x83, 0x0F); }//-V524
void jnbe(const Label& label, LabelType type = T_AUTO) { opJmp(label, type, 0x77, 0x87, 0x0F); }//-V524
void jnbe(const char *label, LabelType type = T_AUTO) { jnbe(std::string(label), type); }//-V524
void jnbe(const void *addr) { opJmpAbs(addr, T_NEAR, 0x77, 0x87, 0x0F); }//-V524
void jnbe(std::string label, LabelType type = T_AUTO) { opJmp(label, type, 0x77, 0x87, 0x0F); }//-V524
void jnc(const Label& label, LabelType type = T_AUTO) { opJmp(label, type, 0x73, 0x83, 0x0F); }//-V524
void jnc(const char *label, LabelType type = T_AUTO) { jnc(std::string(label), type); }//-V524
void jnc(const void *addr) { opJmpAbs(addr, T_NEAR, 0x73, 0x83, 0x0F); }//-V524
void jnc(std::string label, LabelType type = T_AUTO) { opJmp(label, type, 0x73, 0x83, 0x0F); }//-V524
void jne(const Label& label, LabelType type = T_AUTO) { opJmp(label, type, 0x75, 0x85, 0x0F); }//-V524
void jne(const char *label, LabelType type = T_AUTO) { jne(std::string(label), type); }//-V524
void jne(const void *addr) { opJmpAbs(addr, T_NEAR, 0x75, 0x85, 0x0F); }//-V524
void jne(std::string label, LabelType type = T_AUTO) { opJmp(label, type, 0x75, 0x85, 0x0F); }//-V524
void jng(const Label& label, LabelType type = T_AUTO) { opJmp(label, type, 0x7E, 0x8E, 0x0F); }//-V524
void jng(const char *label, LabelType type = T_AUTO) { jng(std::string(label), type); }//-V524
void jng(const void *addr) { opJmpAbs(addr, T_NEAR, 0x7E, 0x8E, 0x0F); }//-V524
void jng(std::string label, LabelType type = T_AUTO) { opJmp(label, type, 0x7E, 0x8E, 0x0F); }//-V524
void jnge(const Label& label, LabelType type = T_AUTO) { opJmp(label, type, 0x7C, 0x8C, 0x0F); }//-V524
void jnge(const char *label, LabelType type = T_AUTO) { jnge(std::string(label), type); }//-V524
void jnge(const void *addr) { opJmpAbs(addr, T_NEAR, 0x7C, 0x8C, 0x0F); }//-V524
void jnge(std::string label, LabelType type = T_AUTO) { opJmp(label, type, 0x7C, 0x8C, 0x0F); }//-V524
void jnl(const Label& label, LabelType type = T_AUTO) { opJmp(label, type, 0x7D, 0x8D, 0x0F); }//-V524
void jnl(const char *label, LabelType type = T_AUTO) { jnl(std::string(label), type); }//-V524
void jnl(const void *addr) { opJmpAbs(addr, T_NEAR, 0x7D, 0x8D, 0x0F); }//-V524
void jnl(std::string label, LabelType type = T_AUTO) { opJmp(label, type, 0x7D, 0x8D, 0x0F); }//-V524
void jnle(const Label& label, LabelType type = T_AUTO) { opJmp(label, type, 0x7F, 0x8F, 0x0F); }//-V524
void jnle(const char *label, LabelType type = T_AUTO) { jnle(std::string(label), type); }//-V524
void jnle(const void *addr) { opJmpAbs(addr, T_NEAR, 0x7F, 0x8F, 0x0F); }//-V524
void jnle(std::string label, LabelType type = T_AUTO) { opJmp(label, type, 0x7F, 0x8F, 0x0F); }//-V524
void jno(const Label& label, LabelType type = T_AUTO) { opJmp(label, type, 0x71, 0x81, 0x0F); }//-V524
void jno(const char *label, LabelType type = T_AUTO) { jno(std::string(label), type); }//-V524
void jno(const void *addr) { opJmpAbs(addr, T_NEAR, 0x71, 0x81, 0x0F); }//-V524
void jno(std::string label, LabelType type = T_AUTO) { opJmp(label, type, 0x71, 0x81, 0x0F); }//-V524
void jnp(const Label& label, LabelType type = T_AUTO) { opJmp(label, type, 0x7B, 0x8B, 0x0F); }//-V524
void jnp(const char *label, LabelType type = T_AUTO) { jnp(std::string(label), type); }//-V524
void jnp(const void *addr) { opJmpAbs(addr, T_NEAR, 0x7B, 0x8B, 0x0F); }//-V524
void jnp(std::string label, LabelType type = T_AUTO) { opJmp(label, type, 0x7B, 0x8B, 0x0F); }//-V524
void jns(const Label& label, LabelType type = T_AUTO) { opJmp(label, type, 0x79, 0x89, 0x0F); }//-V524
void jns(const char *label, LabelType type = T_AUTO) { jns(std::string(label), type); }//-V524
void jns(const void *addr) { opJmpAbs(addr, T_NEAR, 0x79, 0x89, 0x0F); }//-V524
void jns(std::string label, LabelType type = T_AUTO) { opJmp(label, type, 0x79, 0x89, 0x0F); }//-V524
void jnz(const Label& label, LabelType type = T_AUTO) { opJmp(label, type, 0x75, 0x85, 0x0F); }//-V524
void jnz(const char *label, LabelType type = T_AUTO) { jnz(std::string(label), type); }//-V524
void jnz(const void *addr) { opJmpAbs(addr, T_NEAR, 0x75, 0x85, 0x0F); }//-V524
void jnz(std::string label, LabelType type = T_AUTO) { opJmp(label, type, 0x75, 0x85, 0x0F); }//-V524
void jo(const Label& label, LabelType type = T_AUTO) { opJmp(label, type, 0x70, 0x80, 0x0F); }//-V524
void jo(const char *label, LabelType type = T_AUTO) { jo(std::string(label), type); }//-V524
void jo(const void *addr) { opJmpAbs(addr, T_NEAR, 0x70, 0x80, 0x0F); }//-V524
void jo(std::string label, LabelType type = T_AUTO) { opJmp(label, type, 0x70, 0x80, 0x0F); }//-V524
void jp(const Label& label, LabelType type = T_AUTO) { opJmp(label, type, 0x7A, 0x8A, 0x0F); }//-V524
void jp(const char *label, LabelType type = T_AUTO) { jp(std::string(label), type); }//-V524
void jp(const void *addr) { opJmpAbs(addr, T_NEAR, 0x7A, 0x8A, 0x0F); }//-V524
void jp(std::string label, LabelType type = T_AUTO) { opJmp(label, type, 0x7A, 0x8A, 0x0F); }//-V524
void jpe(const Label& label, LabelType type = T_AUTO) { opJmp(label, type, 0x7A, 0x8A, 0x0F); }//-V524
void jpe(const char *label, LabelType type = T_AUTO) { jpe(std::string(label), type); }//-V524
void jpe(const void *addr) { opJmpAbs(addr, T_NEAR, 0x7A, 0x8A, 0x0F); }//-V524
void jpe(std::string label, LabelType type = T_AUTO) { opJmp(label, type, 0x7A, 0x8A, 0x0F); }//-V524
void jpo(const Label& label, LabelType type = T_AUTO) { opJmp(label, type, 0x7B, 0x8B, 0x0F); }//-V524
void jpo(const char *label, LabelType type = T_AUTO) { jpo(std::string(label), type); }//-V524
void jpo(const void *addr) { opJmpAbs(addr, T_NEAR, 0x7B, 0x8B, 0x0F); }//-V524
void jpo(std::string label, LabelType type = T_AUTO) { opJmp(label, type, 0x7B, 0x8B, 0x0F); }//-V524
void js(const Label& label, LabelType type = T_AUTO) { opJmp(label, type, 0x78, 0x88, 0x0F); }//-V524
void js(const char *label, LabelType type = T_AUTO) { js(std::string(label), type); }//-V524
void js(const void *addr) { opJmpAbs(addr, T_NEAR, 0x78, 0x88, 0x0F); }//-V524
void js(std::string label, LabelType type = T_AUTO) { opJmp(label, type, 0x78, 0x88, 0x0F); }//-V524
void jz(const Label& label, LabelType type = T_AUTO) { opJmp(label, type, 0x74, 0x84, 0x0F); }//-V524
void jz(const char *label, LabelType type = T_AUTO) { jz(std::string(label), type); }//-V524
void jz(const void *addr) { opJmpAbs(addr, T_NEAR, 0x74, 0x84, 0x0F); }//-V524
void jz(std::string label, LabelType type = T_AUTO) { opJmp(label, type, 0x74, 0x84, 0x0F); }//-V524
void lahf() { db(0x9F); }
void lddqu(Xmm xmm, const Address& addr) { opSSE(xmm, addr, T_F2 | T_0F, 0xF0); }
void ldmxcsr(const Address& addr) { opMR(addr, Reg32(2), T_0F, 0xAE); }
void lea(Reg reg, const Address& addr) { if (!reg.isBit(16 | i32e)) XBYAK_THROW(ERR_BAD_SIZE_OF_REGISTER) opMR(addr, reg, 0, 0x8D); }
void leave() { db(0xC9); }
void lfence() { db(0x0F); db(0xAE); db(0xE8); }
void lfs(Reg reg, const Address& addr) { opLoadSeg(addr, reg, T_0F, 0xB4); }
void lgs(Reg reg, const Address& addr) { opLoadSeg(addr, reg, T_0F, 0xB5); }
void lock() { db(0xF0); }
void lodsb() { db(0xAC); }
void lodsd() { db(0xAD); }
void lodsw() { db(0x66); db(0xAD); }
void loop(const Label& label) { opJmp(label, T_SHORT, 0xE2, 0, 0); }
void loop(const char *label) { loop(std::string(label)); }
void loop(std::string label) { opJmp(label, T_SHORT, 0xE2, 0, 0); }
void loope(const Label& label) { opJmp(label, T_SHORT, 0xE1, 0, 0); }
void loope(const char *label) { loope(std::string(label)); }
void loope(std::string label) { opJmp(label, T_SHORT, 0xE1, 0, 0); }
void loopne(const Label& label) { opJmp(label, T_SHORT, 0xE0, 0, 0); }
void loopne(const char *label) { loopne(std::string(label)); }
void loopne(std::string label) { opJmp(label, T_SHORT, 0xE0, 0, 0); }
void lss(Reg reg, const Address& addr) { opLoadSeg(addr, reg, T_0F, 0xB2); }
void lzcnt(Reg reg, const Operand& op) { if (opROO(Reg(), op, reg, T_APX|T_NF, 0xF5)) return; opCnt(reg, op, 0xBD); }
void maskmovdqu(Xmm reg1, Xmm reg2) { opSSE(reg1, reg2, T_66|T_0F, 0xF7); }
void maskmovq(Mmx reg1, Mmx reg2) { opSSE(reg1, reg2, T_0F, 0xF7); }
void maxpd(Xmm xmm, const Operand& op) { opSSE(xmm, op, T_0F | T_66, 0x5F, isXMM_XMMorMEM); }
void maxps(Xmm xmm, const Operand& op) { opSSE(xmm, op, T_0F, 0x5F, isXMM_XMMorMEM); }
void maxsd(Xmm xmm, const Operand& op) { opSSE(xmm, op, T_0F | T_F2, 0x5F, isXMM_XMMorMEM); }
void maxss(Xmm xmm, const Operand& op) { opSSE(xmm, op, T_0F | T_F3, 0x5F, isXMM_XMMorMEM); }
void mfence() { db(0x0F); db(0xAE); db(0xF0); }
void minpd(Xmm xmm, const Operand& op) { opSSE(xmm, op, T_0F | T_66, 0x5D, isXMM_XMMorMEM); }
void minps(Xmm xmm, const Operand& op) { opSSE(xmm, op, T_0F, 0x5D, isXMM_XMMorMEM); }
void minsd(Xmm xmm, const Operand& op) { opSSE(xmm, op, T_0F | T_F2, 0x5D, isXMM_XMMorMEM); }
void minss(Xmm xmm, const Operand& op) { opSSE(xmm, op, T_0F | T_F3, 0x5D, isXMM_XMMorMEM); }
void monitor() { db(0x0F); db(0x01); db(0xC8); }
void monitorx() { db(0x0F); db(0x01); db(0xFA); }
void movapd(const Address& addr, Xmm xmm) { opSSE(xmm, addr, T_0F|T_66, 0x29); }
void movapd(Xmm xmm, const Operand& op) { opMMX(xmm, op, 0x28, T_0F, T_66); }
void movaps(const Address& addr, Xmm xmm) { opSSE(xmm, addr, T_0F|T_NONE, 0x29); }
void movaps(Xmm xmm, const Operand& op) { opMMX(xmm, op, 0x28, T_0F, T_NONE); }
void movbe(const Address& addr, Reg reg) { opMR(addr, reg, T_0F38, 0xF1, T_APX, 0x61); }
void movbe(Reg reg, const Address& addr) { opMR(addr, reg, T_0F38, 0xF0, T_APX, 0x60); }
void movd(Mmx mmx, const Operand& op) { if (!(op.isMEM() || op.isREG(32))) XBYAK_THROW(ERR_BAD_COMBINATION) if (mmx.isXMM()) db(0x66); opSSE(mmx, op, T_0F | T_ALLOW_DIFF_SIZE, 0x6E); }
void movd(const Operand& op, Mmx mmx) { if (!(op.isMEM() || op.isREG(32))) XBYAK_THROW(ERR_BAD_COMBINATION) if (mmx.isXMM()) db(0x66); opSSE(mmx, op, T_0F | T_ALLOW_DIFF_SIZE, 0x7E); }
void movddup(Xmm xmm, const Operand& op) { opSSE(xmm, op, T_DUP|T_F2|T_0F|T_EW1|T_YMM|T_EVEX, 0x12, isXMM_XMMorMEM, NONE); }
void movdir64b(Reg reg, const Address& addr) { opMR(addr, reg.cvt32(), T_66|T_0F38, 0xF8, T_APX|T_66); }
void movdiri(const Address& addr, Reg32e reg) { opMR(addr, reg, T_0F38, 0xF9, T_APX); }
void movdq2q(Mmx mmx, Xmm xmm) { opSSE(mmx, xmm, T_F2 | T_0F, 0xD6); }
void movdqa(const Address& addr, Xmm xmm) { opSSE(xmm, addr, T_0F|T_66, 0x7F); }
void movdqa(Xmm xmm, const Operand& op) { opMMX(xmm, op, 0x6F, T_0F, T_66); }
void movdqu(const Address& addr, Xmm xmm) { opSSE(xmm, addr, T_0F|T_F3, 0x7F); }
void movdqu(Xmm xmm, const Operand& op) { opMMX(xmm, op, 0x6F, T_0F, T_F3); }
void movhlps(Xmm reg1, Xmm reg2) { opSSE(reg1, reg2, T_0F, 0x12); }
void movhpd(const Operand& op1, const Operand& op2) { opMovXMM(op1, op2, T_66|T_0F, 0x16); }
void movhps(const Operand& op1, const Operand& op2) { opMovXMM(op1, op2, T_0F, 0x16); }
void movlhps(Xmm reg1, Xmm reg2) { opSSE(reg1, reg2, T_0F, 0x16); }
void movlpd(const Operand& op1, const Operand& op2) { opMovXMM(op1, op2, T_66|T_0F, 0x12); }
void movlps(const Operand& op1, const Operand& op2) { opMovXMM(op1, op2, T_0F, 0x12); }
void movmskpd(Reg32e reg, Xmm xmm) { db(0x66); movmskps(reg, xmm); }
void movmskps(Reg32e reg, Xmm xmm) { opSSE(reg, xmm, T_0F, 0x50); }
void movntdq(const Address& addr, Xmm reg) { if (reg.getIdx() >= 16) XBYAK_THROW(ERR_BAD_PARAMETER) opSSE(Reg16(reg.getIdx()), addr, T_0F, 0xE7); }
void movntdqa(Xmm xmm, const Address& addr) { opSSE(xmm, addr, T_66 | T_0F38, 0x2A); }
void movnti(const Address& addr, Reg32e reg) { opMR(addr, reg, T_0F, 0xC3); }
void movntpd(const Address& addr, Xmm reg) { if (reg.getIdx() >= 16) XBYAK_THROW(ERR_BAD_PARAMETER) opSSE(Reg16(reg.getIdx()), addr, T_0F, 0x2B); }
void movntps(const Address& addr, Xmm xmm) { opSSE(Xmm(xmm.getIdx()), addr, T_0F, 0x2B); }
void movntq(const Address& addr, Mmx mmx) { if (!mmx.isMMX()) XBYAK_THROW(ERR_BAD_COMBINATION) opSSE(mmx, addr, T_0F, 0xE7); }
void movq(const Address& addr, Mmx mmx) { if (mmx.isXMM()) db(0x66); opSSE(mmx, addr, T_0F | T_ALLOW_DIFF_SIZE, mmx.isXMM() ? 0xD6 : 0x7F); }
void movq(Mmx mmx, const Operand& op) { if (!op.isMEM() && mmx.getKind() != op.getKind()) XBYAK_THROW(ERR_BAD_COMBINATION) if (mmx.isXMM()) db(0xF3); opSSE(mmx, op, T_0F | T_ALLOW_DIFF_SIZE, mmx.isXMM() ? 0x7E : 0x6F); }
void movq2dq(Xmm xmm, Mmx mmx) { opSSE(xmm, mmx, T_F3 | T_0F, 0xD6); }
void movsb() { db(0xA4); }
void movsd() { db(0xA5); }
void movsd(const Address& addr, Xmm xmm) { opSSE(xmm, addr, T_0F|T_F2, 0x11); }
void movsd(Xmm xmm, const Operand& op) { opMMX(xmm, op, 0x10, T_0F, T_F2); }
void movshdup(Xmm xmm, const Operand& op) { opSSE(xmm, op, T_F3|T_0F|T_W0|T_YMM|T_EVEX, 0x16, isXMM_XMMorMEM, NONE); }
void movsldup(Xmm xmm, const Operand& op) { opSSE(xmm, op, T_F3|T_0F|T_W0|T_YMM|T_EVEX, 0x12, isXMM_XMMorMEM, NONE); }
void movss(const Address& addr, Xmm xmm) { opSSE(xmm, addr, T_0F|T_F3, 0x11); }
void movss(Xmm xmm, const Operand& op) { opMMX(xmm, op, 0x10, T_0F, T_F3); }
void movsw() { db(0x66); db(0xA5); }
void movsx(Reg reg, const Operand& op) { opMovxx(reg, op, 0xBE); }
void movupd(const Address& addr, Xmm xmm) { opSSE(xmm, addr, T_0F|T_66, 0x11); }
void movupd(Xmm xmm, const Operand& op) { opMMX(xmm, op, 0x10, T_0F, T_66); }
void movups(const Address& addr, Xmm xmm) { opSSE(xmm, addr, T_0F|T_NONE, 0x11); }
void movups(Xmm xmm, const Operand& op) { opMMX(xmm, op, 0x10, T_0F, T_NONE); }
void movzx(Reg reg, const Operand& op) { opMovxx(reg, op, 0xB6); }
void mpsadbw(Xmm xmm, const Operand& op, int imm) { opSSE(xmm, op, T_66 | T_0F3A, 0x42, isXMM_XMMorMEM, static_cast<uint8_t>(imm)); }
void mul(const Operand& op) { opRext(op, 0, 4, T_APX|T_NF|T_CODE1_IF1, 0xF6); }
void mulpd(Xmm xmm, const Operand& op) { opSSE(xmm, op, T_0F | T_66, 0x59, isXMM_XMMorMEM); }
void mulps(Xmm xmm, const Operand& op) { opSSE(xmm, op, T_0F, 0x59, isXMM_XMMorMEM); }
void mulsd(Xmm xmm, const Operand& op) { opSSE(xmm, op, T_0F | T_F2, 0x59, isXMM_XMMorMEM); }
void mulss(Xmm xmm, const Operand& op) { opSSE(xmm, op, T_0F | T_F3, 0x59, isXMM_XMMorMEM); }
void mulx(Reg32e r1, Reg32e r2, const Operand& op) { opRRO(r1, r2, op, T_APX|T_F2|T_0F38, 0xf6); }
void mwait() { db(0x0F); db(0x01); db(0xC9); }
void mwaitx() { db(0x0F); db(0x01); db(0xFB); }
void neg(const Operand& op) { opRext(op, 0, 3, T_APX|T_NF|T_CODE1_IF1, 0xF6); }
void neg(Reg d, const Operand& op) { opROO(d, op, Reg(3, Operand::REG, d.getBit()), T_APX|T_NF|T_CODE1_IF1|T_ND1, 0xF6); }
void not_(const Operand& op) { opRext(op, 0, 2, T_APX|T_CODE1_IF1, 0xF6); }
void not_(Reg d, const Operand& op) { opROO(d, op, Reg(2, Operand::REG, d.getBit()), T_APX|T_CODE1_IF1|T_ND1, 0xF6); }
void or_(const Operand& op, uint32_t imm) { opOI(op, imm, 0x08, 1); }
void or_(const Operand& op1, const Operand& op2) { opRO_MR(op1, op2, 0x08); }
void or_(Reg d, const Operand& op, uint32_t imm) { opROI(d, op, imm, T_NF|T_CODE1_IF1, 1); }
void or_(Reg d, const Operand& op1, const Operand& op2) { opROO(d, op1, op2, T_NF|T_CODE1_IF1, 0x08); }
void orpd(Xmm xmm, const Operand& op) { opSSE(xmm, op, T_0F | T_66, 0x56, isXMM_XMMorMEM); }
void orps(Xmm xmm, const Operand& op) { opSSE(xmm, op, T_0F, 0x56, isXMM_XMMorMEM); }
void out_(Reg d, Reg a) { opInOut(a, d, 0xEE); }
void out_(uint8_t v, Reg a) { opInOut(a, 0xE6, v); }
void outsb() { db(0x6E); }
void outsd() { db(0x6F); }
void outsw() { db(0x66); db(0x6F); }
void pabsb(Mmx mmx, const Operand& op) { opMMX(mmx, op, 0x1C, T_0F38, T_66); }
void pabsd(Mmx mmx, const Operand& op) { opMMX(mmx, op, 0x1E, T_0F38, T_66); }
void pabsw(Mmx mmx, const Operand& op) { opMMX(mmx, op, 0x1D, T_0F38, T_66); }
void packssdw(Mmx mmx, const Operand& op) { opMMX(mmx, op, 0x6B); }
void packsswb(Mmx mmx, const Operand& op) { opMMX(mmx, op, 0x63); }
void packusdw(Xmm xmm, const Operand& op) { opSSE(xmm, op, T_66 | T_0F38, 0x2B, isXMM_XMMorMEM); }
void packuswb(Mmx mmx, const Operand& op) { opMMX(mmx, op, 0x67); }
void paddb(Mmx mmx, const Operand& op) { opMMX(mmx, op, 0xFC); }
void paddd(Mmx mmx, const Operand& op) { opMMX(mmx, op, 0xFE); }
void paddq(Mmx mmx, const Operand& op) { opMMX(mmx, op, 0xD4); }
void paddsb(Mmx mmx, const Operand& op) { opMMX(mmx, op, 0xEC); }
void paddsw(Mmx mmx, const Operand& op) { opMMX(mmx, op, 0xED); }
void paddusb(Mmx mmx, const Operand& op) { opMMX(mmx, op, 0xDC); }
void paddusw(Mmx mmx, const Operand& op) { opMMX(mmx, op, 0xDD); }
void paddw(Mmx mmx, const Operand& op) { opMMX(mmx, op, 0xFD); }
void palignr(Mmx mmx, const Operand& op, int imm) { opMMX(mmx, op, 0x0F, T_0F3A, T_66, static_cast<uint8_t>(imm)); }
void pand(Mmx mmx, const Operand& op) { opMMX(mmx, op, 0xDB); }
void pandn(Mmx mmx, const Operand& op) { opMMX(mmx, op, 0xDF); }
void pause() { db(0xF3); db(0x90); }
void pavgb(Mmx mmx, const Operand& op) { opMMX(mmx, op, 0xE0); }
void pavgw(Mmx mmx, const Operand& op) { opMMX(mmx, op, 0xE3); }
void pblendvb(Xmm xmm, const Operand& op) { opSSE(xmm, op, T_66|T_0F38, 0x10, isXMM_XMMorMEM, NONE); }
void pblendw(Xmm xmm, const Operand& op, int imm) { opSSE(xmm, op, T_66 | T_0F3A, 0x0E, isXMM_XMMorMEM, static_cast<uint8_t>(imm)); }
void pclmulhqhqdq(Xmm xmm, const Operand& op) { pclmulqdq(xmm, op, 0x11); }
void pclmulhqlqdq(Xmm xmm, const Operand& op) { pclmulqdq(xmm, op, 0x01); }
void pclmullqhqdq(Xmm xmm, const Operand& op) { pclmulqdq(xmm, op, 0x10); }
void pclmullqlqdq(Xmm xmm, const Operand& op) { pclmulqdq(xmm, op, 0x00); }
void pclmulqdq(Xmm xmm, const Operand& op, int imm) { opSSE(xmm, op, T_66 | T_0F3A, 0x44, isXMM_XMMorMEM, static_cast<uint8_t>(imm)); }
void pcmpeqb(Mmx mmx, const Operand& op) { opMMX(mmx, op, 0x74); }
void pcmpeqd(Mmx mmx, const Operand& op) { opMMX(mmx, op, 0x76); }
void pcmpeqq(Xmm xmm, const Operand& op) { opSSE(xmm, op, T_66 | T_0F38, 0x29, isXMM_XMMorMEM); }
void pcmpeqw(Mmx mmx, const Operand& op) { opMMX(mmx, op, 0x75); }
void pcmpestri(Xmm xmm, const Operand& op, uint8_t imm) { opSSE(xmm, op, T_66|T_0F3A, 0x61, isXMM_XMMorMEM, imm); }
void pcmpestrm(Xmm xmm, const Operand& op, uint8_t imm) { opSSE(xmm, op, T_66|T_0F3A, 0x60, isXMM_XMMorMEM, imm); }
void pcmpgtb(Mmx mmx, const Operand& op) { opMMX(mmx, op, 0x64); }
void pcmpgtd(Mmx mmx, const Operand& op) { opMMX(mmx, op, 0x66); }
void pcmpgtq(Xmm xmm, const Operand& op) { opSSE(xmm, op, T_66 | T_0F38, 0x37, isXMM_XMMorMEM); }
void pcmpgtw(Mmx mmx, const Operand& op) { opMMX(mmx, op, 0x65); }
void pcmpistri(Xmm xmm, const Operand& op, uint8_t imm) { opSSE(xmm, op, T_66|T_0F3A, 0x63, isXMM_XMMorMEM, imm); }
void pcmpistrm(Xmm xmm, const Operand& op, uint8_t imm) { opSSE(xmm, op, T_66|T_0F3A, 0x62, isXMM_XMMorMEM, imm); }
void pdep(Reg32e r1, Reg32e r2, const Operand& op) { opRRO(r1, r2, op, T_APX|T_F2|T_0F38, 0xf5); }
void pext(Reg32e r1, Reg32e r2, const Operand& op) { opRRO(r1, r2, op, T_APX|T_F3|T_0F38, 0xf5); }
void pextrb(const Operand& op, Xmm xmm, uint8_t imm) { opExt(op, xmm, 0x14, imm); }
void pextrd(const Operand& op, Xmm xmm, uint8_t imm) { opExt(op, xmm, 0x16, imm); }
void pextrw(const Operand& op, Mmx xmm, uint8_t imm) { opExt(op, xmm, 0x15, imm, true); }
void phaddd(Mmx mmx, const Operand& op) { opMMX(mmx, op, 0x02, T_0F38, T_66); }
void phaddsw(Mmx mmx, const Operand& op) { opMMX(mmx, op, 0x03, T_0F38, T_66); }
void phaddw(Mmx mmx, const Operand& op) { opMMX(mmx, op, 0x01, T_0F38, T_66); }
void phminposuw(Xmm xmm, const Operand& op) { opSSE(xmm, op, T_66|T_0F38, 0x41, isXMM_XMMorMEM, NONE); }
void phsubd(Mmx mmx, const Operand& op) { opMMX(mmx, op, 0x06, T_0F38, T_66); }
void phsubsw(Mmx mmx, const Operand& op) { opMMX(mmx, op, 0x07, T_0F38, T_66); }
void phsubw(Mmx mmx, const Operand& op) { opMMX(mmx, op, 0x05, T_0F38, T_66); }
void pinsrb(Xmm xmm, const Operand& op, uint8_t imm) { opSSE(xmm, op, T_66 | T_0F3A, 0x20, isXMM_REG32orMEM, imm); }
void pinsrd(Xmm xmm, const Operand& op, uint8_t imm) { opSSE(xmm, op, T_66 | T_0F3A, 0x22, isXMM_REG32orMEM, imm); }
void pinsrw(Mmx mmx, const Operand& op, int imm) { if (!op.isREG(32) && !op.isMEM()) XBYAK_THROW(ERR_BAD_COMBINATION) opSSE(mmx, op, T_0F | (mmx.isXMM() ? T_66 : T_NONE), 0xC4, 0, imm); }
void pmaddubsw(Mmx mmx, const Operand& op) { opMMX(mmx, op, 0x04, T_0F38, T_66); }
void pmaddwd(Mmx mmx, const Operand& op) { opMMX(mmx, op, 0xF5); }
void pmaxsb(Xmm xmm, const Operand& op) { opSSE(xmm, op, T_66 | T_0F38, 0x3C, isXMM_XMMorMEM); }
void pmaxsd(Xmm xmm, const Operand& op) { opSSE(xmm, op, T_66 | T_0F38, 0x3D, isXMM_XMMorMEM); }
void pmaxsw(Mmx mmx, const Operand& op) { opMMX(mmx, op, 0xEE); }
void pmaxub(Mmx mmx, const Operand& op) { opMMX(mmx, op, 0xDE); }
void pmaxud(Xmm xmm, const Operand& op) { opSSE(xmm, op, T_66 | T_0F38, 0x3F, isXMM_XMMorMEM); }
void pmaxuw(Xmm xmm, const Operand& op) { opSSE(xmm, op, T_66 | T_0F38, 0x3E, isXMM_XMMorMEM); }
void pminsb(Xmm xmm, const Operand& op) { opSSE(xmm, op, T_66 | T_0F38, 0x38, isXMM_XMMorMEM); }
void pminsd(Xmm xmm, const Operand& op) { opSSE(xmm, op, T_66 | T_0F38, 0x39, isXMM_XMMorMEM); }
void pminsw(Mmx mmx, const Operand& op) { opMMX(mmx, op, 0xEA); }
void pminub(Mmx mmx, const Operand& op) { opMMX(mmx, op, 0xDA); }
void pminud(Xmm xmm, const Operand& op) { opSSE(xmm, op, T_66 | T_0F38, 0x3B, isXMM_XMMorMEM); }
void pminuw(Xmm xmm, const Operand& op) { opSSE(xmm, op, T_66 | T_0F38, 0x3A, isXMM_XMMorMEM); }
void pmovmskb(Reg32e reg, Mmx mmx) { if (mmx.isXMM()) db(0x66); opSSE(reg, mmx, T_0F, 0xD7); }
void pmovsxbd(Xmm xmm, const Operand& op) { opSSE(xmm, op, T_N4|T_N_VL|T_66|T_0F38|T_YMM|T_EVEX, 0x21, isXMM_XMMorMEM, NONE); }
void pmovsxbq(Xmm xmm, const Operand& op) { opSSE(xmm, op, T_N2|T_N_VL|T_66|T_0F38|T_YMM|T_EVEX, 0x22, isXMM_XMMorMEM, NONE); }
void pmovsxbw(Xmm xmm, const Operand& op) { opSSE(xmm, op, T_N8|T_N_VL|T_66|T_0F38|T_YMM|T_EVEX, 0x20, isXMM_XMMorMEM, NONE); }
void pmovsxdq(Xmm xmm, const Operand& op) { opSSE(xmm, op, T_N8|T_N_VL|T_66|T_0F38|T_W0|T_YMM|T_EVEX, 0x25, isXMM_XMMorMEM, NONE); }
void pmovsxwd(Xmm xmm, const Operand& op) { opSSE(xmm, op, T_N8|T_N_VL|T_66|T_0F38|T_YMM|T_EVEX, 0x23, isXMM_XMMorMEM, NONE); }
void pmovsxwq(Xmm xmm, const Operand& op) { opSSE(xmm, op, T_N4|T_N_VL|T_66|T_0F38|T_YMM|T_EVEX, 0x24, isXMM_XMMorMEM, NONE); }
void pmovzxbd(Xmm xmm, const Operand& op) { opSSE(xmm, op, T_N4|T_N_VL|T_66|T_0F38|T_YMM|T_EVEX, 0x31, isXMM_XMMorMEM, NONE); }
void pmovzxbq(Xmm xmm, const Operand& op) { opSSE(xmm, op, T_N2|T_N_VL|T_66|T_0F38|T_YMM|T_EVEX, 0x32, isXMM_XMMorMEM, NONE); }
void pmovzxbw(Xmm xmm, const Operand& op) { opSSE(xmm, op, T_N8|T_N_VL|T_66|T_0F38|T_YMM|T_EVEX, 0x30, isXMM_XMMorMEM, NONE); }
void pmovzxdq(Xmm xmm, const Operand& op) { opSSE(xmm, op, T_N8|T_N_VL|T_66|T_0F38|T_W0|T_YMM|T_EVEX, 0x35, isXMM_XMMorMEM, NONE); }
void pmovzxwd(Xmm xmm, const Operand& op) { opSSE(xmm, op, T_N8|T_N_VL|T_66|T_0F38|T_YMM|T_EVEX, 0x33, isXMM_XMMorMEM, NONE); }
void pmovzxwq(Xmm xmm, const Operand& op) { opSSE(xmm, op, T_N4|T_N_VL|T_66|T_0F38|T_YMM|T_EVEX, 0x34, isXMM_XMMorMEM, NONE); }
void pmuldq(Xmm xmm, const Operand& op) { opSSE(xmm, op, T_66 | T_0F38, 0x28, isXMM_XMMorMEM); }
void pmulhrsw(Mmx mmx, const Operand& op) { opMMX(mmx, op, 0x0B, T_0F38, T_66); }
void pmulhuw(Mmx mmx, const Operand& op) { opMMX(mmx, op, 0xE4); }
void pmulhw(Mmx mmx, const Operand& op) { opMMX(mmx, op, 0xE5); }
void pmulld(Xmm xmm, const Operand& op) { opSSE(xmm, op, T_66 | T_0F38, 0x40, isXMM_XMMorMEM); }
void pmullw(Mmx mmx, const Operand& op) { opMMX(mmx, op, 0xD5); }
void pmuludq(Mmx mmx, const Operand& op) { opMMX(mmx, op, 0xF4); }
void popcnt(Reg reg, const Operand& op) { opCnt(reg, op, 0xB8); }
void popf() { db(0x9D); }
void por(Mmx mmx, const Operand& op) { opMMX(mmx, op, 0xEB); }
void prefetchit0(const Address& addr) { opMR(addr, Reg32(7), T_0F, 0x18); }
void prefetchit1(const Address& addr) { opMR(addr, Reg32(6), T_0F, 0x18); }
void prefetchnta(const Address& addr) { opMR(addr, Reg32(0), T_0F, 0x18); }
void prefetchrst2(const Address& addr) { opMR(addr, Reg32(4), T_0F, 0x18); }
void prefetcht0(const Address& addr) { opMR(addr, Reg32(1), T_0F, 0x18); }
void prefetcht1(const Address& addr) { opMR(addr, Reg32(2), T_0F, 0x18); }
void prefetcht2(const Address& addr) { opMR(addr, Reg32(3), T_0F, 0x18); }
void prefetchw(const Address& addr) { opMR(addr, Reg32(1), T_0F, 0x0D); }
void prefetchwt1(const Address& addr) { opMR(addr, Reg32(2), T_0F, 0x0D); }
void psadbw(Mmx mmx, const Operand& op) { opMMX(mmx, op, 0xF6); }
void pshufb(Mmx mmx, const Operand& op) { opMMX(mmx, op, 0x00, T_0F38, T_66); }
void pshufd(Mmx mmx, const Operand& op, uint8_t imm8) { opMMX(mmx, op, 0x70, T_0F, T_66, imm8); }
void pshufhw(Mmx mmx, const Operand& op, uint8_t imm8) { opMMX(mmx, op, 0x70, T_0F, T_F3, imm8); }
void pshuflw(Mmx mmx, const Operand& op, uint8_t imm8) { opMMX(mmx, op, 0x70, T_0F, T_F2, imm8); }
void pshufw(Mmx mmx, const Operand& op, uint8_t imm8) { opMMX(mmx, op, 0x70, T_0F, T_NONE, imm8); }
void psignb(Mmx mmx, const Operand& op) { opMMX(mmx, op, 0x08, T_0F38, T_66); }
void psignd(Mmx mmx, const Operand& op) { opMMX(mmx, op, 0x0A, T_0F38, T_66); }
void psignw(Mmx mmx, const Operand& op) { opMMX(mmx, op, 0x09, T_0F38, T_66); }
void pslld(Mmx mmx, const Operand& op) { opMMX(mmx, op, 0xF2); }
void pslld(Mmx mmx, int imm8) { opMMX_IMM(mmx, imm8, 0x72, 6); }
void pslldq(Xmm xmm, int imm8) { opMMX_IMM(xmm, imm8, 0x73, 7); }
void psllq(Mmx mmx, const Operand& op) { opMMX(mmx, op, 0xF3); }
void psllq(Mmx mmx, int imm8) { opMMX_IMM(mmx, imm8, 0x73, 6); }
void psllw(Mmx mmx, const Operand& op) { opMMX(mmx, op, 0xF1); }
void psllw(Mmx mmx, int imm8) { opMMX_IMM(mmx, imm8, 0x71, 6); }
void psrad(Mmx mmx, const Operand& op) { opMMX(mmx, op, 0xE2); }
void psrad(Mmx mmx, int imm8) { opMMX_IMM(mmx, imm8, 0x72, 4); }
void psraw(Mmx mmx, const Operand& op) { opMMX(mmx, op, 0xE1); }
void psraw(Mmx mmx, int imm8) { opMMX_IMM(mmx, imm8, 0x71, 4); }
void psrld(Mmx mmx, const Operand& op) { opMMX(mmx, op, 0xD2); }
void psrld(Mmx mmx, int imm8) { opMMX_IMM(mmx, imm8, 0x72, 2); }
void psrldq(Xmm xmm, int imm8) { opMMX_IMM(xmm, imm8, 0x73, 3); }
void psrlq(Mmx mmx, const Operand& op) { opMMX(mmx, op, 0xD3); }
void psrlq(Mmx mmx, int imm8) { opMMX_IMM(mmx, imm8, 0x73, 2); }
void psrlw(Mmx mmx, const Operand& op) { opMMX(mmx, op, 0xD1); }
void psrlw(Mmx mmx, int imm8) { opMMX_IMM(mmx, imm8, 0x71, 2); }
void psubb(Mmx mmx, const Operand& op) { opMMX(mmx, op, 0xF8); }
void psubd(Mmx mmx, const Operand& op) { opMMX(mmx, op, 0xFA); }
void psubq(Mmx mmx, const Operand& op) { opMMX(mmx, op, 0xFB); }
void psubsb(Mmx mmx, const Operand& op) { opMMX(mmx, op, 0xE8); }
void psubsw(Mmx mmx, const Operand& op) { opMMX(mmx, op, 0xE9); }
void psubusb(Mmx mmx, const Operand& op) { opMMX(mmx, op, 0xD8); }
void psubusw(Mmx mmx, const Operand& op) { opMMX(mmx, op, 0xD9); }
void psubw(Mmx mmx, const Operand& op) { opMMX(mmx, op, 0xF9); }
void ptest(Xmm xmm, const Operand& op) { opSSE(xmm, op, T_66|T_0F38|T_YMM, 0x17, isXMM_XMMorMEM, NONE); }
void punpckhbw(Mmx mmx, const Operand& op) { opMMX(mmx, op, 0x68); }
void punpckhdq(Mmx mmx, const Operand& op) { opMMX(mmx, op, 0x6A); }
void punpckhqdq(Xmm xmm, const Operand& op) { opSSE(xmm, op, T_66|T_0F, 0x6D, isXMM_XMMorMEM); }
void punpckhwd(Mmx mmx, const Operand& op) { opMMX(mmx, op, 0x69); }
void punpcklbw(Mmx mmx, const Operand& op) { opMMX(mmx, op, 0x60); }
void punpckldq(Mmx mmx, const Operand& op) { opMMX(mmx, op, 0x62); }
void punpcklqdq(Xmm xmm, const Operand& op) { opSSE(xmm, op, T_66|T_0F, 0x6C, isXMM_XMMorMEM); }
void punpcklwd(Mmx mmx, const Operand& op) { opMMX(mmx, op, 0x61); }
void pushf() { db(0x9C); }
void pxor(Mmx mmx, const Operand& op) { opMMX(mmx, op, 0xEF); }
void rcl(const Operand& op, Reg8 _cl) { opShift(op, _cl, 2); }
void rcl(const Operand& op, int imm) { opShift(op, imm, 2); }
void rcl(Reg d, const Operand& op, Reg8 _cl) { opShift(op, _cl, 2, &d); }
void rcl(Reg d, const Operand& op, int imm) { opShift(op, imm, 2, &d); }
void rcpps(Xmm xmm, const Operand& op) { opSSE(xmm, op, T_0F, 0x53, isXMM_XMMorMEM); }
void rcpss(Xmm xmm, const Operand& op) { opSSE(xmm, op, T_0F | T_F3, 0x53, isXMM_XMMorMEM); }
void rcr(const Operand& op, Reg8 _cl) { opShift(op, _cl, 3); }
void rcr(const Operand& op, int imm) { opShift(op, imm, 3); }
void rcr(Reg d, const Operand& op, Reg8 _cl) { opShift(op, _cl, 3, &d); }
void rcr(Reg d, const Operand& op, int imm) { opShift(op, imm, 3, &d); }
void rdmsr() { db(0x0F); db(0x32); }
void rdpmc() { db(0x0F); db(0x33); }
void rdrand(Reg r) { if (r.isBit(8)) XBYAK_THROW(ERR_BAD_SIZE_OF_REGISTER) opRR(Reg(6, Operand::REG, r.getBit()), r, T_0F, 0xC7); }
void rdseed(Reg r) { if (r.isBit(8)) XBYAK_THROW(ERR_BAD_SIZE_OF_REGISTER) opRR(Reg(7, Operand::REG, r.getBit()), r, T_0F, 0xC7); }
void rdtsc() { db(0x0F); db(0x31); }
void rdtscp() { db(0x0F); db(0x01); db(0xF9); }
void rep() { db(0xF3); }
void repe() { db(0xF3); }
void repne() { db(0xF2); }
void repnz() { db(0xF2); }
void repz() { db(0xF3); }
void ret(int imm = 0) { if (imm) { db(0xC2); dw(imm); } else { db(0xC3); } }
void retf(int imm = 0) { if (imm) { db(0xCA); dw(imm); } else { db(0xCB); } }
void rol(const Operand& op, Reg8 _cl) { opShift(op, _cl, 8); }
void rol(const Operand& op, int imm) { opShift(op, imm, 8); }
void rol(Reg d, const Operand& op, Reg8 _cl) { opShift(op, _cl, 8, &d); }
void rol(Reg d, const Operand& op, int imm) { opShift(op, imm, 8, &d); }
void ror(const Operand& op, Reg8 _cl) { opShift(op, _cl, 9); }
void ror(const Operand& op, int imm) { opShift(op, imm, 9); }
void ror(Reg d, const Operand& op, Reg8 _cl) { opShift(op, _cl, 9, &d); }
void ror(Reg d, const Operand& op, int imm) { opShift(op, imm, 9, &d); }
void rorx(Reg32e r, const Operand& op, uint8_t imm) { opRRO(r, Reg32e(0, r.getBit()), op, T_0F3A|T_F2|T_APX, 0xF0, imm); }
void roundpd(Xmm xmm, const Operand& op, uint8_t imm) { opSSE(xmm, op, T_66|T_0F3A|T_YMM, 0x09, isXMM_XMMorMEM, imm); }
void roundps(Xmm xmm, const Operand& op, uint8_t imm) { opSSE(xmm, op, T_66|T_0F3A|T_YMM, 0x08, isXMM_XMMorMEM, imm); }
void roundsd(Xmm xmm, const Operand& op, int imm) { opSSE(xmm, op, T_66 | T_0F3A, 0x0B, isXMM_XMMorMEM, static_cast<uint8_t>(imm)); }
void roundss(Xmm xmm, const Operand& op, int imm) { opSSE(xmm, op, T_66 | T_0F3A, 0x0A, isXMM_XMMorMEM, static_cast<uint8_t>(imm)); }
void rsqrtps(Xmm xmm, const Operand& op) { opSSE(xmm, op, T_0F, 0x52, isXMM_XMMorMEM); }
void rsqrtss(Xmm xmm, const Operand& op) { opSSE(xmm, op, T_0F | T_F3, 0x52, isXMM_XMMorMEM); }
void sahf() { db(0x9E); }
void sal(const Operand& op, Reg8 _cl) { opShift(op, _cl, 12); }
void sal(const Operand& op, int imm) { opShift(op, imm, 12); }
void sal(Reg d, const Operand& op, Reg8 _cl) { opShift(op, _cl, 12, &d); }
void sal(Reg d, const Operand& op, int imm) { opShift(op, imm, 12, &d); }
void sar(const Operand& op, Reg8 _cl) { opShift(op, _cl, 15); }
void sar(const Operand& op, int imm) { opShift(op, imm, 15); }
void sar(Reg d, const Operand& op, Reg8 _cl) { opShift(op, _cl, 15, &d); }
void sar(Reg d, const Operand& op, int imm) { opShift(op, imm, 15, &d); }
void sarx(Reg32e r1, const Operand& op, Reg32e r2) { opRRO(r1, r2, op, T_APX|T_F3|T_0F38, 0xf7); }
void sbb(const Operand& op, uint32_t imm) { opOI(op, imm, 0x18, 3); }
void sbb(const Operand& op1, const Operand& op2) { opRO_MR(op1, op2, 0x18); }
void sbb(Reg d, const Operand& op, uint32_t imm) { opROI(d, op, imm, T_NONE, 3); }
void sbb(Reg d, const Operand& op1, const Operand& op2) { opROO(d, op1, op2, T_NONE, 0x18); }
void scasb() { db(0xAE); }
void scasd() { db(0xAF); }
void scasw() { db(0x66); db(0xAF); }
void serialize() { db(0x0F); db(0x01); db(0xE8); }
void seta(const Operand& op) { opSetCC(op, 7); }//-V524
void setae(const Operand& op) { opSetCC(op, 3); }//-V524
void setb(const Operand& op) { opSetCC(op, 2); }//-V524
void setbe(const Operand& op) { opSetCC(op, 6); }//-V524
void setc(const Operand& op) { opSetCC(op, 2); }//-V524
void sete(const Operand& op) { opSetCC(op, 4); }//-V524
void setg(const Operand& op) { opSetCC(op, 15); }//-V524
void setge(const Operand& op) { opSetCC(op, 13); }//-V524
void setl(const Operand& op) { opSetCC(op, 12); }//-V524
void setle(const Operand& op) { opSetCC(op, 14); }//-V524
void setna(const Operand& op) { opSetCC(op, 6); }//-V524
void setnae(const Operand& op) { opSetCC(op, 2); }//-V524
void setnb(const Operand& op) { opSetCC(op, 3); }//-V524
void setnbe(const Operand& op) { opSetCC(op, 7); }//-V524
void setnc(const Operand& op) { opSetCC(op, 3); }//-V524
void setne(const Operand& op) { opSetCC(op, 5); }//-V524
void setng(const Operand& op) { opSetCC(op, 14); }//-V524
void setnge(const Operand& op) { opSetCC(op, 12); }//-V524
void setnl(const Operand& op) { opSetCC(op, 13); }//-V524
void setnle(const Operand& op) { opSetCC(op, 15); }//-V524
void setno(const Operand& op) { opSetCC(op, 1); }//-V524
void setnp(const Operand& op) { opSetCC(op, 11); }//-V524
void setns(const Operand& op) { opSetCC(op, 9); }//-V524
void setnz(const Operand& op) { opSetCC(op, 5); }//-V524
void seto(const Operand& op) { opSetCC(op, 0); }//-V524
void setp(const Operand& op) { opSetCC(op, 10); }//-V524
void setpe(const Operand& op) { opSetCC(op, 10); }//-V524
void setpo(const Operand& op) { opSetCC(op, 11); }//-V524
void sets(const Operand& op) { opSetCC(op, 8); }//-V524
void setz(const Operand& op) { opSetCC(op, 4); }//-V524
void sfence() { db(0x0F); db(0xAE); db(0xF8); }
void sha1msg1(Xmm x, const Operand& op) { opSSE_APX(x, op, T_0F38, 0xC9, T_MUST_EVEX, 0xD9); }
void sha1msg2(Xmm x, const Operand& op) { opSSE_APX(x, op, T_0F38, 0xCA, T_MUST_EVEX, 0xDA); }
void sha1nexte(Xmm x, const Operand& op) { opSSE_APX(x, op, T_0F38, 0xC8, T_MUST_EVEX, 0xD8); }
void sha1rnds4(Xmm x, const Operand& op, uint8_t imm) { opSSE_APX(x, op, T_0F3A, 0xCC, T_MUST_EVEX, 0xD4, imm); }
void sha256msg1(Xmm x, const Operand& op) { opSSE_APX(x, op, T_0F38, 0xCC, T_MUST_EVEX, 0xDC); }
void sha256msg2(Xmm x, const Operand& op) { opSSE_APX(x, op, T_0F38, 0xCD, T_MUST_EVEX, 0xDD); }
void sha256rnds2(Xmm x, const Operand& op) { opSSE_APX(x, op, T_0F38, 0xCB, T_MUST_EVEX, 0xDB); }
void shl(const Operand& op, Reg8 _cl) { opShift(op, _cl, 12); }
void shl(const Operand& op, int imm) { opShift(op, imm, 12); }
void shl(Reg d, const Operand& op, Reg8 _cl) { opShift(op, _cl, 12, &d); }
void shl(Reg d, const Operand& op, int imm) { opShift(op, imm, 12, &d); }
void shld(const Operand& op, Reg reg, Reg8 _cl) { opShxd(Reg(), op, reg, 0, 0xA4, 0x24, &_cl); }
void shld(const Operand& op, Reg reg, uint8_t imm) { opShxd(Reg(), op, reg, imm, 0xA4, 0x24); }
void shld(Reg d, const Operand& op, Reg reg, Reg8 _cl) { opShxd(d, op, reg, 0, 0xA4, 0x24, &_cl); }
void shld(Reg d, const Operand& op, Reg reg, uint8_t imm) { opShxd(d, op, reg, imm, 0xA4, 0x24); }
void shlx(Reg32e r1, const Operand& op, Reg32e r2) { opRRO(r1, r2, op, T_APX|T_66|T_0F38, 0xf7); }
void shr(const Operand& op, Reg8 _cl) { opShift(op, _cl, 13); }
void shr(const Operand& op, int imm) { opShift(op, imm, 13); }
void shr(Reg d, const Operand& op, Reg8 _cl) { opShift(op, _cl, 13, &d); }
void shr(Reg d, const Operand& op, int imm) { opShift(op, imm, 13, &d); }
void shrd(const Operand& op, Reg reg, Reg8 _cl) { opShxd(Reg(), op, reg, 0, 0xAC, 0x2C, &_cl); }
void shrd(const Operand& op, Reg reg, uint8_t imm) { opShxd(Reg(), op, reg, imm, 0xAC, 0x2C); }
void shrd(Reg d, const Operand& op, Reg reg, Reg8 _cl) { opShxd(d, op, reg, 0, 0xAC, 0x2C, &_cl); }
void shrd(Reg d, const Operand& op, Reg reg, uint8_t imm) { opShxd(d, op, reg, imm, 0xAC, 0x2C); }
void shrx(Reg32e r1, const Operand& op, Reg32e r2) { opRRO(r1, r2, op, T_APX|T_F2|T_0F38, 0xf7); }
void shufpd(Xmm xmm, const Operand& op, uint8_t imm8) { opSSE(xmm, op, T_0F | T_66, 0xC6, isXMM_XMMorMEM, imm8); }
void shufps(Xmm xmm, const Operand& op, uint8_t imm8) { opSSE(xmm, op, T_0F, 0xC6, isXMM_XMMorMEM, imm8); }
void sqrtpd(Xmm xmm, const Operand& op) { opSSE(xmm, op, T_0F | T_66, 0x51, isXMM_XMMorMEM); }
void sqrtps(Xmm xmm, const Operand& op) { opSSE(xmm, op, T_0F, 0x51, isXMM_XMMorMEM); }
void sqrtsd(Xmm xmm, const Operand& op) { opSSE(xmm, op, T_0F | T_F2, 0x51, isXMM_XMMorMEM); }
void sqrtss(Xmm xmm, const Operand& op) { opSSE(xmm, op, T_0F | T_F3, 0x51, isXMM_XMMorMEM); }
void stac() { db(0x0F); db(0x01); db(0xCB); }
void stc() { db(0xF9); }
void std() { db(0xFD); }
void sti() { db(0xFB); }
void stmxcsr(const Address& addr) { opMR(addr, Reg32(3), T_0F, 0xAE); }
void stosb() { db(0xAA); }
void stosd() { db(0xAB); }
void stosw() { db(0x66); db(0xAB); }
void sub(const Operand& op, uint32_t imm) { opOI(op, imm, 0x28, 5); }
void sub(const Operand& op1, const Operand& op2) { opRO_MR(op1, op2, 0x28); }
void sub(Reg d, const Operand& op, uint32_t imm) { opROI(d, op, imm, T_NF|T_CODE1_IF1, 5); }
void sub(Reg d, const Operand& op1, const Operand& op2) { opROO(d, op1, op2, T_NF|T_CODE1_IF1, 0x28); }
void subpd(Xmm xmm, const Operand& op) { opSSE(xmm, op, T_0F | T_66, 0x5C, isXMM_XMMorMEM); }
void subps(Xmm xmm, const Operand& op) { opSSE(xmm, op, T_0F, 0x5C, isXMM_XMMorMEM); }
void subsd(Xmm xmm, const Operand& op) { opSSE(xmm, op, T_0F | T_F2, 0x5C, isXMM_XMMorMEM); }
void subss(Xmm xmm, const Operand& op) { opSSE(xmm, op, T_0F | T_F3, 0x5C, isXMM_XMMorMEM); }
void sysenter() { db(0x0F); db(0x34); }
void sysexit() { db(0x0F); db(0x35); }
void tpause(Reg32 r) { int idx = r.getIdx(); if (idx > 7) XBYAK_THROW(ERR_BAD_PARAMETER) db(0x66); db(0x0F); db(0xAE); setModRM(3, 6, idx); }
void tzcnt(Reg reg, const Operand& op) { if (opROO(Reg(), op, reg, T_APX|T_NF, 0xF4)) return; opCnt(reg, op, 0xBC); }
void ucomisd(Xmm xmm, const Operand& op) { opSSE(xmm, op, T_66|T_0F, 0x2E, isXMM_XMMorMEM); }
void ucomiss(Xmm xmm, const Operand& op) { opSSE(xmm, op, T_0F, 0x2E, isXMM_XMMorMEM); }
void ud2() { db(0x0F); db(0x0B); }
void umonitor(Reg r) { int idx = r.getIdx(); if (idx > 7) XBYAK_THROW(ERR_BAD_PARAMETER) int bit = r.getBit(); if (BIT != bit) { if ((BIT == 32 && bit == 16) || (BIT == 64 && bit == 32)) { db(0x67); } else { XBYAK_THROW(ERR_BAD_SIZE_OF_REGISTER) } } db(0xF3); db(0x0F); db(0xAE); setModRM(3, 6, idx); }
void umwait(Reg32 r) { int idx = r.getIdx(); if (idx > 7) XBYAK_THROW(ERR_BAD_PARAMETER) db(0xF2); db(0x0F); db(0xAE); setModRM(3, 6, idx); }
void unpckhpd(Xmm xmm, const Operand& op) { opSSE(xmm, op, T_0F | T_66, 0x15, isXMM_XMMorMEM); }
void unpckhps(Xmm xmm, const Operand& op) { opSSE(xmm, op, T_0F, 0x15, isXMM_XMMorMEM); }
void unpcklpd(Xmm xmm, const Operand& op) { opSSE(xmm, op, T_0F | T_66, 0x14, isXMM_XMMorMEM); }
void unpcklps(Xmm xmm, const Operand& op) { opSSE(xmm, op, T_0F, 0x14, isXMM_XMMorMEM); }
void vaddpd(Xmm xmm, const Operand& op1, const Operand& op2 = Operand()) { opAVX_X_X_XM(xmm, op1, op2, T_0F | T_66 | T_EW1 | T_YMM | T_EVEX | T_ER_Z | T_B64, 0x58); }
void vaddps(Xmm xmm, const Operand& op1, const Operand& op2 = Operand()) { opAVX_X_X_XM(xmm, op1, op2, T_0F | T_W0 | T_YMM | T_EVEX | T_ER_Z | T_B32, 0x58); }
void vaddsd(Xmm xmm, const Operand& op1, const Operand& op2 = Operand()) { opAVX_X_X_XM(xmm, op1, op2, T_0F | T_F2 | T_EW1 | T_EVEX | T_ER_X | T_N8, 0x58); }
void vaddss(Xmm xmm, const Operand& op1, const Operand& op2 = Operand()) { opAVX_X_X_XM(xmm, op1, op2, T_0F | T_F3 | T_W0 | T_EVEX | T_ER_X | T_N4, 0x58); }
void vaddsubpd(Xmm xmm, const Operand& op1, const Operand& op2 = Operand()) { opAVX_X_X_XM(xmm, op1, op2, T_66|T_0F|T_YMM, 0xD0); }
void vaddsubps(Xmm xmm, const Operand& op1, const Operand& op2 = Operand()) { opAVX_X_X_XM(xmm, op1, op2, T_F2|T_0F|T_YMM, 0xD0); }
void vaesdec(Xmm xmm, const Operand& op1, const Operand& op2 = Operand()) { opAVX_X_X_XM(xmm, op1, op2, T_66|T_0F38|T_YMM|T_EVEX, 0xDE); }
void vaesdeclast(Xmm xmm, const Operand& op1, const Operand& op2 = Operand()) { opAVX_X_X_XM(xmm, op1, op2, T_66|T_0F38|T_YMM|T_EVEX, 0xDF); }
void vaesenc(Xmm xmm, const Operand& op1, const Operand& op2 = Operand()) { opAVX_X_X_XM(xmm, op1, op2, T_66|T_0F38|T_YMM|T_EVEX, 0xDC); }
void vaesenclast(Xmm xmm, const Operand& op1, const Operand& op2 = Operand()) { opAVX_X_X_XM(xmm, op1, op2, T_66|T_0F38|T_YMM|T_EVEX, 0xDD); }
void vaesimc(Xmm xm, const Operand& op) { opAVX_X_XM_IMM(xm, op, T_66|T_0F38|T_W0, 0xDB); }
void vaeskeygenassist(Xmm xm, const Operand& op, uint8_t imm) { opAVX_X_XM_IMM(xm, op, T_66|T_0F3A, 0xDF, imm); }
void vandnpd(Xmm xmm, const Operand& op1, const Operand& op2 = Operand()) { opAVX_X_X_XM(xmm, op1, op2, T_0F | T_66 | T_EW1 | T_YMM | T_EVEX | T_B64, 0x55); }
void vandnps(Xmm xmm, const Operand& op1, const Operand& op2 = Operand()) { opAVX_X_X_XM(xmm, op1, op2, T_0F | T_W0 | T_YMM | T_EVEX | T_B32, 0x55); }
void vandpd(Xmm xmm, const Operand& op1, const Operand& op2 = Operand()) { opAVX_X_X_XM(xmm, op1, op2, T_0F | T_66 | T_EW1 | T_YMM | T_EVEX | T_B64, 0x54); }
void vandps(Xmm xmm, const Operand& op1, const Operand& op2 = Operand()) { opAVX_X_X_XM(xmm, op1, op2, T_0F | T_W0 | T_YMM | T_EVEX | T_B32, 0x54); }
void vbcstnebf162ps(Xmm x, const Address& addr) { opVex(x, 0, addr, T_F3|T_0F38|T_W0|T_YMM|T_B16, 0xB1); }
void vbcstnesh2ps(Xmm x, const Address& addr) { opVex(x, 0, addr, T_66|T_0F38|T_W0|T_YMM|T_B16, 0xB1); }
void vblendpd(Xmm x1, Xmm x2, const Operand& op, uint8_t imm) { opAVX_X_X_XM(x1, x2, op, T_66|T_0F3A|T_W0|T_YMM, 0x0D, imm); }
void vblendps(Xmm x1, Xmm x2, const Operand& op, uint8_t imm) { opAVX_X_X_XM(x1, x2, op, T_66|T_0F3A|T_W0|T_YMM, 0x0C, imm); }
void vblendvpd(Xmm x1, Xmm x2, const Operand& op, Xmm x4) { opAVX_X_X_XM(x1, x2, op, T_0F3A | T_66 | T_YMM, 0x4B, x4.getIdx() << 4); }
void vblendvps(Xmm x1, Xmm x2, const Operand& op, Xmm x4) { opAVX_X_X_XM(x1, x2, op, T_0F3A | T_66 | T_YMM, 0x4A, x4.getIdx() << 4); }
void vbroadcastf128(Ymm y, const Address& addr) { opAVX_X_XM_IMM(y, addr, T_0F38 | T_66 | T_W0 | T_YMM, 0x1A); }
void vbroadcasti128(Ymm y, const Address& addr) { opAVX_X_XM_IMM(y, addr, T_0F38 | T_66 | T_W0 | T_YMM, 0x5A); }
void vbroadcastsd(Ymm y, const Operand& op) { if (!op.isMEM() && !(y.isYMM() && op.isXMM()) && !(y.isZMM() && op.isXMM())) XBYAK_THROW(ERR_BAD_COMBINATION) opAVX_X_XM_IMM(y, op, T_0F38 | T_66 | T_W0 | T_YMM | T_EVEX | T_EW1 | T_N8, 0x19); }
void vbroadcastss(Xmm x, const Operand& op) { if (!(op.isXMM() || op.isMEM())) XBYAK_THROW(ERR_BAD_COMBINATION) opAVX_X_XM_IMM(x, op, T_N4|T_66|T_0F38|T_W0|T_YMM|T_EVEX, 0x18); }
void vcmpeq_ospd(Xmm x1, Xmm x2, const Operand& op) { vcmppd(x1, x2, op, 16); }
void vcmpeq_osps(Xmm x1, Xmm x2, const Operand& op) { vcmpps(x1, x2, op, 16); }
void vcmpeq_ossd(Xmm x1, Xmm x2, const Operand& op) { vcmpsd(x1, x2, op, 16); }
void vcmpeq_osss(Xmm x1, Xmm x2, const Operand& op) { vcmpss(x1, x2, op, 16); }
void vcmpeq_uqpd(Xmm x1, Xmm x2, const Operand& op) { vcmppd(x1, x2, op, 8); }
void vcmpeq_uqps(Xmm x1, Xmm x2, const Operand& op) { vcmpps(x1, x2, op, 8); }
void vcmpeq_uqsd(Xmm x1, Xmm x2, const Operand& op) { vcmpsd(x1, x2, op, 8); }
void vcmpeq_uqss(Xmm x1, Xmm x2, const Operand& op) { vcmpss(x1, x2, op, 8); }
void vcmpeq_uspd(Xmm x1, Xmm x2, const Operand& op) { vcmppd(x1, x2, op, 24); }
void vcmpeq_usps(Xmm x1, Xmm x2, const Operand& op) { vcmpps(x1, x2, op, 24); }
void vcmpeq_ussd(Xmm x1, Xmm x2, const Operand& op) { vcmpsd(x1, x2, op, 24); }
void vcmpeq_usss(Xmm x1, Xmm x2, const Operand& op) { vcmpss(x1, x2, op, 24); }
void vcmpeqpd(Xmm x1, Xmm x2, const Operand& op) { vcmppd(x1, x2, op, 0); }
void vcmpeqps(Xmm x1, Xmm x2, const Operand& op) { vcmpps(x1, x2, op, 0); }
void vcmpeqsd(Xmm x1, Xmm x2, const Operand& op) { vcmpsd(x1, x2, op, 0); }
void vcmpeqss(Xmm x1, Xmm x2, const Operand& op) { vcmpss(x1, x2, op, 0); }
void vcmpfalse_ospd(Xmm x1, Xmm x2, const Operand& op) { vcmppd(x1, x2, op, 27); }
void vcmpfalse_osps(Xmm x1, Xmm x2, const Operand& op) { vcmpps(x1, x2, op, 27); }
void vcmpfalse_ossd(Xmm x1, Xmm x2, const Operand& op) { vcmpsd(x1, x2, op, 27); }
void vcmpfalse_osss(Xmm x1, Xmm x2, const Operand& op) { vcmpss(x1, x2, op, 27); }
void vcmpfalsepd(Xmm x1, Xmm x2, const Operand& op) { vcmppd(x1, x2, op, 11); }
void vcmpfalseps(Xmm x1, Xmm x2, const Operand& op) { vcmpps(x1, x2, op, 11); }
void vcmpfalsesd(Xmm x1, Xmm x2, const Operand& op) { vcmpsd(x1, x2, op, 11); }
void vcmpfalsess(Xmm x1, Xmm x2, const Operand& op) { vcmpss(x1, x2, op, 11); }
void vcmpge_oqpd(Xmm x1, Xmm x2, const Operand& op) { vcmppd(x1, x2, op, 29); }
void vcmpge_oqps(Xmm x1, Xmm x2, const Operand& op) { vcmpps(x1, x2, op, 29); }
void vcmpge_oqsd(Xmm x1, Xmm x2, const Operand& op) { vcmpsd(x1, x2, op, 29); }
void vcmpge_oqss(Xmm x1, Xmm x2, const Operand& op) { vcmpss(x1, x2, op, 29); }
void vcmpgepd(Xmm x1, Xmm x2, const Operand& op) { vcmppd(x1, x2, op, 13); }
void vcmpgeps(Xmm x1, Xmm x2, const Operand& op) { vcmpps(x1, x2, op, 13); }
void vcmpgesd(Xmm x1, Xmm x2, const Operand& op) { vcmpsd(x1, x2, op, 13); }
void vcmpgess(Xmm x1, Xmm x2, const Operand& op) { vcmpss(x1, x2, op, 13); }
void vcmpgt_oqpd(Xmm x1, Xmm x2, const Operand& op) { vcmppd(x1, x2, op, 30); }
void vcmpgt_oqps(Xmm x1, Xmm x2, const Operand& op) { vcmpps(x1, x2, op, 30); }
void vcmpgt_oqsd(Xmm x1, Xmm x2, const Operand& op) { vcmpsd(x1, x2, op, 30); }
void vcmpgt_oqss(Xmm x1, Xmm x2, const Operand& op) { vcmpss(x1, x2, op, 30); }
void vcmpgtpd(Xmm x1, Xmm x2, const Operand& op) { vcmppd(x1, x2, op, 14); }
void vcmpgtps(Xmm x1, Xmm x2, const Operand& op) { vcmpps(x1, x2, op, 14); }
void vcmpgtsd(Xmm x1, Xmm x2, const Operand& op) { vcmpsd(x1, x2, op, 14); }
void vcmpgtss(Xmm x1, Xmm x2, const Operand& op) { vcmpss(x1, x2, op, 14); }
void vcmple_oqpd(Xmm x1, Xmm x2, const Operand& op) { vcmppd(x1, x2, op, 18); }
void vcmple_oqps(Xmm x1, Xmm x2, const Operand& op) { vcmpps(x1, x2, op, 18); }
void vcmple_oqsd(Xmm x1, Xmm x2, const Operand& op) { vcmpsd(x1, x2, op, 18); }
void vcmple_oqss(Xmm x1, Xmm x2, const Operand& op) { vcmpss(x1, x2, op, 18); }
void vcmplepd(Xmm x1, Xmm x2, const Operand& op) { vcmppd(x1, x2, op, 2); }
void vcmpleps(Xmm x1, Xmm x2, const Operand& op) { vcmpps(x1, x2, op, 2); }
void vcmplesd(Xmm x1, Xmm x2, const Operand& op) { vcmpsd(x1, x2, op, 2); }
void vcmpless(Xmm x1, Xmm x2, const Operand& op) { vcmpss(x1, x2, op, 2); }
void vcmplt_oqpd(Xmm x1, Xmm x2, const Operand& op) { vcmppd(x1, x2, op, 17); }
void vcmplt_oqps(Xmm x1, Xmm x2, const Operand& op) { vcmpps(x1, x2, op, 17); }
void vcmplt_oqsd(Xmm x1, Xmm x2, const Operand& op) { vcmpsd(x1, x2, op, 17); }
void vcmplt_oqss(Xmm x1, Xmm x2, const Operand& op) { vcmpss(x1, x2, op, 17); }
void vcmpltpd(Xmm x1, Xmm x2, const Operand& op) { vcmppd(x1, x2, op, 1); }
void vcmpltps(Xmm x1, Xmm x2, const Operand& op) { vcmpps(x1, x2, op, 1); }
void vcmpltsd(Xmm x1, Xmm x2, const Operand& op) { vcmpsd(x1, x2, op, 1); }
void vcmpltss(Xmm x1, Xmm x2, const Operand& op) { vcmpss(x1, x2, op, 1); }
void vcmpneq_oqpd(Xmm x1, Xmm x2, const Operand& op) { vcmppd(x1, x2, op, 12); }
void vcmpneq_oqps(Xmm x1, Xmm x2, const Operand& op) { vcmpps(x1, x2, op, 12); }
void vcmpneq_oqsd(Xmm x1, Xmm x2, const Operand& op) { vcmpsd(x1, x2, op, 12); }
void vcmpneq_oqss(Xmm x1, Xmm x2, const Operand& op) { vcmpss(x1, x2, op, 12); }
void vcmpneq_ospd(Xmm x1, Xmm x2, const Operand& op) { vcmppd(x1, x2, op, 28); }
void vcmpneq_osps(Xmm x1, Xmm x2, const Operand& op) { vcmpps(x1, x2, op, 28); }
void vcmpneq_ossd(Xmm x1, Xmm x2, const Operand& op) { vcmpsd(x1, x2, op, 28); }
void vcmpneq_osss(Xmm x1, Xmm x2, const Operand& op) { vcmpss(x1, x2, op, 28); }
void vcmpneq_uspd(Xmm x1, Xmm x2, const Operand& op) { vcmppd(x1, x2, op, 20); }
void vcmpneq_usps(Xmm x1, Xmm x2, const Operand& op) { vcmpps(x1, x2, op, 20); }
void vcmpneq_ussd(Xmm x1, Xmm x2, const Operand& op) { vcmpsd(x1, x2, op, 20); }
void vcmpneq_usss(Xmm x1, Xmm x2, const Operand& op) { vcmpss(x1, x2, op, 20); }
void vcmpneqpd(Xmm x1, Xmm x2, const Operand& op) { vcmppd(x1, x2, op, 4); }
void vcmpneqps(Xmm x1, Xmm x2, const Operand& op) { vcmpps(x1, x2, op, 4); }
void vcmpneqsd(Xmm x1, Xmm x2, const Operand& op) { vcmpsd(x1, x2, op, 4); }
void vcmpneqss(Xmm x1, Xmm x2, const Operand& op) { vcmpss(x1, x2, op, 4); }
void vcmpnge_uqpd(Xmm x1, Xmm x2, const Operand& op) { vcmppd(x1, x2, op, 25); }
void vcmpnge_uqps(Xmm x1, Xmm x2, const Operand& op) { vcmpps(x1, x2, op, 25); }
void vcmpnge_uqsd(Xmm x1, Xmm x2, const Operand& op) { vcmpsd(x1, x2, op, 25); }
void vcmpnge_uqss(Xmm x1, Xmm x2, const Operand& op) { vcmpss(x1, x2, op, 25); }
void vcmpngepd(Xmm x1, Xmm x2, const Operand& op) { vcmppd(x1, x2, op, 9); }
void vcmpngeps(Xmm x1, Xmm x2, const Operand& op) { vcmpps(x1, x2, op, 9); }
void vcmpngesd(Xmm x1, Xmm x2, const Operand& op) { vcmpsd(x1, x2, op, 9); }
void vcmpngess(Xmm x1, Xmm x2, const Operand& op) { vcmpss(x1, x2, op, 9); }
void vcmpngt_uqpd(Xmm x1, Xmm x2, const Operand& op) { vcmppd(x1, x2, op, 26); }
void vcmpngt_uqps(Xmm x1, Xmm x2, const Operand& op) { vcmpps(x1, x2, op, 26); }
void vcmpngt_uqsd(Xmm x1, Xmm x2, const Operand& op) { vcmpsd(x1, x2, op, 26); }
void vcmpngt_uqss(Xmm x1, Xmm x2, const Operand& op) { vcmpss(x1, x2, op, 26); }
void vcmpngtpd(Xmm x1, Xmm x2, const Operand& op) { vcmppd(x1, x2, op, 10); }
void vcmpngtps(Xmm x1, Xmm x2, const Operand& op) { vcmpps(x1, x2, op, 10); }
void vcmpngtsd(Xmm x1, Xmm x2, const Operand& op) { vcmpsd(x1, x2, op, 10); }
void vcmpngtss(Xmm x1, Xmm x2, const Operand& op) { vcmpss(x1, x2, op, 10); }
void vcmpnle_uqpd(Xmm x1, Xmm x2, const Operand& op) { vcmppd(x1, x2, op, 22); }
void vcmpnle_uqps(Xmm x1, Xmm x2, const Operand& op) { vcmpps(x1, x2, op, 22); }
void vcmpnle_uqsd(Xmm x1, Xmm x2, const Operand& op) { vcmpsd(x1, x2, op, 22); }
void vcmpnle_uqss(Xmm x1, Xmm x2, const Operand& op) { vcmpss(x1, x2, op, 22); }
void vcmpnlepd(Xmm x1, Xmm x2, const Operand& op) { vcmppd(x1, x2, op, 6); }
void vcmpnleps(Xmm x1, Xmm x2, const Operand& op) { vcmpps(x1, x2, op, 6); }
void vcmpnlesd(Xmm x1, Xmm x2, const Operand& op) { vcmpsd(x1, x2, op, 6); }
void vcmpnless(Xmm x1, Xmm x2, const Operand& op) { vcmpss(x1, x2, op, 6); }
void vcmpnlt_uqpd(Xmm x1, Xmm x2, const Operand& op) { vcmppd(x1, x2, op, 21); }
void vcmpnlt_uqps(Xmm x1, Xmm x2, const Operand& op) { vcmpps(x1, x2, op, 21); }
void vcmpnlt_uqsd(Xmm x1, Xmm x2, const Operand& op) { vcmpsd(x1, x2, op, 21); }
void vcmpnlt_uqss(Xmm x1, Xmm x2, const Operand& op) { vcmpss(x1, x2, op, 21); }
void vcmpnltpd(Xmm x1, Xmm x2, const Operand& op) { vcmppd(x1, x2, op, 5); }
void vcmpnltps(Xmm x1, Xmm x2, const Operand& op) { vcmpps(x1, x2, op, 5); }
void vcmpnltsd(Xmm x1, Xmm x2, const Operand& op) { vcmpsd(x1, x2, op, 5); }
void vcmpnltss(Xmm x1, Xmm x2, const Operand& op) { vcmpss(x1, x2, op, 5); }
void vcmpord_spd(Xmm x1, Xmm x2, const Operand& op) { vcmppd(x1, x2, op, 23); }
void vcmpord_sps(Xmm x1, Xmm x2, const Operand& op) { vcmpps(x1, x2, op, 23); }
void vcmpord_ssd(Xmm x1, Xmm x2, const Operand& op) { vcmpsd(x1, x2, op, 23); }
void vcmpord_sss(Xmm x1, Xmm x2, const Operand& op) { vcmpss(x1, x2, op, 23); }
void vcmpordpd(Xmm x1, Xmm x2, const Operand& op) { vcmppd(x1, x2, op, 7); }
void vcmpordps(Xmm x1, Xmm x2, const Operand& op) { vcmpps(x1, x2, op, 7); }
void vcmpordsd(Xmm x1, Xmm x2, const Operand& op) { vcmpsd(x1, x2, op, 7); }
void vcmpordss(Xmm x1, Xmm x2, const Operand& op) { vcmpss(x1, x2, op, 7); }
void vcmppd(Xmm x1, Xmm x2, const Operand& op, uint8_t imm) { opAVX_X_X_XM(x1, x2, op, T_66|T_0F|T_YMM, 0xC2, imm); }
void vcmpps(Xmm x1, Xmm x2, const Operand& op, uint8_t imm) { opAVX_X_X_XM(x1, x2, op, T_0F|T_YMM, 0xC2, imm); }
void vcmpsd(Xmm x1, Xmm x2, const Operand& op, uint8_t imm) { opAVX_X_X_XM(x1, x2, op, T_F2|T_0F, 0xC2, imm); }
void vcmpss(Xmm x1, Xmm x2, const Operand& op, uint8_t imm) { opAVX_X_X_XM(x1, x2, op, T_F3|T_0F, 0xC2, imm); }
void vcmptrue_uspd(Xmm x1, Xmm x2, const Operand& op) { vcmppd(x1, x2, op, 31); }
void vcmptrue_usps(Xmm x1, Xmm x2, const Operand& op) { vcmpps(x1, x2, op, 31); }
void vcmptrue_ussd(Xmm x1, Xmm x2, const Operand& op) { vcmpsd(x1, x2, op, 31); }
void vcmptrue_usss(Xmm x1, Xmm x2, const Operand& op) { vcmpss(x1, x2, op, 31); }
void vcmptruepd(Xmm x1, Xmm x2, const Operand& op) { vcmppd(x1, x2, op, 15); }
void vcmptrueps(Xmm x1, Xmm x2, const Operand& op) { vcmpps(x1, x2, op, 15); }
void vcmptruesd(Xmm x1, Xmm x2, const Operand& op) { vcmpsd(x1, x2, op, 15); }
void vcmptruess(Xmm x1, Xmm x2, const Operand& op) { vcmpss(x1, x2, op, 15); }
void vcmpunord_spd(Xmm x1, Xmm x2, const Operand& op) { vcmppd(x1, x2, op, 19); }
void vcmpunord_sps(Xmm x1, Xmm x2, const Operand& op) { vcmpps(x1, x2, op, 19); }
void vcmpunord_ssd(Xmm x1, Xmm x2, const Operand& op) { vcmpsd(x1, x2, op, 19); }
void vcmpunord_sss(Xmm x1, Xmm x2, const Operand& op) { vcmpss(x1, x2, op, 19); }
void vcmpunordpd(Xmm x1, Xmm x2, const Operand& op) { vcmppd(x1, x2, op, 3); }
void vcmpunordps(Xmm x1, Xmm x2, const Operand& op) { vcmpps(x1, x2, op, 3); }
void vcmpunordsd(Xmm x1, Xmm x2, const Operand& op) { vcmpsd(x1, x2, op, 3); }
void vcmpunordss(Xmm x1, Xmm x2, const Operand& op) { vcmpss(x1, x2, op, 3); }
void vcomisd(Xmm xm, const Operand& op) { opAVX_X_XM_IMM(xm, op, T_N8|T_66|T_0F|T_EW1|T_EVEX|T_SAE_X, 0x2F); }
void vcomiss(Xmm xm, const Operand& op) { opAVX_X_XM_IMM(xm, op, T_N4|T_0F|T_W0|T_EVEX|T_SAE_X, 0x2F); }
void vcvtdq2pd(Xmm x, const Operand& op) { checkCvt1(x, op); opVex(x, 0, op, T_0F | T_F3 | T_YMM | T_EVEX | T_W0 | T_B32 | T_N8 | T_N_VL, 0xE6); }
void vcvtdq2ps(Xmm xm, const Operand& op) { opAVX_X_XM_IMM(xm, op, T_0F|T_W0|T_YMM|T_EVEX|T_ER_Z|T_B32, 0x5B); }
void vcvtneebf162ps(Xmm x, const Address& addr) { opVex(x, 0, addr, T_F3|T_0F38|T_W0|T_YMM, 0xB0); }
void vcvtneeph2ps(Xmm x, const Address& addr) { opVex(x, 0, addr, T_66|T_0F38|T_W0|T_YMM, 0xB0); }
void vcvtneobf162ps(Xmm x, const Address& addr) { opVex(x, 0, addr, T_F2|T_0F38|T_W0|T_YMM, 0xB0); }
void vcvtneoph2ps(Xmm x, const Address& addr) { opVex(x, 0, addr, T_0F38|T_W0|T_YMM, 0xB0); }
void vcvtneps2bf16(Xmm x, const Operand& op, PreferredEncoding encoding = DefaultEncoding) { opCvt2(x, op, T_F3|T_0F38|T_W0|T_YMM|T_SAE_Z|T_B32|orEvexIf(encoding, 0, T_MUST_EVEX, 0), 0x72); }
void vcvtpd2dq(Xmm x, const Operand& op) { opCvt2(x, op, T_0F | T_F2 | T_YMM | T_EVEX | T_EW1 | T_B64 | T_ER_Z, 0xE6); }
void vcvtpd2ps(Xmm x, const Operand& op) { opCvt2(x, op, T_0F | T_66 | T_YMM | T_EVEX | T_EW1 | T_B64 | T_ER_Z, 0x5A); }
void vcvtph2ps(Xmm x, const Operand& op) { checkCvt1(x, op); opVex(x, 0, op, T_0F38 | T_66 | T_W0 | T_EVEX | T_N8 | T_N_VL | T_SAE_Y, 0x13); }
void vcvtps2dq(Xmm xm, const Operand& op) { opAVX_X_XM_IMM(xm, op, T_66|T_0F|T_W0|T_YMM|T_EVEX|T_ER_Z|T_B32, 0x5B); }
void vcvtps2pd(Xmm x, const Operand& op) { checkCvt1(x, op); opVex(x, 0, op, T_0F | T_YMM | T_EVEX | T_W0 | T_B32 | T_N8 | T_N_VL | T_SAE_Y, 0x5A); }
void vcvtps2ph(const Operand& op, Xmm x, uint8_t imm) { checkCvt1(x, op); opVex(x, 0, op, T_0F3A | T_66 | T_W0 | T_EVEX | T_N8 | T_N_VL | T_SAE_Y | T_M_K, 0x1D, imm); }
void vcvtsd2si(Reg32 r, const Operand& op) { opAVX_X_X_XM(Xmm(r.getIdx()), xm0, op, T_0F | T_F2 | T_W0 | T_EVEX | T_N4 | T_ER_X, 0x2D); }
void vcvtsd2ss(Xmm x1, Xmm x2, const Operand& op) { opAVX_X_X_XM(x1, x2, op, T_N8|T_F2|T_0F|T_EW1|T_EVEX|T_ER_X, 0x5A); }
void vcvtsi2sd(Xmm x1, Xmm x2, const Operand& op) { opCvt3(x1, x2, op, T_0F | T_F2 | T_EVEX, T_W1 | T_EW1 | T_ER_X | T_N8, T_W0 | T_N4, 0x2A); }
void vcvtsi2ss(Xmm x1, Xmm x2, const Operand& op) { opCvt3(x1, x2, op, T_0F | T_F3 | T_EVEX | T_ER_X, T_W1 | T_EW1 | T_N8, T_W0 | T_N4, 0x2A); }
void vcvtss2sd(Xmm x1, Xmm x2, const Operand& op) { opAVX_X_X_XM(x1, x2, op, T_N4|T_F3|T_0F|T_W0|T_EVEX|T_SAE_X, 0x5A); }
void vcvtss2si(Reg32 r, const Operand& op) { opAVX_X_X_XM(Xmm(r.getIdx()), xm0, op, T_0F | T_F3 | T_W0 | T_EVEX | T_ER_X | T_N8, 0x2D); }
void vcvttpd2dq(Xmm x, const Operand& op) { opCvt2(x, op, T_66 | T_0F | T_YMM | T_EVEX |T_EW1 | T_B64 | T_SAE_Z, 0xE6); }
void vcvttps2dq(Xmm xm, const Operand& op) { opAVX_X_XM_IMM(xm, op, T_F3|T_0F|T_W0|T_YMM|T_EVEX|T_SAE_Z|T_B32, 0x5B); }
void vcvttsd2si(Reg32 r, const Operand& op) { opAVX_X_X_XM(Xmm(r.getIdx()), xm0, op, T_0F | T_F2 | T_W0 | T_EVEX | T_N4 | T_SAE_X, 0x2C); }
void vcvttss2si(Reg32 r, const Operand& op) { opAVX_X_X_XM(Xmm(r.getIdx()), xm0, op, T_0F | T_F3 | T_W0 | T_EVEX | T_SAE_X | T_N8, 0x2C); }
void vdivpd(Xmm xmm, const Operand& op1, const Operand& op2 = Operand()) { opAVX_X_X_XM(xmm, op1, op2, T_0F | T_66 | T_EW1 | T_YMM | T_EVEX | T_ER_Z | T_B64, 0x5E); }
void vdivps(Xmm xmm, const Operand& op1, const Operand& op2 = Operand()) { opAVX_X_X_XM(xmm, op1, op2, T_0F | T_W0 | T_YMM | T_EVEX | T_ER_Z | T_B32, 0x5E); }
void vdivsd(Xmm xmm, const Operand& op1, const Operand& op2 = Operand()) { opAVX_X_X_XM(xmm, op1, op2, T_0F | T_F2 | T_EW1 | T_EVEX | T_ER_X | T_N8, 0x5E); }
void vdivss(Xmm xmm, const Operand& op1, const Operand& op2 = Operand()) { opAVX_X_X_XM(xmm, op1, op2, T_0F | T_F3 | T_W0 | T_EVEX | T_ER_X | T_N4, 0x5E); }
void vdppd(Xmm x1, Xmm x2, const Operand& op, uint8_t imm) { opAVX_X_X_XM(x1, x2, op, T_66|T_0F3A|T_W0, 0x41, imm); }
void vdpps(Xmm x1, Xmm x2, const Operand& op, uint8_t imm) { opAVX_X_X_XM(x1, x2, op, T_66|T_0F3A|T_W0|T_YMM, 0x40, imm); }
void vextractf128(const Operand& op, Ymm y, uint8_t imm) { if (!(op.isXMEM() && y.isYMM())) XBYAK_THROW(ERR_BAD_COMBINATION) opVex(y, 0, op, T_0F3A | T_66 | T_W0 | T_YMM, 0x19, imm); }
void vextracti128(const Operand& op, Ymm y, uint8_t imm) { if (!(op.isXMEM() && y.isYMM())) XBYAK_THROW(ERR_BAD_COMBINATION) opVex(y, 0, op, T_0F3A | T_66 | T_W0 | T_YMM, 0x39, imm); }
void vextractps(const Operand& op, Xmm x, uint8_t imm) { if (!((op.isREG(32) || op.isMEM()) && x.isXMM())) XBYAK_THROW(ERR_BAD_COMBINATION) opVex(x, 0, op, T_0F3A | T_66 | T_W0 | T_EVEX | T_N4, 0x17, imm); }
void vfmadd132pd(Xmm x1, Xmm x2, const Operand& op) { opAVX_X_X_XM(x1, x2, op, T_66|T_0F38|T_W1|T_EW1|T_YMM|T_EVEX|T_ER_Z|T_B64, 0x98); }
void vfmadd132ps(Xmm x1, Xmm x2, const Operand& op) { opAVX_X_X_XM(x1, x2, op, T_66|T_0F38|T_W0|T_YMM|T_EVEX|T_ER_Z|T_B32, 0x98); }
void vfmadd132sd(Xmm x1, Xmm x2, const Operand& op) { opAVX_X_X_XM(x1, x2, op, T_N8|T_66|T_0F38|T_W1|T_EW1|T_EVEX|T_ER_X, 0x99); }
void vfmadd132ss(Xmm x1, Xmm x2, const Operand& op) { opAVX_X_X_XM(x1, x2, op, T_N4|T_66|T_0F38|T_W0|T_EVEX|T_ER_X, 0x99); }
void vfmadd213pd(Xmm x1, Xmm x2, const Operand& op) { opAVX_X_X_XM(x1, x2, op, T_66|T_0F38|T_W1|T_EW1|T_YMM|T_EVEX|T_ER_Z|T_B64, 0xA8); }
void vfmadd213ps(Xmm x1, Xmm x2, const Operand& op) { opAVX_X_X_XM(x1, x2, op, T_66|T_0F38|T_W0|T_YMM|T_EVEX|T_ER_Z|T_B32, 0xA8); }
void vfmadd213sd(Xmm x1, Xmm x2, const Operand& op) { opAVX_X_X_XM(x1, x2, op, T_N8|T_66|T_0F38|T_W1|T_EW1|T_EVEX|T_ER_X, 0xA9); }
void vfmadd213ss(Xmm x1, Xmm x2, const Operand& op) { opAVX_X_X_XM(x1, x2, op, T_N4|T_66|T_0F38|T_W0|T_EVEX|T_ER_X, 0xA9); }
void vfmadd231pd(Xmm x1, Xmm x2, const Operand& op) { opAVX_X_X_XM(x1, x2, op, T_66|T_0F38|T_W1|T_EW1|T_YMM|T_EVEX|T_ER_Z|T_B64, 0xB8); }
void vfmadd231ps(Xmm x1, Xmm x2, const Operand& op) { opAVX_X_X_XM(x1, x2, op, T_66|T_0F38|T_W0|T_YMM|T_EVEX|T_ER_Z|T_B32, 0xB8); }
void vfmadd231sd(Xmm x1, Xmm x2, const Operand& op) { opAVX_X_X_XM(x1, x2, op, T_N8|T_66|T_0F38|T_W1|T_EW1|T_EVEX|T_ER_X, 0xB9); }
void vfmadd231ss(Xmm x1, Xmm x2, const Operand& op) { opAVX_X_X_XM(x1, x2, op, T_N4|T_66|T_0F38|T_W0|T_EVEX|T_ER_X, 0xB9); }
void vfmaddsub132pd(Xmm x1, Xmm x2, const Operand& op) { opAVX_X_X_XM(x1, x2, op, T_66|T_0F38|T_W1|T_EW1|T_YMM|T_EVEX|T_ER_Z|T_B64, 0x96); }
void vfmaddsub132ps(Xmm x1, Xmm x2, const Operand& op) { opAVX_X_X_XM(x1, x2, op, T_66|T_0F38|T_W0|T_YMM|T_EVEX|T_ER_Z|T_B32, 0x96); }
void vfmaddsub213pd(Xmm x1, Xmm x2, const Operand& op) { opAVX_X_X_XM(x1, x2, op, T_66|T_0F38|T_W1|T_EW1|T_YMM|T_EVEX|T_ER_Z|T_B64, 0xA6); }
void vfmaddsub213ps(Xmm x1, Xmm x2, const Operand& op) { opAVX_X_X_XM(x1, x2, op, T_66|T_0F38|T_W0|T_YMM|T_EVEX|T_ER_Z|T_B32, 0xA6); }
void vfmaddsub231pd(Xmm x1, Xmm x2, const Operand& op) { opAVX_X_X_XM(x1, x2, op, T_66|T_0F38|T_W1|T_EW1|T_YMM|T_EVEX|T_ER_Z|T_B64, 0xB6); }
void vfmaddsub231ps(Xmm x1, Xmm x2, const Operand& op) { opAVX_X_X_XM(x1, x2, op, T_66|T_0F38|T_W0|T_YMM|T_EVEX|T_ER_Z|T_B32, 0xB6); }
void vfmsub132pd(Xmm x1, Xmm x2, const Operand& op) { opAVX_X_X_XM(x1, x2, op, T_66|T_0F38|T_W1|T_EW1|T_YMM|T_EVEX|T_ER_Z|T_B64, 0x9A); }
void vfmsub132ps(Xmm x1, Xmm x2, const Operand& op) { opAVX_X_X_XM(x1, x2, op, T_66|T_0F38|T_W0|T_YMM|T_EVEX|T_ER_Z|T_B32, 0x9A); }
void vfmsub132sd(Xmm x1, Xmm x2, const Operand& op) { opAVX_X_X_XM(x1, x2, op, T_N8|T_66|T_0F38|T_W1|T_EW1|T_EVEX|T_ER_X, 0x9B); }
void vfmsub132ss(Xmm x1, Xmm x2, const Operand& op) { opAVX_X_X_XM(x1, x2, op, T_N4|T_66|T_0F38|T_W0|T_EVEX|T_ER_X, 0x9B); }
void vfmsub213pd(Xmm x1, Xmm x2, const Operand& op) { opAVX_X_X_XM(x1, x2, op, T_66|T_0F38|T_W1|T_EW1|T_YMM|T_EVEX|T_ER_Z|T_B64, 0xAA); }
void vfmsub213ps(Xmm x1, Xmm x2, const Operand& op) { opAVX_X_X_XM(x1, x2, op, T_66|T_0F38|T_W0|T_YMM|T_EVEX|T_ER_Z|T_B32, 0xAA); }
void vfmsub213sd(Xmm x1, Xmm x2, const Operand& op) { opAVX_X_X_XM(x1, x2, op, T_N8|T_66|T_0F38|T_W1|T_EW1|T_EVEX|T_ER_X, 0xAB); }
void vfmsub213ss(Xmm x1, Xmm x2, const Operand& op) { opAVX_X_X_XM(x1, x2, op, T_N4|T_66|T_0F38|T_W0|T_EVEX|T_ER_X, 0xAB); }
void vfmsub231pd(Xmm x1, Xmm x2, const Operand& op) { opAVX_X_X_XM(x1, x2, op, T_66|T_0F38|T_W1|T_EW1|T_YMM|T_EVEX|T_ER_Z|T_B64, 0xBA); }
void vfmsub231ps(Xmm x1, Xmm x2, const Operand& op) { opAVX_X_X_XM(x1, x2, op, T_66|T_0F38|T_W0|T_YMM|T_EVEX|T_ER_Z|T_B32, 0xBA); }
void vfmsub231sd(Xmm x1, Xmm x2, const Operand& op) { opAVX_X_X_XM(x1, x2, op, T_N8|T_66|T_0F38|T_W1|T_EW1|T_EVEX|T_ER_X, 0xBB); }
void vfmsub231ss(Xmm x1, Xmm x2, const Operand& op) { opAVX_X_X_XM(x1, x2, op, T_N4|T_66|T_0F38|T_W0|T_EVEX|T_ER_X, 0xBB); }
void vfmsubadd132pd(Xmm x1, Xmm x2, const Operand& op) { opAVX_X_X_XM(x1, x2, op, T_66|T_0F38|T_W1|T_EW1|T_YMM|T_EVEX|T_ER_Z|T_B64, 0x97); }
void vfmsubadd132ps(Xmm x1, Xmm x2, const Operand& op) { opAVX_X_X_XM(x1, x2, op, T_66|T_0F38|T_W0|T_YMM|T_EVEX|T_ER_Z|T_B32, 0x97); }
void vfmsubadd213pd(Xmm x1, Xmm x2, const Operand& op) { opAVX_X_X_XM(x1, x2, op, T_66|T_0F38|T_W1|T_EW1|T_YMM|T_EVEX|T_ER_Z|T_B64, 0xA7); }
void vfmsubadd213ps(Xmm x1, Xmm x2, const Operand& op) { opAVX_X_X_XM(x1, x2, op, T_66|T_0F38|T_W0|T_YMM|T_EVEX|T_ER_Z|T_B32, 0xA7); }
void vfmsubadd231pd(Xmm x1, Xmm x2, const Operand& op) { opAVX_X_X_XM(x1, x2, op, T_66|T_0F38|T_W1|T_EW1|T_YMM|T_EVEX|T_ER_Z|T_B64, 0xB7); }
void vfmsubadd231ps(Xmm x1, Xmm x2, const Operand& op) { opAVX_X_X_XM(x1, x2, op, T_66|T_0F38|T_W0|T_YMM|T_EVEX|T_ER_Z|T_B32, 0xB7); }
void vfnmadd132pd(Xmm x1, Xmm x2, const Operand& op) { opAVX_X_X_XM(x1, x2, op, T_66|T_0F38|T_W1|T_EW1|T_YMM|T_EVEX|T_ER_Z|T_B64, 0x9C); }
void vfnmadd132ps(Xmm x1, Xmm x2, const Operand& op) { opAVX_X_X_XM(x1, x2, op, T_66|T_0F38|T_W0|T_YMM|T_EVEX|T_ER_Z|T_B32, 0x9C); }
void vfnmadd132sd(Xmm x1, Xmm x2, const Operand& op) { opAVX_X_X_XM(x1, x2, op, T_N8|T_66|T_0F38|T_W1|T_EW1|T_EVEX|T_ER_X, 0x9D); }
void vfnmadd132ss(Xmm x1, Xmm x2, const Operand& op) { opAVX_X_X_XM(x1, x2, op, T_N4|T_66|T_0F38|T_W0|T_EVEX|T_ER_X, 0x9D); }
void vfnmadd213pd(Xmm x1, Xmm x2, const Operand& op) { opAVX_X_X_XM(x1, x2, op, T_66|T_0F38|T_W1|T_EW1|T_YMM|T_EVEX|T_ER_Z|T_B64, 0xAC); }
void vfnmadd213ps(Xmm x1, Xmm x2, const Operand& op) { opAVX_X_X_XM(x1, x2, op, T_66|T_0F38|T_W0|T_YMM|T_EVEX|T_ER_Z|T_B32, 0xAC); }
void vfnmadd213sd(Xmm x1, Xmm x2, const Operand& op) { opAVX_X_X_XM(x1, x2, op, T_N8|T_66|T_0F38|T_W1|T_EW1|T_EVEX|T_ER_X, 0xAD); }
void vfnmadd213ss(Xmm x1, Xmm x2, const Operand& op) { opAVX_X_X_XM(x1, x2, op, T_N4|T_66|T_0F38|T_W0|T_EVEX|T_ER_X, 0xAD); }
void vfnmadd231pd(Xmm x1, Xmm x2, const Operand& op) { opAVX_X_X_XM(x1, x2, op, T_66|T_0F38|T_W1|T_EW1|T_YMM|T_EVEX|T_ER_Z|T_B64, 0xBC); }
void vfnmadd231ps(Xmm x1, Xmm x2, const Operand& op) { opAVX_X_X_XM(x1, x2, op, T_66|T_0F38|T_W0|T_YMM|T_EVEX|T_ER_Z|T_B32, 0xBC); }
void vfnmadd231sd(Xmm x1, Xmm x2, const Operand& op) { opAVX_X_X_XM(x1, x2, op, T_N8|T_66|T_0F38|T_W1|T_EW1|T_EVEX|T_ER_X, 0xBD); }
void vfnmadd231ss(Xmm x1, Xmm x2, const Operand& op) { opAVX_X_X_XM(x1, x2, op, T_N4|T_66|T_0F38|T_W0|T_EVEX|T_ER_X, 0xBD); }
void vfnmsub132pd(Xmm x1, Xmm x2, const Operand& op) { opAVX_X_X_XM(x1, x2, op, T_66|T_0F38|T_W1|T_EW1|T_YMM|T_EVEX|T_ER_Z|T_B64, 0x9E); }
void vfnmsub132ps(Xmm x1, Xmm x2, const Operand& op) { opAVX_X_X_XM(x1, x2, op, T_66|T_0F38|T_W0|T_YMM|T_EVEX|T_ER_Z|T_B32, 0x9E); }
void vfnmsub132sd(Xmm x1, Xmm x2, const Operand& op) { opAVX_X_X_XM(x1, x2, op, T_N8|T_66|T_0F38|T_W1|T_EW1|T_EVEX|T_ER_X, 0x9F); }
void vfnmsub132ss(Xmm x1, Xmm x2, const Operand& op) { opAVX_X_X_XM(x1, x2, op, T_N4|T_66|T_0F38|T_W0|T_EVEX|T_ER_X, 0x9F); }
void vfnmsub213pd(Xmm x1, Xmm x2, const Operand& op) { opAVX_X_X_XM(x1, x2, op, T_66|T_0F38|T_W1|T_EW1|T_YMM|T_EVEX|T_ER_Z|T_B64, 0xAE); }
void vfnmsub213ps(Xmm x1, Xmm x2, const Operand& op) { opAVX_X_X_XM(x1, x2, op, T_66|T_0F38|T_W0|T_YMM|T_EVEX|T_ER_Z|T_B32, 0xAE); }
void vfnmsub213sd(Xmm x1, Xmm x2, const Operand& op) { opAVX_X_X_XM(x1, x2, op, T_N8|T_66|T_0F38|T_W1|T_EW1|T_EVEX|T_ER_X, 0xAF); }
void vfnmsub213ss(Xmm x1, Xmm x2, const Operand& op) { opAVX_X_X_XM(x1, x2, op, T_N4|T_66|T_0F38|T_W0|T_EVEX|T_ER_X, 0xAF); }
void vfnmsub231pd(Xmm x1, Xmm x2, const Operand& op) { opAVX_X_X_XM(x1, x2, op, T_66|T_0F38|T_W1|T_EW1|T_YMM|T_EVEX|T_ER_Z|T_B64, 0xBE); }
void vfnmsub231ps(Xmm x1, Xmm x2, const Operand& op) { opAVX_X_X_XM(x1, x2, op, T_66|T_0F38|T_W0|T_YMM|T_EVEX|T_ER_Z|T_B32, 0xBE); }
void vfnmsub231sd(Xmm x1, Xmm x2, const Operand& op) { opAVX_X_X_XM(x1, x2, op, T_N8|T_66|T_0F38|T_W1|T_EW1|T_EVEX|T_ER_X, 0xBF); }
void vfnmsub231ss(Xmm x1, Xmm x2, const Operand& op) { opAVX_X_X_XM(x1, x2, op, T_N4|T_66|T_0F38|T_W0|T_EVEX|T_ER_X, 0xBF); }
void vgatherdpd(Xmm x1, const Address& addr, Xmm x2) { opGather(x1, addr, x2, T_0F38 | T_66 | T_YMM | T_VSIB | T_W1, 0x92, 0); }
void vgatherdps(Xmm x1, const Address& addr, Xmm x2) { opGather(x1, addr, x2, T_0F38 | T_66 | T_YMM | T_VSIB | T_W0, 0x92, 1); }
void vgatherqpd(Xmm x1, const Address& addr, Xmm x2) { opGather(x1, addr, x2, T_0F38 | T_66 | T_YMM | T_VSIB | T_W1, 0x93, 1); }
void vgatherqps(Xmm x1, const Address& addr, Xmm x2) { opGather(x1, addr, x2, T_0F38 | T_66 | T_YMM | T_VSIB | T_W0, 0x93, 2); }
void vgf2p8affineinvqb(Xmm x1, Xmm x2, const Operand& op, uint8_t imm) { opAVX_X_X_XM(x1, x2, op, T_66|T_0F3A|T_W1|T_EW1|T_YMM|T_EVEX|T_SAE_Z|T_B64, 0xCF, imm); }
void vgf2p8affineqb(Xmm x1, Xmm x2, const Operand& op, uint8_t imm) { opAVX_X_X_XM(x1, x2, op, T_66|T_0F3A|T_W1|T_EW1|T_YMM|T_EVEX|T_SAE_Z|T_B64, 0xCE, imm); }
void vgf2p8mulb(Xmm x1, Xmm x2, const Operand& op) { opAVX_X_X_XM(x1, x2, op, T_66|T_0F38|T_W0|T_YMM|T_EVEX|T_SAE_Z, 0xCF); }
void vhaddpd(Xmm xmm, const Operand& op1, const Operand& op2 = Operand()) { opAVX_X_X_XM(xmm, op1, op2, T_66|T_0F|T_YMM, 0x7C); }
void vhaddps(Xmm xmm, const Operand& op1, const Operand& op2 = Operand()) { opAVX_X_X_XM(xmm, op1, op2, T_F2|T_0F|T_YMM, 0x7C); }
void vhsubpd(Xmm xmm, const Operand& op1, const Operand& op2 = Operand()) { opAVX_X_X_XM(xmm, op1, op2, T_66|T_0F|T_YMM, 0x7D); }
void vhsubps(Xmm xmm, const Operand& op1, const Operand& op2 = Operand()) { opAVX_X_X_XM(xmm, op1, op2, T_F2|T_0F|T_YMM, 0x7D); }
void vinsertf128(Ymm y1, Ymm y2, const Operand& op, uint8_t imm) { if (!(y1.isYMM() && y2.isYMM() && op.isXMEM())) XBYAK_THROW(ERR_BAD_COMBINATION) opVex(y1, &y2, op, T_0F3A | T_66 | T_W0 | T_YMM, 0x18, imm); }
void vinserti128(Ymm y1, Ymm y2, const Operand& op, uint8_t imm) { if (!(y1.isYMM() && y2.isYMM() && op.isXMEM())) XBYAK_THROW(ERR_BAD_COMBINATION) opVex(y1, &y2, op, T_0F3A | T_66 | T_W0 | T_YMM, 0x38, imm); }
void vinsertps(Xmm x1, Xmm x2, const Operand& op, uint8_t imm) { opAVX_X_X_XM(x1, x2, op, T_N4|T_66|T_0F3A|T_W0|T_EVEX, 0x21, imm); }
void vlddqu(Xmm x, const Address& addr) { opAVX_X_X_XM(x, cvtIdx0(x), addr, T_0F | T_F2 | T_W0 | T_YMM, 0xF0); }
void vldmxcsr(const Address& addr) { opAVX_X_X_XM(xm2, xm0, addr, T_0F, 0xAE); }
void vmaskmovdqu(Xmm x1, Xmm x2) { opAVX_X_X_XM(x1, xm0, x2, T_0F | T_66, 0xF7); }
void vmaskmovpd(const Address& addr, Xmm x1, Xmm x2) { opAVX_X_X_XM(x2, x1, addr, T_0F38 | T_66 | T_W0 | T_YMM, 0x2F); }
void vmaskmovpd(Xmm x1, Xmm x2, const Address& addr) { opAVX_X_X_XM(x1, x2, addr, T_0F38 | T_66 | T_W0 | T_YMM, 0x2D); }
void vmaskmovps(const Address& addr, Xmm x1, Xmm x2) { opAVX_X_X_XM(x2, x1, addr, T_0F38 | T_66 | T_W0 | T_YMM, 0x2E); }
void vmaskmovps(Xmm x1, Xmm x2, const Address& addr) { opAVX_X_X_XM(x1, x2, addr, T_0F38 | T_66 | T_W0 | T_YMM, 0x2C); }
void vmaxpd(Xmm xmm, const Operand& op1, const Operand& op2 = Operand()) { opAVX_X_X_XM(xmm, op1, op2, T_0F | T_66 | T_EW1 | T_YMM | T_EVEX | T_SAE_Z | T_B64, 0x5F); }
void vmaxps(Xmm xmm, const Operand& op1, const Operand& op2 = Operand()) { opAVX_X_X_XM(xmm, op1, op2, T_0F | T_W0 | T_YMM | T_EVEX | T_SAE_Z | T_B32, 0x5F); }
void vmaxsd(Xmm xmm, const Operand& op1, const Operand& op2 = Operand()) { opAVX_X_X_XM(xmm, op1, op2, T_0F | T_F2 | T_EW1 | T_EVEX | T_SAE_X | T_N8, 0x5F); }
void vmaxss(Xmm xmm, const Operand& op1, const Operand& op2 = Operand()) { opAVX_X_X_XM(xmm, op1, op2, T_0F | T_F3 | T_W0 | T_EVEX | T_SAE_X | T_N4, 0x5F); }
void vminpd(Xmm xmm, const Operand& op1, const Operand& op2 = Operand()) { opAVX_X_X_XM(xmm, op1, op2, T_0F | T_66 | T_EW1 | T_YMM | T_EVEX | T_SAE_Z | T_B64, 0x5D); }
void vminps(Xmm xmm, const Operand& op1, const Operand& op2 = Operand()) { opAVX_X_X_XM(xmm, op1, op2, T_0F | T_W0 | T_YMM | T_EVEX | T_SAE_Z | T_B32, 0x5D); }
void vminsd(Xmm xmm, const Operand& op1, const Operand& op2 = Operand()) { opAVX_X_X_XM(xmm, op1, op2, T_0F | T_F2 | T_EW1 | T_EVEX | T_SAE_X | T_N8, 0x5D); }
void vminss(Xmm xmm, const Operand& op1, const Operand& op2 = Operand()) { opAVX_X_X_XM(xmm, op1, op2, T_0F | T_F3 | T_W0 | T_EVEX | T_SAE_X | T_N4, 0x5D); }
void vmovapd(const Address& addr, Xmm xmm) { opAVX_X_XM_IMM(xmm, addr, T_66|T_0F|T_EW1|T_YMM|T_EVEX|T_M_K, 0x29); }
void vmovapd(Xmm xm, const Operand& op) { opAVX_X_XM_IMM(xm, op, T_66|T_0F|T_EW1|T_YMM|T_EVEX, 0x28); }
void vmovaps(const Address& addr, Xmm xmm) { opAVX_X_XM_IMM(xmm, addr, T_0F|T_W0|T_YMM|T_EVEX|T_M_K, 0x29); }
void vmovaps(Xmm xm, const Operand& op) { opAVX_X_XM_IMM(xm, op, T_0F|T_W0|T_YMM|T_EVEX, 0x28); }
void vmovddup(Xmm xm, const Operand& op) { opAVX_X_XM_IMM(xm, op, T_DUP|T_F2|T_0F|T_EW1|T_YMM|T_EVEX, 0x12); }
void vmovdqa(const Address& addr, Xmm xmm) { opAVX_X_XM_IMM(xmm, addr, T_66|T_0F|T_YMM, 0x7F); }
void vmovdqa(Xmm xm, const Operand& op) { opAVX_X_XM_IMM(xm, op, T_66|T_0F|T_YMM, 0x6F); }
void vmovdqu(const Address& addr, Xmm xmm) { opAVX_X_XM_IMM(xmm, addr, T_F3|T_0F|T_YMM, 0x7F); }
void vmovdqu(Xmm xm, const Operand& op) { opAVX_X_XM_IMM(xm, op, T_F3|T_0F|T_YMM, 0x6F); }
void vmovhlps(Xmm x1, Xmm x2, const Operand& op = Operand()) { if (!op.isNone() && !op.isXMM()) XBYAK_THROW(ERR_BAD_COMBINATION) opAVX_X_X_XM(x1, x2, op, T_0F | T_EVEX | T_W0, 0x12); }
void vmovhpd(const Address& addr, Xmm x) { opAVX_X_X_XM(x, xm0, addr, T_N8|T_66|T_0F|T_EW1|T_EVEX, 0x17); }
void vmovhpd(Xmm x, const Operand& op1, const Operand& op2 = Operand()) { if (!op2.isNone() && !op2.isMEM()) XBYAK_THROW(ERR_BAD_COMBINATION) opAVX_X_X_XM(x, op1, op2, T_N8|T_66|T_0F|T_EW1|T_EVEX, 0x16); }
void vmovhps(const Address& addr, Xmm x) { opAVX_X_X_XM(x, xm0, addr, T_N8|T_0F|T_W0|T_EVEX, 0x17); }
void vmovhps(Xmm x, const Operand& op1, const Operand& op2 = Operand()) { if (!op2.isNone() && !op2.isMEM()) XBYAK_THROW(ERR_BAD_COMBINATION) opAVX_X_X_XM(x, op1, op2, T_N8|T_0F|T_W0|T_EVEX, 0x16); }
void vmovlhps(Xmm x1, Xmm x2, const Operand& op = Operand()) { if (!op.isNone() && !op.isXMM()) XBYAK_THROW(ERR_BAD_COMBINATION) opAVX_X_X_XM(x1, x2, op, T_0F | T_EVEX | T_W0, 0x16); }
void vmovlpd(const Address& addr, Xmm x) { opAVX_X_X_XM(x, xm0, addr, T_N8|T_66|T_0F|T_EW1|T_EVEX, 0x13); }
void vmovlpd(Xmm x, const Operand& op1, const Operand& op2 = Operand()) { if (!op2.isNone() && !op2.isMEM()) XBYAK_THROW(ERR_BAD_COMBINATION) opAVX_X_X_XM(x, op1, op2, T_N8|T_66|T_0F|T_EW1|T_EVEX, 0x12); }
void vmovlps(const Address& addr, Xmm x) { opAVX_X_X_XM(x, xm0, addr, T_N8|T_0F|T_W0|T_EVEX, 0x13); }
void vmovlps(Xmm x, const Operand& op1, const Operand& op2 = Operand()) { if (!op2.isNone() && !op2.isMEM()) XBYAK_THROW(ERR_BAD_COMBINATION) opAVX_X_X_XM(x, op1, op2, T_N8|T_0F|T_W0|T_EVEX, 0x12); }
void vmovmskpd(Reg r, Xmm x) { if (!r.isBit(i32e)) XBYAK_THROW(ERR_BAD_COMBINATION) opAVX_X_X_XM(x.isXMM() ? Xmm(r.getIdx()) : Ymm(r.getIdx()), cvtIdx0(x), x, T_0F | T_66 | T_W0 | T_YMM, 0x50); }
void vmovmskps(Reg r, Xmm x) { if (!r.isBit(i32e)) XBYAK_THROW(ERR_BAD_COMBINATION) opAVX_X_X_XM(x.isXMM() ? Xmm(r.getIdx()) : Ymm(r.getIdx()), cvtIdx0(x), x, T_0F | T_W0 | T_YMM, 0x50); }
void vmovntdq(const Address& addr, Xmm x) { opVex(x, 0, addr, T_0F | T_66 | T_YMM | T_EVEX | T_W0, 0xE7); }
void vmovntdqa(Xmm x, const Address& addr) { opVex(x, 0, addr, T_0F38 | T_66 | T_YMM | T_EVEX | T_W0, 0x2A); }
void vmovntpd(const Address& addr, Xmm x) { opVex(x, 0, addr, T_0F | T_66 | T_YMM | T_EVEX | T_EW1, 0x2B); }
void vmovntps(const Address& addr, Xmm x) { opVex(x, 0, addr, T_0F | T_YMM | T_EVEX | T_W0, 0x2B); }
void vmovq(const Address& addr, Xmm x) { opAVX_X_X_XM(x, xm0, addr, T_0F | T_66 | T_EVEX | T_EW1 | T_N8, x.getIdx() < 16 ? 0xD6 : 0x7E); }
void vmovq(Xmm x, const Address& addr) { uint64_t type; uint8_t code; if (x.getIdx() < 16) { type = T_0F | T_F3; code = 0x7E; } else { type = T_0F | T_66 | T_EVEX | T_EW1 | T_N8; code = 0x6E; } opAVX_X_X_XM(x, xm0, addr, type, code); }
void vmovq(Xmm x1, Xmm x2) { opAVX_X_X_XM(x1, xm0, x2, T_0F | T_F3 | T_EVEX | T_EW1 | T_N8, 0x7E); }
void vmovsd(const Address& addr, Xmm x) { opAVX_X_X_XM(x, xm0, addr, T_N8|T_F2|T_0F|T_EW1|T_EVEX | T_M_K, 0x11); }
void vmovsd(Xmm x, const Address& addr) { opAVX_X_X_XM(x, xm0, addr, T_N8|T_F2|T_0F|T_EW1|T_EVEX, 0x10); }
void vmovsd(Xmm x1, Xmm x2, const Operand& op = Operand()) { if (!op.isNone() && !op.isXMM()) XBYAK_THROW(ERR_BAD_COMBINATION) opAVX_X_X_XM(x1, x2, op, T_N8|T_F2|T_0F|T_EW1|T_EVEX, 0x10); }
void vmovshdup(Xmm xm, const Operand& op) { opAVX_X_XM_IMM(xm, op, T_F3|T_0F|T_W0|T_YMM|T_EVEX, 0x16); }
void vmovsldup(Xmm xm, const Operand& op) { opAVX_X_XM_IMM(xm, op, T_F3|T_0F|T_W0|T_YMM|T_EVEX, 0x12); }
void vmovss(const Address& addr, Xmm x) { opAVX_X_X_XM(x, xm0, addr, T_N4|T_F3|T_0F|T_W0|T_EVEX | T_M_K, 0x11); }
void vmovss(Xmm x, const Address& addr) { opAVX_X_X_XM(x, xm0, addr, T_N4|T_F3|T_0F|T_W0|T_EVEX, 0x10); }
void vmovss(Xmm x1, Xmm x2, const Operand& op = Operand()) { if (!op.isNone() && !op.isXMM()) XBYAK_THROW(ERR_BAD_COMBINATION) opAVX_X_X_XM(x1, x2, op, T_N4|T_F3|T_0F|T_W0|T_EVEX, 0x10); }
void vmovupd(const Address& addr, Xmm xmm) { opAVX_X_XM_IMM(xmm, addr, T_66|T_0F|T_EW1|T_YMM|T_EVEX|T_M_K, 0x11); }
void vmovupd(Xmm xm, const Operand& op) { opAVX_X_XM_IMM(xm, op, T_66|T_0F|T_EW1|T_YMM|T_EVEX, 0x10); }
void vmovups(const Address& addr, Xmm xmm) { opAVX_X_XM_IMM(xmm, addr, T_0F|T_W0|T_YMM|T_EVEX|T_M_K, 0x11); }
void vmovups(Xmm xm, const Operand& op) { opAVX_X_XM_IMM(xm, op, T_0F|T_W0|T_YMM|T_EVEX, 0x10); }
void vmulpd(Xmm xmm, const Operand& op1, const Operand& op2 = Operand()) { opAVX_X_X_XM(xmm, op1, op2, T_0F | T_66 | T_EW1 | T_YMM | T_EVEX | T_ER_Z | T_B64, 0x59); }
void vmulps(Xmm xmm, const Operand& op1, const Operand& op2 = Operand()) { opAVX_X_X_XM(xmm, op1, op2, T_0F | T_W0 | T_YMM | T_EVEX | T_ER_Z | T_B32, 0x59); }
void vmulsd(Xmm xmm, const Operand& op1, const Operand& op2 = Operand()) { opAVX_X_X_XM(xmm, op1, op2, T_0F | T_F2 | T_EW1 | T_EVEX | T_ER_X | T_N8, 0x59); }
void vmulss(Xmm xmm, const Operand& op1, const Operand& op2 = Operand()) { opAVX_X_X_XM(xmm, op1, op2, T_0F | T_F3 | T_W0 | T_EVEX | T_ER_X | T_N4, 0x59); }
void vorpd(Xmm xmm, const Operand& op1, const Operand& op2 = Operand()) { opAVX_X_X_XM(xmm, op1, op2, T_0F | T_66 | T_EW1 | T_YMM | T_EVEX | T_B64, 0x56); }
void vorps(Xmm xmm, const Operand& op1, const Operand& op2 = Operand()) { opAVX_X_X_XM(xmm, op1, op2, T_0F | T_W0 | T_YMM | T_EVEX | T_B32, 0x56); }
void vpabsb(Xmm xm, const Operand& op) { opAVX_X_XM_IMM(xm, op, T_66|T_0F38|T_YMM|T_EVEX, 0x1C); }
void vpabsd(Xmm xm, const Operand& op) { opAVX_X_XM_IMM(xm, op, T_66|T_0F38|T_W0|T_YMM|T_EVEX|T_B32, 0x1E); }
void vpabsw(Xmm xm, const Operand& op) { opAVX_X_XM_IMM(xm, op, T_66|T_0F38|T_YMM|T_EVEX, 0x1D); }
void vpackssdw(Xmm x1, Xmm x2, const Operand& op) { opAVX_X_X_XM(x1, x2, op, T_66|T_0F|T_W0|T_YMM|T_EVEX|T_B32, 0x6B); }
void vpacksswb(Xmm x1, Xmm x2, const Operand& op) { opAVX_X_X_XM(x1, x2, op, T_66|T_0F|T_YMM|T_EVEX, 0x63); }
void vpackusdw(Xmm x1, Xmm x2, const Operand& op) { opAVX_X_X_XM(x1, x2, op, T_66|T_0F38|T_W0|T_YMM|T_EVEX|T_B32, 0x2B); }
void vpackuswb(Xmm x1, Xmm x2, const Operand& op) { opAVX_X_X_XM(x1, x2, op, T_66|T_0F|T_YMM|T_EVEX, 0x67); }
void vpaddb(Xmm x1, Xmm x2, const Operand& op) { opAVX_X_X_XM(x1, x2, op, T_66|T_0F|T_YMM|T_EVEX, 0xFC); }
void vpaddd(Xmm x1, Xmm x2, const Operand& op) { opAVX_X_X_XM(x1, x2, op, T_66|T_0F|T_W0|T_YMM|T_EVEX|T_B32, 0xFE); }
void vpaddq(Xmm x1, Xmm x2, const Operand& op) { opAVX_X_X_XM(x1, x2, op, T_66|T_0F|T_EW1|T_YMM|T_EVEX|T_B64, 0xD4); }
void vpaddsb(Xmm x1, Xmm x2, const Operand& op) { opAVX_X_X_XM(x1, x2, op, T_66|T_0F|T_YMM|T_EVEX, 0xEC); }
void vpaddsw(Xmm x1, Xmm x2, const Operand& op) { opAVX_X_X_XM(x1, x2, op, T_66|T_0F|T_YMM|T_EVEX, 0xED); }
void vpaddusb(Xmm x1, Xmm x2, const Operand& op) { opAVX_X_X_XM(x1, x2, op, T_66|T_0F|T_YMM|T_EVEX, 0xDC); }
void vpaddusw(Xmm x1, Xmm x2, const Operand& op) { opAVX_X_X_XM(x1, x2, op, T_66|T_0F|T_YMM|T_EVEX, 0xDD); }
void vpaddw(Xmm x1, Xmm x2, const Operand& op) { opAVX_X_X_XM(x1, x2, op, T_66|T_0F|T_YMM|T_EVEX, 0xFD); }
void vpalignr(Xmm x1, Xmm x2, const Operand& op, uint8_t imm) { opAVX_X_X_XM(x1, x2, op, T_66|T_0F3A|T_YMM|T_EVEX, 0x0F, imm); }
void vpand(Xmm x1, Xmm x2, const Operand& op) { opAVX_X_X_XM(x1, x2, op, T_66|T_0F|T_YMM, 0xDB); }
void vpandn(Xmm x1, Xmm x2, const Operand& op) { opAVX_X_X_XM(x1, x2, op, T_66|T_0F|T_YMM, 0xDF); }
void vpavgb(Xmm x1, Xmm x2, const Operand& op) { opAVX_X_X_XM(x1, x2, op, T_66|T_0F|T_YMM|T_EVEX, 0xE0); }
void vpavgw(Xmm x1, Xmm x2, const Operand& op) { opAVX_X_X_XM(x1, x2, op, T_66|T_0F|T_YMM|T_EVEX, 0xE3); }
void vpblendd(Xmm x1, Xmm x2, const Operand& op, uint8_t imm) { opAVX_X_X_XM(x1, x2, op, T_66|T_0F3A|T_W0|T_YMM, 0x02, imm); }
void vpblendvb(Xmm x1, Xmm x2, const Operand& op, Xmm x4) { opAVX_X_X_XM(x1, x2, op, T_0F3A | T_66 | T_YMM, 0x4C, x4.getIdx() << 4); }
void vpblendw(Xmm x1, Xmm x2, const Operand& op, uint8_t imm) { opAVX_X_X_XM(x1, x2, op, T_66|T_0F3A|T_W0|T_YMM, 0x0E, imm); }
void vpbroadcastb(Xmm x, const Operand& op) { if (!(op.isXMM() || op.isMEM())) XBYAK_THROW(ERR_BAD_COMBINATION) opAVX_X_XM_IMM(x, op, T_N1|T_66|T_0F38|T_W0|T_YMM|T_EVEX, 0x78); }
void vpbroadcastd(Xmm x, const Operand& op) { if (!(op.isXMM() || op.isMEM())) XBYAK_THROW(ERR_BAD_COMBINATION) opAVX_X_XM_IMM(x, op, T_N4|T_66|T_0F38|T_W0|T_YMM|T_EVEX, 0x58); }
void vpbroadcastq(Xmm x, const Operand& op) { if (!(op.isXMM() || op.isMEM())) XBYAK_THROW(ERR_BAD_COMBINATION) opAVX_X_XM_IMM(x, op, T_N8|T_66|T_0F38|T_W0|T_EW1|T_YMM|T_EVEX, 0x59); }
void vpbroadcastw(Xmm x, const Operand& op) { if (!(op.isXMM() || op.isMEM())) XBYAK_THROW(ERR_BAD_COMBINATION) opAVX_X_XM_IMM(x, op, T_N2|T_66|T_0F38|T_W0|T_YMM|T_EVEX, 0x79); }
void vpclmulhqhqdq(Xmm x1, Xmm x2, const Operand& op) { vpclmulqdq(x1, x2, op, 0x11); }
void vpclmulhqlqdq(Xmm x1, Xmm x2, const Operand& op) { vpclmulqdq(x1, x2, op, 0x01); }
void vpclmullqhqdq(Xmm x1, Xmm x2, const Operand& op) { vpclmulqdq(x1, x2, op, 0x10); }
void vpclmullqlqdq(Xmm x1, Xmm x2, const Operand& op) { vpclmulqdq(x1, x2, op, 0x00); }
void vpclmulqdq(Xmm x1, Xmm x2, const Operand& op, uint8_t imm) { opAVX_X_X_XM(x1, x2, op, T_66|T_0F3A|T_W0|T_YMM|T_EVEX, 0x44, imm); }
void vpcmpeqb(Xmm x1, Xmm x2, const Operand& op) { opAVX_X_X_XM(x1, x2, op, T_66|T_0F|T_YMM, 0x74); }
void vpcmpeqd(Xmm x1, Xmm x2, const Operand& op) { opAVX_X_X_XM(x1, x2, op, T_66|T_0F|T_YMM, 0x76); }
void vpcmpeqq(Xmm x1, Xmm x2, const Operand& op) { opAVX_X_X_XM(x1, x2, op, T_66|T_0F38|T_YMM, 0x29); }
void vpcmpeqw(Xmm x1, Xmm x2, const Operand& op) { opAVX_X_X_XM(x1, x2, op, T_66|T_0F|T_YMM, 0x75); }
void vpcmpestri(Xmm xm, const Operand& op, uint8_t imm) { opAVX_X_XM_IMM(xm, op, T_66|T_0F3A, 0x61, imm); }
void vpcmpestrm(Xmm xm, const Operand& op, uint8_t imm) { opAVX_X_XM_IMM(xm, op, T_66|T_0F3A, 0x60, imm); }
void vpcmpgtb(Xmm x1, Xmm x2, const Operand& op) { opAVX_X_X_XM(x1, x2, op, T_66|T_0F|T_YMM, 0x64); }
void vpcmpgtd(Xmm x1, Xmm x2, const Operand& op) { opAVX_X_X_XM(x1, x2, op, T_66|T_0F|T_YMM, 0x66); }
void vpcmpgtq(Xmm x1, Xmm x2, const Operand& op) { opAVX_X_X_XM(x1, x2, op, T_66|T_0F38|T_YMM, 0x37); }
void vpcmpgtw(Xmm x1, Xmm x2, const Operand& op) { opAVX_X_X_XM(x1, x2, op, T_66|T_0F|T_YMM, 0x65); }
void vpcmpistri(Xmm xm, const Operand& op, uint8_t imm) { opAVX_X_XM_IMM(xm, op, T_66|T_0F3A, 0x63, imm); }
void vpcmpistrm(Xmm xm, const Operand& op, uint8_t imm) { opAVX_X_XM_IMM(xm, op, T_66|T_0F3A, 0x62, imm); }
void vpdpbusd(Xmm x1, Xmm x2, const Operand& op, PreferredEncoding encoding = DefaultEncoding) { opEncoding(x1, x2, op, T_66|T_0F38|T_W0|T_YMM|T_SAE_Z|T_B32, 0x50, encoding); }
void vpdpbusds(Xmm x1, Xmm x2, const Operand& op, PreferredEncoding encoding = DefaultEncoding) { opEncoding(x1, x2, op, T_66|T_0F38|T_W0|T_YMM|T_SAE_Z|T_B32, 0x51, encoding); }
void vpdpwssd(Xmm x1, Xmm x2, const Operand& op, PreferredEncoding encoding = DefaultEncoding) { opEncoding(x1, x2, op, T_66|T_0F38|T_W0|T_YMM|T_SAE_Z|T_B32, 0x52, encoding); }
void vpdpwssds(Xmm x1, Xmm x2, const Operand& op, PreferredEncoding encoding = DefaultEncoding) { opEncoding(x1, x2, op, T_66|T_0F38|T_W0|T_YMM|T_SAE_Z|T_B32, 0x53, encoding); }
void vperm2f128(Ymm y1, Ymm y2, const Operand& op, uint8_t imm) { if (!(y1.isYMM() && y2.isYMM() && op.isYMEM())) XBYAK_THROW(ERR_BAD_COMBINATION) opVex(y1, &y2, op, T_0F3A | T_66 | T_W0 | T_YMM, 0x06, imm); }
void vperm2i128(Ymm y1, Ymm y2, const Operand& op, uint8_t imm) { if (!(y1.isYMM() && y2.isYMM() && op.isYMEM())) XBYAK_THROW(ERR_BAD_COMBINATION) opVex(y1, &y2, op, T_0F3A | T_66 | T_W0 | T_YMM, 0x46, imm); }
void vpermd(Ymm y1, Ymm y2, const Operand& op) { opAVX_X_X_XM(y1, y2, op, T_66|T_0F38|T_W0|T_YMM|T_EVEX|T_B32, 0x36); }
void vpermilpd(Xmm x1, Xmm x2, const Operand& op) { opAVX_X_X_XM(x1, x2, op, T_66|T_0F38|T_W0|T_EW1|T_YMM|T_EVEX|T_B64, 0x0D); }
void vpermilpd(Xmm xm, const Operand& op, uint8_t imm) { opAVX_X_XM_IMM(xm, op, T_66|T_0F3A|T_EW1|T_YMM|T_EVEX|T_B64, 0x05, imm); }
void vpermilps(Xmm x1, Xmm x2, const Operand& op) { opAVX_X_X_XM(x1, x2, op, T_66|T_0F38|T_W0|T_YMM|T_EVEX|T_B32, 0x0C); }
void vpermilps(Xmm xm, const Operand& op, uint8_t imm) { opAVX_X_XM_IMM(xm, op, T_66|T_0F3A|T_W0|T_YMM|T_EVEX|T_B32, 0x04, imm); }
void vpermpd(Ymm y, const Operand& op, uint8_t imm) { opAVX_X_XM_IMM(y, op, T_66|T_0F3A|T_W1|T_EW1|T_YMM|T_EVEX|T_B64, 0x01, imm); }
void vpermpd(Ymm y1, Ymm y2, const Operand& op) { opAVX_X_X_XM(y1, y2, op, T_66|T_0F38|T_EW1|T_YMM|T_MUST_EVEX|T_B64, 0x16); }
void vpermps(Ymm y1, Ymm y2, const Operand& op) { opAVX_X_X_XM(y1, y2, op, T_66|T_0F38|T_W0|T_YMM|T_EVEX|T_B32, 0x16); }
void vpermq(Ymm y, const Operand& op, uint8_t imm) { opAVX_X_XM_IMM(y, op, T_66|T_0F3A|T_W1|T_EW1|T_YMM|T_EVEX|T_B64, 0x00, imm); }
void vpermq(Ymm y1, Ymm y2, const Operand& op) { opAVX_X_X_XM(y1, y2, op, T_66|T_0F38|T_EW1|T_YMM|T_EVEX|T_B64, 0x36); }
void vpextrb(const Operand& op, Xmm x, uint8_t imm) { if (!((op.isREG(8|16|i32e) || op.isMEM()) && x.isXMM())) XBYAK_THROW(ERR_BAD_COMBINATION) opVex(x, 0, op, T_0F3A | T_66 | T_EVEX | T_N1, 0x14, imm); }
void vpextrd(const Operand& op, Xmm x, uint8_t imm) { if (!((op.isREG(32) || op.isMEM()) && x.isXMM())) XBYAK_THROW(ERR_BAD_COMBINATION) opVex(x, 0, op, T_0F3A | T_66 | T_W0 | T_EVEX | T_N4, 0x16, imm); }
void vpextrq(const Operand& op, Xmm x, uint8_t imm) { if (!((op.isREG(64) || op.isMEM()) && x.isXMM())) XBYAK_THROW(ERR_BAD_COMBINATION) opVex(x, 0, op, T_0F3A | T_66 | T_W1 | T_EVEX | T_EW1 | T_N8, 0x16, imm); }
void vpextrw(const Operand& op, Xmm x, uint8_t imm) { if (!((op.isREG(16|i32e) || op.isMEM()) && x.isXMM())) XBYAK_THROW(ERR_BAD_COMBINATION) if (op.isREG() && x.getIdx() < 16) { opAVX_X_X_XM(Xmm(op.getIdx()), xm0, x, T_0F | T_66, 0xC5, imm); } else { opVex(x, 0, op, T_0F3A | T_66 | T_EVEX | T_N2, 0x15, imm); } }
void vpgatherdd(Xmm x1, const Address& addr, Xmm x2) { opGather(x1, addr, x2, T_0F38 | T_66 | T_YMM | T_VSIB | T_W0, 0x90, 1); }
void vpgatherdq(Xmm x1, const Address& addr, Xmm x2) { opGather(x1, addr, x2, T_0F38 | T_66 | T_YMM | T_VSIB | T_W1, 0x90, 0); }
void vpgatherqd(Xmm x1, const Address& addr, Xmm x2) { opGather(x1, addr, x2, T_0F38 | T_66 | T_YMM | T_VSIB | T_W0, 0x91, 2); }
void vpgatherqq(Xmm x1, const Address& addr, Xmm x2) { opGather(x1, addr, x2, T_0F38 | T_66 | T_YMM | T_VSIB | T_W1, 0x91, 1); }
void vphaddd(Xmm x1, Xmm x2, const Operand& op) { opAVX_X_X_XM(x1, x2, op, T_66|T_0F38|T_YMM, 0x02); }
void vphaddsw(Xmm x1, Xmm x2, const Operand& op) { opAVX_X_X_XM(x1, x2, op, T_66|T_0F38|T_YMM, 0x03); }
void vphaddw(Xmm x1, Xmm x2, const Operand& op) { opAVX_X_X_XM(x1, x2, op, T_66|T_0F38|T_YMM, 0x01); }
void vphminposuw(Xmm xm, const Operand& op) { opAVX_X_XM_IMM(xm, op, T_66|T_0F38, 0x41); }
void vphsubd(Xmm x1, Xmm x2, const Operand& op) { opAVX_X_X_XM(x1, x2, op, T_66|T_0F38|T_YMM, 0x06); }
void vphsubsw(Xmm x1, Xmm x2, const Operand& op) { opAVX_X_X_XM(x1, x2, op, T_66|T_0F38|T_YMM, 0x07); }
void vphsubw(Xmm x1, Xmm x2, const Operand& op) { opAVX_X_X_XM(x1, x2, op, T_66|T_0F38|T_YMM, 0x05); }
void vpinsrb(Xmm x1, Xmm x2, const Operand& op, uint8_t imm) { if (!(x1.isXMM() && x2.isXMM() && (op.isREG(32) || op.isMEM()))) XBYAK_THROW(ERR_BAD_COMBINATION) opVex(x1, &x2, op, T_0F3A | T_66 | T_EVEX | T_N1, 0x20, imm); }
void vpinsrd(Xmm x1, Xmm x2, const Operand& op, uint8_t imm) { if (!(x1.isXMM() && x2.isXMM() && (op.isREG(32) || op.isMEM()))) XBYAK_THROW(ERR_BAD_COMBINATION) opVex(x1, &x2, op, T_0F3A | T_66 | T_W0 | T_EVEX | T_N4, 0x22, imm); }
void vpinsrq(Xmm x1, Xmm x2, const Operand& op, uint8_t imm) { if (!(x1.isXMM() && x2.isXMM() && (op.isREG(64) || op.isMEM()))) XBYAK_THROW(ERR_BAD_COMBINATION) opVex(x1, &x2, op, T_0F3A | T_66 | T_W1 | T_EVEX | T_EW1 | T_N8, 0x22, imm); }
void vpinsrw(Xmm x1, Xmm x2, const Operand& op, uint8_t imm) { if (!(x1.isXMM() && x2.isXMM() && (op.isREG(32) || op.isMEM()))) XBYAK_THROW(ERR_BAD_COMBINATION) opVex(x1, &x2, op, T_0F | T_66 | T_EVEX | T_N2, 0xC4, imm); }
void vpmaddubsw(Xmm x1, Xmm x2, const Operand& op) { opAVX_X_X_XM(x1, x2, op, T_66|T_0F38|T_YMM|T_EVEX, 0x04); }
void vpmaddwd(Xmm x1, Xmm x2, const Operand& op) { opAVX_X_X_XM(x1, x2, op, T_66|T_0F|T_YMM|T_EVEX, 0xF5); }
void vpmaskmovd(const Address& addr, Xmm x1, Xmm x2) { opAVX_X_X_XM(x2, x1, addr, T_0F38 | T_66 | T_W0 | T_YMM, 0x8E); }
void vpmaskmovd(Xmm x1, Xmm x2, const Address& addr) { opAVX_X_X_XM(x1, x2, addr, T_0F38 | T_66 | T_W0 | T_YMM, 0x8C); }
void vpmaskmovq(const Address& addr, Xmm x1, Xmm x2) { opAVX_X_X_XM(x2, x1, addr, T_0F38 | T_66 | T_W1 | T_YMM, 0x8E); }
void vpmaskmovq(Xmm x1, Xmm x2, const Address& addr) { opAVX_X_X_XM(x1, x2, addr, T_0F38 | T_66 | T_W1 | T_YMM, 0x8C); }
void vpmaxsb(Xmm x1, Xmm x2, const Operand& op) { opAVX_X_X_XM(x1, x2, op, T_66|T_0F38|T_YMM|T_EVEX, 0x3C); }
void vpmaxsd(Xmm x1, Xmm x2, const Operand& op) { opAVX_X_X_XM(x1, x2, op, T_66|T_0F38|T_W0|T_YMM|T_EVEX|T_B32, 0x3D); }
void vpmaxsw(Xmm x1, Xmm x2, const Operand& op) { opAVX_X_X_XM(x1, x2, op, T_66|T_0F|T_YMM|T_EVEX, 0xEE); }
void vpmaxub(Xmm x1, Xmm x2, const Operand& op) { opAVX_X_X_XM(x1, x2, op, T_66|T_0F|T_YMM|T_EVEX, 0xDE); }
void vpmaxud(Xmm x1, Xmm x2, const Operand& op) { opAVX_X_X_XM(x1, x2, op, T_66|T_0F38|T_W0|T_YMM|T_EVEX|T_B32, 0x3F); }
void vpmaxuw(Xmm x1, Xmm x2, const Operand& op) { opAVX_X_X_XM(x1, x2, op, T_66|T_0F38|T_YMM|T_EVEX, 0x3E); }
void vpminsb(Xmm x1, Xmm x2, const Operand& op) { opAVX_X_X_XM(x1, x2, op, T_66|T_0F38|T_YMM|T_EVEX, 0x38); }
void vpminsd(Xmm x1, Xmm x2, const Operand& op) { opAVX_X_X_XM(x1, x2, op, T_66|T_0F38|T_W0|T_YMM|T_EVEX|T_B32, 0x39); }
void vpminsw(Xmm x1, Xmm x2, const Operand& op) { opAVX_X_X_XM(x1, x2, op, T_66|T_0F|T_YMM|T_EVEX, 0xEA); }
void vpminub(Xmm x1, Xmm x2, const Operand& op) { opAVX_X_X_XM(x1, x2, op, T_66|T_0F|T_YMM|T_EVEX, 0xDA); }
void vpminud(Xmm x1, Xmm x2, const Operand& op) { opAVX_X_X_XM(x1, x2, op, T_66|T_0F38|T_W0|T_YMM|T_EVEX|T_B32, 0x3B); }
void vpminuw(Xmm x1, Xmm x2, const Operand& op) { opAVX_X_X_XM(x1, x2, op, T_66|T_0F38|T_YMM|T_EVEX, 0x3A); }
void vpmovmskb(Reg32e r, Xmm x) { if (!x.is(Operand::XMM | Operand::YMM)) XBYAK_THROW(ERR_BAD_COMBINATION) opVex(x.isYMM() ? Ymm(r.getIdx()) : Xmm(r.getIdx()), 0, x, T_0F | T_66 | T_YMM, 0xD7); }
void vpmovsxbd(Xmm xm, const Operand& op) { opAVX_X_XM_IMM(xm, op, T_N4|T_N_VL|T_66|T_0F38|T_YMM|T_EVEX, 0x21); }
void vpmovsxbq(Xmm xm, const Operand& op) { opAVX_X_XM_IMM(xm, op, T_N2|T_N_VL|T_66|T_0F38|T_YMM|T_EVEX, 0x22); }
void vpmovsxbw(Xmm xm, const Operand& op) { opAVX_X_XM_IMM(xm, op, T_N8|T_N_VL|T_66|T_0F38|T_YMM|T_EVEX, 0x20); }
void vpmovsxdq(Xmm xm, const Operand& op) { opAVX_X_XM_IMM(xm, op, T_N8|T_N_VL|T_66|T_0F38|T_W0|T_YMM|T_EVEX, 0x25); }
void vpmovsxwd(Xmm xm, const Operand& op) { opAVX_X_XM_IMM(xm, op, T_N8|T_N_VL|T_66|T_0F38|T_YMM|T_EVEX, 0x23); }
void vpmovsxwq(Xmm xm, const Operand& op) { opAVX_X_XM_IMM(xm, op, T_N4|T_N_VL|T_66|T_0F38|T_YMM|T_EVEX, 0x24); }
void vpmovzxbd(Xmm xm, const Operand& op) { opAVX_X_XM_IMM(xm, op, T_N4|T_N_VL|T_66|T_0F38|T_YMM|T_EVEX, 0x31); }
void vpmovzxbq(Xmm xm, const Operand& op) { opAVX_X_XM_IMM(xm, op, T_N2|T_N_VL|T_66|T_0F38|T_YMM|T_EVEX, 0x32); }
void vpmovzxbw(Xmm xm, const Operand& op) { opAVX_X_XM_IMM(xm, op, T_N8|T_N_VL|T_66|T_0F38|T_YMM|T_EVEX, 0x30); }
void vpmovzxdq(Xmm xm, const Operand& op) { opAVX_X_XM_IMM(xm, op, T_N8|T_N_VL|T_66|T_0F38|T_W0|T_YMM|T_EVEX, 0x35); }
void vpmovzxwd(Xmm xm, const Operand& op) { opAVX_X_XM_IMM(xm, op, T_N8|T_N_VL|T_66|T_0F38|T_YMM|T_EVEX, 0x33); }
void vpmovzxwq(Xmm xm, const Operand& op) { opAVX_X_XM_IMM(xm, op, T_N4|T_N_VL|T_66|T_0F38|T_YMM|T_EVEX, 0x34); }
void vpmuldq(Xmm x1, Xmm x2, const Operand& op) { opAVX_X_X_XM(x1, x2, op, T_66|T_0F38|T_EW1|T_YMM|T_EVEX|T_B64, 0x28); }
void vpmulhrsw(Xmm x1, Xmm x2, const Operand& op) { opAVX_X_X_XM(x1, x2, op, T_66|T_0F38|T_YMM|T_EVEX, 0x0B); }
void vpmulhuw(Xmm x1, Xmm x2, const Operand& op) { opAVX_X_X_XM(x1, x2, op, T_66|T_0F|T_YMM|T_EVEX, 0xE4); }
void vpmulhw(Xmm x1, Xmm x2, const Operand& op) { opAVX_X_X_XM(x1, x2, op, T_66|T_0F|T_YMM|T_EVEX, 0xE5); }
void vpmulld(Xmm x1, Xmm x2, const Operand& op) { opAVX_X_X_XM(x1, x2, op, T_66|T_0F38|T_W0|T_YMM|T_EVEX|T_B32, 0x40); }
void vpmullw(Xmm x1, Xmm x2, const Operand& op) { opAVX_X_X_XM(x1, x2, op, T_66|T_0F|T_YMM|T_EVEX, 0xD5); }
void vpmuludq(Xmm x1, Xmm x2, const Operand& op) { opAVX_X_X_XM(x1, x2, op, T_66|T_0F|T_EW1|T_YMM|T_EVEX|T_B64, 0xF4); }
void vpor(Xmm x1, Xmm x2, const Operand& op) { opAVX_X_X_XM(x1, x2, op, T_66|T_0F|T_YMM, 0xEB); }
void vpsadbw(Xmm x1, Xmm x2, const Operand& op) { opAVX_X_X_XM(x1, x2, op, T_66|T_0F|T_YMM|T_EVEX, 0xF6); }
void vpshufb(Xmm x1, Xmm x2, const Operand& op) { opAVX_X_X_XM(x1, x2, op, T_66|T_0F38|T_YMM|T_EVEX, 0x00); }
void vpshufd(Xmm xm, const Operand& op, uint8_t imm) { opAVX_X_XM_IMM(xm, op, T_66|T_0F|T_W0|T_YMM|T_EVEX|T_B32, 0x70, imm); }
void vpshufhw(Xmm xm, const Operand& op, uint8_t imm) { opAVX_X_XM_IMM(xm, op, T_F3|T_0F|T_YMM|T_EVEX, 0x70, imm); }
void vpshuflw(Xmm xm, const Operand& op, uint8_t imm) { opAVX_X_XM_IMM(xm, op, T_F2|T_0F|T_YMM|T_EVEX, 0x70, imm); }
void vpsignb(Xmm x1, Xmm x2, const Operand& op) { opAVX_X_X_XM(x1, x2, op, T_66|T_0F38|T_YMM, 0x08); }
void vpsignd(Xmm x1, Xmm x2, const Operand& op) { opAVX_X_X_XM(x1, x2, op, T_66|T_0F38|T_YMM, 0x0A); }
void vpsignw(Xmm x1, Xmm x2, const Operand& op) { opAVX_X_X_XM(x1, x2, op, T_66|T_0F38|T_YMM, 0x09); }
void vpslld(Xmm x, const Operand& op, uint8_t imm) { opAVX_X_X_XM(Xmm(x.getKind(), 6), x, op, T_66|T_0F|T_W0|T_YMM|T_EVEX|T_B32|T_MEM_EVEX, 0x72, imm); }
void vpslld(Xmm x1, Xmm x2, const Operand& op) { opAVX_X_X_XM(x1, x2, op, T_N16|T_66|T_0F|T_W0|T_YMM|T_EVEX, 0xF2); }
void vpslldq(Xmm x, const Operand& op, uint8_t imm) { opAVX_X_X_XM(Xmm(x.getKind(), 7), x, op, T_66|T_0F|T_YMM|T_EVEX|T_MEM_EVEX, 0x73, imm); }
void vpsllq(Xmm x, const Operand& op, uint8_t imm) { opAVX_X_X_XM(Xmm(x.getKind(), 6), x, op, T_66|T_0F|T_EW1|T_YMM|T_EVEX|T_B64|T_MEM_EVEX, 0x73, imm); }
void vpsllq(Xmm x1, Xmm x2, const Operand& op) { opAVX_X_X_XM(x1, x2, op, T_N16|T_66|T_0F|T_EW1|T_YMM|T_EVEX, 0xF3); }
void vpsllvd(Xmm x1, Xmm x2, const Operand& op) { opAVX_X_X_XM(x1, x2, op, T_66|T_0F38|T_W0|T_YMM|T_EVEX|T_B32, 0x47); }
void vpsllvq(Xmm x1, Xmm x2, const Operand& op) { opAVX_X_X_XM(x1, x2, op, T_66|T_0F38|T_W1|T_EW1|T_YMM|T_EVEX|T_B64, 0x47); }
void vpsllw(Xmm x, const Operand& op, uint8_t imm) { opAVX_X_X_XM(Xmm(x.getKind(), 6), x, op, T_66|T_0F|T_YMM|T_EVEX|T_MEM_EVEX, 0x71, imm); }
void vpsllw(Xmm x1, Xmm x2, const Operand& op) { opAVX_X_X_XM(x1, x2, op, T_N16|T_66|T_0F|T_YMM|T_EVEX, 0xF1); }
void vpsrad(Xmm x, const Operand& op, uint8_t imm) { opAVX_X_X_XM(Xmm(x.getKind(), 4), x, op, T_66|T_0F|T_W0|T_YMM|T_EVEX|T_B32|T_MEM_EVEX, 0x72, imm); }
void vpsrad(Xmm x1, Xmm x2, const Operand& op) { opAVX_X_X_XM(x1, x2, op, T_N16|T_66|T_0F|T_W0|T_YMM|T_EVEX, 0xE2); }
void vpsravd(Xmm x1, Xmm x2, const Operand& op) { opAVX_X_X_XM(x1, x2, op, T_66|T_0F38|T_W0|T_YMM|T_EVEX|T_B32, 0x46); }
void vpsraw(Xmm x, const Operand& op, uint8_t imm) { opAVX_X_X_XM(Xmm(x.getKind(), 4), x, op, T_66|T_0F|T_YMM|T_EVEX|T_MEM_EVEX, 0x71, imm); }
void vpsraw(Xmm x1, Xmm x2, const Operand& op) { opAVX_X_X_XM(x1, x2, op, T_N16|T_66|T_0F|T_YMM|T_EVEX, 0xE1); }
void vpsrld(Xmm x, const Operand& op, uint8_t imm) { opAVX_X_X_XM(Xmm(x.getKind(), 2), x, op, T_66|T_0F|T_W0|T_YMM|T_EVEX|T_B32|T_MEM_EVEX, 0x72, imm); }
void vpsrld(Xmm x1, Xmm x2, const Operand& op) { opAVX_X_X_XM(x1, x2, op, T_N16|T_66|T_0F|T_W0|T_YMM|T_EVEX, 0xD2); }
void vpsrldq(Xmm x, const Operand& op, uint8_t imm) { opAVX_X_X_XM(Xmm(x.getKind(), 3), x, op, T_66|T_0F|T_YMM|T_EVEX|T_MEM_EVEX, 0x73, imm); }
void vpsrlq(Xmm x, const Operand& op, uint8_t imm) { opAVX_X_X_XM(Xmm(x.getKind(), 2), x, op, T_66|T_0F|T_EW1|T_YMM|T_EVEX|T_B64|T_MEM_EVEX, 0x73, imm); }
void vpsrlq(Xmm x1, Xmm x2, const Operand& op) { opAVX_X_X_XM(x1, x2, op, T_N16|T_66|T_0F|T_EW1|T_YMM|T_EVEX, 0xD3); }
void vpsrlvd(Xmm x1, Xmm x2, const Operand& op) { opAVX_X_X_XM(x1, x2, op, T_66|T_0F38|T_W0|T_YMM|T_EVEX|T_B32, 0x45); }
void vpsrlvq(Xmm x1, Xmm x2, const Operand& op) { opAVX_X_X_XM(x1, x2, op, T_66|T_0F38|T_W1|T_EW1|T_YMM|T_EVEX|T_B64, 0x45); }
void vpsrlw(Xmm x, const Operand& op, uint8_t imm) { opAVX_X_X_XM(Xmm(x.getKind(), 2), x, op, T_66|T_0F|T_YMM|T_EVEX|T_MEM_EVEX, 0x71, imm); }
void vpsrlw(Xmm x1, Xmm x2, const Operand& op) { opAVX_X_X_XM(x1, x2, op, T_N16|T_66|T_0F|T_YMM|T_EVEX, 0xD1); }
void vpsubb(Xmm x1, Xmm x2, const Operand& op) { opAVX_X_X_XM(x1, x2, op, T_66|T_0F|T_YMM|T_EVEX, 0xF8); }
void vpsubd(Xmm x1, Xmm x2, const Operand& op) { opAVX_X_X_XM(x1, x2, op, T_66|T_0F|T_W0|T_YMM|T_EVEX|T_B32, 0xFA); }
void vpsubq(Xmm x1, Xmm x2, const Operand& op) { opAVX_X_X_XM(x1, x2, op, T_66|T_0F|T_EW1|T_YMM|T_EVEX|T_B64, 0xFB); }
void vpsubsb(Xmm x1, Xmm x2, const Operand& op) { opAVX_X_X_XM(x1, x2, op, T_66|T_0F|T_YMM|T_EVEX, 0xE8); }
void vpsubsw(Xmm x1, Xmm x2, const Operand& op) { opAVX_X_X_XM(x1, x2, op, T_66|T_0F|T_YMM|T_EVEX, 0xE9); }
void vpsubusb(Xmm x1, Xmm x2, const Operand& op) { opAVX_X_X_XM(x1, x2, op, T_66|T_0F|T_YMM|T_EVEX, 0xD8); }
void vpsubusw(Xmm x1, Xmm x2, const Operand& op) { opAVX_X_X_XM(x1, x2, op, T_66|T_0F|T_YMM|T_EVEX, 0xD9); }
void vpsubw(Xmm x1, Xmm x2, const Operand& op) { opAVX_X_X_XM(x1, x2, op, T_66|T_0F|T_YMM|T_EVEX, 0xF9); }
void vptest(Xmm xm, const Operand& op) { opAVX_X_XM_IMM(xm, op, T_66|T_0F38|T_YMM, 0x17); }
void vpunpckhbw(Xmm x1, Xmm x2, const Operand& op) { opAVX_X_X_XM(x1, x2, op, T_66|T_0F|T_YMM|T_EVEX, 0x68); }
void vpunpckhdq(Xmm x1, Xmm x2, const Operand& op) { opAVX_X_X_XM(x1, x2, op, T_66|T_0F|T_W0|T_YMM|T_EVEX|T_B32, 0x6A); }
void vpunpckhqdq(Xmm x1, Xmm x2, const Operand& op) { opAVX_X_X_XM(x1, x2, op, T_66|T_0F|T_EW1|T_YMM|T_EVEX|T_B64, 0x6D); }
void vpunpckhwd(Xmm x1, Xmm x2, const Operand& op) { opAVX_X_X_XM(x1, x2, op, T_66|T_0F|T_YMM|T_EVEX, 0x69); }
void vpunpcklbw(Xmm x1, Xmm x2, const Operand& op) { opAVX_X_X_XM(x1, x2, op, T_66|T_0F|T_YMM|T_EVEX, 0x60); }
void vpunpckldq(Xmm x1, Xmm x2, const Operand& op) { opAVX_X_X_XM(x1, x2, op, T_66|T_0F|T_W0|T_YMM|T_EVEX|T_B32, 0x62); }
void vpunpcklqdq(Xmm x1, Xmm x2, const Operand& op) { opAVX_X_X_XM(x1, x2, op, T_66|T_0F|T_EW1|T_YMM|T_EVEX|T_B64, 0x6C); }
void vpunpcklwd(Xmm x1, Xmm x2, const Operand& op) { opAVX_X_X_XM(x1, x2, op, T_66|T_0F|T_YMM|T_EVEX, 0x61); }
void vpxor(Xmm x1, Xmm x2, const Operand& op) { opAVX_X_X_XM(x1, x2, op, T_66|T_0F|T_YMM, 0xEF); }
void vrcpps(Xmm xm, const Operand& op) { opAVX_X_XM_IMM(xm, op, T_0F|T_YMM, 0x53); }
void vrcpss(Xmm x1, Xmm x2, const Operand& op) { opAVX_X_X_XM(x1, x2, op, T_F3|T_0F, 0x53); }
void vroundpd(Xmm xm, const Operand& op, uint8_t imm) { opAVX_X_XM_IMM(xm, op, T_66|T_0F3A|T_YMM, 0x09, imm); }
void vroundps(Xmm xm, const Operand& op, uint8_t imm) { opAVX_X_XM_IMM(xm, op, T_66|T_0F3A|T_YMM, 0x08, imm); }
void vroundsd(Xmm x1, Xmm x2, const Operand& op, uint8_t imm) { opAVX_X_X_XM(x1, x2, op, T_66|T_0F3A|T_W0, 0x0B, imm); }
void vroundss(Xmm x1, Xmm x2, const Operand& op, uint8_t imm) { opAVX_X_X_XM(x1, x2, op, T_66|T_0F3A|T_W0, 0x0A, imm); }
void vrsqrtps(Xmm xm, const Operand& op) { opAVX_X_XM_IMM(xm, op, T_0F|T_YMM, 0x52); }
void vrsqrtss(Xmm x1, Xmm x2, const Operand& op) { opAVX_X_X_XM(x1, x2, op, T_F3|T_0F, 0x52); }
void vsha512msg1(Ymm y, Xmm x) { if (!(y.isYMM() && x.isXMM())) XBYAK_THROW(ERR_BAD_PARAMETER) opVex(y, 0, x, T_F2 | T_0F38 | T_W0 | T_YMM, 0xCC); }
void vsha512msg2(Ymm y1, Ymm y2) { if (!(y1.isYMM() && y2.isYMM())) XBYAK_THROW(ERR_BAD_PARAMETER) opVex(y1, 0, y2, T_F2 | T_0F38 | T_W0 | T_YMM, 0xCD); }
void vsha512rnds2(Ymm y1, Ymm y2, Xmm x) { if (!(y1.isYMM() && y2.isYMM() && x.isXMM())) XBYAK_THROW(ERR_BAD_PARAMETER) opVex(y1, &y2, x, T_F2 | T_0F38 | T_W0 | T_YMM, 0xCB); }
void vshufpd(Xmm x1, Xmm x2, const Operand& op, uint8_t imm) { opAVX_X_X_XM(x1, x2, op, T_66|T_0F|T_EW1|T_YMM|T_EVEX|T_B64, 0xC6, imm); }
void vshufps(Xmm x1, Xmm x2, const Operand& op, uint8_t imm) { opAVX_X_X_XM(x1, x2, op, T_0F|T_W0|T_YMM|T_EVEX|T_B32, 0xC6, imm); }
void vsm3msg1(Xmm x1, Xmm x2, const Operand& op) { opAVX_X_X_XM(x1, x2, op, T_0F38|T_W0|T_EVEX, 0xDA); }
void vsm3msg2(Xmm x1, Xmm x2, const Operand& op) { opAVX_X_X_XM(x1, x2, op, T_66|T_0F38|T_W0|T_EVEX, 0xDA); }
void vsm3rnds2(Xmm x1, Xmm x2, const Operand& op, uint8_t imm) { opAVX_X_X_XM(x1, x2, op, T_66|T_0F3A|T_W0|T_EVEX, 0xDE, imm); }
void vsm4key4(Xmm x1, Xmm x2, const Operand& op) { opAVX_X_X_XM(x1, x2, op, T_F3|T_0F38|T_W0|T_EVEX, 0xDA); }
void vsm4rnds4(Xmm x1, Xmm x2, const Operand& op) { opAVX_X_X_XM(x1, x2, op, T_F2|T_0F38|T_W0|T_EVEX, 0xDA); }
void vsqrtpd(Xmm xm, const Operand& op) { opAVX_X_XM_IMM(xm, op, T_66|T_0F|T_EW1|T_YMM|T_EVEX|T_ER_Z|T_B64, 0x51); }
void vsqrtps(Xmm xm, const Operand& op) { opAVX_X_XM_IMM(xm, op, T_0F|T_W0|T_YMM|T_EVEX|T_ER_Z|T_B32, 0x51); }
void vsqrtsd(Xmm x1, Xmm x2, const Operand& op) { opAVX_X_X_XM(x1, x2, op, T_N8|T_F2|T_0F|T_EW1|T_EVEX|T_ER_X, 0x51); }
void vsqrtss(Xmm x1, Xmm x2, const Operand& op) { opAVX_X_X_XM(x1, x2, op, T_N4|T_F3|T_0F|T_W0|T_EVEX|T_ER_X, 0x51); }
void vstmxcsr(const Address& addr) { opAVX_X_X_XM(xm3, xm0, addr, T_0F, 0xAE); }
void vsubpd(Xmm xmm, const Operand& op1, const Operand& op2 = Operand()) { opAVX_X_X_XM(xmm, op1, op2, T_0F | T_66 | T_EW1 | T_YMM | T_EVEX | T_ER_Z | T_B64, 0x5C); }
void vsubps(Xmm xmm, const Operand& op1, const Operand& op2 = Operand()) { opAVX_X_X_XM(xmm, op1, op2, T_0F | T_W0 | T_YMM | T_EVEX | T_ER_Z | T_B32, 0x5C); }
void vsubsd(Xmm xmm, const Operand& op1, const Operand& op2 = Operand()) { opAVX_X_X_XM(xmm, op1, op2, T_0F | T_F2 | T_EW1 | T_EVEX | T_ER_X | T_N8, 0x5C); }
void vsubss(Xmm xmm, const Operand& op1, const Operand& op2 = Operand()) { opAVX_X_X_XM(xmm, op1, op2, T_0F | T_F3 | T_W0 | T_EVEX | T_ER_X | T_N4, 0x5C); }
void vtestpd(Xmm xm, const Operand& op) { opAVX_X_XM_IMM(xm, op, T_66|T_0F38|T_YMM, 0x0F); }
void vtestps(Xmm xm, const Operand& op) { opAVX_X_XM_IMM(xm, op, T_66|T_0F38|T_YMM, 0x0E); }
void vucomisd(Xmm xm, const Operand& op) { opAVX_X_XM_IMM(xm, op, T_N8|T_66|T_0F|T_EW1|T_EVEX|T_SAE_X, 0x2E); }
void vucomiss(Xmm xm, const Operand& op) { opAVX_X_XM_IMM(xm, op, T_N4|T_0F|T_W0|T_EVEX|T_SAE_X, 0x2E); }
void vunpckhpd(Xmm x1, Xmm x2, const Operand& op) { opAVX_X_X_XM(x1, x2, op, T_66|T_0F|T_EW1|T_YMM|T_EVEX|T_B64, 0x15); }
void vunpckhps(Xmm x1, Xmm x2, const Operand& op) { opAVX_X_X_XM(x1, x2, op, T_0F|T_W0|T_YMM|T_EVEX|T_B32, 0x15); }
void vunpcklpd(Xmm x1, Xmm x2, const Operand& op) { opAVX_X_X_XM(x1, x2, op, T_66|T_0F|T_EW1|T_YMM|T_EVEX|T_B64, 0x14); }
void vunpcklps(Xmm x1, Xmm x2, const Operand& op) { opAVX_X_X_XM(x1, x2, op, T_0F|T_W0|T_YMM|T_EVEX|T_B32, 0x14); }
void vxorpd(Xmm xmm, const Operand& op1, const Operand& op2 = Operand()) { opAVX_X_X_XM(xmm, op1, op2, T_0F | T_66 | T_EW1 | T_YMM | T_EVEX | T_B64, 0x57); }
void vxorps(Xmm xmm, const Operand& op1, const Operand& op2 = Operand()) { opAVX_X_X_XM(xmm, op1, op2, T_0F | T_W0 | T_YMM | T_EVEX | T_B32, 0x57); }
void vzeroall() { db(0xC5); db(0xFC); db(0x77); }
void vzeroupper() { db(0xC5); db(0xF8); db(0x77); }
void wait() { db(0x9B); }
void wbinvd() { db(0x0F); db(0x09); }
void wrmsr() { db(0x0F); db(0x30); }
void xabort(uint8_t imm) { db(0xC6); db(0xF8); db(imm); }
void xadd(const Operand& op, Reg reg) { opRO(reg, op, T_0F, 0xC0 | (reg.isBit(8) ? 0 : 1), op.getBit() == reg.getBit()); }
void xbegin(uint32_t rel) { db(0xC7); db(0xF8); dd(rel); }
void xend() { db(0x0F); db(0x01); db(0xD5); }
void xgetbv() { db(0x0F); db(0x01); db(0xD0); }
void xlatb() { db(0xD7); }
void xor_(const Operand& op, uint32_t imm) { opOI(op, imm, 0x30, 6); }
void xor_(const Operand& op1, const Operand& op2) { opRO_MR(op1, op2, 0x30); }
void xor_(Reg d, const Operand& op, uint32_t imm) { opROI(d, op, imm, T_NF|T_CODE1_IF1, 6); }
void xor_(Reg d, const Operand& op1, const Operand& op2) { opROO(d, op1, op2, T_NF|T_CODE1_IF1, 0x30); }
void xorpd(Xmm xmm, const Operand& op) { opSSE(xmm, op, T_0F | T_66, 0x57, isXMM_XMMorMEM); }
void xorps(Xmm xmm, const Operand& op) { opSSE(xmm, op, T_0F, 0x57, isXMM_XMMorMEM); }
void xresldtrk() { db(0xF2); db(0x0F); db(0x01); db(0xE9); }
void xsusldtrk() { db(0xF2); db(0x0F); db(0x01); db(0xE8); }
#ifdef XBYAK_ENABLE_OMITTED_OPERAND
void vblendpd(Xmm x, const Operand& op, uint8_t imm) { vblendpd(x, x, op, imm); }
void vblendps(Xmm x, const Operand& op, uint8_t imm) { vblendps(x, x, op, imm); }
void vblendvpd(Xmm x1, const Operand& op, Xmm x4) { vblendvpd(x1, x1, op, x4); }
void vblendvps(Xmm x1, const Operand& op, Xmm x4) { vblendvps(x1, x1, op, x4); }
void vcmpeq_ospd(Xmm x, const Operand& op) { vcmpeq_ospd(x, x, op); }
void vcmpeq_osps(Xmm x, const Operand& op) { vcmpeq_osps(x, x, op); }
void vcmpeq_ossd(Xmm x, const Operand& op) { vcmpeq_ossd(x, x, op); }
void vcmpeq_osss(Xmm x, const Operand& op) { vcmpeq_osss(x, x, op); }
void vcmpeq_uqpd(Xmm x, const Operand& op) { vcmpeq_uqpd(x, x, op); }
void vcmpeq_uqps(Xmm x, const Operand& op) { vcmpeq_uqps(x, x, op); }
void vcmpeq_uqsd(Xmm x, const Operand& op) { vcmpeq_uqsd(x, x, op); }
void vcmpeq_uqss(Xmm x, const Operand& op) { vcmpeq_uqss(x, x, op); }
void vcmpeq_uspd(Xmm x, const Operand& op) { vcmpeq_uspd(x, x, op); }
void vcmpeq_usps(Xmm x, const Operand& op) { vcmpeq_usps(x, x, op); }
void vcmpeq_ussd(Xmm x, const Operand& op) { vcmpeq_ussd(x, x, op); }
void vcmpeq_usss(Xmm x, const Operand& op) { vcmpeq_usss(x, x, op); }
void vcmpeqpd(Xmm x, const Operand& op) { vcmpeqpd(x, x, op); }
void vcmpeqps(Xmm x, const Operand& op) { vcmpeqps(x, x, op); }
void vcmpeqsd(Xmm x, const Operand& op) { vcmpeqsd(x, x, op); }
void vcmpeqss(Xmm x, const Operand& op) { vcmpeqss(x, x, op); }
void vcmpfalse_ospd(Xmm x, const Operand& op) { vcmpfalse_ospd(x, x, op); }
void vcmpfalse_osps(Xmm x, const Operand& op) { vcmpfalse_osps(x, x, op); }
void vcmpfalse_ossd(Xmm x, const Operand& op) { vcmpfalse_ossd(x, x, op); }
void vcmpfalse_osss(Xmm x, const Operand& op) { vcmpfalse_osss(x, x, op); }
void vcmpfalsepd(Xmm x, const Operand& op) { vcmpfalsepd(x, x, op); }
void vcmpfalseps(Xmm x, const Operand& op) { vcmpfalseps(x, x, op); }
void vcmpfalsesd(Xmm x, const Operand& op) { vcmpfalsesd(x, x, op); }
void vcmpfalsess(Xmm x, const Operand& op) { vcmpfalsess(x, x, op); }
void vcmpge_oqpd(Xmm x, const Operand& op) { vcmpge_oqpd(x, x, op); }
void vcmpge_oqps(Xmm x, const Operand& op) { vcmpge_oqps(x, x, op); }
void vcmpge_oqsd(Xmm x, const Operand& op) { vcmpge_oqsd(x, x, op); }
void vcmpge_oqss(Xmm x, const Operand& op) { vcmpge_oqss(x, x, op); }
void vcmpgepd(Xmm x, const Operand& op) { vcmpgepd(x, x, op); }
void vcmpgeps(Xmm x, const Operand& op) { vcmpgeps(x, x, op); }
void vcmpgesd(Xmm x, const Operand& op) { vcmpgesd(x, x, op); }
void vcmpgess(Xmm x, const Operand& op) { vcmpgess(x, x, op); }
void vcmpgt_oqpd(Xmm x, const Operand& op) { vcmpgt_oqpd(x, x, op); }
void vcmpgt_oqps(Xmm x, const Operand& op) { vcmpgt_oqps(x, x, op); }
void vcmpgt_oqsd(Xmm x, const Operand& op) { vcmpgt_oqsd(x, x, op); }
void vcmpgt_oqss(Xmm x, const Operand& op) { vcmpgt_oqss(x, x, op); }
void vcmpgtpd(Xmm x, const Operand& op) { vcmpgtpd(x, x, op); }
void vcmpgtps(Xmm x, const Operand& op) { vcmpgtps(x, x, op); }
void vcmpgtsd(Xmm x, const Operand& op) { vcmpgtsd(x, x, op); }
void vcmpgtss(Xmm x, const Operand& op) { vcmpgtss(x, x, op); }
void vcmple_oqpd(Xmm x, const Operand& op) { vcmple_oqpd(x, x, op); }
void vcmple_oqps(Xmm x, const Operand& op) { vcmple_oqps(x, x, op); }
void vcmple_oqsd(Xmm x, const Operand& op) { vcmple_oqsd(x, x, op); }
void vcmple_oqss(Xmm x, const Operand& op) { vcmple_oqss(x, x, op); }
void vcmplepd(Xmm x, const Operand& op) { vcmplepd(x, x, op); }
void vcmpleps(Xmm x, const Operand& op) { vcmpleps(x, x, op); }
void vcmplesd(Xmm x, const Operand& op) { vcmplesd(x, x, op); }
void vcmpless(Xmm x, const Operand& op) { vcmpless(x, x, op); }
void vcmplt_oqpd(Xmm x, const Operand& op) { vcmplt_oqpd(x, x, op); }
void vcmplt_oqps(Xmm x, const Operand& op) { vcmplt_oqps(x, x, op); }
void vcmplt_oqsd(Xmm x, const Operand& op) { vcmplt_oqsd(x, x, op); }
void vcmplt_oqss(Xmm x, const Operand& op) { vcmplt_oqss(x, x, op); }
void vcmpltpd(Xmm x, const Operand& op) { vcmpltpd(x, x, op); }
void vcmpltps(Xmm x, const Operand& op) { vcmpltps(x, x, op); }
void vcmpltsd(Xmm x, const Operand& op) { vcmpltsd(x, x, op); }
void vcmpltss(Xmm x, const Operand& op) { vcmpltss(x, x, op); }
void vcmpneq_oqpd(Xmm x, const Operand& op) { vcmpneq_oqpd(x, x, op); }
void vcmpneq_oqps(Xmm x, const Operand& op) { vcmpneq_oqps(x, x, op); }
void vcmpneq_oqsd(Xmm x, const Operand& op) { vcmpneq_oqsd(x, x, op); }
void vcmpneq_oqss(Xmm x, const Operand& op) { vcmpneq_oqss(x, x, op); }
void vcmpneq_ospd(Xmm x, const Operand& op) { vcmpneq_ospd(x, x, op); }
void vcmpneq_osps(Xmm x, const Operand& op) { vcmpneq_osps(x, x, op); }
void vcmpneq_ossd(Xmm x, const Operand& op) { vcmpneq_ossd(x, x, op); }
void vcmpneq_osss(Xmm x, const Operand& op) { vcmpneq_osss(x, x, op); }
void vcmpneq_uspd(Xmm x, const Operand& op) { vcmpneq_uspd(x, x, op); }
void vcmpneq_usps(Xmm x, const Operand& op) { vcmpneq_usps(x, x, op); }
void vcmpneq_ussd(Xmm x, const Operand& op) { vcmpneq_ussd(x, x, op); }
void vcmpneq_usss(Xmm x, const Operand& op) { vcmpneq_usss(x, x, op); }
void vcmpneqpd(Xmm x, const Operand& op) { vcmpneqpd(x, x, op); }
void vcmpneqps(Xmm x, const Operand& op) { vcmpneqps(x, x, op); }
void vcmpneqsd(Xmm x, const Operand& op) { vcmpneqsd(x, x, op); }
void vcmpneqss(Xmm x, const Operand& op) { vcmpneqss(x, x, op); }
void vcmpnge_uqpd(Xmm x, const Operand& op) { vcmpnge_uqpd(x, x, op); }
void vcmpnge_uqps(Xmm x, const Operand& op) { vcmpnge_uqps(x, x, op); }
void vcmpnge_uqsd(Xmm x, const Operand& op) { vcmpnge_uqsd(x, x, op); }
void vcmpnge_uqss(Xmm x, const Operand& op) { vcmpnge_uqss(x, x, op); }
void vcmpngepd(Xmm x, const Operand& op) { vcmpngepd(x, x, op); }
void vcmpngeps(Xmm x, const Operand& op) { vcmpngeps(x, x, op); }
void vcmpngesd(Xmm x, const Operand& op) { vcmpngesd(x, x, op); }
void vcmpngess(Xmm x, const Operand& op) { vcmpngess(x, x, op); }
void vcmpngt_uqpd(Xmm x, const Operand& op) { vcmpngt_uqpd(x, x, op); }
void vcmpngt_uqps(Xmm x, const Operand& op) { vcmpngt_uqps(x, x, op); }
void vcmpngt_uqsd(Xmm x, const Operand& op) { vcmpngt_uqsd(x, x, op); }
void vcmpngt_uqss(Xmm x, const Operand& op) { vcmpngt_uqss(x, x, op); }
void vcmpngtpd(Xmm x, const Operand& op) { vcmpngtpd(x, x, op); }
void vcmpngtps(Xmm x, const Operand& op) { vcmpngtps(x, x, op); }
void vcmpngtsd(Xmm x, const Operand& op) { vcmpngtsd(x, x, op); }
void vcmpngtss(Xmm x, const Operand& op) { vcmpngtss(x, x, op); }
void vcmpnle_uqpd(Xmm x, const Operand& op) { vcmpnle_uqpd(x, x, op); }
void vcmpnle_uqps(Xmm x, const Operand& op) { vcmpnle_uqps(x, x, op); }
void vcmpnle_uqsd(Xmm x, const Operand& op) { vcmpnle_uqsd(x, x, op); }
void vcmpnle_uqss(Xmm x, const Operand& op) { vcmpnle_uqss(x, x, op); }
void vcmpnlepd(Xmm x, const Operand& op) { vcmpnlepd(x, x, op); }
void vcmpnleps(Xmm x, const Operand& op) { vcmpnleps(x, x, op); }
void vcmpnlesd(Xmm x, const Operand& op) { vcmpnlesd(x, x, op); }
void vcmpnless(Xmm x, const Operand& op) { vcmpnless(x, x, op); }
void vcmpnlt_uqpd(Xmm x, const Operand& op) { vcmpnlt_uqpd(x, x, op); }
void vcmpnlt_uqps(Xmm x, const Operand& op) { vcmpnlt_uqps(x, x, op); }
void vcmpnlt_uqsd(Xmm x, const Operand& op) { vcmpnlt_uqsd(x, x, op); }
void vcmpnlt_uqss(Xmm x, const Operand& op) { vcmpnlt_uqss(x, x, op); }
void vcmpnltpd(Xmm x, const Operand& op) { vcmpnltpd(x, x, op); }
void vcmpnltps(Xmm x, const Operand& op) { vcmpnltps(x, x, op); }
void vcmpnltsd(Xmm x, const Operand& op) { vcmpnltsd(x, x, op); }
void vcmpnltss(Xmm x, const Operand& op) { vcmpnltss(x, x, op); }
void vcmpord_spd(Xmm x, const Operand& op) { vcmpord_spd(x, x, op); }
void vcmpord_sps(Xmm x, const Operand& op) { vcmpord_sps(x, x, op); }
void vcmpord_ssd(Xmm x, const Operand& op) { vcmpord_ssd(x, x, op); }
void vcmpord_sss(Xmm x, const Operand& op) { vcmpord_sss(x, x, op); }
void vcmpordpd(Xmm x, const Operand& op) { vcmpordpd(x, x, op); }
void vcmpordps(Xmm x, const Operand& op) { vcmpordps(x, x, op); }
void vcmpordsd(Xmm x, const Operand& op) { vcmpordsd(x, x, op); }
void vcmpordss(Xmm x, const Operand& op) { vcmpordss(x, x, op); }
void vcmppd(Xmm x, const Operand& op, uint8_t imm) { vcmppd(x, x, op, imm); }
void vcmpps(Xmm x, const Operand& op, uint8_t imm) { vcmpps(x, x, op, imm); }
void vcmpsd(Xmm x, const Operand& op, uint8_t imm) { vcmpsd(x, x, op, imm); }
void vcmpss(Xmm x, const Operand& op, uint8_t imm) { vcmpss(x, x, op, imm); }
void vcmptrue_uspd(Xmm x, const Operand& op) { vcmptrue_uspd(x, x, op); }
void vcmptrue_usps(Xmm x, const Operand& op) { vcmptrue_usps(x, x, op); }
void vcmptrue_ussd(Xmm x, const Operand& op) { vcmptrue_ussd(x, x, op); }
void vcmptrue_usss(Xmm x, const Operand& op) { vcmptrue_usss(x, x, op); }
void vcmptruepd(Xmm x, const Operand& op) { vcmptruepd(x, x, op); }
void vcmptrueps(Xmm x, const Operand& op) { vcmptrueps(x, x, op); }
void vcmptruesd(Xmm x, const Operand& op) { vcmptruesd(x, x, op); }
void vcmptruess(Xmm x, const Operand& op) { vcmptruess(x, x, op); }
void vcmpunord_spd(Xmm x, const Operand& op) { vcmpunord_spd(x, x, op); }
void vcmpunord_sps(Xmm x, const Operand& op) { vcmpunord_sps(x, x, op); }
void vcmpunord_ssd(Xmm x, const Operand& op) { vcmpunord_ssd(x, x, op); }
void vcmpunord_sss(Xmm x, const Operand& op) { vcmpunord_sss(x, x, op); }
void vcmpunordpd(Xmm x, const Operand& op) { vcmpunordpd(x, x, op); }
void vcmpunordps(Xmm x, const Operand& op) { vcmpunordps(x, x, op); }
void vcmpunordsd(Xmm x, const Operand& op) { vcmpunordsd(x, x, op); }
void vcmpunordss(Xmm x, const Operand& op) { vcmpunordss(x, x, op); }
void vcvtsd2ss(Xmm x, const Operand& op) { vcvtsd2ss(x, x, op); }
void vcvtsi2sd(Xmm x, const Operand& op) { vcvtsi2sd(x, x, op); }
void vcvtsi2ss(Xmm x, const Operand& op) { vcvtsi2ss(x, x, op); }
void vcvtss2sd(Xmm x, const Operand& op) { vcvtss2sd(x, x, op); }
void vdppd(Xmm x, const Operand& op, uint8_t imm) { vdppd(x, x, op, imm); }
void vdpps(Xmm x, const Operand& op, uint8_t imm) { vdpps(x, x, op, imm); }
void vinsertps(Xmm x, const Operand& op, uint8_t imm) { vinsertps(x, x, op, imm); }
void vmpsadbw(Xmm x, const Operand& op, uint8_t imm) { vmpsadbw(x, x, op, imm); }
void vpackssdw(Xmm x, const Operand& op) { vpackssdw(x, x, op); }
void vpacksswb(Xmm x, const Operand& op) { vpacksswb(x, x, op); }
void vpackusdw(Xmm x, const Operand& op) { vpackusdw(x, x, op); }
void vpackuswb(Xmm x, const Operand& op) { vpackuswb(x, x, op); }
void vpaddb(Xmm x, const Operand& op) { vpaddb(x, x, op); }
void vpaddd(Xmm x, const Operand& op) { vpaddd(x, x, op); }
void vpaddq(Xmm x, const Operand& op) { vpaddq(x, x, op); }
void vpaddsb(Xmm x, const Operand& op) { vpaddsb(x, x, op); }
void vpaddsw(Xmm x, const Operand& op) { vpaddsw(x, x, op); }
void vpaddusb(Xmm x, const Operand& op) { vpaddusb(x, x, op); }
void vpaddusw(Xmm x, const Operand& op) { vpaddusw(x, x, op); }
void vpaddw(Xmm x, const Operand& op) { vpaddw(x, x, op); }
void vpalignr(Xmm x, const Operand& op, uint8_t imm) { vpalignr(x, x, op, imm); }
void vpand(Xmm x, const Operand& op) { vpand(x, x, op); }
void vpandn(Xmm x, const Operand& op) { vpandn(x, x, op); }
void vpavgb(Xmm x, const Operand& op) { vpavgb(x, x, op); }
void vpavgw(Xmm x, const Operand& op) { vpavgw(x, x, op); }
void vpblendd(Xmm x, const Operand& op, uint8_t imm) { vpblendd(x, x, op, imm); }
void vpblendvb(Xmm x1, const Operand& op, Xmm x4) { vpblendvb(x1, x1, op, x4); }
void vpblendw(Xmm x, const Operand& op, uint8_t imm) { vpblendw(x, x, op, imm); }
void vpclmulqdq(Xmm x, const Operand& op, uint8_t imm) { vpclmulqdq(x, x, op, imm); }
void vpcmpeqb(Xmm x, const Operand& op) { vpcmpeqb(x, x, op); }
void vpcmpeqd(Xmm x, const Operand& op) { vpcmpeqd(x, x, op); }
void vpcmpeqq(Xmm x, const Operand& op) { vpcmpeqq(x, x, op); }
void vpcmpeqw(Xmm x, const Operand& op) { vpcmpeqw(x, x, op); }
void vpcmpgtb(Xmm x, const Operand& op) { vpcmpgtb(x, x, op); }
void vpcmpgtd(Xmm x, const Operand& op) { vpcmpgtd(x, x, op); }
void vpcmpgtq(Xmm x, const Operand& op) { vpcmpgtq(x, x, op); }
void vpcmpgtw(Xmm x, const Operand& op) { vpcmpgtw(x, x, op); }
void vphaddd(Xmm x, const Operand& op) { vphaddd(x, x, op); }
void vphaddsw(Xmm x, const Operand& op) { vphaddsw(x, x, op); }
void vphaddw(Xmm x, const Operand& op) { vphaddw(x, x, op); }
void vphsubd(Xmm x, const Operand& op) { vphsubd(x, x, op); }
void vphsubsw(Xmm x, const Operand& op) { vphsubsw(x, x, op); }
void vphsubw(Xmm x, const Operand& op) { vphsubw(x, x, op); }
void vpinsrb(Xmm x, const Operand& op, uint8_t imm) { vpinsrb(x, x, op, imm); }
void vpinsrd(Xmm x, const Operand& op, uint8_t imm) { vpinsrd(x, x, op, imm); }
void vpinsrq(Xmm x, const Operand& op, uint8_t imm) { vpinsrq(x, x, op, imm); }
void vpinsrw(Xmm x, const Operand& op, uint8_t imm) { vpinsrw(x, x, op, imm); }
void vpmaddubsw(Xmm x, const Operand& op) { vpmaddubsw(x, x, op); }
void vpmaddwd(Xmm x, const Operand& op) { vpmaddwd(x, x, op); }
void vpmaxsb(Xmm x, const Operand& op) { vpmaxsb(x, x, op); }
void vpmaxsd(Xmm x, const Operand& op) { vpmaxsd(x, x, op); }
void vpmaxsw(Xmm x, const Operand& op) { vpmaxsw(x, x, op); }
void vpmaxub(Xmm x, const Operand& op) { vpmaxub(x, x, op); }
void vpmaxud(Xmm x, const Operand& op) { vpmaxud(x, x, op); }
void vpmaxuw(Xmm x, const Operand& op) { vpmaxuw(x, x, op); }
void vpminsb(Xmm x, const Operand& op) { vpminsb(x, x, op); }
void vpminsd(Xmm x, const Operand& op) { vpminsd(x, x, op); }
void vpminsw(Xmm x, const Operand& op) { vpminsw(x, x, op); }
void vpminub(Xmm x, const Operand& op) { vpminub(x, x, op); }
void vpminud(Xmm x, const Operand& op) { vpminud(x, x, op); }
void vpminuw(Xmm x, const Operand& op) { vpminuw(x, x, op); }
void vpmuldq(Xmm x, const Operand& op) { vpmuldq(x, x, op); }
void vpmulhrsw(Xmm x, const Operand& op) { vpmulhrsw(x, x, op); }
void vpmulhuw(Xmm x, const Operand& op) { vpmulhuw(x, x, op); }
void vpmulhw(Xmm x, const Operand& op) { vpmulhw(x, x, op); }
void vpmulld(Xmm x, const Operand& op) { vpmulld(x, x, op); }
void vpmullw(Xmm x, const Operand& op) { vpmullw(x, x, op); }
void vpmuludq(Xmm x, const Operand& op) { vpmuludq(x, x, op); }
void vpor(Xmm x, const Operand& op) { vpor(x, x, op); }
void vpsadbw(Xmm x, const Operand& op) { vpsadbw(x, x, op); }
void vpsignb(Xmm x, const Operand& op) { vpsignb(x, x, op); }
void vpsignd(Xmm x, const Operand& op) { vpsignd(x, x, op); }
void vpsignw(Xmm x, const Operand& op) { vpsignw(x, x, op); }
void vpslld(Xmm x, const Operand& op) { vpslld(x, x, op); }
void vpslld(Xmm x, uint8_t imm) { vpslld(x, x, imm); }
void vpslldq(Xmm x, uint8_t imm) { vpslldq(x, x, imm); }
void vpsllq(Xmm x, const Operand& op) { vpsllq(x, x, op); }
void vpsllq(Xmm x, uint8_t imm) { vpsllq(x, x, imm); }
void vpsllw(Xmm x, const Operand& op) { vpsllw(x, x, op); }
void vpsllw(Xmm x, uint8_t imm) { vpsllw(x, x, imm); }
void vpsrad(Xmm x, const Operand& op) { vpsrad(x, x, op); }
void vpsrad(Xmm x, uint8_t imm) { vpsrad(x, x, imm); }
void vpsraw(Xmm x, const Operand& op) { vpsraw(x, x, op); }
void vpsraw(Xmm x, uint8_t imm) { vpsraw(x, x, imm); }
void vpsrld(Xmm x, const Operand& op) { vpsrld(x, x, op); }
void vpsrld(Xmm x, uint8_t imm) { vpsrld(x, x, imm); }
void vpsrldq(Xmm x, uint8_t imm) { vpsrldq(x, x, imm); }
void vpsrlq(Xmm x, const Operand& op) { vpsrlq(x, x, op); }
void vpsrlq(Xmm x, uint8_t imm) { vpsrlq(x, x, imm); }
void vpsrlw(Xmm x, const Operand& op) { vpsrlw(x, x, op); }
void vpsrlw(Xmm x, uint8_t imm) { vpsrlw(x, x, imm); }
void vpsubb(Xmm x, const Operand& op) { vpsubb(x, x, op); }
void vpsubd(Xmm x, const Operand& op) { vpsubd(x, x, op); }
void vpsubq(Xmm x, const Operand& op) { vpsubq(x, x, op); }
void vpsubsb(Xmm x, const Operand& op) { vpsubsb(x, x, op); }
void vpsubsw(Xmm x, const Operand& op) { vpsubsw(x, x, op); }
void vpsubusb(Xmm x, const Operand& op) { vpsubusb(x, x, op); }
void vpsubusw(Xmm x, const Operand& op) { vpsubusw(x, x, op); }
void vpsubw(Xmm x, const Operand& op) { vpsubw(x, x, op); }
void vpunpckhbw(Xmm x, const Operand& op) { vpunpckhbw(x, x, op); }
void vpunpckhdq(Xmm x, const Operand& op) { vpunpckhdq(x, x, op); }
void vpunpckhqdq(Xmm x, const Operand& op) { vpunpckhqdq(x, x, op); }
void vpunpckhwd(Xmm x, const Operand& op) { vpunpckhwd(x, x, op); }
void vpunpcklbw(Xmm x, const Operand& op) { vpunpcklbw(x, x, op); }
void vpunpckldq(Xmm x, const Operand& op) { vpunpckldq(x, x, op); }
void vpunpcklqdq(Xmm x, const Operand& op) { vpunpcklqdq(x, x, op); }
void vpunpcklwd(Xmm x, const Operand& op) { vpunpcklwd(x, x, op); }
void vpxor(Xmm x, const Operand& op) { vpxor(x, x, op); }
void vrcpss(Xmm x, const Operand& op) { vrcpss(x, x, op); }
void vroundsd(Xmm x, const Operand& op, uint8_t imm) { vroundsd(x, x, op, imm); }
void vroundss(Xmm x, const Operand& op, uint8_t imm) { vroundss(x, x, op, imm); }
void vrsqrtss(Xmm x, const Operand& op) { vrsqrtss(x, x, op); }
void vshufpd(Xmm x, const Operand& op, uint8_t imm) { vshufpd(x, x, op, imm); }
void vshufps(Xmm x, const Operand& op, uint8_t imm) { vshufps(x, x, op, imm); }
void vsqrtsd(Xmm x, const Operand& op) { vsqrtsd(x, x, op); }
void vsqrtss(Xmm x, const Operand& op) { vsqrtss(x, x, op); }
void vunpckhpd(Xmm x, const Operand& op) { vunpckhpd(x, x, op); }
void vunpckhps(Xmm x, const Operand& op) { vunpckhps(x, x, op); }
void vunpcklpd(Xmm x, const Operand& op) { vunpcklpd(x, x, op); }
void vunpcklps(Xmm x, const Operand& op) { vunpcklps(x, x, op); }
#endif
#ifdef XBYAK64
void jecxz(std::string label) { db(0x67); opJmp(label, T_SHORT, 0xe3, 0, 0); }
void jecxz(const Label& label) { db(0x67); opJmp(label, T_SHORT, 0xe3, 0, 0); }
void jrcxz(std::string label) { opJmp(label, T_SHORT, 0xe3, 0, 0); }
void jrcxz(const Label& label) { opJmp(label, T_SHORT, 0xe3, 0, 0); }
void cdqe() { db(0x48); db(0x98); }
void cqo() { db(0x48); db(0x99); }
void cmpsq() { db(0x48); db(0xA7); }
void popfq() { db(0x9D); }
void pushfq() { db(0x9C); }
void lodsq() { db(0x48); db(0xAD); }
void movsq() { db(0x48); db(0xA5); }
void scasq() { db(0x48); db(0xAF); }
void stosq() { db(0x48); db(0xAB); }
void syscall() { db(0x0F); db(0x05); }
void sysret() { db(0x0F); db(0x07); }
void clui() { db(0xF3); db(0x0F); db(0x01); db(0xEE); }
void stui() { db(0xF3); db(0x0F); db(0x01); db(0xEF); }
void testui() { db(0xF3); db(0x0F); db(0x01); db(0xED); }
void uiret() { db(0xF3); db(0x0F); db(0x01); db(0xEC); }
void cmpxchg16b(const Address& addr) { opMR(addr, Reg64(1), T_0F|T_ALLOW_DIFF_SIZE, 0xC7); }
void fxrstor64(const Address& addr) { opMR(addr, Reg64(1), T_0F, 0xAE); }
void movq(Reg64 reg, Mmx mmx) { if (mmx.isXMM()) db(0x66); opSSE(mmx, reg, T_0F, 0x7E); }
void movq(Mmx mmx, Reg64 reg) { if (mmx.isXMM()) db(0x66); opSSE(mmx, reg, T_0F, 0x6E); }
void movrs(Reg reg, const Address& addr) { opMR(addr, reg, T_0F38, reg.isBit(8) ? 0x8A : 0x8B); }
void movsxd(Reg64 reg, const Operand& op) { if (!op.isBit(32)) XBYAK_THROW(ERR_BAD_COMBINATION) opRO(reg, op, T_ALLOW_DIFF_SIZE, 0x63); }
void pextrq(const Operand& op, Xmm xmm, uint8_t imm) { if (!op.isREG(64) && !op.isMEM()) XBYAK_THROW(ERR_BAD_COMBINATION) opSSE(Reg64(xmm.getIdx()), op, T_66 | T_0F3A, 0x16, 0, imm); }
void pinsrq(Xmm xmm, const Operand& op, uint8_t imm) { if (!op.isREG(64) && !op.isMEM()) XBYAK_THROW(ERR_BAD_COMBINATION) opSSE(Reg64(xmm.getIdx()), op, T_66 | T_0F3A, 0x22, 0, imm); }
void senduipi(Reg64 r) { opRR(Reg32(6), r.cvt32(), T_F3 | T_0F, 0xC7); }
void vcvtss2si(Reg64 r, const Operand& op) { opAVX_X_X_XM(Xmm(r.getIdx()), xm0, op, T_0F | T_F3 | T_W1 | T_EVEX | T_EW1 | T_ER_X | T_N8, 0x2D); }
void vcvttss2si(Reg64 r, const Operand& op) { opAVX_X_X_XM(Xmm(r.getIdx()), xm0, op, T_0F | T_F3 | T_W1 | T_EVEX | T_EW1 | T_SAE_X | T_N8, 0x2C); }
void vcvtsd2si(Reg64 r, const Operand& op) { opAVX_X_X_XM(Xmm(r.getIdx()), xm0, op, T_0F | T_F2 | T_W1 | T_EVEX | T_EW1 | T_N4 | T_ER_X, 0x2D); }
void vcvttsd2si(Reg64 r, const Operand& op) { opAVX_X_X_XM(Xmm(r.getIdx()), xm0, op, T_0F | T_F2 | T_W1 | T_EVEX | T_EW1 | T_N4 | T_SAE_X, 0x2C); }
void vmovq(Xmm x, Reg64 r) { opAVX_X_X_XM(x, xm0, Xmm(r.getIdx()), T_66 | T_0F | T_W1 | T_EVEX | T_EW1, 0x6E); }
void vmovq(Reg64 r, Xmm x) { opAVX_X_X_XM(x, xm0, Xmm(r.getIdx()), T_66 | T_0F | T_W1 | T_EVEX | T_EW1, 0x7E); }
void jmpabs(uint64_t addr) { db(0xD5); db(0x00); db(0xA1); dq(addr); }
void push2(Reg64 r1, Reg64 r2) { opROO(r1, r2, Reg64(6), T_APX|T_ND1|T_W0, 0xFF); }
void push2p(Reg64 r1, Reg64 r2) { opROO(r1, r2, Reg64(6), T_APX|T_ND1|T_W1, 0xFF); }
void pop2(Reg64 r1, Reg64 r2) { opROO(r1, r2, Reg64(0), T_APX|T_ND1|T_W0, 0x8F); }
void pop2p(Reg64 r1, Reg64 r2) { opROO(r1, r2, Reg64(0), T_APX|T_ND1|T_W1, 0x8F); }
void cmpbexadd(const Address& addr, Reg32e r1, Reg32e r2) { opRRO(r1, r2, addr, T_APX|T_66|T_0F38, 0xE6); }
void cmpbxadd(const Address& addr, Reg32e r1, Reg32e r2) { opRRO(r1, r2, addr, T_APX|T_66|T_0F38, 0xE2); }
void cmplexadd(const Address& addr, Reg32e r1, Reg32e r2) { opRRO(r1, r2, addr, T_APX|T_66|T_0F38, 0xEE); }
void cmplxadd(const Address& addr, Reg32e r1, Reg32e r2) { opRRO(r1, r2, addr, T_APX|T_66|T_0F38, 0xEC); }
void cmpnbexadd(const Address& addr, Reg32e r1, Reg32e r2) { opRRO(r1, r2, addr, T_APX|T_66|T_0F38, 0xE7); }
void cmpnbxadd(const Address& addr, Reg32e r1, Reg32e r2) { opRRO(r1, r2, addr, T_APX|T_66|T_0F38, 0xE3); }
void cmpnlexadd(const Address& addr, Reg32e r1, Reg32e r2) { opRRO(r1, r2, addr, T_APX|T_66|T_0F38, 0xEF); }
void cmpnlxadd(const Address& addr, Reg32e r1, Reg32e r2) { opRRO(r1, r2, addr, T_APX|T_66|T_0F38, 0xED); }
void cmpnoxadd(const Address& addr, Reg32e r1, Reg32e r2) { opRRO(r1, r2, addr, T_APX|T_66|T_0F38, 0xE1); }
void cmpnpxadd(const Address& addr, Reg32e r1, Reg32e r2) { opRRO(r1, r2, addr, T_APX|T_66|T_0F38, 0xEB); }
void cmpnsxadd(const Address& addr, Reg32e r1, Reg32e r2) { opRRO(r1, r2, addr, T_APX|T_66|T_0F38, 0xE9); }
void cmpnzxadd(const Address& addr, Reg32e r1, Reg32e r2) { opRRO(r1, r2, addr, T_APX|T_66|T_0F38, 0xE5); }
void cmpoxadd(const Address& addr, Reg32e r1, Reg32e r2) { opRRO(r1, r2, addr, T_APX|T_66|T_0F38, 0xE0); }
void cmppxadd(const Address& addr, Reg32e r1, Reg32e r2) { opRRO(r1, r2, addr, T_APX|T_66|T_0F38, 0xEA); }
void cmpsxadd(const Address& addr, Reg32e r1, Reg32e r2) { opRRO(r1, r2, addr, T_APX|T_66|T_0F38, 0xE8); }
void cmpzxadd(const Address& addr, Reg32e r1, Reg32e r2) { opRRO(r1, r2, addr, T_APX|T_66|T_0F38, 0xE4); }
void aesdec128kl(Xmm x, const Address& addr) { opSSE_APX(x, addr, T_F3|T_0F38, 0xDD, T_F3|T_MUST_EVEX, 0xDD); }
void aesdec256kl(Xmm x, const Address& addr) { opSSE_APX(x, addr, T_F3|T_0F38, 0xDF, T_F3|T_MUST_EVEX, 0xDF); }
void aesdecwide128kl(const Address& addr) { opSSE_APX(xmm1, addr, T_F3|T_0F38, 0xD8, T_F3|T_MUST_EVEX, 0xD8); }
void aesdecwide256kl(const Address& addr) { opSSE_APX(xmm3, addr, T_F3|T_0F38, 0xD8, T_F3|T_MUST_EVEX, 0xD8); }
void aesenc128kl(Xmm x, const Address& addr) { opSSE_APX(x, addr, T_F3|T_0F38, 0xDC, T_F3|T_MUST_EVEX, 0xDC); }
void aesenc256kl(Xmm x, const Address& addr) { opSSE_APX(x, addr, T_F3|T_0F38, 0xDE, T_F3|T_MUST_EVEX, 0xDE); }
void aesencwide128kl(const Address& addr) { opSSE_APX(xmm0, addr, T_F3|T_0F38, 0xD8, T_F3|T_MUST_EVEX, 0xD8); }
void aesencwide256kl(const Address& addr) { opSSE_APX(xmm2, addr, T_F3|T_0F38, 0xD8, T_F3|T_MUST_EVEX, 0xD8); }
void encodekey128(Reg32 r1, Reg32 r2) { opEncodeKey(r1, r2, 0xFA, 0xDA); }
void encodekey256(Reg32 r1, Reg32 r2) { opEncodeKey(r1, r2, 0xFB, 0xDB); }
void rdfsbase(Reg32e r) { opRR(eax, r, T_F3|T_0F|T_ALLOW_DIFF_SIZE, 0xAE); }
void rdgsbase(Reg32e r) { opRR(ecx, r, T_F3|T_0F|T_ALLOW_DIFF_SIZE, 0xAE); }
void wrfsbase(Reg32e r) { opRR(edx, r, T_F3|T_0F|T_ALLOW_DIFF_SIZE, 0xAE); }
void wrgsbase(Reg32e r) { opRR(ebx, r, T_F3|T_0F|T_ALLOW_DIFF_SIZE, 0xAE); }
void tdpbssd(const Tmm& x1, const Tmm& x2, const Tmm& x3) { opVex(x1, &x3, x2, T_F2|T_0F38|T_W0, 0x5E); }
void tdpbsud(const Tmm& x1, const Tmm& x2, const Tmm& x3) { opVex(x1, &x3, x2, T_F3|T_0F38|T_W0, 0x5E); }
void tdpbusd(const Tmm& x1, const Tmm& x2, const Tmm& x3) { opVex(x1, &x3, x2, T_66|T_0F38|T_W0, 0x5E); }
void tdpbuud(const Tmm& x1, const Tmm& x2, const Tmm& x3) { opVex(x1, &x3, x2, T_0F38|T_W0, 0x5E); }
void tdpfp16ps(const Tmm& x1, const Tmm& x2, const Tmm& x3) { opVex(x1, &x3, x2, T_F2|T_0F38|T_W0, 0x5C); }
void tdpbf16ps(const Tmm& x1, const Tmm& x2, const Tmm& x3) { opVex(x1, &x3, x2, T_F3|T_0F38|T_W0, 0x5C); }
void tdpbf8ps(const Tmm& x1, const Tmm& x2, const Tmm& x3) { opVex(x1, &x3, x2, T_MAP5|T_W0, 0xFD); }
void tdpbhf8ps(const Tmm& x1, const Tmm& x2, const Tmm& x3) { opVex(x1, &x3, x2, T_F2|T_MAP5|T_W0, 0xFD); }
void tdphbf8ps(const Tmm& x1, const Tmm& x2, const Tmm& x3) { opVex(x1, &x3, x2, T_F3|T_MAP5|T_W0, 0xFD); }
void tdphf8ps(const Tmm& x1, const Tmm& x2, const Tmm& x3) { opVex(x1, &x3, x2, T_66|T_MAP5|T_W0, 0xFD); }
void tmmultf32ps(const Tmm& x1, const Tmm& x2, const Tmm& x3) { opVex(x1, &x3, x2, T_66|T_0F38|T_W0, 0x48); }
void tcmmimfp16ps(const Tmm& x1, const Tmm& x2, const Tmm& x3) { opVex(x1, &x3, x2, T_66|T_0F38|T_W0, 0x6C); }
void tcmmrlfp16ps(const Tmm& x1, const Tmm& x2, const Tmm& x3) { opVex(x1, &x3, x2, T_0F38|T_W0, 0x6C); }
void tileloadd(const Tmm& tm, const Address& addr) { opAMX(tm, addr, T_F2|T_0F38|T_W0, 0x4B); }
void tileloaddt1(const Tmm& tm, const Address& addr) { opAMX(tm, addr, T_66|T_0F38|T_W0, 0x4B); }
void tileloaddrs(const Tmm& tm, const Address& addr) { opAMX(tm, addr, T_F2|T_0F38|T_W0, 0x4A); }
void tileloaddrst1(const Tmm& tm, const Address& addr) { opAMX(tm, addr, T_66|T_0F38|T_W0, 0x4A); }
void ldtilecfg(const Address& addr) { opAMX(tmm0, addr, T_0F38|T_W0, 0x49); }
void sttilecfg(const Address& addr) { opAMX(tmm0, addr,  T_66|T_0F38|T_W0, 0x49); }
void tilestored(const Address& addr, const Tmm& tm) { opAMX(tm, addr, T_F3|T_0F38|T_W0, 0x4B); }
void tilerelease() { db(0xc4); db(0xe2); db(0x78); db(0x49); db(0xc0); }
void tilezero(const Tmm& t) { opVex(t, &tmm0, tmm0, T_F2|T_0F38|T_W0, 0x49); }
#else
void jcxz(std::string label) { db(0x67); opJmp(label, T_SHORT, 0xe3, 0, 0); }
void jcxz(const Label& label) { db(0x67); opJmp(label, T_SHORT, 0xe3, 0, 0); }
void jecxz(std::string label) { opJmp(label, T_SHORT, 0xe3, 0, 0); }
void jecxz(const Label& label) { opJmp(label, T_SHORT, 0xe3, 0, 0); }
void aaa() { db(0x37); }
void aad() { db(0xD5); db(0x0A); }
void aam() { db(0xD4); db(0x0A); }
void aas() { db(0x3F); }
void daa() { db(0x27); }
void das() { db(0x2F); }
void into() { db(0xCE); }
void popad() { db(0x61); }
void popfd() { db(0x9D); }
void pusha() { db(0x60); }
void pushad() { db(0x60); }
void pushfd() { db(0x9C); }
void popa() { db(0x61); }
void lds(Reg reg, const Address& addr) { opLoadSeg(addr, reg, T_NONE, 0xC5); }
void les(Reg reg, const Address& addr) { opLoadSeg(addr, reg, T_NONE, 0xC4); }
#endif
#ifndef XBYAK_NO_OP_NAMES
void and(const Operand& op1, const Operand& op2) { and_(op1, op2); }
void and(const Operand& op, uint32_t imm) { and_(op, imm); }
void or(const Operand& op1, const Operand& op2) { or_(op1, op2); }
void or(const Operand& op, uint32_t imm) { or_(op, imm); }
void xor(const Operand& op1, const Operand& op2) { xor_(op1, op2); }
void xor(const Operand& op, uint32_t imm) { xor_(op, imm); }
void not(const Operand& op) { not_(op); }
#endif
#ifndef XBYAK_DISABLE_AVX512
void kaddb(const Opmask& r1, const Opmask& r2, const Opmask& r3) { opVex(r1, &r2, r3, T_L1 | T_0F | T_66 | T_W0, 0x4A); }
void kaddd(const Opmask& r1, const Opmask& r2, const Opmask& r3) { opVex(r1, &r2, r3, T_L1 | T_0F | T_66 | T_W1, 0x4A); }
void kaddq(const Opmask& r1, const Opmask& r2, const Opmask& r3) { opVex(r1, &r2, r3, T_L1 | T_0F | T_W1, 0x4A); }
void kaddw(const Opmask& r1, const Opmask& r2, const Opmask& r3) { opVex(r1, &r2, r3, T_L1 | T_0F | T_W0, 0x4A); }
void kandb(const Opmask& r1, const Opmask& r2, const Opmask& r3) { opVex(r1, &r2, r3, T_L1 | T_0F | T_66 | T_W0, 0x41); }
void kandd(const Opmask& r1, const Opmask& r2, const Opmask& r3) { opVex(r1, &r2, r3, T_L1 | T_0F | T_66 | T_W1, 0x41); }
void kandnb(const Opmask& r1, const Opmask& r2, const Opmask& r3) { opVex(r1, &r2, r3, T_L1 | T_0F | T_66 | T_W0, 0x42); }
void kandnd(const Opmask& r1, const Opmask& r2, const Opmask& r3) { opVex(r1, &r2, r3, T_L1 | T_0F | T_66 | T_W1, 0x42); }
void kandnq(const Opmask& r1, const Opmask& r2, const Opmask& r3) { opVex(r1, &r2, r3, T_L1 | T_0F | T_W1, 0x42); }
void kandnw(const Opmask& r1, const Opmask& r2, const Opmask& r3) { opVex(r1, &r2, r3, T_L1 | T_0F | T_W0, 0x42); }
void kandq(const Opmask& r1, const Opmask& r2, const Opmask& r3) { opVex(r1, &r2, r3, T_L1 | T_0F | T_W1, 0x41); }
void kandw(const Opmask& r1, const Opmask& r2, const Opmask& r3) { opVex(r1, &r2, r3, T_L1 | T_0F | T_W0, 0x41); }
void kmovb(const Address& addr, const Opmask& k) { opKmov(k, addr, true, 8); }
void kmovb(const Opmask& k, const Operand& op) { opKmov(k, op, false, 8); }
void kmovb(Reg32 r, const Opmask& k) { opKmov(k, r, true, 8); }
void kmovd(const Address& addr, const Opmask& k) { opKmov(k, addr, true, 32); }
void kmovd(const Opmask& k, const Operand& op) { opKmov(k, op, false, 32); }
void kmovd(Reg32 r, const Opmask& k) { opKmov(k, r, true, 32); }
void kmovq(const Address& addr, const Opmask& k) { opKmov(k, addr, true, 64); }
void kmovq(const Opmask& k, const Operand& op) { opKmov(k, op, false, 64); }
void kmovw(const Address& addr, const Opmask& k) { opKmov(k, addr, true, 16); }
void kmovw(const Opmask& k, const Operand& op) { opKmov(k, op, false, 16); }
void kmovw(Reg32 r, const Opmask& k) { opKmov(k, r, true, 16); }
void knotb(const Opmask& r1, const Opmask& r2) { opVex(r1, 0, r2, T_0F | T_66 | T_W0, 0x44); }
void knotd(const Opmask& r1, const Opmask& r2) { opVex(r1, 0, r2, T_0F | T_66 | T_W1, 0x44); }
void knotq(const Opmask& r1, const Opmask& r2) { opVex(r1, 0, r2, T_0F | T_W1, 0x44); }
void knotw(const Opmask& r1, const Opmask& r2) { opVex(r1, 0, r2, T_0F | T_W0, 0x44); }
void korb(const Opmask& r1, const Opmask& r2, const Opmask& r3) { opVex(r1, &r2, r3, T_L1 | T_0F | T_66 | T_W0, 0x45); }
void kord(const Opmask& r1, const Opmask& r2, const Opmask& r3) { opVex(r1, &r2, r3, T_L1 | T_0F | T_66 | T_W1, 0x45); }
void korq(const Opmask& r1, const Opmask& r2, const Opmask& r3) { opVex(r1, &r2, r3, T_L1 | T_0F | T_W1, 0x45); }
void kortestb(const Opmask& r1, const Opmask& r2) { opVex(r1, 0, r2, T_0F | T_66 | T_W0, 0x98); }
void kortestd(const Opmask& r1, const Opmask& r2) { opVex(r1, 0, r2, T_0F | T_66 | T_W1, 0x98); }
void kortestq(const Opmask& r1, const Opmask& r2) { opVex(r1, 0, r2, T_0F | T_W1, 0x98); }
void kortestw(const Opmask& r1, const Opmask& r2) { opVex(r1, 0, r2, T_0F | T_W0, 0x98); }
void korw(const Opmask& r1, const Opmask& r2, const Opmask& r3) { opVex(r1, &r2, r3, T_L1 | T_0F | T_W0, 0x45); }
void kshiftlb(const Opmask& r1, const Opmask& r2, uint8_t imm) { opVex(r1, 0, r2, T_66 | T_0F3A | T_W0, 0x32, imm); }
void kshiftld(const Opmask& r1, const Opmask& r2, uint8_t imm) { opVex(r1, 0, r2, T_66 | T_0F3A | T_W0, 0x33, imm); }
void kshiftlq(const Opmask& r1, const Opmask& r2, uint8_t imm) { opVex(r1, 0, r2, T_66 | T_0F3A | T_W1, 0x33, imm); }
void kshiftlw(const Opmask& r1, const Opmask& r2, uint8_t imm) { opVex(r1, 0, r2, T_66 | T_0F3A | T_W1, 0x32, imm); }
void kshiftrb(const Opmask& r1, const Opmask& r2, uint8_t imm) { opVex(r1, 0, r2, T_66 | T_0F3A | T_W0, 0x30, imm); }
void kshiftrd(const Opmask& r1, const Opmask& r2, uint8_t imm) { opVex(r1, 0, r2, T_66 | T_0F3A | T_W0, 0x31, imm); }
void kshiftrq(const Opmask& r1, const Opmask& r2, uint8_t imm) { opVex(r1, 0, r2, T_66 | T_0F3A | T_W1, 0x31, imm); }
void kshiftrw(const Opmask& r1, const Opmask& r2, uint8_t imm) { opVex(r1, 0, r2, T_66 | T_0F3A | T_W1, 0x30, imm); }
void ktestb(const Opmask& r1, const Opmask& r2) { opVex(r1, 0, r2, T_0F | T_66 | T_W0, 0x99); }
void ktestd(const Opmask& r1, const Opmask& r2) { opVex(r1, 0, r2, T_0F | T_66 | T_W1, 0x99); }
void ktestq(const Opmask& r1, const Opmask& r2) { opVex(r1, 0, r2, T_0F | T_W1, 0x99); }
void ktestw(const Opmask& r1, const Opmask& r2) { opVex(r1, 0, r2, T_0F | T_W0, 0x99); }
void kunpckbw(const Opmask& r1, const Opmask& r2, const Opmask& r3) { opVex(r1, &r2, r3, T_L1 | T_0F | T_66 | T_W0, 0x4B); }
void kunpckdq(const Opmask& r1, const Opmask& r2, const Opmask& r3) { opVex(r1, &r2, r3, T_L1 | T_0F | T_W1, 0x4B); }
void kunpckwd(const Opmask& r1, const Opmask& r2, const Opmask& r3) { opVex(r1, &r2, r3, T_L1 | T_0F | T_W0, 0x4B); }
void kxnorb(const Opmask& r1, const Opmask& r2, const Opmask& r3) { opVex(r1, &r2, r3, T_L1 | T_0F | T_66 | T_W0, 0x46); }
void kxnord(const Opmask& r1, const Opmask& r2, const Opmask& r3) { opVex(r1, &r2, r3, T_L1 | T_0F | T_66 | T_W1, 0x46); }
void kxnorq(const Opmask& r1, const Opmask& r2, const Opmask& r3) { opVex(r1, &r2, r3, T_L1 | T_0F | T_W1, 0x46); }
void kxnorw(const Opmask& r1, const Opmask& r2, const Opmask& r3) { opVex(r1, &r2, r3, T_L1 | T_0F | T_W0, 0x46); }
void kxorb(const Opmask& r1, const Opmask& r2, const Opmask& r3) { opVex(r1, &r2, r3, T_L1 | T_0F | T_66 | T_W0, 0x47); }
void kxord(const Opmask& r1, const Opmask& r2, const Opmask& r3) { opVex(r1, &r2, r3, T_L1 | T_0F | T_66 | T_W1, 0x47); }
void kxorq(const Opmask& r1, const Opmask& r2, const Opmask& r3) { opVex(r1, &r2, r3, T_L1 | T_0F | T_W1, 0x47); }
void kxorw(const Opmask& r1, const Opmask& r2, const Opmask& r3) { opVex(r1, &r2, r3, T_L1 | T_0F | T_W0, 0x47); }
void v4fmaddps(Zmm z1, Zmm z2, const Address& addr) { opAVX_X_X_XM(z1, z2, addr, T_0F38 | T_F2 | T_W0 | T_YMM | T_MUST_EVEX | T_N16, 0x9A); }
void v4fmaddss(Xmm x1, Xmm x2, const Address& addr) { opAVX_X_X_XM(x1, x2, addr, T_0F38 | T_F2 | T_W0 | T_MUST_EVEX | T_N16, 0x9B); }
void v4fnmaddps(Zmm z1, Zmm z2, const Address& addr) { opAVX_X_X_XM(z1, z2, addr, T_0F38 | T_F2 | T_W0 | T_YMM | T_MUST_EVEX | T_N16, 0xAA); }
void v4fnmaddss(Xmm x1, Xmm x2, const Address& addr) { opAVX_X_X_XM(x1, x2, addr, T_0F38 | T_F2 | T_W0 | T_MUST_EVEX | T_N16, 0xAB); }
void vaddbf16(Xmm x1, Xmm x2, const Operand& op) { opAVX_X_X_XM(x1, x2, op, T_66|T_MAP5|T_W0|T_YMM|T_MUST_EVEX|T_B16, 0x58); }
void vaddph(Xmm xmm, const Operand& op1, const Operand& op2 = Operand()) { opAVX_X_X_XM(xmm, op1, op2, T_MAP5 | T_W0 | T_YMM | T_MUST_EVEX | T_ER_Z | T_B16, 0x58); }
void vaddsh(Xmm xmm, const Operand& op1, const Operand& op2 = Operand()) { opAVX_X_X_XM(xmm, op1, op2, T_MAP5 | T_F3 | T_W0 | T_MUST_EVEX | T_ER_X | T_N2, 0x58); }
void valignd(Xmm x1, Xmm x2, const Operand& op, uint8_t imm) { opAVX_X_X_XM(x1, x2, op, T_66|T_0F3A|T_W0|T_YMM|T_MUST_EVEX, 0x03, imm); }
void valignq(Xmm x1, Xmm x2, const Operand& op, uint8_t imm) { opAVX_X_X_XM(x1, x2, op, T_66|T_0F3A|T_EW1|T_YMM|T_MUST_EVEX, 0x03, imm); }
void vblendmpd(Xmm x1, Xmm x2, const Operand& op) { opAVX_X_X_XM(x1, x2, op, T_66|T_0F38|T_EW1|T_YMM|T_MUST_EVEX|T_B64, 0x65); }
void vblendmps(Xmm x1, Xmm x2, const Operand& op) { opAVX_X_X_XM(x1, x2, op, T_66|T_0F38|T_W0|T_YMM|T_MUST_EVEX|T_B32, 0x65); }
void vbroadcastf32x2(Ymm y, const Operand& op) { opAVX_X_XM_IMM(y, op, T_66 | T_0F38 | T_YMM | T_MUST_EVEX | T_W0 | T_N8, 0x19); }
void vbroadcastf32x4(Ymm y, const Address& addr) { opAVX_X_XM_IMM(y, addr, T_66 | T_0F38 | T_YMM | T_MUST_EVEX | T_W0 | T_N16, 0x1A); }
void vbroadcastf32x8(Zmm y, const Address& addr) { opAVX_X_XM_IMM(y, addr, T_66 | T_0F38 | T_YMM | T_MUST_EVEX | T_W0 | T_N32, 0x1B); }
void vbroadcastf64x2(Ymm y, const Address& addr) { opAVX_X_XM_IMM(y, addr, T_66 | T_0F38 | T_YMM | T_MUST_EVEX | T_EW1 | T_N16, 0x1A); }
void vbroadcastf64x4(Zmm y, const Address& addr) { opAVX_X_XM_IMM(y, addr, T_66 | T_0F38 | T_YMM | T_MUST_EVEX | T_EW1 | T_N32, 0x1B); }
void vbroadcasti32x2(Xmm x, const Operand& op) { opAVX_X_XM_IMM(x, op, T_66 | T_0F38 | T_YMM | T_MUST_EVEX | T_W0 | T_N8, 0x59); }
void vbroadcasti32x4(Ymm y, const Operand& op) { opAVX_X_XM_IMM(y, op, T_66 | T_0F38 | T_YMM | T_MUST_EVEX | T_W0 | T_N16, 0x5A); }
void vbroadcasti32x8(Zmm z, const Operand& op) { opAVX_X_XM_IMM(z, op, T_66 | T_0F38 | T_YMM | T_MUST_EVEX | T_W0 | T_N32, 0x5B); }
void vbroadcasti64x2(Ymm y, const Operand& op) { opAVX_X_XM_IMM(y, op, T_66 | T_0F38 | T_YMM | T_MUST_EVEX | T_EW1 | T_N16, 0x5A); }
void vbroadcasti64x4(Zmm z, const Operand& op) { opAVX_X_XM_IMM(z, op, T_66 | T_0F38 | T_YMM | T_MUST_EVEX | T_EW1 | T_N32, 0x5B); }
void vcmpbf16(const Opmask& k, Xmm x, const Operand& op, uint8_t imm) { opVex(k, &x, op, T_MUST_EVEX|T_F2|T_0F3A|T_W0|T_YMM|T_B16, 0xC2, imm); }
void vcmpeq_ospd(const Opmask& k, Xmm x, const Operand& op) { vcmppd(k, x, op, 16); }
void vcmpeq_osps(const Opmask& k, Xmm x, const Operand& op) { vcmpps(k, x, op, 16); }
void vcmpeq_ossd(const Opmask& k, Xmm x, const Operand& op) { vcmpsd(k, x, op, 16); }
void vcmpeq_osss(const Opmask& k, Xmm x, const Operand& op) { vcmpss(k, x, op, 16); }
void vcmpeq_uqpd(const Opmask& k, Xmm x, const Operand& op) { vcmppd(k, x, op, 8); }
void vcmpeq_uqps(const Opmask& k, Xmm x, const Operand& op) { vcmpps(k, x, op, 8); }
void vcmpeq_uqsd(const Opmask& k, Xmm x, const Operand& op) { vcmpsd(k, x, op, 8); }
void vcmpeq_uqss(const Opmask& k, Xmm x, const Operand& op) { vcmpss(k, x, op, 8); }
void vcmpeq_uspd(const Opmask& k, Xmm x, const Operand& op) { vcmppd(k, x, op, 24); }
void vcmpeq_usps(const Opmask& k, Xmm x, const Operand& op) { vcmpps(k, x, op, 24); }
void vcmpeq_ussd(const Opmask& k, Xmm x, const Operand& op) { vcmpsd(k, x, op, 24); }
void vcmpeq_usss(const Opmask& k, Xmm x, const Operand& op) { vcmpss(k, x, op, 24); }
void vcmpeqpd(const Opmask& k, Xmm x, const Operand& op) { vcmppd(k, x, op, 0); }
void vcmpeqps(const Opmask& k, Xmm x, const Operand& op) { vcmpps(k, x, op, 0); }
void vcmpeqsd(const Opmask& k, Xmm x, const Operand& op) { vcmpsd(k, x, op, 0); }
void vcmpeqss(const Opmask& k, Xmm x, const Operand& op) { vcmpss(k, x, op, 0); }
void vcmpfalse_ospd(const Opmask& k, Xmm x, const Operand& op) { vcmppd(k, x, op, 27); }
void vcmpfalse_osps(const Opmask& k, Xmm x, const Operand& op) { vcmpps(k, x, op, 27); }
void vcmpfalse_ossd(const Opmask& k, Xmm x, const Operand& op) { vcmpsd(k, x, op, 27); }
void vcmpfalse_osss(const Opmask& k, Xmm x, const Operand& op) { vcmpss(k, x, op, 27); }
void vcmpfalsepd(const Opmask& k, Xmm x, const Operand& op) { vcmppd(k, x, op, 11); }
void vcmpfalseps(const Opmask& k, Xmm x, const Operand& op) { vcmpps(k, x, op, 11); }
void vcmpfalsesd(const Opmask& k, Xmm x, const Operand& op) { vcmpsd(k, x, op, 11); }
void vcmpfalsess(const Opmask& k, Xmm x, const Operand& op) { vcmpss(k, x, op, 11); }
void vcmpge_oqpd(const Opmask& k, Xmm x, const Operand& op) { vcmppd(k, x, op, 29); }
void vcmpge_oqps(const Opmask& k, Xmm x, const Operand& op) { vcmpps(k, x, op, 29); }
void vcmpge_oqsd(const Opmask& k, Xmm x, const Operand& op) { vcmpsd(k, x, op, 29); }
void vcmpge_oqss(const Opmask& k, Xmm x, const Operand& op) { vcmpss(k, x, op, 29); }
void vcmpgepd(const Opmask& k, Xmm x, const Operand& op) { vcmppd(k, x, op, 13); }
void vcmpgeps(const Opmask& k, Xmm x, const Operand& op) { vcmpps(k, x, op, 13); }
void vcmpgesd(const Opmask& k, Xmm x, const Operand& op) { vcmpsd(k, x, op, 13); }
void vcmpgess(const Opmask& k, Xmm x, const Operand& op) { vcmpss(k, x, op, 13); }
void vcmpgt_oqpd(const Opmask& k, Xmm x, const Operand& op) { vcmppd(k, x, op, 30); }
void vcmpgt_oqps(const Opmask& k, Xmm x, const Operand& op) { vcmpps(k, x, op, 30); }
void vcmpgt_oqsd(const Opmask& k, Xmm x, const Operand& op) { vcmpsd(k, x, op, 30); }
void vcmpgt_oqss(const Opmask& k, Xmm x, const Operand& op) { vcmpss(k, x, op, 30); }
void vcmpgtpd(const Opmask& k, Xmm x, const Operand& op) { vcmppd(k, x, op, 14); }
void vcmpgtps(const Opmask& k, Xmm x, const Operand& op) { vcmpps(k, x, op, 14); }
void vcmpgtsd(const Opmask& k, Xmm x, const Operand& op) { vcmpsd(k, x, op, 14); }
void vcmpgtss(const Opmask& k, Xmm x, const Operand& op) { vcmpss(k, x, op, 14); }
void vcmple_oqpd(const Opmask& k, Xmm x, const Operand& op) { vcmppd(k, x, op, 18); }
void vcmple_oqps(const Opmask& k, Xmm x, const Operand& op) { vcmpps(k, x, op, 18); }
void vcmple_oqsd(const Opmask& k, Xmm x, const Operand& op) { vcmpsd(k, x, op, 18); }
void vcmple_oqss(const Opmask& k, Xmm x, const Operand& op) { vcmpss(k, x, op, 18); }
void vcmplepd(const Opmask& k, Xmm x, const Operand& op) { vcmppd(k, x, op, 2); }
void vcmpleps(const Opmask& k, Xmm x, const Operand& op) { vcmpps(k, x, op, 2); }
void vcmplesd(const Opmask& k, Xmm x, const Operand& op) { vcmpsd(k, x, op, 2); }
void vcmpless(const Opmask& k, Xmm x, const Operand& op) { vcmpss(k, x, op, 2); }
void vcmplt_oqpd(const Opmask& k, Xmm x, const Operand& op) { vcmppd(k, x, op, 17); }
void vcmplt_oqps(const Opmask& k, Xmm x, const Operand& op) { vcmpps(k, x, op, 17); }
void vcmplt_oqsd(const Opmask& k, Xmm x, const Operand& op) { vcmpsd(k, x, op, 17); }
void vcmplt_oqss(const Opmask& k, Xmm x, const Operand& op) { vcmpss(k, x, op, 17); }
void vcmpltpd(const Opmask& k, Xmm x, const Operand& op) { vcmppd(k, x, op, 1); }
void vcmpltps(const Opmask& k, Xmm x, const Operand& op) { vcmpps(k, x, op, 1); }
void vcmpltsd(const Opmask& k, Xmm x, const Operand& op) { vcmpsd(k, x, op, 1); }
void vcmpltss(const Opmask& k, Xmm x, const Operand& op) { vcmpss(k, x, op, 1); }
void vcmpneq_oqpd(const Opmask& k, Xmm x, const Operand& op) { vcmppd(k, x, op, 12); }
void vcmpneq_oqps(const Opmask& k, Xmm x, const Operand& op) { vcmpps(k, x, op, 12); }
void vcmpneq_oqsd(const Opmask& k, Xmm x, const Operand& op) { vcmpsd(k, x, op, 12); }
void vcmpneq_oqss(const Opmask& k, Xmm x, const Operand& op) { vcmpss(k, x, op, 12); }
void vcmpneq_ospd(const Opmask& k, Xmm x, const Operand& op) { vcmppd(k, x, op, 28); }
void vcmpneq_osps(const Opmask& k, Xmm x, const Operand& op) { vcmpps(k, x, op, 28); }
void vcmpneq_ossd(const Opmask& k, Xmm x, const Operand& op) { vcmpsd(k, x, op, 28); }
void vcmpneq_osss(const Opmask& k, Xmm x, const Operand& op) { vcmpss(k, x, op, 28); }
void vcmpneq_uspd(const Opmask& k, Xmm x, const Operand& op) { vcmppd(k, x, op, 20); }
void vcmpneq_usps(const Opmask& k, Xmm x, const Operand& op) { vcmpps(k, x, op, 20); }
void vcmpneq_ussd(const Opmask& k, Xmm x, const Operand& op) { vcmpsd(k, x, op, 20); }
void vcmpneq_usss(const Opmask& k, Xmm x, const Operand& op) { vcmpss(k, x, op, 20); }
void vcmpneqpd(const Opmask& k, Xmm x, const Operand& op) { vcmppd(k, x, op, 4); }
void vcmpneqps(const Opmask& k, Xmm x, const Operand& op) { vcmpps(k, x, op, 4); }
void vcmpneqsd(const Opmask& k, Xmm x, const Operand& op) { vcmpsd(k, x, op, 4); }
void vcmpneqss(const Opmask& k, Xmm x, const Operand& op) { vcmpss(k, x, op, 4); }
void vcmpnge_uqpd(const Opmask& k, Xmm x, const Operand& op) { vcmppd(k, x, op, 25); }
void vcmpnge_uqps(const Opmask& k, Xmm x, const Operand& op) { vcmpps(k, x, op, 25); }
void vcmpnge_uqsd(const Opmask& k, Xmm x, const Operand& op) { vcmpsd(k, x, op, 25); }
void vcmpnge_uqss(const Opmask& k, Xmm x, const Operand& op) { vcmpss(k, x, op, 25); }
void vcmpngepd(const Opmask& k, Xmm x, const Operand& op) { vcmppd(k, x, op, 9); }
void vcmpngeps(const Opmask& k, Xmm x, const Operand& op) { vcmpps(k, x, op, 9); }
void vcmpngesd(const Opmask& k, Xmm x, const Operand& op) { vcmpsd(k, x, op, 9); }
void vcmpngess(const Opmask& k, Xmm x, const Operand& op) { vcmpss(k, x, op, 9); }
void vcmpngt_uqpd(const Opmask& k, Xmm x, const Operand& op) { vcmppd(k, x, op, 26); }
void vcmpngt_uqps(const Opmask& k, Xmm x, const Operand& op) { vcmpps(k, x, op, 26); }
void vcmpngt_uqsd(const Opmask& k, Xmm x, const Operand& op) { vcmpsd(k, x, op, 26); }
void vcmpngt_uqss(const Opmask& k, Xmm x, const Operand& op) { vcmpss(k, x, op, 26); }
void vcmpngtpd(const Opmask& k, Xmm x, const Operand& op) { vcmppd(k, x, op, 10); }
void vcmpngtps(const Opmask& k, Xmm x, const Operand& op) { vcmpps(k, x, op, 10); }
void vcmpngtsd(const Opmask& k, Xmm x, const Operand& op) { vcmpsd(k, x, op, 10); }
void vcmpngtss(const Opmask& k, Xmm x, const Operand& op) { vcmpss(k, x, op, 10); }
void vcmpnle_uqpd(const Opmask& k, Xmm x, const Operand& op) { vcmppd(k, x, op, 22); }
void vcmpnle_uqps(const Opmask& k, Xmm x, const Operand& op) { vcmpps(k, x, op, 22); }
void vcmpnle_uqsd(const Opmask& k, Xmm x, const Operand& op) { vcmpsd(k, x, op, 22); }
void vcmpnle_uqss(const Opmask& k, Xmm x, const Operand& op) { vcmpss(k, x, op, 22); }
void vcmpnlepd(const Opmask& k, Xmm x, const Operand& op) { vcmppd(k, x, op, 6); }
void vcmpnleps(const Opmask& k, Xmm x, const Operand& op) { vcmpps(k, x, op, 6); }
void vcmpnlesd(const Opmask& k, Xmm x, const Operand& op) { vcmpsd(k, x, op, 6); }
void vcmpnless(const Opmask& k, Xmm x, const Operand& op) { vcmpss(k, x, op, 6); }
void vcmpnlt_uqpd(const Opmask& k, Xmm x, const Operand& op) { vcmppd(k, x, op, 21); }
void vcmpnlt_uqps(const Opmask& k, Xmm x, const Operand& op) { vcmpps(k, x, op, 21); }
void vcmpnlt_uqsd(const Opmask& k, Xmm x, const Operand& op) { vcmpsd(k, x, op, 21); }
void vcmpnlt_uqss(const Opmask& k, Xmm x, const Operand& op) { vcmpss(k, x, op, 21); }
void vcmpnltpd(const Opmask& k, Xmm x, const Operand& op) { vcmppd(k, x, op, 5); }
void vcmpnltps(const Opmask& k, Xmm x, const Operand& op) { vcmpps(k, x, op, 5); }
void vcmpnltsd(const Opmask& k, Xmm x, const Operand& op) { vcmpsd(k, x, op, 5); }
void vcmpnltss(const Opmask& k, Xmm x, const Operand& op) { vcmpss(k, x, op, 5); }
void vcmpord_spd(const Opmask& k, Xmm x, const Operand& op) { vcmppd(k, x, op, 23); }
void vcmpord_sps(const Opmask& k, Xmm x, const Operand& op) { vcmpps(k, x, op, 23); }
void vcmpord_ssd(const Opmask& k, Xmm x, const Operand& op) { vcmpsd(k, x, op, 23); }
void vcmpord_sss(const Opmask& k, Xmm x, const Operand& op) { vcmpss(k, x, op, 23); }
void vcmpordpd(const Opmask& k, Xmm x, const Operand& op) { vcmppd(k, x, op, 7); }
void vcmpordps(const Opmask& k, Xmm x, const Operand& op) { vcmpps(k, x, op, 7); }
void vcmpordsd(const Opmask& k, Xmm x, const Operand& op) { vcmpsd(k, x, op, 7); }
void vcmpordss(const Opmask& k, Xmm x, const Operand& op) { vcmpss(k, x, op, 7); }
void vcmppd(const Opmask& k, Xmm x, const Operand& op, uint8_t imm) { opAVX_K_X_XM(k, x, op, T_66|T_0F|T_EW1|T_YMM|T_SAE_Z|T_MUST_EVEX|T_B64, 0xC2, imm); }
void vcmpph(const Opmask& k, Xmm x, const Operand& op, uint8_t imm) { opAVX_K_X_XM(k, x, op, T_0F3A|T_W0|T_YMM|T_SAE_Z|T_MUST_EVEX|T_B16, 0xC2, imm); }
void vcmpps(const Opmask& k, Xmm x, const Operand& op, uint8_t imm) { opAVX_K_X_XM(k, x, op, T_0F|T_W0|T_YMM|T_SAE_Z|T_MUST_EVEX|T_B32, 0xC2, imm); }
void vcmpsd(const Opmask& k, Xmm x, const Operand& op, uint8_t imm) { opAVX_K_X_XM(k, x, op, T_N8|T_F2|T_0F|T_EW1|T_SAE_Z|T_MUST_EVEX, 0xC2, imm); }
void vcmpsh(const Opmask& k, Xmm x, const Operand& op, uint8_t imm) { opAVX_K_X_XM(k, x, op, T_N2|T_F3|T_0F3A|T_W0|T_SAE_X|T_MUST_EVEX, 0xC2, imm); }
void vcmpss(const Opmask& k, Xmm x, const Operand& op, uint8_t imm) { opAVX_K_X_XM(k, x, op, T_N4|T_F3|T_0F|T_W0|T_SAE_Z|T_MUST_EVEX, 0xC2, imm); }
void vcmptrue_uspd(const Opmask& k, Xmm x, const Operand& op) { vcmppd(k, x, op, 31); }
void vcmptrue_usps(const Opmask& k, Xmm x, const Operand& op) { vcmpps(k, x, op, 31); }
void vcmptrue_ussd(const Opmask& k, Xmm x, const Operand& op) { vcmpsd(k, x, op, 31); }
void vcmptrue_usss(const Opmask& k, Xmm x, const Operand& op) { vcmpss(k, x, op, 31); }
void vcmptruepd(const Opmask& k, Xmm x, const Operand& op) { vcmppd(k, x, op, 15); }
void vcmptrueps(const Opmask& k, Xmm x, const Operand& op) { vcmpps(k, x, op, 15); }
void vcmptruesd(const Opmask& k, Xmm x, const Operand& op) { vcmpsd(k, x, op, 15); }
void vcmptruess(const Opmask& k, Xmm x, const Operand& op) { vcmpss(k, x, op, 15); }
void vcmpunord_spd(const Opmask& k, Xmm x, const Operand& op) { vcmppd(k, x, op, 19); }
void vcmpunord_sps(const Opmask& k, Xmm x, const Operand& op) { vcmpps(k, x, op, 19); }
void vcmpunord_ssd(const Opmask& k, Xmm x, const Operand& op) { vcmpsd(k, x, op, 19); }
void vcmpunord_sss(const Opmask& k, Xmm x, const Operand& op) { vcmpss(k, x, op, 19); }
void vcmpunordpd(const Opmask& k, Xmm x, const Operand& op) { vcmppd(k, x, op, 3); }
void vcmpunordps(const Opmask& k, Xmm x, const Operand& op) { vcmpps(k, x, op, 3); }
void vcmpunordsd(const Opmask& k, Xmm x, const Operand& op) { vcmpsd(k, x, op, 3); }
void vcmpunordss(const Opmask& k, Xmm x, const Operand& op) { vcmpss(k, x, op, 3); }
void vcomisbf16(Xmm x, const Operand& op) { opAVX_X_XM_IMM(x, op, T_N2|T_66|T_MAP5|T_W0|T_MUST_EVEX, 0x2F); }
void vcomish(Xmm x, const Operand& op) { opAVX_X_XM_IMM(x, op, T_N2|T_MAP5|T_W0|T_SAE_X|T_MUST_EVEX, 0x2F); }
void vcompresspd(const Operand& op, Xmm x) { opAVX_X_XM_IMM(x, op, T_N8|T_66|T_0F38|T_EW1|T_YMM|T_MUST_EVEX, 0x8A); }
void vcompressps(const Operand& op, Xmm x) { opAVX_X_XM_IMM(x, op, T_N4|T_66|T_0F38|T_W0|T_YMM|T_MUST_EVEX, 0x8A); }
void vcomxsd(Xmm x, const Operand& op) { opAVX_X_XM_IMM(x, op, T_N8|T_F2|T_0F|T_EW1|T_SAE_X|T_MUST_EVEX, 0x2F); }
void vcomxsh(Xmm x, const Operand& op) { opAVX_X_XM_IMM(x, op, T_N2|T_F3|T_MAP5|T_W0|T_SAE_X|T_MUST_EVEX, 0x2F); }
void vcomxss(Xmm x, const Operand& op) { opAVX_X_XM_IMM(x, op, T_N4|T_F3|T_0F|T_W0|T_SAE_X|T_MUST_EVEX, 0x2F); }
void vcvt2ph2bf8(Xmm x1, Xmm x2, const Operand& op) { opAVX_X_X_XM(x1, x2, op, T_N1|T_F2|T_0F38|T_W0|T_YMM|T_MUST_EVEX|T_B16, 0x74); }
void vcvt2ph2bf8s(Xmm x1, Xmm x2, const Operand& op) { opAVX_X_X_XM(x1, x2, op, T_N1|T_F2|T_MAP5|T_W0|T_YMM|T_MUST_EVEX|T_B16, 0x74); }
void vcvt2ph2hf8(Xmm x1, Xmm x2, const Operand& op) { opAVX_X_X_XM(x1, x2, op, T_N1|T_F2|T_MAP5|T_W0|T_YMM|T_MUST_EVEX|T_B16, 0x18); }
void vcvt2ph2hf8s(Xmm x1, Xmm x2, const Operand& op) { opAVX_X_X_XM(x1, x2, op, T_N1|T_F2|T_MAP5|T_W0|T_YMM|T_MUST_EVEX|T_B16, 0x1B); }
void vcvt2ps2phx(Xmm x1, Xmm x2, const Operand& op) { opAVX_X_X_XM(x1, x2, op, T_66|T_0F38|T_W0|T_YMM|T_ER_Z|T_MUST_EVEX|T_B32, 0x67); }
void vcvtbf162ibs(Xmm x, const Operand& op) { opAVX_X_XM_IMM(x, op, T_F2|T_MAP5|T_W0|T_YMM|T_MUST_EVEX|T_B16, 0x69); }
void vcvtbf162iubs(Xmm x, const Operand& op) { opAVX_X_XM_IMM(x, op, T_F2|T_MAP5|T_W0|T_YMM|T_MUST_EVEX|T_B16, 0x6B); }
void vcvtbiasph2bf8(Xmm x1, Xmm x2, const Operand& op) { opCvt6(x1, x2, op, T_0F38|T_W0|T_YMM|T_MUST_EVEX|T_B16, 0x74); }
void vcvtbiasph2bf8s(Xmm x1, Xmm x2, const Operand& op) { opCvt6(x1, x2, op, T_MAP5|T_W0|T_YMM|T_MUST_EVEX|T_B16, 0x74); }
void vcvtbiasph2hf8(Xmm x1, Xmm x2, const Operand& op) { opCvt6(x1, x2, op, T_MAP5|T_W0|T_YMM|T_MUST_EVEX|T_B16, 0x18); }
void vcvtbiasph2hf8s(Xmm x1, Xmm x2, const Operand& op) { opCvt6(x1, x2, op, T_MAP5|T_W0|T_YMM|T_MUST_EVEX|T_B16, 0x1B); }
void vcvtdq2ph(Xmm x, const Operand& op) { checkCvt4(x, op); opCvt(x, op, T_N16|T_N_VL|T_MAP5|T_W0|T_YMM|T_ER_Z|T_MUST_EVEX|T_B32, 0x5B); }
void vcvthf82ph(Xmm x, const Operand& op) { checkCvt1(x, op); opVex(x, 0, op, T_MUST_EVEX | T_F2 | T_MAP5 | T_W0 | T_YMM | T_N1, 0x1E); }
void vcvtne2ps2bf16(Xmm x1, Xmm x2, const Operand& op) { opAVX_X_X_XM(x1, x2, op, T_F2|T_0F38|T_W0|T_YMM|T_SAE_Z|T_MUST_EVEX|T_B32, 0x72); }
void vcvtpd2ph(Xmm x, const Operand& op) { opCvt5(x, op, T_N16|T_N_VL|T_66|T_MAP5|T_EW1|T_ER_Z|T_MUST_EVEX|T_B64, 0x5A); }
void vcvtpd2qq(Xmm x, const Operand& op) { opAVX_X_XM_IMM(x, op, T_66|T_0F|T_EW1|T_YMM|T_ER_Z|T_MUST_EVEX|T_B64, 0x7B); }
void vcvtpd2udq(Xmm x, const Operand& op) { opCvt2(x, op, T_0F|T_EW1|T_YMM|T_ER_Z|T_MUST_EVEX|T_B64, 0x79); }
void vcvtpd2uqq(Xmm x, const Operand& op) { opAVX_X_XM_IMM(x, op, T_66|T_0F|T_EW1|T_YMM|T_ER_Z|T_MUST_EVEX|T_B64, 0x79); }
void vcvtph2bf8(Xmm x, const Operand& op) { opCvt2(x, op, T_F3|T_0F38|T_W0|T_YMM|T_MUST_EVEX|T_B16, 0x74); }
void vcvtph2bf8s(Xmm x, const Operand& op) { opCvt2(x, op, T_F3|T_MAP5|T_W0|T_YMM|T_MUST_EVEX|T_B16, 0x74); }
void vcvtph2dq(Xmm x, const Operand& op) { checkCvt1(x, op); opVex(x, 0, op, T_N8|T_N_VL|T_66|T_MAP5|T_W0|T_YMM|T_ER_Y|T_MUST_EVEX|T_B16, 0x5B); }
void vcvtph2hf8(Xmm x, const Operand& op) { opCvt2(x, op, T_F3|T_MAP5|T_W0|T_YMM|T_MUST_EVEX|T_B16, 0x18); }
void vcvtph2hf8s(Xmm x, const Operand& op) { opCvt2(x, op, T_F3|T_MAP5|T_W0|T_YMM|T_MUST_EVEX|T_B16, 0x1B); }
void vcvtph2ibs(Xmm x, const Operand& op) { opAVX_X_XM_IMM(x, op, T_MAP5|T_W0|T_YMM|T_ER_Z|T_MUST_EVEX|T_B16, 0x69); }
void vcvtph2iubs(Xmm x, const Operand& op) { opAVX_X_XM_IMM(x, op, T_MAP5|T_W0|T_YMM|T_ER_Z|T_MUST_EVEX|T_B16, 0x6B); }
void vcvtph2pd(Xmm x, const Operand& op) { if (!op.isXMM() && !op.isMEM()) XBYAK_THROW(ERR_BAD_MEM_SIZE) opVex(x, 0, op, T_N4|T_N_VL|T_MAP5|T_W0|T_YMM|T_SAE_X|T_MUST_EVEX|T_B16, 0x5A); }
void vcvtph2psx(Xmm x, const Operand& op) { checkCvt1(x, op); opVex(x, 0, op, T_N8|T_N_VL|T_66|T_MAP6|T_W0|T_YMM|T_SAE_Y|T_MUST_EVEX|T_B16, 0x13); }
void vcvtph2qq(Xmm x, const Operand& op) { if (!op.isXMM() && !op.isMEM()) XBYAK_THROW(ERR_BAD_MEM_SIZE) opVex(x, 0, op, T_N4|T_N_VL|T_66|T_MAP5|T_W0|T_YMM|T_ER_X|T_MUST_EVEX|T_B16, 0x7B); }
void vcvtph2udq(Xmm x, const Operand& op) { checkCvt1(x, op); opVex(x, 0, op, T_N8|T_N_VL|T_MAP5|T_W0|T_YMM|T_ER_Y|T_MUST_EVEX|T_B16, 0x79); }
void vcvtph2uqq(Xmm x, const Operand& op) { if (!op.isXMM() && !op.isMEM()) XBYAK_THROW(ERR_BAD_MEM_SIZE) opVex(x, 0, op, T_N4|T_N_VL|T_66|T_MAP5|T_W0|T_YMM|T_ER_X|T_MUST_EVEX|T_B16, 0x79); }
void vcvtph2uw(Xmm x, const Operand& op) { opAVX_X_XM_IMM(x, op, T_MAP5|T_W0|T_YMM|T_ER_Z|T_MUST_EVEX|T_B16, 0x7D); }
void vcvtph2w(Xmm x, const Operand& op) { opAVX_X_XM_IMM(x, op, T_66|T_MAP5|T_W0|T_YMM|T_ER_Z|T_MUST_EVEX|T_B16, 0x7D); }
void vcvtps2ibs(Xmm x, const Operand& op) { opAVX_X_XM_IMM(x, op, T_66|T_MAP5|T_W0|T_YMM|T_ER_Z|T_MUST_EVEX|T_B32, 0x69); }
void vcvtps2iubs(Xmm x, const Operand& op) { opAVX_X_XM_IMM(x, op, T_66|T_MAP5|T_W0|T_YMM|T_ER_Z|T_MUST_EVEX|T_B32, 0x6B); }
void vcvtps2phx(Xmm x, const Operand& op) { checkCvt4(x, op); opCvt(x, op, T_N16|T_N_VL|T_66|T_MAP5|T_W0|T_ER_Z|T_MUST_EVEX|T_B32, 0x1D); }
void vcvtps2qq(Xmm x, const Operand& op) { checkCvt1(x, op); opVex(x, 0, op, T_N8|T_N_VL|T_66|T_0F|T_W0|T_YMM|T_ER_Y|T_MUST_EVEX|T_B32, 0x7B); }
void vcvtps2udq(Xmm x, const Operand& op) { opAVX_X_XM_IMM(x, op, T_0F|T_W0|T_YMM|T_ER_Z|T_MUST_EVEX|T_B32, 0x79); }
void vcvtps2uqq(Xmm x, const Operand& op) { checkCvt1(x, op); opVex(x, 0, op, T_N8|T_N_VL|T_66|T_0F|T_W0|T_YMM|T_ER_Y|T_MUST_EVEX|T_B32, 0x79); }
void vcvtqq2pd(Xmm x, const Operand& op) { opAVX_X_XM_IMM(x, op, T_F3|T_0F|T_EW1|T_YMM|T_ER_Z|T_MUST_EVEX|T_B64, 0xE6); }
void vcvtqq2ph(Xmm x, const Operand& op) { opCvt5(x, op, T_N16|T_N_VL|T_MAP5|T_EW1|T_ER_Z|T_MUST_EVEX|T_B64, 0x5B); }
void vcvtqq2ps(Xmm x, const Operand& op) { opCvt2(x, op, T_0F|T_EW1|T_YMM|T_ER_Z|T_MUST_EVEX|T_B64, 0x5B); }
void vcvtsd2sh(Xmm x1, Xmm x2, const Operand& op) { opAVX_X_X_XM(x1, x2, op, T_N8|T_F2|T_MAP5|T_EW1|T_ER_X|T_MUST_EVEX, 0x5A); }
void vcvtsd2usi(Reg32e r, const Operand& op) { uint64_t type = (T_N8|T_F2|T_0F|T_ER_X|T_MUST_EVEX) | (r.isREG(64) ? T_EW1 : T_W0); opVex(r, &xm0, op, type, 0x79); }
void vcvtsh2sd(Xmm x1, Xmm x2, const Operand& op) { opAVX_X_X_XM(x1, x2, op, T_N2|T_F3|T_MAP5|T_W0|T_SAE_X|T_MUST_EVEX, 0x5A); }
void vcvtsh2si(Reg32e r, const Operand& op) { uint64_t type = (T_N2|T_F3|T_MAP5|T_ER_X|T_MUST_EVEX) | (r.isREG(64) ? T_EW1 : T_W0); opVex(r, &xm0, op, type, 0x2D); }
void vcvtsh2ss(Xmm x1, Xmm x2, const Operand& op) { opAVX_X_X_XM(x1, x2, op, T_N2|T_MAP6|T_W0|T_SAE_X|T_MUST_EVEX, 0x13); }
void vcvtsh2usi(Reg32e r, const Operand& op) { uint64_t type = (T_N2|T_F3|T_MAP5|T_ER_X|T_MUST_EVEX) | (r.isREG(64) ? T_EW1 : T_W0); opVex(r, &xm0, op, type, 0x79); }
void vcvtsi2sh(Xmm x1, Xmm x2, const Operand& op) { if (!(x1.isXMM() && x2.isXMM() && op.isBit(32|64))) XBYAK_THROW(ERR_BAD_COMBINATION) uint64_t type = (T_F3|T_MAP5|T_ER_R|T_MUST_EVEX|T_M_K) | (op.isBit(32) ? (T_W0 | T_N4) : (T_EW1 | T_N8)); opVex(x1, &x2, op, type, 0x2A); }
void vcvtss2sh(Xmm x1, Xmm x2, const Operand& op) { opAVX_X_X_XM(x1, x2, op, T_N4|T_MAP5|T_W0|T_ER_X|T_MUST_EVEX, 0x1D); }
void vcvtss2usi(Reg32e r, const Operand& op) { uint64_t type = (T_N4|T_F3|T_0F|T_ER_X|T_MUST_EVEX) | (r.isREG(64) ? T_EW1 : T_W0); opVex(r, &xm0, op, type, 0x79); }
void vcvttbf162ibs(Xmm x, const Operand& op) { opAVX_X_XM_IMM(x, op, T_F2|T_MAP5|T_W0|T_YMM|T_MUST_EVEX|T_B16, 0x68); }
void vcvttbf162iubs(Xmm x, const Operand& op) { opAVX_X_XM_IMM(x, op, T_F2|T_MAP5|T_W0|T_YMM|T_MUST_EVEX|T_B16, 0x6A); }
void vcvttpd2dqs(Xmm x, const Operand& op) { opCvt2(x, op, T_MAP5|T_EW1|T_YMM|T_SAE_Z|T_MUST_EVEX|T_B64, 0x6D); }
void vcvttpd2qq(Xmm x, const Operand& op) { opAVX_X_XM_IMM(x, op, T_66|T_0F|T_EW1|T_YMM|T_SAE_Z|T_MUST_EVEX|T_B64, 0x7A); }
void vcvttpd2qqs(Xmm x, const Operand& op) { opAVX_X_XM_IMM(x, op, T_66|T_MAP5|T_EW1|T_YMM|T_SAE_Z|T_MUST_EVEX|T_B64, 0x6D); }
void vcvttpd2udq(Xmm x, const Operand& op) { opCvt2(x, op, T_0F|T_EW1|T_YMM|T_SAE_Z|T_MUST_EVEX|T_B64, 0x78); }
void vcvttpd2udqs(Xmm x, const Operand& op) { opCvt2(x, op, T_MAP5|T_EW1|T_YMM|T_SAE_Z|T_MUST_EVEX|T_B64, 0x6C); }
void vcvttpd2uqq(Xmm x, const Operand& op) { opAVX_X_XM_IMM(x, op, T_66|T_0F|T_EW1|T_YMM|T_SAE_Z|T_MUST_EVEX|T_B64, 0x78); }
void vcvttpd2uqqs(Xmm x, const Operand& op) { opAVX_X_XM_IMM(x, op, T_66|T_MAP5|T_EW1|T_YMM|T_SAE_Z|T_MUST_EVEX|T_B64, 0x6C); }
void vcvttph2dq(Xmm x, const Operand& op) { checkCvt1(x, op); opVex(x, 0, op, T_N8|T_N_VL|T_F3|T_MAP5|T_W0|T_YMM|T_SAE_Y|T_MUST_EVEX|T_B16, 0x5B); }
void vcvttph2ibs(Xmm x, const Operand& op) { opAVX_X_XM_IMM(x, op, T_MAP5|T_W0|T_YMM|T_ER_Z|T_MUST_EVEX|T_B16, 0x68); }
void vcvttph2iubs(Xmm x, const Operand& op) { opAVX_X_XM_IMM(x, op, T_MAP5|T_W0|T_YMM|T_ER_Z|T_MUST_EVEX|T_B16, 0x6A); }
void vcvttph2qq(Xmm x, const Operand& op) { if (!op.isXMM() && !op.isMEM()) XBYAK_THROW(ERR_BAD_MEM_SIZE) opVex(x, 0, op, T_N4|T_N_VL|T_66|T_MAP5|T_W0|T_YMM|T_SAE_X|T_MUST_EVEX|T_B16, 0x7A); }
void vcvttph2udq(Xmm x, const Operand& op) { checkCvt1(x, op); opVex(x, 0, op, T_N8|T_N_VL|T_MAP5|T_W0|T_YMM|T_SAE_Y|T_MUST_EVEX|T_B16, 0x78); }
void vcvttph2uqq(Xmm x, const Operand& op) { if (!op.isXMM() && !op.isMEM()) XBYAK_THROW(ERR_BAD_MEM_SIZE) opVex(x, 0, op, T_N4|T_N_VL|T_66|T_MAP5|T_W0|T_YMM|T_SAE_X|T_MUST_EVEX|T_B16, 0x78); }
void vcvttph2uw(Xmm x, const Operand& op) { opAVX_X_XM_IMM(x, op, T_MAP5|T_W0|T_YMM|T_SAE_Z|T_MUST_EVEX|T_B16, 0x7C); }
void vcvttph2w(Xmm x, const Operand& op) { opAVX_X_XM_IMM(x, op, T_66|T_MAP5|T_W0|T_YMM|T_SAE_Z|T_MUST_EVEX|T_B16, 0x7C); }
void vcvttps2dqs(Xmm x, const Operand& op) { opAVX_X_XM_IMM(x, op, T_MAP5|T_W0|T_YMM|T_SAE_Z|T_MUST_EVEX|T_B32, 0x6D); }
void vcvttps2ibs(Xmm x, const Operand& op) { opAVX_X_XM_IMM(x, op, T_66|T_MAP5|T_W0|T_YMM|T_ER_Z|T_MUST_EVEX|T_B32, 0x68); }
void vcvttps2iubs(Xmm x, const Operand& op) { opAVX_X_XM_IMM(x, op, T_66|T_MAP5|T_W0|T_YMM|T_ER_Z|T_MUST_EVEX|T_B32, 0x6A); }
void vcvttps2qq(Xmm x, const Operand& op) { checkCvt1(x, op); opVex(x, 0, op, T_N8|T_N_VL|T_66|T_0F|T_W0|T_YMM|T_SAE_Y|T_MUST_EVEX|T_B32, 0x7A); }
void vcvttps2qqs(Xmm x, const Operand& op) { checkCvt1(x, op); opVex(x, 0, op, T_N8|T_N_VL|T_66|T_MAP5|T_W0|T_YMM|T_SAE_Y|T_MUST_EVEX|T_B32, 0x6D); }
void vcvttps2udq(Xmm x, const Operand& op) { opAVX_X_XM_IMM(x, op, T_0F|T_W0|T_YMM|T_SAE_Z|T_MUST_EVEX|T_B32, 0x78); }
void vcvttps2udqs(Xmm x, const Operand& op) { opAVX_X_XM_IMM(x, op, T_MAP5|T_W0|T_YMM|T_SAE_Z|T_MUST_EVEX|T_B32, 0x6C); }
void vcvttps2uqq(Xmm x, const Operand& op) { checkCvt1(x, op); opVex(x, 0, op, T_N8|T_N_VL|T_66|T_0F|T_W0|T_YMM|T_SAE_Y|T_MUST_EVEX|T_B32, 0x78); }
void vcvttps2uqqs(Xmm x, const Operand& op) { checkCvt1(x, op); opVex(x, 0, op, T_N8|T_N_VL|T_66|T_MAP5|T_W0|T_YMM|T_SAE_Y|T_MUST_EVEX|T_B32, 0x6C); }
void vcvttsd2sis(Reg32e r, const Operand& op) { uint64_t type = (T_N8|T_F2|T_MAP5|T_SAE_X|T_MUST_EVEX) | (r.isREG(64) ? T_EW1 : T_W0); opVex(r, &xm0, op, type, 0x6D); }
void vcvttsd2usi(Reg32e r, const Operand& op) { uint64_t type = (T_N8|T_F2|T_0F|T_SAE_X|T_MUST_EVEX) | (r.isREG(64) ? T_EW1 : T_W0); opVex(r, &xm0, op, type, 0x78); }
void vcvttsd2usis(Reg32e r, const Operand& op) { uint64_t type = (T_N8|T_F2|T_MAP5|T_SAE_X|T_MUST_EVEX) | (r.isREG(64) ? T_EW1 : T_W0); opVex(r, &xm0, op, type, 0x6C); }
void vcvttsh2si(Reg32e r, const Operand& op) { uint64_t type = (T_N2|T_F3|T_MAP5|T_SAE_X|T_MUST_EVEX) | (r.isREG(64) ? T_EW1 : T_W0); opVex(r, &xm0, op, type, 0x2C); }
void vcvttsh2usi(Reg32e r, const Operand& op) { uint64_t type = (T_N2|T_F3|T_MAP5|T_SAE_X|T_MUST_EVEX) | (r.isREG(64) ? T_EW1 : T_W0); opVex(r, &xm0, op, type, 0x78); }
void vcvttss2sis(Reg32e r, const Operand& op) { uint64_t type = (T_N4|T_F3|T_MAP5|T_SAE_X|T_MUST_EVEX) | (r.isREG(64) ? T_EW1 : T_W0); opVex(r, &xm0, op, type, 0x6D); }
void vcvttss2usi(Reg32e r, const Operand& op) { uint64_t type = (T_N4|T_F3|T_0F|T_SAE_X|T_MUST_EVEX) | (r.isREG(64) ? T_EW1 : T_W0); opVex(r, &xm0, op, type, 0x78); }
void vcvttss2usis(Reg32e r, const Operand& op) { uint64_t type = (T_N4|T_F3|T_MAP5|T_SAE_X|T_MUST_EVEX) | (r.isREG(64) ? T_EW1 : T_W0); opVex(r, &xm0, op, type, 0x6C); }
void vcvtudq2pd(Xmm x, const Operand& op) { checkCvt1(x, op); opVex(x, 0, op, T_N8|T_N_VL|T_F3|T_0F|T_W0|T_YMM|T_MUST_EVEX|T_B32, 0x7A); }
void vcvtudq2ph(Xmm x, const Operand& op) { checkCvt4(x, op); opCvt(x, op, T_N16|T_N_VL|T_F2|T_MAP5|T_W0|T_ER_Z|T_MUST_EVEX|T_B32, 0x7A); }
void vcvtudq2ps(Xmm x, const Operand& op) { opAVX_X_XM_IMM(x, op, T_F2|T_0F|T_W0|T_YMM|T_ER_Z|T_MUST_EVEX|T_B32, 0x7A); }
void vcvtuqq2pd(Xmm x, const Operand& op) { opAVX_X_XM_IMM(x, op, T_F3|T_0F|T_EW1|T_YMM|T_ER_Z|T_MUST_EVEX|T_B64, 0x7A); }
void vcvtuqq2ph(Xmm x, const Operand& op) { opCvt5(x, op, T_N16|T_N_VL|T_F2|T_MAP5|T_EW1|T_ER_Z|T_MUST_EVEX|T_B64, 0x7A); }
void vcvtuqq2ps(Xmm x, const Operand& op) { opCvt2(x, op, T_F2|T_0F|T_EW1|T_YMM|T_ER_Z|T_MUST_EVEX|T_B64, 0x7A); }
void vcvtusi2sd(Xmm x1, Xmm x2, const Operand& op) { opCvt3(x1, x2, op, T_F2 | T_0F | T_MUST_EVEX, T_W1 | T_EW1 | T_ER_X | T_N8, T_W0 | T_N4, 0x7B); }
void vcvtusi2sh(Xmm x1, Xmm x2, const Operand& op) { if (!(x1.isXMM() && x2.isXMM() && op.isBit(32|64))) XBYAK_THROW(ERR_BAD_COMBINATION) uint64_t type = (T_F3|T_MAP5|T_ER_R|T_MUST_EVEX|T_M_K) | (op.isBit(32) ? (T_W0 | T_N4) : (T_EW1 | T_N8)); opVex(x1, &x2, op, type, 0x7B); }
void vcvtusi2ss(Xmm x1, Xmm x2, const Operand& op) { opCvt3(x1, x2, op, T_F3 | T_0F | T_MUST_EVEX | T_ER_X, T_W1 | T_EW1 | T_N8, T_W0 | T_N4, 0x7B); }
void vcvtuw2ph(Xmm x, const Operand& op) { opAVX_X_XM_IMM(x, op, T_F2|T_MAP5|T_W0|T_YMM|T_ER_Z|T_MUST_EVEX|T_B16, 0x7D); }
void vcvtw2ph(Xmm x, const Operand& op) { opAVX_X_XM_IMM(x, op, T_F3|T_MAP5|T_W0|T_YMM|T_ER_Z|T_MUST_EVEX|T_B16, 0x7D); }
void vdbpsadbw(Xmm x1, Xmm x2, const Operand& op, uint8_t imm) { opAVX_X_X_XM(x1, x2, op, T_66|T_0F3A|T_W0|T_YMM|T_MUST_EVEX, 0x42, imm); }
void vdivbf16(Xmm x1, Xmm x2, const Operand& op) { opAVX_X_X_XM(x1, x2, op, T_66|T_MAP5|T_W0|T_YMM|T_MUST_EVEX|T_B16, 0x5E); }
void vdivph(Xmm xmm, const Operand& op1, const Operand& op2 = Operand()) { opAVX_X_X_XM(xmm, op1, op2, T_MAP5 | T_W0 | T_YMM | T_MUST_EVEX | T_ER_Z | T_B16, 0x5E); }
void vdivsh(Xmm xmm, const Operand& op1, const Operand& op2 = Operand()) { opAVX_X_X_XM(xmm, op1, op2, T_MAP5 | T_F3 | T_W0 | T_MUST_EVEX | T_ER_X | T_N2, 0x5E); }
void vdpbf16ps(Xmm x1, Xmm x2, const Operand& op) { opAVX_X_X_XM(x1, x2, op, T_F3|T_0F38|T_W0|T_YMM|T_SAE_Z|T_MUST_EVEX|T_B32, 0x52); }
void vdpphps(Xmm x1, Xmm x2, const Operand& op) { opAVX_X_X_XM(x1, x2, op, T_0F38|T_W0|T_YMM|T_SAE_Z|T_MUST_EVEX|T_B32, 0x52); }
void vexp2pd(Zmm z, const Operand& op) { opAVX_X_XM_IMM(z, op, T_66 | T_0F38 | T_MUST_EVEX | T_YMM | T_EW1 | T_B64 | T_SAE_Z, 0xC8); }
void vexp2ps(Zmm z, const Operand& op) { opAVX_X_XM_IMM(z, op, T_66 | T_0F38 | T_MUST_EVEX | T_YMM | T_W0 | T_B32 | T_SAE_Z, 0xC8); }
void vexpandpd(Xmm x, const Operand& op) { opAVX_X_XM_IMM(x, op, T_N8|T_66|T_0F38|T_EW1|T_YMM|T_MUST_EVEX, 0x88); }
void vexpandps(Xmm x, const Operand& op) { opAVX_X_XM_IMM(x, op, T_N4|T_66|T_0F38|T_W0|T_YMM|T_MUST_EVEX, 0x88); }
void vextractf32x4(const Operand& op, Ymm r, uint8_t imm) { if (!op.is(Operand::MEM | Operand::XMM)) XBYAK_THROW(ERR_BAD_COMBINATION) opVex(r, 0, op, T_N16|T_66|T_0F3A|T_W0|T_YMM|T_MUST_EVEX, 0x19, imm); }
void vextractf32x8(const Operand& op, Zmm r, uint8_t imm) { if (!op.is(Operand::MEM | Operand::YMM)) XBYAK_THROW(ERR_BAD_COMBINATION) opVex(r, 0, op, T_N32|T_66|T_0F3A|T_W0|T_YMM|T_MUST_EVEX, 0x1B, imm); }
void vextractf64x2(const Operand& op, Ymm r, uint8_t imm) { if (!op.is(Operand::MEM | Operand::XMM)) XBYAK_THROW(ERR_BAD_COMBINATION) opVex(r, 0, op, T_N16|T_66|T_0F3A|T_EW1|T_YMM|T_MUST_EVEX, 0x19, imm); }
void vextractf64x4(const Operand& op, Zmm r, uint8_t imm) { if (!op.is(Operand::MEM | Operand::YMM)) XBYAK_THROW(ERR_BAD_COMBINATION) opVex(r, 0, op, T_N32|T_66|T_0F3A|T_EW1|T_YMM|T_MUST_EVEX, 0x1B, imm); }
void vextracti32x4(const Operand& op, Ymm r, uint8_t imm) { if (!op.is(Operand::MEM | Operand::XMM)) XBYAK_THROW(ERR_BAD_COMBINATION) opVex(r, 0, op, T_N16|T_66|T_0F3A|T_W0|T_YMM|T_MUST_EVEX, 0x39, imm); }
void vextracti32x8(const Operand& op, Zmm r, uint8_t imm) { if (!op.is(Operand::MEM | Operand::YMM)) XBYAK_THROW(ERR_BAD_COMBINATION) opVex(r, 0, op, T_N32|T_66|T_0F3A|T_W0|T_YMM|T_MUST_EVEX, 0x3B, imm); }
void vextracti64x2(const Operand& op, Ymm r, uint8_t imm) { if (!op.is(Operand::MEM | Operand::XMM)) XBYAK_THROW(ERR_BAD_COMBINATION) opVex(r, 0, op, T_N16|T_66|T_0F3A|T_EW1|T_YMM|T_MUST_EVEX, 0x39, imm); }
void vextracti64x4(const Operand& op, Zmm r, uint8_t imm) { if (!op.is(Operand::MEM | Operand::YMM)) XBYAK_THROW(ERR_BAD_COMBINATION) opVex(r, 0, op, T_N32|T_66|T_0F3A|T_EW1|T_YMM|T_MUST_EVEX, 0x3B, imm); }
void vfcmaddcph(Xmm x1, Xmm x2, const Operand& op) { opAVX_X_X_XM(x1, x2, op, T_F2|T_MAP6|T_W0|T_YMM|T_ER_Z|T_MUST_EVEX|T_B32, 0x56); }
void vfcmulcph(Xmm x1, Xmm x2, const Operand& op) { opAVX_X_X_XM(x1, x2, op, T_F2|T_MAP6|T_W0|T_YMM|T_ER_Z|T_MUST_EVEX|T_B32, 0xD6); }
void vfixupimmpd(Xmm x1, Xmm x2, const Operand& op, uint8_t imm) { opAVX_X_X_XM(x1, x2, op, T_66|T_0F3A|T_EW1|T_YMM|T_SAE_Z|T_MUST_EVEX|T_B64, 0x54, imm); }
void vfixupimmps(Xmm x1, Xmm x2, const Operand& op, uint8_t imm) { opAVX_X_X_XM(x1, x2, op, T_66|T_0F3A|T_W0|T_YMM|T_SAE_Z|T_MUST_EVEX|T_B32, 0x54, imm); }
void vfixupimmsd(Xmm x1, Xmm x2, const Operand& op, uint8_t imm) { opAVX_X_X_XM(x1, x2, op, T_N8|T_66|T_0F3A|T_EW1|T_SAE_Z|T_MUST_EVEX, 0x55, imm); }
void vfixupimmss(Xmm x1, Xmm x2, const Operand& op, uint8_t imm) { opAVX_X_X_XM(x1, x2, op, T_N4|T_66|T_0F3A|T_W0|T_SAE_Z|T_MUST_EVEX, 0x55, imm); }
void vfmadd132bf16(Xmm x1, Xmm x2, const Operand& op) { opAVX_X_X_XM(x1, x2, op, T_MAP6|T_W0|T_YMM|T_MUST_EVEX|T_B16, 0x98); }
void vfmadd132ph(Xmm x1, Xmm x2, const Operand& op) { opAVX_X_X_XM(x1, x2, op, T_66|T_MAP6|T_W0|T_YMM|T_ER_Z|T_MUST_EVEX|T_B16, 0x98); }
void vfmadd132sh(Xmm x1, Xmm x2, const Operand& op) { opAVX_X_X_XM(x1, x2, op, T_N2|T_66|T_MAP6|T_W0|T_ER_X|T_MUST_EVEX, 0x99); }
void vfmadd213bf16(Xmm x1, Xmm x2, const Operand& op) { opAVX_X_X_XM(x1, x2, op, T_MAP6|T_W0|T_YMM|T_MUST_EVEX|T_B16, 0xA8); }
void vfmadd213ph(Xmm x1, Xmm x2, const Operand& op) { opAVX_X_X_XM(x1, x2, op, T_66|T_MAP6|T_W0|T_YMM|T_ER_Z|T_MUST_EVEX|T_B16, 0xA8); }
void vfmadd213sh(Xmm x1, Xmm x2, const Operand& op) { opAVX_X_X_XM(x1, x2, op, T_N2|T_66|T_MAP6|T_W0|T_ER_X|T_MUST_EVEX, 0xA9); }
void vfmadd231bf16(Xmm x1, Xmm x2, const Operand& op) { opAVX_X_X_XM(x1, x2, op, T_MAP6|T_W0|T_YMM|T_MUST_EVEX|T_B16, 0xB8); }
void vfmadd231ph(Xmm x1, Xmm x2, const Operand& op) { opAVX_X_X_XM(x1, x2, op, T_66|T_MAP6|T_W0|T_YMM|T_ER_Z|T_MUST_EVEX|T_B16, 0xB8); }
void vfmadd231sh(Xmm x1, Xmm x2, const Operand& op) { opAVX_X_X_XM(x1, x2, op, T_N2|T_66|T_MAP6|T_W0|T_ER_X|T_MUST_EVEX, 0xB9); }
void vfmaddcph(Xmm x1, Xmm x2, const Operand& op) { opAVX_X_X_XM(x1, x2, op, T_F3|T_MAP6|T_W0|T_YMM|T_ER_Z|T_MUST_EVEX|T_B32, 0x56); }
void vfmaddsub132ph(Xmm x1, Xmm x2, const Operand& op) { opAVX_X_X_XM(x1, x2, op, T_66|T_MAP6|T_W0|T_YMM|T_ER_Z|T_MUST_EVEX|T_B16, 0x96); }
void vfmaddsub213ph(Xmm x1, Xmm x2, const Operand& op) { opAVX_X_X_XM(x1, x2, op, T_66|T_MAP6|T_W0|T_YMM|T_ER_Z|T_MUST_EVEX|T_B16, 0xA6); }
void vfmaddsub231ph(Xmm x1, Xmm x2, const Operand& op) { opAVX_X_X_XM(x1, x2, op, T_66|T_MAP6|T_W0|T_YMM|T_ER_Z|T_MUST_EVEX|T_B16, 0xB6); }
void vfmsub132bf16(Xmm x1, Xmm x2, const Operand& op) { opAVX_X_X_XM(x1, x2, op, T_MAP6|T_W0|T_YMM|T_MUST_EVEX|T_B16, 0x9A); }
void vfmsub132ph(Xmm x1, Xmm x2, const Operand& op) { opAVX_X_X_XM(x1, x2, op, T_66|T_MAP6|T_W0|T_YMM|T_ER_Z|T_MUST_EVEX|T_B16, 0x9A); }
void vfmsub132sh(Xmm x1, Xmm x2, const Operand& op) { opAVX_X_X_XM(x1, x2, op, T_N2|T_66|T_MAP6|T_W0|T_ER_X|T_MUST_EVEX, 0x9B); }
void vfmsub213bf16(Xmm x1, Xmm x2, const Operand& op) { opAVX_X_X_XM(x1, x2, op, T_MAP6|T_W0|T_YMM|T_MUST_EVEX|T_B16, 0xAA); }
void vfmsub213ph(Xmm x1, Xmm x2, const Operand& op) { opAVX_X_X_XM(x1, x2, op, T_66|T_MAP6|T_W0|T_YMM|T_ER_Z|T_MUST_EVEX|T_B16, 0xAA); }
void vfmsub213sh(Xmm x1, Xmm x2, const Operand& op) { opAVX_X_X_XM(x1, x2, op, T_N2|T_66|T_MAP6|T_W0|T_ER_X|T_MUST_EVEX, 0xAB); }
void vfmsub231bf16(Xmm x1, Xmm x2, const Operand& op) { opAVX_X_X_XM(x1, x2, op, T_MAP6|T_W0|T_YMM|T_MUST_EVEX|T_B16, 0xBA); }
void vfmsub231ph(Xmm x1, Xmm x2, const Operand& op) { opAVX_X_X_XM(x1, x2, op, T_66|T_MAP6|T_W0|T_YMM|T_ER_Z|T_MUST_EVEX|T_B16, 0xBA); }
void vfmsub231sh(Xmm x1, Xmm x2, const Operand& op) { opAVX_X_X_XM(x1, x2, op, T_N2|T_66|T_MAP6|T_W0|T_ER_X|T_MUST_EVEX, 0xBB); }
void vfmsubadd132ph(Xmm x1, Xmm x2, const Operand& op) { opAVX_X_X_XM(x1, x2, op, T_66|T_MAP6|T_W0|T_YMM|T_ER_Z|T_MUST_EVEX|T_B16, 0x97); }
void vfmsubadd213ph(Xmm x1, Xmm x2, const Operand& op) { opAVX_X_X_XM(x1, x2, op, T_66|T_MAP6|T_W0|T_YMM|T_ER_Z|T_MUST_EVEX|T_B16, 0xA7); }
void vfmsubadd231ph(Xmm x1, Xmm x2, const Operand& op) { opAVX_X_X_XM(x1, x2, op, T_66|T_MAP6|T_W0|T_YMM|T_ER_Z|T_MUST_EVEX|T_B16, 0xB7); }
void vfmulcph(Xmm x1, Xmm x2, const Operand& op) { opAVX_X_X_XM(x1, x2, op, T_F3|T_MAP6|T_W0|T_YMM|T_ER_Z|T_MUST_EVEX|T_B32, 0xD6); }
void vfnmadd132bf16(Xmm x1, Xmm x2, const Operand& op) { opAVX_X_X_XM(x1, x2, op, T_MAP6|T_W0|T_YMM|T_MUST_EVEX|T_B16, 0x9C); }
void vfnmadd132ph(Xmm x1, Xmm x2, const Operand& op) { opAVX_X_X_XM(x1, x2, op, T_66|T_MAP6|T_W0|T_YMM|T_ER_Z|T_MUST_EVEX|T_B16, 0x9C); }
void vfnmadd132sh(Xmm x1, Xmm x2, const Operand& op) { opAVX_X_X_XM(x1, x2, op, T_N2|T_66|T_MAP6|T_W0|T_ER_X|T_MUST_EVEX, 0x9D); }
void vfnmadd213bf16(Xmm x1, Xmm x2, const Operand& op) { opAVX_X_X_XM(x1, x2, op, T_MAP6|T_W0|T_YMM|T_MUST_EVEX|T_B16, 0xAC); }
void vfnmadd213ph(Xmm x1, Xmm x2, const Operand& op) { opAVX_X_X_XM(x1, x2, op, T_66|T_MAP6|T_W0|T_YMM|T_ER_Z|T_MUST_EVEX|T_B16, 0xAC); }
void vfnmadd213sh(Xmm x1, Xmm x2, const Operand& op) { opAVX_X_X_XM(x1, x2, op, T_N2|T_66|T_MAP6|T_W0|T_ER_X|T_MUST_EVEX, 0xAD); }
void vfnmadd231bf16(Xmm x1, Xmm x2, const Operand& op) { opAVX_X_X_XM(x1, x2, op, T_MAP6|T_W0|T_YMM|T_MUST_EVEX|T_B16, 0xBC); }
void vfnmadd231ph(Xmm x1, Xmm x2, const Operand& op) { opAVX_X_X_XM(x1, x2, op, T_66|T_MAP6|T_W0|T_YMM|T_ER_Z|T_MUST_EVEX|T_B16, 0xBC); }
void vfnmadd231sh(Xmm x1, Xmm x2, const Operand& op) { opAVX_X_X_XM(x1, x2, op, T_N2|T_66|T_MAP6|T_W0|T_ER_X|T_MUST_EVEX, 0xBD); }
void vfnmsub132bf16(Xmm x1, Xmm x2, const Operand& op) { opAVX_X_X_XM(x1, x2, op, T_MAP6|T_W0|T_YMM|T_MUST_EVEX|T_B16, 0x9E); }
void vfnmsub132ph(Xmm x1, Xmm x2, const Operand& op) { opAVX_X_X_XM(x1, x2, op, T_66|T_MAP6|T_W0|T_YMM|T_ER_Z|T_MUST_EVEX|T_B16, 0x9E); }
void vfnmsub132sh(Xmm x1, Xmm x2, const Operand& op) { opAVX_X_X_XM(x1, x2, op, T_N2|T_66|T_MAP6|T_W0|T_ER_X|T_MUST_EVEX, 0x9F); }
void vfnmsub213bf16(Xmm x1, Xmm x2, const Operand& op) { opAVX_X_X_XM(x1, x2, op, T_MAP6|T_W0|T_YMM|T_MUST_EVEX|T_B16, 0xAE); }
void vfnmsub213ph(Xmm x1, Xmm x2, const Operand& op) { opAVX_X_X_XM(x1, x2, op, T_66|T_MAP6|T_W0|T_YMM|T_ER_Z|T_MUST_EVEX|T_B16, 0xAE); }
void vfnmsub213sh(Xmm x1, Xmm x2, const Operand& op) { opAVX_X_X_XM(x1, x2, op, T_N2|T_66|T_MAP6|T_W0|T_ER_X|T_MUST_EVEX, 0xAF); }
void vfnmsub231bf16(Xmm x1, Xmm x2, const Operand& op) { opAVX_X_X_XM(x1, x2, op, T_MAP6|T_W0|T_YMM|T_MUST_EVEX|T_B16, 0xBE); }
void vfnmsub231ph(Xmm x1, Xmm x2, const Operand& op) { opAVX_X_X_XM(x1, x2, op, T_66|T_MAP6|T_W0|T_YMM|T_ER_Z|T_MUST_EVEX|T_B16, 0xBE); }
void vfnmsub231sh(Xmm x1, Xmm x2, const Operand& op) { opAVX_X_X_XM(x1, x2, op, T_N2|T_66|T_MAP6|T_W0|T_ER_X|T_MUST_EVEX, 0xBF); }
void vfpclassbf16(const Opmask& k, const Operand& op, uint8_t imm) { opVex(k.changeBit(op.getBit()), 0, op, T_MUST_EVEX|T_F2|T_0F3A|T_W0|T_YMM|T_B16, 0x66, imm); }
void vfpclasspd(const Opmask& k, const Operand& op, uint8_t imm) { if (!op.isBit(128|256|512)) XBYAK_THROW(ERR_BAD_MEM_SIZE) opVex(k.changeBit(op.getBit()), 0, op, T_66 | T_0F3A | T_MUST_EVEX | T_YMM | T_EW1 | T_B64, 0x66, imm); }
void vfpclassph(const Opmask& k, const Operand& op, uint8_t imm) { if (!op.isBit(128|256|512)) XBYAK_THROW(ERR_BAD_MEM_SIZE) opVex(k.changeBit(op.getBit()), 0, op, T_0F3A | T_MUST_EVEX | T_YMM | T_W0 | T_B16, 0x66, imm); }
void vfpclassps(const Opmask& k, const Operand& op, uint8_t imm) { if (!op.isBit(128|256|512)) XBYAK_THROW(ERR_BAD_MEM_SIZE) opVex(k.changeBit(op.getBit()), 0, op, T_66 | T_0F3A | T_MUST_EVEX | T_YMM | T_W0 | T_B32, 0x66, imm); }
void vfpclasssd(const Opmask& k, const Operand& op, uint8_t imm) { if (!op.isXMEM()) XBYAK_THROW(ERR_BAD_MEM_SIZE) opVex(k, 0, op, T_66 | T_0F3A | T_MUST_EVEX | T_EW1 | T_N8, 0x67, imm); }
void vfpclasssh(const Opmask& k, const Operand& op, uint8_t imm) { if (!op.isXMEM()) XBYAK_THROW(ERR_BAD_MEM_SIZE) opVex(k, 0, op, T_0F3A | T_MUST_EVEX | T_W0 | T_N2, 0x67, imm); }
void vfpclassss(const Opmask& k, const Operand& op, uint8_t imm) { if (!op.isXMEM()) XBYAK_THROW(ERR_BAD_MEM_SIZE) opVex(k, 0, op, T_66 | T_0F3A | T_MUST_EVEX | T_W0 | T_N4, 0x67, imm); }
void vgatherdpd(Xmm x, const Address& addr) { opGather2(x, addr, T_N8|T_66|T_0F38|T_EW1|T_YMM|T_MUST_EVEX|T_VSIB, 0x92, 1); }
void vgatherdps(Xmm x, const Address& addr) { opGather2(x, addr, T_N4|T_66|T_0F38|T_W0|T_YMM|T_MUST_EVEX|T_VSIB, 0x92, 0); }
void vgatherpf0dpd(const Address& addr) { opGatherFetch(addr, zm1, T_N8|T_66|T_0F38|T_EW1|T_MUST_EVEX|T_M_K|T_VSIB, 0xC6, Operand::YMM); }
void vgatherpf0dps(const Address& addr) { opGatherFetch(addr, zm1, T_N4|T_66|T_0F38|T_W0|T_MUST_EVEX|T_M_K|T_VSIB, 0xC6, Operand::ZMM); }
void vgatherpf0qpd(const Address& addr) { opGatherFetch(addr, zm1, T_N8|T_66|T_0F38|T_EW1|T_MUST_EVEX|T_M_K|T_VSIB, 0xC7, Operand::ZMM); }
void vgatherpf0qps(const Address& addr) { opGatherFetch(addr, zm1, T_N4|T_66|T_0F38|T_W0|T_MUST_EVEX|T_M_K|T_VSIB, 0xC7, Operand::ZMM); }
void vgatherpf1dpd(const Address& addr) { opGatherFetch(addr, zm2, T_N8|T_66|T_0F38|T_EW1|T_MUST_EVEX|T_M_K|T_VSIB, 0xC6, Operand::YMM); }
void vgatherpf1dps(const Address& addr) { opGatherFetch(addr, zm2, T_N4|T_66|T_0F38|T_W0|T_MUST_EVEX|T_M_K|T_VSIB, 0xC6, Operand::ZMM); }
void vgatherpf1qpd(const Address& addr) { opGatherFetch(addr, zm2, T_N8|T_66|T_0F38|T_EW1|T_MUST_EVEX|T_M_K|T_VSIB, 0xC7, Operand::ZMM); }
void vgatherpf1qps(const Address& addr) { opGatherFetch(addr, zm2, T_N4|T_66|T_0F38|T_W0|T_MUST_EVEX|T_M_K|T_VSIB, 0xC7, Operand::ZMM); }
void vgatherqpd(Xmm x, const Address& addr) { opGather2(x, addr, T_N8|T_66|T_0F38|T_EW1|T_YMM|T_MUST_EVEX|T_VSIB, 0x93, 0); }
void vgatherqps(Xmm x, const Address& addr) { opGather2(x, addr, T_N4|T_66|T_0F38|T_W0|T_YMM|T_MUST_EVEX|T_VSIB, 0x93, 2); }
void vgetexpbf16(Xmm x, const Operand& op) { opAVX_X_XM_IMM(x, op, T_MAP6|T_W0|T_YMM|T_MUST_EVEX|T_B16, 0x42); }
void vgetexppd(Xmm x, const Operand& op) { opAVX_X_XM_IMM(x, op, T_66|T_0F38|T_EW1|T_YMM|T_SAE_Z|T_MUST_EVEX|T_B64, 0x42); }
void vgetexpph(Xmm x, const Operand& op) { opAVX_X_XM_IMM(x, op, T_66|T_MAP6|T_W0|T_YMM|T_SAE_Z|T_MUST_EVEX|T_B16, 0x42); }
void vgetexpps(Xmm x, const Operand& op) { opAVX_X_XM_IMM(x, op, T_66|T_0F38|T_W0|T_YMM|T_SAE_Z|T_MUST_EVEX|T_B32, 0x42); }
void vgetexpsd(Xmm x1, Xmm x2, const Operand& op) { opAVX_X_X_XM(x1, x2, op, T_N8|T_66|T_0F38|T_EW1|T_SAE_X|T_MUST_EVEX, 0x43); }
void vgetexpsh(Xmm x1, Xmm x2, const Operand& op) { opAVX_X_X_XM(x1, x2, op, T_N2|T_66|T_MAP6|T_W0|T_SAE_X|T_MUST_EVEX, 0x43); }
void vgetexpss(Xmm x1, Xmm x2, const Operand& op) { opAVX_X_X_XM(x1, x2, op, T_N4|T_66|T_0F38|T_W0|T_SAE_X|T_MUST_EVEX, 0x43); }
void vgetmantbf16(Xmm x, const Operand& op, uint8_t imm) { opAVX_X_XM_IMM(x, op, T_F2|T_0F3A|T_W0|T_YMM|T_MUST_EVEX|T_B16, 0x26, imm); }
void vgetmantpd(Xmm x, const Operand& op, uint8_t imm) { opAVX_X_XM_IMM(x, op, T_66|T_0F3A|T_EW1|T_YMM|T_SAE_Z|T_MUST_EVEX|T_B64, 0x26, imm); }
void vgetmantph(Xmm x, const Operand& op, uint8_t imm) { opAVX_X_XM_IMM(x, op, T_0F3A|T_W0|T_YMM|T_SAE_Z|T_MUST_EVEX|T_B16, 0x26, imm); }
void vgetmantps(Xmm x, const Operand& op, uint8_t imm) { opAVX_X_XM_IMM(x, op, T_66|T_0F3A|T_W0|T_YMM|T_SAE_Z|T_MUST_EVEX|T_B32, 0x26, imm); }
void vgetmantsd(Xmm x1, Xmm x2, const Operand& op, uint8_t imm) { opAVX_X_X_XM(x1, x2, op, T_N8|T_66|T_0F3A|T_EW1|T_SAE_X|T_MUST_EVEX, 0x27, imm); }
void vgetmantsh(Xmm x1, Xmm x2, const Operand& op, uint8_t imm) { opAVX_X_X_XM(x1, x2, op, T_N2|T_0F3A|T_W0|T_SAE_X|T_MUST_EVEX, 0x27, imm); }
void vgetmantss(Xmm x1, Xmm x2, const Operand& op, uint8_t imm) { opAVX_X_X_XM(x1, x2, op, T_N4|T_66|T_0F3A|T_W0|T_SAE_X|T_MUST_EVEX, 0x27, imm); }
void vinsertf32x4(Ymm r1, Ymm r2, const Operand& op, uint8_t imm) {if (!(r1.getKind() == r2.getKind() && op.is(Operand::MEM | Operand::XMM))) XBYAK_THROW(ERR_BAD_COMBINATION) opVex(r1, &r2, op, T_N16|T_66|T_0F3A|T_W0|T_YMM|T_MUST_EVEX, 0x18, imm); }
void vinsertf32x8(Zmm r1, Zmm r2, const Operand& op, uint8_t imm) {if (!op.is(Operand::MEM | Operand::YMM)) XBYAK_THROW(ERR_BAD_COMBINATION) opVex(r1, &r2, op, T_N32|T_66|T_0F3A|T_W0|T_YMM|T_MUST_EVEX, 0x1A, imm); }
void vinsertf64x2(Ymm r1, Ymm r2, const Operand& op, uint8_t imm) {if (!(r1.getKind() == r2.getKind() && op.is(Operand::MEM | Operand::XMM))) XBYAK_THROW(ERR_BAD_COMBINATION) opVex(r1, &r2, op, T_N16|T_66|T_0F3A|T_EW1|T_YMM|T_MUST_EVEX, 0x18, imm); }
void vinsertf64x4(Zmm r1, Zmm r2, const Operand& op, uint8_t imm) {if (!op.is(Operand::MEM | Operand::YMM)) XBYAK_THROW(ERR_BAD_COMBINATION) opVex(r1, &r2, op, T_N32|T_66|T_0F3A|T_EW1|T_YMM|T_MUST_EVEX, 0x1A, imm); }
void vinserti32x4(Ymm r1, Ymm r2, const Operand& op, uint8_t imm) {if (!(r1.getKind() == r2.getKind() && op.is(Operand::MEM | Operand::XMM))) XBYAK_THROW(ERR_BAD_COMBINATION) opVex(r1, &r2, op, T_N16|T_66|T_0F3A|T_W0|T_YMM|T_MUST_EVEX, 0x38, imm); }
void vinserti32x8(Zmm r1, Zmm r2, const Operand& op, uint8_t imm) {if (!op.is(Operand::MEM | Operand::YMM)) XBYAK_THROW(ERR_BAD_COMBINATION) opVex(r1, &r2, op, T_N32|T_66|T_0F3A|T_W0|T_YMM|T_MUST_EVEX, 0x3A, imm); }
void vinserti64x2(Ymm r1, Ymm r2, const Operand& op, uint8_t imm) {if (!(r1.getKind() == r2.getKind() && op.is(Operand::MEM | Operand::XMM))) XBYAK_THROW(ERR_BAD_COMBINATION) opVex(r1, &r2, op, T_N16|T_66|T_0F3A|T_EW1|T_YMM|T_MUST_EVEX, 0x38, imm); }
void vinserti64x4(Zmm r1, Zmm r2, const Operand& op, uint8_t imm) {if (!op.is(Operand::MEM | Operand::YMM)) XBYAK_THROW(ERR_BAD_COMBINATION) opVex(r1, &r2, op, T_N32|T_66|T_0F3A|T_EW1|T_YMM|T_MUST_EVEX, 0x3A, imm); }
void vmaxbf16(Xmm x1, Xmm x2, const Operand& op) { opAVX_X_X_XM(x1, x2, op, T_66|T_MAP5|T_W0|T_YMM|T_MUST_EVEX|T_B16, 0x5F); }
void vmaxph(Xmm xmm, const Operand& op1, const Operand& op2 = Operand()) { opAVX_X_X_XM(xmm, op1, op2, T_MAP5 | T_W0 | T_YMM | T_MUST_EVEX | T_SAE_Z | T_B16, 0x5F); }
void vmaxsh(Xmm xmm, const Operand& op1, const Operand& op2 = Operand()) { opAVX_X_X_XM(xmm, op1, op2, T_MAP5 | T_F3 | T_W0 | T_MUST_EVEX | T_SAE_X | T_N2, 0x5F); }
void vminbf16(Xmm x1, Xmm x2, const Operand& op) { opAVX_X_X_XM(x1, x2, op, T_66|T_MAP5|T_W0|T_YMM|T_MUST_EVEX|T_B16, 0x5D); }
void vminmaxbf16(Xmm x1, Xmm x2, const Operand& op, uint8_t imm) { opAVX_X_X_XM(x1, x2, op, T_F2|T_0F3A|T_W0|T_YMM|T_MUST_EVEX|T_B16, 0x52, imm); }
void vminmaxpd(Xmm x1, Xmm x2, const Operand& op, uint8_t imm) { opAVX_X_X_XM(x1, x2, op, T_66|T_0F3A|T_EW1|T_YMM|T_SAE_Z|T_MUST_EVEX|T_B64, 0x52, imm); }
void vminmaxph(Xmm x1, Xmm x2, const Operand& op, uint8_t imm) { opAVX_X_X_XM(x1, x2, op, T_0F3A|T_W0|T_YMM|T_SAE_Z|T_MUST_EVEX|T_B16, 0x52, imm); }
void vminmaxps(Xmm x1, Xmm x2, const Operand& op, uint8_t imm) { opAVX_X_X_XM(x1, x2, op, T_66|T_0F3A|T_W0|T_YMM|T_SAE_Z|T_MUST_EVEX|T_B32, 0x52, imm); }
void vminmaxsd(Xmm x1, Xmm x2, const Operand& op, uint8_t imm) { opAVX_X_X_XM(x1, x2, op, T_N8|T_66|T_0F3A|T_EW1|T_SAE_X|T_MUST_EVEX, 0x53, imm); }
void vminmaxsh(Xmm x1, Xmm x2, const Operand& op, uint8_t imm) { opAVX_X_X_XM(x1, x2, op, T_N2|T_0F3A|T_W0|T_SAE_X|T_MUST_EVEX, 0x53, imm); }
void vminmaxss(Xmm x1, Xmm x2, const Operand& op, uint8_t imm) { opAVX_X_X_XM(x1, x2, op, T_N4|T_66|T_0F3A|T_W0|T_SAE_X|T_MUST_EVEX, 0x53, imm); }
void vminph(Xmm xmm, const Operand& op1, const Operand& op2 = Operand()) { opAVX_X_X_XM(xmm, op1, op2, T_MAP5 | T_W0 | T_YMM | T_MUST_EVEX | T_SAE_Z | T_B16, 0x5D); }
void vminsh(Xmm xmm, const Operand& op1, const Operand& op2 = Operand()) { opAVX_X_X_XM(xmm, op1, op2, T_MAP5 | T_F3 | T_W0 | T_MUST_EVEX | T_SAE_X | T_N2, 0x5D); }
void vmovdqa32(const Address& addr, Xmm x) { opAVX_X_XM_IMM(x, addr, T_66|T_0F|T_W0|T_YMM|T_MUST_EVEX|T_M_K, 0x7F); }
void vmovdqa32(Xmm x, const Operand& op) { opAVX_X_XM_IMM(x, op, T_66|T_0F|T_W0|T_YMM|T_MUST_EVEX, 0x6F); }
void vmovdqa64(const Address& addr, Xmm x) { opAVX_X_XM_IMM(x, addr, T_66|T_0F|T_EW1|T_YMM|T_MUST_EVEX|T_M_K, 0x7F); }
void vmovdqa64(Xmm x, const Operand& op) { opAVX_X_XM_IMM(x, op, T_66|T_0F|T_EW1|T_YMM|T_MUST_EVEX, 0x6F); }
void vmovdqu16(const Address& addr, Xmm x) { opAVX_X_XM_IMM(x, addr, T_F2|T_0F|T_EW1|T_YMM|T_MUST_EVEX|T_M_K, 0x7F); }
void vmovdqu16(Xmm x, const Operand& op) { opAVX_X_XM_IMM(x, op, T_F2|T_0F|T_EW1|T_YMM|T_MUST_EVEX, 0x6F); }
void vmovdqu32(const Address& addr, Xmm x) { opAVX_X_XM_IMM(x, addr, T_F3|T_0F|T_W0|T_YMM|T_MUST_EVEX|T_M_K, 0x7F); }
void vmovdqu32(Xmm x, const Operand& op) { opAVX_X_XM_IMM(x, op, T_F3|T_0F|T_W0|T_YMM|T_MUST_EVEX, 0x6F); }
void vmovdqu64(const Address& addr, Xmm x) { opAVX_X_XM_IMM(x, addr, T_F3|T_0F|T_EW1|T_YMM|T_MUST_EVEX|T_M_K, 0x7F); }
void vmovdqu64(Xmm x, const Operand& op) { opAVX_X_XM_IMM(x, op, T_F3|T_0F|T_EW1|T_YMM|T_MUST_EVEX, 0x6F); }
void vmovdqu8(const Address& addr, Xmm x) { opAVX_X_XM_IMM(x, addr, T_F2|T_0F|T_W0|T_YMM|T_MUST_EVEX|T_M_K, 0x7F); }
void vmovdqu8(Xmm x, const Operand& op) { opAVX_X_XM_IMM(x, op, T_F2|T_0F|T_W0|T_YMM|T_MUST_EVEX, 0x6F); }
void vmovsh(const Address& addr, Xmm x) { opAVX_X_XM_IMM(x, addr, T_N2|T_F3|T_MAP5|T_W0|T_MUST_EVEX|T_M_K, 0x11); }
void vmovsh(Xmm x, const Address& addr) { opAVX_X_X_XM(x, xm0, addr, T_N2|T_F3|T_MAP5|T_W0|T_MUST_EVEX, 0x10); }
void vmovsh(Xmm x1, Xmm x2, Xmm x3) { opAVX_X_X_XM(x1, x2, x3, T_N2|T_F3|T_MAP5|T_W0|T_MUST_EVEX, 0x10); }
void vmpsadbw(Xmm x1, Xmm x2, const Operand& op, uint8_t imm, PreferredEncoding encoding = DefaultEncoding) { opEncoding(x1, x2, op, T_0F3A|T_YMM, 0x42, encoding, imm, T_66|T_YMM, T_F3|T_0F3A|T_B32, 1); }
void vmulbf16(Xmm x1, Xmm x2, const Operand& op) { opAVX_X_X_XM(x1, x2, op, T_66|T_MAP5|T_W0|T_YMM|T_MUST_EVEX|T_B16, 0x59); }
void vmulph(Xmm xmm, const Operand& op1, const Operand& op2 = Operand()) { opAVX_X_X_XM(xmm, op1, op2, T_MAP5 | T_W0 | T_YMM | T_MUST_EVEX | T_ER_Z | T_B16, 0x59); }
void vmulsh(Xmm xmm, const Operand& op1, const Operand& op2 = Operand()) { opAVX_X_X_XM(xmm, op1, op2, T_MAP5 | T_F3 | T_W0 | T_MUST_EVEX | T_ER_X | T_N2, 0x59); }
void vp2intersectd(const Opmask& k, Xmm x, const Operand& op) { if (k.getOpmaskIdx() != 0) XBYAK_THROW(ERR_OPMASK_IS_ALREADY_SET) opAVX_K_X_XM(k, x, op, T_F2 | T_0F38 | T_YMM | T_EVEX | T_W0 | T_B32, 0x68); }
void vp2intersectq(const Opmask& k, Xmm x, const Operand& op) { if (k.getOpmaskIdx() != 0) XBYAK_THROW(ERR_OPMASK_IS_ALREADY_SET) opAVX_K_X_XM(k, x, op, T_F2 | T_0F38 | T_YMM | T_EVEX | T_EW1 | T_B64, 0x68); }
void vp4dpwssd(Zmm z1, Zmm z2, const Address& addr) { opAVX_X_X_XM(z1, z2, addr, T_0F38 | T_F2 | T_W0 | T_YMM | T_MUST_EVEX | T_N16, 0x52); }
void vp4dpwssds(Zmm z1, Zmm z2, const Address& addr) { opAVX_X_X_XM(z1, z2, addr, T_0F38 | T_F2 | T_W0 | T_YMM | T_MUST_EVEX | T_N16, 0x53); }
void vpabsq(Xmm x, const Operand& op) { opAVX_X_XM_IMM(x, op, T_66 | T_0F38 | T_MUST_EVEX | T_EW1 | T_B64 | T_YMM, 0x1F); }
void vpandd(Xmm x1, Xmm x2, const Operand& op) { opAVX_X_X_XM(x1, x2, op, T_66|T_0F|T_W0|T_YMM|T_MUST_EVEX|T_B32, 0xDB); }
void vpandnd(Xmm x1, Xmm x2, const Operand& op) { opAVX_X_X_XM(x1, x2, op, T_66|T_0F|T_W0|T_YMM|T_MUST_EVEX|T_B32, 0xDF); }
void vpandnq(Xmm x1, Xmm x2, const Operand& op) { opAVX_X_X_XM(x1, x2, op, T_66|T_0F|T_EW1|T_YMM|T_MUST_EVEX|T_B64, 0xDF); }
void vpandq(Xmm x1, Xmm x2, const Operand& op) { opAVX_X_X_XM(x1, x2, op, T_66|T_0F|T_EW1|T_YMM|T_MUST_EVEX|T_B64, 0xDB); }
void vpblendmb(Xmm x1, Xmm x2, const Operand& op) { opAVX_X_X_XM(x1, x2, op, T_66|T_0F38|T_W0|T_YMM|T_MUST_EVEX, 0x66); }
void vpblendmd(Xmm x1, Xmm x2, const Operand& op) { opAVX_X_X_XM(x1, x2, op, T_66|T_0F38|T_W0|T_YMM|T_MUST_EVEX|T_B32, 0x64); }
void vpblendmq(Xmm x1, Xmm x2, const Operand& op) { opAVX_X_X_XM(x1, x2, op, T_66|T_0F38|T_EW1|T_YMM|T_MUST_EVEX|T_B64, 0x64); }
void vpblendmw(Xmm x1, Xmm x2, const Operand& op) { opAVX_X_X_XM(x1, x2, op, T_66|T_0F38|T_EW1|T_YMM|T_MUST_EVEX, 0x66); }
void vpbroadcastb(Xmm x, Reg8 r) { opVex(x, 0, r, T_66|T_0F38|T_W0|T_YMM|T_MUST_EVEX, 0x7A); }
void vpbroadcastd(Xmm x, Reg32 r) { opVex(x, 0, r, T_66|T_0F38|T_W0|T_YMM|T_MUST_EVEX, 0x7C); }
void vpbroadcastmb2q(Xmm x, const Opmask& k) { opVex(x, 0, k, T_F3 | T_0F38 | T_YMM | T_MUST_EVEX | T_EW1, 0x2A); }
void vpbroadcastmw2d(Xmm x, const Opmask& k) { opVex(x, 0, k, T_F3 | T_0F38 | T_YMM | T_MUST_EVEX | T_W0, 0x3A); }
void vpbroadcastw(Xmm x, Reg16 r) { opVex(x, 0, r, T_66|T_0F38|T_W0|T_YMM|T_MUST_EVEX, 0x7B); }
void vpcmpb(const Opmask& k, Xmm x, const Operand& op, uint8_t imm) { opAVX_K_X_XM(k, x, op, T_66|T_0F3A|T_W0|T_YMM|T_MUST_EVEX, 0x3F, imm); }
void vpcmpd(const Opmask& k, Xmm x, const Operand& op, uint8_t imm) { opAVX_K_X_XM(k, x, op, T_66|T_0F3A|T_W0|T_YMM|T_MUST_EVEX|T_B32, 0x1F, imm); }
void vpcmpeqb(const Opmask& k, Xmm x, const Operand& op) { opAVX_K_X_XM(k, x, op, T_66|T_0F|T_YMM|T_MUST_EVEX, 0x74); }
void vpcmpeqd(const Opmask& k, Xmm x, const Operand& op) { opAVX_K_X_XM(k, x, op, T_66|T_0F|T_YMM|T_MUST_EVEX|T_B32, 0x76); }
void vpcmpeqq(const Opmask& k, Xmm x, const Operand& op) { opAVX_K_X_XM(k, x, op, T_66|T_0F38|T_EW1|T_YMM|T_MUST_EVEX|T_B64, 0x29); }
void vpcmpeqw(const Opmask& k, Xmm x, const Operand& op) { opAVX_K_X_XM(k, x, op, T_66|T_0F|T_YMM|T_MUST_EVEX, 0x75); }
void vpcmpgtb(const Opmask& k, Xmm x, const Operand& op) { opAVX_K_X_XM(k, x, op, T_66|T_0F|T_YMM|T_MUST_EVEX, 0x64); }
void vpcmpgtd(const Opmask& k, Xmm x, const Operand& op) { opAVX_K_X_XM(k, x, op, T_66|T_0F|T_W0|T_YMM|T_MUST_EVEX|T_B32, 0x66); }
void vpcmpgtq(const Opmask& k, Xmm x, const Operand& op) { opAVX_K_X_XM(k, x, op, T_66|T_0F38|T_EW1|T_YMM|T_MUST_EVEX|T_B64, 0x37); }
void vpcmpgtw(const Opmask& k, Xmm x, const Operand& op) { opAVX_K_X_XM(k, x, op, T_66|T_0F|T_YMM|T_MUST_EVEX, 0x65); }
void vpcmpq(const Opmask& k, Xmm x, const Operand& op, uint8_t imm) { opAVX_K_X_XM(k, x, op, T_66|T_0F3A|T_EW1|T_YMM|T_MUST_EVEX|T_B64, 0x1F, imm); }
void vpcmpub(const Opmask& k, Xmm x, const Operand& op, uint8_t imm) { opAVX_K_X_XM(k, x, op, T_66|T_0F3A|T_W0|T_YMM|T_MUST_EVEX, 0x3E, imm); }
void vpcmpud(const Opmask& k, Xmm x, const Operand& op, uint8_t imm) { opAVX_K_X_XM(k, x, op, T_66|T_0F3A|T_W0|T_YMM|T_MUST_EVEX|T_B32, 0x1E, imm); }
void vpcmpuq(const Opmask& k, Xmm x, const Operand& op, uint8_t imm) { opAVX_K_X_XM(k, x, op, T_66|T_0F3A|T_EW1|T_YMM|T_MUST_EVEX|T_B64, 0x1E, imm); }
void vpcmpuw(const Opmask& k, Xmm x, const Operand& op, uint8_t imm) { opAVX_K_X_XM(k, x, op, T_66|T_0F3A|T_EW1|T_YMM|T_MUST_EVEX, 0x3E, imm); }
void vpcmpw(const Opmask& k, Xmm x, const Operand& op, uint8_t imm) { opAVX_K_X_XM(k, x, op, T_66|T_0F3A|T_EW1|T_YMM|T_MUST_EVEX, 0x3F, imm); }
void vpcompressb(const Operand& op, Xmm x) { opAVX_X_XM_IMM(x, op, T_N1|T_66|T_0F38|T_W0|T_YMM|T_MUST_EVEX, 0x63); }
void vpcompressd(const Operand& op, Xmm x) { opAVX_X_XM_IMM(x, op, T_N4|T_66|T_0F38|T_W0|T_YMM|T_MUST_EVEX, 0x8B); }
void vpcompressq(const Operand& op, Xmm x) { opAVX_X_XM_IMM(x, op, T_N8|T_66|T_0F38|T_EW1|T_YMM|T_MUST_EVEX, 0x8B); }
void vpcompressw(const Operand& op, Xmm x) { opAVX_X_XM_IMM(x, op, T_N2|T_66|T_0F38|T_EW1|T_YMM|T_MUST_EVEX, 0x63); }
void vpconflictd(Xmm x, const Operand& op) { opAVX_X_XM_IMM(x, op, T_66|T_0F38|T_W0|T_YMM|T_MUST_EVEX|T_B32, 0xC4); }
void vpconflictq(Xmm x, const Operand& op) { opAVX_X_XM_IMM(x, op, T_66|T_0F38|T_EW1|T_YMM|T_MUST_EVEX|T_B64, 0xC4); }
void vpdpbssd(Xmm x1, Xmm x2, const Operand& op, PreferredEncoding encoding = DefaultEncoding) { opEncoding(x1, x2, op, T_F2|T_0F38|T_W0|T_YMM, 0x50, encoding, NONE, T_NONE, T_B32, 1); }
void vpdpbssds(Xmm x1, Xmm x2, const Operand& op, PreferredEncoding encoding = DefaultEncoding) { opEncoding(x1, x2, op, T_F2|T_0F38|T_W0|T_YMM, 0x51, encoding, NONE, T_NONE, T_B32, 1); }
void vpdpbsud(Xmm x1, Xmm x2, const Operand& op, PreferredEncoding encoding = DefaultEncoding) { opEncoding(x1, x2, op, T_F3|T_0F38|T_W0|T_YMM, 0x50, encoding, NONE, T_NONE, T_B32, 1); }
void vpdpbsuds(Xmm x1, Xmm x2, const Operand& op, PreferredEncoding encoding = DefaultEncoding) { opEncoding(x1, x2, op, T_F3|T_0F38|T_W0|T_YMM, 0x51, encoding, NONE, T_NONE, T_B32, 1); }
void vpdpbuud(Xmm x1, Xmm x2, const Operand& op, PreferredEncoding encoding = DefaultEncoding) { opEncoding(x1, x2, op, T_0F38|T_W0|T_YMM, 0x50, encoding, NONE, T_NONE, T_B32, 1); }
void vpdpbuuds(Xmm x1, Xmm x2, const Operand& op, PreferredEncoding encoding = DefaultEncoding) { opEncoding(x1, x2, op, T_0F38|T_W0|T_YMM, 0x51, encoding, NONE, T_NONE, T_B32, 1); }
void vpdpwsud(Xmm x1, Xmm x2, const Operand& op, PreferredEncoding encoding = DefaultEncoding) { opEncoding(x1, x2, op, T_F3|T_0F38|T_W0|T_YMM, 0xD2, encoding, NONE, T_NONE, T_B32, 1); }
void vpdpwsuds(Xmm x1, Xmm x2, const Operand& op, PreferredEncoding encoding = DefaultEncoding) { opEncoding(x1, x2, op, T_F3|T_0F38|T_W0|T_YMM, 0xD3, encoding, NONE, T_NONE, T_B32, 1); }
void vpdpwusd(Xmm x1, Xmm x2, const Operand& op, PreferredEncoding encoding = DefaultEncoding) { opEncoding(x1, x2, op, T_66|T_0F38|T_W0|T_YMM, 0xD2, encoding, NONE, T_NONE, T_B32, 1); }
void vpdpwusds(Xmm x1, Xmm x2, const Operand& op, PreferredEncoding encoding = DefaultEncoding) { opEncoding(x1, x2, op, T_66|T_0F38|T_W0|T_YMM, 0xD3, encoding, NONE, T_NONE, T_B32, 1); }
void vpdpwuud(Xmm x1, Xmm x2, const Operand& op, PreferredEncoding encoding = DefaultEncoding) { opEncoding(x1, x2, op, T_0F38|T_W0|T_YMM, 0xD2, encoding, NONE, T_NONE, T_B32, 1); }
void vpdpwuuds(Xmm x1, Xmm x2, const Operand& op, PreferredEncoding encoding = DefaultEncoding) { opEncoding(x1, x2, op, T_0F38|T_W0|T_YMM, 0xD3, encoding, NONE, T_NONE, T_B32, 1); }
void vpermb(Xmm x1, Xmm x2, const Operand& op) { opAVX_X_X_XM(x1, x2, op, T_66|T_0F38|T_W0|T_YMM|T_MUST_EVEX, 0x8D); }
void vpermi2b(Xmm x1, Xmm x2, const Operand& op) { opAVX_X_X_XM(x1, x2, op, T_66|T_0F38|T_W0|T_YMM|T_MUST_EVEX, 0x75); }
void vpermi2d(Xmm x1, Xmm x2, const Operand& op) { opAVX_X_X_XM(x1, x2, op, T_66|T_0F38|T_W0|T_YMM|T_MUST_EVEX|T_B32, 0x76); }
void vpermi2pd(Xmm x1, Xmm x2, const Operand& op) { opAVX_X_X_XM(x1, x2, op, T_66|T_0F38|T_EW1|T_YMM|T_MUST_EVEX|T_B64, 0x77); }
void vpermi2ps(Xmm x1, Xmm x2, const Operand& op) { opAVX_X_X_XM(x1, x2, op, T_66|T_0F38|T_W0|T_YMM|T_MUST_EVEX|T_B32, 0x77); }
void vpermi2q(Xmm x1, Xmm x2, const Operand& op) { opAVX_X_X_XM(x1, x2, op, T_66|T_0F38|T_EW1|T_YMM|T_MUST_EVEX|T_B64, 0x76); }
void vpermi2w(Xmm x1, Xmm x2, const Operand& op) { opAVX_X_X_XM(x1, x2, op, T_66|T_0F38|T_EW1|T_YMM|T_MUST_EVEX, 0x75); }
void vpermt2b(Xmm x1, Xmm x2, const Operand& op) { opAVX_X_X_XM(x1, x2, op, T_66|T_0F38|T_W0|T_YMM|T_MUST_EVEX, 0x7D); }
void vpermt2d(Xmm x1, Xmm x2, const Operand& op) { opAVX_X_X_XM(x1, x2, op, T_66|T_0F38|T_W0|T_YMM|T_MUST_EVEX|T_B32, 0x7E); }
void vpermt2pd(Xmm x1, Xmm x2, const Operand& op) { opAVX_X_X_XM(x1, x2, op, T_66|T_0F38|T_EW1|T_YMM|T_MUST_EVEX|T_B64, 0x7F); }
void vpermt2ps(Xmm x1, Xmm x2, const Operand& op) { opAVX_X_X_XM(x1, x2, op, T_66|T_0F38|T_W0|T_YMM|T_MUST_EVEX|T_B32, 0x7F); }
void vpermt2q(Xmm x1, Xmm x2, const Operand& op) { opAVX_X_X_XM(x1, x2, op, T_66|T_0F38|T_EW1|T_YMM|T_MUST_EVEX|T_B64, 0x7E); }
void vpermt2w(Xmm x1, Xmm x2, const Operand& op) { opAVX_X_X_XM(x1, x2, op, T_66|T_0F38|T_EW1|T_YMM|T_MUST_EVEX, 0x7D); }
void vpermw(Xmm x1, Xmm x2, const Operand& op) { opAVX_X_X_XM(x1, x2, op, T_66|T_0F38|T_EW1|T_YMM|T_MUST_EVEX, 0x8D); }
void vpexpandb(Xmm x, const Operand& op) { opAVX_X_XM_IMM(x, op, T_N1|T_66|T_0F38|T_W0|T_YMM|T_SAE_Z|T_MUST_EVEX, 0x62); }
void vpexpandd(Xmm x, const Operand& op) { opAVX_X_XM_IMM(x, op, T_N4|T_66|T_0F38|T_W0|T_YMM|T_MUST_EVEX, 0x89); }
void vpexpandq(Xmm x, const Operand& op) { opAVX_X_XM_IMM(x, op, T_N8|T_66|T_0F38|T_EW1|T_YMM|T_MUST_EVEX, 0x89); }
void vpexpandw(Xmm x, const Operand& op) { opAVX_X_XM_IMM(x, op, T_N2|T_66|T_0F38|T_EW1|T_YMM|T_SAE_Z|T_MUST_EVEX, 0x62); }
void vpgatherdd(Xmm x, const Address& addr) { opGather2(x, addr, T_N4|T_66|T_0F38|T_W0|T_YMM|T_MUST_EVEX|T_VSIB, 0x90, 0); }
void vpgatherdq(Xmm x, const Address& addr) { opGather2(x, addr, T_N8|T_66|T_0F38|T_EW1|T_YMM|T_MUST_EVEX|T_VSIB, 0x90, 1); }
void vpgatherqd(Xmm x, const Address& addr) { opGather2(x, addr, T_N4|T_66|T_0F38|T_W0|T_YMM|T_MUST_EVEX|T_VSIB, 0x91, 2); }
void vpgatherqq(Xmm x, const Address& addr) { opGather2(x, addr, T_N8|T_66|T_0F38|T_EW1|T_YMM|T_MUST_EVEX|T_VSIB, 0x91, 0); }
void vplzcntd(Xmm x, const Operand& op) { opAVX_X_XM_IMM(x, op, T_66|T_0F38|T_W0|T_YMM|T_MUST_EVEX|T_B32, 0x44); }
void vplzcntq(Xmm x, const Operand& op) { opAVX_X_XM_IMM(x, op, T_66|T_0F38|T_EW1|T_YMM|T_MUST_EVEX|T_B64, 0x44); }
void vpmadd52huq(Xmm x1, Xmm x2, const Operand& op) { opAVX_X_X_XM(x1, x2, op, T_66|T_0F38|T_EW1|T_YMM|T_MUST_EVEX|T_B64, 0xB5); }
void vpmadd52luq(Xmm x1, Xmm x2, const Operand& op) { opAVX_X_X_XM(x1, x2, op, T_66|T_0F38|T_EW1|T_YMM|T_MUST_EVEX|T_B64, 0xB4); }
void vpmaxsq(Xmm x1, Xmm x2, const Operand& op) { opAVX_X_X_XM(x1, x2, op, T_66|T_0F38|T_EW1|T_YMM|T_MUST_EVEX|T_B64, 0x3D); }
void vpmaxuq(Xmm x1, Xmm x2, const Operand& op) { opAVX_X_X_XM(x1, x2, op, T_66|T_0F38|T_EW1|T_YMM|T_MUST_EVEX|T_B64, 0x3F); }
void vpminsq(Xmm x1, Xmm x2, const Operand& op) { opAVX_X_X_XM(x1, x2, op, T_66|T_0F38|T_EW1|T_YMM|T_MUST_EVEX|T_B64, 0x39); }
void vpminuq(Xmm x1, Xmm x2, const Operand& op) { opAVX_X_X_XM(x1, x2, op, T_66|T_0F38|T_EW1|T_YMM|T_MUST_EVEX|T_B64, 0x3B); }
void vpmovb2m(const Opmask& k, Xmm x) { opVex(k, 0, x, T_F3 | T_0F38 | T_MUST_EVEX | T_YMM | T_W0, 0x29); }
void vpmovd2m(const Opmask& k, Xmm x) { opVex(k, 0, x, T_F3 | T_0F38 | T_MUST_EVEX | T_YMM | T_W0, 0x39); }
void vpmovdb(const Operand& op, Xmm x) { opVmov(op, x, T_N4|T_N_VL|T_F3|T_0F38|T_W0|T_YMM|T_MUST_EVEX|T_M_K, 0x31, false); }
void vpmovdw(const Operand& op, Xmm x) { opVmov(op, x, T_N8|T_N_VL|T_F3|T_0F38|T_W0|T_YMM|T_MUST_EVEX|T_M_K, 0x33, true); }
void vpmovm2b(Xmm x, const Opmask& k) { opVex(x, 0, k, T_F3 | T_0F38 | T_MUST_EVEX | T_YMM | T_W0, 0x28); }
void vpmovm2d(Xmm x, const Opmask& k) { opVex(x, 0, k, T_F3 | T_0F38 | T_MUST_EVEX | T_YMM | T_W0, 0x38); }
void vpmovm2q(Xmm x, const Opmask& k) { opVex(x, 0, k, T_F3 | T_0F38 | T_MUST_EVEX | T_YMM | T_EW1, 0x38); }
void vpmovm2w(Xmm x, const Opmask& k) { opVex(x, 0, k, T_F3 | T_0F38 | T_MUST_EVEX | T_YMM | T_EW1, 0x28); }
void vpmovq2m(const Opmask& k, Xmm x) { opVex(k, 0, x, T_F3 | T_0F38 | T_MUST_EVEX | T_YMM | T_EW1, 0x39); }
void vpmovqb(const Operand& op, Xmm x) { opVmov(op, x, T_N2|T_N_VL|T_F3|T_0F38|T_W0|T_YMM|T_MUST_EVEX|T_M_K, 0x32, false); }
void vpmovqd(const Operand& op, Xmm x) { opVmov(op, x, T_N8|T_N_VL|T_F3|T_0F38|T_W0|T_YMM|T_MUST_EVEX|T_M_K, 0x35, true); }
void vpmovqw(const Operand& op, Xmm x) { opVmov(op, x, T_N4|T_N_VL|T_F3|T_0F38|T_W0|T_YMM|T_MUST_EVEX|T_M_K, 0x34, false); }
void vpmovsdb(const Operand& op, Xmm x) { opVmov(op, x, T_N4|T_N_VL|T_F3|T_0F38|T_W0|T_YMM|T_MUST_EVEX|T_M_K, 0x21, false); }
void vpmovsdw(const Operand& op, Xmm x) { opVmov(op, x, T_N8|T_N_VL|T_F3|T_0F38|T_W0|T_YMM|T_MUST_EVEX|T_M_K, 0x23, true); }
void vpmovsqb(const Operand& op, Xmm x) { opVmov(op, x, T_N2|T_N_VL|T_F3|T_0F38|T_W0|T_YMM|T_MUST_EVEX|T_M_K, 0x22, false); }
void vpmovsqd(const Operand& op, Xmm x) { opVmov(op, x, T_N8|T_N_VL|T_F3|T_0F38|T_W0|T_YMM|T_MUST_EVEX|T_M_K, 0x25, true); }
void vpmovsqw(const Operand& op, Xmm x) { opVmov(op, x, T_N4|T_N_VL|T_F3|T_0F38|T_W0|T_YMM|T_MUST_EVEX|T_M_K, 0x24, false); }
void vpmovswb(const Operand& op, Xmm x) { opVmov(op, x, T_N8|T_N_VL|T_F3|T_0F38|T_W0|T_YMM|T_MUST_EVEX|T_M_K, 0x20, true); }
void vpmovusdb(const Operand& op, Xmm x) { opVmov(op, x, T_N4|T_N_VL|T_F3|T_0F38|T_W0|T_YMM|T_MUST_EVEX|T_M_K, 0x11, false); }
void vpmovusdw(const Operand& op, Xmm x) { opVmov(op, x, T_N8|T_N_VL|T_F3|T_0F38|T_W0|T_YMM|T_MUST_EVEX|T_M_K, 0x13, true); }
void vpmovusqb(const Operand& op, Xmm x) { opVmov(op, x, T_N2|T_N_VL|T_F3|T_0F38|T_W0|T_YMM|T_MUST_EVEX|T_M_K, 0x12, false); }
void vpmovusqd(const Operand& op, Xmm x) { opVmov(op, x, T_N8|T_N_VL|T_F3|T_0F38|T_W0|T_YMM|T_MUST_EVEX|T_M_K, 0x15, true); }
void vpmovusqw(const Operand& op, Xmm x) { opVmov(op, x, T_N4|T_N_VL|T_F3|T_0F38|T_W0|T_YMM|T_MUST_EVEX|T_M_K, 0x14, false); }
void vpmovuswb(const Operand& op, Xmm x) { opVmov(op, x, T_N8|T_N_VL|T_F3|T_0F38|T_W0|T_YMM|T_MUST_EVEX|T_M_K, 0x10, true); }
void vpmovw2m(const Opmask& k, Xmm x) { opVex(k, 0, x, T_F3 | T_0F38 | T_MUST_EVEX | T_YMM | T_EW1, 0x29); }
void vpmovwb(const Operand& op, Xmm x) { opVmov(op, x, T_N8|T_N_VL|T_F3|T_0F38|T_W0|T_YMM|T_MUST_EVEX|T_M_K, 0x30, true); }
void vpmullq(Xmm x1, Xmm x2, const Operand& op) { opAVX_X_X_XM(x1, x2, op, T_66|T_0F38|T_EW1|T_YMM|T_MUST_EVEX|T_B64, 0x40); }
void vpmultishiftqb(Xmm x1, Xmm x2, const Operand& op) { opAVX_X_X_XM(x1, x2, op, T_66|T_0F38|T_EW1|T_YMM|T_MUST_EVEX|T_B64, 0x83); }
void vpopcntb(Xmm x, const Operand& op) { opAVX_X_XM_IMM(x, op, T_66|T_0F38|T_W0|T_YMM|T_SAE_Z|T_MUST_EVEX, 0x54); }
void vpopcntd(Xmm x, const Operand& op) { opAVX_X_XM_IMM(x, op, T_66|T_0F38|T_W0|T_YMM|T_SAE_Z|T_MUST_EVEX|T_B32, 0x55); }
void vpopcntq(Xmm x, const Operand& op) { opAVX_X_XM_IMM(x, op, T_66|T_0F38|T_EW1|T_YMM|T_SAE_Z|T_MUST_EVEX|T_B64, 0x55); }
void vpopcntw(Xmm x, const Operand& op) { opAVX_X_XM_IMM(x, op, T_66|T_0F38|T_EW1|T_YMM|T_SAE_Z|T_MUST_EVEX, 0x54); }
void vpord(Xmm x1, Xmm x2, const Operand& op) { opAVX_X_X_XM(x1, x2, op, T_66|T_0F|T_W0|T_YMM|T_MUST_EVEX|T_B32, 0xEB); }
void vporq(Xmm x1, Xmm x2, const Operand& op) { opAVX_X_X_XM(x1, x2, op, T_66|T_0F|T_EW1|T_YMM|T_MUST_EVEX|T_B64, 0xEB); }
void vprold(Xmm x, const Operand& op, uint8_t imm) { opAVX_X_X_XM(Xmm(x.getKind(), 1), x, op, T_66|T_0F|T_W0|T_YMM|T_MUST_EVEX|T_B32, 0x72, imm); }
void vprolq(Xmm x, const Operand& op, uint8_t imm) { opAVX_X_X_XM(Xmm(x.getKind(), 1), x, op, T_66|T_0F|T_EW1|T_YMM|T_MUST_EVEX|T_B64, 0x72, imm); }
void vprolvd(Xmm x1, Xmm x2, const Operand& op) { opAVX_X_X_XM(x1, x2, op, T_66|T_0F38|T_W0|T_YMM|T_MUST_EVEX|T_B32, 0x15); }
void vprolvq(Xmm x1, Xmm x2, const Operand& op) { opAVX_X_X_XM(x1, x2, op, T_66|T_0F38|T_EW1|T_YMM|T_MUST_EVEX|T_B64, 0x15); }
void vprord(Xmm x, const Operand& op, uint8_t imm) { opAVX_X_X_XM(Xmm(x.getKind(), 0), x, op, T_66|T_0F|T_W0|T_YMM|T_MUST_EVEX|T_B32, 0x72, imm); }
void vprorq(Xmm x, const Operand& op, uint8_t imm) { opAVX_X_X_XM(Xmm(x.getKind(), 0), x, op, T_66|T_0F|T_EW1|T_YMM|T_MUST_EVEX|T_B64, 0x72, imm); }
void vprorvd(Xmm x1, Xmm x2, const Operand& op) { opAVX_X_X_XM(x1, x2, op, T_66|T_0F38|T_W0|T_YMM|T_MUST_EVEX|T_B32, 0x14); }
void vprorvq(Xmm x1, Xmm x2, const Operand& op) { opAVX_X_X_XM(x1, x2, op, T_66|T_0F38|T_EW1|T_YMM|T_MUST_EVEX|T_B64, 0x14); }
void vpscatterdd(const Address& addr, Xmm x) { opGather2(x, addr, T_N4|T_66|T_0F38|T_W0|T_YMM|T_MUST_EVEX|T_M_K|T_VSIB, 0xA0, 0); }
void vpscatterdq(const Address& addr, Xmm x) { opGather2(x, addr, T_N8|T_66|T_0F38|T_EW1|T_YMM|T_MUST_EVEX|T_M_K|T_VSIB, 0xA0, 1); }
void vpscatterqd(const Address& addr, Xmm x) { opGather2(x, addr, T_N4|T_66|T_0F38|T_W0|T_YMM|T_MUST_EVEX|T_M_K|T_VSIB, 0xA1, 2); }
void vpscatterqq(const Address& addr, Xmm x) { opGather2(x, addr, T_N8|T_66|T_0F38|T_EW1|T_YMM|T_MUST_EVEX|T_M_K|T_VSIB, 0xA1, 0); }
void vpshldd(Xmm x1, Xmm x2, const Operand& op, uint8_t imm) { opAVX_X_X_XM(x1, x2, op, T_66|T_0F3A|T_W0|T_YMM|T_SAE_Z|T_MUST_EVEX|T_B32, 0x71, imm); }
void vpshldq(Xmm x1, Xmm x2, const Operand& op, uint8_t imm) { opAVX_X_X_XM(x1, x2, op, T_66|T_0F3A|T_EW1|T_YMM|T_SAE_Z|T_MUST_EVEX|T_B64, 0x71, imm); }
void vpshldvd(Xmm x1, Xmm x2, const Operand& op) { opAVX_X_X_XM(x1, x2, op, T_66|T_0F38|T_W0|T_YMM|T_SAE_Z|T_MUST_EVEX|T_B32, 0x71); }
void vpshldvq(Xmm x1, Xmm x2, const Operand& op) { opAVX_X_X_XM(x1, x2, op, T_66|T_0F38|T_EW1|T_YMM|T_SAE_Z|T_MUST_EVEX|T_B64, 0x71); }
void vpshldvw(Xmm x1, Xmm x2, const Operand& op) { opAVX_X_X_XM(x1, x2, op, T_66|T_0F38|T_EW1|T_YMM|T_SAE_Z|T_MUST_EVEX, 0x70); }
void vpshldw(Xmm x1, Xmm x2, const Operand& op, uint8_t imm) { opAVX_X_X_XM(x1, x2, op, T_66|T_0F3A|T_EW1|T_YMM|T_SAE_Z|T_MUST_EVEX, 0x70, imm); }
void vpshrdd(Xmm x1, Xmm x2, const Operand& op, uint8_t imm) { opAVX_X_X_XM(x1, x2, op, T_66|T_0F3A|T_W0|T_YMM|T_SAE_Z|T_MUST_EVEX|T_B32, 0x73, imm); }
void vpshrdq(Xmm x1, Xmm x2, const Operand& op, uint8_t imm) { opAVX_X_X_XM(x1, x2, op, T_66|T_0F3A|T_EW1|T_YMM|T_SAE_Z|T_MUST_EVEX|T_B64, 0x73, imm); }
void vpshrdvd(Xmm x1, Xmm x2, const Operand& op) { opAVX_X_X_XM(x1, x2, op, T_66|T_0F38|T_W0|T_YMM|T_SAE_Z|T_MUST_EVEX|T_B32, 0x73); }
void vpshrdvq(Xmm x1, Xmm x2, const Operand& op) { opAVX_X_X_XM(x1, x2, op, T_66|T_0F38|T_EW1|T_YMM|T_SAE_Z|T_MUST_EVEX|T_B64, 0x73); }
void vpshrdvw(Xmm x1, Xmm x2, const Operand& op) { opAVX_X_X_XM(x1, x2, op, T_66|T_0F38|T_EW1|T_YMM|T_SAE_Z|T_MUST_EVEX, 0x72); }
void vpshrdw(Xmm x1, Xmm x2, const Operand& op, uint8_t imm) { opAVX_X_X_XM(x1, x2, op, T_66|T_0F3A|T_EW1|T_YMM|T_SAE_Z|T_MUST_EVEX, 0x72, imm); }
void vpshufbitqmb(const Opmask& k, Xmm x, const Operand& op) { opVex(k, &x, op, T_66 | T_0F38 | T_W0 | T_YMM | T_MUST_EVEX, 0x8F); }
void vpsllvw(Xmm x1, Xmm x2, const Operand& op) { opAVX_X_X_XM(x1, x2, op, T_66|T_0F38|T_EW1|T_YMM|T_MUST_EVEX, 0x12); }
void vpsraq(Xmm x, const Operand& op, uint8_t imm) { opAVX_X_X_XM(Xmm(x.getKind(), 4), x, op, T_66|T_0F|T_EW1|T_YMM|T_MUST_EVEX|T_B64, 0x72, imm); }
void vpsraq(Xmm x1, Xmm x2, const Operand& op) { opAVX_X_X_XM(x1, x2, op, T_N16|T_66|T_0F|T_EW1|T_YMM|T_MUST_EVEX, 0xE2); }
void vpsravq(Xmm x1, Xmm x2, const Operand& op) { opAVX_X_X_XM(x1, x2, op, T_66|T_0F38|T_EW1|T_YMM|T_MUST_EVEX|T_B64, 0x46); }
void vpsravw(Xmm x1, Xmm x2, const Operand& op) { opAVX_X_X_XM(x1, x2, op, T_66|T_0F38|T_EW1|T_YMM|T_MUST_EVEX, 0x11); }
void vpsrlvw(Xmm x1, Xmm x2, const Operand& op) { opAVX_X_X_XM(x1, x2, op, T_66|T_0F38|T_EW1|T_YMM|T_MUST_EVEX, 0x10); }
void vpternlogd(Xmm x1, Xmm x2, const Operand& op, uint8_t imm) { opAVX_X_X_XM(x1, x2, op, T_66|T_0F3A|T_W0|T_YMM|T_MUST_EVEX|T_B32, 0x25, imm); }
void vpternlogq(Xmm x1, Xmm x2, const Operand& op, uint8_t imm) { opAVX_X_X_XM(x1, x2, op, T_66|T_0F3A|T_EW1|T_YMM|T_MUST_EVEX|T_B64, 0x25, imm); }
void vptestmb(const Opmask& k, Xmm x, const Operand& op) { opAVX_K_X_XM(k, x, op, T_66|T_0F38|T_W0|T_YMM|T_MUST_EVEX, 0x26); }
void vptestmd(const Opmask& k, Xmm x, const Operand& op) { opAVX_K_X_XM(k, x, op, T_66|T_0F38|T_W0|T_YMM|T_MUST_EVEX|T_B32, 0x27); }
void vptestmq(const Opmask& k, Xmm x, const Operand& op) { opAVX_K_X_XM(k, x, op, T_66|T_0F38|T_EW1|T_YMM|T_MUST_EVEX|T_B64, 0x27); }
void vptestmw(const Opmask& k, Xmm x, const Operand& op) { opAVX_K_X_XM(k, x, op, T_66|T_0F38|T_EW1|T_YMM|T_MUST_EVEX, 0x26); }
void vptestnmb(const Opmask& k, Xmm x, const Operand& op) { opAVX_K_X_XM(k, x, op, T_F3|T_0F38|T_W0|T_YMM|T_MUST_EVEX, 0x26); }
void vptestnmd(const Opmask& k, Xmm x, const Operand& op) { opAVX_K_X_XM(k, x, op, T_F3|T_0F38|T_W0|T_YMM|T_MUST_EVEX|T_B32, 0x27); }
void vptestnmq(const Opmask& k, Xmm x, const Operand& op) { opAVX_K_X_XM(k, x, op, T_F3|T_0F38|T_EW1|T_YMM|T_MUST_EVEX|T_B64, 0x27); }
void vptestnmw(const Opmask& k, Xmm x, const Operand& op) { opAVX_K_X_XM(k, x, op, T_F3|T_0F38|T_EW1|T_YMM|T_MUST_EVEX, 0x26); }
void vpxord(Xmm x1, Xmm x2, const Operand& op) { opAVX_X_X_XM(x1, x2, op, T_66|T_0F|T_W0|T_YMM|T_MUST_EVEX|T_B32, 0xEF); }
void vpxorq(Xmm x1, Xmm x2, const Operand& op) { opAVX_X_X_XM(x1, x2, op, T_66|T_0F|T_EW1|T_YMM|T_MUST_EVEX|T_B64, 0xEF); }
void vrangepd(Xmm x1, Xmm x2, const Operand& op, uint8_t imm) { opAVX_X_X_XM(x1, x2, op, T_66|T_0F3A|T_EW1|T_YMM|T_SAE_Z|T_MUST_EVEX|T_B64, 0x50, imm); }
void vrangeps(Xmm x1, Xmm x2, const Operand& op, uint8_t imm) { opAVX_X_X_XM(x1, x2, op, T_66|T_0F3A|T_W0|T_YMM|T_SAE_Z|T_MUST_EVEX|T_B32, 0x50, imm); }
void vrangesd(Xmm x1, Xmm x2, const Operand& op, uint8_t imm) { opAVX_X_X_XM(x1, x2, op, T_N8|T_66|T_0F3A|T_EW1|T_SAE_X|T_MUST_EVEX, 0x51, imm); }
void vrangess(Xmm x1, Xmm x2, const Operand& op, uint8_t imm) { opAVX_X_X_XM(x1, x2, op, T_N4|T_66|T_0F3A|T_W0|T_SAE_X|T_MUST_EVEX, 0x51, imm); }
void vrcp14pd(Xmm x, const Operand& op) { opAVX_X_XM_IMM(x, op, T_66|T_0F38|T_EW1|T_YMM|T_MUST_EVEX|T_B64, 0x4C); }
void vrcp14ps(Xmm x, const Operand& op) { opAVX_X_XM_IMM(x, op, T_66|T_0F38|T_W0|T_YMM|T_MUST_EVEX|T_B32, 0x4C); }
void vrcp14sd(Xmm x1, Xmm x2, const Operand& op) { opAVX_X_X_XM(x1, x2, op, T_N8|T_66|T_0F38|T_EW1|T_MUST_EVEX, 0x4D); }
void vrcp14ss(Xmm x1, Xmm x2, const Operand& op) { opAVX_X_X_XM(x1, x2, op, T_N4|T_66|T_0F38|T_W0|T_MUST_EVEX, 0x4D); }
void vrcp28pd(Zmm z, const Operand& op) { opAVX_X_XM_IMM(z, op, T_66 | T_0F38 | T_MUST_EVEX | T_YMM | T_EW1 | T_B64 | T_SAE_Z, 0xCA); }
void vrcp28ps(Zmm z, const Operand& op) { opAVX_X_XM_IMM(z, op, T_66 | T_0F38 | T_MUST_EVEX | T_YMM | T_W0 | T_B32 | T_SAE_Z, 0xCA); }
void vrcp28sd(Xmm x1, Xmm x2, const Operand& op) { opAVX_X_X_XM(x1, x2, op, T_N8|T_66|T_0F38|T_EW1|T_SAE_X|T_MUST_EVEX, 0xCB); }
void vrcp28ss(Xmm x1, Xmm x2, const Operand& op) { opAVX_X_X_XM(x1, x2, op, T_N4|T_66|T_0F38|T_W0|T_SAE_X|T_MUST_EVEX, 0xCB); }
void vrcpbf16(Xmm x, const Operand& op) { opAVX_X_XM_IMM(x, op, T_MAP6|T_W0|T_YMM|T_MUST_EVEX|T_B16, 0x4C); }
void vrcpph(Xmm x, const Operand& op) { opAVX_X_XM_IMM(x, op, T_66|T_MAP6|T_W0|T_YMM|T_MUST_EVEX|T_B16, 0x4C); }
void vrcpsh(Xmm x1, Xmm x2, const Operand& op) { opAVX_X_X_XM(x1, x2, op, T_N2|T_66|T_MAP6|T_W0|T_MUST_EVEX, 0x4D); }
void vreducebf16(Xmm x, const Operand& op, uint8_t imm) { opAVX_X_XM_IMM(x, op, T_F2|T_0F3A|T_W0|T_YMM|T_MUST_EVEX|T_B16, 0x56, imm); }
void vreducepd(Xmm x, const Operand& op, uint8_t imm) { opAVX_X_XM_IMM(x, op, T_66|T_0F3A|T_EW1|T_YMM|T_SAE_Z|T_MUST_EVEX|T_B64, 0x56, imm); }
void vreduceph(Xmm x, const Operand& op, uint8_t imm) { opAVX_X_XM_IMM(x, op, T_0F3A|T_W0|T_YMM|T_SAE_Z|T_MUST_EVEX|T_B16, 0x56, imm); }
void vreduceps(Xmm x, const Operand& op, uint8_t imm) { opAVX_X_XM_IMM(x, op, T_66|T_0F3A|T_W0|T_YMM|T_SAE_Z|T_MUST_EVEX|T_B32, 0x56, imm); }
void vreducesd(Xmm x1, Xmm x2, const Operand& op, uint8_t imm) { opAVX_X_X_XM(x1, x2, op, T_N8|T_66|T_0F3A|T_EW1|T_SAE_X|T_MUST_EVEX, 0x57, imm); }
void vreducesh(Xmm x1, Xmm x2, const Operand& op, uint8_t imm) { opAVX_X_X_XM(x1, x2, op, T_N2|T_0F3A|T_W0|T_SAE_X|T_MUST_EVEX, 0x57, imm); }
void vreducess(Xmm x1, Xmm x2, const Operand& op, uint8_t imm) { opAVX_X_X_XM(x1, x2, op, T_N4|T_66|T_0F3A|T_W0|T_SAE_X|T_MUST_EVEX, 0x57, imm); }
void vrndscalebf16(Xmm x, const Operand& op, uint8_t imm) { opAVX_X_XM_IMM(x, op, T_F2|T_0F3A|T_W0|T_YMM|T_MUST_EVEX|T_B16, 0x08, imm); }
void vrndscalepd(Xmm x, const Operand& op, uint8_t imm) { opAVX_X_XM_IMM(x, op, T_66|T_0F3A|T_EW1|T_YMM|T_SAE_Z|T_MUST_EVEX|T_B64, 0x09, imm); }
void vrndscaleph(Xmm x, const Operand& op, uint8_t imm) { opAVX_X_XM_IMM(x, op, T_0F3A|T_W0|T_YMM|T_SAE_Z|T_MUST_EVEX|T_B16, 0x08, imm); }
void vrndscaleps(Xmm x, const Operand& op, uint8_t imm) { opAVX_X_XM_IMM(x, op, T_66|T_0F3A|T_W0|T_YMM|T_SAE_Z|T_MUST_EVEX|T_B32, 0x08, imm); }
void vrndscalesd(Xmm x1, Xmm x2, const Operand& op, uint8_t imm) { opAVX_X_X_XM(x1, x2, op, T_N8|T_66|T_0F3A|T_EW1|T_SAE_X|T_MUST_EVEX, 0x0B, imm); }
void vrndscalesh(Xmm x1, Xmm x2, const Operand& op, uint8_t imm) { opAVX_X_X_XM(x1, x2, op, T_N2|T_0F3A|T_W0|T_SAE_X|T_MUST_EVEX, 0x0A, imm); }
void vrndscaless(Xmm x1, Xmm x2, const Operand& op, uint8_t imm) { opAVX_X_X_XM(x1, x2, op, T_N4|T_66|T_0F3A|T_W0|T_SAE_X|T_MUST_EVEX, 0x0A, imm); }
void vrsqrt14pd(Xmm x, const Operand& op) { opAVX_X_XM_IMM(x, op, T_66|T_0F38|T_EW1|T_YMM|T_MUST_EVEX|T_B64, 0x4E); }
void vrsqrt14ps(Xmm x, const Operand& op) { opAVX_X_XM_IMM(x, op, T_66|T_0F38|T_W0|T_YMM|T_MUST_EVEX|T_B32, 0x4E); }
void vrsqrt14sd(Xmm x1, Xmm x2, const Operand& op) { opAVX_X_X_XM(x1, x2, op, T_N8|T_66|T_0F38|T_EW1|T_YMM|T_MUST_EVEX, 0x4F); }
void vrsqrt14ss(Xmm x1, Xmm x2, const Operand& op) { opAVX_X_X_XM(x1, x2, op, T_N4|T_66|T_0F38|T_W0|T_YMM|T_MUST_EVEX, 0x4F); }
void vrsqrt28pd(Zmm z, const Operand& op) { opAVX_X_XM_IMM(z, op, T_66 | T_0F38 | T_MUST_EVEX | T_YMM | T_EW1 | T_B64 | T_SAE_Z, 0xCC); }
void vrsqrt28ps(Zmm z, const Operand& op) { opAVX_X_XM_IMM(z, op, T_66 | T_0F38 | T_MUST_EVEX | T_YMM | T_W0 | T_B32 | T_SAE_Z, 0xCC); }
void vrsqrt28sd(Xmm x1, Xmm x2, const Operand& op) { opAVX_X_X_XM(x1, x2, op, T_N8|T_66|T_0F38|T_EW1|T_SAE_X|T_MUST_EVEX, 0xCD); }
void vrsqrt28ss(Xmm x1, Xmm x2, const Operand& op) { opAVX_X_X_XM(x1, x2, op, T_N4|T_66|T_0F38|T_W0|T_SAE_X|T_MUST_EVEX, 0xCD); }
void vrsqrtbf16(Xmm x, const Operand& op) { opAVX_X_XM_IMM(x, op, T_MAP6|T_W0|T_YMM|T_MUST_EVEX|T_B16, 0x4E); }
void vrsqrtph(Xmm x, const Operand& op) { opAVX_X_XM_IMM(x, op, T_66|T_MAP6|T_W0|T_YMM|T_MUST_EVEX|T_B16, 0x4E); }
void vrsqrtsh(Xmm x1, Xmm x2, const Operand& op) { opAVX_X_X_XM(x1, x2, op, T_N2|T_66|T_MAP6|T_W0|T_MUST_EVEX, 0x4F); }
void vscalefbf16(Xmm x, const Operand& op) { opAVX_X_XM_IMM(x, op, T_MAP6|T_W0|T_YMM|T_MUST_EVEX|T_B16, 0x2C); }
void vscalefbf16(Xmm x1, Xmm x2, const Operand& op) { opAVX_X_X_XM(x1, x2, op, T_MAP6|T_W0|T_YMM|T_MUST_EVEX|T_B16, 0x2C); }
void vscalefpd(Xmm x1, Xmm x2, const Operand& op) { opAVX_X_X_XM(x1, x2, op, T_66|T_0F38|T_EW1|T_YMM|T_ER_Z|T_MUST_EVEX|T_B64, 0x2C); }
void vscalefph(Xmm x1, Xmm x2, const Operand& op) { opAVX_X_X_XM(x1, x2, op, T_66|T_MAP6|T_W0|T_YMM|T_ER_Z|T_MUST_EVEX|T_B16, 0x2C); }
void vscalefps(Xmm x1, Xmm x2, const Operand& op) { opAVX_X_X_XM(x1, x2, op, T_66|T_0F38|T_W0|T_YMM|T_ER_Z|T_MUST_EVEX|T_B32, 0x2C); }
void vscalefsd(Xmm x1, Xmm x2, const Operand& op) { opAVX_X_X_XM(x1, x2, op, T_N8|T_66|T_0F38|T_EW1|T_ER_X|T_MUST_EVEX, 0x2D); }
void vscalefsh(Xmm x1, Xmm x2, const Operand& op) { opAVX_X_X_XM(x1, x2, op, T_N2|T_66|T_MAP6|T_W0|T_ER_X|T_MUST_EVEX, 0x2D); }
void vscalefss(Xmm x1, Xmm x2, const Operand& op) { opAVX_X_X_XM(x1, x2, op, T_N4|T_66|T_0F38|T_W0|T_ER_X|T_MUST_EVEX, 0x2D); }
void vscatterdpd(const Address& addr, Xmm x) { opGather2(x, addr, T_N8|T_66|T_0F38|T_EW1|T_YMM|T_MUST_EVEX|T_M_K|T_VSIB, 0xA2, 1); }
void vscatterdps(const Address& addr, Xmm x) { opGather2(x, addr, T_N4|T_66|T_0F38|T_W0|T_YMM|T_MUST_EVEX|T_M_K|T_VSIB, 0xA2, 0); }
void vscatterpf0dpd(const Address& addr) { opGatherFetch(addr, zm5, T_N8|T_66|T_0F38|T_EW1|T_MUST_EVEX|T_M_K|T_VSIB, 0xC6, Operand::YMM); }
void vscatterpf0dps(const Address& addr) { opGatherFetch(addr, zm5, T_N4|T_66|T_0F38|T_W0|T_MUST_EVEX|T_M_K|T_VSIB, 0xC6, Operand::ZMM); }
void vscatterpf0qpd(const Address& addr) { opGatherFetch(addr, zm5, T_N8|T_66|T_0F38|T_EW1|T_MUST_EVEX|T_M_K|T_VSIB, 0xC7, Operand::ZMM); }
void vscatterpf0qps(const Address& addr) { opGatherFetch(addr, zm5, T_N4|T_66|T_0F38|T_W0|T_MUST_EVEX|T_M_K|T_VSIB, 0xC7, Operand::ZMM); }
void vscatterpf1dpd(const Address& addr) { opGatherFetch(addr, zm6, T_N8|T_66|T_0F38|T_EW1|T_MUST_EVEX|T_M_K|T_VSIB, 0xC6, Operand::YMM); }
void vscatterpf1dps(const Address& addr) { opGatherFetch(addr, zm6, T_N4|T_66|T_0F38|T_W0|T_MUST_EVEX|T_M_K|T_VSIB, 0xC6, Operand::ZMM); }
void vscatterpf1qpd(const Address& addr) { opGatherFetch(addr, zm6, T_N8|T_66|T_0F38|T_EW1|T_MUST_EVEX|T_M_K|T_VSIB, 0xC7, Operand::ZMM); }
void vscatterpf1qps(const Address& addr) { opGatherFetch(addr, zm6, T_N4|T_66|T_0F38|T_W0|T_MUST_EVEX|T_M_K|T_VSIB, 0xC7, Operand::ZMM); }
void vscatterqpd(const Address& addr, Xmm x) { opGather2(x, addr, T_N8|T_66|T_0F38|T_EW1|T_YMM|T_MUST_EVEX|T_M_K|T_VSIB, 0xA3, 0); }
void vscatterqps(const Address& addr, Xmm x) { opGather2(x, addr, T_N4|T_66|T_0F38|T_W0|T_YMM|T_MUST_EVEX|T_M_K|T_VSIB, 0xA3, 2); }
void vshuff32x4(Ymm y1, Ymm y2, const Operand& op, uint8_t imm) { opAVX_X_X_XM(y1, y2, op, T_66 | T_0F3A | T_YMM | T_MUST_EVEX | T_W0 | T_B32, 0x23, imm); }
void vshuff64x2(Ymm y1, Ymm y2, const Operand& op, uint8_t imm) { opAVX_X_X_XM(y1, y2, op, T_66 | T_0F3A | T_YMM | T_MUST_EVEX | T_EW1 | T_B64, 0x23, imm); }
void vshufi32x4(Ymm y1, Ymm y2, const Operand& op, uint8_t imm) { opAVX_X_X_XM(y1, y2, op, T_66 | T_0F3A | T_YMM | T_MUST_EVEX | T_W0 | T_B32, 0x43, imm); }
void vshufi64x2(Ymm y1, Ymm y2, const Operand& op, uint8_t imm) { opAVX_X_X_XM(y1, y2, op, T_66 | T_0F3A | T_YMM | T_MUST_EVEX | T_EW1 | T_B64, 0x43, imm); }
void vsqrtbf16(Xmm x, const Operand& op) { opAVX_X_XM_IMM(x, op, T_66|T_MAP5|T_W0|T_YMM|T_MUST_EVEX|T_B16, 0x51); }
void vsqrtph(Xmm x, const Operand& op) { opAVX_X_XM_IMM(x, op, T_MAP5|T_W0|T_YMM|T_ER_Z|T_MUST_EVEX|T_B16, 0x51); }
void vsqrtsh(Xmm x1, Xmm x2, const Operand& op) { opAVX_X_X_XM(x1, x2, op, T_N2|T_F3|T_MAP5|T_W0|T_ER_X|T_MUST_EVEX, 0x51); }
void vsubbf16(Xmm x1, Xmm x2, const Operand& op) { opAVX_X_X_XM(x1, x2, op, T_66|T_MAP5|T_W0|T_YMM|T_MUST_EVEX|T_B16, 0x5C); }
void vsubph(Xmm xmm, const Operand& op1, const Operand& op2 = Operand()) { opAVX_X_X_XM(xmm, op1, op2, T_MAP5 | T_W0 | T_YMM | T_MUST_EVEX | T_ER_Z | T_B16, 0x5C); }
void vsubsh(Xmm xmm, const Operand& op1, const Operand& op2 = Operand()) { opAVX_X_X_XM(xmm, op1, op2, T_MAP5 | T_F3 | T_W0 | T_MUST_EVEX | T_ER_X | T_N2, 0x5C); }
void vucomish(Xmm x, const Operand& op) { opAVX_X_XM_IMM(x, op, T_N2|T_MAP5|T_W0|T_SAE_X|T_MUST_EVEX, 0x2E); }
void vucomxsd(Xmm x, const Operand& op) { opAVX_X_XM_IMM(x, op, T_N8|T_F2|T_0F|T_EW1|T_SAE_X|T_MUST_EVEX, 0x2E); }
void vucomxsh(Xmm x, const Operand& op) { opAVX_X_XM_IMM(x, op, T_N2|T_F3|T_MAP5|T_W0|T_SAE_X|T_MUST_EVEX, 0x2E); }
void vucomxss(Xmm x, const Operand& op) { opAVX_X_XM_IMM(x, op, T_N4|T_F3|T_0F|T_W0|T_SAE_X|T_MUST_EVEX, 0x2E); }
#ifdef XBYAK64
void kmovq(Reg64 r, const Opmask& k) { opKmov(k, r, true, 64); }
void tcvtrowd2ps(Zmm z, const Tmm& t, Reg32 r) { opVex(z, &r, t, T_F3|T_0F38|T_W0|T_MUST_EVEX, 0x4A); }
void tcvtrowd2ps(Zmm z, const Tmm& t, uint8_t imm) { opVex(z, 0, t, T_F3|T_0F3A|T_W0|T_MUST_EVEX, 0x07, imm); }
void tcvtrowps2bf16h(Zmm z, const Tmm& t, Reg32 r) { opVex(z, &r, t, T_F2|T_0F38|T_W0|T_MUST_EVEX, 0x6D); }
void tcvtrowps2bf16h(Zmm z, const Tmm& t, uint8_t imm) { opVex(z, 0, t, T_F2|T_0F3A|T_W0|T_MUST_EVEX, 0x07, imm); }
void tcvtrowps2bf16l(Zmm z, const Tmm& t, Reg32 r) { opVex(z, &r, t, T_F3|T_0F38|T_W0|T_MUST_EVEX, 0x6D); }
void tcvtrowps2bf16l(Zmm z, const Tmm& t, uint8_t imm) { opVex(z, 0, t, T_F3|T_0F3A|T_W0|T_MUST_EVEX, 0x77, imm); }
void tcvtrowps2phh(Zmm z, const Tmm& t, Reg32 r) { opVex(z, &r, t, T_0F38|T_W0|T_MUST_EVEX, 0x6D); }
void tcvtrowps2phh(Zmm z, const Tmm& t, uint8_t imm) { opVex(z, 0, t, T_0F3A|T_W0|T_MUST_EVEX, 0x07, imm); }
void tcvtrowps2phl(Zmm z, const Tmm& t, Reg32 r) { opVex(z, &r, t, T_66|T_0F38|T_W0|T_MUST_EVEX, 0x6D); }
void tcvtrowps2phl(Zmm z, const Tmm& t, uint8_t imm) { opVex(z, 0, t, T_F2|T_0F3A|T_W0|T_MUST_EVEX, 0x77, imm); }
void tilemovrow(Zmm z, const Tmm& t, Reg32 r) { opVex(z, &r, t, T_66|T_0F38|T_W0|T_MUST_EVEX, 0x4A); }
void tilemovrow(Zmm z, const Tmm& t, uint8_t imm) { opVex(z, 0, t, T_66|T_0F3A|T_W0|T_MUST_EVEX, 0x07, imm); }
void vmovrsb(Xmm x, const Address& addr) { opVex(x, 0, addr, T_F2|T_MAP5|T_W0|T_MUST_EVEX, 0x6F); }
void vmovrsd(Xmm x, const Address& addr) { opVex(x, 0, addr, T_F3|T_MAP5|T_W0|T_MUST_EVEX, 0x6F); }
void vmovrsq(Xmm x, const Address& addr) { opVex(x, 0, addr, T_F3|T_MAP5|T_EW1|T_MUST_EVEX, 0x6F); }
void vmovrsw(Xmm x, const Address& addr) { opVex(x, 0, addr, T_F2|T_MAP5|T_EW1|T_MUST_EVEX, 0x6F); }
void vpbroadcastq(Xmm x, Reg64 r) { opVex(x, 0, r, T_66|T_0F38|T_EW1|T_YMM|T_MUST_EVEX, 0x7C); }
#endif
#endif
