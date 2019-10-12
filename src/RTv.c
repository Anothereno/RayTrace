#include "RTv1.h"

t_vector set_vertex(double x, double y, double z)
{
	t_vector res;

	res.x = x;
	res.y = y;
	res.z = z;
	return (res);
}

t_vector	vector_add(t_vector first, t_vector second)
{
	t_vector res;

	res.x = first.x + second.x;
	res.y = first.y + second.y;
	res.z = first.z + second.z;
	return (res);
}

t_vector	vector_sub(t_vector first, t_vector second)
{
	t_vector res;

	res.x = first.x - second.x;
	res.y = first.y - second.y;
	res.z = first.z - second.z;
	return (res);
}


void	vector_sub3(t_vector *res,t_vector *first, t_vector *second)
{

	res->x = first->x - second->x;
	res->y = first->y - second->y;
	res->z = first->z - second->z;
}

t_vector	vector_div_scal(t_vector first, double num)
{
	t_vector res;

	res.x = first.x / num;
	res.y = first.y / num;
	res.z = first.z / num;
	return (res);
}

t_vector	vector_mult_scal(t_vector first, double num)
{
	t_vector res;

	res.x = first.x * num;
	res.y = first.y * num;
	res.z = first.z * num;
	return (res);
}

double	set_intersect(double first, double second)
{
	double distance;

	if (first < 0)
		first = second;
	distance = MIN(first, second);
	return (distance);
}

double vector_dot(t_vector first, t_vector second)
{
	return (first.x * second.x + first.y * second.y + first.z * second.z);
}

double vector_dot2(t_vector *first, t_vector *second)
{
	return (first->x * second->x + first->y * second->y + first->z * second->z);
}

double	vector_length(t_vector vector)
{
	return (sqrt(vector_dot(vector, vector)));
}

double	vector_length2(t_vector *vector)
{
	return (sqrt(vector_dot2(vector, vector)));
}

t_vector			vector_dot_scalar(t_vector vector, double num)
{
	t_vector res;

	res.x = vector.x * num;
	res.y = vector.y * num;
	res.z = vector.z * num;
	return (res);
}

int 	between(double min, double max, double num)
{
	if (num >= min && num <= max)
		return (1);
	return (0);
}

t_vector	reflective(t_vector vector, t_vector normal)
{
	t_vector res;

	res = vector_sub(vector, vector_mult_scal(vector_mult_scal(normal, vector_dot(vector, normal)), 2));
	return res;
}

void light_calculate(t_app *app, t_object *object, t_camera *camera)
{
	t_vector	light_direct;
	double		light_intensity;
	t_object	hit;
	double		light_distance;
	t_vector	sub;
	int			i;
	double		dot;

	i = -1;
	object->diffuse = 0.1;
	object->specular = 0;
	while (++i < app->scene.lights_amount)
	{
		sub = vector_sub(app->scene.lights[i].position, object->hit_point);
		light_direct = vec_normalize(sub);
		light_distance = vector_length(sub);
		hit = find_intersected_spheres(app, object->hit_point, light_direct, 0.001f);
		hit = find_intersected_cones(app, object->hit_point, light_direct, 0.001f, hit);
		hit = find_intersected_cylinders(app, object->hit_point, light_direct, 0.001f, hit);

		if (hit.flag != 0 && hit.distance < light_distance)
			continue;
		dot = MAX(0, vector_dot(light_direct, object->normal));
		light_intensity = app->scene.lights[i].intensity * 200;
		light_intensity /= M_PI * pow(light_distance, 2.0);
		object->diffuse += light_intensity * dot;
		object->specular += pow(MAX(0, vector_dot(
				vec_invert(reflective(vec_invert(light_direct),
						object->normal)), camera->direct)), 300) * light_intensity;
	}
}

t_color pallete(t_color color, double num)
{
	t_color res;

	res.red = clamp(0, 255, color.red * num);
	res.blue = clamp(0, 255, color.blue * num);
	res.green = clamp(0, 255, color.green * num);
	return (res);
}

void raytrace(t_app *app, int x, int y)
{
	t_color		pixel_color;
	t_color		temp_color;
	t_object	object;
	t_camera	camera;

	camera = app->camera;
	camera.direct =
			vec_normalize(rotation_y(&camera,
									 to_viewport(x, y)));
	if (app->scene.spheres_amount != 0)
		object = find_intersected_spheres(app, camera.camera, camera.direct,1);
	if (app->scene.cylinders_amount != 0)
		object = find_intersected_cylinders(app, camera.camera, camera.direct,1, object);
	if (app->scene.cones_amount != 0)
		object = find_intersected_cones(app, camera.camera, camera.direct,1, object);
	if (app->scene.planes_amount != 0)
		object = find_intersected_planes(app, camera.camera, camera.direct, object);
	if (!object.flag)
	{
		set_pixel(app->sdl->surface, x, y, app->black);
		return ;
	}
	light_calculate(app, &object, &camera);
	pixel_color = pallete(object.color, object.diffuse);
	temp_color = pallete(app->white, object.specular);
	sum_color(&pixel_color, &temp_color);
	set_pixel(app->sdl->surface, x, y, pixel_color);

}
