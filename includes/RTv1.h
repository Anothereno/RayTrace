#ifndef WOLF3D_H
# define WOLF3D_H

# include <math.h>
# include "../libft/libft.h"
# include <fcntl.h>
# include <stdlib.h>
# include <stdio.h>
# include <string.h>
# include <pthread.h>
# include "../libft/get_next_line.h"
# include <SDL.h>
//# include <SDL_ttf.h>
# define RAD 0.0174533f
# define SCREEN_WIDTH 400
# define SCREEN_HEIGHT 400
# define MAX(a, b) a > b ? a : b
# define MIN(a, b) a > b ? b : a
# define INF 9999999
# define THREAD_AMOUNT 200


typedef enum e_types
{
	sphere,
	cone,
	plane,
	cylinder,
	light
}			t_types;

typedef struct	s_vector
{
    double		x;
    double		y;
	double		z;
    double		distance;
}				t_vector;


typedef struct      s_intersect
{
	t_vector		oc;
	double			a;
	double			b;
	double			c;
	double			delta;
}                   t_intersect;

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
	double 			rotate_angle_x;
	double 			rotate_angle_z;
	double			camera_speed;
	double 			rotate_speed;
}				t_camera;

typedef struct s_color
{
    int				red;
    int				green;
    int				blue;
}				t_color;

typedef struct	s_ligth
{
	double		intensity;
	t_vector	position;
}				t_light;

typedef	struct		s_plane
{
	t_vector		center;
	t_vector		normal;
	int 			specular;
	float 			diffuse;
	t_color			color;
}					t_plane;

typedef struct	s_sphere
{
    int 		mode;
    t_vector	center;
    double		radius;
	float 		diffuse;
	t_color		color;
    int			specular;
    double 		reflective;
}				t_sphere;

typedef struct	s_cone
{
	t_vector		center;
	double			height;
	t_vector		axis;
	float 			diffuse;
	double 			angle;
	int				specular;
	t_color			color;
}					t_cone;

typedef struct	s_cylinder
{
	t_vector		center;
	t_vector		axis;
	double			height;
	float 			diffuse;
	double			radius;
	int				specular;
	t_color			color;
}				t_cylinder;

typedef struct	s_object
{
	int 		flag;
	char 		object_type;
	t_vector	center;
	t_vector	axis;
	t_color		color;
	double 		specular;
	double 		distance;
	t_vector	normal;
	t_vector	hit_point;
	double		light_intensity;
	double		diffuse;
}				t_object;

typedef struct s_rotate
{
	double		x;
	double		y;
	double		z;
}				t_rotate;

typedef struct	s_scene
{
	char 		cur_obj_type;
    int			spheres_amount;
    int			planes_amount;
    int			cones_amount;
    int			cylinders_amount;
    int 		cameras_amount;
    int			cur_sphere;
    int			cur_plane;
    int			cur_cone;
    int			cur_cylinder;
    int 		cur_camera;
    int			cur_object;
	t_sphere	*spheres;
	t_cone		*cones;
	t_cylinder	*cylinders;
	t_plane		*planes;
	t_light		*lights;
	int			lights_amount;
	int			cur_light;
	int			cur_light_control;
	int 		cur_obj_control;
	double		light_speed;
	t_rotate	rotate;
}               t_scene;

typedef struct	s_app
{
	t_sdl			*sdl;
	const Uint8		*keys;
	t_scene			scene;
	t_camera		camera;
	char			*cur_scene;
	int 			number_scene;
	pthread_mutex_t locker;
	t_color			black;
	t_color			white;
}				t_app;

typedef struct		s_thread
{
	int				id;
	int				y_start;
	int				x_start;
	int 			x_finish;
	pthread_t		pthread;
	int				y_finish;
	t_app			*app;
}					t_thread;

typedef struct s_sphere_intersect
{
	double 			distance;
}				t_object_intersect;

t_vector rotation_y(t_camera *camera, t_vector viewport);
t_vector to_viewport(int x, int y);
t_color				color_randomize();
void				read_file_write_obj(t_app *app, char** argv);
double				intersect_ray_sphere(t_vector camera, t_vector direct, t_sphere sphere);
void				initialize_sdl(t_app *app);
void				init(t_app *app);
void set_pixel(SDL_Surface *surface, int x, int y, t_color c);
void				init_app(t_app *app);

void				init_objects(t_scene *scene);
void				read_file_count_obj(t_app *app, char** argv);
void				ft_error(char *str);
void raytrace(t_app *app, int x, int y);
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
t_sphere new_sphere(t_vector center, double radius);
t_cylinder new_cylinder(t_vector center, double radius, t_vector rot);
t_plane new_plane(t_vector center, t_vector normal);
t_cone new_cone(t_vector center, double angle, t_vector rot);
t_light				new_light(t_vector direct, double intensity);


void				vec_invert2(t_vector *v, t_vector *v2);
void				vector_mult_scal2(t_vector *res,t_vector *first, double num);
t_vector			set_vertex2(double *x, double *y, double *z);
double				vector_dot2(t_vector *first, t_vector *second);

t_color				pallete(t_color color, double num);
t_vector			vec_point_at(t_vector ori, t_vector dir, double t);
double				clamp(int min, int max, int num);
t_color 			set_color(int red, int green, int blue);
void				start_the_game(t_app *app);
int					event_handling(t_app *app);
double				vector_length(t_vector vector);
void				redraw(t_app *app);

void				set_axis(t_vector *axis, t_vector rot);
t_sphere new_sphere(t_vector center, double radius);
void				check_lights(const uint8_t *key, t_app *app);
void				check_camera(const uint8_t *key, t_app *app);
double				set_intersect(double first, double second);
int 				between(double min, double max, double num);
t_object			find_intersected_cones(t_app *app, t_vector camera, t_vector direct, double length_min, t_object prev_object);
t_object			find_intersected_cylinders(t_app *app, t_vector camera, t_vector direct, double length_min, t_object prev_object);
t_object			find_intersected_planes(t_app *app, t_vector camera, t_vector direct,  t_object prev_object);
t_object			find_intersected_spheres(t_app *app, t_vector camera, t_vector direct, double length_min);
int					map_read(int fd, t_app *app);
void				set_pixel2(t_app *app, int x, int y, t_color c);
t_color				to_hsv(int rand_num);
void				sum_color(t_color *first, t_color *second);
void				check_for_redraw(const uint8_t *key, t_app *app);



#endif
