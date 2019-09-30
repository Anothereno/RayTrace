#include "RTv1.h"

int		event_handling(t_app *app)
{
	const uint8_t *key;
	key = app->sdl->keys;

	SDL_PollEvent(&app->sdl->event);
	if (app->sdl->event.type == SDL_QUIT)
		return(0);
	if (key[SDL_SCANCODE_ESCAPE])
		return(0);
	if (key[SDL_SCANCODE_Q])
		app->camera.rotate_angle_y -= 0.5f;
	if (key[SDL_SCANCODE_E])
		app->camera.rotate_angle_y += 0.5f;
	if (key[SDL_SCANCODE_A])
		app->camera.camera.x -= 0.5f;
	if (key[SDL_SCANCODE_D])
		app->camera.camera.x += 0.5f;
	if (key[SDL_SCANCODE_UP])
		app->camera.camera.y += 0.5f;
	if (key[SDL_SCANCODE_DOWN])
		app->camera.camera.y -= 0.5f;
	if (key[SDL_SCANCODE_W])
		app->camera.camera.z += 0.5f;
	if (key[SDL_SCANCODE_S])
		app->camera.camera.z -= 0.5f;
	if (key[SDL_SCANCODE_1])
		app->scene.cur_light_control = 0;
	if (key[SDL_SCANCODE_2])
		app->scene.cur_light_control = 1;
	if (key[SDL_SCANCODE_KP_4])
		app->scene.lights[app->scene.cur_light_control].direct.x -= 0.5f;
	if (key[SDL_SCANCODE_KP_6])
		app->scene.lights[app->scene.cur_light_control].direct.x += 0.5f;
	if (key[SDL_SCANCODE_KP_2])
		app->scene.lights[app->scene.cur_light_control].direct.z -= 0.5f;
	if (key[SDL_SCANCODE_KP_8])
		app->scene.lights[app->scene.cur_light_control].direct.z += 0.5f;
	if (key[SDL_SCANCODE_KP_PLUS])
		app->scene.lights[app->scene.cur_light_control].intensity += 0.1f;
	if (key[SDL_SCANCODE_KP_MINUS])
		app->scene.lights[app->scene.cur_light_control].intensity -= 0.1f;
	return (1);
}

int		event_handling2(t_app *app)
{
	const uint8_t *key;
	key = app->sdl->keys;
	int a = 0;
	SDL_WaitEvent(&app->sdl->event);
	if (app->sdl->event.type == SDL_QUIT)
		return(0);
	if (key[SDL_SCANCODE_ESCAPE])
		return(0);
	a = check_camera(key, app);
	a += check_lights(key, app);
	if (a)
		redraw(app);
//	SDL_WaitEvent(&app->sdl->event);
	return (1);
}