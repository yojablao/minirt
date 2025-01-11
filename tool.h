/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tool.h                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yojablao <yojablao@student.42.ma>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/25 20:42:12 by yojablao          #+#    #+#             */
/*   Updated: 2025/01/04 19:11:09 by yojablao         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef TOOL_H
#define TOOL_H


#include <fcntl.h>
#include <stdio.h>
#include <stdarg.h>
#include <math.h>
#include "parsing/get_next_line.h"

#include "minilibx_linux/mlx.h"

#define HIGTH 500
#define WITH 500

#define	EPSILON 0.00001
#define	π 3.1415926535
#define SPH 1
#define LAST_P 



// #define EPSILON 0.00001

typedef struct s_tuple	{
	double x;
	double y;
	double z;
	double w;
} 	t_tuple;

typedef struct s_color
{
    double r;
    double g;
    double b;

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
typedef struct s_draw
{
	int			mlx_x;
	int			mlx_y;
	int			color;
	float		x_ray;
	float		y_ray;
	float		z_ray;
	t_tuple	*ray;
}	t_draw;
typedef struct s_light
{
    t_tuple point;
    double r;
    t_color color;
    int bright;
    struct s_light *next;
    
}t_light;

typedef struct s_sphere
{
    t_tuple *center;
    double r;
    int id;
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

typedef struct mlx
{
	void*		mlx;
	void*		window;
	int		width;
	int		height;
	double		delta_time;
}	t_mlx;

typedef struct	s_data {
	void	*img;
	char	*addr;
	int		bits_per_pixel;
	int		line_length;
	int		endian;
}				t_data;
typedef struct s_objects
{
}t_objects;
typedef struct s_scene
{
    // t_objects  *obj;
    t_amlight   amligth;
    t_camera    *camera;
    t_light     *ligth;
    t_sphere    *sphere;
    t_plane     *plane;
    t_cylinder *cylinder;
    t_mlx   *mlx;
    int		width;
	int		height;
    t_data *img;
}t_scene;


////////math f{}/////
/* creat a point or a vector */
double	sq(double num);
t_tuple	*cpv(double x, double y, double z, double p_v);
/* checks if its a point or a vector if true(1) its point else its vector */
int ispoint(t_tuple *a);
/* checks if two floating point number are equal or not if true(1) are equal else not*/
int isequal(double a, double b);
/* add two floating point number */
double	add(double a, double b);
/* subtract two floating point number */
double	sub(double a, double b);
/* multiply two floating point number */
double	mul(double a, double b);
/* divide two floating point number */
double	divi(double a, double b);
/* operation between two tuples addition and subtraction */
t_tuple *tpl_o(t_tuple *a, t_tuple *b , char op);
/*get the opposite vector of a given one */
t_tuple *opp(t_tuple *a);
/*we use scalar for dividing or multiplying a vector by a number called scalar*/
t_tuple *scalar(t_tuple *a, double scalar);
/* calculer magnitude of a vector (or its lengh) */
double magnitude(t_tuple *a);
/* check if its a unit vector */
double	isunit(t_tuple *a);
/* normalization its nedded when we have an arbitry vector mean a vector that u have the choise where it will goes */
t_tuple *Normalize(t_tuple *a);
/* we use it to compare between two vector direction and knowing the angle between them */
double	Dot_p(t_tuple *a, t_tuple *b);
/* the result is a vector that its perpodicular to both of the two used vectors*/
t_tuple *Cross_p(t_tuple *a, t_tuple *b);
/* colors addition and subtraction and multiplication */
t_color *colors_operation(t_color *a, t_color *b, char op);
/* colors multiplication with a scalar */
t_color *color_s_mul(t_color *a, double scalar);
/* checks if two matrix are equals*/
int equal_mat(t_matrix *a, t_matrix *b);
/*multiplying two matrixs gives another matrix */
t_matrix	*mul_mat(t_matrix *a, t_matrix *b);
/* identity matrix multipliyng by any matrix it gives the same matrix */
t_matrix *i_mat(void);
/* multipling a matrix by  tuple creat another tuple */
t_tuple *tup_mat_mul(t_matrix *mtx, t_tuple *tpl);
/*transpose take a matrix and change its rows to collomns and its collomns to rows */
t_matrix *transpose(t_matrix *a);
/* get determinant of 2*2 matrix */
double det_2(t_2_2 *a);
/* submatrix 3*3 remove a collamn and a row from a  4*4 matrix */
t_3_3 *sub_m3(t_matrix *a, int row, int col);
/* submatrix 2*2 remove a collamn and a row from a 3*3 matrix */
t_2_2 *sub_m2(t_3_3 *a, int row, int col);
/* is the determinant of a 3*3 submatrix after removing a row and col */
double	ft_minor(t_3_3 *a, int row, int col);
/* get the cofactor sign depending on the case the row and col removed share in the matrix */
double cof_sign(int r, int c);
/* gettin the cofactor of the 3*3 matrix */
double cof_3(t_3_3 *a, int row , int col );
/*getting the determinant of the 3*3 matrix u have the choice to work with the cols o rows
u will get the same  result  */
double det_3(t_3_3 *a);
/* get cofactor of a matrix 4*4 */
double	cofactor(t_matrix *a, int row , int col);
/* get detirminant of a 4*4 matrix */
double determinant(t_matrix *a);
/*checks the matrix inverbility is it return 0 mean thats not invertible */
double invertible(t_matrix *a);
/* get the inverse of a matrix */
t_matrix *inverse(t_matrix *a);
/* get the translation matrix we need to translate a point */
t_matrix *transl_mat(double x, double y, double z);
/* get the scalling matrix */
t_matrix *scal_mat(double x, double y, double z);
/* change from degrees to radians */
double radians(double degrees);
/* translation of a point  */
t_tuple *transl(t_tuple *point, t_matrix *tr_mtx);
/* scall point */
t_tuple *scall(t_tuple *point, t_matrix *scal_mtx);
/* rotat a vector or a point to an axis x y or z */
t_matrix *rotat_matrix(double radians, char axis);
/* get teh skewiing (shearing ) matrix */
t_matrix *skew_mat(double *arr);
/* creat a ray wih an origine and a direction */
t_ray *ray(t_tuple *origine, t_tuple *direction);
/* shows how far the ray travels in (x distance) seconds  (Computing a point from a distance)*/
t_tuple *position(t_ray *ray, double distance);
/* creat a sphere with given enter and raduis */
t_sphere *spher(t_tuple *center, double raduis, int id);
/* check rays sphere intersection and fill the t_intersect struct with object type and object and intersection points */
t_intersect	*intersect(t_ray *ray, t_sphere *spher);
t_ray *transform(t_ray *t, t_matrix *mat);
/////init stuct/////

void	init_scene(t_scene *scene);
void init_camera(t_camera *cam,  float fov, float aspect_ratio);
t_scene *allocat_scene(t_scene *scene);
int minirt(char **av,t_scene * sc);
int parser(char *av,t_scene *sc);
//////camira
void calculate_camera(t_scene *mt);

//////end////
void	my_mlx_pixel_put(t_data *data, int x, int y, int color);
int check_file(char *s,int *fd);
int check_identifier(char *s);
double get_nb(char *s);
int len2d(char **a);
int fill_ambligth(t_amlight *al,char **s);
int sphere_handle(t_sphere **lt,char **s);
int cylinder_handle(t_cylinder **lt,char **s);
int Plane_handle(t_plane **lt,char **s);
int read_it(int fd, t_scene *scene);
int fill_struct(t_scene *scene,char **buffer,int type);
int ft_rang(double min,double num,double max);
int light_handle(t_light **lt,char **s);
int camera_handle(t_camera **c,char **s);
int ratio_check(char *s,double *i);
int get_colors(t_color *color,char *s);
int get_point(t_tuple *point,char *s);
int get_normalizer(t_tuple *vector,char *s);
int field_of_view(double *view,char *s);
int diameter_handle(double *dmeter,char *s);
void print_point(t_tuple l,t_color c);
int check_if_nb(char *s);
int	ft_isdigit(int c);
int	ft_atoi(const char *str);
char	**ft_split(char const *s, char c ,char c1);
int	ft_strncmp(const char *str1, const char *str2, size_t n);
#endif




