#include "ft_printf.h"

#include <stddef.h>
#include <stdio.h>
#include <limits.h>
#include <zconf.h>
#include <libft.h>

void test(char* format, int value);

int main()
{
	setvbuf(stdout, NULL, _IONBF, 0);

//	test("%0d", -42);
//	test("%7d", 42);
//	test("%7d", -42);
//	test("%+7d", 42);
//	test("% 7d", 42);

	test("%07d", -42);
	test("%+07d", 42);
	test("% 07d", 42);
	test("%07d", 42);
//
	test("%.7d", -42);
	test("%+.7d", 42);
	test("% .7d", 42);
	test("%.7d", 42);
	test("%010.6d", 42);
	return 0;
}

void test(char* format, int value)
{
	printf("TEST: %s, %d\n", format, value);
	printf(format, value);
	puts("");
//	puts("-- MINE --");
//	ft_printf(format, value);
//	puts("\n");
}