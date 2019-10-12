#include "RTv1.h"

void	check_for_redraw(const uint8_t *key, t_app *app)
{
	if(key[SDL_SCANCODE_Q] || key[SDL_SCANCODE_E] || key[SDL_SCANCODE_A] ||
			key[SDL_SCANCODE_D] || key[SDL_SCANCODE_UP] || key[SDL_SCANCODE_DOWN] ||
			key[SDL_SCANCODE_W] || key[SDL_SCANCODE_S] || key[SDL_SCANCODE_1] ||
			key[SDL_SCANCODE_2] || key[SDL_SCANCODE_KP_4] || key[SDL_SCANCODE_KP_6] ||
			key[SDL_SCANCODE_KP_5] || key[SDL_SCANCODE_KP_8] || key[SDL_SCANCODE_KP_9] ||
			key[SDL_SCANCODE_KP_3] || key[SDL_SCANCODE_KP_1] || key[SDL_SCANCODE_KP_MINUS] ||
			key[SDL_SCANCODE_KP_PLUS])
		redraw(app);
}

void		move_camera(t_app *app, double angle)
{
	app->camera.camera.x = app->camera.camera.x
						   + app->camera.camera_speed * sin(angle);
	app->camera.camera.z = app->camera.camera.z
						   + app->camera.camera_speed * cos(angle);
}

void	check_camera(const uint8_t *key, t_app *app)
{
	if (key[SDL_SCANCODE_Q])
		app->camera.rotate_angle_y -= app->camera.rotate_speed * RAD;
	if (key[SDL_SCANCODE_E])
		app->camera.rotate_angle_y += app->camera.rotate_speed * RAD;
	if (key[SDL_SCANCODE_A])
		move_camera(app, app->camera.rotate_angle_y - 90 * RAD);
	if (key[SDL_SCANCODE_D])
		move_camera(app, app->camera.rotate_angle_y + 90 * RAD);
	if (key[SDL_SCANCODE_UP])
		app->camera.camera.y += 0.5f;
	if (key[SDL_SCANCODE_DOWN])
		app->camera.camera.y -= 0.5f;
	if (key[SDL_SCANCODE_W])
		move_camera(app, app->camera.rotate_angle_y);
	if (key[SDL_SCANCODE_S])
		move_camera(app, app->camera.rotate_angle_y + 180 * RAD);
}

void		move_light(t_app *app, double angle)
{
	app->scene.lights[app->scene.cur_light_control].position.x =
			app->scene.lights[app->scene.cur_light_control].position.x
			+ app->scene.light_speed * sin(angle);
	app->scene.lights[app->scene.cur_light_control].position.z =
			app->scene.lights[app->scene.cur_light_control].position.z
			+ app->scene.light_speed * cos(angle);
}

void		check_lights(const uint8_t *key, t_app *app)
{
	if (key[SDL_SCANCODE_1] && app->scene.cur_light_control >= 1)
		app->scene.cur_light_control--;
	if (key[SDL_SCANCODE_2] &&
			app->scene.cur_light_control + 1 < app->scene.lights_amount)
		app->scene.cur_light_control++;
	if (key[SDL_SCANCODE_KP_4])
		move_light(app, app->camera.rotate_angle_y - 90 * RAD);
	if (key[SDL_SCANCODE_KP_6])
		move_light(app, app->camera.rotate_angle_y + 90 * RAD);
	if (key[SDL_SCANCODE_KP_5])
		move_light(app, app->camera.rotate_angle_y + 180 * RAD);
	if (key[SDL_SCANCODE_KP_8])
		move_light(app, app->camera.rotate_angle_y);
	if (key[SDL_SCANCODE_KP_9])
		app->scene.lights[app->scene.cur_light_control].position.y += 2.1f;
	if (key[SDL_SCANCODE_KP_3])
		app->scene.lights[app->scene.cur_light_control].position.y -= 2.1f;
	if (key[SDL_SCANCODE_KP_PLUS])
		app->scene.lights[app->scene.cur_light_control].intensity += 0.1f;
	if (key[SDL_SCANCODE_KP_MINUS])
		app->scene.lights[app->scene.cur_light_control].intensity -= 0.1f;
}
