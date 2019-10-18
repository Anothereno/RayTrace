/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   light.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hdwarven <hdwarven@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/10/13 17:49:25 by hdwarven          #+#    #+#             */
/*   Updated: 2019/10/18 15:39:16 by hdwarven         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "rtv.h"

void		light_calculate(t_app *app, t_object *object, t_camera *camera)
{
	double			light_intensity;
	t_object		hit;
	t_light_spot	spot;
	int				i;

	i = -1;
	object->diffuse = 0.1;
	object->specular = 0;
	while (++i < app->scene.lights_amount)
	{
		set_spot(&spot, object, i, app);
		hit = find_intersected_spheres(app, 0.001, &spot.shadow);
		hit = find_intersected_cones(app, 0.001, hit, &spot.shadow);
		hit = find_intersected_cylinders(app, 0.001, hit, &spot.shadow);
		if (hit.flag != 0 && hit.distance < spot.light_distance)
			continue;
		spot.dot = MAX(0, vector_dot(spot.light_direct, object->normal));
		light_intensity = app->scene.lights[i].intensity * 50;
		light_intensity /= M_PI * POWTWO(spot.light_distance);
		object->diffuse += light_intensity * spot.dot;
		object->specular += pow(MAX(0, vector_dot(
				vector_invert(reflective(vector_invert(spot.light_direct),
				object->normal)), camera->direct)), 30) * light_intensity;
	}
}

t_light		new_light(t_app *app, t_vector direct, double intensity)
{
	t_light res;

	res.intensity = intensity;
	res.position = direct;
	app->scene.cur_light++;
	return (res);
}

void		set_spot(t_light_spot *spot, t_object *object, int i, t_app *app)
{
	t_vector	sub;

	sub = vector_sub(app->scene.lights[i].position, object->hit_point);
	spot->light_direct = normalize(sub);
	spot->light_distance = vector_length(sub);
	spot->shadow.position = vector_add(object->hit_point,
		vector_mult_scal(object->normal, 0.1));
	spot->shadow.direct = spot->light_direct;
}
