/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   draw.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hdwarven <hdwarven@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/10/13 17:36:17 by hdwarven          #+#    #+#             */
/*   Updated: 2019/10/13 17:37:18 by hdwarven         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "rtv.h"

void	set_pixel(SDL_Surface *surface, int x, int y, t_color c)
{
	int				offset;
	unsigned char	*pixels;

	offset = 4 * (y * SCREEN_WIDTH + x);
	pixels = (unsigned char*)surface->pixels;
	pixels[offset] = c.blue;
	pixels[offset + 1] = c.green;
	pixels[offset + 2] = c.red;
}
