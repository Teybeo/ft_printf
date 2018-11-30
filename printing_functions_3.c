/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   printing_functions_3.c                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tdarchiv <tdarchiv@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/11/28 15:25:08 by tdarchiv          #+#    #+#             */
/*   Updated: 2018/11/30 16:56:54 by tdarchiv         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "printing.h"

#include <stdlib.h>
#include <stdio.h>
#include <math.h>
#include <assert.h>
#include "libft.h"

void	print_invalid(t_array *output, t_arg arg, va_list list, int *error)
{
	if (arg.left_adjust == false)
		append_n_chars(output, arg.pad_with_zero ? '0' : ' ',
				arg.min_width - 1);
	if (ft_isprint(arg.token))
		array_append(output, &arg.token, 1);
	if (arg.left_adjust)
		append_n_chars(output, ' ', arg.min_width - 1);
	(void)list;
	(void)error;
}

void	append_real_part(t_array *output, t_arg arg, long double value,
		int blank_count)
{
	char		digit;
	long double	temp_value;

	if (arg.precision)
		array_append(output, ".", 1);
	value = ft_abs_double(value);
	value = value - (long)value;
	temp_value = value;
	while (arg.precision > 0)
	{
		temp_value *= 10;
		digit = ((char)temp_value) + '0';
		array_append(output, &digit, 1);
		temp_value -= (unsigned long)temp_value;
		arg.precision--;
	}
	if (arg.left_adjust)
		append_n_chars(output, ' ', blank_count);
}

void	print_float(t_array *output, t_arg arg, long double value)
{
	char			has_sign_char;
	size_t			digit_count;
	t_format_result	fmt;

	if (arg.has_precision == false)
	{
		arg.has_precision = true;
		arg.precision = 6;
	}
	fmt.string = ft_ltoa_sign(value, arg.plus_sign);
	fmt.str_len = ft_strlen(fmt.string);
	has_sign_char = ft_isdigit(fmt.string[0]) == false;
	digit_count =
			fmt.str_len + (arg.has_precision && arg.precision) + arg.precision;
	ft_memcpy(fmt.string, fmt.string + has_sign_char, fmt.str_len);
	fmt.zero_count = arg.pad_with_zero *
	ft_max(arg.min_width - (digit_count + has_sign_char + arg.precision), 0);
	fmt.blank_count = ft_max(arg.min_width - (digit_count + fmt.zero_count), 0);
	append_n_chars(output, ' ', fmt.blank_count * (arg.left_adjust == false));
	if (has_sign_char)
		array_append(output, (value < 0) ? "-" : &arg.plus_sign, 1);
	append_n_chars(output, '0', fmt.zero_count);
	array_append(output, fmt.string, ft_strlen(fmt.string));
	append_real_part(output, arg, value, fmt.blank_count);
	free(fmt.string);
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
		append_n_chars(output, arg.pad_with_zero ? '0' : ' ',
				arg.min_width - 1);
	array_append(output, "%", 1);
	if (arg.left_adjust)
		append_n_chars(output, ' ', arg.min_width - 1);
	(void)list;
	(void)error;
}
