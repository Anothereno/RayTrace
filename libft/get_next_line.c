/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hdwarven <hdwarven@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/01/19 13:49:21 by hdwarven          #+#    #+#             */
/*   Updated: 2019/10/11 20:53:17 by hdwarven         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"

static int	returner(char **string, char **line)
{
	char	*delim;
	int		flag;
	char 	*tmp;

	flag = 0;
	delim = NULL;
	if (*string && (delim = ft_strchr(*string, '\n')) && ++flag)
	{
		*delim = '\0';
		delim++;
	}
	*line = *string;
	*string = ft_strdup("");
	if (delim && ft_strlen(delim))
	{
		free(*string);
		*string = ft_strdup(delim);
	}

	if ((*line && ft_strcmp(*line, "")) ||
		(*line && !ft_strcmp(*line, "") && flag))
		return (1);
	return (0);
}

static int	ft_solve(int fd, char **string, char **line)
{
	char	tmp[BUFF_SIZE + 1];
	int		i;
	char	*cur;

	while ((i = read(fd, tmp, BUFF_SIZE)))
	{
		tmp[i] = '\0';
		cur = *string;
		*string = ft_strjoin(*string, tmp);
		free(cur);
		if (ft_strchr(tmp, '\n'))
			break ;
	}
	if (returner(string, line))
		return (1);
	return (0);
}

int			get_next_line(const int fd, char **line)
{
	static char *str[65000];

	if (fd < 0 || line == NULL || (read(fd, NULL, 0) < 0) ||
		BUFF_SIZE <= 0)
		return (-1);
	if (!str[fd])
		str[fd] = ft_strdup("");
	if (ft_solve(fd, &str[fd], line))
	{
//		free(&str[fd]);
		return (1);
	}
	else
		return (0);
}
