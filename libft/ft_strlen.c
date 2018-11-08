/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strlen.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tdarchiv <tdarchiv@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/04/06 18:06:47 by tdarchiv          #+#    #+#             */
/*   Updated: 2018/11/08 18:38:25 by tdarchiv         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

#include <stddef.h>
#include <limits.h>

size_t	ft_strlen(const char *s)
{
	size_t i;

	i = 0;
	while (s[i] != '\0')
		i++;
	return (i);
}

size_t	ft_get_mb_size(const wchar_t *s)
{
	size_t	i;
	size_t	byte_count;
	char	buffer[MB_LEN_MAX];

	i = 0;
	byte_count = 0;
	while (s[i] != '\0')
	{
		byte_count += ft_wctomb(buffer, s[i]);
		i++;
	}
	return (byte_count);
}

size_t	ft_get_fitting_mb_size(wchar_t *s, size_t max_size)
{
	size_t	i;
	size_t	byte_count;
	int		mbchar_size;
	char	buffer[MB_LEN_MAX];

	i = 0;
	byte_count = 0;
	while (s[i] != '\0')
	{
		mbchar_size = ft_wctomb(buffer, s[i]);
		if (byte_count + mbchar_size > max_size)
			return byte_count;
		byte_count += mbchar_size;
		i++;
	}
	return byte_count;
}