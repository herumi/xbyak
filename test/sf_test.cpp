#define XBYAK_NO_OP_NAMES
#include <xbyak/xbyak_util.h>

#ifdef XBYAK32
	#error "this sample is for only 64-bit mode"
#endif

using namespace Xbyak::util;

struct Code : public Xbyak::CodeGenerator {
	void gen1()
	{
		StackFrame sf(this, 1);
		mov(rax, sf.p(0));
	}
	void gen2()
	{
		StackFrame sf(this, 2);
		mov(rax, sf.p(0));
		add(rax, sf.p(1));
	}
	void gen3()
	{
		StackFrame sf(this, 3);
		mov(rax, sf.p(0));
		add(rax, sf.p(1));
		add(rax, sf.p(2));
	}
	void gen4()
	{
		StackFrame sf(this, 4);
		mov(rax, sf.p(0));
		add(rax, sf.p(1));
		add(rax, sf.p(2));
		add(rax, sf.p(3));
	}

	void gen5()
	{
		StackFrame sf(this, 4, 0, UseRCX);
		xor_(rcx, rcx);
		mov(rax, sf.p(0));
		add(rax, sf.p(1));
		add(rax, sf.p(2));
		add(rax, sf.p(3));
	}

	void gen6()
	{
		StackFrame sf(this, 4, 0, UseRCX | UseRDX);
		xor_(rcx, rcx);
		xor_(rdx, rdx);
		mov(rax, sf.p(0));
		add(rax, sf.p(1));
		add(rax, sf.p(2));
		add(rax, sf.p(3));
	}

	void gen7()
	{
		StackFrame sf(this, 3, 0, UseRCX | UseRDX);
		xor_(rcx, rcx);
		xor_(rdx, rdx);
		mov(rax, sf.p(0));
		add(rax, sf.p(1));
		add(rax, sf.p(2));
	}

	void gen8()
	{
		StackFrame sf(this, 4, 3, UseRCX | UseRDX);
		xor_(rcx, rcx);
		xor_(rdx, rdx);
		mov(sf.t(0), 1);
		mov(sf.t(1), 2);
		mov(sf.t(2), 3);
		mov(rax, sf.p(0));
		add(rax, sf.p(1));
		add(rax, sf.p(2));
	}

	void gen9()
	{
		StackFrame sf(this, 4, 3, UseRCX | UseRDX, 4);
		xor_(rcx, rcx);
		xor_(rdx, rdx);
		mov(sf.t(0), 1);
		mov(sf.t(1), 2);
		mov(sf.t(2), 3);
		mov(rax, sf.p(0));
		add(rax, sf.p(1));
		add(rax, sf.p(2));
		mov(ptr [rsp + 8 * 0], rax);
		mov(ptr [rsp + 8 * 1], rax);
		mov(ptr [rsp + 8 * 2], rax);
		mov(ptr [rsp + 8 * 3], rax);
	}

	void gen10()
	{
		StackFrame sf(this, 4, 8, UseRCX | UseRDX, 4);
		xor_(rcx, rcx);
		xor_(rdx, rdx);
		for (int i = 0; i < 8; i++) {
			mov(sf.t(i), i);
		}
		mov(rax, sf.p(0));
		add(rax, sf.p(1));
		add(rax, sf.p(2));
		add(rax, sf.p(3));
		mov(ptr [rsp + 8 * 0], rax);
		mov(ptr [rsp + 8 * 1], rax);
		mov(ptr [rsp + 8 * 2], rax);
		mov(ptr [rsp + 8 * 3], rax);
	}
};

static int errNum = 0;
void check(int x, int y)
{
	if (x != y) {
		printf("err x=%d, y=%d\n", x, y);
		errNum++;
	}
}

int main()
{
	Code code;
	int (*f1)(int) = code.getCurr<int (*)(int)>();
	code.gen1();
	check(5, f1(5));

	int (*f2)(int, int) = code.getCurr<int (*)(int, int)>();
	code.gen2();
	check(9, f2(3, 6));

	int (*f3)(int, int, int) = code.getCurr<int (*)(int, int, int)>();
	code.gen3();
	check(14, f3(1, 4, 9));

	int (*f4)(int, int, int, int) = code.getCurr<int (*)(int, int, int, int)>();
	code.gen4();
	check(30, f4(1, 4, 9, 16));

	int (*f5)(int, int, int, int) = code.getCurr<int (*)(int, int, int, int)>();
	code.gen5();
	check(23, f5(2, 5, 7, 9));

	int (*f6)(int, int, int, int) = code.getCurr<int (*)(int, int, int, int)>();
	code.gen6();
	check(18, f6(3, 4, 5, 6));

	int (*f7)(int, int, int) = code.getCurr<int (*)(int, int, int)>();
	code.gen7();
	check(12, f7(3, 4, 5));

	int (*f8)(int, int, int) = code.getCurr<int (*)(int, int, int)>();
	code.gen8();
	check(23, f8(5, 8, 10));

	int (*f9)(int, int, int) = code.getCurr<int (*)(int, int, int)>();
	code.gen9();
	check(60, f9(10, 20, 30));

	int (*f10)(int, int, int, int) = code.getCurr<int (*)(int, int, int, int)>();
	code.gen10();
	check(100, f10(10, 20, 30, 40));
	printf("errNum=%d\n", errNum);
}
