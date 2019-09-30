/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strstr.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hdwarven <hdwarven@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/11/22 19:20:36 by hdwarven          #+#    #+#             */
/*   Updated: 2019/09/03 10:27:10 by hdwarven         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strstr(const char *haystack, const char *needle)
{
	const char *s1;
	const char *s2;

	if (!ft_strlen(haystack) && !ft_strlen(needle))
		return ((char *)(haystack));
	while (*haystack && (ft_strlen(haystack) >= ft_strlen(needle)))
	{
		s1 = haystack;
		s2 = needle;
		while (*s2 && *s1 == *s2)
		{
			s1++;
			s2++;
		}
		if (*s2 == '\0')
			return ((char *)(haystack));
		haystack++;
	}
	return (NULL);
}
