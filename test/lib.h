#pragma once
#include <stdio.h>

struct A {
	int a;
	A()
		: a(5)
	{
		puts("A cstr");
	}
	~A()
	{
		puts("A dstr");
	}
	void put() const
	{
		printf("a=%d\n", a);
	}
};

template<int dummy = 0>
struct XT {
	static A a;
};

template<int dummy>
A XT<dummy>::a;

typedef XT<0> X;

void init();

static struct Init {
	Init()
	{
		puts("Init");
		init();
	}
} s_init;

