/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   printing.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tdarchiv <tdarchiv@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/11/27 17:48:48 by tdarchiv          #+#    #+#             */
/*   Updated: 2018/11/30 17:52:35 by tdarchiv         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "processing.h"

#include "parsing.h"
#include "array.h"
#include "printing.h"

#include <stdarg.h>

typedef void	(*t_printing_fn)(t_array *, t_arg, va_list list, int *);

static void	init_table(t_printing_fn table[128])
{
	int i;

	i = 0;
	while (i < 128)
		table[i++] = print_invalid;
	table['d'] = print_d;
	table['u'] = print_u;
	table['o'] = print_o;
	table['x'] = print_x;
	table['p'] = print_p;
	table['c'] = print_c;
	table['C'] = print_wc;
	table['s'] = print_s;
	table['S'] = print_ws;
	table['f'] = print_f;
	table['F'] = print_f;
	table['%'] = print_percent;
	table['b'] = print_b;
}

void		process_arg2(t_array *output, t_arg arg, va_list list, int *error)
{
	static t_printing_fn	printing_fn_table[128] = {NULL};
	t_printing_fn			function;

	if (printing_fn_table[0] == NULL)
		init_table(printing_fn_table);
	function = printing_fn_table[(int)arg.token];
	function(output, arg, list, error);
}
