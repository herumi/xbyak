#pragma once
#include <stdio.h>
#include <xbyak/xbyak.h>

struct A : public Xbyak::CodeGenerator {
	A()
	{
		puts("A cstr");
	}
	void put() const
	{
		try {
			printf("eax=%s\n", eax.toString());
			printf("util::eax=%s\n", Xbyak::util::eax.toString());
		} catch (Xbyak::Error e) {
			printf("err=%s\n", Xbyak::ConvertErrorToString(e));
		}
	}
};

void init();

static struct Init {
	Init()
	{
		puts("Init");
		init();
	}
} s_init;

