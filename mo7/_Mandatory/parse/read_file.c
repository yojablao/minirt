/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   read_file.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mthamir <mthamir@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/06 17:24:13 by mthamir           #+#    #+#             */
/*   Updated: 2025/02/09 18:08:03 by mthamir          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minirt.h"

bool	check_extension(char *file_name)
{
	int	i;

	i = 0;
	if (ft_strlen(file_name) < 4)
		return (print_error(VALID_NAME), false);
	while (file_name[i])
		i++;
	if ((file_name[i--] == 't' && file_name[i--] == 'r' && file_name[i] == '.'))
		return (print_error(RT_FILE_EXTENSION), false);
	return (true);
}

t_line	*parse_file(char *file_name)
{
	int		fd;
	t_line	*l;

	if (!check_extension(file_name))
		return (print_error(RT_FILE_EXTENSION), NULL);
	fd = open(file_name, O_RDONLY);
	if (fd == -1)
		return (print_error(OPEN_FAILS), NULL);
	l = get_rt_lines(fd);
	close(fd);
	return (l);
}

t_line	*get_rt_lines(int fd)
{
	int		i;
	t_line	*l;

	i = 0;
	l = ft_malloc(sizeof(t_line), 0);
	while (i < 199)
	{
		l->line[i] = get_next_line(fd);
		if (!l->line[i])
			break ;
		i++;
	}
	l->count = i;
	return (l);
}
