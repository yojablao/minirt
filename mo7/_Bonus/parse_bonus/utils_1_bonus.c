/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils_1_bonus.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mthamir <mthamir@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/06 17:18:26 by mthamir           #+#    #+#             */
/*   Updated: 2025/02/09 16:18:22 by mthamir          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minirt_bonus.h"

bool	ft_strcmp(char *s1, char *s2)
{
	int	i;

	i = 0;
	while (s1[i] || s2[i])
	{
		if (s1[i] != s2[i])
			return (false);
		i++;
	}
	return (true);
}

char	*ft_copy(char *s1, char *s2, int i)
{
	int	j;

	j = 0;
	while (s2[j] != '\0')
		s1[i++] = s2[j++];
	return (s1);
}

int	is_float(char *s)
{
	int	i;
	int	floating_point;

	i = 0;
	floating_point = 0;
	while (*s == 9 || *s == 10 || *s == 11 || *s == 12 || *s == 13 || *s == 32)
		s++;
	if (*s == 45 || *s == 43)
		i++;
	if (!(s[i] >= '0' && s[i] <= '9'))
		return (0);
	while (s[i])
	{
		if (s[i] == '.' && !floating_point && i++)
			floating_point++;
		if (!(s[i] >= '0' && s[i] <= '9'))
			return (0);
		i++;
	}
	return (1);
}

int	ft_strstrlen(char **str)
{
	int	i;

	i = 0;
	while (str && str[i])
		i++;
	return (i);
}
