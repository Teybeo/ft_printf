/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing_functions_2.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tdarchiv <tdarchiv@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/11/26 21:22:52 by tdarchiv          #+#    #+#             */
/*   Updated: 2018/11/26 21:22:52 by tdarchiv         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "parsing.h"

#include <stdbool.h>
#include "libft.h"

/*
** '+' or ' '. Don't replace a previous '+' with ' ' (plus takes priority)
*/

bool	positive_prefix(t_arg *arg, const char **ptr)
{
	if (**ptr == ' ' && arg->plus_sign != '+')
		arg->plus_sign = ' ';
	else
		arg->plus_sign = '+';
	return (false);
}

bool	hashtag_token(t_arg *arg, const char **ptr)
{
	(void)ptr;
	arg->alternat_form = true;
	return (false);
}

bool	precision_parsing(t_arg *arg, const char **ptr)
{
	const char	*ptr_tmp;

	ptr_tmp = *ptr;
	ptr_tmp++;
	arg->precision = (size_t)ft_atoi(ptr_tmp);
	arg->has_precision = true;
	while (ft_isdigit(*ptr_tmp) && *ptr_tmp != '\0')
		ptr_tmp++;
	ptr_tmp--;
	*ptr = ptr_tmp;
	return (false);
}

bool	field_width_parsing(t_arg *arg, const char **ptr)
{
	const char	*ptr_tmp;

	ptr_tmp = *ptr;
	arg->min_width = (size_t)ft_atoi(ptr_tmp);
	while (ft_isdigit(*ptr_tmp) && *ptr_tmp != '\0')
		ptr_tmp++;
	ptr_tmp--;
	*ptr = ptr_tmp;
	return (false);
}

bool	left_adjust_token(t_arg *arg, const char **ptr)
{
	(void)ptr;
	arg->left_adjust = true;
	arg->pad_with_zero = false;
	return (false);
}
