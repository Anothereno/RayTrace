#include "RTv1.h"

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

t_vector to_vieport2(int x, int y)
{
	t_vector vector;

	float u_scale = SCREEN_WIDTH > SCREEN_HEIGHT ? (float)SCREEN_WIDTH / (float)SCREEN_HEIGHT : 1.0f;
	float v_scale = SCREEN_HEIGHT > SCREEN_WIDTH ? (float)SCREEN_HEIGHT / (float)SCREEN_WIDTH : 1.0f;

	vector.x = (float)x / (SCREEN_WIDTH - 1) - 0.5;
	vector.y = 0.5f - (float)y / (SCREEN_HEIGHT - 1);
	vector.x *= u_scale;
	vector.y *= v_scale;
	vector.z = 1.0f;
	return (vector);
}

t_sphere new_sphere(t_vector center, float radius, t_color color, int specular)
{
	t_sphere	res;

	res.center = center;
	res.radius = radius;
	res.color = color;
	res.specular = specular;
	return (res);
}

t_plane new_plane(t_vector center, t_vector normal, t_color color, int specular)
{
	t_plane	res;

	res.center = center;
	res.normal = normal;
	res.color = color;
	res.specular = specular;
	return (res);
}

t_cylinder new_cylinder(t_vector center, float radius, t_color color, float height, int specular)
{
	t_cylinder	res;

	res.center = center;
	res.radius = radius;
	res.color = color;
	res.height = height;
	res.specular = specular;
	return (res);
}

t_light new_light(t_vector direct, float intensity, char type)
{
	t_light res;

	res.intensity = intensity;
	res.direct = direct;
	res.type = type;
	return res;
}

float	clamp(int min, int max, int num)
{
	if (num < min)
		return (min);
	else if (num > max)
		return (max);
	return (num);
}

void	prepare_objects(t_app *app)
{
	int i;

	i = -1;
	while (++i < app->scene.spheres_amount)
	{
		app->scene.spheres[i] = new_sphere(set_vertex(i - 2, 0, i * 2),i + 2,
				set_color(30 * i *2 + 50, 20 * i + 30, 20 * i + 120),10 + i * 30);
	}
	i = -1;
	while (++i < app->scene.cylinders_amount)
	{
		app->scene.cylinders[i] = new_cylinder(set_vertex(i - 2, 0, i * 6),
										   i + 1, set_color(30 * i *2 + 50, 20 * i + 30, 20 * i + 120), 2.0f + i * 100, 200);
	}
	i = -1;
	while (++i < app->scene.planes_amount)
	{
		app->scene.planes[i] = new_plane(set_vertex(0, -3, 8),
				set_vertex(0, i + i * 90, 3), set_color(30, 40, 180), 140);
	}
	app->scene.planes[0].color = set_color(0, 200, 0);
//	app->scene.spheres[2].center = set_vertex(0, -5001, 0);
//	app->scene.spheres[2].radius = 5000;
//	app->scene.spheres[2].color = set_color(255, 255, 0);
//	app->scene.spheres[2].specular = 500;

}

void	prepare_light(t_app *app)
{
	int i;

	i = -1;
	while (++i < app->scene.lights_amount)
	{
		app->scene.lights[i] = new_light(set_vertex(-20 + i, 6 + i, -20 + i), 2.0f, 'p');
	}
	app->scene.lights[0].type = 'd';
	app->scene.lights[0].intensity = 0.9f;
	app->scene.lights[0].direct = set_vertex(-15, 40, -14);
	app->scene.lights[1].type = 'a';
	app->scene.lights[1].intensity = 0.4f;
//	app->scene.lights[2].type = 'd';
//	app->scene.lights[2].intensity = 0.9f;
//	app->scene.lights[2].direct = set_vertex(20, 40, -10);
}

t_vector rotation_y(t_app *app, t_vector viewport)
{
	t_vector res;

	res.x = viewport.x * cosf(app->camera.rotate_angle_y)
			+ viewport.z * sinf(app->camera.rotate_angle_y);
	res.y = viewport.y;
	res.z = viewport.x * sinf(app->camera.rotate_angle_y) * -1.0f
			+ viewport.z * cosf(app->camera.rotate_angle_y);
	return (res);
}

void	start_the_game2(t_app *app)
{
	prepare_light(app);
	prepare_objects(app);
	app->camera.camera = set_vertex(0.0f, 0.0f, -5.50f);
	redraw(app);
	while (1)
	{
		if (!event_handling2(app))
			break;
	}
	SDL_Quit();
	SDL_DestroyWindow(app->sdl->window);
}

void	redraw(t_app *app)
{
	t_color		color;

		int x = 0;
		int y = 0;
		while (y < SCREEN_HEIGHT)
		{
			x = 0;
			while (x < SCREEN_WIDTH)
			{
				app->scene.cur_object = 0;
				app->camera.direct = rotation_y(app, to_vieport2(x, y));
				color = raytrace(app->camera.camera, app->camera.direct, 1.0f, 999999.0f, app);
				set_pixel(app->sdl->surface, x, y, color);
				x++;
			}
			y++;
		}
		SDL_UpdateWindowSurface(app->sdl->window);
}