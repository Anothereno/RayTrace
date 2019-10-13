/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   events.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hdwarven <hdwarven@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/10/13 17:45:05 by hdwarven          #+#    #+#             */
/*   Updated: 2019/10/13 17:45:59 by hdwarven         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "RTv1.h"

int		event_handling(t_app *app)
{
	const uint8_t *key;

	key = app->sdl->keys;
	SDL_WaitEvent(&app->sdl->event);
	if (app->sdl->event.type == SDL_QUIT
			|| key[SDL_SCANCODE_ESCAPE])
		return (0);
	check_camera(key, app);
	check_lights(key, app);
	check_for_redraw(key, app);
	return (1);
}

void	ft_error(char *str)
{
	ft_putendl(str);
	exit(0);
}
