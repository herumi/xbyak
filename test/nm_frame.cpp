#include <stdio.h>
#define XBYAK_NO_OP_NAMES
#define XBYAK_ENABLE_OMITTED_OPERAND
#include "xbyak/xbyak.h"

using namespace Xbyak;

#ifdef _MSC_VER
	#pragma warning(disable : 4245)
	#pragma warning(disable : 4312)
#endif
class Sample : public CodeGenerator {
	void operator=(const Sample&);
public:
#include "nm.cpp"
};

#define _STR(x) #x
#define TEST(syntax) err = true; try { syntax; err = false; } catch (Xbyak::Error) { } catch (...) { } if (!err) printf("should be err:%s;\n", _STR(syntax))

class ErrorSample : public CodeGenerator {
	void operator=(const ErrorSample&);
public:
	void gen()
	{
		bool err;
		TEST(mov(ptr[eax],1));
		TEST(test(ptr[eax],1));
		TEST(adc(ptr[eax],1));
		TEST(setz(eax));
	}
};
int main()
	try
{
	size_t size = sizeof(Xbyak::Operand);
	if (size != 4) {
		printf("sizeof Operand %d\n", (int)size);
	}
	try {
		Sample s;
		s.gen();
	} catch (std::exception& e) {
		printf("ERR:%s\n", e.what());
	} catch (...) {
		printf("unknown error\n");
	}
	ErrorSample es;
	es.gen();
} catch (std::exception& e) {
	printf("err %s\n", e.what());
	return 1;
}
