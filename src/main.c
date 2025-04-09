/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: julio.formiga <julio.formiga@gmail.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/01 06:33:27 by julio.formiga     #+#    #+#             */
/*   Updated: 2025/04/01 06:33:27 by julio.formiga    ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

static void	ft_mlx_init_values(t_env *env)
{
	env->view.zoom = (float)WIN_WIDTH / env->map.width / (float)2;
	env->view.projection = 1;
	env->view.angle = 120;
	env->view.angle_rotate = 10;
	env->view.height = 0.05;
	env->view.rotation_angle_x = 0;
	env->view.rotation_angle_y = 0;
	env->view.rotation_angle_z = 0;
	env->map.player.x = 300;
	env->map.player.y = 300;
	env->map.player.direction = 0.1f;
	env->map.player.dx = 1;
	env->map.player.dy = 1;
	env->init.x = ((float)WIN_WIDTH / 2)
		- (env->view.zoom * (env->map.width - 1)) / 8;
	env->init.y = ((float)WIN_HEIGHT / 2)
		- (env->view.zoom * env->map.height) / 2;
}

int	main(int argc, char **argv)
{
	t_env	*env;
	t_map	map;

	if (argc != 2)
		argv[1] = "./maps/minimap_large.cub";
		// ft_mlx_error("Usage: ./cub3d <map>.cub");
	ft_check_file(argv[1]);
	map = ft_map_parse(argv[1]);
	env = ft_mlx_create_env();
	env->map = map;
	env->screen.img = mlx_new_image(env->mlx, WIN_WIDTH, WIN_HEIGHT);
	env->screen.addr = mlx_get_data_addr(env->screen.img,
			&env->screen.bpp, &env->screen.line, &env->screen.endian);
	ft_mlx_init_values(env);
	draw_map(env);
	ft_mlx_hooks(env);
	mlx_loop(env->mlx);
	exit(EXIT_SUCCESS);
	return (0);
}
