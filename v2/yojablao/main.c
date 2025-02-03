/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yojablao <yojablao@student.42.fr>          #+#  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025-02-02 11:13:46 by yojablao          #+#    #+#             */
/*   Updated: 2025-02-02 11:13:46 by yojablao         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pars.h"

int main(int ac, char **av)
{
    t_scene *sc= NULL;
    int fd;
    if(ac != 2)
        return(printf("arg/n"));
    sc = allocat_scene(NULL);
	if (!sc)
		return(printf("broooh"));
	init_scene(sc);
    parser(av[1],&sc);
    master(0,0);    
}