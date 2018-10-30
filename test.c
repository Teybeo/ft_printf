#include "ft_printf.h"

#include <stddef.h>
#include <stdio.h>
#include <limits.h>
#include <zconf.h>
#include <libft.h>

void test(char* format, int value);

void test_UL(char* format, unsigned long value);

int main()
{
	setvbuf(stdout, NULL, _IONBF, 0);

	test("%d", 42);

	test("%07d", -42);
	test("%+07d", 42);
	test("% 07d", 42);
	test("%07d", 42);
//
	test("%.7d", -42);
	test("%+.7d", 42);
	test("% .7d", 42);
	test("%.7d", 42);
	test("%010.1d", 42);
	test("%010.0d", 42);
	test("%010.d", 42);
	test("%+.0d nothing", 0);
	test("%%", 0);

//	test("%-+10.4d", 42);
	test_UL("%+u", 4294967295UL);
	test_UL("%zu", -145612220UL);
	test("titi % +---12.5% et%%%0004% et %+1%", 0);
//	printf("%lu\n", -12345612220);
//	ft_printf("%lu\n", -12345612220);
//	test("%lu", -12345612220U);

	return 0;
}

void test(char* format, int value)
{
	int ret_lib;
	int ret_mine;

	printf("TEST: %s, %d\n", format, value);
	ret_lib = printf(format, value);
	printf(", %d", ret_lib);
	puts("");
	puts("-- MINE --");
	ret_mine = ft_printf(format, value);
	printf(", %d", ret_mine);
	puts("\n");
}

void test_UL(char* format, unsigned long value)
{
	int ret_lib;
	int ret_mine;

	printf("TEST: %s, %lu\n", format, value);
	ret_lib = printf(format, value);
	printf(", %d", ret_lib);
	puts("");
	puts("-- MINE --");
	ret_mine = ft_printf(format, value);
	printf(", %d", ret_mine);
	puts("\n");
}
