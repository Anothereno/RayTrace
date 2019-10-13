#include "RTv1.h"

t_vector set_vector(double x, double y, double z)
{
	t_vector res;

	res.x = x;
	res.y = y;
	res.z = z;
	return (res);
}

t_vector	vector_add(t_vector first, t_vector second)
{
	t_vector res;

	res.x = first.x + second.x;
	res.y = first.y + second.y;
	res.z = first.z + second.z;
	return (res);
}

t_vector	vector_sub(t_vector first, t_vector second)
{
	t_vector res;

	res.x = first.x - second.x;
	res.y = first.y - second.y;
	res.z = first.z - second.z;
	return (res);
}

t_vector	normalize(t_vector v)
{
	t_vector	new_v;
	double	length;

	length = vector_length(v);
	new_v.x = v.x / length;
	new_v.y = v.y / length;
	new_v.z = v.z / length;
	return (new_v);
}

t_vector	vector_invert(t_vector v)
{
	t_vector	new_v;

	new_v.x = -v.x;
	new_v.y = -v.y;
	new_v.z = -v.z;
	return (new_v);
}

t_vector	vector_mult_scal(t_vector first, double num)
{
	t_vector res;

	res.x = first.x * num;
	res.y = first.y * num;
	res.z = first.z * num;
	return (res);
}

double vector_dot(t_vector first, t_vector second)
{
	return (first.x * second.x + first.y * second.y + first.z * second.z);
}

double	vector_length(t_vector vector)
{
	return (sqrt(vector_dot(vector, vector)));
}
