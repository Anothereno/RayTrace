/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cylinder.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hdwarven <hdwarven@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/10/13 17:38:34 by hdwarven          #+#    #+#             */
/*   Updated: 2019/10/13 19:37:39 by hdwarven         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "rtv.h"

t_cylinder	new_cylinder(t_app *app, t_vector center,
		double radius, t_vector rot)
{
	t_cylinder	res;

	res.center = center;
	res.radius = radius;
	res.color = color_randomize();
	res.specular = rand() % 1000;
	set_axis(&res.axis, rot);
	app->scene.cur_cylinder++;
	return (res);
}

double		intersect_ray_cylinder(t_vector camera,
		t_vector direct, t_cylinder cylinder)
{
	t_abc		abc;
	t_vector	oc;
	double		delta;

	oc = vector_sub(camera, cylinder.center);
	abc.a = vector_dot(direct, direct)
			- POWTWO(vector_dot(direct, cylinder.axis));
	abc.b = (vector_dot(direct, oc)
			- vector_dot(direct, cylinder.axis)
			* vector_dot(oc, cylinder.axis)) * 2;
	abc.c = vector_dot(oc, oc)
			- POWTWO(vector_dot(oc, cylinder.axis))
			- cylinder.radius * cylinder.radius;
	delta = abc.b * abc.b - 4 * (abc.a * abc.c);
	abc.b = -abc.b;
	abc.a = abc.a * 2;
	if (fabs(delta) < 0.001)
		return (set_intersect(INF, INF));
	else
		return (set_intersect(
				((abc.b) + sqrt(delta))
				/ abc.a, ((abc.b) - sqrt(delta)) / abc.a));
}

void		normal_cylinder(t_app *app, t_cylinder *cylinder, t_object *object)
{
	t_vector	obj_cam;
	double		temp;

	obj_cam = vector_sub(app->camera.position, cylinder->center);
	temp = vector_dot(app->camera.direct, cylinder->axis)
			* object->hit_point.distance
			+ vector_dot(obj_cam, cylinder->axis);
	object->normal = vector_sub(vector_sub(object->hit_point, cylinder->center),
								vector_mult_scal(cylinder->axis, temp));
	object->normal = normalize(object->normal);
}

t_object	find_intersected_cylinders(t_app *app,
		double length_min, t_object prev_object, t_camera *camera)
{
	int			i;
	t_object	object;
	double		distance;

	i = -1;
	object.flag = 0;
	object.distance = INF;
	while (++i < app->scene.cylinders_amount)
	{
		distance = intersect_ray_cylinder(camera->position,
				camera->direct, app->scene.cylinders[i]);
		if (between(length_min, INF, distance) && distance < object.distance)
		{
			object.distance = distance;
			object.center = app->scene.cylinders[i].center;
			object.hit_point = vector_add(camera->position,
					vector_mult_scal(camera->direct, object.distance));
			normal_cylinder(app, &app->scene.cylinders[i], &object);
			object.color = app->scene.cylinders[i].color;
			object.specular = app->scene.cylinders[i].specular;
			object.flag = 1;
		}
	}
	return (object.distance < prev_object.distance) ? object : prev_object;
}
