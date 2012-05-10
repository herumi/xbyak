#include <stdio.h>
#include "xbyak/xbyak.h"
#include "xbyak/xbyak_util.h"

#define NUM_OF_ARRAY(x) (sizeof(x) / sizeof(x[0]))

struct PopCountTest : public Xbyak::CodeGenerator {
	PopCountTest(int n)
	{
		mov(eax, n);
		popcnt(eax, eax);
		ret();
	}
};

void putCPUinfo()
{
	using namespace Xbyak::util;
	Cpu cpu;
	printf("vendor %s\n", cpu.has(Cpu::tINTEL) ? "intel" : "amd");
	static const struct {
		Cpu::Type type;
		const char *str;
	} tbl[] = {
		{ Cpu::tMMX, "mmx" },
		{ Cpu::tMMX2, "mmx2" },
		{ Cpu::tCMOV, "cmov" },
		{ Cpu::tSSE, "sse" },
		{ Cpu::tSSE2, "sse2" },
		{ Cpu::tSSE3, "sse3" },
		{ Cpu::tSSSE3, "ssse3" },
		{ Cpu::tSSE41, "sse41" },
		{ Cpu::tSSE42, "sse42" },
		{ Cpu::tPOPCNT, "popcnt" },
		{ Cpu::t3DN, "3dn" },
		{ Cpu::tE3DN, "e3dn" },
		{ Cpu::tSSE4a, "sse4a" },
		{ Cpu::tSSE5, "sse5" },
		{ Cpu::tAESNI, "aesni" },
		{ Cpu::tRDTSCP, "rdtscp" },
		{ Cpu::tOSXSAVE, "osxsave(xgetvb)" },
		{ Cpu::tPCLMULQDQ, "pclmulqdq" },
		{ Cpu::tAVX, "avx" },
		{ Cpu::tFMA, "fma" },
	};
	for (size_t i = 0; i < NUM_OF_ARRAY(tbl); i++) {
		if (cpu.has(tbl[i].type)) printf(" %s", tbl[i].str);
	}
	printf("\n");
	if (cpu.has(Cpu::tPOPCNT)) {
		const int n = 0x12345678; // bitcount = 13
		const int ok = 13;
		int r = ((int (*)())((const void*)PopCountTest(n).getCode()))();
		if (r == ok) {
			puts("popcnt ok");
		} else {
			printf("popcnt ng %d %d\n", r, ok);
		}
	}
}

#ifdef XBYAK32
struct EipTest : public Xbyak::CodeGenerator {
	EipTest()
	{
		Xbyak::util::setEipTo(this, eax);
		ret();
	}
};

void putEip()
{
	EipTest s;
	int (*getEip)() = (int(*)())(const void*)s.getCode();
	printf("eip=%08x\n", getEip());
}
#endif

int main()
{
#ifdef XBYAK32
	puts("32bit");
#else
	puts("64bit");
#endif
	putCPUinfo();
#ifdef XBYAK32
	putEip();
#endif
}
