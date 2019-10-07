#include "RTv1.h"

void	set_axis(t_vector *axis, t_vector rot)
{
	t_vector	tmp_1;
	t_vector	tmp_2;

	rot.y *= M_PI / 180.0;
	rot.x *= M_PI / 180.0;
	rot.z *= M_PI / 180.0;
	tmp_1 = set_vertex(0.0, -1.0, 0.0);
	tmp_2 = tmp_1;
	tmp_1.x = tmp_2.x * cos(rot.z) - tmp_2.y * sin(rot.z);
	tmp_1.y = tmp_2.x * sin(rot.z) + tmp_2.y * cos(rot.z);
	tmp_2 = tmp_1;
	tmp_1.x = tmp_2.x * cos(rot.y) + tmp_2.z * sin(rot.y);
	tmp_1.z = -tmp_2.x * sin(rot.y) + tmp_2.z * cos(rot.y);
	tmp_2 = tmp_1;
	tmp_1.y = tmp_2.y * cos(rot.x) - tmp_2.z * sin(rot.x);
	tmp_1.z = tmp_2.y * sin(rot.x) + tmp_2.z * cos(rot.x);
	*axis = vec_normalize(tmp_1);
}

t_cylinder new_cylinder(t_vector axis, double radius, t_color color, double height, int specular, t_vector rot)
{
	t_cylinder	res;

	res.axis = axis;
	res.radius = radius;
	res.color = color;
	res.height = height;
	res.specular = specular;
	set_axis(&res.axis, rot);
	return (res);
}

double   cylinder_intersection(t_vector camera, t_vector direct, t_cylinder cylinder)
{
	t_vector oc;
	double a;
	double b;
	double c;

	oc = vector_sub(camera, cylinder.center);
	a = vec_dot(direct, direct) - pow(vec_dot(direct, cylinder.axis), 2);
	b = (vec_dot(direct, oc) - vec_dot(direct, cylinder.axis) * vec_dot(oc, cylinder.axis)) * 2;
	c = vec_dot(oc, oc) - pow(vec_dot(oc, cylinder.axis), 2) - cylinder.radius * cylinder.radius;
	return (b * b - 4 * (a * c));
}

t_intersect	find_abc(t_vector camera, t_vector direct, t_cylinder cylinder)
{
	t_intersect abc;

	abc.oc = vector_sub(camera, cylinder.center);
	abc.a = vec_dot(direct, direct) - pow(vec_dot(direct, cylinder.axis), 2);
	abc.b = (vec_dot(direct, abc.oc) - vec_dot(direct, cylinder.axis) * vec_dot(abc.oc, cylinder.axis)) * 2;
	abc.c = vec_dot(abc.oc, abc.oc) - pow(vec_dot(abc.oc, cylinder.axis), 2) - cylinder.radius * cylinder.radius;
	abc.delta = abc.b * abc.b - 4 * (abc.a * abc.c);
	abc.b = -abc.b;
	abc.a = abc.a * 2;
	return (abc);
}

t_object_intersect	intersect_ray_cylinder(t_vector camera, t_vector direct, t_cylinder cylinder)
{
	t_intersect abc;

	abc = find_abc(camera, direct, cylinder);

	if (fabs(abc.delta) < 0.001)
		return (set_intersect(0, 999999, 999999));
	else if (abc.delta == 0)
		return (set_intersect(1,
							  ((abc.b) + sqrt(abc.delta)) / abc.a, ((abc.b) - sqrt(abc.delta)) / abc.a));
	else
		return (set_intersect(2,
							  ((abc.b) + sqrt(abc.delta)) / abc.a, ((abc.b) - sqrt(abc.delta)) / abc.a));
}

t_object	find_intersected_cylinders(t_app *app, t_vector camera, t_vector direct,
									   double length_min, double length_max, t_object prev_object)
{
	int		i;
	t_object object;
	t_object_intersect intersect_cylinder;

	i = -1;
	object.flag = 0;
	object.distance = 999999;
	while (++i < app->scene.cylinders_amount)
	{
		intersect_cylinder = intersect_ray_cylinder(camera, direct, app->scene.cylinders[i]);
		if (between(length_min, length_max, intersect_cylinder.first) &&
			intersect_cylinder.first < object.distance)
		{
			object.distance = intersect_cylinder.first;
			object.axis = app->scene.cylinders[i].axis;
			object.center = app->scene.cylinders[i].center;
			object.color = app->scene.cylinders[i].color;
			object.specular = app->scene.cylinders[i].specular;
			app->scene.cur_obj_type = 'y';

			object.flag = 1;
		}
		if (between(length_min, length_max, intersect_cylinder.second) &&
			intersect_cylinder.second < object.distance)
		{
			object.distance = intersect_cylinder.second;
			object.axis = app->scene.cylinders[i].axis;
			object.center = app->scene.cylinders[i].center;
			object.color = app->scene.cylinders[i].color;
			object.specular = app->scene.cylinders[i].specular;
			app->scene.cur_obj_type = 'y';

			object.flag = 1;
		}
		double r = camera.y + object.distance * direct.y;

/*		if (!((r >= object.axis.y) && (r <= object.axis.y + app->scene.cylinders[i].height)))
			object.flag = 0;*/
	}
	if (object.distance < prev_object.distance)
		return (object);
	return (prev_object);
}

