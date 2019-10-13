/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   new_objects.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hdwarven <hdwarven@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/10/13 19:04:05 by hdwarven          #+#    #+#             */
/*   Updated: 2019/10/13 19:11:26 by hdwarven         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "RTv1.h"

void	create_sphere(t_app *app, char **string)
{
	app->scene.spheres[app->scene.cur_sphere] = new_sphere(app,
		set_vector(ft_atoi(string[1]), ft_atoi(string[2]),
		ft_atoi(string[3])), ft_atoi(string[4]));
}

void	create_plane(t_app *app, char **string)
{
	app->scene.planes[app->scene.cur_plane] = new_plane(app,
		set_vector(ft_atoi(string[1]), ft_atoi(string[2]),
		ft_atoi(string[3])),
		set_vector(ft_atoi(string[4]), ft_atoi(string[5]),
		ft_atoi(string[6])));
}

void	create_cone(t_app *app, char **string)
{
	app->scene.cones[app->scene.cur_cone] = new_cone(app,
		set_vector(ft_atoi(string[1]), ft_atoi(string[2]),
		ft_atoi(string[3])), ft_atoi(string[4]),
		set_vector(ft_atoi(string[5]), ft_atoi(string[6]),
		ft_atoi(string[7])));
}

void	create_cylinder(t_app *app, char **string)
{
	app->scene.cylinders[app->scene.cur_cylinder] = new_cylinder(app,
		set_vector(ft_atoi(string[1]), ft_atoi(string[2]),
		ft_atoi(string[3])), ft_atoi(string[4]),
		set_vector(ft_atoi(string[5]), ft_atoi(string[6]),
		ft_atoi(string[7])));
}

void	create_light(t_app *app, char **string)
{
	app->scene.lights[app->scene.cur_light] = new_light(app,
		set_vector(ft_atoi(string[1]), ft_atoi(string[2]),
		ft_atoi(string[3])), ft_atoi(string[4]));
}
