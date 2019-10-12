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

t_vector rotation_y(t_camera *camera, t_vector viewport)
{
	t_vector res;

	res.x = viewport.x * cos(camera->rotate_angle_y)  + viewport.z * sin(camera->rotate_angle_y);
	res.y = viewport.y;
	res.z = viewport.x * sin(camera->rotate_angle_y) * -1.0f + viewport.z * cos(camera->rotate_angle_y);
	return (res);
}

void	quit(t_app *app)
{
	SDL_FreeSurface(app->sdl->surface);
	SDL_DestroyWindow(app->sdl->window);
	SDL_Quit();
	free(app->sdl);
	free(app->scene.lights);
	free(app->scene.cylinders);
	free(app->scene.cones);
	free(app->scene.spheres);
	free(app->scene.planes);
	free(app);
}

void	start_the_game(t_app *app)
{
	redraw(app);
	while (1)
		if (!event_handling(app))
			break;
	quit(app);
}

void	*draw_thread(void *thread_info)
{
	int x;
	int y;
	t_thread thread;

	thread = *(t_thread*)thread_info;
	y = thread.y_start - 1;
	while (++y < thread.y_finish)
	{
		x = -1;
		while (++x < SCREEN_WIDTH)
			raytrace(thread.app, x, y);
	}
	return (NULL);
}

void	redraw(t_app *app)
{
	t_thread	threads_info[THREAD_AMOUNT];
	int			i;

	i = -1;
	while (++i < THREAD_AMOUNT)
	{
		threads_info[i].y_start = i * (SCREEN_HEIGHT / THREAD_AMOUNT);
		threads_info[i].y_finish = (i + 1) * (SCREEN_HEIGHT / THREAD_AMOUNT);
		threads_info[i].app = app;
		if (pthread_create(&threads_info[i].pthread, NULL, draw_thread, &threads_info[i]))
			ft_error("Threads was crashed");
	}
	i = -1;
	while (++i < THREAD_AMOUNT)
		pthread_join(threads_info[i].pthread, NULL);
	SDL_UpdateWindowSurface(app->sdl->window);
}
