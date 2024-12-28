/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strdup.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yojablao <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/07 17:29:33 by yojablao          #+#    #+#             */
/*   Updated: 2023/11/07 17:30:36 by yojablao         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strdup(const char *s)
{
	int		n;
	char	*ptr;

	n = 0;
	while (s[n])
		n++;
	ptr = (char *)malloc(n + 1);
	if (ptr == NULL)
		return (NULL);
	ft_strlcpy(ptr, s, n + 1);
	return (ptr);
}
