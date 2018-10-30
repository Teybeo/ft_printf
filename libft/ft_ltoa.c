/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_itoa.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tdarchiv <tdarchiv@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/04/09 19:36:35 by tdarchiv          #+#    #+#             */
/*   Updated: 2018/10/30 10:10:20 by tdarchiv         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdlib.h>
#include <limits.h>

static unsigned long	ft_power(int power)
{
	if (power <= 0)
		return (1);
	return (10 * ft_power(power - 1));
}

static void	*ltoa_alloc_string(int *len, long nb)
{
	long	number;
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

char		*ft_ltoa(long nb)
{
	unsigned long	number;
	long			diviseur;
	int				len;
	char			*string;
	char			*tmp;

	string = ltoa_alloc_string(&len, nb);
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


static void	*ltoa_alloc_string_sign(int *digit_count, long nb, char plus_sign)
{
	long	number;
	int		str_len;
	char	*temp;

	str_len = 0;
	number = (nb < 0) ? -nb : nb;
	while (number != 0)
	{
		number /= 10;
		str_len++;
	}
	*digit_count = str_len;
	str_len++;
	if (nb > 0 && plus_sign == 0)
		str_len--;
	if (nb == 0)
		str_len = 1;
	temp = malloc(sizeof(char) * (str_len + 1));
	if (temp == NULL)
		return (NULL);
	temp[str_len] = '\0';
	return (temp);
}

char		*ft_ltoa_sign(long nb, char plus_sign)
{
	unsigned long	number;
	long			diviseur;
	int				len;
	char			*string;
	char			*tmp;

	string = ltoa_alloc_string_sign(&len, nb, plus_sign);
	if (string == NULL)
		return (NULL);
	tmp = string;
	if (nb == 0)
		*string = '0';
	number = (nb < 0) ? -nb : nb;
	if (nb < 0)
		*tmp++ = '-';
	if (nb >= 0 && plus_sign)
		*tmp++ = plus_sign;
	diviseur = ft_power(len - 1);
	while (diviseur > 0)
	{
		*tmp++ = (char)('0' + (number / diviseur));
		number %= diviseur;
		diviseur /= 10;
	}
	return (string);
}

static void	*lutoa_alloc_string_sign(int *digit_count, unsigned long nb, char plus_sign)
{
	unsigned long	number;
	int				str_len;
	char			*temp;

	str_len = 0;
	number = nb;
	while (number != 0)
	{
		number /= 10;
		str_len++;
	}
	*digit_count = str_len;
	str_len++;
	if (nb > 0 && plus_sign == 0)
		str_len--;
	if (nb == 0)
		str_len = 1;
	temp = malloc(sizeof(char) * (str_len + 1));
	if (temp == NULL)
		return (NULL);
	temp[str_len] = '\0';
	return (temp);
}

char		*ft_lutoa_sign(unsigned long nb, char plus_sign)
{
	unsigned long	number;
	unsigned long	diviseur;
	int				len;
	char			*string;
	char			*tmp;

	string = lutoa_alloc_string_sign(&len, nb, plus_sign);
	if (string == NULL)
		return (NULL);
	tmp = string;
	if (nb == 0)
		*string = '0';
	number = nb;
	if (plus_sign)
		*tmp++ = plus_sign;
	diviseur = ft_power(len - 1);
	while (diviseur > 0)
	{
		*tmp++ = (char)('0' + (number / diviseur));
		number %= diviseur;
		diviseur /= 10;
	}
	return (string);
}
