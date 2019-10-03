#include "RTv1.h"

t_cylinder new_cylinder(t_vector center, double radius, t_color color, double height, int specular)
{
	t_cylinder	res;

	res.center = center;
	res.radius = radius;
	res.color = color;
	res.height = height;
	res.specular = specular;
	return (res);
}

t_object_intersect	intersect_ray_cylinder(t_vector camera, t_vector direct,
											 t_cylinder cylinder)
{
	double a;
	double b;
	double c;

	a = (direct.x * direct.x) + (direct.z * direct.z);
	b = 2.0f * (direct.x * (camera.x - cylinder.center.x) + direct.z * (camera.z - cylinder.center.z));
	c = (camera.x - cylinder.center.x) * (camera.x - cylinder.center.x) + (camera.z - cylinder.center.z) * (camera.z - cylinder.center.z) - (cylinder.radius * cylinder.radius);
	double delta = b * b - 4 * (a * c);
	if (fabs(delta) < 0.001)
		return (set_intersect(0, 999999, 999999));
	else if (delta == 0)
		return (set_intersect(1,
							  ((-b) + sqrt(delta)) / (2 * a),
							  ((-b) - sqrt(delta)) / (2 * a)));
	else
		return (set_intersect(2,
							  ((-b) + sqrt(delta)) / (2 * a),
							  ((-b) - sqrt(delta)) / (2 * a)));
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
			object.center = app->scene.cylinders[i].center;
			object.color = app->scene.cylinders[i].color;
			object.specular = app->scene.cylinders[i].specular;
			object.flag = 1;
		}
		if (between(length_min, length_max, intersect_cylinder.second) &&
			intersect_cylinder.second < object.distance)
		{
			object.distance = intersect_cylinder.second;
			object.center = app->scene.cylinders[i].center;
			object.color = app->scene.cylinders[i].color;
			object.specular = app->scene.cylinders[i].specular;
			object.flag = 1;
		}
		double r = camera.y + object.distance * direct.y;

		if (!((r >= object.center.y) && (r <= object.center.y + app->scene.cylinders[i].height)))
			object.flag = 0;
	}
	if (object.distance < prev_object.distance)
		return (object);
	return (prev_object);
}

