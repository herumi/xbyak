#define XBYAK_NO_OP_NAMES
#include "xbyak/xbyak.h"
#include <stdio.h>
#include <stdlib.h>
#include <stack>
#include <fstream>
#ifdef _MSC_VER
	#pragma warning(disable : 4996) // scanf
	#define snprintf _snprintf_s
#endif

class Brainfuck : public Xbyak::CodeGenerator {
private:
	enum Direction { B, F };
	std::string toStr(int labelNo, Direction dir)
	{
		return Xbyak::Label::toStr(labelNo) + (dir == B ? 'B' : 'F');
	}
public:
	int getContinuousChar(std::istream& is, char c)
	{
		int count = 1;
		char p;
		while (is >> p) {
			if (p != c) break;
			count++;
		}
		is.unget();
		return count;
	}
	Brainfuck(std::istream& is) : CodeGenerator(100000)
	{
		// void (*)(void* putchar, void* getchar, int *stack)
		using namespace Xbyak;
#ifdef XBYAK32
		const Reg32& pPutchar(esi);
		const Reg32& pGetchar(edi);
		const Reg32& stack(ebp);
		const Address cur = dword [stack];
		push(ebp); // stack
		push(esi);
		push(edi);
		const int P_ = 4 * 3;
		mov(pPutchar, ptr[esp + P_ + 4]); // putchar
		mov(pGetchar, ptr[esp + P_ + 8]); // getchar
		mov(stack, ptr[esp + P_ + 12]); // stack
#elif defined(XBYAK64_WIN)
		const Reg64& pPutchar(rsi);
		const Reg64& pGetchar(rdi);
		const Reg64& stack(rbp); // stack
		const Address cur = dword [stack];
		push(rsi);
		push(rdi);
		push(rbp);
		mov(pPutchar, rcx); // putchar
		mov(pGetchar, rdx); // getchar
		mov(stack, r8); // stack
#else
		const Reg64& pPutchar(rbx);
		const Reg64& pGetchar(rbp);
		const Reg64& stack(r12); // stack
		const Address cur = dword [stack];
		push(rbx);
		push(rbp);
		push(r12);
		mov(pPutchar, rdi); // putchar
		mov(pGetchar, rsi); // getchar
		mov(stack, rdx); // stack
#endif
		int labelNo = 0;
		std::stack<int> keepLabelNo;
		char c;
		while (is >> c) {
			switch (c) {
			case '+':
			case '-':
				{
					int count = getContinuousChar(is, c);
					if (count == 1) {
						c == '+' ? inc(cur) : dec(cur);
					} else {
						add(cur, (c == '+' ? count : -count));
					}
				}
				break;
			case '>':
			case '<':
				{
					int count = getContinuousChar(is, c);
					add(stack, 4 * (c == '>' ? count : -count));
				}
				break;
			case '.':
#ifdef XBYAK32
				push(cur);
				call(pPutchar);
				pop(eax);
#elif defined(XBYAK64_WIN)
				mov(rcx, cur);
				sub(rsp, 32);
				call(pPutchar);
				add(rsp, 32);
#else
				mov(rdi, cur);
				call(pPutchar);
#endif
				break;
			case ',':
#if defined(XBYAK32) || defined(XBYAK64_GCC)
				call(pGetchar);
				mov(cur, eax);
#elif defined(XBYAK64_WIN)
				sub(rsp, 32);
				call(pGetchar);
				add(rsp, 32);
				mov(cur, rax);
#endif
				break;
			case '[':
				L(toStr(labelNo, B));
				mov(eax, cur);
				test(eax, eax);
				jz(toStr(labelNo, F), T_NEAR);
				keepLabelNo.push(labelNo++);
				break;
			case ']':
				{
					int no = keepLabelNo.top(); keepLabelNo.pop();
					jmp(toStr(no, B));
					L(toStr(no, F));
				}
				break;
			default:
				break;
			}
		}
#ifdef XBYAK32
		pop(edi);
		pop(esi);
		pop(ebp);
#elif defined(XBYAK64_WIN)
		pop(rbp);
		pop(rdi);
		pop(rsi);
#else
		pop(r12);
		pop(rbp);
		pop(rbx);
#endif
		ret();
	}
};

void dump(const Xbyak::uint8 *code, size_t size)
{
	puts("#include <stdio.h>\nstatic int stack[128 * 1024];\nstatic const unsigned char code[] = {");
	for (size_t i = 0; i < size; i++) {
		printf("0x%02x,", code[i]); if ((i % 16) == 15) putchar('\n');
	}
	puts("\n};");
#ifndef _WIN32
	puts("#include <unistd.h>");
	puts("#include <sys/mman.h>");
#endif
	puts("main()\n{");
#ifndef _WIN32
	puts("\tlong pageSize = sysconf(_SC_PAGESIZE) - 1;");
	puts("\tmprotect((void*)code, (sizeof(code) + pageSize) & ~pageSize, PROT_READ | PROT_EXEC);");
#endif
	puts(
		"\t((void (*)(void*, void*, int *))code)((void*)putchar, (void*)getchar, stack);\n"
		"}"
	);
}

int main(int argc, char *argv[])
{
#ifdef XBYAK32
	fprintf(stderr, "32bit mode\n");
#else
	fprintf(stderr, "64bit mode\n");
#endif
	if (argc == 1) {
		fprintf(stderr, "bf filename.bf [0|1]\n");
		return 1;
	}
	std::ifstream ifs(argv[1]);
	int mode = argc == 3 ? atoi(argv[2]) : 0;
	try {
		Brainfuck bf(ifs);
		if (mode == 0) {
			static int stack[128 * 1024];
			bf.getCode<void (*)(void*, void*, int *)>()(Xbyak::CastTo<void*>(putchar), Xbyak::CastTo<void*>(getchar), stack);
		} else {
			dump(bf.getCode(), bf.getSize());
		}
	} catch (std::exception& e) {
		printf("ERR:%s\n", e.what());
	} catch (...) {
		printf("unknown error\n");
	}
}

