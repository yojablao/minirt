/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check_fn.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yojablao <yojablao@student.42.ma>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/25 20:42:51 by yojablao          #+#    #+#             */
/*   Updated: 2025/01/04 18:41:18 by yojablao         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../tool.h"

int ratio_check(char *s,double *i)
{
    if(!check_if_nb(s))
        return(printf("waa3333\n"),0);
    *i = get_nb(s);
    if(*i <= 1.00 && *i >= 0.00)
        return(1);
    return(0);
}
int get_colors(t_color *color,char *s)
{
    char **buffer;

    buffer = ft_split(s,',',',');
    int i = 0;
    int j;
    if(!buffer ||!buffer[0] || !buffer[1] || !buffer[2])
        return(0);
    while(buffer[i])
    {
        j = 0;
        while (ft_isdigit(buffer[i][j]))
            j++;
        if(buffer[i][j] != '\0')// && ft_isdigit(buffer[i][j])
            return(printf("lolo_notnum [%s]\n",buffer[i]),0);
        i++;
    }
    color->r =  ft_atoi(buffer[0]);
    color->b =  ft_atoi(buffer[2]);
    color->g =  ft_atoi(buffer[1]);
    if(color->r > 255 || color->b > 255 || color->g > 255)
        return(0);
    if(color->r < 0 || color->b < 0 || color->g < 0)
        return(0);
    return(1);
}

int get_point(t_tuple *point,char *s)
{
    char **buffer;

    buffer = ft_split(s,',',',');
    int i = -1;
    if(!buffer[0] || !buffer[1] || !buffer[2])
        return(0);
    while(buffer[++i])
    {
      if(!check_if_nb(buffer[i]))
        return(0);
    }
    point->x = get_nb(buffer[0]);
    point->y = get_nb(buffer[1]);
    point->z = get_nb(buffer[2]);
    return(1);
}

int get_normalizer(t_tuple *vector,char *s)
{
    if(!s ||!get_point(vector,s))
        return(0);
    if(!ft_rang(-1,vector->x,1) || !ft_rang(-1,vector->y,1) || !ft_rang(-1,vector->z,1))
        return(0);
    return(1);
}
int field_of_view(double *view,char *s)
{
    if(!check_if_nb(s))
        return(0);
    *view = get_nb(s);
    if(!ft_rang(0,*view,180))
        return(0);
    return(1);
}

int diameter_handle(double *dmeter,char *s)
{
    if(!check_if_nb(s))
        return(0);
    *dmeter = get_nb(s);
    if(*dmeter < 0)
        return(0);
    return(1);
}