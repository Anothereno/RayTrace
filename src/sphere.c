#include "RTv1.h"

t_sphere new_sphere(t_vector center, double radius, t_color color, int specular)
{
	t_sphere	res;

	res.center = center;
	res.radius = radius;
	res.color = color;
	res.specular = specular;
	return (res);
}

t_object_intersect	intersect_ray_sphere(t_vector camera, t_vector direct,
										   t_sphere sphere)
{
	t_vector oc;
	double a;
	double b;
	double c;
	double discr;

	oc = vector_sub(camera, sphere.center);
	a = vector_dot(direct, direct);
	b = 2.0f * vector_dot(direct, oc);
	c = vector_dot(oc, oc) - sphere.radius * sphere.radius;
	discr = b * b - 4 * a * c;
	if (discr < 0)
		return (set_intersect(INF, INF));
	else
		return (set_intersect(
				((-b) + sqrt(discr)) / (2 * a),
				((-b) - sqrt(discr)) / (2 * a)));
}

t_object	find_intersected_spheres(t_app *app, t_vector camera, t_vector direct,
									 double length_min, double length_max)
{
	int		i;
	t_object object;
	t_object_intersect intersect_sphere;

	i = -1;
	object.flag = 0;
	object.distance = INF;
	while (++i < app->scene.spheres_amount)
	{
		intersect_sphere = intersect_ray_sphere(camera, direct, app->scene.spheres[i]);
		if (between(length_min, INF, intersect_sphere.distance) &&
			intersect_sphere.distance < object.distance)
		{
			object.distance = intersect_sphere.distance;
			object.hit_point = vec_add(camera, vec_mul_by(direct, object.distance));
			object.center = app->scene.spheres[i].center;
			object.normal = vector_sub(object.hit_point, object.center);
			object.normal = (vec_normalize(object.normal));
			object.color = app->scene.spheres[i].color;
			object.specular = app->scene.spheres[i].specular;
			object.flag = 1;
		}
	}
	return (object);
}
