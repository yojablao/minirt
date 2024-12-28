/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memmove.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yojablao <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/06 23:23:11 by yojablao          #+#    #+#             */
/*   Updated: 2023/12/07 09:49:08 by yojablao         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	*ft_memmove(void *str1, const void *str2, size_t n)
{
	size_t		i;
	char		*p2;
	char		*p1;

	p1 = (char *)str1;
	p2 = (char *)str2;
	if (p1 > p2)
	{
		i = n;
		while (i--)
			p1[i] = p2[i];
	}
	else
		p1 = ft_memcpy(p1, p2, n);
	return (p1);
}
