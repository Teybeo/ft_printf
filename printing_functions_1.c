/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   printing_functions_1.c                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tdarchiv <tdarchiv@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/11/28 15:22:04 by tdarchiv          #+#    #+#             */
/*   Updated: 2018/11/29 16:06:39 by tdarchiv         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "printing.h"

#include <stdlib.h>
#include "libft.h"

void	print_hex(t_array *output, t_arg arg, unsigned long o)
{
	char			*hextoa;
	int				has_prefix;
	t_format_result	fmt;

	has_prefix = (arg.alternat_form && o != 0);
	hextoa = ft_hextoa(o, arg.uppercase_prefix);
	if (o == 0 && arg.has_precision && arg.precision == 0)
		hextoa[0] = '\0';
	if (o == 0 && arg.has_precision && arg.precision == 0 && arg.min_width == 0)
		return ;
	fmt.str_len = ft_strlen(hextoa);
	arg.min_width = ft_max(arg.min_width - has_prefix * 2, 0);
	if (arg.min_width > 0 && arg.pad_with_zero && arg.has_precision == false)
	{
		arg.precision = arg.min_width;
		arg.min_width = 0;
	}
	fmt.zero_count = ft_max(arg.precision - fmt.str_len, 0);
	fmt.blank_count = ft_max(arg.min_width - (fmt.str_len + fmt.zero_count), 0);
	fmt.left_adjust = arg.left_adjust;
	fmt.prefix = arg.uppercase_prefix ? "0X" : "0x";
	fmt.prefix_len = (arg.alternat_form && o > 0) ? 2 : 0;
	fmt.string = hextoa;
	format_string(output, fmt);
	free(hextoa);
}

void	print_octal(t_array *output, t_arg arg, unsigned long o)
{
	t_format_result	fmt;
	int				has_prefix;

	has_prefix = (arg.alternat_form && o != 0);
	fmt.string = ft_otoa(o);
	if (o == 0 && arg.has_precision && arg.precision == 0 && !arg.alternat_form)
	{
		fmt.string[0] = '\0';
		if (arg.min_width == 0)
			return ;
	}
	fmt.str_len = ft_strlen(fmt.string);
	if (arg.min_width > 0 && arg.pad_with_zero && arg.has_precision == false)
	{
		arg.precision = arg.min_width;
		arg.min_width = 0;
	}
	fmt.zero_count = ft_max(arg.precision - fmt.str_len, 0);
	fmt.zero_count = (fmt.zero_count) ? fmt.zero_count : has_prefix;
	fmt.blank_count = ft_max(arg.min_width - (fmt.str_len + fmt.zero_count), 0);
	fmt.prefix_len = 0;
	fmt.left_adjust = arg.left_adjust;
	format_string(output, fmt);
	free(fmt.string);
}

void	print_integer(t_array *output, t_arg arg, char *itoa, size_t itoa_len)
{
	int				is_neg;
	int				has_sign_char;
	t_format_result	fmt;

	is_neg = itoa[0] == '-';
	has_sign_char = ft_isdigit(itoa[0]) == false && (itoa[0] != '\0');
	fmt.str_len = ft_max(itoa_len - has_sign_char, 0);
	ft_memcpy(itoa, itoa + has_sign_char, fmt.str_len);
	if (arg.min_width > 0 && arg.pad_with_zero && arg.has_precision == false)
	{
		arg.precision = arg.min_width - has_sign_char;
		arg.min_width = 0;
	}
	fmt.zero_count = ft_max(arg.precision - fmt.str_len, 0);
	fmt.blank_count = ft_max(arg.min_width - (itoa_len + fmt.zero_count), 0);
	fmt.prefix = (is_neg) ? "-" : &arg.plus_sign;
	fmt.prefix_len = has_sign_char;
	fmt.string = itoa;
	fmt.left_adjust = arg.left_adjust;
	format_string(output, fmt);
}

/*
** If working precision is 0 and value is 0, dont print 0 but still print prefix
*/

void	print_int(t_array *output, t_arg arg, long l)
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

void	print_uint(t_array *output, t_arg arg, unsigned long l)
{
	char	*ultoa;

	ultoa = ft_ultoa_sign(l, arg.plus_sign);
	if (l == 0 && arg.has_precision && arg.precision == 0)
		ultoa[arg.plus_sign != 0] = '\0';
	print_integer(output, arg, ultoa, ft_strlen(ultoa));
	free(ultoa);
}
