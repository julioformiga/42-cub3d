/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   map.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tfalchi <tfalchi@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/09 12:09:11 by julio.formi       #+#    #+#             */
/*   Updated: 2025/05/09 15:14:02 by tfalchi          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

static void	draw_ceiling(t_env *env)
{
	int	floor;

	floor = ft_mlx_color((t_color){0, 100, 100, 100});
	if (env->map.floor.r >= 0)
		floor = ft_mlx_color(env->map.floor);
	ft_mlx_draw_rect(env,
		(t_rect){
		(t_point){0, WIN_HEIGHT / 2},
		(t_point){0, WIN_HEIGHT},
		(t_point){WIN_WIDTH, WIN_HEIGHT},
		(t_point){WIN_WIDTH, WIN_HEIGHT / 2},
	},
		floor,
		1);
}

static void	draw_floor(t_env *env)
{
	int	ceiling;

	ceiling = ft_mlx_color((t_color){0, 135, 206, 235});
	if (env->map.ceiling.r >= 0)
		ceiling = ft_mlx_color(env->map.ceiling);
	ft_mlx_draw_rect(env,
		(t_rect){
		(t_point){0, 0},
		(t_point){0, WIN_HEIGHT / 2},
		(t_point){WIN_WIDTH, WIN_HEIGHT / 2},
		(t_point){WIN_WIDTH, 0},
	},
		ceiling,
		1);
}

static void	draw_red_cross(t_env *env, t_point pos)
{
	int	i;
	int	j;

	i = -1;
	while (i++, i < 11)
	{
		j = -1;
		while (j++, j < 11)
			if (i == 4 || i == 5 || j == 4 || j == 5)
				ft_draw_line_to_image(env, pos.x + i - 5, pos.y + j, RED);
	}
}

void	draw_minimap(t_env *env)
{
	int		i;
	int		j;
	t_point	position;

	env->map.player.dx = cos(env->map.player.direction);
	env->map.player.dy = sin(env->map.player.direction);
	i = -1;
	while (i++, env->map.data[i])
	{
		j = -1;
		while (j++, env->map.data[i][j] != -2)
		{
			if (!env->map.data[i])
				ft_mlx_error("Map data is NULL");
			position = (t_point){j * env->map.size, i * env->map.size};
			if (env->map.data[i][j] == 0 || env->map.data[i][j] == 1
				|| env->map.data[i][j] == 2 || env->map.data[i][j] == 3)
				ft_mlx_draw_square(env, position, env->map.size,
					env->map.data[i][j]);
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
	ft_bzero(env->screen.addr,
		WIN_WIDTH * WIN_HEIGHT * ((double)env->screen.bpp / 8));
	draw_ceiling(env);
	draw_floor(env);
	raycasting3d(env);
	draw_minimap(env);
	draw_red_cross(env, (t_point){WIN_WIDTH / 2, WIN_HEIGHT / 2});
	mlx_put_image_to_window(env->mlx, env->win, env->screen.img, 0, 0);
	position.x = (WIN_WIDTH / 2) - ((double)env->weapon.width / 2);
	position.y = WIN_HEIGHT - (env->weapon.frame_height * env->weapon.scale);
	sprite_draw(env, env->weapon, position);
	map_render_info(env);
	mlx_do_sync(env->mlx);
}
