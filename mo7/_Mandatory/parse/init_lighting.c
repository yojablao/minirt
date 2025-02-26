/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_lighting.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mthamir <mthamir@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/06 17:28:53 by mthamir           #+#    #+#             */
/*   Updated: 2025/02/09 18:07:58 by mthamir          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minirt.h"

void	init_light(char **line, int exist, t_rt *rt)
{
	double	light_ratio;
	t_color	*light_col;
	t_tuple	*pos;

	if (exist)
		return (print_error(DUPLICAT_LIGHT));
	if (ft_strstrlen(line) != 3)
		return (print_error(BAD_INFORM_LIGHT));
	if (!is_float(line[2]))
		return (print_error(INVALID_AMB_R));
	pos = char_to_vec(line[1], 1);
	light_ratio = char_to_double(line[2]);
	if (!(light_ratio >= 0.0 && light_ratio <= 1.0))
		return (print_error(INVALID_AMB_R));
	light_col = new_color(light_ratio, light_ratio, light_ratio);
	rt->world->light = light_source(pos, light_col);
}

void	init_ambiant(char **line, int exist, t_rt *rt)
{
	double	amb_ratio;
	t_color	*ambiant;

	if (exist)
		return (print_error(DUPLICAT_AMB));
	if (!is_float(line[1]))
		return (print_error(INVALID_AMB_R));
	amb_ratio = char_to_double(line[1]);
	if (!(amb_ratio >= 0.0 && amb_ratio <= 1.0))
		return (print_error(INVALID_AMB_R));
	ambiant = char_to_color(line[2]);
	rt->world->ambiant_color = color_s_mul(ambiant, amb_ratio);
}
