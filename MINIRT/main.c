#include "tool.h"

#define EPSILON 0.00001


int check_file(char *s,int *fd)
{
    int i;

    if (!s)
        return (1);
    i = strlen(s) - 1;
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
    if(ft_strncmp(s,"A",1) == 0)
        return (1);
    else if(ft_strncmp(s,"C",1) == 0)
        return (2);
    else if(ft_strncmp(s,"L",1) == 0)
        return (3);
    else if(ft_strncmp(s,"sp",1) == 0)
        return (4);
    else if(ft_strncmp(s,"pl",1) == 0)
        return (5);
    else if(ft_strncmp(s,"cy",1) == 0)
        return (6);
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
int check_if_nb(char *s)
{
    int a ;
    int dote;

    a = -1;
    dote = 0;
    if(!ft_isdigit(s[0]) && (s[0] == '-' || s[0] == '+'))
        a++;
    while (s[++a])
    {
        if(!ft_isdigit(s[a]))
        {
            if(s[a] == '.' && dote == 0)
            {
                dote++;
                continue;
            }
            return(0);
        }
    }
    return(1);    
}
int ratio_check_amlight(char *s,double *i)
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

    buffer = ft_split(s,',');
    int i = 0;
    int j;
    if(!buffer[0] || !buffer[1] || !buffer[2])
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
    color->g =  ft_atoi(buffer[1]);
    color->b =  ft_atoi(buffer[2]);
    return(1);
}
int fill_ambligth(t_amlight **al,char **s)
{
    t_amlight *tmp;

    tmp = malloc(sizeof(t_amlight));
    if(!ratio_check_amlight(s[1],&tmp->ratio) || !get_colors(&tmp->color,s[2])) 
        return(0);
    return(1);
}
int fill_struct(t_scene *scene,char **buffer,int type)
{
    if (type == 1 && fill_ambligth(&scene->amligth,buffer))
            return (1);
    else if (type == 2)
        return (1);
    else if (type == 3)
        return (1);
    else if (type == 4)
        return (1);
    else if (type == 5)
        return (1);
    else if (type == 6)
        return (1);
    else
        return(printf("nagh type[%d]\n",type),0);
}
// int check_amligth_nbs(char **v)
// {
//     int i = 0;
    
//     if(v[1][i])
// // }
// int check_nb(char **buffer,int type)
// {
//     // if (type == 1 && check_amligth_nbs(buffer))
//     //         return (1);
//     else if (type == 2)
//         return (1);
//     else if (type == 3)
//         return (1);
//     else if (type == 4)
//         return (1);
//     else if (type == 5)
//         return (1);
//     else if (type == 6)
//         return (1);
//     else
//         return(0);
// }
int pars_it(char *s,t_scene *scene)
{
    char **buffer;
    int i  = ft_strlen(s);
    if(s[i-1] == '\n')
        s[i-1] = '\0';
    buffer = ft_split(s,' ');
    int type;
    type = check_identifier(buffer[0]);
    if(!type)
        return(0);
    // if(!check_nb(scene,buffer,type))
    //     return(0);
    if(!fill_struct(scene,buffer,type))
        return(0);
    return(1);
}
t_scene *read_it(int fd)
{
    t_scene *scene;
    char *buffer;

    scene = malloc(sizeof(t_scene));
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
    // printf("done_hire\n");
    return (scene);
    

}

int main(int c , char **v)
{
    int fd;
    t_scene *scene;

    if(c == 2)
    {
        if(check_file(v[1],&fd))
            return(printf("error\n"), 1);
        scene = read_it(fd);
        

    }
}