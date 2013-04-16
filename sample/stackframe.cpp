#define XBYAK_NO_OP_NAMES
#include <xbyak/xbyak_util.h>

#ifdef XBYAK32
	#error "this sample is for only 64-bit mode"
#endif

struct Code : public Xbyak::CodeGenerator {
	Code()
	{
		Xbyak::util::StackFrame sf(this, 4);
		mov(rax, sf.p(0));
		add(rax, sf.p(1));
		add(rax, sf.p(2));
		add(rax, sf.p(3));
		ret();
	}
};

int main()
{
	Code c;
	int (*f)(int, int, int, int) = c.getCode<int(*) (int, int, int, int)>();
	printf("%d\n", f(3, 5, 2, 9));
	puts("ok");
}
