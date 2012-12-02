#pragma once
#include <stdio.h>

void init();

static struct Init {
	Init()
	{
		puts("Init");
		init();
	}
} s_init;

