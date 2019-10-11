#include "RTv1.h"

int 	amount_elements(char **string)
{
	int i;
	int res;

	res = 0;
	i  = -1;
	while (string[++i] != 0)
		res++;
	return (res);
}

void	string_processing_counting(char **string, t_app *app, int amount)
{

	if (ft_strequ(string[0], "sphere") && amount == 5)
		app->scene.spheres_amount++;
	else if (ft_strequ(string[0], "plane") && amount == 7)
		app->scene.planes_amount++;
	else if (ft_strequ(string[0], "cone") && amount == 8)
		app->scene.cones_amount++;
	else if (ft_strequ(string[0], "cylinder") && amount == 8)
		app->scene.cylinders_amount++;
	else if (ft_strequ(string[0], "camera") && amount == 7)
		app->scene.cameras_amount++;
	else if (ft_strequ(string[0], "light") && amount == 5)
		app->scene.lights_amount++;
	else
		ft_error("Wrong file");
}

void	string_processing_writing(char **string, t_app *app, int amount)
{

	if (ft_strequ(string[0], "sphere") && amount == 5)
	{
		app->scene.spheres[app->scene.cur_sphere] = new_sphere(set_vertex(ft_atoi(string[1]), ft_atoi(string[2]),
				ft_atoi(string[3])), ft_atoi(string[4]));
		app->scene.cur_sphere++;
	}
	else if (ft_strequ(string[0], "plane") && amount == 7)
	{
		app->scene.planes[app->scene.cur_plane] = new_plane(set_vertex(ft_atoi(string[1]), ft_atoi(string[2]),
																		  ft_atoi(string[3])),
															set_vertex(ft_atoi(string[4]), ft_atoi(string[5]),
																		  ft_atoi(string[6])));
		app->scene.cur_plane++;
	}
	else if (ft_strequ(string[0], "cone") && amount == 8)
	{
		app->scene.cones[app->scene.cur_cone] = new_cone(set_vertex(ft_atoi(string[1]), ft_atoi(string[2]),
																	   ft_atoi(string[3])),
															ft_atoi(string[4]),
															set_vertex(ft_atoi(string[5]), ft_atoi(string[6]),
																	   ft_atoi(string[7])));
		app->scene.cur_cone++;

	}
	else if (ft_strequ(string[0], "cylinder") && amount == 8)
	{
		app->scene.cylinders[app->scene.cur_cylinder] = new_cylinder(set_vertex(ft_atoi(string[1]), ft_atoi(string[2]),
																	ft_atoi(string[3])),
														 ft_atoi(string[4]),
														 set_vertex(ft_atoi(string[5]), ft_atoi(string[6]),
																	ft_atoi(string[7])));

		app->scene.cur_cylinder++;

	}
	else if (ft_strequ(string[0], "camera") && amount == 7)
	{
		app->camera.camera = set_vertex(ft_atoi(string[1]), ft_atoi(string[2]), ft_atoi(string[3]));
	}
	else if (ft_strequ(string[0], "light") && amount == 5)
	{
		app->scene.lights[app->scene.cur_light] = new_light(set_vertex(ft_atoi(string[1]), ft_atoi(string[2]),
							 ft_atoi(string[3])), ft_atoi(string[4]));
		app->scene.cur_light++;
	}
	else
		ft_error("Wrong file");
}

void	clear_split(char **string)
{
	int i;

	i = 0;
	while (string[i] != 0)
	{
		free(string[i]);
		i++;
	}
	free(string);
}

void	read_file_count_obj(t_app *app, int argc, char** argv)
{
	int		fd;
	char	*line;
	char	**temp;
	int		amount;

	if ((fd = open(argv[1], O_RDONLY)) < 3)
		ft_error("Configuration file not found.\n"
				 "Usage : ./RTv1  configuration_file.scene");
	while (get_next_line(fd, &line))
	{
		temp = ft_strsplit(line, ' ');
		amount = amount_elements(temp);
		string_processing_counting(temp, app, amount);
		free(line);
		clear_split(temp);
		//make free TEMP MUST HAVE
	}
	init_objects(&app->scene);
	close(fd);

}

void	read_file_write_obj(t_app *app, int argc, char** argv)
{
	int		fd;
	char	*line;
	char	**temp;
	int		amount;

	if ((fd = open(argv[1], O_RDONLY)) < 3)
		ft_error("Configuration file not found.\n"
				 "Usage : ./RTv1  configuration_file.scene");
	while (get_next_line(fd, &line))
	{
		temp = ft_strsplit(line, ' ');
		amount = amount_elements(temp);
		string_processing_writing(temp, app, amount);
		free(line);
		clear_split(temp);
		//make free TEMP MUST HAVE

	}
	close(fd);
}