#include <stdio.h>
#define XBYAK_NO_OP_NAMES
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
		{ Cpu::tAVX2, "avx2" },
		{ Cpu::tBMI1, "bmi1" },
		{ Cpu::tBMI2, "bmi2" },
		{ Cpu::tLZCNT, "lzcnt" },
		{ Cpu::tENHANCED_REP, "enh_rep" },
		{ Cpu::tRDRAND, "rdrand" },
	};
	for (size_t i = 0; i < NUM_OF_ARRAY(tbl); i++) {
		if (cpu.has(tbl[i].type)) printf(" %s", tbl[i].str);
	}
	printf("\n");
	if (cpu.has(Cpu::tPOPCNT)) {
		const int n = 0x12345678; // bitcount = 13
		const int ok = 13;
		int r = PopCountTest(n).getCode<int (*)()>()();
		if (r == ok) {
			puts("popcnt ok");
		} else {
			printf("popcnt ng %d %d\n", r, ok);
		}
	}
	/*
		                displayFamily displayModel
		Opteron 2376        10            4
		Core2 Duo T7100      6            F
		Core i3-2120T        6           2A
		Core i7-2600         6           2A
		Xeon X5650           6           2C
		Core i7-3517         6           3A
		Core i7-3930K        6           2D
	*/
	cpu.putFamily();
}

int main()
{
#ifdef XBYAK32
	puts("32bit");
#else
	puts("64bit");
#endif
	putCPUinfo();
}
