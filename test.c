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
	test("%010.1d", 42);
	test("%010.0d", 42);
	test("%010.d", 42);
	test("%.0d", 0);
	
	ft_printf("toto%.0d et %+.i et  %   .0D !!!", 0, 0, 0);
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
