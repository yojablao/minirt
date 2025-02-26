/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   prepare_computing_bonus.c                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yojablao <yojablao@student.42.ma>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/06 16:38:09 by mthamir           #+#    #+#             */
/*   Updated: 2025/02/24 20:52:54 by yojablao         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minirt_bonus.h"

t_comps	*new_comps(void)
{
	return (ft_malloc(sizeof(t_comps), 0));
}

bool	in_shadow(t_world *w, t_comps *comp, int i)
{
	t_tuple		*shadow_ray;
	t_intersect	*inter;
	t_ray		*r1;
	double		distance;

	shadow_ray = tpl_o(w->light[i].position, *comp->point, sub);
	distance = magnitude(*shadow_ray);
	comp->shadow = false;
	normalize(shadow_ray);
	r1 = ray(*comp->point ,*shadow_ray);
	inter = world_intersection(w, r1);
	if (inter && ( distance - inter->t[0] ) > 0.001)
		return (true);
	return (false);
}

void	is_sphere(t_comps *comp)
{
	comp->normalv = normal_at(&comp->object.shape, scalar(*comp->point ,comp->scaler_b));
	if (dot_p(*comp->normalv, *comp->eyev) < EPSILON)
	{
		comp->inside = true;
		opp(comp->normalv);
	}
	else
		comp->inside = false;
}

t_comps	*prepare_computing(t_intersect *list, t_ray *r, t_world *w)
{
	t_comps	*comp;

	if (!list)
		return (NULL);
	comp = new_comps();
	comp->t = list->t[0];
	comp->object = list->object;
	comp->point = position(r, comp->t);
	comp->eyev = &r->d;
	opp(comp->eyev);
	if (comp->object.type == SPHER)
	{
		if(comp->object.shape.material->bump_map)
			 comp->scaler_b = bump_maping(comp->object.shape.material,&comp->object.shape,comp);
		else
			 comp->scaler_b = 1;
		is_sphere(comp);
	}
	else if (comp->object.type == PLANE)
		comp->normalv = list->object.shape_pl.normalv;
	else if (comp->object.type == CYLINDER)
	{
		comp->normalv = normal_at_cyl(&comp->object.shape_cyl, comp->point);
		if (dot_p(*comp->normalv, *comp->eyev) <= 0.0)
			opp(comp->normalv);
	}
	return (comp);
}
