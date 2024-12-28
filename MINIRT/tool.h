/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tool.h                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yojablao <yojablao@student.42.ma>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/25 20:42:12 by yojablao          #+#    #+#             */
/*   Updated: 2024/12/25 20:42:13 by yojablao         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef TOOL_H
#define TOOL_H

#include <libc.h>
#include <math.h>
#include "includes/get_next_line.h"
#include "includes/lib/libft.h"
// #include <b.h/>
#define EPSILON 0.00001

typedef struct s_color
{
    double r;
    double g;
    double b;

}t_color;
typedef struct s_point
{
    double x;
    double y;
    double z;
}t_point;


typedef struct s_tuple
{
    t_point p;
    double w;
}t_tuple;

typedef struct s_amlight
{
    double ratio;
    t_color color;
    
}t_amlight;

typedef struct s_camera
{
    t_point point;
    t_point vector;
    double viewdegrees;
}t_camera;

typedef struct s_light
{
    t_point point;
    double ratio;
    t_color color;
    struct s_light *next;
    
}t_light;

typedef struct s_sphere
{
    t_point center;
    double diameter;
    t_color color;
    struct s_sphere *next;
}t_sphere;

typedef struct s_plane
{
    t_point point;
    t_point vector;
    t_color color;
    struct s_plane *next;
}t_plane;

typedef struct s_cylinder
{
    t_point center;
    t_point vector;
    double diameter;
    double height;
    t_color color;
    struct s_cylinder *next;
}t_cylinder;

typedef struct s_scene
{
    t_amlight   *amligth;
    t_camera    *camera;
    t_light     *ligth;
    t_sphere    *sphere;
    t_plane     *plane;
    t_cylinder *cylinder;
}t_scene;

int check_file(char *s,int *fd);
int check_identifier(char *s);
double get_nb(char *s);
int len2d(char **a);
int fill_ambligth(t_amlight **al,char **s);
int sphere_handle(t_sphere **lt,char **s);
int cylinder_handle(t_cylinder **lt,char **s);
int Plane_handle(t_plane **lt,char **s);
t_scene *read_it(int fd);
int fill_struct(t_scene *scene,char **buffer,int type);
int ft_rang(double min,double num,double max);
int light_handle(t_light **lt,char **s);
int camera_handle(t_camera **cam,char **s);
int ratio_check(char *s,double *i);
int get_colors(t_color *color,char *s);
int get_point(t_point *point,char *s);
int get_normalizer(t_point *vector,char *s);
int field_of_view(double *view,char *s);
int diameter_handle(double *dmeter,char *s);
void print_point(t_point l,t_color c);
int check_if_nb(char *s);
#endif




