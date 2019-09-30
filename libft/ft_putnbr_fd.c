/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_putnbr_fd.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hdwarven <hdwarven@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/11/29 19:20:42 by hdwarven          #+#    #+#             */
/*   Updated: 2019/09/03 10:27:10 by hdwarven         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static long int	ft_count(long int n)
{
	long int count;

	count = 1;
	while (n > 0)
	{
		count *= 10;
		n /= 10;
	}
	return (count / 10);
}

static void		check_mult(long int mult, int fd)
{
	while (mult > 0)
	{
		ft_putchar_fd('0', fd);
		mult /= 10;
	}
}

void			ft_putnbr_fd(int n, int fd)
{
	long int	nb;
	long int	mult;

	nb = n;
	if (nb != 0)
	{
		if (nb < 0)
		{
			ft_putchar_fd('-', fd);
			nb *= -1;
		}
		mult = ft_count(nb);
		while (nb > 0)
		{
			ft_putchar_fd(nb / mult + '0', fd);
			nb %= mult;
			mult /= 10;
		}
		check_mult(mult, fd);
		return ;
	}
	ft_putchar_fd('0', fd);
}
