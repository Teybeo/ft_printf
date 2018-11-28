/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   printing_functions_3.c                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tdarchiv <tdarchiv@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/11/28 15:25:08 by tdarchiv          #+#    #+#             */
/*   Updated: 2018/11/28 15:25:08 by tdarchiv         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "printing.h"

#include <stdlib.h>
#include "libft.h"

void	print_invalid(t_array *output, t_arg arg, va_list list, int *error)
{
	if (arg.left_adjust == false)
		append_n_chars(output, arg.pad_with_zero ? '0' : ' ', arg.min_width - 1);
	if (ft_isprint(arg.token))
		array_append(output, &arg.token, 1);
	if (arg.left_adjust)
		append_n_chars(output, ' ', arg.min_width - 1);
	(void)list;
	(void)error;
}

void	print_float(t_array *output, t_arg arg, double value)
{
	long	int_part;
	char	*int_string;
	char	has_sign_char;
	size_t	int_digit_count;
	size_t	digit_count; // Include the '.' and fractional part

	if (arg.has_precision == false)
	{
		arg.has_precision = true;
		arg.precision = 6;
	}
//	char is_neg = value < 0;
//	value *= is_neg * -1;
	int_part = (long int)value;
	int_string = ft_ltoa_sign(int_part, arg.plus_sign);
	int_digit_count = ft_strlen(int_string);
	has_sign_char = ft_isdigit(int_string[0]) == false;
	digit_count = int_digit_count + (arg.has_precision && arg.precision) + arg.precision;
	ft_memcpy(int_string, int_string + has_sign_char, int_digit_count);
	int zero_count = arg.pad_with_zero * ft_max(arg.min_width - (digit_count + has_sign_char + arg.precision), 0);
	int blank_count = ft_max(arg.min_width - (digit_count + has_sign_char + zero_count), 0);
//	printf("zero_count: %d\n", zero_count);
//	printf("blank_count: %d\n", blank_count);
	if (arg.left_adjust == false)
		append_n_chars(output, ' ', blank_count);
	if (has_sign_char)
		array_append(output, (value < 0) ? "-" : &arg.plus_sign, 1);
	append_n_chars(output, '0', zero_count);
//	array_append(output, itoa, digit_count);
	array_append(output, int_string, ft_strlen(int_string));
	if (arg.precision)
		array_append(output, ".", 1);
#if 0
	unsigned int precision = 1;
	long double real_part = (value - (size_t)value);
	while (precision <= arg.precision)
	{
		size_t tmp = (size_t)(real_part * powl(10, precision));
		tmp %= 10;
		char digit = (char)(tmp + '0');
		array_append(output, &digit, 1);
		precision++;
	}
#else
	int precision = (int)arg.precision;
	value = ft_abs_double(value - (long)value);
	long double temp_value;
	while (precision > 0)
	{
		temp_value = value * 10;
		char digit = ((char)temp_value) + '0';
		array_append(output, &digit, 1);
		value = temp_value - (unsigned long)temp_value;
		precision--;
	}
#endif
	if (arg.left_adjust)
		append_n_chars(output, ' ', blank_count);
	free(int_string);
}

void	print_address(t_array *output, t_arg arg, unsigned long ul)
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
		arg.precision = arg.min_width - 2;
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


void	print_percent(t_array *output, t_arg arg, va_list list, int *error)
{
	if (arg.left_adjust == false)
		append_n_chars(output, arg.pad_with_zero ? '0' : ' ', arg.min_width - 1);
	array_append(output, "%", 1);
	if (arg.left_adjust)
		append_n_chars(output, ' ', arg.min_width - 1);
	(void)list;
	(void)error;
}

void	append_n_chars(t_array *array, char c, int i)
{
	while (i-- > 0)
		array_append(array, &c, 1);
}