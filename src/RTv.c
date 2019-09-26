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

//int		main(int argc, char **argv)
//{
//	t_app		my_app;
//	t_map		map;
//	t_map		objects;
//	t_player	player;
//
//	my_app.start_tick = 0;
//	if (argc == 2)
//	{
//		if (!val_set(argv[1], &map, &objects, &player))
//			exit(0);
//		init(&my_app, &map, &player, &objects);
//		my_app.key_menu = SDL_GetKeyboardState(NULL);
//		if (my_app.fullscreen_mode)
//			SDL_SetWindowFullscreen(my_app.win, -1);
//		main_loop(my_app, map, objects, player);
//	}
//	else
//		usage();
//	return (0);
//}

t_vector field_to_view(int x, int y)
{
	float v_h, v_w, d;
	t_vector res;
	float u_scale, v_scale;

	v_h = 1;
	v_w = 1;
	d = 1;
//	res.x = x * (1.0f / SCREEN_WIDTH);
//	res.y = y * (1.0f / SCREEN_HEIGHT);
	u_scale = SCREEN_WIDTH > SCREEN_HEIGHT ? (float)SCREEN_WIDTH / (float)SCREEN_HEIGHT : 1.0f;
	v_scale = SCREEN_HEIGHT > SCREEN_WIDTH ? (float)SCREEN_HEIGHT / (float)SCREEN_WIDTH : 1.0f;

	res.x = ((float)x / (SCREEN_WIDTH - 1)) - 0.5f;
	res.y = 0.5f - ((float)y / (SCREEN_HEIGHT - 1));
	res.x *= u_scale;
	res.y *= v_scale;
	res.z = d;

	return res;
}

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
	res.y = first.y - num;
	res.z = first.z - num;
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
//    t_vector    oc;
//    float	a;
//    float	b;
//    float	c;
//    float	discriminant;
//
//    oc = vector_sub(camera, spheres.center);
//    a = vector_dot(direct, direct);
//    b = 2.0f * vector_dot(oc, direct);
//    c = vector_dot(oc, oc) - spheres.radius * spheres.radius;
//
//    discriminant = b * b - 4 * a * c;
//    float t1 = (-b + sqrtf(discriminant)) / (2.0f * a);
//    float t2 = (-b - sqrtf(discriminant)) / (2.0f * a);
//    return (t1 > -1.0f);

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

float 	light_calculate(t_vector plane, t_vector normal, t_app *app)
{
	float res;
	t_vector temp;
	int i;
	float dot;

	i = -1;
	res = 0.0f;
	while (++i < app->scene.lights_amount)
	{
		if (app->scene.lights[i].type == 'a')
			res += app->scene.lights[i].intensity;
		else
		{
			if (app->scene.lights[i].type == 'p')
				temp = vector_sub(app->scene.lights[i].direct, plane);
			else
				temp = app->scene.lights[i].direct;
			dot = vector_dot(normal, temp);
			if (dot > 0)
				res += app->scene.lights[i].intensity * dot /
						(vector_length(normal) * vector_length(temp));
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
	float closest_intersect;
	t_sphere closest_object;
	t_sphere_intersect   intersect;
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
//	return (closest_object.color);
	plane = vector_add(camera, vector_dot_scal(direct, closest_intersect));
	normal = vector_sub(plane, closest_object.center);
	normal = vector_div_scal(normal, vector_length(normal));
	return pallete(closest_object.color,
			light_calculate(plane, normal, app));
}
