/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   camera.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hdwarven <hdwarven@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/10/13 17:58:52 by hdwarven          #+#    #+#             */
/*   Updated: 2019/10/13 19:20:10 by hdwarven         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "rtv.h"

void		set_camera(t_app *app, t_vector position, t_vector rotation)
{
	app->camera.position = position;
	app->camera.rotation = rotation;
	app->scene.cur_camera++;
}

void		set_axis(t_vector *axis, t_vector rot)
{
	t_vector	tmp_1;
	t_vector	tmp_2;

	rot.y *= M_PI / 180.0;
	rot.x *= M_PI / 180.0;
	rot.z *= M_PI / 180.0;
	tmp_1 = set_vector(0.0, -1.0, 0.0);
	tmp_2 = tmp_1;
	tmp_1.x = tmp_2.x * cos(rot.z) - tmp_2.y * sin(rot.z);
	tmp_1.y = tmp_2.x * sin(rot.z) + tmp_2.y * cos(rot.z);
	tmp_2 = tmp_1;
	tmp_1.x = tmp_2.x * cos(rot.y) + tmp_2.z * sin(rot.y);
	tmp_1.z = -tmp_2.x * sin(rot.y) + tmp_2.z * cos(rot.y);
	tmp_2 = tmp_1;
	tmp_1.y = tmp_2.y * cos(rot.x) - tmp_2.z * sin(rot.x);
	tmp_1.z = tmp_2.y * sin(rot.x) + tmp_2.z * cos(rot.x);
	*axis = normalize(tmp_1);
}

void		view_direction(t_vector *axis, t_vector rot)
{
	t_vector	tmp_1;
	t_vector	tmp_2;

	rot.y *= M_PI / 180.0;
	rot.x *= M_PI / 180.0;
	rot.z *= M_PI / 180.0;
	tmp_1 = *axis;
	tmp_2 = tmp_1;
	tmp_1.x = tmp_2.x * cos(rot.z) - tmp_2.y * sin(rot.z);
	tmp_1.y = tmp_2.x * sin(rot.z) + tmp_2.y * cos(rot.z);
	tmp_2 = tmp_1;
	tmp_1.x = tmp_2.x * cos(rot.y) + tmp_2.z * sin(rot.y);
	tmp_1.z = -tmp_2.x * sin(rot.y) + tmp_2.z * cos(rot.y);
	tmp_2 = tmp_1;
	tmp_1.y = tmp_2.y * cos(rot.x) - tmp_2.z * sin(rot.x);
	tmp_1.z = tmp_2.y * sin(rot.x) + tmp_2.z * cos(rot.x);
	*axis = normalize(tmp_1);
}

t_vector	to_viewport(t_app *app, int x, int y)
{
	t_vector	vector;
	double		u_scale;
	double		v_scale;

	u_scale = SCREEN_WIDTH > SCREEN_HEIGHT ?
			(double)SCREEN_WIDTH / (double)SCREEN_HEIGHT : 1.0f;
	v_scale = SCREEN_HEIGHT > SCREEN_WIDTH ?
			(double)SCREEN_HEIGHT / (double)SCREEN_WIDTH : 1.0f;
	vector.x = (double)x / (SCREEN_WIDTH - 1) - 0.5;
	vector.y = 0.5 - (double)y / (SCREEN_HEIGHT - 1);
	vector.x *= u_scale;
	vector.y *= v_scale;
	vector.z = 1.0;
	view_direction(&vector, app->camera.rotation);
	return (vector);
}
