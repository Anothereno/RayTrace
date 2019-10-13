/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hdwarven <hdwarven@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/10/13 17:53:30 by hdwarven          #+#    #+#             */
/*   Updated: 2019/10/13 17:54:00 by hdwarven         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "RTv1.h"

int		main(int argc, char **argv)
{
	t_app	*app;

	if (argc != 2)
		ft_error("No arguments passed.\n"
			"Usage : ./RTv1  configuration_file");
	app = (t_app *)malloc(sizeof(t_app));
	app->sdl = (t_sdl *)malloc(sizeof(t_sdl));
	init_app(app);
	read_file_count_obj(app, argv);
	read_file_write_obj(app, argv);
	start_the_game(app);
	return (0);
}
