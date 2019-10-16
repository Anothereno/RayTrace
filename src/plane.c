/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   plane.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hdwarven <hdwarven@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/10/13 17:54:53 by hdwarven          #+#    #+#             */
/*   Updated: 2019/10/13 19:21:37 by hdwarven         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "rtv.h"

t_plane		new_plane(t_app *app, t_vector center, t_vector normal)
{
	t_plane	res;

	res.center = center;
	res.normal = normal;
	res.color = color_randomize();
	res.specular = rand() % 1000;
	app->scene.cur_plane++;
	return (res);
}

double		intersect_ray_plane(t_vector camera, t_vector direct, t_plane plane)
{
	double		distance;
	double		plane_dot_ray;
	double		plane_dot_psr;

	plane_dot_ray = vector_dot(direct, plane.normal);
	if (plane_dot_ray == 0)
		return (INF);
	plane_dot_psr = vector_dot(plane.normal, vector_sub(plane.center, camera));
	distance = plane_dot_psr / plane_dot_ray;
	return (distance);
}

t_object	find_intersected_planes(t_app *app,
		t_object prev_object, t_camera *camera)
{
	int			i;
	t_object	object;
	double		distance;

	i = -1;
	object.flag = 0;
	object.distance = INF;
	while (++i < app->scene.planes_amount)
	{
		distance = intersect_ray_plane(camera->position,
				camera->direct, app->scene.planes[i]);
		if (between(1, INF, distance) && distance < object.distance)
		{
			object.distance = distance;
			object.center = app->scene.planes[i].center;
			object.color = app->scene.planes[i].color;
			object.specular = app->scene.planes[i].specular;
			object.hit_point = vector_add(camera->position,
					vector_mult_scal(camera->direct, object.distance));
			object.normal = vector_invert(app->scene.planes[i].normal);
			object.flag = 1;
		}
	}
	return (object.distance < prev_object.distance) ? object : prev_object;
}
