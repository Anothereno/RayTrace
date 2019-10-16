/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   start.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hdwarven <hdwarven@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/10/13 19:14:22 by hdwarven          #+#    #+#             */
/*   Updated: 2019/10/13 19:15:04 by hdwarven         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "rtv.h"

double	clamp(int min, int max, int num)
{
	if (num < min)
		return (min);
	else if (num > max)
		return (max);
	return (num);
}

void	quit(t_app *app)
{
	if (app)
	{
		SDL_FreeSurface(app->sdl->surface);
		SDL_DestroyWindow(app->sdl->window);
		SDL_Quit();
		free(app->sdl);
		if (app->scene.lights)
			free(app->scene.lights);
		if (app->scene.cylinders)
			free(app->scene.cylinders);
		if (app->scene.cones)
			free(app->scene.cones);
		if (app->scene.spheres)
			free(app->scene.spheres);
		if (app->scene.planes)
			free(app->scene.planes);
		free(app);
	}
}

void	start_the_game(t_app *app)
{
	redraw(app);
	while (1)
		if (!event_handling(app))
			break ;
	quit(app);
}

void	*draw_thread(void *thread_info)
{
	int			x;
	int			y;
	t_thread	thread;

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
		if (pthread_create(&threads_info[i].pthread,
				NULL, draw_thread, &threads_info[i]))
			ft_error("Threads was crashed", NULL);
	}
	i = -1;
	while (++i < THREAD_AMOUNT)
		pthread_join(threads_info[i].pthread, NULL);
	SDL_UpdateWindowSurface(app->sdl->window);
}
