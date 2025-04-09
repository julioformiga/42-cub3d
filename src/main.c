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
	env->map.size = 30;
	env->map.player.x = 300;
	env->map.player.y = 300;
	env->map.player.direction = 0.0001f;
	env->map.player.speed = 2.5f;
	env->map.player.dx = cos(env->map.player.direction)
		* env->map.player.speed;
	env->map.player.dy = sin(env->map.player.direction)
		* env->map.player.speed;
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
	ft_mlx_init_values(env);
	env->screen.img = mlx_new_image(env->mlx, WIN_WIDTH, WIN_HEIGHT);
	env->screen.addr = mlx_get_data_addr(env->screen.img,
			&env->screen.bpp, &env->screen.line, &env->screen.endian);
	draw_map(env);
	ft_mlx_hooks(env);
	mlx_loop(env->mlx);
	exit(EXIT_SUCCESS);
	return (0);
}
