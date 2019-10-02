#include "RTv1.h"

t_vector	vec_new(double x, double y, double z)
{
	t_vector	new_v;

	new_v.x = x;
	new_v.y = y;
	new_v.z = z;
	return (new_v);
}

t_vector	vec_point_at(t_vector ori, t_vector dir, double t)
{
	return (vec_add(vec_mul_by(dir, t), ori));
}
