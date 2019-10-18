/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   RTv.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hdwarven <hdwarven@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/10/13 18:00:41 by hdwarven          #+#    #+#             */
/*   Updated: 2019/10/17 17:59:41 by hdwarven         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "rtv.h"

double		set_intersect(double first, double second)
{
	double distance;

	if (first < 0)
		first = second;
	distance = MIN(first, second);
	return (distance);
}

int			between(double min, double max, double num)
{
	if (num >= min && num <= max)
		return (1);
	return (0);
}

t_vector	reflective(t_vector vector, t_vector normal)
{
	t_vector res;

	res = vector_sub(vector, vector_mult_scal(
			vector_mult_scal(normal, vector_dot(vector, normal)),
			2));
	return (res);
}

void		raytrace(t_app *app, int x, int y)
{
	t_color		pixel_color;
	t_color		temp_color;
	t_object	object;
	t_camera	camera;

	camera = app->camera;
	camera.direct = normalize(to_viewport(app, x, y));
	object = find_intersected_spheres(app, 1, &camera);
	if (app->scene.cylinders_amount != 0)
		object = find_intersected_cylinders(app, 1, object, &camera);
	if (app->scene.cones_amount != 0)
		object = find_intersected_cones(app, 1, object, &camera);
	if (app->scene.planes_amount != 0)
		object = find_intersected_planes(app, object, &camera);
	if (object.flag && object.distance < INF)
	{
		light_calculate(app, &object, &camera);
		pixel_color = pallete(object.color, object.diffuse);
		temp_color = pallete(app->white, object.specular);
		sum_color(&pixel_color, &temp_color);
		set_pixel(app->sdl->surface, x, y, &pixel_color);
		return ;
	}
	set_pixel(app->sdl->surface, x, y, &app->black);
}
