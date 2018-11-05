#include "ft_printf.h"

#include <stddef.h>
#include <stdio.h>
#include <limits.h>
#include <zconf.h>
#include <libft.h>
#include <locale.h>
#include <stdlib.h>

void test(char* format, int value);

void test_UL(char* format, unsigned long value);

void test_str(char* format, char *string)
;

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

	test("%o", 42);
	test("%5o", 42);
	test("%.0o", 42);
	test("%.o", 42);
	test("%5.0o", 42);

	test("%0o", 42);
	test("%05o", 42);
	test("%0.0o", 42);
	test("%0.o", 42);
	test("%05.0o", 42);

	test("% o", 42);
	test("% 5o", 42);
	test("% .0o", 42);
	test("% .o", 42);
	test("% 5.0o", 42);

	test("%0 o", 42);
	test("%0 5o", 42);
	test("%0 .0o", 42);
	test("%0 .o", 42);
	test("%0 5.0o", 42);

	test("%#o", 42);
	test("%#5o", 42);
	test("%#.0o", 42);
	test("%#.o", 42);
	test("%#5.0o", 42);

	test("%#0o", 42);
	test("%#05o", 42);
	test("%#0.0o", 42);
	test("%#0.o", 42);
	test("%#05.0o", 42);

	test("%# o", 42);
	test("%# 5o", 42);
	test("%# .0o", 42);
	test("%# .o", 42);
	test("%# 5.0o", 42);

	test("%#0 o", 42);
	test("%#0 5o", 42);
	test("%#0 .0o", 42);
	test("%#0 .o", 42);
	test("%#0 5.0o", 42);

	test("%#o", 0);
	test("%#5o", 0);
	test("%#.0o", 0);
	test("%#.o", 0);
	test("%#5.0o", 0);

	test("%#0o", 0);
	test("%#05o", 0);
	test("%#0.0o", 0);
	test("%#0.o", 0);
	test("%#05.0o", 0);

	test("%# o", 0);
	test("%# 5o", 0);
	test("%# .0o", 0);
	test("%# .o", 0);
	test("%# 5.0o", 0);

	test("%#0 o", 0);
	test("%#0 5o", 0);
	test("%#0 .0o", 0);
	test("%#0 .o", 0);
	test("%#0 5.0o", 0);

	test("%#05o", 12);
	test("%#0.5o", 12);
	test("%#.5o", 12);

	test("%#010x", 12);

	test("%#.1x", 0);
	test("%#.0x", 0);
	test("%#.x", 0);

	test("%#10.0x", 0);
	test("%0#10.0x", 0);

	test("%p", 0);
	test("%.0p", 0);
	test("%.p", 0);
	test("%.4p", 42);
	test("%.4p", 0);
	test("%#20.4hhp", INT_MAX);
	for (int i = 0; i < 258; ++i) {
		test("%c", i);
	}
//	test_str("%s", "coco");
	test_str("%10.5s", "ab");
//	printf("%lu\n", -12345612220);
//	ft_printf("%lu\n", -12345612220);
//	test("%lu", -12345612220U);

	return 0;
}

void test_str(char* format, char *string)
{
	int ret;

	printf("TEST: %s, %s\n", format, string);
	ret = ft_printf(format, string);
	printf(", %d", ret);
	puts("");
	puts("-- LIB --");
	ret = printf(format, string);
	printf(", %d", ret);
	puts("\n");
}
void test(char* format, int value)
{
	int ret;

	printf("TEST: %s, %d\n", format, value);
	ret = ft_printf(format, value);
	printf(", %d", ret);
	puts("");
	puts("-- LIB --");
	ret = printf(format, value);
	printf(", %d", ret);
	puts("\n");
}

void test_UL(char* format, unsigned long value)
{
	int ret_lib;
	int ret_mine;

	printf("TEST: %s, %lu\n", format, value);
	ret_lib = printf(format, value, value);
	printf(", %d", ret_lib);
	puts("");
	puts("-- MINE --");
	ret_mine = ft_printf(format, value, value);
	printf(", %d", ret_mine);
	puts("\n");
}

void test_locale()
{
	setlocale(LC_ALL, "");
	setlocale(LC_ALL, "en_US.UTF-8");
	printf("MB_CUR_MAX: %d\n", MB_CUR_MAX);
//	printf("%s\n", setlocale(LC_ALL, NULL));
	for (int i = 0; i < 512; ++i) {

		printf("%d: ", i);
		int ret = printf("%lc", i);
		printf("   %d\n", ret);
	}
	printf("\nsizeof wchar_t: %zu\n", sizeof(wchar_t));

//	printf("")
//	setlocale (LC_MONETARY,"");
	struct lconv * lc;
	lc=localeconv();
//	lc->grouping
	printf ("Local Currency Symbol: %s\n",lc->currency_symbol);
	printf ("International Currency Symbol: %s\n",lc->int_curr_symbol);
	printf("%\'f\n", 40900002.f);

}