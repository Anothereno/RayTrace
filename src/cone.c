#include "RTv1.h"

t_cone new_cone(t_vector center, double angle, t_vector rot)
{
	t_cone	res;

	res.center = center;
	res.angle = angle * RAD;
	res.color = color_randomize();
	res.specular = rand() % 1000;
	set_axis(&res.axis, rot);
	return (res);
}

t_object_intersect	     intersect_ray_cone(t_vector camera, t_vector direct, t_cone cone)
{

	t_vector obj_cam;
	double tan_angle;
	double a;
	double b;
	double c;

	obj_cam = vector_sub(camera, cone.center);
	tan_angle = tan(cone.angle);
	tan_angle = tan_angle * tan_angle + 1;
	a = vector_dot(direct, direct) - tan_angle * pow(vector_dot(direct, cone.axis), 2);
	b = (vector_dot(direct, obj_cam) - tan_angle * vector_dot(direct, cone.axis) *
			vector_dot(obj_cam, cone.axis)) * 2;
	c = vector_dot(obj_cam, obj_cam) - tan_angle * pow(vector_dot(obj_cam, cone.axis), 2);

	double delta = b * b - 4 * a * c;
	if (fabs(delta) < 0.001)
		return (set_intersect(INF, INF));
	else
		return (set_intersect(
				((-b) + sqrt(delta)) / (2 * a),
				((-b) - sqrt(delta)) / (2 * a)));
}

void normal_cone(t_app *app, t_cone *cone, t_object *object)
{
	t_vector obj_cam;
	double		tan_angle;
	double 		temp;

	obj_cam = vector_sub(app->camera.camera, cone->center);
	tan_angle = tan(cone->angle);
	tan_angle = tan_angle * tan_angle + 1;
	temp = vector_dot(app->camera.direct, cone->axis) * object->hit_point.distance +
			vector_dot(obj_cam, cone->axis);
	object->normal = vector_sub(vector_sub(object->hit_point, cone->center),
			vector_mult_scal(vector_mult_scal(cone->axis, temp), tan_angle));
	object->normal = vec_normalize(object->normal);
}

t_object	find_intersected_cones(t_app *app, t_vector camera, t_vector direct,
								   double length_min, double length_max, t_object prev_object)
{
	int		i;
	t_object object;
	t_object_intersect intersect_cone;

	i = -1;
	object.flag = 0;
	object.distance = INF;
	while (++i < app->scene.cones_amount)
	{
		intersect_cone = intersect_ray_cone(camera, direct, app->scene.cones[i]);
		if (between(length_min, INF, intersect_cone.distance) &&
			intersect_cone.distance < object.distance)
		{
			object.distance = intersect_cone.distance;
			object.hit_point = vec_add(camera, vector_mult_scal(direct, object.distance));
			object.center = app->scene.cones[i].center;
			normal_cone(app, &app->scene.cones[i], &object);
			object.color = app->scene.cones[i].color;
			object.specular = app->scene.cones[i].specular;
			object.flag = 1;
		}
	}
	if (object.distance < prev_object.distance)
		return (object);
	return (prev_object);
}
