/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memcpy.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yojablao <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/06 23:13:47 by yojablao          #+#    #+#             */
/*   Updated: 2023/11/06 23:15:44 by yojablao         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	*ft_memcpy(void *to, const void *fr, size_t n)
{
	size_t	i;

	i = 0;
	if (!fr && !to)
		return (NULL);
	if (to == fr)
		return (to);
	while (i < n)
	{
		((char *)to)[i] = ((char *)fr)[i];
		i++;
	}
	return (to);
}
