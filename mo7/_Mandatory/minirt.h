/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minirt.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mthamir <mthamir@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/28 15:23:22 by mthamir           #+#    #+#             */
/*   Updated: 2025/02/16 12:24:54 by mthamir          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINIRT_BONUS_H
#define MINIRT_BONUS_H

#include <unistd.h>
#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <stdarg.h>
#include <stdbool.h>
#include <fcntl.h>
#include "../MLX42/include/MLX42/MLX42.h"


#define	EPSILON 0.00001
#define SPHER 1
#define PLANE 2
#define CYLINDER 3
#define BLACK 0x0000000FF
#define FREE 10


#define RT_FILE_EXTENSION "The Programme Support Only rt Files"
#define VALID_NAME "Enter a Valid File_Name"
#define OPEN_FAILS "Can't Open File"
#define DUPLICAT_CAM "Camera Can Only Be Declared Once"
#define BAD_INFORM_CAM "Camera Bad Number Of Param"
#define BAD_INFORM_OBJ "Object Bad Number Of Param"
#define DUPLICAT_LIGHT "Light Can Only Be Declared Once"
#define BAD_INFORM_LIGHT "Light Bad Bad Number Of Param"
#define DUPLICAT_AMB "Ambiant Can Only Be Declared Once"
#define BAD_INFORM_AMB "Ambiant Bad Number Of Param"
#define INVALID_CORD "Invalid Cord In File"
#define INVALID_FLOATING_NUM "Invalid Number In File"
#define INVALID_FOV "Invalid FOV"
#define INVALID_AMB_R "Invalid Ambiant Ratio"
#define INVALID_SPHERE_RD "Invalid Spher Raduis"
#define INVALID_PL_NORMAL "Invalid Plane Normal"
#define INVALID_CYL_DATA "Invalid Cylinder Data"
#define MALLOC_FAILS "Malloc Syscall Fails"
#define INDEFINED_OBJECT "Uknown Identifier"

/* for collecting leaks */

#define BLOCK_SIZE 100000000000
#define INIT 22

typedef struct s_pool t_pool;
typedef struct s_pool
{
	void *block;
	size_t offset;
}	t_pool;
/*___________________________________________________________________________________*/


/* for reading lines from the file map */

typedef struct s_line{
	char *line[200];
	int count;
}	t_line ;

/*___________________________________________________________________________________*/

/* colors  */
typedef struct s_color	{
	double r;
	double g;
	double b;
}	t_color;

/*___________________________________________________________________________________*/

typedef struct s_material
{
	t_color color;
	double ambiant;
	double diffuse;
}	t_material;


typedef struct s_tuple	{
	double x;
	double y;
	double z;
	double w;
} 	t_tuple;

typedef struct s_light
{
	t_tuple position;
	t_color color;
}	t_light;


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
	t_tuple o;
	t_tuple d;
}	t_ray;

typedef struct s_spher
{
	double	r;
	int		id;
	t_matrix *transform;
	t_tuple	*c;
	t_color color;
	t_material *material;
	t_matrix *inverse_m;
	t_matrix *transpose_in;

}	t_spher;

typedef struct s_plane
{
	int		id;
	t_tuple	*c;
	t_color color;
	t_material *material;
	t_matrix *transform;
	t_matrix *inverse_m;
	t_matrix *transpose_inverse;
	t_tuple *normalv;
}	t_plane;

typedef struct s_cylinder
{
	int		id;
	t_tuple *centre;
	double min;
	double max;
	t_color color;
	t_material *material;
	t_matrix *transform;
	t_matrix *inverse_m;
	t_matrix *transpose_inverse;
}	t_cylinder;

typedef struct s_object
{
	int type;
	t_spher shape;
	t_plane shape_pl;
	t_cylinder shape_cyl;
} t_object;

typedef struct s_intersect t_intersect;
typedef struct s_intersect
{
	t_ray *ray;
	t_object object;
	double t[2];
	t_intersect *next;
}  t_intersect;

typedef struct s_camera
{
	t_ray *cam_ray;
	void *mlx;
	double pixel_size;
	double half_width;
	double half_hight;
	double field_of_view;
	double aspect_ratio;
	double horizontal_size;
	double vertical_size;
	t_tuple *origine;
	t_matrix *transform;
	t_matrix *transform_inverse;
}			t_camera;

typedef struct s_lighting
{
	t_material *material;
	t_tuple *point;
	t_light *light;
	t_camera *camera;
	t_tuple *normal_vec;
}	t_lighting;


typedef struct s_world
{
	int object_count;
	t_light *light;
	t_object object[200];
	t_color *ambiant_color;
}	t_world;

typedef struct s_comps
{
	double t;
	t_object object;
	t_tuple *point;
	bool shadow;
	t_tuple *eyev;
	t_tuple *normalv;
	bool inside;
}	t_comps;

typedef struct s_rt
{
	t_world *world;
	t_camera *cam;

}	t_rt;
/*______________________________parse_____________________________*/
char	*ft_copy(char *s1, char *s2, int i);
int ft_strstrlen(char **str);
int  is_float(char *s);
char	**split_line(char *s, char c, char c1);
char	*get_next_line(int fd);
bool ft_strcmp(char *s1, char *s2);
size_t	ft_strlen(const char *str);
char	*ft_strdup(char *s);
char	*ft_strjoin(char *s1, char *s2);
double char_to_double(char *s);
void parse_init_structs(t_line *l, t_rt *rt);
void	init_struct(char **line, t_rt *rt);
void init_objects(char **line, t_rt *rt, int num_obj);
void	init_plane(char **line, t_rt *rt, int id);
t_matrix *get_rotat_matrice(t_tuple *normal);
void init_spher(char **line, t_rt *rt, int id);
void init_light(char **line, int exist ,t_rt *rt);
void init_ambiant(char **line,int exist,t_rt *rt);
t_color *char_to_color(char *s);
void init_camera(char **line, int exist, t_rt *rt);
t_tuple *char_to_vec(char *cam_line, int type);
t_line 	*parse_file(char *file_name);
t_line *get_rt_lines(int fd);
bool check_extension(char *file_name);
void print_error(char *error);
void init_cylinder(char **line, t_rt *rt, int id);
int all_spaces(char *s);
void ft_memset(void *block_part,int  size);



/*______________________________exec_____________________________*/
/* creat a point or a vector */
t_tuple	*cpv(double x, double y, double z, double p_v);
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
t_tuple *tpl_o(t_tuple a, t_tuple b , double (*f)(double p1, double p2));
/*get the opposite vector of a given one */
void opp(t_tuple *a);
/*we use scalar for dividing or multiplying a vector by a number called scalar*/
t_tuple *scalar(t_tuple a, double scalar);
/* calculer magnitude of a vector (or its lengh) */
double magnitude(t_tuple a);
/* normalization its nedded when we have an arbitry vector mean a vector that u have the choise where it will goes */
void normalize(t_tuple *a);
/* we use it to compare between two vector direction and knowing the angle between them */
double	dot_p(t_tuple a, t_tuple b);
/* the result is a vector that its perpodicular to both of the two used vectors*/
t_tuple *cross_p(t_tuple a, t_tuple b);
/* get squar of a number */
double	sq(double num);
/* colors multiplication with a scalar */
t_color *color_s_mul(t_color *a, double scalar);
/* checks if two matrix are equals*/
int equal_mat(t_matrix *a, t_matrix *b);
/*multiplying two matrixs gives another matrix */
t_matrix	*mul_mat(t_matrix *a, t_matrix *b);
/* identity matrix multipliyng by any matrix it gives the same matrix */
t_matrix *i_mat(double diagonal);
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
t_ray *ray(t_tuple origine, t_tuple direction);
/* shows how far the ray travels in (x distance) seconds  (Computing a point from a distance)*/
t_tuple *position(t_ray *ray, double distance);
/* creat a sphere with given enter and raduis */
t_spher *spher(t_tuple *center, double raduis, int id, t_matrix *tr);
/* check rays sphere intersection and fill the t_intersect struct with object type and object and intersection points */
t_intersect	*intersect(t_ray *ray, t_spher *spher);
t_ray *transform(t_ray *t, t_matrix *mat);
/* get the normal vector on a point on the spher*/
t_tuple *normal_at(t_spher *sph, t_tuple *point);
/* colors addition and subtraction */
t_color *colors_operation(t_color *a, t_color *b, double (*f) (double a, double b));
/* colors multiplication with a scalar */
t_color *color_s_mul(t_color *a, double scalar);
/* get diffuse and ambiant color ona apoint */
t_color *compute_lightning(t_material *m, t_light *light, t_tuple *pos, t_tuple *normalv);
void *ft_malloc(size_t size, int flag);
double hit(double *arr);
t_light *light_source(t_tuple *position, t_color *color);
t_tuple *reflect(t_tuple in, t_tuple normal);
double get_closest(double *t);
t_material *material();
t_color *new_color(double r, double g, double b);
uint64_t get_col(t_color * color);
t_color *to_rgba(double color);
t_world *world();
t_intersect *new_intersect();
t_intersect *world_intersection(t_world *world, t_ray *r);
t_comps *new_comps();
t_comps	*prepare_computing(t_intersect *list, t_ray *r, t_world *w);
t_color *shade_hit(t_world *w, t_comps *comp);
t_color *color_at(t_world *w, t_ray *r);
t_matrix *view_transformation(t_tuple *from, t_tuple *to, t_tuple *up);
t_ray *ray_for_pixel(t_camera *cam, double x, double y);
t_camera *new_camera(double hsize, double vsize, double fov, t_matrix *transformation);
void render(t_rt *rt);
t_intersect *get_first_intersect(t_intersect *list, t_ray *r);
t_intersect *pl_intersect(t_ray *r1, t_plane *pl);
t_plane *plane(int id, t_matrix *tr);
t_tuple *normal_at_cyl(t_cylinder *cyl, t_tuple *p);
t_intersect *cyl_intersect(t_ray *r, t_cylinder *cyl);
t_cylinder *cylinder(double trunc[2], int id, t_matrix *tr);
t_material *material();
void intersect_caps_cyl(t_cylinder *cyl, t_ray *r, double *t1, double *t2);
void ch_pv(t_tuple *a, double x, double y, double z);
#endif

/*  ambiant reflection   
	
							I ambiant 
								= 
		ambiant cofficient of the surface (material properity)
									 X 
		I brghitness of the ambiant light in the scene 
*/

/*  diffuse reflection 

					I diffuse
						=
		diffuse cofficient (material properity )
						X
		I intensity of the light source 
						X
		DOT PRODUCT (N normal vector of surface  X  L light direction vector )
		(N . L) the dot product between the normal vector and the light direction ,
		which gives the cosin of the ongle between them ;
*/

/*		Specular reflection 

					I specular
						=
		specular reflection cofficient (material prepority )
						X
		the intensity of the light source
						X
		POW (DOT PRODUCT (R the reflection vector  X  V the view (camera ) direction vector ))) n
		POW ((R . V), n)  dot product betwene the reflection vector and the view direction, 
		raised to the power of n the PHONG EXPENONT , wich control the the sharpness of the specular highlight ;


*/


/*       THE PHONG REFLECTION EQUATION 

		I total = Iambiant + I diffuse + I specular;
		

*/


/*

Vanishing Points: no9tat talashi 
Field of View (FOV) : zawiya ro2ya gedma kabret katzad ro2ya 7edha 180;

*/