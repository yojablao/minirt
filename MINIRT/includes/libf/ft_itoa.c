/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_itoa.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yojablao <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/11 20:22:51 by yojablao          #+#    #+#             */
/*   Updated: 2023/12/07 06:19:24 by yojablao         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static int	size(long long n)
{
	int	i;

	i = 0;
	if (n <= 0)
		i = 1;
	while (n != 0)
	{
		n /= 10;
		i++;
	}
	return (i);
}

char	*ft_itoa(int n)
{
	int			i;
	char		*p;
	long long	num;

	i = size(n);
	p = (char *)malloc(i + 1);
	if (!p)
		return (NULL);
	p[i] = '\0';
	num = n;
	if (num < 0)
	{
		p[0] = '-';
		num = -num;
	}
	if (num == 0)
		p[0] = '0';
	while (num > 0)
	{
		p[--i] = num % 10 + '0';
		num /= 10;
	}
	return (p);
}
