/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pars.h                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yojablao <yojablao@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025-02-02 11:12:32 by yojablao          #+#    #+#             */
/*   Updated: 2025-02-02 11:12:32 by yojablao         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */
#ifndef PARS__H
#define PARS__H

#include <fcntl.h>
#include <stdio.h>
#include <stdarg.h>
#include <math.h>
#include "parsing/get_next_line.h"


//////structs////
typedef struct s_tuple	{
	double x;
	double y;
	double z;
	double w;
} 	t_tuple;

typedef struct s_color
{
    int r;
    int g;
    int b;

}t_color;

typedef struct s_matrix{
	double matrix[4][4];
}	t_matrix;

typedef struct s_2_2{
	double matrix[2][2];
}	t_2_2;

typedef struct s_3_3{
	double matrix[3][3];
}	t_3_3;

typedef struct s_ray
{
	t_tuple *o;
	t_tuple *d;
	t_tuple *ud;
}	t_ray;


typedef struct s_amlight
{
    double r;
    t_color color;
    
}t_amlight;

typedef struct s_camera
{
    t_ray *cam_ray;
    double aspect_ratio;
	double win_hight;
	double win_width;
    double fov;
    t_tuple  *u;
    t_tuple  *r;
    t_tuple	*fw;
}t_camera;
// typedef struct s_camera
// {
// 	t_vector	origin;
// 	t_vector	direction;
// 	int			fov;
// 	t_vector	up_v;
// 	t_vector	right_u;

// }	t_camera;
typedef struct s_pixels
{
	int			win_x;
	int			win_y;
	int			color;
	float		x_ray;
	float		y_ray;
	float		z_ray;
	t_tuple	*ray;
}	t_pixels;
typedef struct s_light
{
    t_tuple point;
    double r;
    t_color color;
    // int bright;
    struct s_light *next;
    
}t_light;

typedef struct s_sphere
{
	struct s_sphere *head;
	int is_head;
    t_tuple *center;
    double r;
    double id;
    double diameter;
    t_matrix *transform;
    t_color color;
    struct s_sphere *next;
}t_sphere;

typedef struct s_plane
{
    t_tuple point;
    t_tuple vector;
    t_color color;
    struct s_plane *next;
}t_plane;

typedef struct s_intersect
{
	t_ray *ray;
	void *object;
	double t;
}  t_intersect;

typedef struct s_cylinder
{
    t_tuple center;
    t_tuple vector;
    double diameter;
    double height;
    t_color color;
    struct s_cylinder *next;
}t_cylinder;

typedef struct	s_data {
	void	*img;
	char	*addr;
	int		bits_per_pixel;
	int		line_length;
	int		endian;
}				t_data;
typedef struct mlx
{
	void*		mlx;
	void*		window;
	t_data *img;
	int		width;
	int		height;
	double		delta_time;
}	t_mlx;


typedef struct s_dist
{
	float		dist;
	float		min_dist;
	size_t		closest_obj;
	t_sphere	*cl_sp;
	t_plane		*cl_pl;
	// t_cylinder	*cl_cy;
	t_tuple	*dot_light;
}	t_dist;

typedef struct s_objects
{
}t_objects;
typedef struct s_scene
{
    // t_objects  *obj;
    t_amlight   amligth;
    t_camera    camera;
    t_light     *ligth;
    t_sphere    *sphere;
    t_plane     *plane;
    t_cylinder *cylinder;
    t_mlx   mlx;
    int		width;
	int		height;
    
}t_scene;
////
void	init_scene(t_scene *scene);
// void init_camera(t_camera *cam,  float fov, float aspect_ratio);
t_scene *allocat_scene(t_scene *scene);
// int minirt(char **av,t_scene ** sc);
int parser(char *av,t_scene **sc);
//////camira
// void calculate_camera(t_scene *mt);
void print_all_cylinders(t_scene *scene);
//////end////
// void	my_mlx_pixel_put(t_data *data, int x, int y, int color);
char	**f_split(char const *s, char c ,char c1);
void	*master(size_t size, int flag);
void fre2d(void **arr);
int check_file(char *s,int *fd);
int check_identifier(char *s);
double get_nb(char *s);
int len2d(char **a);
int fill_ambligth(t_amlight *al,char **s);
int sphere_handle(t_sphere **lt,char **s);
int cylinder_handle(t_cylinder **lt,char **s);
int Plane_handle(t_plane **lt,char **s);
int read_it(int fd, t_scene **scene);
int fill_struct(t_scene **scene,char **buffer,int type);
int ft_rang(double min,double num,double max);
int light_handle(t_light **lt,char **s);
int camera_handle(t_camera *c,char **s);
int ratio_check(char *s,double *i);
int get_colors(t_color *color,char *s);
int get_point(t_tuple *point,char *s);
int get_normalizer(t_tuple *vector,char *s);
int field_of_view(double *view,char *s);
int diameter_handle(double *dmeter,char *s);
float	ft_comp_float(float f1, float f2) ;
// void print_point(t_tuple l,t_color c);
int check_if_nb(char *s);
int	ft_isdigit(int c);
int	ft_atoi(const char *str);
char	**ft_split(char const *s, char c ,char c1);
int	ft_strncmp(const char *str1, const char *str2, size_t n);

void print_light(t_light *light);
void print_tuple(const char *name, const t_tuple *tuple);
void print_ray(const t_ray *ray);
void print_camera(const t_camera *camera);
void print_sphere(t_sphere *sphere);

#endif