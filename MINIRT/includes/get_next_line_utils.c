/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line_utils.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yojablao <yojablao@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/23 12:46:21 by yojablao          #+#    #+#             */
/*   Updated: 2024/01/17 06:06:51 by yojablao         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"

int	ft_strchr(const char *str, int find)
{
	int	i;

	i = 0;
	if (!str)
		return (0);
	while (str[i])
	{
		if (str[i] == (char)find)
			return (1);
		i++;
	}
	return (0);
}

char	*strjoin(char *s1, char	*s2)
{
	char	*ret;

	if (!s1 && s2)
	{
		ret = malloc(ft_strlen(s2) + 1);
		if (!ret)
			return (NULL);
		ft_strcpy(ret, s2);
		return (ret);
	}
	ret = malloc((ft_strlen(s1) + ft_strlen(s2) + 1));
	if (!ret)
		return (NULL);
	ft_strcpy(ret, s1);
	ft_strcat(ret, s2);
	free(s1);
	return (ret);
}

void	ft_strcpy(char *dest, const char	*src)
{
	size_t	i;

	i = 0;
	while (src [i] != '\0')
	{
		dest[i] = src[i];
		i++;
	}
	dest[i] = '\0';
}

size_t	ft_strlen(const char *str)
{
	size_t	i;

	if (!str)
		return (0);
	i = 0;
	while (str[i])
		i++;
	return (i);
}

void	ft_strcat(char *dst, const char *src)
{
	size_t	ls;
	size_t	ld;
	size_t	l;
	size_t	i;

	if (!dst || !src)
		return ;
	ld = ft_strlen(dst);
	ls = ft_strlen(src);
	l = ld;
	i = 0;
	while (src[i] != '\0')
		dst[l++] = src[i++];
	dst[l] = '\0';
}
