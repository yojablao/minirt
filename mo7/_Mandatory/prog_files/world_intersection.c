/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   world_intersection.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mthamir <mthamir@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/06 16:31:21 by mthamir           #+#    #+#             */
/*   Updated: 2025/02/09 18:09:26 by mthamir          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minirt.h"

static void	add_to_list(t_intersect **head, t_intersect *new)
{
	static t_intersect	*tmp;

	if (!*head)
	{
		*head = new;
		tmp = *head;
	}
	else
	{
		tmp->next = new;
		tmp = tmp->next;
	}
}

t_intersect	*world_intersection(t_world *world, t_ray *r)
{
	t_intersect	*head;
	t_intersect	*inter;
	int			i;

	i = 0;
	inter = NULL;
	head = NULL;
	while (i < world->object_count)
	{
		if (world->object[i].type == SPHER)
			inter = intersect(r, &world->object[i].shape);
		else if (world->object[i].type == PLANE)
			inter = pl_intersect(r, &world->object[i].shape_pl);
		else if (world->object[i].type == CYLINDER)
			inter = cyl_intersect(r, &world->object[i].shape_cyl);
		if (inter)
			add_to_list(&head, inter);
		i++;
	}
	return (get_first_intersect(head, r));
}

t_intersect	*get_first_intersect(t_intersect *list, t_ray *r)
{
	t_intersect	*tmp;
	t_intersect	*ret;

	ret = new_intersect();
	tmp = list;
	ret->ray = r;
	ret->t[0] = HUGE_VAL;
	while (tmp)
	{
		if (hit(tmp->t))
		{
			tmp->t[0] = get_closest(tmp->t);
			if (tmp->t[0] < ret->t[0])
			{
				ret->t[0] = tmp->t[0];
				ret->object = tmp->object;
			}
		}
		tmp = tmp->next;
	}
	if (ret->t[0] == HUGE_VAL)
		return (NULL);
	return (ret);
}

double	get_closest(double *t)
{
	if (t[0] < EPSILON)
		return (t[1]);
	else if (t[1] < EPSILON)
		return (t[0]);
	return (fmin(t[0], t[1]));
}

double	hit(double *arr)
{
	return (!(arr[0] < EPSILON && arr[1] < EPSILON));
}
