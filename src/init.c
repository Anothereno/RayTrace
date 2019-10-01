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

    app->scene.spheres_amount = AMOUNT_SPHERES;
    app->scene.spheres = (t_sphere*)malloc(sizeof(t_sphere)
										   * app->scene.spheres_amount);
    app->scene.cones_amount = AMOUNT_CONES;
    app->scene.cones = (t_cone*)malloc(sizeof(t_cone)
										   * app->scene.cones_amount);
    app->scene.planes_amount = AMOUNT_PLANES;
    app->scene.planes = (t_plane*)malloc(sizeof(t_plane)
										   * app->scene.planes_amount);
    app->scene.cylinders_amount = AMOUNT_CYLINDERS;
    app->scene.cylinders = (t_cylinder*)malloc(sizeof(t_cylinder)
										   * app->scene.cylinders_amount);
    app->scene.lights_amount = AMOUNT_LIGHTS;
    app->scene.lights = (t_light*)malloc(sizeof(t_light)
										   * app->scene.lights_amount);
    app->scene.cur_light_control = 0;
    app->camera.rotate_angle_y = 0;
    app->camera.camera_speed = 1.0f;
    app->camera.rotate_speed = 4.0f;
    app->scene.light_speed = 3.0f;
}