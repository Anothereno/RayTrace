/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memccpy.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hdwarven <hdwarven@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/11/26 13:14:08 by hdwarven          #+#    #+#             */
/*   Updated: 2019/09/03 10:27:10 by hdwarven         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	*ft_memccpy(void *dest, const void *src, int c, size_t n)
{
	void			*ch;

	ch = ft_memchr(src, c, n);
	if (ch == NULL)
	{
		ft_memcpy(dest, src, n);
		return (NULL);
	}
	else
	{
		n = ch - src + 1;
		ft_memcpy(dest, src, n);
		return (dest + n);
	}
}
