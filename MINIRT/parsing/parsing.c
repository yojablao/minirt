/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yojablao <yojablao@student.42.ma>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/25 20:42:46 by yojablao          #+#    #+#             */
/*   Updated: 2025/01/04 19:12:04 by yojablao         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../tool.h"

int fill_ambligth(t_amlight **al,char **s)
{
    t_amlight *tmp;
    if(*al)
        return(0);
    tmp = malloc(sizeof(t_amlight));
    if(!ratio_check(s[1],&tmp->r) || !get_colors(&tmp->color,s[2])) 
        return(0);
    
    (*al) = tmp;
    return(1);
}

int fill_struct(t_scene *scene,char **buffer,int type)
{
    if (type == 1 && fill_ambligth(&scene->amligth,buffer))
            return (printf("[%f][%f][%f][%f]\n",scene->amligth->r,scene->amligth->color.r,scene->amligth->color.b,scene->amligth->color.g),1);
    else if (type == 2 && camera_handle(&scene->camera,buffer))
        return (printf("CAMIRA ->{%f}[%f][%f][%f][%f]\n",scene->camera->fov,scene->camera->cam_ray->o->x,scene->camera->cam_ray->o->y,scene->camera->cam_ray->o->z,scene->camera->fov),1);
    else if (type == 3 && light_handle(&scene->ligth,buffer))
        return (printf("[%f][%f][%f][%f]\n",scene->ligth->r,scene->ligth->color.r,scene->ligth->color.b,scene->ligth->color.g),1);
    else if (type == 4 && sphere_handle(&scene->sphere,buffer))
            return(print_point(*scene->sphere->center,scene->sphere->color),1);
    else if (type == 5 && Plane_handle(&scene->plane,buffer))
        return (print_point(scene->plane->point,scene->plane->color),1);
    else if (type == 6 && cylinder_handle(&scene->cylinder,buffer))
        return (print_point(scene->cylinder->center,scene->cylinder->color),1);
    else if (type == -1)
        return (1);
    else
        return(printf("nagh type[%d]\n",type),0);
}

int pars_it(char *s,t_scene *scene)
{
    char **buffer;
    int type;
    int i  = ft_strlen(s);
    if(s[i-1] == '\n')
        s[i-1] = '\0';
    buffer = ft_split(s,' ', '\t' );
     printf("%d\n",len2d(buffer));
    printf("check [%s]\n",buffer[0]);
    type = check_identifier(buffer[0]);
    printf("done [%s]\n",buffer[0]);
    if(!type)
        return(0);
    if(!fill_struct(scene,buffer,type))
        return(0);
    return(1);
}
t_scene  *init_scene(t_scene *s)
{
    s = malloc(sizeof(t_scene));
    s->amligth = NULL;
    s->camera = NULL;
    s->ligth = NULL;
    s->sphere = NULL;
    s->cylinder = NULL;
    s->plane = NULL;
    return(s);
}
t_scene *read_it(int fd)
{
    t_scene *scene;
    char *buffer;

    scene = init_scene(NULL);

    if (!scene)
        return (NULL);
    while (1)
    {

        buffer = get_next_line(fd);
        if (!buffer)
            break;
        if(!pars_it(buffer,scene))
            break;
    }
    return (scene);
}