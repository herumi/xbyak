#include <stdio.h>

struct A {
	int aaa;
	A()
		: aaa(123)
	{
		puts("A cstr");
	}
	~A()
	{
		puts("A dstr");
	}
	void put() const
	{
		printf("aaa=%d\n", aaa);
	}
};

template<int dummy = 0>
struct XT {
	static A sss;
};

template<int dummy>
A XT<dummy>::sss;

typedef XT<0> X;

static struct Init {
	Init()
	{
		puts("Init");
		X::sss.put();
	}
} s_init;


int main()
{
	puts("main");
	X::sss.put();
}
