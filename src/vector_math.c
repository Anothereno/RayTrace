#include "RTv1.h"

t_vector	vec_add(t_vector v1, t_vector v2)
{
	t_vector	new_v;

	new_v.x = v1.x + v2.x;
	new_v.y = v1.y + v2.y;
	new_v.z = v1.z + v2.z;
	return	(new_v);
}

t_vector	vec_sub(t_vector v1, t_vector v2)
{
	t_vector	new_v;

	new_v.x = v1.x - v2.x;
	new_v.y = v1.y - v2.y;
	new_v.z = v1.z - v2.z;
	return	(new_v);
}

t_vector	vec_mul_by(t_vector v, float k)
{
	t_vector	new_v;

	new_v.x = v.x * k;
	new_v.y = v.y * k;
	new_v.z = v.z * k;
	return	(new_v);
}

t_vector	vec_div_by(t_vector v, float k)
{
	t_vector	new_v;

	new_v.x = v.x / k;
	new_v.y = v.y / k;
	new_v.z = v.z / k;
	return	(new_v);
}
