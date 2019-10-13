/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   vector1.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hdwarven <hdwarven@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/10/13 19:31:51 by hdwarven          #+#    #+#             */
/*   Updated: 2019/10/13 19:32:07 by hdwarven         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "RTv1.h"

t_vector	set_vector(double x, double y, double z)
{
	t_vector res;

	res.x = x;
	res.y = y;
	res.z = z;
	return (res);
}

t_vector	vector_add(t_vector first, t_vector second)
{
	t_vector res;

	res.x = first.x + second.x;
	res.y = first.y + second.y;
	res.z = first.z + second.z;
	return (res);
}

t_vector	vector_sub(t_vector first, t_vector second)
{
	t_vector res;

	res.x = first.x - second.x;
	res.y = first.y - second.y;
	res.z = first.z - second.z;
	return (res);
}

t_vector	normalize(t_vector v)
{
	t_vector	new_v;
	double		length;

	length = vector_length(v);
	new_v.x = v.x / length;
	new_v.y = v.y / length;
	new_v.z = v.z / length;
	return (new_v);
}

t_vector	vector_invert(t_vector v)
{
	t_vector	new_v;

	new_v.x = -v.x;
	new_v.y = -v.y;
	new_v.z = -v.z;
	return (new_v);
}
