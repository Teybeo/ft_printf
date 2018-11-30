#include "ft_printf.h"

#include <stddef.h>
#include <stdio.h>
#include <limits.h>
#include <zconf.h>
#include <libft.h>
#include <locale.h>
#include <stdlib.h>
#include <errno.h>
#include <memory.h>
#include <float.h>
#include <time.h>
#include <math.h>

void test(char* format, int value);
void test_UL(char* format, unsigned long value);
void test_str(char* format, char *string);
void test_wstr(char* format, wchar_t *string);
void test_locale();

void test_lf(char* format, double value);

int main()
{
//	setbuf(stdout, NULL);

	setlocale(LC_ALL, "en_US.UTF-8");

//	test_locale();
//	test("%lc", 0x4e6);
//	test_wstr("%.4S", L"我是一只猫。");
//	test_wstr("%S", L"我是一只猫。");
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

//	test_str("%4.0S", (char *) L"我是一只猫。");
//	test_str("%4.15S", L"我是一只猫。");

//	test_str("%10S", (char*)(L"☭bar☭"));
	// LIB C returns 0
	// UB OR WHAT ????
//	test_str("%.2S", (char*)(L"\x53\x3abc\x81000"));
//	printf("%S", (L"A\x3ABC\x81000"));
//	test_str("%S", (char*)(L"\x53\x3abc\x81000"));
//	test_str("%.S", (char*)(L"S\x100u"));
//	ft_printf("%S%S", L"Α α", L"Β β");
//	ft_printf("%S%S%S%S%S%S%S%S%S%S%S%S%S%S%S%S%S%S%S%S%S%S%S%S%S",	L"Α α", L"Β β", L"Γ γ", L"Δ δ", L"Ε ε", L"Ζ ζ", L"Η η", L"Θ θ", L"Ι ι", L"Κ κ", L"Λ λ", L"Μ μ", L"Ν ν", L"Ξ ξ", L"Ο ο", L"Π π", L"Ρ ρ", L"Σ σ", L"Τ τ", L"Υ υ", L"Φ φ", L"Χ χ", L"Ψ ψ", L"Ω ω", L"");
//	printf("%S%S%S%S%S%S%S%S%S%S%S%S%S%S%S%S%S%S%S%S%S%S%S%S%S",	L"Α α", L"Β β", L"Γ γ", L"Δ δ", L"Ε ε", L"Ζ ζ", L"Η η", L"Θ θ", L"Ι ι", L"Κ κ", L"Λ λ", L"Μ μ", L"Ν ν", L"Ξ ξ", L"Ο ο", L"Π π", L"Ρ ρ", L"Σ σ", L"Τ τ", L"Υ υ", L"Φ φ", L"Χ χ", L"Ψ ψ", L"Ω ω", L"");
//	printf("%S%S", L"Α α", L"Β β");
//	test_str("%150.8S", (char *) L"我是一只猫。");
//	test_str("%S", (char *) L"我是一只猫。");
//	test_str("%S", L"米");
//	test_UL("%C", 0x40501);
//	test_str("hello", "abc");
//	ft_printf("%C", 0x001fffff);
//	ft_printf("%C", 0x40501);
//	printf("%C", 0x40501);
//	test("%C", (size_t)-2);
//	test("%C", 256);

//	test_lf("%.60lf", FLT_MAX);
//	test_lf("%f", DBL_MAX);
//	printf("%f", DBL_MAX);
//	test_lf("%20.60lf", 42420412345678901.);
//	test_lf("%20.60lf", 0.42420412345678901);
//	test_lf("%10.5lf", -4.5); // BUG HERE
//	printf("%.1lf", 42.);

//	printf
//	char buffer[128] = "";
//	for (int i = 0; i < 255; ++i) {
//		sprintf(buffer, "%%%c", i);
//		ft_printf("%10s\n", buffer);
//		printf("%10s\n", buffer, 42);
//	}

//	printf("%-010}bdf  %d hello\n", 20);
//	ft_printf("%-010}bdf  %d hello", 20);

	// printing 0 as octal with 0 precision but X width
//	test_UL("%-05.o", 0);
//	test_UL("%#1.o", 0);
//	test_UL("%C", -214);
	srand(1);
//	test_lf("%3.9f", 27.09L);
//	test_lf("%4.1f", 89.8);
//	test_lf("%4.1f", 41.22);
	float max = 10000.f;
	for (unsigned char i = 0; i < 255; ++i)
	{
		char format[] = "%5.1f";
		format[1] = '0' + rand() % 10;
		//format[3] = '0' + rand() % 10;
		double x = rand() % (int)max;
		x -= max / 2;
		x /= powf(10, rand() % 3);
//		test_lf(format, x);
//		ft_printf("i: %d (%c) -> [", i, i);
//		test_str(buffer, "lol");
//		ft_printf("]\n");
	}
	double x1=46.51L;
//	test_lf("%34.18f", x1);
//	test_lf("%9.9f", x1);
//	test_lf("%9.8f", x1);
//	test_lf("%9.7f", x1);
//	test_lf("%9.6f", x1);
//	test_lf("%9.5f", x1);
//	test_lf("%9.4f", x1);
//	test_lf("%9.3f", x1);
//	test_lf("%9.2f", x1);
//	test_lf("%9.1f", x1);
//	test_lf("%.0f", 1.4);
//	test_lf("%.f", 1.5);
//	test_lf("%.f", -1.6);
//	test_lf("%.f", 2.6);
//	test_lf("%.f", 2.5);
//	test_lf("%.f", -2.4);
//	test_lf("%8.6Ld", -27.19);
	printf("%f", 4543513513514.4L);
//	float a = 1024;
//	ft_printf("%b", &a);
/*
 	double x1=108.765625;
	test_lf("%34.30f\n", x1);
	test_lf("%9.5f\n", x1);
	double x2=108.046875;
	test_lf("%34.30lf\n", x2);
	test_lf("%9.5f\n", x2);
*/


	return 0;
	printf("MB_CUR_MAX: %d\n", MB_CUR_MAX);
	printf("MB_LEN_MAX: %d\n", MB_LEN_MAX);
	printf("%s\n", setlocale(LC_ALL, NULL));

	return 0;
}

void test_lf(char* format, double value)
{
	int ret;

	printf("TEST: %s, %.15f\n", format, value);
	ret = ft_printf(format, value);
	printf(", %d", ret);
	puts("");
	puts("-- LIB --");
	ret = printf(format, value);
	printf(", %d", ret);
	puts("\n");
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
	printf(", %d\n", ret);
	if (errno)
		puts(strerror(errno));
}

void test_wstr(char* format, wchar_t *string)
{
	int ret;

	printf("TEST: %s, %ls\n", format, string);
	ret = ft_printf(format, string);
	printf(", %d", ret);
	puts("");
	puts("-- LIB --");
	ret = printf(format, string);
	printf(", %d\n", ret);
	if (errno)
		puts(strerror(errno));
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