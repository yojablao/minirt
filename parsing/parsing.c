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

int fill_ambligth(t_amlight *al,char **s)
{
    // tmp = malloc(sizeof(t_amlight));
    if(!ratio_check(s[1],&al->r) || !get_colors(&al->color,s[2])) 
        return(0);
    return(1);
}

int fill_struct(t_scene **scene,char **buffer,int type)
{
    if (type == 1 && fill_ambligth(&(*scene)->amligth,buffer))
            return (1);
    else if (type == 2 && camera_handle(&(*scene)->camera,buffer))
        return (1);
    else if (type == 3 && light_handle(&(*scene)->ligth,buffer))
        return (1);
    else if (type == 4 && sphere_handle(&(*scene)->sphere,buffer))
    {

        return(1);
    }
    else if (type == 5 && Plane_handle(&(*scene)->plane,buffer))
        return (1);
    else if (type == 6 && cylinder_handle(&(*scene)->cylinder,buffer))
        return (1);
    else if (type == -1)
        return (1);
    else
        return(printf("nagh type[%d]\n",type),0);
}
void pintit(t_scene **l)
{

    t_sphere *tmp = (*l)->sphere;
    while (tmp)
    {
        printf("sphere[%f][%f][%f][%f][%f][%f][%f][%f][%lf]\n",tmp->center->x,tmp->center->y,tmp->center->z,tmp->color.r,tmp->color.g,tmp->color.b,tmp->diameter,tmp->id);
        tmp = tmp->next;
    }
    
}
int pars_it(char *s,t_scene **scene)
{
    char **buffer;
    int type;
    int i  = ft_strlen(s);
    if(s[i-1] == '\n')
        s[i-1] = '\0';
    buffer = ft_split(s,' ', '\t' );
    //  printf("%d\n",len2d(buffer));
    // printf("check [%s]\n",buffer[0]);
    type = check_identifier(buffer[0]);
    if(!type)
        return(0);
    if(!fill_struct(scene,buffer,type))
        return(0);
    // (*scene)->sphere = (*scene)->sphere->head;

    return(1);
}
// t_scene  *init_scene_n(t_scene *s)
// {
//     s = malloc(sizeof(t_scene));
//     s->amligth = NULL;
//     s->camera = NULL;
//     s->ligth = NULL;
//     s->sphere = NULL;
//     s->cylinder = NULL;
//     s->plane = NULL;
//     return(s);
// }
int read_it(int fd, t_scene **scene)
{
    char *buffer;

    if (!(*scene))
        return (1);
    while (1)
    {
        buffer = get_next_line(fd);
        if (!buffer)
            break;
        // printf("%s",buffer);
        if(!pars_it(buffer,scene))
            break;
    }
    return (0);
}
int parser(char *av,t_scene **sc)
{
    int fd;
    // printf("error\n");
    if(check_file(av,&fd) || read_it(fd,sc))
        return(printf("error\n"), 1);
                pintit(sc);
    return 0;
    
}