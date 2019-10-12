/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ndremora <ndremora@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/01/06 13:25:46 by ndremora          #+#    #+#             */
/*   Updated: 2019/10/12 18:33:55 by hdwarven         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"

static	int	ft_find_next_line(char **str, char **line)
{
	char	*cur;
	if (*str && (cur = ft_strchr(*str, '\n')))
	{
		*cur = '\0';
		*line = ft_strdup(*str);
		*str = ft_strcpy(*str, cur + 1);
		return (1);
	}
	else
	{
		if (*str)
		{
			*line = ft_strdup(*str);
			ft_strdel(str);
			if (*line && ft_strcmp(*line, ""))
				return (1);
			return (0);
		}
		return (0);
	}
}

static	int	ft_read(int fd, char **str, char **line)
{
	char	newstr[BUFF_SIZE + 1];
	char	*tmp;
	int		ret;
	char	*tmp2;

	while ((ret = read(fd, newstr, BUFF_SIZE)) > 0)
	{
		newstr[ret] = '\0';
		if (!*str)
			*str = ft_strdup(newstr);
		else
		{
			tmp = *str;
			*str = ft_strjoin(*str, newstr);
			ft_strdel(&tmp);
		}
		if ((tmp2 = ft_strchr(*str, '\n')))
			if (ft_find_next_line(str, line) == 1)
				return (1);
	}
	if (ft_find_next_line(str, line) == 1)
		return (1);
	return (ret);
}

int			get_next_line(const int fd, char **line)
{
	static	char	*str[65000];
	int				a;

	if (!line || fd < 0 || BUFF_SIZE < 1 || (read(fd, NULL, 0) < 0))
		return (-1);
	a = ft_read(fd, &str[fd], line);
	if (a < 0)
		return (-1);
	if (a)
		return (1);
	else
		return (0);
}
