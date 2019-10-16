/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   read_file.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hdwarven <hdwarven@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/10/13 18:40:00 by hdwarven          #+#    #+#             */
/*   Updated: 2019/10/16 19:38:27 by hdwarven         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "rtv.h"

int		amount_elements(char **string)
{
	int i;
	int res;

	res = 0;
	i = -1;
	while (string[++i])
		res++;
	return (res);
}

void	string_processing_counting(char **string, t_app *app, int amount)
{
	if (ft_strequ(*string, "sphere") && amount == 5)
		app->scene.spheres_amount++;
	else if (ft_strequ(*string, "plane") && amount == 7)
		app->scene.planes_amount++;
	else if (ft_strequ(*string, "cone") && amount == 8)
		app->scene.cones_amount++;
	else if (ft_strequ(*string, "cylinder") && amount == 8)
		app->scene.cylinders_amount++;
	else if (ft_strequ(*string, "camera") && amount == 7)
		app->scene.cameras_amount++;
	else if (ft_strequ(*string, "light") && amount == 5)
		app->scene.lights_amount++;
	else
		ft_error("Wrong file", app);
}

void	string_processing_writing(char **string, t_app *app)
{
	if (ft_strequ(string[0], "sphere"))
		create_sphere(app, string);
	else if (ft_strequ(string[0], "plane"))
		create_plane(app, string);
	else if (ft_strequ(string[0], "cone"))
		create_cone(app, string);
	else if (ft_strequ(string[0], "cylinder"))
		create_cylinder(app, string);
	else if (ft_strequ(string[0], "camera"))
		set_camera(app, set_vector(ft_atoi(string[1]), ft_atoi(string[2]),
				ft_atoi(string[3])),
				set_vector(ft_atoi(string[4]), ft_atoi(string[5]),
				ft_atoi(string[6])));
	else if (ft_strequ(string[0], "light"))
		create_light(app, string);
	else
		ft_error("Wrong file\n", app);
}

void	read_file_count_obj(t_app *app, char **argv)
{
	int		fd;
	char	*line;
	char	**temp;
	int		amount;

	if ((fd = open(argv[1], O_RDONLY)) < 3)
		ft_error("Cannot read.\n"
			"Usage : ./RTv1  configuration_file.scene", app);
	while (get_next_line(fd, &line))
	{
		temp = ft_strsplit(line, ' ');
		amount = amount_elements(temp);
		string_processing_counting(temp, app, amount);
		clear_split(temp);
		free(line);
	}
	init_objects(&app->scene);
	close(fd);
}

void	read_file_write_obj(t_app *app, char **argv)
{
	int		fd;
	char	*line;
	char	**temp;

	if ((fd = open(argv[1], O_RDONLY)) < 3)
		ft_error("Cannot write.\n"
			"Usage : ./RTv1  configuration_file", app);
	else if (app->scene.cameras_amount < 1)
		ft_error("No camera set\n", app);
	else if (app->scene.lights_amount < 1)
		ft_error("No light spot installed\n", app);
	while (get_next_line(fd, &line))
	{
		temp = ft_strsplit(line, ' ');
		string_processing_writing(temp, app);
		clear_split(temp);
		free(line);
	}
	close(fd);
}
