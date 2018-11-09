#include "ft_printf.h"
#include "libft.h"

#include "array.h"

#include <stdio.h>
#include <zconf.h>
#include <stdbool.h>
#include <stdlib.h>
#include <assert.h>
#include <stddef.h>
#include <limits.h>
#include <wchar.h>

/*
 * sS p dD i oO uU xX cC
 * #
 * 0
 * -
 * +
 * ' '
 *
 * hh, h, l, ll, j, et .
 */

typedef struct s_arg t_arg;

typedef void (*ft_token)(t_arg arg);

struct s_arg
{
	bool alternate_form;
	bool left_adjust; // Default to right adjust
	bool pad_with_zero; // Default to blank-padding
	bool short_modifier;
	bool double_short_modifier;
	bool long_modifier;
	bool has_precision;
	size_t min_width;
	size_t precision;
//	ft_token fn;
	char token;
	char plus_sign;
	bool uppercase_prefix;
};

void process_arg(t_array *output, t_arg arg, va_list list, int *error);
void consume_non_arg(const char *string, t_array *array, int *consumed);

void print_int(t_array *output, t_arg arg, long l);
void print_octal(t_array *output, t_arg arg, unsigned long o);
void print_hex(t_array *output, t_arg arg, unsigned long o);
void print_uint(t_array *output, t_arg arg, unsigned long l);
void print_percent(t_array *output, t_arg arg);
void print_address(t_array *output, t_arg arg, unsigned long ul);
void print_char(t_array *output, t_arg arg, unsigned char uc);
void print_wchar(t_array *output, t_arg arg, wchar_t wc, int *error);
void print_string(t_array *output, t_arg arg, char *string);
void print_wstring(t_array *output, t_arg arg, wchar_t *string, int *error);

int		get_first_index(const char *string, char c)
{
	int	i;

	i = 0;
	while (string[i] != c && string[i] != '\0')
		i++;
	return (string[i] != '\0' ? i : -1);
}

t_arg get_next_arg(const char *string, int *consumed)
{
	const char	*ptr;
	t_arg		arg;

	arg = (t_arg){};
	ptr = string;
	while (*ptr != '\0')
	{
		if (*ptr == 'd' || *ptr == 'i' || *ptr == 'D')
		{
			arg.token = 'd';
			arg.long_modifier |= (*ptr == 'D');
			ptr++;
			break;
		}
		else if (*ptr == 'u' || *ptr == 'U')
		{
			arg.token = 'u';
			arg.long_modifier |= (*ptr == 'U');
			arg.plus_sign = false;
			ptr++;
			break;
		}
		else if (*ptr == 'o' || (*ptr == 'O'))
		{
			arg.token = 'o';
			arg.long_modifier |= (*ptr == 'O');
			ptr++;
			break;
		}
		else if (*ptr == 'x' || (*ptr == 'X'))
		{
			arg.token = 'x';
			arg.uppercase_prefix |= (*ptr == 'X');
			ptr++;
			break;
		}
		else if (*ptr == 'p')
		{
			arg.token = 'p';
			ptr++;
			break;
		}
		else if (*ptr == 'c')
		{
			arg.token = arg.long_modifier ? 'C' : 'c';
			ptr++;
			break;
		}
		else if (*ptr == 'C')
		{
			arg.token = 'C';
			ptr++;
			break;
		}
		else if (*ptr == 's')
		{
			arg.token = arg.long_modifier ? 'S' : 's';
			ptr++;
			break;
		}
		else if (*ptr == 'S')
		{
			arg.token = 'S';
			ptr++;
			break;
		}
		else if (*ptr == '%')
		{
			arg.token = '%';
			ptr++;
			break;
		}
		else if (*ptr == ' ')
		{
			if (arg.plus_sign != '+')
				arg.plus_sign = ' ';
		}
		else if (*ptr == '+')
		{
			arg.plus_sign = '+';
		}
		else if (*ptr == '-')
		{
			arg.left_adjust = true;
			arg.pad_with_zero = false;
		}
		else if (*ptr == 'l' || *ptr == 'j')
		{
			arg.long_modifier = true;
		}
		else if (*ptr == 'h')
		{
			if (arg.short_modifier)
			{
				arg.double_short_modifier = true;
				arg.short_modifier = false;
			}
			arg.short_modifier = true;
		}
		else if (*ptr == 'z')
		{
			arg.long_modifier = true;
		}
		else if (*ptr == '#')
		{
			arg.alternate_form = true;
		}
		else if (*ptr == '.')
		{
			ptr++;
			arg.precision = ft_atoi(ptr);
			arg.has_precision = true;
			while (ft_isdigit(*ptr) && *ptr != '\0')
				ptr++;
			ptr--;
		}
		else if (*ptr == '0')
		{
			if (arg.left_adjust == false)
				arg.pad_with_zero = true;
			while (*ptr == '0')
				ptr++;
			ptr--;
		}
		else if (ft_isdigit(*ptr))
		{
			arg.min_width = ft_atoi(ptr);
			while (ft_isdigit(*ptr) && *ptr != '\0')
				ptr++;
			ptr--;
		}
		ptr++;
	}
	*consumed = (int)(ptr - string);
	return (arg);
}

int		ft_printf(const char *string, ...)
{
	va_list	list;
	t_array	output;
	t_arg	arg;
	int		consumed;
	int		error;

	error = 0;
	output = array_create(sizeof(char), 64);
	va_start(list, string);
	while (*string)
	{
		if (*string == '%')
		{
			string++;
			arg = get_next_arg(string, &consumed);
			string += consumed;
			process_arg(&output, arg, list, &error);
			if (error)
				return -1;
		}
		else
		{
			consume_non_arg(string, &output, &consumed);
			string += consumed;
		}
	}
	va_end(list);
	write(1, output.data, (size_t)output.size);
	free(output.data);
	return output.size;
}

void	append_n_chars(t_array *array, char c, int i)
{
	while (i-- > 0)
		array_append(array, &c, 1);
}

void process_arg(t_array *output, t_arg arg, va_list list, int *error)
{
	long l;
	unsigned long ul;

	if (arg.token == 'd')
	{
		l = va_arg(list, long);
		if (arg.long_modifier)
			print_int(output, arg, l);
		else if (arg.double_short_modifier)
			print_int(output, arg, (char)l);
		else if (arg.short_modifier)
			print_int(output, arg, (short)l);
		else
			print_int(output, arg, (int)l);
	}
	else if (arg.token == 'u')
	{
		ul = va_arg(list, unsigned long);
		if (arg.long_modifier)
			print_uint(output, arg, ul);
		else if (arg.double_short_modifier)
			print_uint(output, arg, (unsigned char)ul);
		else if (arg.short_modifier)
			print_uint(output, arg, (unsigned short)ul);
		else
			print_uint(output, arg, (unsigned int)ul);
	}
	else if (arg.token == 'o')
	{
		ul = va_arg(list, unsigned long);
		if (arg.long_modifier)
			print_octal(output, arg, ul);
		else if (arg.double_short_modifier)
			print_octal(output, arg, (unsigned char)ul);
		else if (arg.short_modifier)
			print_octal(output, arg, (unsigned short)ul);
		else
			print_octal(output, arg, (unsigned int)ul);
	}
	else if (arg.token == 'x')
	{
		ul = va_arg(list, unsigned long);
		if (arg.long_modifier)
			print_hex(output, arg, ul);
		else if (arg.double_short_modifier)
			print_hex(output, arg, (unsigned char)ul);
		else if (arg.short_modifier)
			print_hex(output, arg, (unsigned short)ul);
		else
			print_hex(output, arg, (unsigned int)ul);
	}
	else if (arg.token == 'p')
	{
		ul = va_arg(list, unsigned long);
		print_address(output, arg, ul);
	}
	else if (arg.token == 'c')
	{
		ul = va_arg(list, unsigned long);
		print_char(output, arg, (unsigned char)ul);
	}
	else if (arg.token == 'C')
	{
		ul = va_arg(list, unsigned long);
		print_wchar(output, arg, (wchar_t) ul, error);
	}
	else if (arg.token == 's')
	{
		ul = va_arg(list, unsigned long);
		print_string(output, arg, (char *)ul);
	}
	else if (arg.token == 'S')
	{
		ul = va_arg(list, unsigned long);
		print_wstring(output, arg, (wchar_t *)ul, error);
	}
	else if (arg.token == '%')
	{
		print_percent(output, arg);
	}
}

void print_wchar(t_array *output, t_arg arg, wchar_t wc, int *error)
{
	int		blank_count;
	char	pad_char;
	int		byte_count;

	pad_char = (arg.pad_with_zero && !arg.left_adjust) ? '0' : ' ';
	char buffer[MB_LEN_MAX] = {};
	byte_count = ft_wctomb(buffer, wc);
	if (byte_count == 0)
	{
		*error = true;
		return ;
	}
	blank_count = ft_max(arg.min_width - byte_count, 0);
	if (arg.left_adjust == false)
		append_n_chars(output, pad_char, blank_count);
	array_append(output, buffer, byte_count);
	if (arg.left_adjust)
		append_n_chars(output, pad_char, blank_count);
}

void print_string(t_array *output, t_arg arg, char *string)
{
	int		i;
	int		written_char_count;
	size_t	str_len;
	int		blank_count;
	char	pad_char;

	pad_char = (arg.pad_with_zero && !arg.left_adjust) ? '0' : ' ';
	string = (string) ? string : "(null)";
	str_len = ft_strlen(string);
	written_char_count = str_len;
	if (arg.has_precision && arg.precision < str_len)
		written_char_count = arg.precision;
	blank_count = ft_max(arg.min_width - written_char_count, 0);
	if (arg.left_adjust == false)
		append_n_chars(output, pad_char, blank_count);
	i = 0;
	while (string[i] != 0 && i < written_char_count)
	{
		array_append(output, string + i, 1);
		i++;
	}
	if (arg.left_adjust)
		append_n_chars(output, pad_char, blank_count);
}
// For wchar* strings, the precision and width are the max/min count of BYTES
// that can be written, not the actual character count
// If we reach an invalid sequence, dont print anything
void print_wstring(t_array *output, t_arg arg, wchar_t *string, int *error)
{
	int		i;
	size_t	max_written_byte_count;
	size_t	written_byte_count;
	int		blank_count;
	char	pad_char;
	char	buffer[MB_LEN_MAX] = {};

	pad_char = (arg.pad_with_zero && !arg.left_adjust) ? '0' : ' ';
	string = (string) ? string : L"(null)";
	if (arg.has_precision)
		max_written_byte_count = ft_get_fitting_mb_size(string, arg.precision, error);
	else
		max_written_byte_count = ft_get_mb_size(string, error);
	if (*error)
		return;
	blank_count = ft_max(arg.min_width - max_written_byte_count, 0);
	if (arg.left_adjust == false)
		append_n_chars(output, pad_char, blank_count);
	i = 0;
	written_byte_count = 0;
	while (string[i] != 0 && written_byte_count < max_written_byte_count)
	{
		ft_memset(buffer, 0, MB_LEN_MAX);
		int byte_count = ft_wctomb(buffer, string[i]);
		*error = (byte_count == 0);
		if (*error)
			return;
		if (written_byte_count + byte_count > max_written_byte_count)
			break;
		written_byte_count += byte_count;
		array_append(output, buffer, byte_count);
		i++;
	}
	if (arg.left_adjust)
		append_n_chars(output, pad_char, blank_count);
}

void print_char(t_array *output, t_arg arg, unsigned char uc)
{
	int		blank_count;
	char	pad_char;

	pad_char = (arg.pad_with_zero && !arg.left_adjust) ? '0' : ' ';
	blank_count = ft_max(arg.min_width - 1, 0);
	if (arg.left_adjust == false)
		append_n_chars(output, pad_char, blank_count);
	array_append(output, &uc, 1);
	if (arg.left_adjust)
		append_n_chars(output, pad_char, blank_count);
}

void print_address(t_array *output, t_arg arg, unsigned long ul)
{
	size_t	hextoa_len;
	char	*hextoa;
	int		blank_count;
	int		zero_count;

	hextoa = ft_hextoa(ul, false);
	hextoa_len = ft_strlen(hextoa);
	if (arg.precision == 0 && ul == 0 && arg.has_precision)
		hextoa_len--;
	if (arg.min_width > 0 && arg.pad_with_zero && arg.has_precision == false)
	{
		arg.precision = arg.min_width;
		arg.min_width = 0;
	}
	zero_count = ft_max(arg.precision - hextoa_len, 0);
	blank_count = ft_max(arg.min_width - 2 - (hextoa_len + zero_count), 0);
	if (arg.left_adjust == false)
		append_n_chars(output, ' ', blank_count);
	array_append(output, "0x", 2);
	append_n_chars(output, '0', zero_count);
	array_append(output, hextoa, hextoa_len);
	if (arg.left_adjust)
		append_n_chars(output, ' ', blank_count);
	free(hextoa);
}

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
		return;
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

void print_percent(t_array *output, t_arg arg)
{
	if (arg.left_adjust == false)
		append_n_chars(output, arg.pad_with_zero ? '0' : ' ', arg.min_width - 1);
	array_append(output, "%", 1);
	if (arg.left_adjust)
		append_n_chars(output, ' ', arg.min_width - 1);
}

void consume_non_arg(const char *string, t_array *array, int *consumed)
{
	int	start_idx;

	start_idx = get_first_index(string, '%');
	if (start_idx == -1)
	{
		start_idx = (int)ft_strlen(string);
	}
	array_append(array, (void *)string, (size_t)start_idx);
	*consumed = start_idx;
}
