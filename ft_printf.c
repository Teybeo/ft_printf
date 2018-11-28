/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printf.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tdarchiv <tdarchiv@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/11/28 15:26:56 by tdarchiv          #+#    #+#             */
/*   Updated: 2018/11/28 17:39:31 by tdarchiv         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

#include <array.h>
#include <stdarg.h>
#include <stdlib.h>
#include <unistd.h>

#include "libft.h"
#include "parsing.h"
#include "processing.h"

int		get_first_index(const char *string, char c)
{
	int	i;

	i = 0;
	while (string[i] != c && string[i] != '\0')
		i++;
	return (string[i] != '\0' ? i : -1);
}

void	consume_non_arg(const char *string, t_array *array, int *consumed)
{
	int	start_idx;

	start_idx = get_first_index(string, '%');
	if (start_idx == -1)
	{
		start_idx = (int)ft_strlen(string);
	}
	array_append(array, (void *)string, (size_t)start_idx);
	*consumed = start_idx;
}

int		real_printf(t_array *output, const char *format, va_list list)
{
	t_arg	arg;
	int		consumed;
	int		error;

	error = 0;
	*output = array_create(sizeof(char), 64);
	while (*format)
	{
		if (*format == '%')
		{
			format++;
			arg = get_next_arg(format, &consumed);
			format += consumed;
			process_arg2(output, arg, list, &error);
			if (error)
				return (-1);
		}
		else
		{
			consume_non_arg(format, output, &consumed);
			format += consumed;
		}
	}
	return (output->size);
}
