#ifndef TOOL_H
#define TOOL_H

#include <libc.h>
#include <math.h>
#include "includes/get_next_line.h"
#include "includes/lib/libft.h"
// #include <b.h/>


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
}t_light;

typedef struct s_sphere
{
    t_point center;
    double diameter;
    t_color color;
}t_sphere;

typedef struct s_plane
{
    t_point point;
    t_point vector;
    t_color color;
}t_plane;

typedef struct s_cylinder
{
    t_point center;
    t_point vector;
    double diameter;
    double height;
    t_color color;
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


int ft_rang(double min,double num,double max);
#endif