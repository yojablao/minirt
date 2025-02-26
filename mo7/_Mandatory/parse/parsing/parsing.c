/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yojablao <yojablao@student.42.ma>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/25 20:42:46 by yojablao          #+#    #+#             */
/*   Updated: 2025/02/21 23:23:50 by yojablao         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../pars.h"

int fill_ambligth(t_amlight *al,char **s)
{
    // tmp = malloc(sizeof(t_amlight));
    if(al->r != -1.0)
        return(0);
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
        return(1);
    else if (type == 5 && Plane_handle(&(*scene)->plane,buffer))
        return (1);
    else if (type == 6 && cylinder_handle(&(*scene)->cylinder,buffer))
        return (1);
    else if (type == -1)
        return (1);
    else
        return(printf("nagh type[%d]\n",type),0);
}

int pars_it(char *s,t_scene **scene)
{
    char **buffer;
    int type;
    int i  = ft_strlen(s);
    if(s[i-1] == '\n')
        s[i-1] = '\0';
    buffer = f_split(s,' ', '\t' );
    if (!buffer)
        return(0);
    type = check_identifier(buffer[0]);
    if(!type)
        return(0);
    if(!fill_struct(scene,buffer,type))
        return(0);
    return(1);
}

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
        if(!pars_it(buffer,scene))
            return(free(buffer),1);
        free(buffer);
    }
    return (0);
}

int parser(char *av,t_scene **sc)
{
    int fd;

    if(check_file(av,&fd) || read_it(fd,sc))
        return(printf("error\n"), 1);
    print_camera(&(*sc)->camera);
    print_tuple("ambligth",&(*sc)->amligth.color);
    print_sphere((*sc)->sphere);
    print_light((*sc)->ligth);
    print_all_cylinders(*sc);
    return 0;
    
}