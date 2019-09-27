#include "RTv1.h"

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

    app->scene.objects_amount = AMOUNT_OBJECTS;
    app->scene.spheres = (t_sphere*)malloc(sizeof(t_sphere)
										   * app->scene.objects_amount);
    app->scene.lights_amount = AMOUNT_LIGHTS;
    app->scene.lights = (t_light*)malloc(sizeof(t_light)
										   * app->scene.lights_amount);
    app->scene.cur_light_control = 0;
}