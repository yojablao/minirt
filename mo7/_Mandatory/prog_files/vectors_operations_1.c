/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   vectors_operations_1.c                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mthamir <mthamir@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/06 15:45:29 by mthamir           #+#    #+#             */
/*   Updated: 2025/02/09 18:09:19 by mthamir          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minirt.h"

t_tuple	*cpv(double x, double y, double z, double p_v)
{
	t_tuple	*a;

	a = ft_malloc(sizeof(t_tuple), 0);
	a->x = x;
	a->y = y;
	a->z = z;
	a->w = p_v;
	return (a);
}

void	ch_pv(t_tuple *a, double x, double y, double z)
{
	a->x = x;
	a->y = y;
	a->z = z;
}

t_tuple	*tpl_o(t_tuple a, t_tuple b, double (*f)(double p1, double p2))
{
	return (cpv(f(a.x, b.x), f(a.y, b.y), f(a.z, b.z), f(a.w, b.w)));
}

/*get the opposite vector if the given is 
from a to b it will return the vector from b to a */
void	opp(t_tuple *a)
{
	a->x *= -1.0;
	a->y *= -1.0;
	a->z *= -1.0;
}

/* normalization its nedded when we have an arbitry
 vector mean a vector that u have the choise where it will goes */
void	normalize(t_tuple *a)
{
	double	v;

	v = magnitude(*a);
	if (!v)
		return ;
	return (ch_pv(a, (a->x / v), (a->y / v), (a->z / v)));
}
