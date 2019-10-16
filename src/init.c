/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hdwarven <hdwarven@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/10/13 17:46:25 by hdwarven          #+#    #+#             */
/*   Updated: 2019/10/13 19:37:39 by hdwarven         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "rtv.h"

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
	SDL_Error(SDL_Init(SDL_INIT_VIDEO));
	app->sdl->window = SDL_CreateWindow("RTv1", 500, 400,
			SCREEN_WIDTH, SCREEN_HEIGHT, 0);
	app->sdl->surface = SDL_GetWindowSurface(app->sdl->window);
	app->sdl->keys = SDL_GetKeyboardState(NULL);
	app->camera.camera_speed = 3;
	app->camera.rotate_speed = 3.5;
	ft_bzero(&app->scene, sizeof(app->scene));
	app->scene.light_speed = 0.5;
	app->black = set_color(0, 0, 0);
	app->white = set_color(255, 255, 255);
	app->scene.cylinders = NULL;
	app->scene.spheres = NULL;
	app->scene.lights = NULL;
	app->scene.planes = NULL;
	app->scene.cones = NULL;
	srand(time(0));
}
