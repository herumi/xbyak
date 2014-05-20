#include <xbyak/xbyak.h>

#define TEST_EXCEPTION(state) \
{ \
	num++; \
	bool exception = false; \
	try { \
		state; \
	} catch (...) { \
		exception = true; \
	} \
	if (!exception) { \
		printf("exception should arise for %s\n", #state); \
		err++; \
	} \
}

struct Code : Xbyak::CodeGenerator {
	Code()
	{
		int err = 0;
		int num = 0;
		TEST_EXCEPTION(mov(eax, ptr [esp + esp]));
		TEST_EXCEPTION(mov(eax, ptr [ax])); // not support
		TEST_EXCEPTION(mov(eax, ptr [esp * 4]));
		TEST_EXCEPTION(mov(eax, ptr [eax * 16]));
		TEST_EXCEPTION(mov(eax, ptr [eax + eax + eax]));
		TEST_EXCEPTION(mov(eax, ptr [eax * 2 + ecx * 4]));
		TEST_EXCEPTION(mov(eax, ptr [eax * 2 + ecx * 4]));
		TEST_EXCEPTION(vgatherdpd(xmm0, ptr [eax * 2], ymm3));
		TEST_EXCEPTION(vgatherdpd(xmm0, ptr [xmm0 + xmm1], ymm3));
#ifdef XBYAK64
		TEST_EXCEPTION(mov(eax, ptr [rax + eax]));
		TEST_EXCEPTION(mov(eax, ptr [xmm0 + ymm0]));
#endif
		if (!err) {
			printf("bad_address test %d ok\n", num);
		}
	}
};

int main()
{
	Code c;
}
