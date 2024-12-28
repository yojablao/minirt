/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strtrim.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yojablao <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/11 04:30:16 by yojablao          #+#    #+#             */
/*   Updated: 2023/12/08 13:20:33 by yojablao         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static int	find_front(char const *set, char c)
{
	int	i;

	i = 0;
	while (set[i])
	{
		if (set[i] == c)
			return (1);
		i++;
	}
	return (0);
}

static int	find_back(const char *set, const char *s1, int i)
{
	int	l;

	l = ft_strlen(s1) - 1;
	while (i <= l && find_front (set, s1[l]) == 1)
		l--;
	return (l);
}

char	*ft_strtrim(char const *s1, char const *set)
{
	int		i;
	int		l;
	char	*p;
	int		k;

	i = 0;
	k = 0;
	if (!s1 || !set)
		return (NULL);
	while (s1[i] && find_front(set, s1[i]))
		i++;
	l = find_back(set, s1, i);
	p = malloc((l - i) + 2);
	if (p == 0)
		return (NULL);
	while (l >= i)
	{
		p[k] = s1[i];
		k++;
		i++;
	}
	p[k] = '\0';
	return (p);
}
