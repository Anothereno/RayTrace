/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_atoi.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hdwarven <hdwarven@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/11/22 13:15:08 by hdwarven          #+#    #+#             */
/*   Updated: 2019/09/03 10:27:10 by hdwarven         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static int	check_max_min(unsigned long long num, int sign)
{
	unsigned long long max;

	max = 9223372036854775807;
	if (num > max && sign == 1)
		return (-1);
	if (num > max && sign == -1)
		return (0);
	return (1);
}

int			ft_atoi(const char *nptr)
{
	int					sign;
	unsigned long long	num;

	num = 0;
	sign = 1;
	while (ft_iswhitespaces(*nptr) && *nptr != '+' && *nptr != '-')
		nptr++;
	if (*nptr == '-')
		sign = -1;
	if (*nptr == '-' || *nptr == '+')
		nptr++;
	if (!ft_isdigit(*nptr))
		return (0);
	while (ft_isdigit(*nptr))
	{
		num = num * 10 + *nptr - '0';
		nptr++;
	}
	if (check_max_min(num, sign) == 0 || check_max_min(num, sign) == -1)
		return (check_max_min(num, sign));
	return (num * sign);
}
