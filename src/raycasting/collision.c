/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   collision.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tfalchi <tfalchi@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/20 15:15:25 by julio.formi       #+#    #+#             */
/*   Updated: 2025/04/23 15:51:42 by tfalchi          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

bool	collision(t_env *env, double p_x, double p_y)
{
	int		x;
	int		y;
	t_wall	wall;
	double	p_rad;

	p_rad = env->map.size / 8;
	y = -1;
	while (y++, y < env->map.height)
	{
		x = -1;
		while (x++, env->map.data[y] && env->map.data[y][x] >= -1)
		{
			if (env->map.data[y][x] == 1 || env->map.data[y][x] == 2)
			{
				wall.left = x * env->map.size;
				wall.right = (x + 1) * env->map.size;
				wall.top = y * env->map.size;
				wall.bottom = (y + 1) * env->map.size;
				if (p_x + p_rad > wall.left && p_x - p_rad < wall.right && p_y
					+ p_rad > wall.top && p_y - p_rad < wall.bottom)
					return (true);
			}
		}
	}
	return (false);
}

static int	ft_process_movement(t_env *env)
{
	int		move_direction;
	double	tmp;

	move_direction = 0;
	if (env->keys.up)
		move_direction = 1;
	if (env->keys.down)
		move_direction = -1;
	if (env->keys.left)
	{
		move_direction = -1;
		tmp = -env->map.player.dy;
		env->map.player.dy = env->map.player.dx;
		env->map.player.dx = tmp;
	}
	if (env->keys.right)
	{
		move_direction = 1;
		tmp = -env->map.player.dy;
		env->map.player.dy = env->map.player.dx;
		env->map.player.dx = tmp;
	}
	return (move_direction);
}

static void	ft_update_position(t_env *env, int move_direction)
{
	if (move_direction != 0)
	{
		if (!collision(env, env->map.player.x, env->map.player.y
				+ env->map.player.dy * env->map.player.speed * move_direction))
		{
			env->map.player.y += env->map.player.dy * env->map.player.speed
				* move_direction;
		}
		if (!collision(env, env->map.player.x + env->map.player.dx
				* env->map.player.speed * move_direction, env->map.player.y))
		{
			env->map.player.x += env->map.player.dx * env->map.player.speed
				* move_direction;
		}
	}
}

static void	ft_process_rotation(t_env *env)
{
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
}

int	ft_update_game(t_env *env)
{
	int	move_direction;

	ft_mouse_move(env);
	move_direction = ft_process_movement(env);
	ft_update_position(env, move_direction);
	ft_process_rotation(env);
	draw_map(env);
	sprite_update_animation(&env->weapon);
	return (0);
}
