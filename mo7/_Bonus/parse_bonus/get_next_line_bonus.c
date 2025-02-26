/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line_bonus.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mthamir <mthamir@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/06 17:17:06 by mthamir           #+#    #+#             */
/*   Updated: 2025/02/16 12:42:22 by mthamir          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minirt_bonus.h"

int	check_for_nl(char	**buff)
{
	int		i;
	char	*tmp;

	i = 0;
	tmp = *buff;
	while (tmp[i])
	{
		if (tmp[i] == '\n')
			return (1);
		i++;
	}
	return (0);
}

static char	*ft_get_buff(int fd, char *buffer)
{
	char	*ret;
	int		i;

	i = 1;
	while (i > 0)
	{
		ret = ft_malloc (((size_t)10 + 1) * sizeof(char), 0);
		if (!ret)
			return (NULL);
		i = read (fd, ret, 10);
		if (i == -1)
			return (NULL);
		if (i == 0)
			return (buffer);
		ret[i] = '\0';
		buffer = ft_strjoin(buffer, ret);
		if (!buffer)
			return (NULL);
		if (check_for_nl(&ret) == 1)
			break ;
	}
	return (buffer);
}

static int	get_i(char *tmp)
{
	int	i;

	i = 0;
	while (tmp[i] != '\n' && tmp[i] != '\0')
		i++;
	if (tmp[i] == '\n')
		i++;
	return (i);
}

static char	*get_line_(char *buffer)
{
	char	*ret;
	int		i;

	i = 0;
	i = get_i(buffer);
	ret = ft_malloc ((i + 1) * sizeof(char), 0);
	if (!ret)
		return (NULL);
	i = 0;
	while (buffer[i] != '\n' && buffer[i] != '\0')
	{
		ret[i] = buffer[i];
		i++;
	}
	if (buffer[i] == '\n')
	{
		ret[i] = ' ';
		i++;
	}
	ret[i] = '\0';
	return (ret);
}

char	*get_next_line(int fd)
{
	static char	*buffer;
	char		*line;

	if (fd < 0 || read (fd, buffer, 0) < 0)
		return (buffer = NULL, NULL);
	buffer = ft_get_buff(fd, buffer);
	if (!buffer || buffer [0] == 0)
		return (NULL);
	line = get_line_(buffer);
	if (!line || line [0] == 0)
		return (NULL);
	buffer = ft_strdup(buffer + ft_strlen(line));
	if (all_spaces(line))
		return (get_next_line(fd));
	return (line);
}
