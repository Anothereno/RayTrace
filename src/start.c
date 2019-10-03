#include "RTv1.h"

t_vector to_viewport(int x, int y)
{
	t_vector vector;

	double u_scale = SCREEN_WIDTH > SCREEN_HEIGHT ? (double)SCREEN_WIDTH / (double)SCREEN_HEIGHT : 1.0f;
	double v_scale = SCREEN_HEIGHT > SCREEN_WIDTH ? (double)SCREEN_HEIGHT / (double)SCREEN_WIDTH : 1.0f;

	vector.x = (double)x / (SCREEN_WIDTH - 1) - 0.5;
	vector.y = 0.5f - (double)y / (SCREEN_HEIGHT - 1);
	vector.x *= u_scale;
	vector.y *= v_scale;
	vector.z = 1.0f;
	return (vector);
}

double	clamp(int min, int max, int num)
{
	if (num < min)
		return (min);
	else if (num > max)
		return (max);
	return (num);
}

void	prepare_objects(t_scene *scene)
{
	int i;

	i = -1;
	while (++i < scene->spheres_amount)
		scene->spheres[i] = new_sphere(set_vertex(i - 2, 0, i * 2),i + 2,
				set_color(30 * i *2 + 50, 20 * i + 30, 20 * i + 120),10 + i * 30);
	i = -1;
	while (++i < scene->cylinders_amount)
	{
		scene->cylinders[i] = new_cylinder(set_vertex(i - 2, 0, i * 6),
										   i + 1, set_color(30 * i *2 + 50, 20 * i + 30, 20 * i + 120), 2.0f + i * 100, 200);
	}
	i = -1;
	while (++i < scene->cones_amount)
	{
		scene->cones[i] = new_cone(set_vertex(i - 2, (i * 2) - 1, i * 6),
											   i + 1, set_color(30 * i *2 + 50, 20 * i + 30, 20 * i + 120), 2.0f + i * 2, 200);
	}
	i = -1;
	while (++i < scene->planes_amount)
		scene->planes[i] = new_plane(set_vertex(0, -3, 8),
				set_vertex(0, i + i * 90, 3), set_color(30, 40, 180), 140);
	i = -1;

}

void	prepare_light(t_scene *scene)
{
	int i;

	i = -1;
	while (++i < scene->lights_amount)
	{
		scene->lights[i] = new_light(set_vertex(-20 + i, 6 + i, -20 + i), 2.0f, 'p');
	}
	scene->lights[0].type = 'd';
	scene->lights[0].intensity = 0.9f;
	scene->lights[0].direct = set_vertex(-15, 40, -14);
	scene->lights[1].type = 'a';
	scene->lights[1].intensity = 0.4f;
//	app->scene.lights[2].type = 'd';
//	app->scene.lights[2].intensity = 0.9f;
//	app->scene.lights[2].direct = set_vertex(20, 40, -10);
}

t_vector rotation_y(t_camera *camera, t_vector viewport)
{
	t_vector res;

	res.x = viewport.x * cos(camera->rotate_angle_y)  + viewport.z * sin(camera->rotate_angle_y);
	res.y = viewport.y;
	res.z = viewport.x * sin(camera->rotate_angle_y) * -1.0f + viewport.z * cos(camera->rotate_angle_y);
	return (res);
}

void	start_the_game(t_app *app)
{
	prepare_light(&app->scene);
	prepare_objects(&app->scene);
	app->camera.camera = set_vertex(0.0, 0.0, -5.50);
	redraw(app);
	while (1)
	{
		if (!event_handling2(app))
			break;
	}
	SDL_Quit();
	SDL_DestroyWindow(app->sdl->window);
}

void	redraw(t_app *app)
{
	t_color		color;
	int			x;
	int 		y;

	y = -1;
	while (++y < SCREEN_HEIGHT)
	{
		x = -1;
		while (++x < SCREEN_WIDTH)
		{
			app->scene.cur_object = 0;
			app->camera.direct = rotation_y(&app->camera, to_viewport(x, y));
			color = raytrace(app->camera.camera, app->camera.direct, 1.0f, 999999.0f, app);
			set_pixel(app->sdl->surface, x, y, color);
		}
	}
	SDL_UpdateWindowSurface(app->sdl->window);
}
