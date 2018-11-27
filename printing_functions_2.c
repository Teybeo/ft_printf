/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   printing_functions_2.c                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tdarchiv <tdarchiv@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/11/27 17:48:12 by tdarchiv          #+#    #+#             */
/*   Updated: 2018/11/27 17:48:14 by tdarchiv         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "printing.h"

void	print_c(t_array *output, t_arg arg, va_list list, int *error)
{
	unsigned long ul;

	ul = va_arg(list, unsigned long);
	print_char(output, arg, (unsigned char)ul);
	(void)error;
}

void	print_wc(t_array *output, t_arg arg, va_list list, int *error)
{
	unsigned long ul;

	ul = va_arg(list, unsigned long);
	print_wchar(output, arg, (wchar_t)ul, error);
	(void)error;
}

void	print_s(t_array *output, t_arg arg, va_list list, int *error)
{
	unsigned long ul;

	ul = va_arg(list, unsigned long);
	print_string(output, arg, (char *)ul);
	(void)error;
}

void	print_ws(t_array *output, t_arg arg, va_list list, int *error)
{
	unsigned long ul;

	ul = va_arg(list, unsigned long);
	print_wstring(output, arg, (wchar_t *)ul, error);
	(void)error;
}

void	print_f(t_array *output, t_arg arg, va_list list, int *error)
{
	print_float(output, arg, va_arg(list, double));
	(void)error;
}
