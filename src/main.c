/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tfalchi <tfalchi@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/01 06:33:27 by julio.formi       #+#    #+#             */
/*   Updated: 2025/04/15 17:51:26 by tfalchi          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

static void	ft_mlx_init_values(t_env *env)
{
	env->map.numrays = 360.0;
	env->map.player.fov = 60.0;
	env->map.player.speed = 1.0;
	env->map.player.dx = cos(env->map.player.direction) * env->map.player.speed;
	env->map.player.dy = sin(env->map.player.direction) * env->map.player.speed;
}

void	free_all(t_env *env)
{
	if (env)
	{
		if (env->map.data)
		{
			while (env->map.height--)
				free(env->map.data[env->map.height]);
			free(env->map.data);
		}
		if (env->imgs->img)
		{
			mlx_destroy_image(env->mlx, env->imgs->img);
			free(env->imgs);
		}
		if (env->screen.img)
			mlx_destroy_image(env->mlx, env->screen.img);
		if (env->win)
			mlx_destroy_window(env->mlx, env->win);
		if (env->mlx)
		{
			mlx_destroy_display(env->mlx);
			free(env->mlx);
		}
		free(env->mlx);
		free(env);
	}
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
	env->screen.addr = mlx_get_data_addr(env->screen.img, &env->screen.bpp,
			&env->screen.line, &env->screen.endian);
	draw_map(env);
	ft_mlx_hooks(env);
	mlx_loop(env->mlx);
	free_all(env);
	exit(EXIT_SUCCESS);
	return (0);
}
// mlx_mouse_hide(env->mlx, env->win);
