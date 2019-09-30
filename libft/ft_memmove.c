/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memmove.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hdwarven <hdwarven@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/11/23 18:27:05 by hdwarven          #+#    #+#             */
/*   Updated: 2019/09/03 10:27:10 by hdwarven         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	*ft_memmove(void *dest, const void *src, size_t n)
{
	unsigned char	*begin;
	size_t			i;

	begin = (unsigned char*)src;
	if (dest == src)
		return (dest);
	if (dest < src)
		return (ft_memcpy(dest, src, n));
	i = dest - src + n - 1;
	while (n-- > 0)
	{
		begin[i] = begin[n];
		i--;
	}
	return (dest);
}
