/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   type_object.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yojablao <yojablao@student.42.ma>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/25 20:42:39 by yojablao          #+#    #+#             */
/*   Updated: 2024/12/25 20:42:40 by yojablao         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../tool.h"


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
    tmp->next = NULL;
    if(!tmp)
        return(0);
    if(!get_point(&tmp->center,s[1]) || !diameter_handle(&tmp->diameter,s[2])|| !get_colors(&tmp->color,s[3]))
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
    if(!get_point(&tmp->point,s[1]) || !ratio_check(s[2],&tmp->ratio) || !get_colors(&tmp->color,s[3]))
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
    if(len2d(s) != 4)
        return(printf("done_hire1\n"),0);
    if(!get_point(&c->point,s[1]) || !get_normalizer(&c->vector,s[2]) || !field_of_view(&c->viewdegrees,s[3]))
        return(printf("done_hire2\n"),0);
    *cam = c;
    return (1);
}