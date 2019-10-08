#include "RTv1.h"

char	*write_map_to_string(int fd)
{
	char	*read_string;

	read_string = ft_strnew(999999999);
	read(fd, read_string, 999999999);
	return (read_string);
}

int		map_read(int fd, t_app *app)
{
	char	*scene;
	scene = write_map_to_string(fd);
	close(fd);

}