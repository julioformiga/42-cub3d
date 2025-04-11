/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_mlx_controls.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tfalchi <tfalchi@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/05 02:19:51 by julio.formi       #+#    #+#             */
/*   Updated: 2025/04/11 17:49:33 by tfalchi          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"



static int	ft_mlx_mouse(int button, int x, int y, t_env *env)
{
	(void)x;
	(void)y;
	if (button == 5)
		ft_mlx_keypress('-', env);
	if (button == 4)
		ft_mlx_keypress('+', env);
	return (0);
}

int ft_mouse_move(void *param)
{
    t_env *env;
	int x;
	int y;
	
	printf("Mouse moved\n");
	env = (t_env *)param;
	mlx_mouse_get_pos(env->mlx, env->win, &x, &y);
	env->map.player.direction += (x - WIN_WIDTH / 2) * MROT_SPEED;
	// env->map.player.direction = env->map.player.direction, (x - WIN_WIDTH / 2) * MROT_SPEED);
	mlx_mouse_move(env->mlx, env->win, WIN_WIDTH / 2, WIN_HEIGHT / 2);
    return (0);
}

void	ft_mlx_hooks(t_env *env)
{
	env->keys.up = 0;
	env->keys.down = 0;
	env->keys.left = 0;
	env->keys.right = 0;
	mlx_hook(env->win, KeyPress, KeyPressMask, ft_mlx_keypress, env);
	mlx_hook(env->win, KeyRelease, KeyReleaseMask, ft_mlx_keyrelease, env);
	mlx_hook(env->win, ButtonPress, ButtonPressMask, ft_mlx_mouse, env);
	mlx_hook(env->win, DestroyNotify, StructureNotifyMask,
		ft_mlx_destroy_window, env);
	mlx_loop_hook(env->mlx, ft_update_game, env);
}

int	ft_mlx_keypress(int keycode, t_env *env)
{
	if (keycode == XK_Escape || keycode == 'q')
		ft_mlx_destroy_window(env);
	else if (keycode == 'w')
		env->keys.up = 1;
	else if (keycode == 's')
		env->keys.down = 1;
	else if (keycode == 'a')
		env->keys.left = 1;
	else if (keycode == 'd')
		env->keys.right = 1;
	else if (keycode == XK_Left)
		env->keys.arrow_left = 1;
	else if (keycode == XK_Right)
		env->keys.arrow_right = 1;
	else if (keycode == '-')
	{
		env->map.size -= 1;
		draw_map(env);
	}
	else if (keycode == '+')
	{
		env->map.size += 1;
		draw_map(env);
	}
	return (0);
}

int	ft_mlx_keyrelease(int keycode, t_env *env)
{
	if (keycode == 'w')
		env->keys.up = 0;
	else if (keycode == 's')
		env->keys.down = 0;
	else if (keycode == 'a')
		env->keys.left = 0;
	else if (keycode == 'd')
		env->keys.right = 0;
	else if (keycode == XK_Left)
		env->keys.arrow_left = 0;
	else if (keycode == XK_Right)
		env->keys.arrow_right = 0;
	return (0);
}

bool	collision(t_env *env, double p_x, double p_y)
{
	int		x;
	int		y;
	double	wall_left;
	double	wall_right;
	double	wall_top;
	double	wall_bottom;

	double player_radius = env->map.size / 4;
	y = 0;
	while (y < env->map.height)
	{
		x = 0;
		while (x < env->map.width)
		{
			if (env->map.data[y][x] == 1)
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
	int	update_needed;
	int	i = 0;
	double tmp;
	
	ft_mouse_move(env);
	update_needed = 0;
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
	if (i != 0 && !collision(env, env->map.player.x, env->map.player.y + env->map.player.dy
		* env->map.player.speed * i))
	{
		env->map.player.y += env->map.player.dy * env->map.player.speed * i;
		update_needed = 1;
	}
	if (i != 0 && !collision(env, env->map.player.x + env->map.player.dx
		* env->map.player.speed * i, env->map.player.y))
	{
		env->map.player.x += env->map.player.dx * env->map.player.speed * i;
		update_needed = 1;
	}
	if (env->keys.arrow_left)
	{
		env->map.player.direction -= 0.04;
		if (env->map.player.direction < 0)
			env->map.player.direction += 2.0f * M_PI;
		env->map.player.dx = cos(env->map.player.direction)
			* env->map.player.speed;
		env->map.player.dy = sin(env->map.player.direction)
			* env->map.player.speed;
		update_needed = 1;
	}
	if (env->keys.arrow_right)
	{
		env->map.player.direction += 0.04;
		if (env->map.player.direction > 2 * M_PI)
			env->map.player.direction -= 2.0f * M_PI;
		env->map.player.dx = cos(env->map.player.direction)
			* env->map.player.speed;
		env->map.player.dy = sin(env->map.player.direction)
			* env->map.player.speed;
		update_needed = 1;
	}
	draw_map(env);
	return (0);
}
