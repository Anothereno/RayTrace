#include "RTv1.h"

int 	out_of_border(int x, int y)
{
    if (x < 0 || x > SCREEN_WIDTH - 1)
        return (1);
    if (y < 0 || y > SCREEN_HEIGHT - 1)
        return (1);
    return (0);
}

void	set_pixel(SDL_Surface *surface, int x, int y, t_color c)
{
	int		offset;

    if (out_of_border(x, y))
        return ;
	offset = 4 * (y * surface -> w + x);
	unsigned char* pixels = (unsigned char*)surface->pixels;
	pixels[offset] = c.blue;
	pixels[offset + 1] = c.green;
	pixels[offset + 2] = c.red;
}