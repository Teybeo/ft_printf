/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   printing_functions_1.c                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tdarchiv <tdarchiv@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/11/27 17:48:23 by tdarchiv          #+#    #+#             */
/*   Updated: 2018/11/27 17:48:25 by tdarchiv         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "printing.h"

void	print_d(t_array *output, t_arg arg, va_list list, int *error)
{
	long	l;

	l = va_arg(list, long);
	if (arg.long_modifier)
		print_int(output, arg, l);
	else if (arg.double_short_modifier)
		print_int(output, arg, (char)l);
	else if (arg.short_modifier)
		print_int(output, arg, (short)l);
	else
		print_int(output, arg, (int)l);
	(void)error;
}

void	print_u(t_array *output, t_arg arg, va_list list, int *error)
{
	unsigned long	ul;

	ul = va_arg(list, unsigned long);
	if (arg.long_modifier)
		print_uint(output, arg, ul);
	else if (arg.double_short_modifier)
		print_uint(output, arg, (unsigned char)ul);
	else if (arg.short_modifier)
		print_uint(output, arg, (unsigned short)ul);
	else
		print_uint(output, arg, (unsigned int)ul);
	(void)error;
}

void	print_o(t_array *output, t_arg arg, va_list list, int *error)
{
	unsigned long	ul;

	ul = va_arg(list, unsigned long);
	if (arg.long_modifier)
		print_octal(output, arg, ul);
	else if (arg.double_short_modifier)
		print_octal(output, arg, (unsigned char)ul);
	else if (arg.short_modifier)
		print_octal(output, arg, (unsigned short)ul);
	else
		print_octal(output, arg, (unsigned int)ul);
	(void)error;
}

void	print_x(t_array *output, t_arg arg, va_list list, int *error)
{
	unsigned long	ul;

	ul = va_arg(list, unsigned long);
	if (arg.long_modifier)
		print_hex(output, arg, ul);
	else if (arg.double_short_modifier)
		print_hex(output, arg, (unsigned char)ul);
	else if (arg.short_modifier)
		print_hex(output, arg, (unsigned short)ul);
	else
		print_hex(output, arg, (unsigned int)ul);
	(void)error;
}

void	print_p(t_array *output, t_arg arg, va_list list, int *error)
{
	print_address(output, arg, va_arg(list, unsigned long));
	(void)error;
}
