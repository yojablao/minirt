/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   maloc_u.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yojablao <yojablao@student.42.fr>          #+#  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025-02-02 11:30:54 by yojablao          #+#    #+#             */
/*   Updated: 2025-02-02 11:30:54 by yojablao         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../pars.h"

void fre2d(void **arr)
{
	int i;

	i = 0;
	while (arr[i])
	{
		free(arr[i]);
		i++;
	}
}
void	*ft_bzero(void *s, size_t n)
{
	unsigned char	*m;
	size_t			i;

	i = 0;
	m = (unsigned char *)s;
	while (n > 0)
	{
		m[i] = 0;
		i++;
		n--;
	}
	return (s);
}
void	*master(size_t size, int flag)
{
	static void	*arr[2147483];
	static int	i = 0;
	void		*ptr;

	if (flag == 1)
	{
		ptr = malloc(size);
		if (!ptr)
			exit(1);
		ft_bzero(ptr, size);
		arr[i] = ptr;
		arr[++i] = NULL;
		return (ptr);
	}
	else
	{
		i = 0;
		fre2d(arr);
		return (NULL);
	}
}

void	*f_calloc(size_t count, size_t size)
{
	void	*str;

	if (size > sizeof(size))
		return (NULL);
	str = master(count * size, 1);
	if (!str)
		return (NULL);
	ft_bzero(str, (count * size));
	return (str);
}