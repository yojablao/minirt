/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lighting.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mthamir <mthamir@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/06 16:35:03 by mthamir           #+#    #+#             */
/*   Updated: 2025/02/16 17:30:08 by mthamir          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minirt.h"

t_light	*light_source(t_tuple *position, t_color *color)
{
	t_light	*light;

	light = ft_malloc(sizeof(t_light), 0);
	light->position = *position;
	light->color = *color;
	return (light);
}

t_material	*material(void)
{
	t_material	*mate;

	mate = ft_malloc(sizeof(t_material), 0);
	return (mate);
}

t_color	*shade_hit(t_world *w, t_comps *comp)
{
	t_material	*m;
	t_color *ambiant;
	t_color *diffuse;

	if (!comp)
		return (new_color(0, 0, 0));
	if (comp->object.type == SPHER)
		m = comp->object.shape.material;
	else if (comp->object.type == PLANE)
		m = comp->object.shape_pl.material;
	else if (comp->object.type == CYLINDER)
		m = comp->object.shape_cyl.material;
	ambiant = colors_operation(w->ambiant_color, &m->color, mul);
	if (comp->shadow)
		return (ambiant);
	diffuse = compute_lightning(m, w->light, comp->point, comp->normalv);
	if (!diffuse)
		return (ambiant);
	return (colors_operation(diffuse, ambiant, add));
}

t_color	*compute_lightning(t_material *m, \
				t_light *light, t_tuple *pos, t_tuple *normalv)
{
	t_color	*effective_color;
	t_color	*diffuse;
	t_tuple	*lightv;
	double	light_dot_normal;

	diffuse = NULL;
	effective_color = colors_operation(&light->color, &m->color, mul);
	lightv = tpl_o(light->position, *pos, sub);
	normalize(lightv);
	light_dot_normal = dot_p(*lightv,*normalv);
	if (light_dot_normal >= 0.0)
		diffuse = color_s_mul(effective_color, light_dot_normal);
	return (diffuse);
}

t_intersect	*new_intersect(void)
{
	t_intersect	*ret;

	ret = ft_malloc(sizeof(t_intersect), 0);
	ret->next = NULL;
	return (ret);
}
