/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   color.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hdwarven <hdwarven@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/10/13 16:31:07 by hdwarven          #+#    #+#             */
/*   Updated: 2019/10/13 17:57:06 by hdwarven         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "rtv.h"

t_color	set_color(int red, int green, int blue)
{
	t_color color;

	color.red = clamp(0, 255, red);
	color.green = clamp(0, 255, green);
	color.blue = clamp(0, 255, blue);
	return (color);
}

void	sum_color(t_color *first, t_color *second)
{
	first->red += second->red;
	first->blue += second->blue;
	first->green += second->green;
	*first = set_color(first->red, first->green, first->blue);
}

t_color	to_hsv(int rand_num)
{
	t_color color;
	double	calc_color;

	calc_color = (1 - fabs(fmod(rand_num / 60.0, 2) - 1)) * 255;
	if (rand_num >= 0 && rand_num < 60)
		color = set_color(255, calc_color, 0);
	else if (rand_num >= 60 && rand_num < 120)
		color = set_color(calc_color, 255, 0);
	else if (rand_num >= 120 && rand_num < 180)
		color = set_color(0, 255, calc_color);
	else if (rand_num >= 180 && rand_num < 240)
		color = set_color(0, calc_color, 255);
	else if (rand_num >= 240 && rand_num < 300)
		color = set_color(calc_color, 0, 255);
	else
		color = set_color(255, 0, calc_color);
	return (color);
}

t_color	color_randomize(void)
{
	t_color color;

	color = to_hsv(rand() % 360);
	return (color);
}

t_color	pallete(t_color color, double num)
{
	t_color res;

	res.red = clamp(0, 255, color.red * num);
	res.blue = clamp(0, 255, color.blue * num);
	res.green = clamp(0, 255, color.green * num);
	return (res);
}
