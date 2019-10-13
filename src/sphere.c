/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sphere.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hdwarven <hdwarven@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/10/13 19:15:36 by hdwarven          #+#    #+#             */
/*   Updated: 2019/10/13 19:17:05 by hdwarven         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "RTv1.h"

t_sphere	new_sphere(t_app *app, t_vector center, double radius)
{
	t_sphere	res;

	res.center = center;
	res.radius = radius;
	res.color = color_randomize();
	res.specular = rand() % 1000;
	app->scene.cur_sphere++;
	return (res);
}

double		intersect_ray_sphere(t_vector camera, t_vector direct,
									t_sphere sphere)
{
	t_vector	oc;
	t_abc		abc;
	double		discr;

	oc = vector_sub(camera, sphere.center);
	abc.a = vector_dot(direct, direct);
	abc.b = 2.0f * vector_dot(direct, oc);
	abc.c = vector_dot(oc, oc) - sphere.radius * sphere.radius;
	discr = abc.b * abc.b - 4 * abc.a * abc.c;
	if (discr < 0)
		return (set_intersect(INF, INF));
	else
		return (set_intersect(
				((-abc.b) + sqrt(discr)) / (2 * abc.a),
				((-abc.b) - sqrt(discr)) / (2 * abc.a)));
}

t_object	find_intersected_spheres(t_app *app,
		double length_min, t_camera *camera)
{
	int			i;
	t_object	object;
	double		distance;

	i = -1;
	object.flag = 0;
	object.distance = INF;
	while (++i < app->scene.spheres_amount)
	{
		distance = intersect_ray_sphere(camera->position,
				camera->direct, app->scene.spheres[i]);
		if (between(length_min, INF, distance) && distance < object.distance)
		{
			object.distance = distance;
			object.hit_point = vector_add(camera->position,
				vector_mult_scal(camera->direct, object.distance));
			object.center = app->scene.spheres[i].center;
			object.normal = vector_sub(object.hit_point, object.center);
			object.normal = (normalize(object.normal));
			object.color = app->scene.spheres[i].color;
			object.specular = app->scene.spheres[i].specular;
			object.flag = 1;
		}
	}
	return (object);
}
