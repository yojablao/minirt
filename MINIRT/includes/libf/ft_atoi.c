/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_atoi.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yojablao <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/06 20:50:26 by yojablao          #+#    #+#             */
/*   Updated: 2023/11/06 20:50:41 by yojablao         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static int	signe(const char *str, int *c)
{
	int	sign;
	int	i;

	i = 0;
	sign = 1;
	while (str[i] == 32 || (str[i] >= 9 && str[i] <= 13))
		i++;
	if (str[i] == '-')
	{
		sign = -1;
		i++;
	}
	else if (str[i] == '+')
		i++;
	*c = i;
	return (sign);
}

int	ft_atoi(const char *str)
{
	int					i;
	int					sign;
	long				result;
	long				test;
	long				holder;

	sign = signe(str, &i);
	result = 0;
	while (ft_isdigit(str[i]))
	{
		test = result;
		result *= 10;
		result += str[i] - '0';
		holder = result / 10;
		if (holder == test)
			i++;
		else
		{
			if (sign < 0)
				return (0);
			else
				return (-1);
		}
	}
	return (result * sign);
}
