#include <stdio.h>
#include "xbyak/xbyak.h"

using namespace Xbyak;

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
{
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
}
