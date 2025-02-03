/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   print.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yojablao <yojablao@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025-02-02 14:20:18 by yojablao          #+#    #+#             */
/*   Updated: 2025-02-02 14:20:18 by yojablao         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../pars.h"



void print_cylinder(t_cylinder *cylinder)
{
    if (!cylinder)
        return;

    printf("Cylinder:\n");
    printf("  Center: (%.2f, %.2f, %.2f)\n", cylinder->center.x, cylinder->center.y, cylinder->center.z);
    printf("  Axis:   (%.2f, %.2f, %.2f)\n", cylinder->vector.x, cylinder->vector.y, cylinder->vector.z);
    printf("  Diameter: %.2f\n", cylinder->diameter);
    printf("  Height: %.2f\n", cylinder->height);
    printf("  Color:  (%d, %d, %d)\n", cylinder->color.r, cylinder->color.g, cylinder->color.b);
    printf("\n");
}

void print_all_cylinders(t_scene *scene)
{
    if (!scene || !scene->cylinder)
        return;

    t_cylinder *cylinder = scene->cylinder;
    while (cylinder)
    {
        print_cylinder(cylinder);
        cylinder = cylinder->next;
    }
}

void print_light(t_light *light)
{
    if (!light)
        return;
    while (light)
    {
        printf("Light:\n");
        printf("  Position: (%.2f, %.2f, %.2f)\n", light->point.x, light->point.y, light->point.z);
        printf("  r: %.2f\n", light->r);
        printf("  Color:  (%d, %d, %d)\n", light->color.r, light->color.g, light->color.b);
        printf("\n");
        light = light->next;
    }
}
void print_tuple(const char *name, const t_tuple *tuple) {
    if (!tuple) {
        printf("  %s: NULL\n", name);
        return;
    }
    printf("  %s: (%f, %f, %f)\n", name, tuple->x, tuple->y, tuple->z);
}
void print_ray(const t_ray *ray) {
    if (!ray) {
        printf("  Ray: NULL\n");
        return;
    }
    printf("  Ray Details:\n");
    print_tuple("Origin (O)", ray->o);
    print_tuple("Direction (D)", ray->d);
    // print_tuple("Up Direction (UD)", ray->ud);
}

void print_camera(const t_camera *camera) {
    if (!camera) {
        printf("Error: Camera pointer is NULL\n");
        return;
    }
    printf("%f",camera->fov);

    if (camera->cam_ray) {
        print_ray(camera->cam_ray);
    } else {
        printf("  Camera Ray: NULL\n");
    }
}
void print_sphere(t_sphere *sphere)
{
    if (!sphere)
        return;
    while (sphere)
    {
        printf("Sphere:\n");
        printf("  Center: (%.2f, %.2f, %.2f)\n", sphere->center->x, sphere->center->y, sphere->center->z);
        // printf("  Radius: %.2f\n", sphere->r);
        printf("  Color:  (%d, %d, %d)\n", sphere->color.r, sphere->color.g, sphere->color.b);
        printf("  Diameter: %.2f\n", sphere->diameter);
        printf("  ID: %.2f\n", sphere->id);
        printf("\n");
        sphere = sphere->next;
    }
}
