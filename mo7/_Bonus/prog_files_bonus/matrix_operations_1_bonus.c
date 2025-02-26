/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   matrix_operations_1_bonus.c                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mthamir <mthamir@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/06 15:58:46 by mthamir           #+#    #+#             */
/*   Updated: 2025/02/16 12:27:36 by mthamir          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minirt_bonus.h"

/*helper function that help multiplying two matrixs */
static double	get(t_matrix *a, t_matrix *b, int row, int col)
{
	double	result;
	int		i;

	result = 0;
	i = -1;
	while (++i < 4)
		result += (a->matrix[row][i] * b->matrix[i][col]);
	return (result);
}

/*multiplying two matrixs gives another matrix */
t_matrix	*mul_mat(t_matrix *a, t_matrix *b)
{
	int			i;
	int			j;
	t_matrix	*ret;

	i = -1;
	ret = i_mat(0.0);
	while (++i < 4)
	{
		j = -1;
		while (++j < 4)
			ret->matrix[i][j] = get(a, b, i, j);
	}
	return (ret);
}

/* multipling a matrix by  tuple creat another tuple */
t_tuple	*tup_mat_mul(t_matrix *mtx, t_tuple *tpl)
{
	return (cpv((mtx->matrix[0][0] * tpl->x) + (mtx->matrix[0][1] * tpl->y) + \
	(mtx->matrix[0][2] * tpl->z) + (mtx->matrix[0][3] * tpl->w), \
	(mtx->matrix[1][0] * tpl->x) + (mtx->matrix[1][1] * tpl->y) + \
	(mtx->matrix[1][2] * tpl->z) + (mtx->matrix[1][3] * tpl->w), \
	(mtx->matrix[2][0] * tpl->x) + (mtx->matrix[2][1] * tpl->y) + \
	(mtx->matrix[2][2] * tpl->z) + (mtx->matrix[2][3] * tpl->w), \
	(mtx->matrix[3][0] * tpl->x) + (mtx->matrix[3][1] * tpl->y) + \
	(mtx->matrix[3][2] * tpl->z) + (mtx->matrix[3][3] * tpl->w)));
}

static t_matrix	*get_final(t_matrix *tr, t_matrix *cr, double beta)
{
	t_matrix	*final;
	int			i;

	final = i_mat(1.0);
	i = 0;
	while (i < 4)
	{
		final->matrix[i][0] = final->matrix[i][0] + ((1 - cos(beta)) * \
		tr->matrix[i][0]) + cr->matrix[i][0];
		final->matrix[i][1] = final->matrix[i][1] + ((1 - cos(beta)) * \
		tr->matrix[i][1]) + cr->matrix[i][1];
		final->matrix[i][2] = final->matrix[i][2] + ((1 - cos(beta)) * \
		tr->matrix[i][2]) + cr->matrix[i][2];
		final->matrix[i][3] = final->matrix[i][3] + ((1 - cos(beta)) * \
		tr->matrix[i][3]) + cr->matrix[i][3];
		i++;
	}
	return (final);
}

t_matrix	*get_rotat_matrice(t_tuple *normal)
{
	t_tuple		*r;
	t_tuple		*axe;
	t_matrix	*cr;
	t_matrix	*tr;
	double		beta;

	r = cpv(0.0, 1.0, 0.0, 0.0);
	axe = cross_p(*r, *normal);
	normalize(axe);
	beta = acos(dot_p(*r, *normal));
	cr = i_mat(0.0);
	cr->matrix[0][1] = (-axe->z);
	cr->matrix[1][0] = axe->z;
	cr->matrix[1][2] = -axe->x;
	cr->matrix[2][1] = axe->x;
	tr = mul_mat(cr, cr);
	cr->matrix[0][1] = sin(beta) * (-axe->z);
	cr->matrix[1][0] = sin(beta) * axe->z;
	cr->matrix[1][2] = sin(beta) * -axe->x;
	cr->matrix[2][1] = sin(beta) * axe->x;
	return (get_final(tr, cr, beta));
}
