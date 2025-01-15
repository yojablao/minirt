/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minirt.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yojablao <yojablao@student.42.fr>          #+#  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025-01-10 16:15:36 by yojablao          #+#    #+#             */
/*   Updated: 2025-01-10 16:15:36 by yojablao         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "tool.h"
float sphere_intersect(t_camera *cam, t_tuple *ray, t_sphere *sp)
{
    t_holol hal;
    t_tuple *cam_sp;
    float d1, d2;

    cam_sp = tpl_o(cam->cam_ray->o, sp->center, '-');
    hal.a = 1.0; // Assuming ray is normalized
    hal.b = 2 * (cam_sp->x * ray->x + cam_sp->y * ray->y + cam_sp->z * ray->z);
    hal.c = cam_sp->x * cam_sp->x + cam_sp->y * cam_sp->y + cam_sp->z * cam_sp->z - pow(sp->diameter / 2, 2);
    hal.disc = pow(hal.b, 2) - 4.0 * hal.a * hal.c;

    if (hal.disc < 0.0)
        return (-1.0); // No intersection

    d1 = (-hal.b - sqrt(hal.disc)) / (2 * hal.a);
    d2 = (-hal.b + sqrt(hal.disc)) / (2 * hal.a);

    if (d1 > 0.0)
        return (d1);
    else if (d2 > 0.0)
        return (d2);
    return (-1.0); // Intersection is behind the camera
}

void closest_sp(t_scene *mt, t_dist *dist, t_tuple *ray)
{
    t_sphere *sp = mt->sphere;

    while (sp)
    {
        dist->dist = sphere_intersect(mt->camera, ray, sp);
        if (dist->dist >= 0.0 && dist->dist < dist->min_dist) // Updated to check >= 0
        {
            dist->min_dist = dist->dist;
            printf("dist->min_dist: %f\n", dist->min_dist);
            dist->closest_obj = 1;
            dist->cl_sp = sp;
        }
        sp = sp->next;
    }
}

static t_dist *dist_init(t_dist *dist)
{
    dist->dist = -INFINITY;
    dist->min_dist = INFINITY;
    dist->closest_obj = 0;
    dist->cl_sp = NULL;
    // dist->dot_light = malloc(sizeof(t_tuple)); // Ignoring leaks as per request
    return (dist);
}
float plane_intersect(t_camera *c,t_tuple *ray,t_plane *pl)
{
    t_tuple *cam_pl;
    float d1, d2;

    cam_pl = tpl_o(c->cam_ray->o, &pl->point, '-');
    d1 = Dot_p(cam_pl, &pl->vector);
    d2 = Dot_p(ray, &pl->vector);

    if (d2 == 0.0)
        return (-1.0); // Ray is parallel to the plane

    return (-d1 / d2);
}

void closest_pl(t_scene *mt, t_dist *dist, t_tuple *ray)
{
    t_plane *pl = mt->plane;

    while (pl)
    {
        dist->dist = plane_intersect(mt->camera, ray, pl);
        if (dist->dist >= 0.0 && dist->dist < dist->min_dist) // Updated to check >= 0
        {
            dist->min_dist = dist->dist;
            printf("dist->min_dist: %f\n", dist->min_dist);
            dist->closest_obj = 2;
            dist->cl_pl = pl;
        }
        pl = pl->next;
    }
}
void draw_intersection_obj(t_scene *sc, t_tuple *ray, int *color)
{
    t_dist *dist = malloc(sizeof(t_dist));
    float int_light = 0.0;

    dist = dist_init(dist);
    closest_sp(sc, dist, ray);
    closest_pl(sc, dist, ray);

    // Update ray to intersection point
    ray = tpl_o(scalar(ray, dist->min_dist), sc->camera->cam_ray->o, '+');
    dist->dot_light = Normalize(tpl_o(&sc->ligth->point, ray, '-'));

    // Default color if no object is hit
    if (!dist->closest_obj)
	{
        *color = 0xffffe5ff;
		// printf("%d////////////////////////////////////////\n",*color);
	}
    else
    {
        if(dist->closest_obj == 2)
            *color = 0x00ff00; // Placeholder color
        else
            *color = 0xff0000; // Placeholder color

        // Here you can calculate lighting, shadows, etc.
		// printf("%d-----------------------------\n",*color);
    }
}

void shot_ray(t_scene *sc, t_pixels *px)
{
    float x_temp, y_temp, z_temp;
    t_tuple *tmp;

    x_temp = px->x_ray * sc->camera->r->x + px->y_ray * sc->camera->u->x + px->z_ray * sc->camera->fw->x;
    y_temp = px->x_ray * sc->camera->r->y + px->y_ray * sc->camera->u->y + px->z_ray * sc->camera->fw->y;
    z_temp = px->x_ray * sc->camera->r->z + px->y_ray * sc->camera->u->z + px->z_ray * sc->camera->fw->z;

    px->x_ray = x_temp;
    px->y_ray = y_temp;
    px->z_ray = z_temp;

    tmp = cpv(px->x_ray, px->y_ray, px->z_ray, 0);
    // printf("%p\n",px->ray);
    px->ray = Normalize(tmp);
    free(tmp);
    draw_intersection_obj(sc, px->ray, &px->color);
    // if(!)px->color
    // printf("%d\n",px->win_x);
	my_mlx_pixel_put(sc->mlx.img, px->win_x, px->win_y, px->color);
}

void draw_scene(t_scene *sc)
{
    t_pixels *px = malloc(sizeof(t_pixels));
    if (!px)
        return;

    px->win_x = 0;
    while (px->win_x <= sc->width)
    {
        px->win_y = 0;
        while (px->win_y <= sc->height)
        {
            px->x_ray = px->win_x - sc->width / 2;
            px->y_ray = -px->win_y + sc->height / 2;
            px->z_ray = -sc->height * 0.5 / tanf(sc->camera->fov * 0.5 * (I / 180)); // Fixed `I` to `M_PI`
             	// my_mlx_pixel_put(img, px->win_x, px->win_y, 8579678);
            shot_ray(sc, px);
            px->win_y++;
        }
        px->win_x++;
    }
}
int minirt(char **av,t_scene ** c)
{
	parser(av[1],c);
    t_scene * sc = *c;

	calculate_camera(sc);

	draw_scene(sc);
	if (mlx_put_image_to_window(sc->mlx.mlx, sc->mlx.window,sc->mlx.img->img, 0, 0) < 0)
	    printf("pars done/n");
        
	// mlx_loop_hook(sc->gr.mlx, hook, sc);
	// mlx_resize_hook(sc->gr.mlx, resize, sc);
	// mlx_scroll_hook(sc->gr.mlx, scrollhook, sc);

    
	mlx_loop(sc->mlx.mlx);
	// mlx_delete_image(sc->gr.mlx, sc->gr.img);
	// mlx_terminate(sc->gr.mlx);
	// free_list(sc->sphere);
	// free_list(sc->cylinder);
	// free_list(sc->plane);
	// free(sc);
	return (EXIT_SUCCESS);
}
























































































































































































