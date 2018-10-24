/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_atoi.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tdarchiv <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/02/09 09:37:34 by tdarchiv          #+#    #+#             */
/*   Updated: 2018/04/07 17:15:04 by tdarchiv         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

#include <limits.h>

static int	check_over_under_flow(unsigned long number, int sign)
{
	if (number > LONG_MAX && sign == 1)
		return (-1);
	if (number > LONG_MAX && sign == -1)
		return (0);
	return ((int)number * sign);
}

static int	get_start_index(const char *str)
{
	int i;

	i = 0;
	while (str[i] == ' '
		|| str[i] == '\f'
		|| str[i] == '\t'
		|| str[i] == '\n'
		|| str[i] == '\r'
		|| str[i] == '\v')
		i++;
	return (i);
}

int			ft_atoi(const char *str)
{
	int		i;
	size_t	number;
	size_t	length;
	int		sign;

	length = ft_strlen(str);
	number = 0;
	if (length == 0)
		return (0);
	i = get_start_index(str);
	sign = (str[i] == '-') ? -1 : 1;
	if (str[i] == '-' || str[i] == '+')
		i++;
	while (str[i] >= '0' && str[i] <= '9')
	{
		number *= 10;
		number += str[i] - '0';
		i++;
	}
	return (check_over_under_flow(number, sign));
}
