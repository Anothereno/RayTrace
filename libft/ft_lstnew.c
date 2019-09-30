/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstnew.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hdwarven <hdwarven@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/11/30 19:10:38 by hdwarven          #+#    #+#             */
/*   Updated: 2019/09/03 10:27:10 by hdwarven         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

t_list	*ft_lstnew(void const *content, size_t content_size)
{
	t_list *list;

	list = NULL;
	if ((list = (t_list*)malloc(sizeof(t_list))))
	{
		if (content != NULL)
		{
			if (!(list->content = (void*)malloc(content_size)))
			{
				free(list);
				return (list = NULL);
			}
			ft_memcpy(list->content, content, content_size);
			list->content_size = content_size;
		}
		else
		{
			list->content = (void*)0;
			list->content_size = 0;
		}
		list->next = NULL;
	}
	return (list);
}
