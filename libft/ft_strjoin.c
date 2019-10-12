/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strjoin.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hdwarven <hdwarven@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/11/28 21:21:28 by hdwarven          #+#    #+#             */
/*   Updated: 2019/10/12 18:19:57 by hdwarven         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strjoin(char const *s1, char const *s2)
{
	char	*res;
	char 	*tmp;
	int		size;

	res = NULL;
	if (s1 && s2)
	{
		size = ft_strlen(s1) + ft_strlen(s2) + 1;
		res = ft_strnew(size);
		if (res == NULL)
			return (NULL);
		res = ft_strcat(res, s1);
		res = ft_strcat(res, s2);
	}
	return (res);
}
