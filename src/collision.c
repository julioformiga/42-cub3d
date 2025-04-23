/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   collision.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: julio.formiga <julio.formiga@gmail.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/20 15:15:25 by julio.formiga     #+#    #+#             */
/*   Updated: 2025/04/20 15:15:25 by julio.formiga    ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

bool	collision(t_env *env, double p_x, double p_y)
{
	int		x;
	int		y;
	double	wall_left;
	double	wall_right;
	double	wall_top;
	double	wall_bottom;
	double	player_radius;

	player_radius = env->map.size / 4;
	y = 0;
	while (y < env->map.height)
	{
		x = 0;
		while (env->map.data[y] && env->map.data[y][x] != -1)
		{
			if (env->map.data[y][(int)x] == 1)
			{
				wall_left = x * env->map.size;
				wall_right = (x + 1) * env->map.size;
				wall_top = y * env->map.size;
				wall_bottom = (y + 1) * env->map.size;
				if (p_x + player_radius > wall_left && p_x
					- player_radius < wall_right && p_y
					+ player_radius > wall_top && p_y
					- player_radius < wall_bottom)
				{
					return (true);
				}
			}
			x++;
		}
		y++;
	}
	return (false);
}

int	ft_update_game(t_env *env)
{
	int		i;
	double	tmp;

	i = 0;
	ft_mouse_move(env);
	if (env->keys.up)
		i = 1;
	if (env->keys.down)
		i = -1;
	if (env->keys.left)
	{
		i = -1;
		tmp = -env->map.player.dy;
		env->map.player.dy = env->map.player.dx;
		env->map.player.dx = tmp;
	}
	if (env->keys.right)
	{
		i = 1;
		tmp = -env->map.player.dy;
		env->map.player.dy = env->map.player.dx;
		env->map.player.dx = tmp;
	}
	if (i != 0 && !collision(env, env->map.player.x, env->map.player.y
			+ env->map.player.dy * env->map.player.speed * i))
	{
		env->map.player.y += env->map.player.dy * env->map.player.speed * i;
	}
	if (i != 0 && !collision(env, env->map.player.x + env->map.player.dx
			* env->map.player.speed * i, env->map.player.y))
	{
		env->map.player.x += env->map.player.dx * env->map.player.speed * i;
	}
	if (env->keys.arrow_left)
	{
		env->map.player.direction -= 0.04;
		if (env->map.player.direction < 0)
			env->map.player.direction += 2.0 * M_PI;
		env->map.player.dx = cos(env->map.player.direction)
			* env->map.player.speed;
		env->map.player.dy = sin(env->map.player.direction)
			* env->map.player.speed;
	}
	if (env->keys.arrow_right)
	{
		env->map.player.direction += 0.04;
		if (env->map.player.direction > 2 * M_PI)
			env->map.player.direction -= 2.0 * M_PI;
		env->map.player.dx = cos(env->map.player.direction)
			* env->map.player.speed;
		env->map.player.dy = sin(env->map.player.direction)
			* env->map.player.speed;
	}
	draw_map(env);
	sprite_update_animation(&env->weapon);
	return (0);
}
