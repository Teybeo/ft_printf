#include "ft_printf.h"
#include "libft.h"

#include "array.h"

#include <stdio.h>
#include <zconf.h>
#include <stdbool.h>
#include <stdlib.h>
#include <assert.h>

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
	bool long_modifier;
	bool has_precision;
	size_t min_width;
	size_t precision;
//	ft_token fn;
	char token;
	char plus_sign;
};

void process_arg(t_array *output, t_arg arg, va_list list);
void consume_non_arg(const char *string, t_array *array, int *consumed);

void print_int32(t_array *output, t_arg arg, va_list list);
void print_int64(t_array *output, t_arg arg, va_list list);
void print_uint32(t_array *output, t_arg arg, va_list list);
void print_uint64(t_array *output, t_arg arg, va_list list);
void print_percent(t_array *output, t_arg arg);

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
		else if (*ptr == 'l')
		{
			arg.long_modifier = true;
		}
		else if (*ptr == 'z')
		{
			arg.long_modifier = true;
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

	output = array_create(sizeof(char), 64);
	va_start(list, string);
	while (*string)
	{
		if (*string == '%')
		{
			string++;
			arg = get_next_arg(string, &consumed);
			string += consumed;
			process_arg(&output, arg, list);
		}
		else
		{
			consume_non_arg(string, &output, &consumed);
			string += consumed;
		}
	}
	va_end(list);
	write(1, output.data, (size_t)output.size);
	return output.size;
}

void	append_n_chars(t_array *array, char c, int i)
{
	while (i-- > 0)
		array_append(array, &c, 1);
}

void process_arg(t_array *output, t_arg arg, va_list list)
{
	if (arg.token == 'd')
	{
		if (arg.long_modifier)
			print_int64(output, arg, list);
		else
			print_int32(output, arg, list);
	}
	else if (arg.token == 'u')
	{
		if (arg.long_modifier)
			print_uint64(output, arg, list);
		else
			print_uint32(output, arg, list);
	}
	else if (arg.token == '%')
	{
		print_percent(output, arg);
	}
}

void print_percent(t_array *output, t_arg arg)
{
	if (arg.left_adjust == false)
		append_n_chars(output, arg.pad_with_zero ? '0' : ' ', arg.min_width - 1);
	array_append(output, "%", 1);
	if (arg.left_adjust)
		append_n_chars(output, ' ', arg.min_width - 1);
}

void print_integer(t_array *output, t_arg arg, char *itoa, size_t itoa_len)
{
	int		is_neg;
	int		has_sign_char;
	size_t	blank_count;
	size_t	zero_count;
	size_t	digit_count;

	is_neg = itoa[0] == '-';
	has_sign_char = ft_isdigit(itoa[0]) == false;
	digit_count = itoa_len - has_sign_char;
	ft_memcpy(itoa, itoa + has_sign_char, digit_count);
	if (arg.min_width > 0 && arg.pad_with_zero && arg.has_precision == false)
	{
		arg.precision = arg.min_width - has_sign_char;
		arg.min_width = 0;
	}
	zero_count =  ft_max(arg.precision - digit_count, 0);
	blank_count = ft_max(arg.min_width - (itoa_len + zero_count), 0);
//	printf("\n[zero_count: %d]\n", zero_count);
//	printf("[blank_count: %d]\n", blank_count);
	if (arg.left_adjust == false)
		append_n_chars(output, ' ', blank_count);
	if (has_sign_char)
		array_append(output, (is_neg) ? "-" : &arg.plus_sign, 1);
	append_n_chars(output, '0', zero_count);
	array_append(output, itoa, itoa_len - has_sign_char);
	if (arg.left_adjust)
		append_n_chars(output, ' ', blank_count);
}

void print_int64(t_array *output, t_arg arg, va_list list)
{
	char	*ltoa;
	long	l;

	l = va_arg(list, long);
	// If precision is 0 and value is 0, dont print 0 but still print prefix
	if (l == 0 && arg.has_precision && arg.precision == 0)
	{
		if (arg.plus_sign)
			array_append(output, &arg.plus_sign, 1);
		return;
	}
	ltoa = ft_ltoa_sign(l, arg.plus_sign);
	print_integer(output, arg, ltoa, ft_strlen(ltoa));
	free(ltoa);
}

void print_int32(t_array *output, t_arg arg, va_list list)
{
	char	*itoa;
	int		d;

	d = va_arg(list, int);
	// If precision is 0 and value is 0, dont print 0 but still print prefix
	if (d == 0 && arg.has_precision && arg.precision == 0)
	{
		if (arg.plus_sign)
			array_append(output, &arg.plus_sign, 1);
		return;
	}
	itoa = ft_itoa_sign(d, arg.plus_sign);
	print_integer(output, arg, itoa, ft_strlen(itoa));
	free(itoa);
}

void print_uint32(t_array *output, t_arg arg, va_list list)
{
	char			*utoa;
	unsigned int	u;

	u = va_arg(list, unsigned int);
	// If precision is 0 and value is 0, dont print 0 but still print prefix
	if (u == 0 && arg.has_precision && arg.precision == 0)
	{
		if (arg.plus_sign)
			array_append(output, &arg.plus_sign, 1);
		return;
	}
	utoa = ft_ltoa_sign(u, arg.plus_sign);
	print_integer(output, arg, utoa, ft_strlen(utoa));
	free(utoa);
}

void print_uint64(t_array *output, t_arg arg, va_list list)
{
	char			*lutoa;
	unsigned long int	lu;

	lu = va_arg(list, unsigned long int);
	// If precision is 0 and value is 0, dont print 0 but still print prefix
	if (lu == 0 && arg.has_precision && arg.precision == 0)
	{
		if (arg.plus_sign)
			array_append(output, &arg.plus_sign, 1);
		return;
	}
	lutoa = ft_lutoa_sign(lu, arg.plus_sign);
	print_integer(output, arg, lutoa, ft_strlen(lutoa));
	free(lutoa);
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
