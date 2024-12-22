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
    if(!s)
        return(-1);
    else if(ft_strncmp(s,"A",ft_strlen(s)) == 0)
        return (1);
    else if(ft_strncmp(s,"C",ft_strlen(s)) == 0)
        return (2);
    else if(ft_strncmp(s,"L",ft_strlen(s)) == 0)
        return (3);
    else if(ft_strncmp(s,"sp",ft_strlen(s)) == 0)
        return (4);
    else if(ft_strncmp(s,"pl",ft_strlen(s)) == 0)
        return (5);
    else if(ft_strncmp(s,"cy",ft_strlen(s)) == 0)
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
int len2d(char **a)
{
    int i = 0;
    if(!a||!*a)
        return(0);
    while(a[i])
        i++;
    return(i);
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
    color->b =  ft_atoi(buffer[2]);
    color->g =  ft_atoi(buffer[1]);
    if(color->r > 255 || color->b > 255 || color->g > 255)
        return(0);
    if(color->r < 0 || color->b < 0 || color->g < 0)
        return(0);
    return(1);
}
int fill_ambligth(t_amlight **al,char **s)
{
    t_amlight *tmp;

    tmp = malloc(sizeof(t_amlight));
    if(!ratio_check(s[1],&tmp->ratio) || !get_colors(&tmp->color,s[2])) 
        return(0);
    
    (*al) = tmp;
    return(1);
}
int get_point(t_point *point,char *s)
{
    char **buffer;

    buffer = ft_split(s,',');
    int i = 0;
    int j;
    if(!buffer[0] || !buffer[1] || !buffer[2])
        return(0);
    while(buffer[i])
    {
      if(!check_if_nb(buffer[i]))
        return(0);
        i++;
    }
    point->x = get_nb(buffer[0]);
    point->y = get_nb(buffer[1]);
    point->z = get_nb(buffer[2]);
    return(1);
}

int get_normalizer(t_point *vector,char *s)
{
    if(!get_point(vector,s))
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
int camera_handle(t_camera **cam,char **s)
{
    t_camera *c;

    c = malloc(sizeof(t_camera));
    if(len2d(s) != 4)
        return(printf("done_hire1\n"),0);
    if(!get_point(&c->point,s[1]) || !get_normalizer(&c->vector,s[2]) || !field_of_view(&c->viewdegrees,s[3]))
        return(printf("done_hire2\n"),0);
    *cam = c;
    return (1);
}






int light_handle(t_light **lt,char **s)
{
    t_light *tmp;
    tmp = malloc(sizeof(t_light));
    if(!tmp)
        return(0);
    if(!get_point(&tmp->point,s[1]) || !ratio_check(s[2],&tmp->ratio) || !get_colors(&tmp->color,s[3]))
        return(0);
    *lt = tmp;
    return(1);
    
}
int diameter_handle(double *dmeter,char *s)
{
    if(!check_if_nb(s))
        return(0);
    *dmeter = get_nb(s);
    return(1);

}
int sphere_handle(t_sphere **lt,char **s)
{
    t_sphere *tmp;

    tmp = malloc(sizeof(t_sphere));
    if(!tmp)
        return(0);
    if(!get_point(&tmp->center,s[1]) || !diameter_handle(&tmp->diameter,s[2])|| !get_colors(&tmp->color,s[3]))
        return(0);
    *lt = tmp;
    return(1);
}
int Plane_handle(t_plane **lt,char **s)
{
    t_plane *tmp;

    tmp = malloc(sizeof(t_plane));
    if(!tmp)
        return(0);
    if(!get_point(&tmp->point,s[1]) || !get_normalizer(&tmp->vector,s[2]) || !get_colors(&tmp->color,s[3]))
        return(0);
    *lt = tmp;
    return(1);
}
void print_point(t_point l,t_color c)
{
    printf(" point(%f,%f,%f) color(%f,%f,%f)\n",l.x,l.y,l.z,c.r,c.g,c.b);
}

int cylinder_handle(t_cylinder **lt,char **s)
{
    t_cylinder *tmp;

    tmp = malloc(sizeof(t_cylinder));
    if(!tmp)
        return (0);
    if(!get_point(&tmp->center,s[1]) || !get_normalizer(&tmp->vector,s[2])
        || !diameter_handle(&tmp->diameter,s[3] || !diameter_handle(&tmp->height,s[4]))
        || !get_colors(&tmp->color,s[5]))
            return(0);
    *lt = tmp;
    return(1);

}

int fill_struct(t_scene *scene,char **buffer,int type)
{
    if (type == 1 && fill_ambligth(&scene->amligth,buffer))
            return (printf("[%f][%f][%f][%f]\n",scene->amligth->ratio,scene->amligth->color.r,scene->amligth->color.b,scene->amligth->color.g),1);
    else if (type == 2 && camera_handle(&scene->camera,buffer))
        return (printf("[%f][%f][%f][%f]\n",scene->camera->point.x,scene->camera->point.y,scene->camera->point.z,scene->camera->viewdegrees),1);
    else if (type == 3 && light_handle(&scene->ligth,buffer))
        return (printf("[%f][%f][%f][%f]\n",scene->ligth->ratio,scene->ligth->color.r,scene->ligth->color.b,scene->ligth->color.g),1);
    else if (type == 4 && sphere_handle(&scene->sphere,buffer))
            return(print_point(scene->sphere->center,scene->sphere->color),1);
    else if (type == 5 && Plane_handle(&scene->plane,buffer))
        return (print_point(scene->plane->point,scene->plane->color),1);
    else if (type == 6 && cylinder_handle(&scene->cylinder,buffer))
        return (1);
    else if (type == -1)
        return (1);
    else
        return(printf("nagh type[%d]\n",type),0);
}
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