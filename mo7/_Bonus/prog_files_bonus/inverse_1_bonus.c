/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   inverse_1_bonus.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mthamir <mthamir@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/06 16:02:53 by mthamir           #+#    #+#             */
/*   Updated: 2025/02/09 16:18:22 by mthamir          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minirt_bonus.h"

t_3_3	*sub_m3(t_matrix *a, int row, int col)
{
	t_3_3	*d;
	int		arr[4];

	d = ft_malloc (sizeof(t_3_3), 0);
	arr[0] = 0;
	arr[1] = 0;
	while (arr[0] < 4 && !(arr[0] == row && row == 3))
	{
		if (arr[0] == row && row < 3)
			(arr[0])++;
		arr[2] = 0;
		arr[3] = 0;
		while (arr[2] < 4 && !(arr[2] == col && col == 3))
		{
			if (arr[2] == col && col < 3)
				(arr[2])++;
			d->matrix[arr[1]][arr[3]] = a->matrix[arr[0]][arr[2]];
			(arr[3])++;
			(arr[2])++;
		}
		(arr[0])++;
		(arr[1])++;
	}
	return (d);
}

/* is the determinant of a 3*3 submatrix after removing a row and col */
double	ft_minor(t_3_3 *a, int row, int col)
{
	return (det_2(sub_m2(a, row, col)));
}

/* get the cofactor sign depending on 
the case the row and col removed share in the matrix */
double	cof_sign(int r, int c)
{
	if ((!(r % 2) && (c % 2)) || ((r % 2) && (!(c % 2))))
		return (-1);
	return (1);
}
/* gettin the cofactor of the 3*3 matrix */

double	cof_3(t_3_3 *a, int row, int col )
{
	return ((ft_minor(a, row, col) * cof_sign(row, col)));
}
