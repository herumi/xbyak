#include <xbyak/xbyak.h>

using namespace Xbyak;
using namespace Xbyak::util;

#ifdef XBYAK64
const struct Ptn {
	const Reg8 *reg8;
	Reg16 reg16;
	Reg32 reg32;
	Reg64 reg64;
} tbl[] = {
	{ &al, ax, eax, rax },
	{ &bl, bx, ebx, rbx },
	{ &cl, cx, ecx, rcx },
	{ &dl, dx, edx, rdx },
	{ &sil, si, esi, rsi },
	{ &dil, di, edi, rdi },
	{ &bpl, bp, ebp, rbp },
	{ &spl, sp, esp, rsp },
	{ &r8b, r8w, r8d, r8 },
	{ &r9b, r9w, r9d, r9 },
	{ &r10b, r10w, r10d, r10 },
	{ &r11b, r11w, r11d, r11 },
	{ &r12b, r12w, r12d, r12 },
	{ &r13b, r13w, r13d, r13 },
	{ &r14b, r14w, r14d, r14 },
	{ &r15b, r15w, r15d, r15 },
};
#else
const struct Ptn {
	const Reg8 *reg8;
	Reg16 reg16;
	Reg32 reg32;
} tbl[] = {
	{ &al, ax, eax },
	{ &bl, bx, ebx },
	{ &cl, cx, ecx },
	{ &dl, dx, edx },
	{ 0, si, esi },
	{ 0, di, edi },
	{ 0, bp, ebp },
	{ 0, sp, esp },
};
#endif

int errNum = 0;
int testNum = 0;

template<class T>
void verify(const T& x, const T& y)
{
	if (x != y) {
		printf("ERR %s %s\n", x.toString(), y.toString());
		errNum++;
	}
	testNum++;
}

#define verifyExp(state) \
{ \
	bool isOK = false; \
	try { \
		state; \
	} catch (const Xbyak::Error& e) { \
		if ((int)e == ERR_CANT_CONVERT) { \
			isOK = true; \
		} \
	} \
	if (!isOK) { \
		printf("ERR " #state "\n"); \
		errNum++; \
	} \
	testNum++; \
}

int main()
	try
{
	for (size_t i = 0; i < sizeof(tbl) / sizeof(tbl[0]); i++) {
		if (tbl[i].reg8) {
			verify(tbl[i].reg8->cvt8(), *tbl[i].reg8);
			verify(tbl[i].reg8->cvt16(), tbl[i].reg16);
			verify(tbl[i].reg8->cvt32(), tbl[i].reg32);
			verify(tbl[i].reg16.cvt8(), *tbl[i].reg8);
			verify(tbl[i].reg32.cvt8(), *tbl[i].reg8);
		}
		verify(tbl[i].reg16.cvt16(), tbl[i].reg16);
		verify(tbl[i].reg16.cvt32(), tbl[i].reg32);
		verify(tbl[i].reg32.cvt16(), tbl[i].reg16);
		verify(tbl[i].reg32.cvt32(), tbl[i].reg32);
#ifdef XBYAK64
		if (tbl[i].reg8) {
			verify(tbl[i].reg64.cvt8(), *tbl[i].reg8);
			verify(tbl[i].reg8->cvt64(), tbl[i].reg64);
		}
		verify(tbl[i].reg64.cvt16(), tbl[i].reg16);
		verify(tbl[i].reg64.cvt32(), tbl[i].reg32);
		verify(tbl[i].reg64.cvt64(), tbl[i].reg64);
		verify(tbl[i].reg16.cvt64(), tbl[i].reg64);
		verify(tbl[i].reg32.cvt64(), tbl[i].reg64);
#endif
	}
	{
		const Reg8 errTbl[] = {
			ah, bh, ch, dh
		};
		for (size_t i = 0; i < sizeof(errTbl) / sizeof(errTbl[0]); i++) {
			verifyExp(errTbl[i].cvt16());
		}
	}
#ifdef XBYAK32
	{
		const Reg16 errTbl[] = {
			si, di, bp, sp
		};
		for (size_t i = 0; i < sizeof(errTbl) / sizeof(errTbl[0]); i++) {
			verifyExp(errTbl[i].cvt8());
		}
	}
#endif
	printf("test=%d(err=%d)\n", testNum, errNum);
} catch (std::exception& e) {
	printf("ERR %s\n", e.what());
}
