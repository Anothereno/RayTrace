#include "RTv1.h"

void	ft_error(char *str)
{
	ft_putendl(str);
	exit(0);
}


int	choose_scene(t_app *app, char **av)
{
	char	path[50];

	app->cur_scene = path;
	app->number_scene = 0;


	if ((ft_strcmp(av[1], "1.scene")) == 0)
	{
		app->number_scene = 1;
		ft_strcpy(app->cur_scene, "./scenes/1.scene");
	}
	else if ((ft_strcmp(av[1], "2.scene")) == 0)
	{
		app->number_scene = 2;
		ft_strcpy(app->cur_scene, "./scenes/2.scene");
	}
	else if ((ft_strcmp(av[1], "3.scene")) == 0)
	{
		app->number_scene = 3;
		ft_strcpy(app->cur_scene, "./scenes/3.scene");
	}
	else if ((ft_strcmp(av[1], "4.scene")) == 0)
	{
		app->number_scene = 4;
		ft_strcpy(app->cur_scene, "./scenes/4.scene");
	}
	else if (app->cur_scene == 0)
		return(0);
	return (1);
}

int		main(int argc, char **argv)
{
	t_app	*app;

//	getchar();
	if (argc != 2)
		ft_error("Configuration file not found.\n"
		   "Usage : ./RTv1  configuration_file.scene");
	app = (t_app *)malloc(sizeof(t_app));
	app->sdl = (t_sdl *)malloc(sizeof(t_sdl));
	init_app(app);
	read_file_count_obj(app, argc, argv);
	read_file_write_obj(app, argc, argv);
//	if (choose_scene(app, av) && load_parser(app))
	{
		start_the_game(app);
	}

	return 0;
}