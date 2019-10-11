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

t_cylinder new_cylinder(t_vector center, double radius, t_vector rot)
{
	t_cylinder	res;

	res.center = center;
	res.radius = radius;
	res.color = color_randomize();
	res.specular = rand() % 1000;
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

	abc.oc = vector_sub(camera, cylinder.center);
	abc.a = vec_dot(direct, direct) - pow(vec_dot(direct, cylinder.axis), 2);
	abc.b = (vec_dot(direct, abc.oc) - vec_dot(direct, cylinder.axis) * vec_dot(abc.oc, cylinder.axis)) * 2;
	abc.c = vec_dot(abc.oc, abc.oc) - pow(vec_dot(abc.oc, cylinder.axis), 2) - cylinder.radius * cylinder.radius;
	abc.delta = abc.b * abc.b - 4 * (abc.a * abc.c);
	abc.b = -abc.b;
	abc.a = abc.a * 2;

//	abc = find_abc(camera, direct, cylinder);

	if (fabs(abc.delta) < 0.001)
		return (set_intersect(999999, 999999));
	else
		return (set_intersect(
				((abc.b) + sqrt(abc.delta)) / abc.a, ((abc.b) - sqrt(abc.delta)) / abc.a));
}

void normal_cylinder(t_app *app, t_cylinder *cylinder, t_object *object)
{
	t_vector obj_cam;
	double 		temp;

	obj_cam = vector_sub(app->camera.camera, cylinder->center);
	temp = vector_dot(app->camera.direct, cylinder->axis) * object->hit_point.distance +
		   vector_dot(obj_cam, cylinder->axis);
	object->normal = vector_sub(vector_sub(object->hit_point, cylinder->center),
								vector_mult_scal(cylinder->axis, temp));
	object->normal = vec_normalize(object->normal);
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
		if (between(length_min, length_max, intersect_cylinder.distance) &&
			intersect_cylinder.distance < object.distance)
		{
			object.distance = intersect_cylinder.distance;
			object.axis = app->scene.cylinders[i].axis;
			object.center = app->scene.cylinders[i].center;
			object.hit_point = vec_add(camera, vector_mult_scal(direct, object.distance));
			normal_cylinder(app, &app->scene.cylinders[i], &object);
			object.color = app->scene.cylinders[i].color;
			object.specular = app->scene.cylinders[i].specular;
			app->scene.cur_obj_type = 'y';

			object.flag = 1;
		}
	}
	if (object.distance < prev_object.distance)
		return (object);
	return (prev_object);
}

