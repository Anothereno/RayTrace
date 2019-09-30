/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strcmp.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hdwarven <hdwarven@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/11/19 18:47:39 by hdwarven          #+#    #+#             */
/*   Updated: 2019/09/03 10:27:10 by hdwarven         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

int		ft_strcmp(const char *st1, const char *st2)
{
	unsigned char *s1;
	unsigned char *s2;

	s1 = (unsigned char*)st1;
	s2 = (unsigned char*)st2;
	while (*s1 && *s2 && *s1 == *s2)
	{
		s1++;
		s2++;
	}
	if (!(*s1) && !(*s2))
		return (0);
	else if (!(*s1) && *s2)
		return (*s2 * -1);
	else if (!(*s2) && s1)
		return (*s1);
	else
		return (*s1 - *s2);
}
