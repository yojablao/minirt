/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   error_bonus.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mthamir <mthamir@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/06 17:31:41 by mthamir           #+#    #+#             */
/*   Updated: 2025/02/16 12:35:34 by mthamir          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minirt_bonus.h"

void	print_error(char *error)
{
	int	i;

	i = 0;
	write (2, "Error\n", sizeof("Error\n"));
	while (error[i])
		write (2, &error[i++], 1);
	write (2, "\n", 1);
	ft_malloc(0, FREE);
}


void	*ft_malloc(size_t size, int flag)
{
	static t_pool	head;
	void			*ret;

	if (flag == FREE)
	{
		free(head.block);
		exit(0);
	}
	if (flag == INIT)
		head.block = malloc (BLOCK_SIZE);
	if (head.offset + size > BLOCK_SIZE)
		return (print_error(MALLOC_FAILS), ft_malloc(0, FREE), NULL);
	ret = head.block + head.offset;
	head.offset +=  size;
	return (ret);
}