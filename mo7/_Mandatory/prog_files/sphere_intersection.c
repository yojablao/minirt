/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sphere_intersection.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mthamir <mthamir@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/06 16:07:55 by mthamir           #+#    #+#             */
/*   Updated: 2025/02/16 16:46:35 by mthamir          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minirt.h"

/* get the element of the quadratiq equation */
static double	*eq_inter(t_ray *ray1, double arr[])
{
	arr[0] = dot_p(ray1->d, ray1->d);
	arr[1] = 2.0 * (dot_p(ray1->o, ray1->d));
	arr[2] = (dot_p(ray1->o, ray1->o) - 1);
	arr[3] = sq(arr[1]) - (4.0 * (arr[0] * arr[2]));
	return (arr);
}

/* check intersection between a ray and a spher */
t_intersect	*intersect(t_ray *ray, t_spher *sph)
{
	t_intersect	*inter;
	t_ray		*ray1;
	double		arr[6];

	ray1 = transform(ray, sph->inverse_m);
	eq_inter(ray1, arr);
	inter = new_intersect();
	if (!inter || arr[3] < EPSILON)
		return (NULL);
	arr[4] = (2 * (arr[0]));
	arr[5] = sqrt(arr[3]);
	inter->t[0] = (-arr[1] - arr[5]) / arr[4];
	inter->t[1] = (-arr[1] + arr[5]) / arr[4];
	inter->object.type = SPHER;
	inter->object.shape = *sph;
	inter->ray = ray1;
	inter->next = NULL;
	return (inter);
}
