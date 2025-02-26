/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_objects.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yojablao <yojablao@student.42.ma>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/06 17:30:25 by mthamir           #+#    #+#             */
/*   Updated: 2025/02/24 18:43:54 by yojablao         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minirt.h"

void	init_spher(char **line, t_rt *rt, int id)
{
	t_spher		*s;
	t_tuple		*crd;
	double		raduis;
	t_matrix	*tr;
	t_color		*col;
	char	**tex;

	if (ft_strstrlen(line) != 4 && ft_strstrlen(line) != 5)
		return (print_error(BAD_INFORM_OBJ));
	if (!is_float(line[2]))
		return (print_error(INVALID_SPHERE_RD));
	raduis = char_to_double(line[2]) / 2.0;
	crd = char_to_vec(line[1], 1);
	col = char_to_color(line[3]);
	rt->world->object[rt->world->object_count].type = SPHER;
	tr = mul_mat(transl_mat(crd->x, crd->y, crd->z), \
		scal_mat(raduis, raduis, raduis));
	rt->world->object[rt->world->object_count].shape = \
		*spher(cpv(0, 0, 0, 1), 1, id, tr);

	
	rt->world->object[rt->world->object_count].shape.material->color = *col;
	rt->world->object_count++;
}

void	init_plane(char **line, t_rt *rt, int id)
{
	t_color		*col;
	t_tuple		*normal;
	t_tuple		*point;
	t_matrix	*tr;

	tr = i_mat(1.0);
	if (ft_strstrlen(line) != 4)
		return (print_error(BAD_INFORM_OBJ));
	col = char_to_color(line[3]);
	normal = char_to_vec(line[2], 0);
	normalize(normal);
	point = char_to_vec(line[1], 1);
	rt->world->object[rt->world->object_count].type = PLANE;
	rt->world->object[rt->world->object_count].shape_pl = *plane(id, \
		mul_mat(transl_mat(point->x, point->y, point->z), \
		get_rotat_matrice(normal)));
	rt->world->object[rt->world->object_count].shape_pl.material->color = *col;
	rt->world->object_count++;
}

void	init_cylinder(char **line, t_rt *rt, int id)
{
	t_tuple		*centre;
	t_tuple		*normal;
	t_matrix	*tr;
	double		arr[4];
	t_color		*col;

	if (ft_strstrlen(line) != 6)
		return (print_error(INVALID_CYL_DATA));
	centre = char_to_vec(line[1], 1);
	normal = char_to_vec(line[2], 0);
	normalize(normal);
	if (!is_float(line[3]) || !is_float(line[4]))
		return (print_error(INVALID_CYL_DATA));
	arr[0] = char_to_double(line[3]) / 2.0;
	arr[1] = char_to_double(line[4]) / 2.0;
	arr[2] = -arr[1];
	arr[3] = arr[1];
	col = char_to_color(line[5]);
	rt->world->object[rt->world->object_count].type = CYLINDER;
	tr = mul_mat(mul_mat(transl_mat(centre->x, centre->y, centre->z), get_rotat_matrice(normal)), scal_mat(arr[0], 1, arr[0]));
	rt->world->object[rt->world->object_count].shape_cyl = \
		*cylinder((arr + 2), id, tr);
	rt->world->object[rt->world->object_count].shape_cyl.material->color = *col;
	rt->world->object_count++;
}
