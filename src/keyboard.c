#include "RTv1.h"


int		check_camera(const uint8_t *key, t_app *app)
{
	int a = 0;
	float angle;

	if (key[SDL_SCANCODE_Q])
	{
		app->camera.rotate_angle_y -= app->camera.rotate_speed * RAD;
		a = 1;
	}
	if (key[SDL_SCANCODE_E])
	{
		app->camera.rotate_angle_y += app->camera.rotate_speed * RAD;
		a = 1;
	}
	if (key[SDL_SCANCODE_A])
	{
		angle = app->camera.rotate_angle_y - 90 * RAD;
		app->camera.camera.x = app->camera.camera.x
				+ app->camera.camera_speed * sin(angle);
		app->camera.camera.z = app->camera.camera.z
							   + app->camera.camera_speed * cos(angle);
		a = 1;
	}
	if (key[SDL_SCANCODE_D])
	{
		angle = app->camera.rotate_angle_y + 90 * RAD;
		app->camera.camera.x = app->camera.camera.x
							   + app->camera.camera_speed * sin(angle);
		app->camera.camera.z = app->camera.camera.z
							   + app->camera.camera_speed * cos(angle);
		a = 1;
	}
	if (key[SDL_SCANCODE_UP])
	{
		app->camera.camera.y += 0.5f;
		a = 1;
	}
	if (key[SDL_SCANCODE_DOWN])
	{
		app->camera.camera.y -= 0.5f;
		a = 1;
	}
	if (key[SDL_SCANCODE_W])
	{
		app->camera.camera.x = app->camera.camera.x
							   + app->camera.camera_speed
							   * sin(app->camera.rotate_angle_y);
		app->camera.camera.z = app->camera.camera.z
							   + app->camera.camera_speed
							   * cos(app->camera.rotate_angle_y);

		a = 1;
	}
	if (key[SDL_SCANCODE_S])
	{
		angle = app->camera.rotate_angle_y + 180 * RAD;
		app->camera.camera.x = app->camera.camera.x
							   + app->camera.camera_speed * sin(angle);
		app->camera.camera.z = app->camera.camera.z
							   + app->camera.camera_speed * cos(angle);
		a = 1;
	}
	return (a);
}

int		check_lights(const uint8_t *key, t_app *app)
{
	int		a;
	float	angle;

	a = 0;
	if (key[SDL_SCANCODE_1] && app->scene.cur_light_control >= 1)
	{
		app->scene.cur_light_control--;
		a = 1;
	}
	if (key[SDL_SCANCODE_2])
	{
		if (app->scene.cur_light_control + 1 < AMOUNT_LIGHTS)
		{
			app->scene.cur_light_control++;
			a = 1;
		}
	}
	if (key[SDL_SCANCODE_KP_4])
	{
		angle = app->camera.rotate_angle_y - 90 * RAD;
		app->scene.lights[app->scene.cur_light_control].position.x =
				app->scene.lights[app->scene.cur_light_control].position.x
				+ app->scene.light_speed * sin(angle);
		app->scene.lights[app->scene.cur_light_control].position.z =
				app->scene.lights[app->scene.cur_light_control].position.z
				+ app->scene.light_speed * cos(angle);
//		app->scene.lights[app->scene.cur_light_control].position.x -= app->scene.light_speed;
		a = 1;
	}
	if (key[SDL_SCANCODE_KP_6])
	{
		angle = app->camera.rotate_angle_y + 90 * RAD;
		app->scene.lights[app->scene.cur_light_control].position.x =
				app->scene.lights[app->scene.cur_light_control].position.x
				+ app->scene.light_speed * sin(angle);
		app->scene.lights[app->scene.cur_light_control].position.z =
				app->scene.lights[app->scene.cur_light_control].position.z
				+ app->scene.light_speed * cos(angle);
		a = 1;
	}
	if (key[SDL_SCANCODE_KP_5])
	{
		angle = app->camera.rotate_angle_y + 180 * RAD;
		app->scene.lights[app->scene.cur_light_control].position.x =
				app->scene.lights[app->scene.cur_light_control].position.x
				+ app->scene.light_speed * sin(angle);
		app->scene.lights[app->scene.cur_light_control].position.z =
				app->scene.lights[app->scene.cur_light_control].position.z
				+ app->scene.light_speed * cos(angle);
		a = 1;
	}
	if (key[SDL_SCANCODE_KP_8])
	{
		app->scene.lights[app->scene.cur_light_control].position.x =
				app->scene.lights[app->scene.cur_light_control].position.x
				+ app->scene.light_speed * sin(app->camera.rotate_angle_y);
		app->scene.lights[app->scene.cur_light_control].position.z =
				app->scene.lights[app->scene.cur_light_control].position.z
				+ app->scene.light_speed * cos(app->camera.rotate_angle_y);
		a = 1;
	}
	if (key[SDL_SCANCODE_KP_9])
	{
		app->scene.lights[app->scene.cur_light_control].position.y += 2.1f;
		a = 1;
	}
	if (key[SDL_SCANCODE_KP_3])
	{
		app->scene.lights[app->scene.cur_light_control].position.y -= 2.1f;
		a = 1;
	}
	if (key[SDL_SCANCODE_KP_PLUS])
	{
		app->scene.lights[app->scene.cur_light_control].intensity += 0.1f;
		a = 1;
	}
	if (key[SDL_SCANCODE_KP_MINUS])
	{
		app->scene.lights[app->scene.cur_light_control].intensity -= 0.1f;
		a = 1;
	}
	return (a);
}
