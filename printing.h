#ifndef PRINTING_H
# define PRINTING_H

# include "array.h"
# include "parsing.h"

# include <stdarg.h>

void	process_arg2(t_array *output, t_arg arg, va_list list, int *error);

void	print_d(t_array *output, t_arg arg, va_list list, int *error);
void	print_u(t_array *output, t_arg arg, va_list list, int *error);
void	print_o(t_array *output, t_arg arg, va_list list, int *error);
void	print_x(t_array *output, t_arg arg, va_list list, int *error);
void	print_p(t_array *output, t_arg arg, va_list list, int *error);

void	print_c(t_array *output, t_arg arg, va_list list, int *error);
void	print_wc(t_array *output, t_arg arg, va_list list, int *error);
void	print_s(t_array *output, t_arg arg, va_list list, int *error);
void	print_ws(t_array *output, t_arg arg, va_list list, int *error);
void	print_f(t_array *output, t_arg arg, va_list list, int *error);

void	print_int(t_array *output, t_arg arg, long l);
void	print_octal(t_array *output, t_arg arg, unsigned long o);
void	print_hex(t_array *output, t_arg arg, unsigned long o);
void	print_uint(t_array *output, t_arg arg, unsigned long l);
void	print_address(t_array *output, t_arg arg, unsigned long ul);
void	print_char(t_array *output, t_arg arg, unsigned char uc);
void	print_wchar(t_array *output, t_arg arg, wchar_t wc, int *error);
void	print_string(t_array *output, t_arg arg, char *string);
void	print_wstring(t_array *output, t_arg arg, wchar_t *string, int *error);
void	print_float(t_array *output, t_arg arg, double value);
void	print_invalid(t_array *output, t_arg arg, va_list list, int *error);
void	print_percent(t_array *output, t_arg arg, va_list list, int *error);



#endif
