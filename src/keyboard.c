/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   keyboard.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hdwarven <hdwarven@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/10/13 17:50:23 by hdwarven          #+#    #+#             */
/*   Updated: 2019/10/17 11:24:07 by hdwarven         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "rtv.h"

void	check_for_redraw(const uint8_t *key, t_app *app)
{
	if (key[SDL_SCANCODE_KP_4] || key[SDL_SCANCODE_KP_6]
			|| key[SDL_SCANCODE_KP_5] || key[SDL_SCANCODE_KP_8]
			|| key[SDL_SCANCODE_KP_9] || key[SDL_SCANCODE_KP_3]
			|| key[SDL_SCANCODE_KP_1] || key[SDL_SCANCODE_KP_MINUS]
			|| key[SDL_SCANCODE_KP_PLUS])
		redraw(app);
}

void	move_light(t_scene *scene, double angle)
{
	scene->lights[scene->cur_light_control].position.x =
			scene->lights[scene->cur_light_control].position.x
			+ scene->light_speed * sin(angle);
	scene->lights[scene->cur_light_control].position.z =
			scene->lights[scene->cur_light_control].position.z
			+ scene->light_speed * cos(angle);
}

void	check_lights(const uint8_t *key, t_app *app)
{
	if (key[SDL_SCANCODE_1] && app->scene.cur_light_control >= 1)
		app->scene.cur_light_control--;
	if (key[SDL_SCANCODE_2] &&
			app->scene.cur_light_control + 1 < app->scene.lights_amount)
		app->scene.cur_light_control++;
	if (key[SDL_SCANCODE_KP_4])
		move_light(&app->scene, (app->camera.rotation.y - 90) * RAD);
	if (key[SDL_SCANCODE_KP_6])
		move_light(&app->scene, (app->camera.rotation.y + 90) * RAD);
	if (key[SDL_SCANCODE_KP_5])
		move_light(&app->scene, (app->camera.rotation.y + 180) * RAD);
	if (key[SDL_SCANCODE_KP_8])
		move_light(&app->scene, app->camera.rotation.y * RAD);
	if (key[SDL_SCANCODE_KP_9])
		app->scene.lights[app->scene.cur_light_control].position.y += 0.5;
	if (key[SDL_SCANCODE_KP_3])
		app->scene.lights[app->scene.cur_light_control].position.y -= 0.5;
	if (key[SDL_SCANCODE_KP_PLUS])
		app->scene.lights[app->scene.cur_light_control].intensity += 0.1;
	if (key[SDL_SCANCODE_KP_MINUS])
		app->scene.lights[app->scene.cur_light_control].intensity -= 0.1;
}
