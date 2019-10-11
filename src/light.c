#include "RTv1.h"

t_light		new_light(t_vector direct, double intensity)
{
	t_light res;

	res.intensity = intensity;
	res.position = direct;
	return res;
}

