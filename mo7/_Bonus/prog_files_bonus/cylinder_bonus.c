/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cylinder_bonus.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yojablao <yojablao@student.42.ma>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/06 16:16:09 by mthamir           #+#    #+#             */
/*   Updated: 2025/02/22 21:26:40 by yojablao         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minirt_bonus.h"

t_cylinder	*cylinder(double *trunc, int id, t_matrix *tr)
{
	t_cylinder	*cyl;

	cyl = ft_malloc(sizeof(t_cylinder), 0);
	cyl->id = id;
	cyl->min = trunc[0];
	cyl->max = trunc[1];
	cyl->material = material();
	cyl->transform = tr;
	cyl->inverse_m = inverse(tr);
	cyl->transpose_inverse = transpose(cyl->inverse_m);
	return (cyl);
}

t_tuple	*normal_at_cyl(t_cylinder *cyl, t_tuple *p_)
{
	t_tuple	*n_obj_space;
	t_tuple	*p;
	double	dist;
	t_tuple	*n_world_space;

	p = tup_mat_mul(cyl->inverse_m, p_);
	n_obj_space = cpv(p->x, 0, p->z, 0);
	dist = sq(p->x) + sq(p->z);
	if (dist < 1.0 && p->y >= (cyl->max - EPSILON))
		ch_pv(n_obj_space, 0, 1, 0);
	else if (dist < 1.0 && p->y <= (cyl->min + EPSILON))
		ch_pv(n_obj_space, 0, -1, 0);
	n_world_space = tup_mat_mul(cyl->transpose_inverse, n_obj_space);
	normalize(n_world_space);
	return (n_world_space);
}
