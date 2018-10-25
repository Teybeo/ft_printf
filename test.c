#include "ft_printf.h"

#include <stddef.h>
#include <stdio.h>
#include <limits.h>
#include <zconf.h>

int main()
{
	wchar_t str[4];
	str[0] = 945;
	str[1] = 10000;
	str[2] = 946;
//	int 	ret;
//	printf("Hello, World!\n");
//	ret = printf("%d Salut %S   %d\n", 10, str, 42);
//	printf("%010 wetrjyZ %d\n", 42);

//	printf("%0217d\n", 42);
//	return 0;
//	ft_token token_table[255] = {};
//	token_table['%'] = arg_start;
//	token_table['d'] = int_token;
//	token_table['i'] = int_token;

	setvbuf(stdout, NULL, _IONBF, 0);

//	ft_printf("abc %0d test %01561d end of string", -42, 256);
//	printf("coco %&rtasgdfsg2  mol mdr", 42);
//	printf("%D\n", 42);
//	ft_printf("%D\n", 0xff11ff11ff88);
//	printf("%D\n", 0xff11ff11ff88);
//	ft_printf("%D\n", 280452758896520);
//	printf("%D\n", 280452758896520);
//	ft_printf("%.123d testlol", 42);
	int arg = -42;
	char *format = "%07d";
	printf(format, arg);
	puts("\n-- MINE --");
//	ft_printf("%10.4d", -42);
	ft_printf(format, arg);
	puts("");
//	foo("test %d lol", token_table);

	return 0;
}