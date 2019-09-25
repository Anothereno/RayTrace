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

	return (1);
}