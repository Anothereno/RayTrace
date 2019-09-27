#include "RTv1.h"


int		check_camera(const uint8_t *key, t_app *app)
{
	int a = 0;
	if (key[SDL_SCANCODE_A])
	{
		app->camera.camera.x -= 0.5f;
		a = 1;
	}
	if (key[SDL_SCANCODE_D])
	{
		app->camera.camera.x += 0.5f;
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
		app->camera.camera.z += 0.5f;
		a = 1;
	}
	if (key[SDL_SCANCODE_S])
	{
		app->camera.camera.z -= 0.5f;
		a = 1;
	}
	return (a);
}

int		check_lights(const uint8_t *key, t_app *app)
{
	int		a;

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
		app->scene.lights[app->scene.cur_light_control].direct.x -= 0.5f;
		a = 1;
	}
	if (key[SDL_SCANCODE_KP_6])
	{
		app->scene.lights[app->scene.cur_light_control].direct.x += 0.5f;
		a = 1;
	}
	if (key[SDL_SCANCODE_KP_2])
	{
		app->scene.lights[app->scene.cur_light_control].direct.z -= 0.5f;
		a = 1;
	}
	if (key[SDL_SCANCODE_KP_8])
	{
		app->scene.lights[app->scene.cur_light_control].direct.z += 0.5f;
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
