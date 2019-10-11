/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strsplit.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hdwarven <hdwarven@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/11/29 12:51:37 by hdwarven          #+#    #+#             */
/*   Updated: 2019/09/03 10:27:10 by hdwarven         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

unsigned long	ft_count_word(char const *s, char c)
{
	unsigned long	count;

	count = 0;
	while (*s)
	{
		if (*s != c)
		{
			count++;
			while (*s != c && *s)
				s++;
		}
		else
			s++;
	}
	return (count);
}

static size_t			ft_length(const char *s, char c)
{
	size_t count;

	count = 0;
	while (*s == c)
		s++;
	while (*s != c && *s)
	{
		count++;
		s++;
	}
	return (count);
}

static size_t			ft_skip(const char *s, char c)
{
	size_t count;

	count = 0;
	while (*s == c && *s)
	{
		s++;
		count++;
	}
	return (count);
}

static int				ft_check_del(char const *s, char c, char **arr_z)
{
	*arr_z = ft_strnew(ft_length(s, c));
	if (!(*arr_z))
		return (0);
	*arr_z = ft_strncpy(*arr_z, s, ft_length(s, c));
	return (1);
}

char					**ft_strsplit(char const *s, char c)
{
	unsigned long	i;
	unsigned long	z;
	char			**arr;

	z = -1;
	arr = NULL;
	if (!s)
		return (NULL);
	i = ft_count_word(s, c);
	if (!(arr = (char**)malloc(sizeof(char*) * i + 1)))
		return (NULL);
	while (++z < i && *s)
	{
		s += ft_skip(s, c);
		if (*s)
			if (!ft_check_del(s, c, &arr[z]))
				return (ft_free_arr((void***)&arr, z));
		s += ft_length(s, c) + 1;
	}
	arr[z] = 0;
	return (arr);
}
