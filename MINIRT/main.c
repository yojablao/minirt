/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yojablao <yojablao@student.42.ma>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/25 20:42:29 by yojablao          #+#    #+#             */
/*   Updated: 2025/01/04 18:48:10 by yojablao         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "tool.h"

#define WINDOW_WIDTH 800
#define WINDOW_HEIGHT 600
#define PI 3.14159265359

typedef struct l_data {
    void    *mlx;
    void    *win;
    int     radius;
    int     center_x;
    int     center_y;
    t_data ll;
} p_data;



double map(double unscaled_num,double min,double max ,double oldmax)
{
	return((max - min) * (unscaled_num - 0) / (oldmax - 0) + min);
}
void	my_mlx_pixel_put(t_data *data, int x, int y, int color)
{
	char	*dst;

	dst = data->addr + (y * data->line_length + x * (data->bits_per_pixel / 8));
	*(unsigned int*)dst = color;
}
void project_isometric(t_tuple p, int *x, int *y) {
    double angle = M_PI / 6;
    *x = (p.x - p.y) * cos(angle);
    *y = (p.x + p.y) * sin(angle) - p.z;
}
// void draw_z_axis(void *mlx, void *win) {

    // int x1, y1, x2, y2;

    // // Project points to 2D
    
    // project_isometric(p_end, &x2, &y2);

    // // Adjust to window center
    // x1 += 800 / 2;
    // y1 += 800 / 2;
    // x2 += 800 / 2;
    // y2 += 800 / 2;

    // Draw Z-axis line
    // draw_line(mlx, win, x1, y1, x2, y2, 0x00FF00); // Green line
// }

void print_point(t_tuple l,t_color c)
{
    printf(" point(%f,%f,%f) color(%f,%f,%f)\n",l.x,l.y,l.z,c.r,c.g,c.b);
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

void    draw_sphere(p_data *data)
{
    double  phi, theta;
    int     x, y;
    double  step = 3.14 / 30;  // Controls the density of lines

    // Draw latitude lines
    for (phi = 0; phi <= PI; phi += step)
    {
        for (theta = 0; theta <= 2 * PI; theta += 0.01)
        {
            x = data->center_x + data->radius * sin(phi) * cos(theta);
            y = data->center_y + data->radius * sin(phi) * sin(theta) * 0.5; // 0.5 for perspective
            if (theta == 0 || (int)(theta * 100) % 510 == 0)
                my_mlx_pixel_put(&data->ll, x, y, 0xFFFFFF);
        }
    }

    // Draw longitude lines
    for (theta = 0; theta < 2 * PI; theta += step)
    {
        for (phi = 0; phi <= PI; phi += 0.01)
        {
            x = data->center_x + data->radius * sin(phi) * cos(theta);
            y = data->center_y + data->radius * sin(phi) * sin(theta) * 0.5; // 0.5 for perspective
            if ((int)(phi * 100) % 5 == 0)
                my_mlx_pixel_put(&data->ll, x, y, 0xFFFFFF);
        }
    }
}
int main(int c , char **v)
{
    int fd;
    t_scene *scene;
    // void	*mlx;
	// void	*mlx_win;
    // t_data imag;
    // t_tuple test;


	// mlx = mlx_init();

    if(c == 2)
    {
        if(check_file(v[1],&fd))
            return(printf("error\n"), 1);
	    // mlx_win = mlx_new_window(mlx, 800, 800, "Hello world!");
        // imag.img = mlx_new_image(mlx, 800, 800);
        // imag.addr = mlx_get_data_addr(imag.img, &imag.bits_per_pixel, &imag.line_length, &imag.endian);
        // // int x= 0;
        // int y;
        // while (test.x < 800)
        // {
        //     test.y = 0;
        //     while (test.y < 800)
        //     {
        //         // printf("X->{%d},Y->{%d},MAPED->{%f}\n",x,y,map(y,-15,15,800));
        //         if ((int)test.x % 100 == 0 || (int)test.y % 100 == 0)
        //             my_mlx_pixel_put(&imag, test.x, test.y, 0x00303030);
        //         if(map(test.y,-15,15,800) < 0 && map(test.x,-15,15,800) == 0 )
        //             my_mlx_pixel_put(&imag, test.x, test.y, 0x00F00FFF);
        //         if(map(test.y,-15,15,800) == 0 && map(test.x,-15,15,800) < 0)
        //             my_mlx_pixel_put(&imag, test.x, test.y, 0x00FFFFFF);
        //         if(map(test.y,-15,15,800) - map(test.x,-15,15,800) == 0 || -map(test.x,-15,15,800) - map(test.y,-15,15,800) == 0 || map(test.y,-15,15,800) + map(test.x,-15,15,800) == 0)
        //             my_mlx_pixel_put(&imag, test.x, test.y, 0x00FF0000);
        //         // (, &test.x, &test.y);
        //         test.y++;
        //     }
        //     test.x++;
        // }
        
        scene = read_it(fd);
        
	    // mlx_loop(mlx);
    }
    // else
    // {
    //      p_data  data;

    //     data.mlx = mlx_init();
    //     if (!data.mlx)
    //         return (1);
    
    //     data.win = mlx_new_window(data.mlx, WINDOW_WIDTH, WINDOW_HEIGHT, "MLX Sphere");
    //     data.ll.img = mlx_new_image(mlx, 800, 800);
    //     data.ll.addr = mlx_get_data_addr(data.ll.img, &data.ll.bits_per_pixel, &data.ll.line_length, &data.ll.endian);
    //     if (!data.win)
    //        return (1);

    //     data.radius = 200;
    //     data.center_x = WINDOW_WIDTH / 2;
    //     data.center_y = WINDOW_HEIGHT / 2;

    // // Draw the sphere
    //     draw_sphere(&data);

    // // Keep window open
    //     mlx_put_image_to_window(data.mlx, data.win, data.ll.img, 0, 0);
    //     mlx_loop(data.mlx);
    // }
}