/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   map.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tfalchi <tfalchi@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/09 12:09:11 by julio.formi       #+#    #+#             */
/*   Updated: 2025/04/17 17:27:58 by tfalchi          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

static void	draw_celing_floor(t_env *env)
{
	int		floor;
	int		celing;

	celing = ft_mlx_color((t_color){0, 135, 206, 235});
	if (env->map.ceiling.r)
		celing = ft_mlx_color(env->map.ceiling);
	floor = ft_mlx_color((t_color){0, 100, 100, 100});
	if (env->map.floor.r)
		floor = ft_mlx_color(env->map.floor);
	ft_mlx_draw_rect(env, (t_rect){
		(t_point){0, 0},
		(t_point){0, WIN_HEIGHT / 2},
		(t_point){WIN_WIDTH, WIN_HEIGHT / 2},
		(t_point){WIN_WIDTH, 0},
	}, celing, 1);
	ft_mlx_draw_rect(env, (t_rect){
		(t_point){0, WIN_HEIGHT / 2},
		(t_point){0, WIN_HEIGHT},
		(t_point){WIN_WIDTH, WIN_HEIGHT},
		(t_point){WIN_WIDTH, WIN_HEIGHT / 2},
	}, floor, 1);
}

void	draw_minimap(t_env *env)
{
	int		i;
	int		j;
	double	size;

	size = env->map.size;
	env->map.player.dx = cos(env->map.player.direction);
	env->map.player.dy = sin(env->map.player.direction);
	raycasting3d(env);
	i = -1;
	while (i++, env->map.data[i])
	{
		j = -1;
		while (j++, env->map.data[i][j] != -1)
		{
			if (!env->map.data[i])
				ft_mlx_error("Map data is NULL");
			ft_mlx_draw_square(env, (t_point){j * size, i * size}, size, BLACK);
			if (env->map.data[i][j] == 1)
				ft_mlx_draw_square(env, (t_point){j * size, i * size}, size, WHITE);
			else if (env->map.data[i][j] == 2)
				ft_mlx_draw_square(env, (t_point){j * size, i * size}, size, RED);
			else
				ft_mlx_draw_square(env, (t_point){j * size, i * size}, size, BLACK);
		}
	}
	player(env);
}

void	draw_map(t_env *env)
{
	t_point	position;

	if (!env->map.data)
	{
		printf("Map data is NULL\n");
		return ;
	}
	ft_bzero(env->screen.addr, WIN_WIDTH * WIN_HEIGHT
		* ((double)env->screen.bpp / 8));
	draw_celing_floor(env);
	draw_minimap(env);
	mlx_put_image_to_window(env->mlx, env->win, env->screen.img, 0, 0);
	position.x = (WIN_WIDTH / 2) - ((double)env->weapon.width / 2);
	position.y = WIN_HEIGHT - (env->weapon.frame_height * 1.2);
	sprite_draw(env, env->weapon, position, 1.2);
	mlx_do_sync(env->mlx);
}
