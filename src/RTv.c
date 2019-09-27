/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fractol.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hdwarven <hdwarven@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/05/07 17:22:21 by hdwarven          #+#    #+#             */
/*   Updated: 2019/09/26 17:42:00 by hdwarven         ###   ########.fr       */
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

float vector_length(t_vector vector)
{
	return (sqrtf(vector_dot(vector, vector)));
}

t_sphere_intersect intersect_ray_sphere(t_vector camera, t_vector direct,
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

t_vector	vector_dot_scal(t_vector vector, float num)
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
				L = vector_sub(app->scene.lights[i].direct, plane);
			else
				L = app->scene.lights[i].direct;
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
					res += app->scene.lights[i].intensity * pow(rot / (vector_length(R) * vector_length(V)), specular);
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

t_color raytrace(t_vector camera, t_vector direct,
				 int length_min, int length_max, t_app *app)
{
	float				closest_intersect;
	t_sphere			closest_object;
	t_sphere_intersect	intersect;
	t_vector			plane;
	t_vector			normal;
	int					i;

	i = -1;
	closest_object.mode = 0;
	closest_intersect = 999999;

	while (++i < app->scene.objects_amount)
	{
		intersect = intersect_ray_sphere(camera, direct, app->scene.spheres[i]);

		if (between(length_min, length_max, intersect.first) &&
			intersect.first < closest_intersect)
		{
			closest_intersect = intersect.first;
			closest_object = app->scene.spheres[i];
			closest_object.mode = 1;
		}
		if (between(length_min, length_max, intersect.second) &&
			intersect.second < closest_intersect)
		{
			closest_intersect = intersect.second;
			closest_object = app->scene.spheres[i];
			closest_object.mode = 1;
		}
	}
	if (!closest_object.mode)
		return (set_color(0, 0, 0));
	plane = vector_add(camera, vector_dot_scal(direct, closest_intersect));
	normal = vector_sub(plane, closest_object.center);
	normal = vector_div_scal(normal, vector_length(normal));
	return pallete(closest_object.color, light_calculate(plane, normal, app, closest_object.specular));
}
