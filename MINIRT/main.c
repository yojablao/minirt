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


int fill_struct(t_scene *scene,char **buffer,int type)
{
    if (type == 1)
        fill_ambligth(&scene->amligth,);
    else if (type == 2)

    else if (type == 3)

    else if (type == 4)

    else if (type == 5)

    else if (type == 6)


}
int pars_it(char *s,t_scene *scene)
{
    char **buffer;
    buffer = ft_split(s,' ');
    int type;
    type = check_identifier(buffer[0]);
    if(!type)
        return(0);
    fill_struct(scene,buffer,type)
    
    
    


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
        if(!buffer)
            break;
        if(!pars_it(buffer,scene))
            break;
    }
    printf("done_hire\n");
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