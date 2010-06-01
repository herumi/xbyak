#include <stdio.h>
#include <string.h>

#define NUM_OF_ARRAY(x) (sizeof(x) / sizeof(x[0]))

void genAddress(bool isJIT, const char regTbl[][5], size_t regTblNum)
{
	int count = 0;
	int funcNum = 1;
	if (isJIT) {
		puts("void gen0(){");
	}
	for (size_t i = 0; i < regTblNum + 1; i++) {
		const char *base = regTbl[i];
		for (size_t j = 0; j < regTblNum + 1; j++) {
			if (j == 4) continue; /* esp is not index register */
			const char *index = regTbl[j];
			static const int scaleTbl[] = { 0, 1, 2, 4, 8 };
			for (size_t k = 0; k < NUM_OF_ARRAY(scaleTbl); k++) {
				int scale = scaleTbl[k];
				static const int dispTbl[] = { 0, 1, 1000, -1, -1000 };
				for (size_t m = 0; m < NUM_OF_ARRAY(dispTbl); m++) {
					int disp = dispTbl[m];
					bool isFirst = true;
					if (isJIT) {
						printf("mov (ecx, ptr[");
					} else {
						printf("mov ecx, [");
					}
					if (i < regTblNum) {
						printf("%s", base);
						isFirst = false;
					}
					if (j < regTblNum) {
						if (!isFirst) putchar('+');
						printf("%s", index);
						if (scale) printf("*%d", scale);
						isFirst = false;
					}
					if (isFirst) {
						if (isJIT) printf("(void*)");
						printf("0x%08X", disp);
					} else {
						if (disp >= 0) {
							putchar('+');
						}
						printf("%d", disp);
						isFirst = false;
					}
					if (isJIT) {
						printf("]); dump();\n");
					} else {
						printf("]\n");
					}
					if (isJIT) {
						count++;
						if ((count % 100) == 0) {
							printf("}\n    void gen%d(){\n", funcNum++);
						}
					}
				}
			}
		}
	}
	if (isJIT) {
		printf("}\nvoid gen(){\n");
		for (int i = 0; i < funcNum; i++) {
			printf("   gen%d();\n", i);
		}
		printf("}\n");
	}
}

int main(int argc, char *argv[])
{
	argc--, argv++;
	bool phase = argc > 0 && strcmp(*argv, "1") == 0;
	bool isJIT = (argc > 1);
	fprintf(stderr, "phase:%c %s\n", phase ? '1' : '2', isJIT ? "jit" : "asm");
	if (phase) {
		fprintf(stderr, "32bit reg\n");
		static const char reg32Tbl[][5] = {
			"eax", "ecx", "edx", "ebx", "esp", "ebp", "esi", "edi",
#ifdef XBYAK64
			"r9d", "r10d", "r11d", "r12d", "r13d", "r14d", "r15d",
#endif
		};
		genAddress(isJIT, reg32Tbl, NUM_OF_ARRAY(reg32Tbl));
	} else {
#ifdef XBYAK64
		fprintf(stderr, "64bit reg\n");
		static const char reg64Tbl[][5] = {
			"rax", "rcx", "rdx", "rbx", "rsp", "rbp", "rsi", "rdi", "r9", "r10", "r11", "r12", "r13", "r14", "r15",
		};
		genAddress(isJIT, reg64Tbl, NUM_OF_ARRAY(reg64Tbl));
#endif
	}
}
