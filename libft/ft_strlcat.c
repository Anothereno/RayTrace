/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strlcat.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hdwarven <hdwarven@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/11/27 12:07:13 by hdwarven          #+#    #+#             */
/*   Updated: 2019/09/03 10:27:10 by hdwarven         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

size_t	ft_strlcat(char *dest, const char *src, size_t size)
{
	size_t	len;
	size_t	srclen;
	size_t	res;
	char	*dst;

	dst = dest;
	srclen = ft_strlen(src);
	res = size;
	len = 0;
	while (size > 0 && *dst != '\0')
	{
		dst++;
		size--;
		len++;
	}
	while (size-- > 1 && *src)
	{
		*dst = *src;
		dst++;
		src++;
	}
	if (size == 1 || *src == 0 || size == 0)
		*dst = '\0';
	return (srclen + len);
}
