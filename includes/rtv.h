/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   rtv.h                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hdwarven <hdwarven@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/10/13 19:55:35 by hdwarven          #+#    #+#             */
/*   Updated: 2019/10/16 19:38:27 by hdwarven         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef RTV_H
# define RTV_H

# include <math.h>
# include "../libft/libft.h"
# include <fcntl.h>
# include <stdlib.h>
# include <string.h>
# include <pthread.h>
# include <SDL.h>
# define RAD 0.0174533f
# define SCREEN_WIDTH 400
# define SCREEN_HEIGHT 400
# define MAX(a, b) a > b ? a : b
# define MIN(a, b) a > b ? b : a
# define INF 9999999
# define THREAD_AMOUNT 200
# define POWTWO(a) (a * a)
# define M_PI_180  0.017453292519943295

typedef struct		s_vector
{
	double	x;
	double	y;
	double	z;
	double	distance;
}					t_vector;

typedef struct		s_sdl
{
	const Uint8		*keys;
	SDL_Event		event;
	SDL_Window		*window;
	SDL_Surface		*surface;
}					t_sdl;

typedef struct		s_camera
{
	t_vector		position;
	t_vector		direct;
	t_vector		rotation;
	double			camera_speed;
	double			rotate_speed;
}					t_camera;

typedef struct		s_color
{
	int	red;
	int	green;
	int	blue;
}					t_color;

typedef struct		s_ligth
{
	double		intensity;
	t_vector	position;
}					t_light;

typedef	struct		s_plane
{
	t_vector		center;
	t_vector		normal;
	int				specular;
	t_color			color;
}					t_plane;

typedef struct		s_sphere
{
	t_vector	center;
	double		radius;
	t_color		color;
	int			specular;
}					t_sphere;

typedef struct		s_cone
{
	t_vector		center;
	t_vector		axis;
	double			angle;
	int				specular;
	t_color			color;
}					t_cone;

typedef struct		s_cylinder
{
	t_vector		center;
	t_vector		axis;
	double			radius;
	int				specular;
	t_color			color;
}					t_cylinder;

typedef struct		s_object
{
	int			flag;
	t_vector	center;
	t_color		color;
	double		specular;
	double		distance;
	t_vector	normal;
	t_vector	hit_point;
	double		diffuse;
}					t_object;

typedef struct		s_scene
{
	int			spheres_amount;
	int			planes_amount;
	int			cones_amount;
	int			cylinders_amount;
	int			cameras_amount;
	int			cur_sphere;
	int			cur_plane;
	int			cur_cone;
	int			cur_cylinder;
	int			cur_camera;
	t_sphere	*spheres;
	t_cone		*cones;
	t_cylinder	*cylinders;
	t_plane		*planes;
	t_light		*lights;
	int			lights_amount;
	int			cur_light;
	int			cur_light_control;
	double		light_speed;
}					t_scene;

typedef struct		s_app
{
	t_sdl			*sdl;
	t_scene			scene;
	t_camera		camera;
	t_color			black;
	t_color			white;
}					t_app;

typedef struct		s_light_spot
{
	t_vector	light_direct;
	double		light_distance;
}					t_light_spot;

typedef struct		s_abc
{
	double a;
	double b;
	double c;
}					t_abc;

typedef struct		s_thread
{
	int				y_start;
	pthread_t		pthread;
	int				y_finish;
	t_app			*app;
}					t_thread;

void				quit(t_app *app);
void				create_light(t_app *app, char **string);
void				create_cylinder(t_app *app, char **string);
void				create_cone(t_app *app, char **string);
void				create_plane(t_app *app, char **string);
void				create_sphere(t_app *app, char **string);
t_vector			reflective(t_vector vector, t_vector normal);
void				light_calculate(t_app *app, t_object *object,
						t_camera *camera);
void				set_spot(t_light_spot *spot,
						t_object *object, int i, t_app *app);
void				set_camera(t_app *app, t_vector position,
						t_vector rotation);
void				view_direction(t_vector *axis, t_vector rot);
t_vector			to_viewport(t_app *app, int x, int y);
t_color				color_randomize();
void				read_file_write_obj(t_app *app, char **argv);
double				intersect_ray_sphere(t_vector camera,
						t_vector direct, t_sphere sphere);
void				init_app(t_app *app);
void				init_objects(t_scene *scene);
void				read_file_count_obj(t_app *app, char **argv);
void				ft_error(char *str, t_app *app);
void				raytrace(t_app *app, int x, int y);
t_vector			set_vector(double x, double y, double z);
double				vector_dot(t_vector first, t_vector second);
t_vector			vector_sub(t_vector first, t_vector second);
t_vector			vector_add(t_vector first, t_vector second);
t_vector			vector_mult_scal(t_vector first, double num);
t_vector			normalize(t_vector v);
t_sphere			new_sphere(t_app *app, t_vector center, double radius);
t_cylinder			new_cylinder(t_app *app, t_vector center,
						double radius, t_vector rot);
t_plane				new_plane(t_app *app, t_vector center,
						t_vector normal);
t_cone				new_cone(t_app *app, t_vector center,
						double angle, t_vector rot);
t_light				new_light(t_app *app, t_vector direct, double intensity);
t_vector			vector_invert(t_vector v);
t_color				pallete(t_color color, double num);
double				clamp(int min, int max, int num);
t_color				set_color(int red, int green, int blue);
void				start_the_game(t_app *app);
int					event_handling(t_app *app);
double				vector_length(t_vector vector);
void				redraw(t_app *app);
void				set_axis(t_vector *axis, t_vector rot);
void				check_lights(const uint8_t *key, t_app *app);
double				set_intersect(double first, double second);
int					between(double min, double max, double num);
t_object			find_intersected_cones(t_app *app,
						double length_min, t_object prev_object,
						t_camera *camera);
t_object			find_intersected_cylinders(t_app *app,
						double length_min, t_object prev_object,
						t_camera *camera);
t_object			find_intersected_planes(t_app *app,
						t_object prev_object, t_camera *camera);
t_object			find_intersected_spheres(t_app *app,
						double length_min, t_camera *camera);
t_color				to_hsv(int rand_num);
void				sum_color(t_color *first, t_color *second);
void				check_for_redraw(const uint8_t *key, t_app *app);
void				set_pixel(SDL_Surface *surface, int x, int y, t_color *c);

#endif
