/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstmap.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hdwarven <hdwarven@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/12/01 19:45:04 by hdwarven          #+#    #+#             */
/*   Updated: 2019/09/03 10:27:10 by hdwarven         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

t_list	*ft_lstmap(t_list *lst, t_list *(*f)(t_list *elem))
{
	int		i;
	t_list	*begin;
	t_list	*head;

	begin = NULL;
	head = NULL;
	i = ft_size_of_lst(lst) + 1;
	if (lst && f)
	{
		if (!(begin = ft_lstnew(f(lst)->content, f(lst)->content_size)))
			return (ft_clear_list(begin));
		head = begin;
		lst = lst->next;
		while (i-- > 0)
		{
			if (!(head->next = ft_lstnew(f(lst)->content,
				f(lst)->content_size)))
				return (ft_clear_list(begin));
			if (!lst->next)
				break ;
			head = head->next;
			lst = lst->next;
		}
	}
	return (begin);
}
