/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_mlx_controls.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tfalchi <tfalchi@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/05 02:19:51 by julio.formi       #+#    #+#             */
/*   Updated: 2025/04/17 11:25:07 by tfalchi          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

static int	ft_mlx_button_release(int button, int x, int y, t_env *env)
{
	(void)x;
	(void)y;
	if (button == 1)
	{
		sprite_set_frame(&env->weapon, 0);
		env->weapon.animating = 0;
	}
	return (0);
}

static int	ft_mlx_button(int button, int x, int y, t_env *env)
{
	(void)x;
	(void)y;
	if (button == 5)
		ft_mlx_keypress('-', env);
	if (button == 4)
		ft_mlx_keypress('+', env);
	if (button == 1)
		env->weapon.animating = 1;
	return (0);
}

int ft_mouse_move(void *param)
{
    t_env *env;
	int x;
	int y;
	int delta_x;

	env = (t_env *)param;
	mlx_mouse_get_pos(env->mlx, env->win, &x, &y);
	delta_x = x - env->map.player.mouse_x;
	if (delta_x != 0)
	{
		env->map.player.direction += delta_x * env->map.player.mouse_speed;
		if (env->map.player.direction < 0)
			env->map.player.direction += 2.0 * M_PI;
		else if (env->map.player.direction > 2.0 * M_PI)
			env->map.player.direction -= 2.0 * M_PI;
		env->map.player.dx = cos(env->map.player.direction) * env->map.player.speed;
		env->map.player.dy = sin(env->map.player.direction) * env->map.player.speed;
	}
	env->map.player.mouse_x = x;
	if (x < 100 || x > WIN_WIDTH - 100)
	{
		mlx_mouse_move(env->mlx, env->win, WIN_WIDTH / 2, WIN_HEIGHT / 2);
		env->map.player.mouse_x = WIN_WIDTH / 2;
	}

    return (0);
}

void	ft_mlx_hooks(t_env *env)
{
	int x;
	int y;

	env->keys.up = 0;
	env->keys.down = 0;
	env->keys.left = 0;
	env->keys.right = 0;
  init_textures(env);
	mlx_mouse_get_pos(env->mlx, env->win, &x, &y);
	env->map.player.mouse_x = x;
	mlx_hook(env->win, KeyPress, KeyPressMask, ft_mlx_keypress, env);
	mlx_hook(env->win, KeyRelease, KeyReleaseMask, ft_mlx_keyrelease, env);
	mlx_hook(env->win, ButtonPress, ButtonPressMask, ft_mlx_button, env);
	mlx_hook(env->win, ButtonRelease, ButtonReleaseMask, ft_mlx_button_release, env);
	mlx_hook(env->win, DestroyNotify, StructureNotifyMask,
		ft_mlx_destroy_window, env);
	mlx_loop_hook(env->mlx, ft_update_game, env);
}

int	ft_mlx_keypress(int keycode, t_env *env)
{
	if (keycode == XK_Escape || keycode == 'q')
		ft_mlx_destroy_window(env);
	else if (keycode == 'w' || keycode == XK_Up)
		env->keys.up = 1;
	else if (keycode == 's' || keycode == XK_Down)
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
		if (env->map.player.mouse_speed > 0.0005)
			env->map.player.mouse_speed -= 0.0002;
		if (env->map.numrays > 100)
			env->map.numrays -= 10;
	}
	else if (keycode == '+')
	{
		if (env->map.player.mouse_speed < 0.01)
			env->map.player.mouse_speed += 0.0002;
		if (env->map.numrays < 2000)
			env->map.numrays += 10;
	}
	// else if (keycode == XK_space)
	// 	env->weapon.animating = 1;
	return (0);
}

int	ft_mlx_keyrelease(int keycode, t_env *env)
{
	if (keycode == 'w' || keycode == XK_Up)
		env->keys.up = 0;
	else if (keycode == 's' || keycode == XK_Down)
		env->keys.down = 0;
	else if (keycode == 'a')
		env->keys.left = 0;
	else if (keycode == 'd')
		env->keys.right = 0;
	else if (keycode == XK_Left)
		env->keys.arrow_left = 0;
	else if (keycode == XK_Right)
		env->keys.arrow_right = 0;
	// else if (keycode == XK_space)
	// {
	// 	sprite_set_frame(&env->weapon, 0);
	// 	env->weapon.animating = 0;
	// }
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
	double	player_radius;

	player_radius = env->map.size / 4;
	y = 0;
	while (y < env->map.height)
	{
		x = 0;
		// while (x < env->map.width)
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
