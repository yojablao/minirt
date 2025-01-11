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

#define WINDOW_WIDTH 500
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
    double angle = PI / 6;
    *x = (p.x - p.y) * cos(angle);
    *y = (p.x + p.y) * sin(angle) - p.z;
}
// void draw_z_axis(void *mlx, void *win) {

    // int x1, y1, x2, y2;

    // // Project points to 2D
    
    // project_isometric(p_end, &x2, &y2);

    // // Adjust to window center
    // x1 += 500 / 2;
    // y1 += 500 / 2;
    // x2 += 500 / 2;
    // y2 += 500 / 2;

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
// float intersect_sphere(ray r, t_sphere s) {
//     t_tuple oc = sub_vec3(r.origin, s.center);
//     float a = dot_vec3(r.direction, r.direction);
//     float b = 2.0 * dot_vec3(r.direction, oc);
//     float c = dot_vec3(oc, oc) - s.r * s.r;
//     float discriminant = b * b - 4 * a * c;

//     if (discriminant < 0) {
//         return -1.0; // No intersection
//     } else {
//         float sqrt_d = sqrt(discriminant);
//         float t0 = (-b - sqrt_d) / (2 * a);
//         float t1 = (-b + sqrt_d) / (2 * a);

//         if (t0 < 0 && t1 < 0) {
//             return -1.0; // Both intersections behind the ray origin
//         } else if (t0 < 0) {
//             return t1; // Only t1 is valid
//         } else if (t1 < 0) {
//             return t0; // Only t0 is valid
//         } else {
//             return (t0 < t1) ? t0 : t1; // Both are valid, return the smaller one
//         }
//     }
// }
// void init_camera(t_camera *cam,  float fov, float aspect_ratio)
// {
//     // cam->cam_ray->o = &position;
//     cam->cam_ray->d = Normalize(cam->cam_ray->d);
//     cam->u = Normalize(&(t_tuple){0, 1, 0,0}); // Default up vector
//     cam->r = Normalize(Cross_p(cam->cam_ray->d, cam->u));
//     cam->fov = fov;
//     cam->aspect_ratio = aspect_ratio;
// }
void calculate_camera(t_scene *mt)
{
    t_tuple tmp;

    // Set the forward vector (fw) as the inverted camera ray direction
    mt->camera->fw = cpv(mt->camera->cam_ray->d->x, mt->camera->cam_ray->d->y, mt->camera->cam_ray->d->z, 0); // 0 for vector
    mt->camera->fw = scalar(mt->camera->fw, -1); // Invert the direction
    mt->camera->fw = Normalize(mt->camera->fw); // Normalize the forward vector

    // Define the world up vector (tmp)
    tmp = *cpv(0, 1, 0, 0); // 0 for vector

    // Calculate the right vector (r) as the cross product of world up and forward
    mt->camera->r = Cross_p(&tmp, mt->camera->fw);
    mt->camera->r = Normalize(mt->camera->r); // Normalize the right vector

    // Calculate the camera's up vector (u) as the cross product of forward and right
    mt->camera->u = Cross_p(mt->camera->fw, mt->camera->r);

    // Print camera position
    printf("Camera position:\t[%.2f, %.2f, %.2f]\n",
           mt->camera->cam_ray->o->x, mt->camera->cam_ray->o->y,
           mt->camera->cam_ray->o->z);

    // Print camera direction (corrected)
    printf("Camera direction:\t[%.2f, %.2f, %.2f]\n",
           mt->camera->cam_ray->d->x, mt->camera->cam_ray->d->y,
           mt->camera->cam_ray->d->z);
}
int	main(int ac, char **av)
{
	t_scene	*scene;
    

	if (ac != 2)
		return(printf("arg/n"));
        // printf("%s\n",av[atoi(av[1])]);
        
	scene = allocat_scene(NULL);
	if (!scene)
		return(printf("broooh"));
	init_scene(scene);
    // while (1)
    // {
    //     /* code */
    // }
    
	// scene->mlx->mlx = mlx_init(scene->width, scene->height, "miniRT", 1);
	// if (!scene->mlx)
	// {
	// 	free(scene);
	// 	m_error();
	// }
	// scene->img = mlx_new_image(scene->mlx->mlx, scene->width, scene->height);
	// if (!scene->img)
	// {
	// 	free(scene);
	// 	free(scene->mlx);
	// 	error();
	// }
	// return (0);
    // printf("init done\n");

	return (minirt(av, scene));
}






















































































// int main(int c , char **v)
// {
//     int fd;
//     t_scene *scene;
//     void	*mlx;
// 	void	*mlx_win;
//     t_data imag;
//     t_tuple test;


// 	mlx = mlx_init();

//     if(c == 2)
//     {
//             // printf("Error: /Failed to initialize MLX.\n");/
//         if (!mlx)
//         {
//             printf("Error: Failed to initialize MLX.\n");
//                 return (1);
//         }

//         mlx_win = mlx_new_window(mlx, 500, 500, "Hello world!");
//         if (!mlx_win)
//         {
//             printf("Error: Failed to create MLX window.\n");
//             return (1);
//         }
//             printf("Error: Failed to create MLX window.\n");
//         // mlx_loop(mlx);

//         if(check_file(v[1],&fd))
//             return(printf("error\n"), 1);
        
// 	    // mlx_win = mlx_new_window(mlx, 500, 500, "Hello world!");
//         // imag.img = mlx_new_image(mlx, 500, 500);
//         // imag.addr = mlx_get_data_addr(imag.img, &imag.bits_per_pixel, &imag.line_length, &imag.endian);
//         // test.x= 0;
//         // double tmp1;
//         // double tmp2;
//         // while (test.x < 500)
//         // {
//         //     test.y = 0;
//         //     while (test.y < 500)
//         //     {
//         //         tmp1 = map(test.x,-15,15,500);
//         //         tmp2 = map(test.y,-15,15,500);

//         //         // printf("X->{%f},Y->{%f},MAPED->{%f}\n",test.x,test.y,tmp2);
//         //         // if ((int)test.x % 100 == 0 || (int)test.y % 100 == 0)
//         //         //     my_mlx_pixel_put(&imag, test.x, test.y, 0x00303030);
//         //         if( tmp1 == 0 )
//         //             my_mlx_pixel_put(&imag, test.x, test.y, 0x00F00FFF);
//         //         if(tmp2 == 0 )
//         //             my_mlx_pixel_put(&imag, test.x, test.y, 0x00FFFFFF);
//         //         // if(tmp2 - tmp1 == 0 || -tmp1 - tmp2 == 0 || tmp2 + tmp1 == 0)
//         //         //     my_mlx_pixel_put(&imag, test.x, test.y, 0x00FF0000);
//         //         // (, &test.x, &test.y);
//         //         test.y++;
//         //     }
//         //     test.x++;
//         // }
//         // mlx_put_image_to_window(mlx,mlx_win,imag.img,0,0);
//        scene = read_it(fd);
//         init_camera(scene->camera,)

//         // while (1){};
        
// 	   mlx_loop(mlx);
//     }
//     // else
//     // {
//     //      p_data  data;

//     //     data.mlx = mlx_init();
//     //     if (!data.mlx)
//     //         return (1);
    
//     //     data.win = mlx_new_window(data.mlx, WINDOW_WIDTH, WINDOW_HEIGHT, "MLX Sphere");
//     //     data.ll.img = mlx_new_image(mlx, 500, 500);
//     //     data.ll.addr = mlx_get_data_addr(data.ll.img, &data.ll.bits_per_pixel, &data.ll.line_length, &data.ll.endian);
//     //     if (!data.win)
//     //        return (1);

//     //     data.radius = 200;
//     //     data.center_x = WINDOW_WIDTH / 2;
//     //     data.center_y = WINDOW_HEIGHT / 2;

//     // // Draw the sphere
//     //     draw_sphere(&data);

//     // // Keep window open
//     //     mlx_put_image_to_window(data.mlx, data.win, data.ll.img, 0, 0);
//     //     mlx_loop(data.mlx);
//     // }
// }