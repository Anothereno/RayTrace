/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strtrim.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hdwarven <hdwarven@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/11/29 12:22:16 by hdwarven          #+#    #+#             */
/*   Updated: 2019/09/03 10:27:10 by hdwarven         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static int	ft_check_begin(const char *s)
{
	int i;

	i = 0;
	while (ft_iswhitespaces(*s) && *s)
	{
		s++;
		i++;
	}
	if (*s)
		return (i);
	else
		return (i + 1);
}

static int	ft_check_end(const char *s)
{
	int i;

	i = ft_strlen(s) - 1;
	while (ft_iswhitespaces(s[i]) && s[i])
		i--;
	if (i >= 0 && !ft_iswhitespaces(s[i]))
		return (i);
	else
		return (ft_strlen(s));
}

char		*ft_strtrim(char const *s)
{
	int		begin;
	int		end;
	char	*tmp;
	char	*res;

	tmp = NULL;
	res = NULL;
	if (s)
	{
		begin = ft_check_begin(s);
		end = ft_check_end(s);
		tmp = ft_strnew(end - begin + 1);
		if (tmp == NULL)
			return (NULL);
		res = tmp;
		while (begin <= end)
		{
			*tmp = s[begin];
			tmp++;
			begin++;
		}
	}
	return (res);
}
