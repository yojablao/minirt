/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   inverse_2.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mthamir <mthamir@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/06 16:04:12 by mthamir           #+#    #+#             */
/*   Updated: 2025/02/09 18:08:38 by mthamir          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minirt.h"

/* submatrix 2*2 remove a collamn and a row from a 3*3 matrix */

t_2_2	*sub_m2(t_3_3 *a, int row, int col)
{
	t_2_2	*d;
	int		i[4];

	d = ft_malloc (sizeof(t_3_3), 0);
	i[0] = 0;
	i[2] = 0;
	while ((i[0]) < 3 && (i[2]) < 2)
	{
		if (i[0] == row)
			++(i[0]);
		i[1] = 0;
		i[3] = 0;
		while ((i[1]) < 3 && (i[3]) < 2)
		{
			if (i[1] == col)
				++(i[1]);
			d->matrix[i[2]][i[3]] = a->matrix[i[0]][i[1]];
			i[1]++;
			i[3]++;
		}
		i[0]++;
		i[2]++;
	}
	return (d);
}

/* get determinant of 2*2 matrix */
double	det_2(t_2_2 *a)
{
	return (sub(mul(a->matrix[0][0], a->matrix[1][1]), \
		mul(a->matrix[0][1], a->matrix[1][0])));
}
