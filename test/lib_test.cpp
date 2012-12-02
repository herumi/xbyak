#include <xbyak/xbyak.h>

struct Code : public Xbyak::CodeGenerator {
	Code()
	{
		mov(eax, 5);
		ret();
	}
};

int ret123()
{
	static Code code;
	int (*f)() = (int (*)())code.getCode();
	return f();
}

