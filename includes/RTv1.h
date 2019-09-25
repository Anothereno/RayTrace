/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fractol.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hdwarven <hdwarven@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/04/30 19:03:11 by hdwarven          #+#    #+#             */
/*   Updated: 2019/09/25 17:52:51 by hdwarven         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef WOLF3D_H
# define WOLF3D_H

# include <math.h>
# include "../libft/libft.h"
# include <fcntl.h>
# include <stdlib.h>
# include <stdio.h>
# include <string.h>
# include <pthread.h>
# include <SDL.h>
//# include <SDL_ttf.h>
# define BLOCK_SIZE	64
# define RAD 0.0174533
# define SCREEN_WIDTH 640
# define SCREEN_HEIGHT 480
# define CENTER_WIDTH (SCREEN_WIDTH / 2)
# define CENTER_HEIGHT (SCREEN_HEIGHT / 2)

typedef struct s_vec
{
    float x;
    float y;
    float z;
}				t_vector;

typedef struct      s_ray
{
    t_vector        camera;
    t_vector        direct;
}                   t_ray;

typedef struct		s_sdl
{
    const Uint8		*keys;
    SDL_Event       event;
	SDL_Event		event_mouse;
	SDL_Window		*window;
	SDL_Surface		*surface;
	int				half_height;
	int				half_width;
	int				height;
	int				width;
}					t_sdl;

typedef struct	s_app
{
	t_sdl		*sdl;
	const Uint8 *keys;
}				t_app;
//typedef struct  s_sdl
//{
//    SDL_Event  event;
//    SDL_Event  event_mouse;
//    SDL_Window  *window;
//    SDL_Surface  *surface;
//    //t_timer   *timer;
//    int    half_height;
//    int    half_width;
//    int    height;
//    int    width;
//}     t_sdl;

//typedef struct s_app
//{
//    t_window   window;
//// t_image    screen;
//// t_timer    timer;
//// t_kb_keys_state  keyboard;
//// t_mouse_state  mouse;
//    t_coords   camera;
//// t_mat4x4   projection_mat;
//// t_mat4x4   rotation_mat_z;
//// t_mat4x4   rotation_mat_x;
//// t_vertex   rot;
//// t_mesh    cube;
//// float     speed;
//    t_sdl    *sdl;
//    t_inputs   *inputs;
//// t_rectangles_list *rect_list;
//}     t_app;

typedef struct s_color
{
	int red;
	int green;
	int blue;
}				t_color;

typedef struct s_sphere
{
	int 		mode;
	t_vector	center;
	float		radius;
	t_color		color;
}				t_sphere;



typedef struct s_sphere_intersect
{
	int intersect_amount;
	float first;
	float second;
}				t_sphere_intersect;

t_sphere_intersect intersect_ray_sphere(t_vector camera, t_vector direct,
                         t_sphere sphere);

void			initialize_sdl(t_app *app);
void			init(t_app *app);
int				event_handling(t_app *app);
void			set_pixel(SDL_Surface *surface, int x, int y, t_color c);
void			init_app(t_app *app);
void			start_the_game(t_app *app);
t_vector 		field_to_view(int x, int y);

t_color			raytrace(t_vector camera, t_vector directory,
                        int length_min, int length_max, t_sphere spheres[4]);
t_vector 		set_vertex(float x, float y, float z);

float vector_dot(t_vector first, t_vector second);
t_vector	vector_sub(t_vector first, t_vector second);

float 	vec_length(t_vector v);
t_vector	vec_normalize(t_vector v);
float	vec_dot(t_vector v1, t_vector v2);
t_vector	vec_cross(t_vector v1, t_vector v2);
t_vector	vec_add(t_vector v1, t_vector v2);
t_vector	vec_new(float x, float y, float z);
t_vector	vec_sub(t_vector v1, t_vector v2);
t_vector	vec_mul_by(t_vector v, float k);
t_vector	vec_div_by(t_vector v, float k);
t_vector	vec_invert(t_vector v);
t_vector	vec_point_at(t_vector ori, t_vector dir, float t);


t_color set_color(int red, int green, int blue);
#endif
