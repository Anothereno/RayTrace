/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   clear_split.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hdwarven <hdwarven@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/10/13 18:26:13 by hdwarven          #+#    #+#             */
/*   Updated: 2019/10/13 18:26:13 by hdwarven         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	clear_split(char **string)
{
	int i;

	i = 0;
	while (string[i] != 0)
	{
		free(string[i]);
		i++;
	}
	free(string);
}
