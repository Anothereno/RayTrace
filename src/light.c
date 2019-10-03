#include "RTv1.h"

t_light		new_light(t_vector direct, double intensity, char type)
{
	t_light res;

	res.intensity = intensity;
	res.direct = direct;
	res.type = type;
	return res;
}

