#include "printing.h"

#include <stdlib.h>
#include "libft.h"

void print_hex(t_array *output, t_arg arg, unsigned long o)
{
	size_t	hextoa_len;
	char	*hextoa;
	int		blank_count;
	int		zero_count;
	int		has_prefix;

	has_prefix = (arg.alternate_form && o != 0);
	hextoa = ft_hextoa(o, arg.uppercase_prefix);
	if (o == 0 && arg.has_precision && arg.precision == 0)
		hextoa[0] = '\0';
	if (o == 0 && arg.has_precision && arg.precision == 0 && arg.min_width == 0)
		return;
	hextoa_len = ft_strlen(hextoa);
	arg.min_width = ft_max(arg.min_width - has_prefix * 2, 0);
	if (arg.min_width > 0 && arg.pad_with_zero && arg.has_precision == false)
	{
		arg.precision = arg.min_width;
		arg.min_width = 0;
	}
	zero_count = ft_max(arg.precision - hextoa_len, 0);
//	zero_count = (zero_count) ? zero_count : has_prefix;
	blank_count = ft_max(arg.min_width - (hextoa_len + zero_count), 0);
	if (arg.left_adjust == false)
		append_n_chars(output, ' ', blank_count);
	if (arg.alternate_form && o > 0)
		array_append(output, arg.uppercase_prefix ? "0X" : "0x", 2);
	append_n_chars(output, '0', zero_count);
	array_append(output, hextoa, hextoa_len);
	if (arg.left_adjust)
		append_n_chars(output, ' ', blank_count);
	free(hextoa);
}

void print_octal(t_array *output, t_arg arg, unsigned long o)
{
	size_t	otoa_len;
	char	*otoa;
	int		blank_count;
	int		zero_count;
	int		has_prefix;

	has_prefix = (arg.alternate_form && o != 0);
	otoa = ft_otoa(o);
	if (o == 0 && arg.has_precision && arg.precision == 0 && !arg.alternate_form)
	{
		otoa[0] = '\0';
		if (arg.min_width == 0)
			return;
	}
	otoa_len = ft_strlen(otoa);
	if (arg.min_width > 0 && arg.pad_with_zero && arg.has_precision == false)
	{
		arg.precision = arg.min_width;
		arg.min_width = 0;
	}
	zero_count = ft_max(arg.precision - otoa_len, 0);
	zero_count = (zero_count) ? zero_count : has_prefix;
	blank_count = ft_max(arg.min_width - (otoa_len + zero_count), 0);
	if (arg.left_adjust == false)
		append_n_chars(output, ' ', blank_count);
	append_n_chars(output, '0', zero_count);
	array_append(output, otoa, otoa_len);
	if (arg.left_adjust)
		append_n_chars(output, ' ', blank_count);
	free(otoa);
}

void print_integer(t_array *output, t_arg arg, char *itoa, size_t itoa_len)
{
	int		is_neg;
	int		has_sign_char;
	size_t	blank_count;
	size_t	zero_count;
	size_t	digit_count;

	is_neg = itoa[0] == '-';
	has_sign_char = ft_isdigit(itoa[0]) == false && (itoa[0] != '\0');
	digit_count = ft_max(itoa_len - has_sign_char, 0);
	ft_memcpy(itoa, itoa + has_sign_char, digit_count);
	if (arg.min_width > 0 && arg.pad_with_zero && arg.has_precision == false)
	{
		arg.precision = arg.min_width - has_sign_char;
		arg.min_width = 0;
	}
	zero_count =  ft_max(arg.precision - digit_count, 0);
	blank_count = ft_max(arg.min_width - (itoa_len + zero_count), 0);
	if (arg.left_adjust == false)
		append_n_chars(output, ' ', blank_count);
	if (has_sign_char)
		array_append(output, (is_neg) ? "-" : &arg.plus_sign, 1);
	append_n_chars(output, '0', zero_count);
	array_append(output, itoa, digit_count);
	if (arg.left_adjust)
		append_n_chars(output, ' ', blank_count);
}

/*
** If working precision is 0 and value is 0, dont print 0 but still print prefix
*/

void print_int(t_array *output, t_arg arg, long l)
{
	char	*ltoa;

	ltoa = ft_ltoa_sign(l, arg.plus_sign);
	if (l == 0 && arg.has_precision && arg.precision == 0)
		ltoa[arg.plus_sign != 0] = '\0';
	print_integer(output, arg, ltoa, ft_strlen(ltoa));
	free(ltoa);
}

/*
** If precision is 0 and value is 0, dont print 0 but still print prefix
*/

void print_uint(t_array *output, t_arg arg, unsigned long l)
{
	char	*ultoa;

	ultoa = ft_ultoa_sign(l, arg.plus_sign);
	if (l == 0 && arg.has_precision && arg.precision == 0)
		ultoa[arg.plus_sign != 0] = '\0';
	print_integer(output, arg, ultoa, ft_strlen(ultoa));
	free(ultoa);
}