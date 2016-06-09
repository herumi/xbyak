#ifdef XBYAK_AVX512
void kaddw(const Opmask& r1, const Opmask& r2, const Opmask& r3) { opK(r1, r2, r3, MM_0F, 0x4A, 0); }
void kaddb(const Opmask& r1, const Opmask& r2, const Opmask& r3) { opK(r1, r2, r3, MM_0F | PP_66, 0x4A, 0); }
void kaddq(const Opmask& r1, const Opmask& r2, const Opmask& r3) { opK(r1, r2, r3, MM_0F, 0x4A, 1); }
void kaddd(const Opmask& r1, const Opmask& r2, const Opmask& r3) { opK(r1, r2, r3, MM_0F | PP_66, 0x4A, 1); }
void kandw(const Opmask& r1, const Opmask& r2, const Opmask& r3) { opK(r1, r2, r3, MM_0F, 0x41, 0); }
void kandb(const Opmask& r1, const Opmask& r2, const Opmask& r3) { opK(r1, r2, r3, MM_0F | PP_66, 0x41, 0); }
void kandq(const Opmask& r1, const Opmask& r2, const Opmask& r3) { opK(r1, r2, r3, MM_0F, 0x41, 1); }
void kandd(const Opmask& r1, const Opmask& r2, const Opmask& r3) { opK(r1, r2, r3, MM_0F | PP_66, 0x41, 1); }
void kandnw(const Opmask& r1, const Opmask& r2, const Opmask& r3) { opK(r1, r2, r3, MM_0F, 0x42, 0); }
void kandnb(const Opmask& r1, const Opmask& r2, const Opmask& r3) { opK(r1, r2, r3, MM_0F | PP_66, 0x42, 0); }
void kandnq(const Opmask& r1, const Opmask& r2, const Opmask& r3) { opK(r1, r2, r3, MM_0F, 0x42, 1); }
void kandnd(const Opmask& r1, const Opmask& r2, const Opmask& r3) { opK(r1, r2, r3, MM_0F | PP_66, 0x42, 1); }
void korw(const Opmask& r1, const Opmask& r2, const Opmask& r3) { opK(r1, r2, r3, MM_0F, 0x45, 0); }
void korb(const Opmask& r1, const Opmask& r2, const Opmask& r3) { opK(r1, r2, r3, MM_0F | PP_66, 0x45, 0); }
void korq(const Opmask& r1, const Opmask& r2, const Opmask& r3) { opK(r1, r2, r3, MM_0F, 0x45, 1); }
void kord(const Opmask& r1, const Opmask& r2, const Opmask& r3) { opK(r1, r2, r3, MM_0F | PP_66, 0x45, 1); }
void kxnorw(const Opmask& r1, const Opmask& r2, const Opmask& r3) { opK(r1, r2, r3, MM_0F, 0x46, 0); }
void kxnorb(const Opmask& r1, const Opmask& r2, const Opmask& r3) { opK(r1, r2, r3, MM_0F | PP_66, 0x46, 0); }
void kxnorq(const Opmask& r1, const Opmask& r2, const Opmask& r3) { opK(r1, r2, r3, MM_0F, 0x46, 1); }
void kxnord(const Opmask& r1, const Opmask& r2, const Opmask& r3) { opK(r1, r2, r3, MM_0F | PP_66, 0x46, 1); }
void kxorw(const Opmask& r1, const Opmask& r2, const Opmask& r3) { opK(r1, r2, r3, MM_0F, 0x47, 0); }
void kxorb(const Opmask& r1, const Opmask& r2, const Opmask& r3) { opK(r1, r2, r3, MM_0F | PP_66, 0x47, 0); }
void kxorq(const Opmask& r1, const Opmask& r2, const Opmask& r3) { opK(r1, r2, r3, MM_0F, 0x47, 1); }
void kxord(const Opmask& r1, const Opmask& r2, const Opmask& r3) { opK(r1, r2, r3, MM_0F | PP_66, 0x47, 1); }
#endif
