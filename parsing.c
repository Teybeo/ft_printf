/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tdarchiv <tdarchiv@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/11/26 16:11:18 by tdarchiv          #+#    #+#             */
/*   Updated: 2018/11/27 17:19:12 by tdarchiv         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include "parsing.h"

#include <memory.h>
#include <printf.h>

typedef bool	(*t_parsing_fn)(t_arg *, const char **);

void	table_init_part2(t_parsing_fn table[255])
{
	table['h'] = modifiers_tokens;
	table['l'] = modifiers_tokens;
	table['z'] = modifiers_tokens;
	table['j'] = modifiers_tokens;
	table[' '] = positive_prefix;
	table['+'] = positive_prefix;
	table['-'] = left_adjust_token;
	table['#'] = hashtag_token;
	table['.'] = precision_parsing;
	table['0'] = zero_tokens;
	table['1'] = field_width_parsing;
	table['2'] = field_width_parsing;
	table['3'] = field_width_parsing;
	table['4'] = field_width_parsing;
	table['5'] = field_width_parsing;
	table['6'] = field_width_parsing;
	table['7'] = field_width_parsing;
	table['8'] = field_width_parsing;
	table['9'] = field_width_parsing;
}

void	init_table(t_parsing_fn table[255])
{
	int i;

	i = 0;
	while (i < 255)
		table[i++] = simple_token;
	table['f'] = simple_token;
	table['F'] = simple_token;
	table['p'] = simple_token;
	table['C'] = simple_token;
	table['S'] = simple_token;
	table['%'] = simple_token;
	table['i'] = integer_tokens;
	table['d'] = integer_tokens;
	table['o'] = integer_tokens;
	table['u'] = integer_tokens;
	table['x'] = integer_tokens;
	table['D'] = integer_tokens;
	table['U'] = integer_tokens;
	table['O'] = integer_tokens;
	table['X'] = integer_tokens;
	table['s'] = char_string_tokens;
	table['c'] = char_string_tokens;
	table_init_part2(table);
}

t_arg	get_next_arg(const char *string, int *consumed)
{
	static t_parsing_fn	parsing_fn_table[255] = {NULL};
	t_parsing_fn		function;
	const char			*ptr;
	t_arg				arg;

	if (parsing_fn_table[0] == NULL)
		init_table(parsing_fn_table);
	ft_memset(&arg, 0, sizeof(arg));
	ptr = string;
	while (*ptr != '\0')
	{
		function = parsing_fn_table[(int)*ptr];
		if (function(&arg, &ptr))
			break ;
		ptr++;
	}
	*consumed = (int)(ptr - string);
	return (arg);
}
