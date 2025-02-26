/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cylinder_intersection.c                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mthamir <mthamir@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/06 16:18:46 by mthamir           #+#    #+#             */
/*   Updated: 2025/02/16 16:43:24 by mthamir          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minirt.h"

static void	swap(double *a, double *b)
{
	double	tmp;

	tmp = *b;
	*b = *a;
	*a = tmp;
}

void	*intersect_between_bounds(double arr[4], t_ray *r_ob_space, \
								t_cylinder *cyl, t_intersect *ret)
{
	double	in_bounds[2];

	arr[1] = 2.0 * ((r_ob_space->o.x * r_ob_space->d.x) \
			+ (r_ob_space->o.z * r_ob_space->d.z));
	arr[2] = sq(r_ob_space->o.x) + sq(r_ob_space->o.z) - 1;
	arr[3] = sq(arr[1]) - (4.0 * arr[0] * arr[2]);
	if (arr[3] < 0.0)
		return (NULL);
	printf("%f\n", arr[0]);
	ret->t[0] = (-arr[1] - sqrt(arr[3])) / (2.0 * arr[0]);
	ret->t[1] = (-arr[1] + sqrt(arr[3])) / (2.0 * arr[0]);
	if (ret->t[0] > ret->t[1])
		swap(&ret->t[0], &ret->t[1]);
	in_bounds[0] = r_ob_space->o.y + ret->t[0] * r_ob_space->d.y;
	if (!(cyl->min < in_bounds[0] && in_bounds[0] < cyl->max))
		ret->t[0] = -INFINITY;
	in_bounds[1] = r_ob_space->o.y + ret->t[1] * r_ob_space->d.y;
	if (!(cyl->min < in_bounds[1] && in_bounds[1] < cyl->max))
		ret->t[1] = -INFINITY;
	return ("OK");
}

t_intersect	*cyl_intersect(t_ray *r, t_cylinder *cyl)
{
	t_ray		*r_ob_space;
	t_intersect	*ret;
	double		arr[4];

	ret = new_intersect();
	r_ob_space = transform(r, cyl->inverse_m);
	arr[0] = sq(r_ob_space->d.x) + sq(r_ob_space->d.z);
	if (arr[0] > EPSILON)
		if (!intersect_between_bounds(arr, r_ob_space, cyl, ret))
			return (NULL);
	intersect_caps_cyl(cyl, r_ob_space, &ret->t[0], &ret->t[1]);
	ret->object.shape_cyl = *cyl;
	ret->object.type = CYLINDER;
	ret->ray = r_ob_space;
	ret->next = NULL;
	return (ret);
}

static int	check_cap(t_ray *r, double t)
{
	return (((sq((r->o.x + t * r->d.x)) + sq((r->o.z + t * r->d.z))) <= 1));
}

void	intersect_caps_cyl(t_cylinder *cyl, t_ray *r, double *t1, double *t2)
{
	double	t;

	if (fabs(r->d.y) < EPSILON)
		return ;
	t = (cyl->min - r->o.y) / r->d.y;
	if (check_cap(r, t))
	{
		if (*t1 == -INFINITY)
			*t1 = t;
		else if (*t2 == -INFINITY)
			*t2 = t;
	}
	t = (cyl->max - r->o.y) / r->d.y;
	if (check_cap(r, t))
	{
		if (*t1 == -INFINITY)
			*t1 = t;
		else if (*t2 == -INFINITY)
			*t2 = t;
	}
}
