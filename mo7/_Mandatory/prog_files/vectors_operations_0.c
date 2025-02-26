/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   vectors_operations_0.c                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mthamir <mthamir@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/06 15:48:26 by mthamir           #+#    #+#             */
/*   Updated: 2025/02/09 18:09:16 by mthamir          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minirt.h"

/* if "a" and "b" are vector the dot product is "a"."b" return a number 
wec need it to ompare the direction of the two vectors */
/* if the two vectors are unit theire dot 
product is actually the cosine of the ongle between them */
double	dot_p(t_tuple a, t_tuple b)
{
	return ((a.x * b.x) + (a.y * b.y) + (a.z * b.z));
}

/* cross product if "a" and "b" are vector 
the cross product is "a"^"b" return another vector
that is perpendicular to both of the original vectors. */
t_tuple	*cross_p(t_tuple a, t_tuple b)
{
	return (cpv(((a.y * b.z) - (a.z * b.y)), \
	((a.z * b.x) - (a.x * b.z)), ((a.x * b.y) - (a.y * b.x)), 0));
}

/* change from degrees to radians */
double	radians(double degrees)
{
	return ((degrees / 180) * 3.14159265);
}

/*we use scalar for dividing or multiplying 
a vector by a number called scalar*/
t_tuple	*scalar(t_tuple a, double scalar)
{
	return (cpv(mul(a.x, scalar), mul(a.y, scalar), mul(a.z, scalar), a.w));
}

/* magnitude or distance of a given vector */
double	magnitude(t_tuple a)
{
	return (sqrt((sq(a.x) + sq(a.y) + sq(a.z))));
}
