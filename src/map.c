/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   map.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tfalchi <tfalchi@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/09 12:09:11 by julio.formi       #+#    #+#             */
/*   Updated: 2025/04/26 11:26:52 by tfalchi          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

static void	draw_celing(t_env *env)
{
	int	floor;

	floor = ft_mlx_color((t_color){0, 100, 100, 100});
	if (env->map.floor.r)
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
	int	celing;

	celing = ft_mlx_color((t_color){0, 135, 206, 235});
	if (env->map.ceiling.r)
		celing = ft_mlx_color(env->map.ceiling);
	ft_mlx_draw_rect(env,
		(t_rect){
		(t_point){0, 0},
		(t_point){0, WIN_HEIGHT / 2},
		(t_point){WIN_WIDTH, WIN_HEIGHT / 2},
		(t_point){WIN_WIDTH, 0},
	},
		celing,
		1);
}

static void	draw_red_cross(t_env *env, t_point position)
{
	int	i;
	int	j;

	i = -1;
	while (i++, i < 11)
	{
		j = -1;
		while (j++, j < 11)
			if (i == 4 || i == 5 || j == 4 || j == 5)
				ft_draw_line_to_image(env, position.x + i - 5, position.y + j,
					RED);
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
		while (j++, env->map.data[i][j] != -1)
		{
			if (!env->map.data[i])
				ft_mlx_error("Map data is NULL");
			position = (t_point){j * env->map.size, i * env->map.size};
			ft_mlx_draw_square(env, position, env->map.size, BLACK);
			if (env->map.data[i][j] == 1)
				ft_mlx_draw_square(env, position, env->map.size, WHITE);
			else if (env->map.data[i][j] == 2)
				ft_mlx_draw_square(env, position, env->map.size, RED);
			else
				ft_mlx_draw_square(env, position, env->map.size, BLACK);
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
	ft_bzero(env->screen.addr, WIN_WIDTH * WIN_HEIGHT * ((double)env->screen.bpp
			/ 8));
	draw_celing(env);
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
