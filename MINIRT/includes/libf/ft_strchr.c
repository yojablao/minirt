/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strchr.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yojablao <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/07 17:26:40 by yojablao          #+#    #+#             */
/*   Updated: 2023/11/07 17:28:49 by yojablao         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strchr(const char *str, int find)
{
	while (*str)
	{
		if (*str == (char)find)
			return ((char *)str);
		str++;
	}
	if (*str == (char)find)
		return ((char *)str);
	return (NULL);
}
