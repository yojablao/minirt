/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_rang.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yojablao <yojablao@student.42.ma>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/25 20:42:48 by yojablao          #+#    #+#             */
/*   Updated: 2025/01/01 18:32:40 by yojablao         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../tool.h"

int ft_rang(double min,double num,double max)
{
    if (num >= min && num <= max)
        return (1);
    else 
        return (0);
}
t_scene *allocat_scene(t_scene *scene)
{
    scene = malloc(sizeof(t_scene));
    scene->camera =  malloc(sizeof(t_camera));
    scene->camera->cam_ray =  malloc(sizeof(t_ray));
    // scene->amligth =  malloc(sizeof(t_amlight));
    // scene->ligth =  malloc(sizeof(t_light));
    // scene->sphere =  malloc(sizeof(t_sphere));
    // scene->sphere->head =  malloc(sizeof(t_sphere));
    // scene->plane =  malloc(sizeof(t_plane));
    // scene->cylinder =  malloc(sizeof(t_cylinder));
    // scene->mlx =  malloc(sizeof(t_mlx));
    // scene->img =  malloc(sizeof(t_data));
	return(scene);

}
void	init_scene(t_scene *scene)
{
	scene->width = 500;
	scene->height = 500;
	scene->amligth.r = -1.0;
	scene->amligth.color.r = 0;
	scene->amligth.color.g = 0;
	scene->amligth.color.b = 0;
    scene->camera->cam_ray->o = cpv(0,0,0,0);
    scene->camera->cam_ray->d = cpv(0,0,0,0);
	scene->camera->fov = -1;
	// scene->ligth->bright = -1.0;
	// scene->ligth->point.x = 0.0;
	// scene->ligth->point.y = 0.0;
	// scene->ligth->point.z = 0.0;
	// scene->ligth->color.r = 0.0;
	// scene->ligth->color.g = 0.0;
	// scene->ligth->color.b = 0.0;
	scene->sphere = NULL;
	scene->plane = NULL;
	scene->cylinder = NULL;
	// scene->mlx = NULL;
	// scene->img = NULL;
}
float	ft_comp_float(float f1, float f2)
{
	float	diff;
	float	precision;

	precision = 0.000001;
	if (f1 == f2)
		return (0.0);
	diff = (f1) - (f2);
	if (fabs(diff) < precision)
		return (0.0);
	else
		return (diff);
}
