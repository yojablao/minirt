/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minirt.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yojablao <yojablao@student.42.fr>          #+#  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025-01-10 16:15:36 by yojablao          #+#    #+#             */
/*   Updated: 2025-01-10 16:15:36 by yojablao         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "tool.h"


void draw_scene(t_scene *sc)
{

}
int minirt(char **av,t_scene * sc)
{
	parser(av[1],sc);
	// printf("pars done/n");
	calculate_camera(sc);
	draw_scene(sc);
	return (EXIT_SUCCESS);
}

























































	// if (mlx_put_image_to_window(sc->mlx->mlx, sc->mlx->window,sc->img, 0, 0) < 0)
	// 	error();
	// mlx_loop_hook(sc->gr.mlx, hook, sc);
	// mlx_resize_hook(sc->gr.mlx, resize, sc);
	// mlx_scroll_hook(sc->gr.mlx, scrollhook, sc);
	// mlx_loop(sc->mlx);
	// mlx_delete_image(sc->gr.mlx, sc->gr.img);
	// mlx_terminate(sc->gr.mlx);
	// free_list(sc->sphere);
	// free_list(sc->cylinder);
	// free_list(sc->plane);
	// free(sc);