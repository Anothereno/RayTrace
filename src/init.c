#include "RTv1.h"

void	init_objects(t_scene *scene)
{
	scene->spheres = (t_sphere*)malloc(sizeof(t_sphere)
			* scene->spheres_amount);
	scene->cones = (t_cone*)malloc(sizeof(t_cone)
			* scene->cones_amount);
	scene->planes = (t_plane*)malloc(sizeof(t_plane)
			* scene->planes_amount);
	scene->cylinders = (t_cylinder*)malloc(sizeof(t_cylinder)
			* scene->cylinders_amount);
	scene->lights = (t_light*)malloc(sizeof(t_light)
			* scene->lights_amount);
}

void	init_app(t_app *app)
{

	app->sdl->width = SCREEN_WIDTH;
	app->sdl->height = SCREEN_HEIGHT;
	SDL_Error(SDL_Init(SDL_INIT_VIDEO));
	app->sdl->window = SDL_CreateWindow("RTv1", 500, 400,
			SCREEN_WIDTH, SCREEN_HEIGHT, 0);
	app->sdl->surface = SDL_GetWindowSurface(app->sdl->window);
	app->sdl->keys = SDL_GetKeyboardState(NULL);
	app->scene.cur_light_control = 0;
	app->camera.rotate_angle_y = 0;
	app->camera.camera_speed = 3.0f;
	app->camera.rotate_speed = 4.0f;
	app->scene.light_speed = 0.5f;

	app->scene.lights_amount = 0;
	app->scene.spheres_amount = 0;
	app->scene.cones_amount = 0;
	app->scene.cylinders_amount = 0;
	app->scene.planes_amount = 0;
	app->scene.cameras_amount = 0;
	app->scene.cur_light = 0;
	app->scene.cur_sphere = 0;
	app->scene.cur_cone = 0;
	app->scene.cur_cylinder = 0;
	app->scene.cur_plane = 0;
	app->scene.cur_camera = 0;
	srand(time(0));
}
