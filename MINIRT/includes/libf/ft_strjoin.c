/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strjoin.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yojablao <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/11 04:32:23 by yojablao          #+#    #+#             */
/*   Updated: 2023/12/01 05:24:01 by yojablao         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strjoin(char const *s1, char const *s2)
{
	size_t	lp;
	size_t	lc;
	char	*p;

	if (s1 && !s2)
		return ((char *) s1);
	if (!s1 && s2)
		return ((char *) s2);
	if (!s1 || !s2)
		return (NULL);
	lc = ft_strlen(s2);
	lp = ft_strlen(s1);
	p = (char *)malloc(lp + lc + 1);
	if (p == NULL)
		return (NULL);
	ft_strlcpy (p, s1, lp +1);
	ft_strlcat (p, s2, (lc + lp +1));
	return (p);
}
