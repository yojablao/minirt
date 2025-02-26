/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   split.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mthamir <mthamir@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/06 17:20:28 by mthamir           #+#    #+#             */
/*   Updated: 2025/02/09 18:08:06 by mthamir          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minirt.h"

static int	count_double_array_size(const char *s, char c, char c1)
{
	int	i;
	int	count;

	count = 0;
	i = 0;
	while (s[i] != '\0')
	{
		while (s[i] == c || s[i] == c1)
			i++;
		if (s[i] != '\0' && s[i] != c && s[i] != c1)
			count++;
		while (s[i] != '\0' && s[i] != c && s[i] != c1)
			i++;
	}
	return (count);
}

static int	count_single_array_size(const char *s, char c, char c1)
{
	int	j;

	j = 0;
	while (s[j] != c && s[j] != c1 && s[j] != '\0')
		j++;
	return (j);
}

char	**split_line(char *s, char c, char c1)
{
	int		i[4];
	char	**str;

	if (!s || all_spaces(s))
		return (NULL);
	i[1] = 0;
	i[0] = count_double_array_size(s, c, c1);
	str = (char **) ft_malloc ((i[0] + 1) * sizeof (char *), 0);
	while (i[1] < i[0])
	{
		i[3] = -1;
		while (*s == c || *s == c1)
			s++;
		i[2] = count_single_array_size(s, c, c1);
		str[i[1]] = ft_malloc ((i[2] + 1) * sizeof(char), 0);
		while (++(i[3]) < i[2])
			str[i[1]][i[3]] = s[i[3]];
		str[i[1]][i[3]] = 0;
		s = s + i[2];
		(i[1])++;
	}
	return (str[i[1]] = NULL, str);
}
