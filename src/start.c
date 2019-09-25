#include "RTv1.h"

/*void	clear_screen(t_app *app)
{
	image_clear(app->sdl->surface->pixels, 0, SCREEN_W * SCREEN_H * 4);
}*/

int     hit_sphere(t_vector center, float radius, t_ray ray)
{
    t_vector	oc;
    float	a;
    float	b;
    float	c;
    float	discriminant;

    oc = vector_sub(ray.camera, center);
    a = vector_dot(ray.direct, ray.direct);
    b = 2.0f * vec_dot(oc, ray.direct);
    c = vec_dot(oc, oc) - radius * radius;

    discriminant = b * b - 4 * a * c;

    float t1 = (-b + sqrtf(discriminant)) / (2.0f * a);
    float t2 = (-b - sqrtf(discriminant)) / (2.0f * a);
    return (t1 > -1.0f);
}

t_vector to_vieport(float x, float y)
{
    t_vector vector;

    float u_scale = SCREEN_WIDTH > SCREEN_HEIGHT ? (float)SCREEN_WIDTH / (float)SCREEN_HEIGHT : 1.0f;
    float v_scale = SCREEN_HEIGHT > SCREEN_WIDTH ? (float)SCREEN_HEIGHT / (float)SCREEN_WIDTH : 1.0f;

    vector.x = (float)x / (SCREEN_WIDTH - 1) - 0.5;
    vector.y = 0.5 - (float)y / (SCREEN_HEIGHT - 1);
    vector.x *= u_scale;
    vector.y *= v_scale;
    vector.z = 1.0f;
    return (vector);
}

t_sphere new_sphere(t_vector center, float radius, t_color color)
{
	t_sphere res;

	res.center = center;
	res.radius = radius;
	res.color = color;
	return res;
}

void	prepare_objects(t_app *app)
{
	int i;

	i = -1;
	while (++i < app->scene.amount)
	{
		app->scene.spheres[i] = new_sphere(set_vertex(i + 1, 0, i + 4),
				i * 3 + 1, set_color(30 * i + 100, 20 * i + 120, 20 * i + 120));
	}
}

void	start_the_game(t_app *app)
{
	t_vector	camera;
	t_vector	direct;
	t_color		color;
	color.red = 0;
	color.green = 200;
	color.blue = 10;

	prepare_objects(app);

	camera = set_vertex(0.0f, 0.0f, -5.50f);
	while (1)
	{
	    float x = 0;
	    float y = 0;
        //ft_memset(app->sdl->surface->pixels, 0, SCREEN_WIDTH * SCREEN_HEIGHT * 4);
		if (!event_handling(app))
			break;

		while (y < SCREEN_HEIGHT)
        {
		    x = 0;
		    while (x < SCREEN_WIDTH)
            {

		        direct = to_vieport(x , y);
                color = raytrace(camera, direct, 1, 999999, app);
                set_pixel(app->sdl->surface, x, y, color);
		        x++;
            }
		    y++;
        }

//		for (int x = 0; x < SCREEN_WIDTH; x++)
//		{
//			for (int y = 0; y < SCREEN_HEIGHT; y++)
//			{
//				canvas = field_to_view(x, y);
//			}
//		}
		SDL_UpdateWindowSurface(app->sdl->window);
//set_pixel(app->sdl->surface, 0, 0, &scene[0].color);
//SDL_UpdateWindowSurface((app->sdl->window));
	}
	SDL_Quit();
	SDL_DestroyWindow(app->sdl->window);
}