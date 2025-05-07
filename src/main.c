/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tfalchi <tfalchi@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/01 06:33:27 by julio.formi       #+#    #+#             */
/*   Updated: 2025/05/05 15:26:28 by tfalchi          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

static void	ft_mlx_init_values(t_env *env)
{
	env->map.numrays = 1360.0;
	env->map.player.fov = 60.0;
	env->map.player.max_ray_distance = 1000.0;
	env->map.player.speed = 1.0;
	env->map.player.mouse_speed = 0.002;
	env->map.player.dx = cos(env->map.player.direction) * env->map.player.speed;
	env->map.player.dy = sin(env->map.player.direction) * env->map.player.speed;
	sprite_load(env, "./assets/sprite_weapon.xpm");
}

static void	free_textures(t_env *env)
{
	if (env->imgs)
	{
		if (env->imgs->image)
			mlx_destroy_image(env->mlx, env->imgs->image);
		free(env->imgs);
	}
	if (env->map.north.img)
		mlx_destroy_image(env->mlx, env->map.north.img);
	if (env->map.north.path)
		free(env->map.north.path);
	if (env->map.south.img)
		mlx_destroy_image(env->mlx, env->map.south.img);
	if (env->map.south.path)
		free(env->map.south.path);
	if (env->map.east.img)
		mlx_destroy_image(env->mlx, env->map.east.img);
	if (env->map.east.path)
		free(env->map.east.path);
	if (env->map.west.img)
		mlx_destroy_image(env->mlx, env->map.west.img);
	if (env->map.door.img)
		mlx_destroy_image(env->mlx, env->map.door.img);
	if (env->map.west.path)
		free(env->map.west.path);
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
		free_textures(env);
		if (env->map.door.path)
			free(env->map.door.path);
		if (env->mlx)
		{
			if (env->screen.img)
				mlx_destroy_image(env->mlx, env->screen.img);
			if (env->weapon.img)
				mlx_destroy_image(env->mlx, env->weapon.img);
			if (env->win)
				mlx_destroy_window(env->mlx, env->win);
			mlx_destroy_display(env->mlx);
			free(env->mlx);
		}
		free(env);
	}
}

int	main(int argc, char **argv)
{
	t_env	*env;
	t_map	*map;

	map = NULL;
	if (argc != 2)
		ft_mlx_error("Usage: ./cub3d <map>.cub");
	ft_check_file(argv[1]);
	ft_map_parse(argv[1], map);
	if (map == NULL)
	{
		return (0);
	}
	env = ft_mlx_create_env();
	env->map = *map;
	ft_mlx_init_values(env);
	ft_mouse_hide(env->mlx, env->win);
	env->screen.img = mlx_new_image(env->mlx, WIN_WIDTH, WIN_HEIGHT);
	env->screen.addr = mlx_get_data_addr(env->screen.img, &env->screen.bpp,
			&env->screen.line, &env->screen.endian);
	ft_mlx_hooks(env);
	mlx_loop(env->mlx);
	free_all(env);
	exit(EXIT_SUCCESS);
	return (0);
}
