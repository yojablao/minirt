/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check_identfier.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mthamir <mthamir@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/06 17:27:52 by mthamir           #+#    #+#             */
/*   Updated: 2025/02/09 18:07:48 by mthamir          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minirt.h"

void	parse_init_structs(t_line *l, t_rt *rt)
{
	int		i;
	char	**line;

	i = 0;
	while (i < l->count)
	{
		line = split_line(l->line[i], 32, 9);
		if (line && line[0])
			init_struct(line, rt);
		i++;
	}
}

void	init_struct(char **line, t_rt *rt)
{
	static int	check_identifier[3];
	static int	num_obj;
	int			i;

	i = 0;
	check_identifier[0] = 0;
	check_identifier[1] = 0;
	check_identifier[2] = 0;
	if (ft_strcmp(line[0], "C"))
	{
		init_camera(line, check_identifier[0], rt);
		(check_identifier[0])++;
	}
	else if (ft_strcmp(line[0], "A"))
	{
		init_ambiant(line, check_identifier[1], rt);
		(check_identifier[1])++;
	}
	else if (ft_strcmp(line[0], "L"))
	{
		init_light(line, check_identifier[2], rt);
		(check_identifier[2])++;
	}
	else
		init_objects(line, rt, num_obj);
}

void	init_objects(char **line, t_rt *rt, int num_obj)
{
	static int	arr[3];

	if (ft_strcmp("sp", line[0]))
	{
		init_spher(line, rt, arr[0]);
		(arr[0])++;
	}
	else if (ft_strcmp("pl", line[0]))
	{
		init_plane(line, rt, arr[1]);
		(arr[1])++;
	}
	else if (ft_strcmp("cy", line[0]))
	{
		init_cylinder(line, rt, arr[2]);
		(arr[2])++;
	}
	else
		return (print_error(INDEFINED_OBJECT));
}
