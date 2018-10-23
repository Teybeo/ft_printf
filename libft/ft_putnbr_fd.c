/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_putnbr_fd.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tdarchiv <tdarchiv@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/04/10 11:51:26 by tdarchiv          #+#    #+#             */
/*   Updated: 2018/04/10 12:03:19 by tdarchiv         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	ft_putnbr_fd(int nb, int fd)
{
	int				quotient;
	int				diviseur;
	char			do_print;
	unsigned int	number;

	if (nb == 0)
		ft_putchar_fd('0', fd);
	number = nb;
	if (nb < 0)
	{
		ft_putchar_fd('-', fd);
		number = nb * -1;
	}
	diviseur = 1000000000;
	do_print = 0;
	while (diviseur > 0)
	{
		quotient = number / diviseur;
		number -= quotient * diviseur;
		do_print |= quotient > 0;
		if (do_print)
			ft_putchar_fd('0' + quotient, fd);
		diviseur /= 10;
	}
}
