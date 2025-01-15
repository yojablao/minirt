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

#include "../tool.h"

#define WIN_WIDTH 800
#define WIN_HEIGHT 600


int cylinder_handle(t_cylinder **lt,char **s)
{
    t_cylinder *tmp;
    t_cylinder *last;

    last = *lt;
    tmp = malloc(sizeof(t_cylinder));
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

    last = *lt;
    tmp = malloc(sizeof(t_plane));
    tmp->next = NULL;
    if(!tmp)
        return(0);
    if(!get_point(&tmp->point,s[1]) || !get_normalizer(&tmp->vector,s[2]) || !get_colors(&tmp->color,s[3]))
        return(0);
    if(!last)
        *lt = tmp;
    else
    {
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
//     *lt  = malloc(sizeof(t_sphere));
//     tmp->center = malloc(sizeof(t_tuple));
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
int sphere_handle(t_sphere **lt, char **s) {
    t_sphere *tmp;
    t_sphere *last;

    // Check if the list pointer is valid
    if (!lt) {
        return (0); // Return 0 if the list pointer is NULL
    }

    // Allocate memory for the new sphere
    tmp = malloc(sizeof(t_sphere));
    if (!tmp) {
        return (0); // Return 0 if allocation fails
    }

    // Allocate memory for the sphere's center
    tmp->center = malloc(sizeof(t_tuple));
    if (!tmp->center) {
        free(tmp); // Free the sphere if center allocation fails
        return (0);
    }

    // Initialize the sphere's fields
    if (!get_point(tmp->center, s[1]) || // Set the center
        !diameter_handle(&tmp->diameter, s[2]) || // Set the diameter
        !get_colors(&tmp->color, s[3])) { // Set the color
        free(tmp->center); // Free center if initialization fails
        free(tmp); // Free the sphere if initialization fails
        return (0);
    }

    // Set the next pointer to NULL
    tmp->next = NULL;

    // Add the new sphere to the linked list
    if (*lt == NULL) {
        // If the list is empty, set the new sphere as the head
        *lt = tmp;
    } else {
        // Traverse to the end of the list
        last = *lt;
        while (last->next != NULL) {
            last = last->next;
        }
        // Add the new sphere to the end of the list
        last->next = tmp;
    }

    return (1); // Return 1 on success
}
// int sphere_handle(t_sphere **lt, char **s) {
//     t_sphere *tmp;
//     t_sphere *last;

//     // Allocate memory for the new sphere
//      tmp = malloc(sizeof(t_sphere));
//     if (!tmp)
//         return (0); // Return 0 if allocation fails

//     // Allocate memory for the sphere's center
//     tmp->center = malloc(sizeof(t_tuple));
//     if (!tmp->center) {
//         free(tmp); // Free the sphere if center allocation fails
//         return (0);
//     }

//     // Initialize the sphere's fields
//     if (!get_point(tmp->center, s[1]) || // Set the center
//         !diameter_handle(&tmp->diameter, s[2]) || // Set the diameter
//         !get_colors(&tmp->color, s[3])) { // Set the color
//         free(tmp->center); // Free center if initialization fails
//         free(tmp); // Free the sphere if initialization fails
//         return (0);
//     }

//     // Set the next pointer to NULL
//     tmp->next = NULL;

//     // Add the new sphere to the linked list
//     if (!lt || !*lt) {
//         *lt = tmp;
//         // If the list is empty, set the new sphere as the head
//     } else {
//         // Traverse to the end of the list
//         last = *lt;
//         if(!last)
//         while ((*lt)->next != NULL) {
//             lt = (*lt)->next;
//         }
//         // Add the new sphere to the end of the list
//         (*lt)->next = tmp;
//         (*lt) = last;
//     }

//     return (1); // Return 1 on success
// }

int light_handle(t_light **lt,char **s)
{
    t_light *tmp;
    t_light *last;

    tmp = malloc(sizeof(t_light));
    tmp->next = NULL;
    last = *lt;
    printf("done//\n");
    if(!tmp)
        return(0);
    if(!get_point(&tmp->point,s[1]) || !ratio_check(s[2],&tmp->r) || !get_colors(&tmp->color,s[3]))
        return(0);
        *lt = tmp;
    // else
    // {
    //     while(last != NULL)
    //         last = last->next;
    //     last = tmp;
    // }
    return(1);
    
}
int camera_handle(t_camera **cm,char **s)
{
    // if(c)
    //     return(0);
    // c = malloc(sizeof(t_camera));
    // c->cam_ray = malloc(sizeof(t_ray));
    t_camera *c = *cm;
    c->cam_ray->d = malloc(sizeof(t_tuple));
    c->cam_ray->o = malloc(sizeof(t_tuple));
    c->cam_ray->ud = malloc(sizeof(t_tuple));
    printf("done_hire1\n");
    if(len2d(s) != 4)
        return(printf("done_hire1\n"),0);
    printf("done_hire1\n");
    if(!get_point(c->cam_ray->o,s[1]) || !get_normalizer(c->cam_ray->d,s[2]) || !field_of_view(&c->fov,s[3]))
        return(printf("done_hire2\n"),0);

    printf("done_hire1\n");
    return (1);
}