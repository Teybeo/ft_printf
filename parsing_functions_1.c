/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing_functions_1.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tdarchiv <tdarchiv@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/11/26 21:22:01 by tdarchiv          #+#    #+#             */
/*   Updated: 2018/11/26 21:22:03 by tdarchiv         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "parsing.h"

#include <stdbool.h>
#include "libft.h"

bool	simple_token(t_arg *arg, const char **ptr)
{
	arg->token = **ptr;
	(*ptr)++;
	return (true);
}

bool	integer_tokens(t_arg *arg, const char **ptr)
{
	char	token;

	token = **ptr;
	arg->token = (char)ft_tolower(token);
	if (token == 'D' || token == 'O' || token == 'U')
		arg->long_modifier = true;
	if (token == 'X')
		arg->uppercase_prefix = true;
	if (arg->token == 'u')
		arg->plus_sign = false;
	if (arg->token == 'i')
		arg->token = 'd';
	(*ptr)++;
	return (true);
}

bool	char_string_tokens(t_arg *arg, const char **ptr)
{
	arg->token = (arg->long_modifier ? (char)ft_toupper(**ptr) : **ptr);
	(*ptr)++;
	return (true);
}

bool	modifiers_tokens(t_arg *arg, const char **ptr)
{
	char	token;

	token = **ptr;
	if (token == 'l' || token == 'z' || token == 'j')
		arg->long_modifier = true;
	else if (token == 'h')
	{
		arg->double_short_modifier = arg->short_modifier;
		arg->short_modifier = true;
	}
	return (false);
}

/*
** '0' is ignored when '-' used. Don't set it if a previous '-'
*/

bool	zero_tokens(t_arg *arg, const char **ptr)
{
	const char	*ptr_tmp;

	ptr_tmp = *ptr;
	if (arg->left_adjust == false)
		arg->pad_with_zero = true;
	while (*ptr_tmp == '0')
		ptr_tmp++;
	ptr_tmp--;
	*ptr = ptr_tmp;
	return (false);
}
