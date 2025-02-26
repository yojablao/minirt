/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils_0_bonus.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mthamir <mthamir@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/06 17:15:41 by mthamir           #+#    #+#             */
/*   Updated: 2025/02/09 16:18:22 by mthamir          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minirt_bonus.h"

size_t	ft_strlen(const char *s)
{
	size_t	i;

	if (s == NULL)
		return (0);
	i = 0;
	while (*s++ != 0)
		i++;
	return (i);
}

char	*ft_strdup(char *s)
{
	size_t	i;
	char	*str;

	i = 0;
	str = NULL;
	if (!s)
		return (NULL);
	i = ft_strlen(s);
	str = (char *) ft_malloc ((i + 1) * sizeof(char), 0);
	if (!str)
		return (NULL);
	str = ft_copy(str, s, 0);
	str[i] = '\0';
	return (str);
}

char	*ft_strjoin(char *s1, char *s2)
{
	char	*str;
	char	*ret;
	int		i;

	str = NULL;
	if (s1 == NULL && s2 == NULL)
		return (NULL);
	if (s1 == NULL)
		return (ft_strdup(s2));
	if (s2 == NULL)
		return (ft_strdup(s1));
	i = ft_strlen(s1) + ft_strlen(s2);
	str = (char *) ft_malloc ((i + 1) * sizeof(char), 0);
	if (!str)
		return (NULL);
	ret = str;
	str = ft_copy(str, s1, 0);
	str = ft_copy(str, s2, ft_strlen(s1));
	str[i] = '\0';
	return (ret);
}

int	all_spaces(char *s)
{
	int	i;

	i = 0;
	while (s[i])
	{
		if (s[i] != ' ' && s[i] != '\t')
			return (0);
		i++;
	}
	return (1);
}
