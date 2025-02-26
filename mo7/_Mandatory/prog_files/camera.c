/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   camera.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mthamir <mthamir@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/06 16:29:53 by mthamir           #+#    #+#             */
/*   Updated: 2025/02/16 16:55:57 by mthamir          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minirt.h"

t_world	*world(void)
{
	t_world *ret;

	ret = ft_malloc(sizeof(t_world), 0);
	ret->object_count = 0;
	ret->ambiant_color = NULL;
	return (ret);
}

t_camera	*new_camera(double hsize, double vsize, double fov, t_matrix *tr)
{
	t_camera	*cam;
	double		half_view;

	half_view = 0;
	cam = ft_malloc(sizeof(t_camera), 0);
	half_view = tan(fov / 2);
	cam->aspect_ratio = hsize / vsize;
	if (cam->aspect_ratio >= 1.0)
	{
		cam->half_width = half_view;
		cam->half_hight = half_view / cam->aspect_ratio;
	}
	else
	{
		cam->half_width = half_view * cam->aspect_ratio;
		cam->half_hight = half_view;
	}
	cam->horizontal_size = hsize;
	cam->pixel_size = (cam->half_width * 2) / cam->horizontal_size;
	cam->vertical_size = vsize;
	cam->field_of_view = fov;
	cam->transform = tr;
	cam->transform_inverse = inverse(tr);
	return (cam);
}

t_matrix	*view_transformation(t_tuple *from, t_tuple *to, t_tuple *up)
{
	t_matrix	*ret;
	t_tuple		*left;
	t_tuple		*true_up;

	to->w = 0;
	normalize(up);
	normalize(to);
	left = cross_p(*to, *up);
	true_up = cross_p(*left, *to);
	ret = i_mat(1.0);
	ret->matrix[0][0] = left->x;
	ret->matrix[0][1] = left->y;
	ret->matrix[0][2] = left->z;
	ret->matrix[1][0] = true_up->x;
	ret->matrix[1][1] = true_up->y;
	ret->matrix[1][2] = true_up->z;
	ret->matrix[2][0] = -to->x;
	ret->matrix[2][1] = -to->y;
	ret->matrix[2][2] = -to->z;
	return (mul_mat(ret, transl_mat(-from->x, -from->y, -from->z)));
}
