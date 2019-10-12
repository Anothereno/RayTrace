#include "RTv1.h"

t_plane		new_plane(t_vector center, t_vector normal)
{
	t_plane	res;

	res.center = center;
	res.normal = normal;
	res.color = color_randomize();
	res.specular = rand() % 1000;
	return (res);
}

double		intersect_ray_plane(t_vector camera, t_vector direct, t_plane plane)
{
	double		distance;
	double		plane_dot_ray;
	double		plane_dot_psr;

	plane_dot_ray = vector_dot(direct, plane.normal);
	if (plane_dot_ray == 0)
		return (999999);
	plane_dot_psr = vector_dot(plane.normal, vector_sub(plane.center, camera));
	distance = plane_dot_psr / plane_dot_ray;
	return (distance);
}

t_object	find_intersected_planes(t_app *app, t_vector camera,
								t_vector direct, t_object prev_object)
{
	int			i;
	t_object	object;
	double		distance;

	i = -1;
	object.flag = 0;
	object.distance = 999999;
	while (++i < app->scene.planes_amount)
	{
		distance = intersect_ray_plane(camera, direct, app->scene.planes[i]);
		if (between(1, INF, distance) && distance < object.distance)
		{
			object.distance = distance;
			object.center = app->scene.planes[i].center;
			object.color = app->scene.planes[i].color;
			object.specular = app->scene.planes[i].specular;
			object.hit_point = vec_add(camera, vec_mul_by(direct, object.distance));
			object.normal = vec_invert(app->scene.planes[i].normal);
			object.flag = 1;
		}
	}
	if (object.distance < prev_object.distance)
		return (object);
	return (prev_object);
}
