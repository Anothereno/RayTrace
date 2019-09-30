/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strnstr.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hdwarven <hdwarven@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/11/22 19:20:36 by hdwarven          #+#    #+#             */
/*   Updated: 2019/09/03 10:27:10 by hdwarven         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strnstr(const char *haystack, const char *needle, size_t n)
{
	const char	*s1;
	const char	*s2;
	size_t		tmp;

	if ((!ft_strlen(haystack) && !ft_strlen(needle)) ||
		!ft_strcmp(needle, "") || !ft_strcmp(haystack, needle))
		return ((char *)(haystack));
	tmp = n;
	while (*haystack && (ft_strlen(haystack) >= ft_strlen(needle)) && n > 0)
	{
		s1 = haystack;
		s2 = needle;
		while (*s2 && *s1 == *s2 && n-- > 0)
		{
			s1++;
			s2++;
		}
		if (*s2 == '\0')
			return ((char *)(haystack));
		haystack++;
		n = --tmp;
	}
	return (NULL);
}
