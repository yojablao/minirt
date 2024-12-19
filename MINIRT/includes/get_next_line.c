/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yojablao <yojablao@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/22 11:14:29 by yojablao          #+#    #+#             */
/*   Updated: 2024/01/20 18:01:15 by yojablao         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"

char	*check_line(char	*old)
{
	char	*new;
	int		i;
	int		j;

	j = 0;
	i = 0;
	if (old[i] == '\0' || !old)
		return (NULL);
	while (old[i] != '\n' && old[i])
		i++;
	if (old[i] == '\n')
		i++;
	new = malloc(ft_strlen(old) - i + 1);
	if (!new)
		return (NULL);
	while (old[i] != '\0')
	{
		new[j] = old[i];
		j++;
		i++;
	}
	new[j] = '\0';
	free(old);
	return (new);
}

char	*extract_line(char *rez)
{
	int		i;
	char	*line;
	int		j;

	i = 0;
	if (rez[i] == '\0' || !rez)
		return (NULL);
	while (rez[i] != '\0' && rez[i] != '\n')
		i++;
	if (rez[i] == '\n')
		i++;
	line = malloc(i + 1);
	if (!line)
		return (NULL);
	j = -1;
	while (++j < i)
		line[j] = rez[j];
	line[i] = '\0';
	return (line);
}

char	*readfd(char **buffer, int fd)
{
	char	*r;
	ssize_t	l;

	l = 1;
	r = malloc((size_t)BUFFER_SIZE +1);
	if (!r)
		return (NULL);
	while (l && !ft_strchrg(*buffer, '\n'))
	{
		l = read(fd, r, BUFFER_SIZE);
		if (l < 0)
			return (free(*buffer), free(r), *buffer = NULL, NULL);
		r[l] = '\0';
		*buffer = strjoin(*buffer, r);
		if (!*buffer)
			return (free(r), free(*buffer), NULL);
	}
	free(r);
	return (extract_line(*buffer));
}

char	*get_next_line(int fd)
{
	static char	*rest;
	char		*line;

	if (BUFFER_SIZE < 1 || read(fd, 0, 0) < 0)
		return (NULL);
	line = readfd(&rest, fd);
	if (!line)
		return (free(rest), rest = NULL, NULL);
	rest = check_line(rest);
	return (line);
}
