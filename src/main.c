/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hdwarven <hdwarven@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/10/13 17:53:30 by hdwarven          #+#    #+#             */
/*   Updated: 2019/10/16 19:38:58 by hdwarven         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "rtv.h"

int		main(int argc, char **argv)
{
	t_app	*app;

	app = NULL;
	if (argc != 2)
		ft_error("No arguments passed.\n"
			"Usage : ./RTv1  configuration_file", app);
	app = (t_app *)malloc(sizeof(t_app));
	app->sdl = (t_sdl *)malloc(sizeof(t_sdl));
	init_app(app);
	read_file_count_obj(app, argv);
	read_file_write_obj(app, argv);
	start_the_game(app);
	quit(app);
	return (0);
}
