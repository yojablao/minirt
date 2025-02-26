/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   type_object.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yojablao <yojablao@student.42.ma>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/25 20:42:39 by yojablao          #+#    #+#             */
/*   Updated: 2025/01/04 19:13:37 by yojablao         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../pars.h"

#define WIN_WIDTH 800
#define WIN_HEIGHT 600


int cylinder_handle(t_cylinder **lt,char **s)
{
    t_cylinder *tmp;
    t_cylinder *last;

    last = *lt;
    tmp = master(sizeof(t_cylinder),1);
    if(!tmp)
        return (0);
    tmp->next = NULL;
    if(!get_point(&tmp->center,s[1]) || !get_normalizer(&tmp->vector,s[2])
        || !diameter_handle(&tmp->diameter,s[3]) || !diameter_handle(&tmp->height,s[4])
        || !get_colors(&tmp->color,s[5]))
            return(0);
    if(last == NULL)
        *lt = tmp;
    else
    {
        while(last)
            last = last->next;
        last = tmp;
    }
    printf("totobini/n");
    return(1);
}
int Plane_handle(t_plane **lt,char **s)
{
    t_plane *tmp;
    t_plane *last;

    tmp = master(sizeof(t_plane),1);
    if(!tmp)
        return(0);
    if(!get_point(&tmp->point,s[1]) || !get_normalizer(&tmp->vector,s[2]) || !get_colors(&tmp->color,s[3]))
        return(0);
    tmp->next = NULL;
    if(!last)
        *lt = tmp;
    else
    {
        last = *lt;
        while(last)
            last = last->next;
        last = tmp;
    }
    return(1);
}
// int sphere_handle(t_sphere *sphere, char **s) {
//     // Check if the sphere pointer is valid
//     if (!sphere) {
//         return (0); // Return 0 if the sphere is NULL
//     }

//     // Allocate memory for the center (if not already allocated)
//     // Initialize the sphere's fields
//     if (!get_point(sphere->center, s[1]) || // Set the center
//         !diameter_handle(&sphere->diameter, s[2]) || // Set the diameter
//         !get_colors(&sphere->color, s[3])) { // Set the color
//         // free(sphere->center); // Free allocated memory if initialization fails
//         sphere->center = NULL; // Reset the pointer
//         return (0); // Return 0 if any initialization fails
//     }

//     // Set the next pointer to NULL (assuming it's a linked list)
// //     
//     sphere->next = NULL;

//     return (1); // Return 1 on success
// // }
// int sphere_handle(t_sphere **lt,char **s)
// {
//     t_sphere *tmp;
//     t_sphere *last;
    
//     while (*lt)
//     {
//         *lt = (*lt)->next;
//     }
//     *lt  = master(sizeof(t_sphere));
//     tmp->center = master(sizeof(t_tuple));
//     tmp->next = NULL;
//     if(!tmp)
//         return(0);
//     if(!get_point(tmp->center,s[1]) || !diameter_handle(&tmp->diameter,s[2])|| !get_colors(&tmp->color,s[3]))
//         return(0);
//     if(!last)
//         *lt = tmp;
//     else
//     {
//         while(*lt)
//         {
//             *lt = (*lt)->next;
//         }
//         *lt = tmp;
//         *lt = last;
//     }
//     return(1);
// }
int sphere_handle(t_sphere **lt, char **s)
{
    t_sphere *tmp;
    t_sphere *last;

    if (!lt)
        return (0); 
    tmp = master(sizeof(t_sphere),1);
    if (!tmp)
        return (0);
    tmp->center = master(sizeof(t_tuple),1);
    if (!tmp->center)
        return (0);
    if (!get_point(tmp->center, s[1]) || !diameter_handle(&tmp->diameter, s[2]) ||
        !get_colors(&tmp->color, s[3])) 
        return (0);
    tmp->next = NULL;
    if (*lt == NULL)
        *lt = tmp;
    else
    {
        last = *lt;
        while (last->next != NULL)
            last = last->next;
        last->next = tmp;
    }
    return (1);
}

int light_handle(t_light **lt, char **s)
{
    t_light *tmp;
    t_light *last;

    tmp = master(sizeof(t_light),1);
    if (!tmp)
        return (0);
    if (!get_point(&tmp->point, s[1]) || !ratio_check(s[2], &tmp->r) || !get_colors(&tmp->color, s[3]))
        return (0);
    tmp->next = NULL;
    if (*lt == NULL)
        *lt = tmp;
    else
    {
        last = *lt;
        while (last->next != NULL)
            last = last->next;
        last->next = tmp;
    }
    return (1);
}
int camera_handle(t_camera *c,char **s)
{
    if(c->fov != -1)
        return(0);
    c->cam_ray = master(sizeof(t_ray),1);
    c->cam_ray->d = master(sizeof(t_tuple),1);
    c->cam_ray->o = master(sizeof(t_tuple),1);
    if(len2d(s) != 4)
        return(printf("done_hire1\n"),0);

    if(!get_point(c->cam_ray->o,s[1]) || !get_normalizer(c->cam_ray->d,s[2]) || !field_of_view(&c->fov,s[3]))
        return(printf("done_hire2\n"),0);

    return (1);
}