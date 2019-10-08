/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fractol.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hdwarven <hdwarven@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/05/07 17:22:21 by hdwarven          #+#    #+#             */
/*   Updated: 2019/10/08 12:27:41 by ndremora         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "RTv1.h"

t_vector set_vertex(double x, double y, double z)
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


void	vector_sub3(t_vector *res,t_vector *first, t_vector *second)
{

	res->x = first->x - second->x;
	res->y = first->y - second->y;
	res->z = first->z - second->z;
}

t_vector	vector_div_scal(t_vector first, double num)
{
	t_vector res;

	res.x = first.x / num;
	res.y = first.y / num;
	res.z = first.z / num;
	return (res);
}

t_vector	vector_mult_scal(t_vector first, double num)
{
	t_vector res;

	res.x = first.x * num;
	res.y = first.y * num;
	res.z = first.z * num;
	return (res);
}

void	vector_mult_scal2(t_vector *res,t_vector *first, double num)
{
	res->x = first->x * num;
	res->y = first->y * num;
	res->z = first->z * num;
}

t_object_intersect set_intersect(int amount, double first, double second)
{
	t_object_intersect res;

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

double vector_dot(t_vector first, t_vector second)
{
	return (first.x * second.x + first.y * second.y + first.z * second.z);
}

double vector_dot2(t_vector *first, t_vector *second)
{
	return (first->x * second->x + first->y * second->y + first->z * second->z);
}

double	vector_length(t_vector vector)
{
	return (sqrt(vector_dot(vector, vector)));
}

double	vector_length2(t_vector *vector)
{
	return (sqrt(vector_dot2(vector, vector)));
}

t_vector			vector_dot_scalar(t_vector vector, double num)
{
	t_vector res;

	res.x = vector.x * num;
	res.y = vector.y * num;
	res.z = vector.z * num;
	return (res);
}

int 	between(double min, double max, double num)
{
	if (num >= min && num <= max)
		return (1);
	return (0);
}

double 	light_calculate(t_vector plane, t_vector normal, t_app *app, int specular)
{
	double		res;
	t_vector	L;
	t_vector	R;
	t_vector	V;
	t_object	object;
	double		max;
	int			i;
	double		dot;
	double		rot;

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
						(vector_length(normal) * vector_length2(&L));
			if(specular != -1)
			{
				vec_invert2(&V, &app->camera.direct);
				vector_mult_scal2(&R ,&normal, 2);
				vector_mult_scal2(&R ,&R, dot);
				vector_sub3(&R, &R, &L);
				rot = vector_dot2(&R, &V);
				if (rot > 0)
					res += app->scene.lights[i].intensity * pow(rot / (vector_length2(&R) * vector_length2(&V)), specular);
			}
		}
	}
	return (res);
}

t_color pallete(t_color color, double num)
{
	t_color res;

	res.red = clamp(0, 255, color.red * num);
	res.blue = clamp(0, 255, color.blue * num);
	res.green = clamp(0, 255, color.green * num);
	return (res);
}

t_color raytrace(t_vector camera, t_vector direct,
				 double length_min, double length_max, t_app *app)
{
	t_vector	plane;
	t_vector	normal;
	t_object	object;

	object = find_intersected_spheres(app, app->camera.camera, app->camera.direct, length_min, length_max);
	object = find_intersected_planes(app, app->camera.camera, app->camera.direct, length_min, length_max, object);
	object = find_intersected_cylinders(app, app->camera.camera, app->camera.direct, length_min, length_max, object);
	object = find_intersected_cones(app, app->camera.camera, app->camera.direct, length_min, length_max, object);
	if (!object.flag)
		return (set_color(0, 0, 0));
	plane = vector_add(camera, vector_dot_scalar(direct, object.distance));
	normal = vector_sub(plane, object.center);
	normal = vector_div_scal(normal, vector_length(normal));
	return pallete(object.color, light_calculate(plane, normal, app, object.specular));
}
