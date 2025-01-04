/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   type_object.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yojablao <yojablao@student.42.ma>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/25 20:42:39 by yojablao          #+#    #+#             */
/*   Updated: 2025/01/04 19:13:37 by yojablao         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../tool.h"

#define WIN_WIDTH 800
#define WIN_HEIGHT 600


int cylinder_handle(t_cylinder **lt,char **s)
{
    t_cylinder *tmp;
    t_cylinder *last;

    last = *lt;
    tmp = malloc(sizeof(t_cylinder));
    tmp->next = NULL;
    if(!tmp)
        return (0);
    if(!get_point(&tmp->center,s[1]) || !get_normalizer(&tmp->vector,s[2])
        || !diameter_handle(&tmp->diameter,s[3]) || !diameter_handle(&tmp->height,s[4])
        || !get_colors(&tmp->color,s[5]))
            return(0);
    if(last == NULL)
        *lt = tmp;
    else
    {
        while(last)
            last = last->next;
        last = tmp;
    }
    return(1);
}
int Plane_handle(t_plane **lt,char **s)
{
    t_plane *tmp;
    t_plane *last;

    last = *lt;
    tmp = malloc(sizeof(t_plane));
    tmp->next = NULL;
    if(!tmp)
        return(0);
    if(!get_point(&tmp->point,s[1]) || !get_normalizer(&tmp->vector,s[2]) || !get_colors(&tmp->color,s[3]))
        return(0);
    if(!last)
        *lt = tmp;
    else
    {
        while(last)
            last = last->next;
        last = tmp;
    }
    return(1);
}
int sphere_handle(t_sphere **lt,char **s)
{
    t_sphere *tmp;
    t_sphere *last;

    last = *lt;
    tmp = malloc(sizeof(t_sphere));
    tmp->center = malloc(sizeof(t_tuple));
    tmp->next = NULL;
    if(!tmp)
        return(0);
    if(!get_point(tmp->center,s[1]) || !diameter_handle(&tmp->diameter,s[2])|| !get_colors(&tmp->color,s[3]))
        return(0);
    if(!last)
        *lt = tmp;
    else
    {
        while(last)
            last = last->next;
        last = tmp;
    }
    return(1);
}

int light_handle(t_light **lt,char **s)
{
    t_light *tmp;
    t_light *last;

    last = *lt;
    tmp = malloc(sizeof(t_light));
    tmp->next = NULL;
    printf("done//\n");
    if(!tmp)
        return(0);
    if(!get_point(&tmp->point,s[1]) || !ratio_check(s[2],&tmp->r) || !get_colors(&tmp->color,s[3]))
        return(0);
    if(!last)
        *lt = tmp;
    else
    {
        while(last)
            last = last->next;
        last = tmp;
    }
    return(1);
    
}
int camera_handle(t_camera **cam,char **s)
{
    t_camera *c;

    if(*cam)
        return(0);
    c = malloc(sizeof(t_camera));
    c->cam_ray = malloc(sizeof(t_ray));
    c->cam_ray->d = malloc(sizeof(t_tuple));
    c->cam_ray->o = malloc(sizeof(t_tuple));
    c->cam_ray->ud = malloc(sizeof(t_tuple));
    if(len2d(s) != 4)
        return(printf("done_hire1\n"),0);
    if(!get_point(c->cam_ray->o,s[1]) || !get_normalizer(c->cam_ray->d,s[2]) || !field_of_view(&c->fov,s[3]))
        return(printf("done_hire2\n"),0);
    *cam = c;
    return (1);
}