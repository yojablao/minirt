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

void pars_it(char *s,t_scene *scene)
{
    char **buffer;
    buffer = ft_split(s,' ');
    int i = 0;
    while (buffer[i])
    {
        printf("%s ",buffer[i]);
        i++;
    }
    printf("\n");
    


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
        pars_it(buffer,scene);
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
        printf("%d\n",fd);
        scene = read_it(fd);
        

    }
}