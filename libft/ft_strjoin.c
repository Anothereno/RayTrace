/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strjoin.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hdwarven <hdwarven@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/11/28 21:21:28 by hdwarven          #+#    #+#             */
/*   Updated: 2019/09/03 10:27:10 by hdwarven         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strjoin(char const *s1, char const *s2)
{
	char	*res;
	int		i;

	i = 0;
	res = NULL;
	if (s1 && s2)
	{
		i = ft_strlen(s1) + ft_strlen(s2);
		res = ft_strnew(sizeof(char) * ft_strlen(s1) +
			sizeof(char) * ft_strlen(s2) + 1);
		if (res == NULL)
			return (NULL);
		res = ft_strcat(res, s1);
		res = ft_strcat(res, s2);
	}
	return (res);
}
