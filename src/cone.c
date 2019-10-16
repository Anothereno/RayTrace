/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cone.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hdwarven <hdwarven@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/10/13 16:33:04 by hdwarven          #+#    #+#             */
/*   Updated: 2019/10/13 19:20:48 by hdwarven         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "rtv.h"

t_cone		new_cone(t_app *app, t_vector center, double angle, t_vector rot)
{
	t_cone	res;

	res.center = center;
	res.angle = angle * RAD;
	res.color = color_randomize();
	res.specular = rand() % 1000;
	set_axis(&res.axis, rot);
	app->scene.cur_cone++;
	return (res);
}

double		intersect_ray_cone(t_vector camera, t_vector direct, t_cone cone)
{
	t_vector	obj_cam;
	double		tan_angle;
	t_abc		abc;
	double		delta;

	obj_cam = vector_sub(camera, cone.center);
	tan_angle = tan(cone.angle);
	tan_angle = tan_angle * tan_angle + 1;
	abc.a = vector_dot(direct, direct) - tan_angle
			* pow(vector_dot(direct, cone.axis), 2);
	abc.b = (vector_dot(direct, obj_cam) - tan_angle
			* vector_dot(direct, cone.axis)
			* vector_dot(obj_cam, cone.axis)) * 2;
	abc.c = vector_dot(obj_cam, obj_cam) - tan_angle
			* pow(vector_dot(obj_cam, cone.axis), 2);
	delta = abc.b * abc.b - 4 * abc.a * abc.c;
	if (fabs(delta) < 0.001)
		return (set_intersect(INF, INF));
	else
		return (set_intersect(
				((-abc.b) + sqrt(delta)) / (2 * abc.a),
				((-abc.b) - sqrt(delta)) / (2 * abc.a)));
}

void		normal_cone(t_app *app, t_cone *cone, t_object *object)
{
	t_vector	obj_cam;
	double		tan_angle;
	double		temp;

	obj_cam = vector_sub(app->camera.position, cone->center);
	tan_angle = tan(cone->angle);
	tan_angle = tan_angle * tan_angle + 1;
	temp = vector_dot(app->camera.direct, cone->axis)
			* object->hit_point.distance
			+ vector_dot(obj_cam, cone->axis);
	object->normal = vector_sub(
			vector_sub(object->hit_point, cone->center),
			vector_mult_scal(
					vector_mult_scal(cone->axis, temp), tan_angle));
	object->normal = normalize(object->normal);
}

t_object	find_intersected_cones(t_app *app, double length_min,
		t_object prev_object, t_camera *camera)
{
	int			i;
	t_object	object;
	double		distance;

	i = -1;
	object.flag = 0;
	object.distance = INF;
	while (++i < app->scene.cones_amount)
	{
		distance = intersect_ray_cone(camera->position,
				camera->direct, app->scene.cones[i]);
		if (between(length_min, INF, distance)
			&& distance < object.distance)
		{
			object.distance = distance;
			object.hit_point = vector_add(camera->position,
				vector_mult_scal(camera->direct, object.distance));
			object.center = app->scene.cones[i].center;
			normal_cone(app, &app->scene.cones[i], &object);
			object.color = app->scene.cones[i].color;
			object.specular = app->scene.cones[i].specular;
			object.flag = 1;
		}
	}
	return (object.distance < prev_object.distance) ? object : prev_object;
}
