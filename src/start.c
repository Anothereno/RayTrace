#include "RTv1.h"

t_vector to_viewport(int x, int y)
{
	t_vector vector;

	double u_scale = SCREEN_WIDTH > SCREEN_HEIGHT ? (double)SCREEN_WIDTH / (double)SCREEN_HEIGHT : 1.0f;
	double v_scale = SCREEN_HEIGHT > SCREEN_WIDTH ? (double)SCREEN_HEIGHT / (double)SCREEN_WIDTH : 1.0f;

	vector.x = (double)x / (SCREEN_WIDTH - 1) - 0.5;
	vector.y = 0.5 - (double)y / (SCREEN_HEIGHT - 1);
	vector.x *= u_scale;
	vector.y *= v_scale;
	vector.z = 1.0;
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
				set_color(30 * i *2 + 50, 20 * i + 30, 20 * i + 120),700 + i * 30);
	i = -1;
	while (++i < scene->cylinders_amount)
	{
		t_vector rotate = set_vertex(0,45,45);
		scene->cylinders[i] = new_cylinder(set_vertex(i - 2, 0, i * 6),
										   i + 1, set_color(30 * i *2 + 50, 20 * i + 30, 20 * i + 120), 2.0 + i * 100, 200, rotate);
//		scene->cylinders[i].axis = set_vertex(0, -1, 0);
	}
	i = -1;
	while (++i < scene->cones_amount)
	{
		t_vector rotate = set_vertex(0,45,45);
		scene->cones[i] = new_cone(set_vertex(i - 2, (i * 2) - 1, i * 6),
											   i + 1, set_color(30 * i *2 + 50, 20 * i + 30, 20 * i + 120), 2.0 + i * 2, 200, rotate);
//		scene->cones[i].axis = set_vertex(0, -1, 0);
		scene->cones->angle = 20 * RAD;
	}
	i = -1;
	while (++i < scene->planes_amount)
		scene->planes[i] = new_plane(set_vertex(0, -3, 8),
				set_vertex(0, -1, 0), set_color(30, 40, 180), 700);
	scene->planes[0].normal = set_vertex(0, 0, 1);

}

void	prepare_light(t_scene *scene)
{
	int i;

	i = -1;
	while (++i < scene->lights_amount)
	{
		scene->lights[i] = new_light(set_vertex(0, 4, -3), 3.0, 'p');
	}
}

t_vector rotation_y(t_camera *camera, t_vector viewport)
{
	t_vector res;

	res.x = viewport.x * cos(camera->rotate_angle_y)  + viewport.z * sin(camera->rotate_angle_y);
	res.y = viewport.y;
	res.z = viewport.x * sin(camera->rotate_angle_y) * -1.0f + viewport.z * cos(camera->rotate_angle_y);
	//vec_normalize(res);
	return (res);
}

void	start_the_game(t_app *app)
{
	prepare_light(&app->scene);
	prepare_objects(&app->scene);
	app->camera.camera = set_vertex(0.0, 0.0, -10.50);
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
			app->camera.direct = vec_normalize(rotation_y(&app->camera, to_viewport(x, y)));
			color = raytrace(1, INF, app);
			set_pixel(app->sdl->surface, x, y, color);
		}
	}
	SDL_UpdateWindowSurface(app->sdl->window);
}
