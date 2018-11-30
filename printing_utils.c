/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   printing_utils.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tdarchiv <tdarchiv@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/11/29 17:06:50 by tdarchiv          #+#    #+#             */
/*   Updated: 2018/11/29 17:06:50 by tdarchiv         ###   ########.fr       */
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
