/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   memset.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tdarchiv <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/04/05 12:48:35 by tdarchiv          #+#    #+#             */
/*   Updated: 2018/11/21 16:10:23 by tdarchiv         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	*ft_memset(void *dest, int value, size_t count)
{
	size_t i;

	i = 0;
	while (i < count)
	{
		((char*)dest)[i] = (unsigned char)(value);
		i++;
	}
	return (dest);
}
