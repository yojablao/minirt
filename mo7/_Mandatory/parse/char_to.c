/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   char_to.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mthamir <mthamir@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/06 17:25:23 by mthamir           #+#    #+#             */
/*   Updated: 2025/02/09 18:07:43 by mthamir          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minirt.h"

t_tuple	*char_to_vec(char *cam_line, int type)
{
	char	**cord;
	double	arr[3];
	int		i;

	i = 0;
	cord = split_line(cam_line, ',', ',');
	if (ft_strstrlen(cord) != 3)
		return (print_error(INVALID_CORD), NULL);
	while (cord && cord[i])
	{
		if (is_float(cord[i]))
			arr[i] = char_to_double(cord[i]);
		i++;
	}
	return (cpv(arr[0], arr[1], arr[2], type));
}

t_color	*char_to_color(char *s)
{
	char	**col;
	double	arr[3];
	int		i;

	i = 0;
	col = split_line(s, ',', ',');
	if (ft_strstrlen(col) != 3)
		return (print_error(INVALID_CORD), NULL);
	while (col && col[i])
	{
		if (is_float(col[i]))
			arr[i] = char_to_double(col[i]);
		i++;
	}
	return (new_color ((arr[0] / 255.0), (arr[1] / 255.0), (arr[2] / 255.0)));
}

double	char_to_double(char *s)
{
	double	result;
	double	sign;
	int		i;
	double	check_floating_point;

	result = 0.0;
	sign = 1.0;
	i = 0;
	check_floating_point = 0;
	while (*s == 9 || *s == 10 || *s == 11 || *s == 12 || *s == 13 || *s == 32)
		s++;
	if (*s == 45 || *s == 43)
		if (*s++ == 45)
			sign *= -1.0;
	while ((*s >= '0' && *s <= '9') || (*s == '.' && !check_floating_point))
	{
		if (*s == '.' && s++)
			check_floating_point = 1;
		result = (result * 10.0) + (*s - 48);
		if (check_floating_point)
			i++;
		s++;
	}
	return ((result * sign / pow(10.0, (double)(i))));
}
