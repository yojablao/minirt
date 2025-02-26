/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_camera.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mthamir <mthamir@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/06 17:29:38 by mthamir           #+#    #+#             */
/*   Updated: 2025/02/09 18:07:55 by mthamir          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minirt.h"

void	init_camera(char **line, int exist, t_rt *rt)
{
	double	fov;
	t_tuple	*ori;


	if (exist)
		return (print_error(DUPLICAT_CAM));
	if (ft_strstrlen(line) != 4)
		return (print_error(BAD_INFORM_CAM));
	if (!is_float(line[3]))
		return (print_error(INVALID_FOV));
	fov = char_to_double(line[3]);
	ori = char_to_vec(line[1], 1);
	if (!(fov >= 0.0 && fov <= 180.0))
		return (print_error(INVALID_FOV));
	rt->cam = new_camera(1000, 600, radians(fov), \
		view_transformation (ori, char_to_vec(line[2], 1), cpv(0, 1, 0, 0)));
	rt->cam->origine = ori;
}
