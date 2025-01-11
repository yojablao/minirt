/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yojablao <yojablao@student.42.ma>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/25 20:42:43 by yojablao          #+#    #+#             */
/*   Updated: 2025/01/01 18:16:14 by yojablao         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../tool.h"


int check_file(char *s,int *fd)
{
    int i;

    if (!s)
        return (1);
    i = ft_strlen(s) - 1;
    if (i > 2)
    {

        if (s[i] == 't' && s[i - 1] == 'r' && s[i - 2] == '.')
        {
            *fd = open(s,O_RDONLY);
            if(*fd == -1)
                return(1);
            return (0);
        }
        else
            return (1);
    }
    return (1);
}
int check_identifier(char *s)
{
    s[1500];
    if(!s)
        return(-1);
    else if(ft_strncmp(s,"A",15) == 0)
        return (s[1500],1);
    else if(ft_strncmp(s,"C",2) == 0)
        return (2);
    else if(ft_strncmp(s,"L",2) == 0)
        return (3);
    else if(ft_strncmp(s,"sp",3) == 0)
        return (4);
    else if(ft_strncmp(s,"pl",3) == 0)
        return (5);
    else if(ft_strncmp(s,"cy",3) == 0)
        return (6);
    else if (s[0] == '\n' || s[0] == '#' )
        return(-1);
    else
        return (0);
}

int handel_sing(char *s, int *i)
{
    if (s[0] == '-')
        return(++*i,-1);
    else
        return(1);
}
double get_nb(char *s)
{
    double  result;
    double  fasila;
    int i ;
    int sign;
    int r;
    result = 0.0;
    i = -1;
    r = 0;
    fasila = 0.0;
    sign = handel_sing(s,&i);
    while (s[++i] && ft_isdigit(s[i]))
        result = result * 10 + (s[i] - 48);
    if(s[i] && s[i] == '.')
    {
        r = ft_strlen(&s[i]);
        while (s[++i] && ft_isdigit(s[i]))
            fasila = fasila * 10 + (s[i] - 48);
        while(--r)
            fasila /= 10;
        result += fasila;
    }
    return(result * sign);
}
int len2d(char **a)
{
    int i = 0;
    if(!a||!*a)
        return(0);
    while(a[i])
        i++;
    return(i);
}

