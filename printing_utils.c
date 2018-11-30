/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   printing_utils.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tdarchiv <tdarchiv@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/11/29 17:06:50 by tdarchiv          #+#    #+#             */
/*   Updated: 2018/11/30 18:18:11 by tdarchiv         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "printing.h"
#include "array.h"

void	format_string(t_array *output, t_format_result format)
{
	if (format.left_adjust == false)
		append_n_chars(output, ' ', format.blank_count);
	array_append(output, format.prefix, format.prefix_len);
	append_n_chars(output, '0', format.zero_count);
	array_append(output, format.string, format.str_len);
	if (format.left_adjust)
		append_n_chars(output, ' ', format.blank_count);
}

void	append_n_chars(t_array *array, char c, int i)
{
	while (i-- > 0)
		array_append(array, &c, 1);
}

void	print_b(t_array *output, t_arg arg, va_list list, int *error)
{
	int		i;
	int		bit;
	char	*byte;

	if (arg.min_width == 0)
		arg.min_width = 4;
	i = (int)arg.min_width - 1;
	byte = va_arg(list, char*);
	while (i >= 0)
	{
		bit = 7;
		while (bit >= 0)
		{
			array_append(output, (byte[i] & (1 << bit)) ? "1" : "0", 1);
			bit--;
		}
		array_append(output, " ", 1);
		i--;
	}
	(void)error;
}
