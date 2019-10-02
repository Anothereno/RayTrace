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
# define RAD 0.0174533f
# define SCREEN_WIDTH 800
# define SCREEN_HEIGHT 600
# define CENTER_WIDTH (SCREEN_WIDTH / 2)
# define CENTER_HEIGHT (SCREEN_HEIGHT / 2)
# define AMOUNT_SPHERES 0
# define AMOUNT_CONES 0
# define AMOUNT_PLANES 0
# define AMOUNT_CYLINDERS 1
# define AMOUNT_LIGHTS 2

typedef struct s_vector
{
    double		x;
    double		y;
	double		z;
    double		distance;
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
	int				height;
	int				width;
}					t_sdl;

typedef struct s_camera
{
	t_vector		camera;
	t_vector		direct;
	double 			rotate_angle_y;
	double			camera_speed;
	double 			rotate_speed;
}				t_camera;

typedef struct s_color
{
    int				red;
    int				green;
    int				blue;
}				t_color;

typedef struct s_ligth
{
	char			type;
	double			intensity;
	t_vector		direct;
}				t_light;

typedef	struct		s_plane
{
	t_vector		center;
	t_vector		normal;
	int 			specular;
	t_color			color;
}					t_plane;

typedef struct s_sphere
{
    int 			mode;
    t_vector		center;
    double			radius;
    t_color			color;
    int				specular;
    double 			reflective;
}				t_sphere;

typedef struct	s_cone
{
	t_vector		center;
	double			height;
	double			radius;
	int				specular;
	t_color			color;
}					t_cone;

typedef struct	s_cylinder
{
	t_vector		center;
	double			height;
	double			radius;
	int				specular;
	t_color			color;
}				t_cylinder;

typedef struct	s_object
{
	int 		flag;
	char 		object_type;
	t_vector	center;
	t_color		color;
	int 		specular;
	double 		distance;
}				t_object;

typedef struct s_rotate
{
	double			x;
	double			y;
	double			z;
}				t_rotate;

typedef struct s_scene
{
    int				spheres_amount;
    int				planes_amount;
    int				cones_amount;
    int				cylinders_amount;
    int				cur_object;
	t_sphere		*spheres;
	t_cone			*cones;
	t_cylinder		*cylinders;
	t_plane			*planes;
	t_light			*lights;
	int				lights_amount;
	int				cur_light_control;
	int 			cur_obj_control;
	double			light_speed;
	t_rotate		rotate;
}               t_scene;

typedef struct	s_app
{
	t_sdl			*sdl;
	const Uint8		*keys;
	t_scene			scene;
	t_camera		camera;

}				t_app;

typedef struct s_sphere_intersect
{
	int				intersect_amount;
	double			first;
	double			second;
	t_sphere		intersected_object;
}				t_object_intersect;

t_object_intersect intersect_ray_sphere(t_vector camera, t_vector direct,
										t_sphere sphere);
void				initialize_sdl(t_app *app);
void				init(t_app *app);
int					event_handling(t_app *app);
void				set_pixel(SDL_Surface *surface, int x, int y, t_color c);
void				init_app(t_app *app);

t_color				raytrace(t_vector camera, t_vector direct,
								double length_min, double length_max, t_app *app);
t_vector 			set_vertex(double x, double y, double z);
double				vector_dot(t_vector first, t_vector second);
t_vector			vector_sub(t_vector first, t_vector second);
double 				vec_length(t_vector v);
t_vector			vec_normalize(t_vector v);
double				vec_dot(t_vector v1, t_vector v2);
t_vector			vec_cross(t_vector v1, t_vector v2);
t_vector			vec_add(t_vector v1, t_vector v2);
t_vector			vec_new(double x, double y, double z);
t_vector			vec_sub(t_vector v1, t_vector v2);
t_vector			vec_mul_by(t_vector v, double k);
t_vector			vec_div_by(t_vector v, double k);
t_vector			vector_mult_scal(t_vector first, double num);
t_vector			vec_invert(t_vector v);
t_sphere			new_sphere(t_vector center, double radius, t_color color, int specular);
t_cylinder			new_cylinder(t_vector center, double radius, t_color color, double height, int specular);
t_plane				new_plane(t_vector center, t_vector normal, t_color color, int specular);
t_cone				new_cone(t_vector center, double radius, t_color color, double height, int specular);
t_light				new_light(t_vector direct, double intensity, char type);


void			vec_invert2(t_vector *v, t_vector *v2);
void			vector_mult_scal2(t_vector *res,t_vector *first, double num);
t_vector		set_vertex2(double *x, double *y, double *z);
double vector_dot2(t_vector *first, t_vector *second);


t_vector			vec_point_at(t_vector ori, t_vector dir, double t);
double				clamp(int min, int max, int num);
t_color 			set_color(int red, int green, int blue);
void				start_the_game(t_app *app);
int					event_handling2(t_app *app);
double				vector_length(t_vector vector);
void				redraw(t_app *app);
t_sphere 			new_sphere(t_vector center, double radius, t_color color, int specular);
int					check_lights(const uint8_t *key, t_app *app);
int					check_camera(const uint8_t *key, t_app *app);
t_object_intersect	set_intersect(int amount, double first, double second);
int 				between(double min, double max, double num);
t_object			find_intersected_cones(t_app *app, t_vector camera, t_vector direct,
								   double length_min, double length_max, t_object prev_object);
t_object			find_intersected_cylinders(t_app *app, t_vector camera, t_vector direct,
									   double length_min, double length_max, t_object prev_object);
t_object			find_intersected_planes(t_app *app, t_vector camera, t_vector direct,
									double length_min, double length_max, t_object prev_object);
t_object			find_intersected_spheres(t_app *app, t_vector camera, t_vector direct,
									 double length_min, double length_max);
#endif
