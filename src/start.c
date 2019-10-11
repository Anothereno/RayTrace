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

void	start_the_game(t_app *app)
{
	redraw(app);
	while (1)
		if (!event_handling2(app))
			break;
	SDL_Quit();
	SDL_DestroyWindow(app->sdl->window);
}

void	*draw_thread(void *thread_info)
{
	int x;
	int y;
	t_thread thread;
	t_app	*app;
	t_color color;

	thread = *(t_thread*)thread_info;
//	pthread_mutex_lock(&thread.app->locker);
	app = thread.app;
	y = thread.y_start - 1;
	while (++y < thread.y_finish)
	{
		x = -1;
		while (++x < SCREEN_WIDTH)
		{
			app->scene.cur_object = 0;
			app->camera.direct =
					vec_normalize(rotation_y(&app->camera,
							to_viewport(x, y)));
			color = raytrace(1, INF, app);

			set_pixel(app->sdl->surface, x, y, color);
		}
	}
//	pthread_mutex_unlock(&thread.app->locker);
	return (NULL);
}

void	redraw(t_app *app)
{
	t_thread	*threads_info;
	pthread_t	*threads_array;
	int			i;
	int x;
	int y;
	t_color color;

	threads_info = (t_thread*)malloc(sizeof(t_thread) * THREAD_AMOUNT);
//	threads_array = (pthread_t*)malloc(sizeof(pthread_t) * THREAD_AMOUNT);
	if (pthread_mutex_init(&app->locker, NULL))
		ft_error("MUTEX BROKE");
	i = 0;
	while (i < THREAD_AMOUNT)
	{
		threads_info[i].y_start = i * (SCREEN_HEIGHT / THREAD_AMOUNT);
		threads_info[i].y_finish = (i + 1) * (SCREEN_HEIGHT / THREAD_AMOUNT);
		threads_info[i].app = app;
		if (pthread_create(&threads_info[i].pthread, NULL, draw_thread, &threads_info[i]))
			ft_error("Threads was crashed");
		i++;
	}
	i = -1;/**/
	while (++i < THREAD_AMOUNT)
		pthread_join(threads_info[i].pthread, NULL);
//		i++;
	free(threads_info);
//	y = -1;
//	while (++y < SCREEN_HEIGHT)
//	{
//		x = -1;
//		while (++x < SCREEN_WIDTH)
//		{
//			app->scene.cur_object = 0;
//			app->camera.direct = vec_normalize(rotation_y(&app->camera, to_viewport(x, y)));
//			color = raytrace(1, INF, app);
//			set_pixel(app->sdl->surface, x, y, color);
//		}
//	}
	SDL_UpdateWindowSurface(app->sdl->window);
}
