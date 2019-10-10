#include "RTv1.h"

void	string_processing(char **string, t_app *app)
{

}

void	read_file(t_app *app, int argc, char** argv)
{
	int fd;
	char *line;
	char **temp;

	if ((fd = open(argv[1], O_RDONLY)) < 3)
		ft_error("Configuration file not found.\n"
				 "Usage : ./RTv1  configuration_file.scene");
	while (get_next_line(fd, &line))
	{
		temp = ft_strsplit(line, '\t');
		string_processing(temp, app);
	}
}