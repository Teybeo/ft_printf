/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_itoa.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tdarchiv <tdarchiv@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/04/09 19:36:35 by tdarchiv          #+#    #+#             */
/*   Updated: 2018/04/09 19:49:15 by tdarchiv         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdlib.h>

static int	ft_power(int power)
{
	if (power <= 0)
		return (1);
	return (10 * ft_power(power - 1));
}

static void	*itoa_alloc_string(int *len, int nb)
{
	int		number;
	int		str_len;
	char	*temp;

	str_len = 0;
	number = (nb < 0) ? -nb : nb;
	while (number != 0)
	{
		number /= 10;
		str_len++;
	}
	*len = str_len;
	if (nb < 0)
		str_len++;
	if (nb == 0)
		str_len++;
	temp = malloc(sizeof(char) * (str_len + 1));
	if (temp == NULL)
		return (NULL);
	temp[str_len] = '\0';
	return (temp);
}

char		*ft_itoa(int nb)
{
	unsigned int	number;
	int				diviseur;
	int				len;
	char			*string;
	char			*tmp;

	string = itoa_alloc_string(&len, nb);
	if (string == NULL)
		return (NULL);
	tmp = string;
	if (nb == 0)
		*string = '0';
	number = (nb < 0) ? -nb : nb;
	if (nb < 0)
		*tmp++ = '-';
	diviseur = ft_power(len - 1);
	while (diviseur > 0)
	{
		*tmp++ = (char)('0' + (number / diviseur));
		number %= diviseur;
		diviseur /= 10;
	}
	return (string);
}
