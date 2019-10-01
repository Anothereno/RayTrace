/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fractol.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hdwarven <hdwarven@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/05/07 17:22:21 by hdwarven          #+#    #+#             */
/*   Updated: 2019/10/01 17:57:59 by hdwarven         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "RTv1.h"

t_vector set_vertex(float x, float y, float z)
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

t_vector	vector_div_scal(t_vector first, float num)
{
	t_vector res;

	res.x = first.x / num;
	res.y = first.y / num;
	res.z = first.z / num;
	return (res);
}

t_vector	vector_mult_scal(t_vector first, float num)
{
	t_vector res;

	res.x = first.x * num;
	res.y = first.y * num;
	res.z = first.z * num;
	return (res);
}

t_sphere_intersect set_intersect(int amount, float first, float second)
{
	t_sphere_intersect res;

	res.intersect_amount = amount;
	res.first = first;
	res.second = second;
	return (res);
}

t_color set_color(int red, int green, int blue)
{
	t_color color;

	color.red = clamp(0, 255, red);
	color.green = clamp(0, 255, green);
	color.blue = clamp(0, 255, blue);
	return (color);
}

float vector_dot(t_vector first, t_vector second)
{
	float res;

	res = first.x * second.x + first.y * second.y + first.z * second.z;
	return (res);
}

float				vector_length(t_vector vector)
{
	return (sqrtf(vector_dot(vector, vector)));
}



t_sphere_intersect	intersect_ray_sphere(t_vector camera, t_vector direct,
										t_sphere sphere)
{
	t_vector oc;
	float a;
	float b;
	float c;
	float discr;

	oc = vector_sub(camera, sphere.center);
	a = vector_dot(direct, direct);
	b = 2.0f * vector_dot(oc, direct);
	c = vector_dot(oc, oc) - sphere.radius * sphere.radius;
	discr = b * b - 4 * a * c;
	if (discr < 0)
		return (set_intersect(0, 999999, 999999));
	else if (discr == 0)
		return (set_intersect(1,
							  ((-b) + sqrtf(discr)) / (2 * a),
							  ((-b) - sqrtf(discr)) / (2 * a)));
	else
		return (set_intersect(2,
							  ((-b) + sqrtf(discr)) / (2 * a),
							  ((-b) - sqrtf(discr)) / (2 * a)));
}

t_vector			vector_dot_scalar(t_vector vector, float num)
{
	t_vector res;

	res.x = vector.x * num;
	res.y = vector.y * num;
	res.z = vector.z * num;
	return (res);
}

int 	between(float min, float max, float num)
{
	if (num >= min && num <= max)
		return (1);
	return (0);
}

float 	light_calculate(t_vector plane, t_vector normal, t_app *app, int specular)
{
	float res;
	t_vector L;
	t_vector R;
	t_vector V;
	t_object object;
	float 				max;
	int i;
	float dot;
	float rot;

	i = -1;
	res = 0.0f;
	while (++i < app->scene.lights_amount)
	{
		if (app->scene.lights[i].type == 'a')
			res += app->scene.lights[i].intensity;
		else
		{
			if (app->scene.lights[i].type == 'p')
			{
				L = vector_sub(app->scene.lights[i].direct, plane);
				max = 1;
			}
			else
			{
				L = app->scene.lights[i].direct;
				max = 999999;
			}
			object = find_intersected_spheres(app, plane, L, 0.001f, max);
			if (object.flag != 0)
				continue;
			dot = vector_dot(normal, L);
			if (dot > 0)
				res += app->scene.lights[i].intensity * dot /
						(vector_length(normal) * vector_length(L));
			if(specular != -1)
			{
				V = vec_invert(app->camera.direct);
				R = vector_mult_scal(normal, 2);
				R = vector_mult_scal(R, dot);
				R = vector_sub(R, L);
				rot = vector_dot(R, V);
				if (rot > 0)
					res += app->scene.lights[i].intensity * powf(rot / (vector_length(R) * vector_length(V)), specular);
			}
		}
	}
	return (res);
}

t_color pallete(t_color color, float num)
{
	t_color res;

	res.red = clamp(0, 255, color.red * num);
	res.blue = clamp(0, 255, color.blue * num);
	res.green = clamp(0, 255, color.green * num);
	return (res);
}

t_object	find_intersected_spheres(t_app *app,
									 t_vector camera, t_vector direct,
									 float length_min, float length_max)
{
	int		i;
	t_object object;
	t_sphere_intersect intersect_sphere;

	i = -1;
	object.flag = 0;
	object.distance = 999999;
	while (++i < app->scene.spheres_amount)
	{
		intersect_sphere = intersect_ray_sphere(camera,
				direct, app->scene.spheres[i]);
		if (between(length_min, length_max, intersect_sphere.first) &&
			intersect_sphere.first < object.distance)
		{
			object.distance = intersect_sphere.first;
			object.center = app->scene.spheres[i].center;
			object.color = app->scene.spheres[i].color;
			object.specular = app->scene.spheres[i].specular;
			object.flag = 1;
		}
		if (between(length_min, length_max, intersect_sphere.second) &&
			intersect_sphere.second < object.distance)
		{
			object.distance = intersect_sphere.second;
			object.center = app->scene.spheres[i].center;
			object.color = app->scene.spheres[i].color;
			object.specular = app->scene.spheres[i].specular;
			object.flag = 1;
		}
	}
	return (object);
}


float	intersect_ray_plane(t_vector camera, t_vector direct,
										   t_plane plane)
{
	float		distance;
	float		plane_dot_ray;
	t_vector	plane_sub_ray;
	float		plane_dot_psr;

	plane_dot_ray = vector_dot(plane.normal, direct);
	plane_sub_ray = vector_sub(plane.center, camera);
	plane_dot_psr = vector_dot(plane.normal, plane_sub_ray);
	distance = plane_dot_psr / plane_dot_ray;
	return (distance);
}


t_object	find_intersected_planes(t_app *app,
									 t_vector camera, t_vector direct,
									 float length_min, float length_max,
									 t_object prev_object)
{
	int					i;
	t_object			object;
	float 				distance;

	i = -1;
	object.flag = 0;
	object.distance = 999999;
	while (++i < app->scene.planes_amount)
	{
		distance = intersect_ray_plane(camera,
				direct, app->scene.planes[i]);
		if (between(length_min, length_max, distance) &&
			distance < object.distance)
		{
			object.distance = distance;
			object.center = app->scene.planes[i].center;
			object.color = app->scene.planes[i].color;
			object.specular = app->scene.planes[i].specular;
			object.flag = 1;
		}
	}
	if (object.distance < prev_object.distance)
		return (object);
	return (prev_object);
}

t_color raytrace(t_vector camera, t_vector direct,
				 float length_min, float length_max, t_app *app)
{
	t_vector	plane;
	t_vector	normal;
	t_object	object;

	object = find_intersected_spheres(app, app->camera.camera,
			app->camera.direct, length_min, length_max);
	object = find_intersected_planes(app, app->camera.camera,
			app->camera.direct, length_min, length_max, object);
	if (!object.flag)
		return (set_color(0, 0, 0));
	plane = vector_add(camera, vector_dot_scalar(direct, object.distance));
	normal = vector_sub(plane, object.center);
	normal = vector_div_scal(normal, vector_length(normal));
	return pallete(object.color,
			light_calculate(plane, normal, app,
			object.specular));
}
