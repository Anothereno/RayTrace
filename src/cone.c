#include "RTv1.h"

t_cone	new_cone(t_vector center, double radius, t_color color, double height, int specular)
{
	t_cone	res;

	res.center = center;
	res.radius = radius;
	res.color = color;
	res.height = height;
	res.specular = specular;
	return (res);
}


t_object_intersect	intersect_ray_cone(t_vector camera, t_vector direct,
										 t_cone cone)
{

	double A;
	double B;
	double D;

	double a;
	double b;
	double c;

	A = camera.x - cone.center.x;
	B = camera.z - cone.center.z;
	D = cone.height - camera.y + cone.center.y;

	double tan = (cone.radius / cone.height) * (cone.radius / cone.height);
	a = (direct.x * direct.x) + (direct.z * direct.z) - (tan * (direct.y * direct.y));
	b = (2 * A * direct.x) + (2 * B * direct.z) + (2 * tan * D * direct.y);
	c = (A * A) + (B * B) - (tan * (D * D));

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

t_object	find_intersected_cones(t_app *app, t_vector camera, t_vector direct,
								   double length_min, double length_max, t_object prev_object)
{
	int		i;
	t_object object;
	t_object_intersect intersect_cone;

	i = -1;
	object.flag = 0;
	object.distance = 999999;
	while (++i < app->scene.cones_amount)
	{
		intersect_cone = intersect_ray_cone(camera, direct, app->scene.cones[i]);
		if (between(length_min, length_max, intersect_cone.first) &&
			intersect_cone.first < object.distance)
		{
			object.distance = intersect_cone.first;
			object.center = app->scene.cones[i].center;
			object.color = app->scene.cones[i].color;
			object.specular = app->scene.cones[i].specular;
			object.flag = 1;
		}
		if (between(length_min, length_max, intersect_cone.second) &&
			intersect_cone.second < object.distance)
		{
			object.distance = intersect_cone.second;
			object.center = app->scene.cones[i].center;
			object.color = app->scene.cones[i].color;
			object.specular = app->scene.cones[i].specular;
			object.flag = 1;
		}
		double r = camera.y + object.distance * direct.y;

		if (!((r > object.center.y) && (r < object.center.y + app->scene.cones[i].height)))
			object.flag = 0;
	}
	if (object.distance < prev_object.distance)
		return (object);
	return (prev_object);
}