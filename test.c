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
void test_str(char* format, char *string);
void test_locale();

int main()
{
	setvbuf(stdout, NULL, _IONBF, 0);

	setlocale(LC_ALL, "en_US.UTF-8");

	for (int i = 0; i < 65535; ++i) {
//		test("%C", i);
	}



//	test_locale();
//	test("%lc", 0x4e6);
//	test_UL("%.4S", L"我是一只猫。");
//	test_UL("%5lc", 350);
//	test_UL("%C", 255);
//	test_UL("%jc", L'☭');
//	test_UL("%5.0u", (short)0);
//	test_UL("%p", NULL);
//	test_UL("%C", (__darwin_wint_t)-2);
//	test_UL("%C", 254);
//	test_str("%s", "coco");
//	test_str("%10.5s", "ab");
//	printf("%lu\n", -12345612220);
//	ft_printf("%lu\n", -12345612220);
//	test("%lu", -12345612220U);

//	test_str("%15.4S", (char *) L"我是一只猫。");
//	test_str("%4.15S", L"我是一只猫。");

//	test_str("%10S", (char*)(L"☭bar☭"));
	test_str("%S", (char*)(L"\x53\x3abc\x81000"));
//	test_str("%150.8S", (char *) L"我是一只猫。");
//	test_str("%S", (char *) L"我是一只猫。");
//	test_str("%S", L"米");

	printf("MB_CUR_MAX: %d\n", MB_CUR_MAX);
	printf("MB_LEN_MAX: %d\n", MB_LEN_MAX);
	printf("%s\n", setlocale(LC_ALL, NULL));


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
	ret_lib = ft_printf(format, value, value);
	printf(", %d", ret_lib);
	puts("");
	puts("-- LIB --");
	ret_mine = printf(format, value, value);
	printf(", %d", ret_mine);
	puts("\n");
}

void test_locale()
{
//	setlocale(LC_ALL, "");
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