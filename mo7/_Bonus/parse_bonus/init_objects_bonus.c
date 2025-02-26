/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_objects_bonus.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yojablao <yojablao@student.42.ma>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/06 17:30:25 by mthamir           #+#    #+#             */
/*   Updated: 2025/02/25 16:25:22 by yojablao         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minirt_bonus.h"

void	init_spher(char **line, t_rt *rt, int id)
{
	t_spher		*s;
	t_tuple		*crd;
	double		raduis;
	t_matrix	*tr;
	t_color		*col;
	char **bum;
	char **tex;

	if (ft_strstrlen(line) != 4 && ft_strstrlen(line) != 5 && ft_strstrlen(line) != 6)
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
	if(ft_strstrlen(line) == 6 || ft_strstrlen(line) == 5)
	{
		tex = split_line(line[4],':',':');
		if(ft_strcmp(tex[0],"texter") && tex[1])
		{
			printf("%s\n", tex[1]);
			rt->world->object[rt->world->object_count].shape.material->texter = mlx_load_png(tex[1]);
			if(!rt->world->object[rt->world->object_count].shape.material->texter)
				return(print_error(BAD_INFORM_OBJ));
			
		}
		if(line[5])
		{
			bum = split_line(line[5],':',':');
			if(ft_strcmp(bum[0],"bump") && bum[1]  && ft_strstrlen(line) == 6)
			{
				printf("cccc%s\n", bum[1]);
				printf("hire */n");
				rt->world->object[rt->world->object_count].shape.material->bump_scale = 1;
				rt->world->object[rt->world->object_count].shape.material->bump_map = mlx_load_png(bum[1]);
				if(!rt->world->object[rt->world->object_count].shape.material->bump_map)
					return(print_error(BAD_INFORM_OBJ));
			}
		}
	}
	rt->world->object[rt->world->object_count].shape.material->color = *col;
	rt->world->object_count++;
}

void	init_checker(t_plane *pl, char *scl, char *line)
{
	char **lines;

	lines = split_line(line, ':', ':');
	if (ft_strstrlen(lines) != 2)
		return (print_error(BAD_INFORM_OBJ));
	pl->material->checker = char_to_double(scl);
	pl->material->pattern_color = *char_to_color(lines[1]);
}

void	init_plane(char **line, t_rt *rt, int id)
{
	t_color		*col;
	t_tuple		*normal;
	t_tuple		*point;
	t_matrix	*tr;
	int			len;

	tr = i_mat(1.0);
	len = ft_strstrlen(line);
	if (len != 4 && len != 6)
		return (print_error(BAD_INFORM_OBJ));
	col = char_to_color(line[3]);
	normal = char_to_vec(line[2], 0);
	normalize(normal);
	point = char_to_vec(line[1], 1);
	rt->world->object[rt->world->object_count].type = PLANE;
	rt->world->object[rt->world->object_count].shape_pl = *plane(id, \
	mul_mat(transl_mat(point->x, point->y, point->z), get_rotat_matrice(normal)));
	if (len == 6)
		init_checker(&rt->world->object[rt->world->object_count].shape_pl, line[4], line[5]);
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
