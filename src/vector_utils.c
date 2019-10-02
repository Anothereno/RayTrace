#include "RTv1.h"

float 	vec_length(t_vector v)
{
	return (sqrtf(vec_dot(v, v)));
}

t_vector	vec_normalize(t_vector v)
{
	t_vector	new_v;
	float	length;

	length = vec_length(v);
	new_v.x = v.x / length;
	new_v.y = v.y / length;
	new_v.z = v.z / length;
	return (new_v);
}

float	vec_dot(t_vector v1, t_vector v2)
{
	return (v1.x * v2.x + v1.y * v2.y + v1.z * v2.z);
}

t_vector	vec_cross(t_vector v1, t_vector v2)
{
	t_vector	new_v;

	new_v.x = v1.y * v2.z - v1.z * v2.y;
	new_v.y = v1.z * v2.x - v1.x * v2.z;
	new_v.z = v1.x * v2.y - v1.y * v2.x;
	return (new_v);
}

t_vector	vec_invert(t_vector v)
{
	t_vector	new_v;

	new_v.x = -v.x;
	new_v.y = -v.y;
	new_v.z = -v.z;
	return (new_v);
}

void	vec_invert2(t_vector *v, t_vector *v2)
{
	v->x = -v2->x;
	v->y = -v2->y;
	v->z = -v2->z;
}
