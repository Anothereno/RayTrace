#include "RTv1.h"

void	create_stuff(t_app *app)
{

}

void	init_sdl(t_sdl *sdl)
{

	//sdl->timer->delta_ticks = 0;
	//sdl->timer->delta = 0.0f;
}

void	init_app(t_app *app)
{

    app->sdl->width = SCREEN_WIDTH;
    app->sdl->half_width = (int)(app->sdl->width * 0.5);
    app->sdl->height = SCREEN_HEIGHT;
    app->sdl->half_height = (int)(app->sdl->height * 0.5);
    SDL_Error(SDL_Init(SDL_INIT_VIDEO));
    app->sdl->window = SDL_CreateWindow(
            "RTv1", 100, 400,
            SCREEN_WIDTH, SCREEN_HEIGHT,0);
    app->sdl->surface = SDL_GetWindowSurface(app->sdl->window);
    app->sdl->keys = SDL_GetKeyboardState(NULL);

    app->scene.amount = AMOUNT_OBJECTS;
    app->scene.spheres = (t_sphere*)malloc(sizeof(t_sphere)
										   * app->scene.amount);
    //bzero(app->sdl, sizeof(t_sdl));
	//init_sdl(app->sdl);
	//create_stuff(app);
	//app->inputs = (t_inputs *)malloc(sizeof(t_inputs));
}