/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_itoa.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hdwarven <hdwarven@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/11/29 20:58:54 by hdwarven          #+#    #+#             */
/*   Updated: 2019/09/03 10:27:10 by hdwarven         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static size_t	ft_size(long int n)
{
	size_t count;

	count = 0;
	while (n != 0)
	{
		count++;
		n /= 10;
	}
	return (count);
}

char			*ft_itoa(int nb)
{
	size_t		i;
	long		n;
	char		*tmp;

	n = nb;
	i = ft_size(n);
	tmp = ft_strnew(i + 1);
	if (tmp == NULL)
		return (NULL);
	if (n == 0)
		tmp[0] = '0';
	if (n < 0)
	{
		tmp[0] = '-';
		n *= -1;
		i++;
	}
	while (i-- > 0 && n > 0)
	{
		tmp[i] = n % 10 + '0';
		n /= 10;
	}
	return (tmp);
}
