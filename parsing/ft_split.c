/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_split.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yojablao <yojablao@student.42.ma>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/15 19:51:21 by yojablao          #+#    #+#             */
/*   Updated: 2025/01/04 19:12:58 by yojablao         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../tool.h"

static char	*subs(const char *s, char *str, size_t start, size_t size)
{
	size_t	i;

	if (str == 0)
		return (NULL);
	i = 0;
	while (start < size)
	{
		str[i] = s[start];
		i++;
		start++;
	}
	str[i] = '\0';
	return (str);
}

static void	free_it(char **str, ssize_t	l)
{
	while (l >= 0)
		free (str[l--]);
	free (str);
}

static size_t	count_words(const char *s, char c, char c1)
{
	int		i;
	size_t	count;

	i = 0;
	count = 0;
	while (s[i])
	{
		while ((s[i] == c || s[i] == c1) && s[i])
			i++;
		if (s[i])
			count++;
		while (s[i] != c && s[i] != c1 && s[i])
			i++;
	}
	return (count);
}

static ssize_t	norm(const char *s, char c,char c1, char **str, size_t i)
{
	size_t	start;
	size_t	l;

	l = 0;
	start = 0;
	while (s[i])
	{
		if (s[i] != c && s[i] != c1)
		{
			start = i;
			while (s[i] && s[i] != c && s[i] != c1)
				i++;
			str[l] = (char *)malloc(((i - start) + 1) * sizeof(char));
			if (str[l] == NULL)
			{
				free_it(str, l);
				return (-1);
			}
			str[l] = subs(s, str[l], start, i);
			l++;
		}
		else
			i++;
	}
	return (l);
}

char	**ft_split(char const *s, char c ,char c1)
{
	char	**str;
	ssize_t	l;
	size_t	i;
	size_t	word_count;

	if (!s)
		return (NULL);
	word_count = count_words (s, c,c1);
	str = malloc ((word_count + 1) * sizeof(char *));
	if (str == NULL)
		return (NULL);
	i = 0;
	l = norm(s, c,c1, str, i);
	if (l == -1)
		return (NULL);
	str[l] = NULL;
	return (str);
}
