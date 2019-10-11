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

void	vector_mult_scal2(t_vector *res,t_vector *first, double num)
{
	res->x = first->x * num;
	res->y = first->y * num;
	res->z = first->z * num;
}

t_object_intersect set_intersect(double first, double second)
{
	t_object_intersect res;


	if (first < 0)
		first = second;
	if (first < 0)
		res.distance = INF;
	res.distance = MIN(first, second);
	return (res);
}

t_color set_color(int red, int green, int blue)
{
	t_color color;

	color.red = clamp(0, 255, red);
	color.green = clamp(0, 255, green);
	color.blue = clamp(0, 255, blue);
	return (color);
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

void light_calculate(t_app *app, t_object *object)
{
	double		result_intens;
	t_vector	light_direct;
	double 		diffuse;
	double		light_intensity;
	t_vector	R;
	t_vector	V;
	t_object	hit;
	double		max;
	double		light_distance;
	t_vector	sub;
	int			i;
	double		dot;
	double		rot;

	i = -1;
	object->diffuse = 0.1;
	object->specular = 0;
	while (++i < app->scene.lights_amount)
	{
		sub = vector_sub(app->scene.lights[i].position, object->hit_point);
		light_direct = vec_normalize(sub);
		light_distance = vector_length(sub);
		hit = find_intersected_spheres(app, object->hit_point, light_direct, 0.001f, INF);
		hit = find_intersected_cones(app, object->hit_point, light_direct, 0.001f, INF, hit);
		hit = find_intersected_cylinders(app, object->hit_point, light_direct, 0.001f, INF, hit);

		if (hit.flag != 0 && hit.distance < light_distance)
			continue;
		dot = MAX(0, vector_dot(light_direct, object->normal));
		light_intensity = app->scene.lights[i].intensity * 200;
		light_intensity /= M_PI * pow(light_distance, 2.0);
		object->diffuse += light_intensity * dot;
		object->specular += pow(MAX(0, vector_dot(
				vec_invert(reflective(vec_invert(light_direct),
						object->normal)), app->camera.direct)), 300) * light_intensity;
	}
}


t_color	to_hsv(int rand_num)
{
	t_color color;
	double	calc_color;

	calc_color = (1 - fabs(fmod(rand_num / 60.0, 2) - 1)) * 255;
	if (rand_num >= 0 && rand_num < 60)
		color = set_color(255, calc_color, 0);
	else if (rand_num >= 60 && rand_num < 120)
		color = set_color(calc_color, 255, 0);
	else if (rand_num >= 120 && rand_num < 180)
		color = set_color(0, 255, calc_color);
	else if (rand_num >= 180 && rand_num < 240)
		color = set_color(0, calc_color, 255);
	else if (rand_num >= 240 && rand_num < 300)
		color = set_color(calc_color, 0, 255);
	else
		color = set_color(255, 0, calc_color);
	return(color);
}

t_color	color_randomize()
{
	t_color color;

	color = to_hsv(rand() % 360);
	return (color);
}

t_color pallete(t_color color, double num)
{
	t_color res;

	res.red = clamp(0, 255, color.red * num);
	res.blue = clamp(0, 255, color.blue * num);
	res.green = clamp(0, 255, color.green * num);
	return (res);
}

void	vector_inverse(t_vector *normal)
{
	normal->x = -normal->x;
	normal->y = -normal->y;
	normal->z = -normal->z;
}

void	sum_color(t_color *first, t_color second)
{
	first->red += second.red;
	first->blue += second.blue;
	first->green += second.green;
	*first = set_color(first->red, first->green, first->blue);
}

t_color raytrace(double length_min, double length_max, t_app *app)
{
	t_color	pixel_color;
	t_color	temp_color;
	t_object	object;


	object = find_intersected_spheres(app, app->camera.camera, app->camera.direct, length_min, length_max);
	object = find_intersected_cylinders(app, app->camera.camera, app->camera.direct, length_min, length_max, object);
	object = find_intersected_cones(app, app->camera.camera, app->camera.direct, length_min, length_max, object);
	object = find_intersected_planes(app, app->camera.camera, app->camera.direct, length_min, length_max, object);
	if (!object.flag)
		return (set_color(0, 0, 0));
	light_calculate(app, &object);
	pixel_color = pallete(object.color, object.diffuse);
	temp_color = pallete(set_color(255, 255, 255), object.specular);
	sum_color(&pixel_color, temp_color);
	return (pixel_color);
}
