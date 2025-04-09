/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_mlx_controls.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: julio.formiga <julio.formiga@gmail.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/05 02:19:51 by julio.formiga     #+#    #+#             */
/*   Updated: 2025/04/05 02:19:51 by julio.formiga    ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

void ft_mlx_hooks(t_env *env)
{
	env->keys.up = 0;
	env->keys.down = 0;
	env->keys.left = 0;
	env->keys.right = 0;

	mlx_hook(env->win, KeyPress, KeyPressMask, ft_mlx_keypress, env);
	mlx_hook(env->win, KeyRelease, KeyReleaseMask, ft_mlx_keyrelease, env);
	mlx_hook(env->win, DestroyNotify, StructureNotifyMask,
			 ft_mlx_destroy_window, env);
	mlx_loop_hook(env->mlx, ft_update_game, env);
}

int ft_mlx_keypress(int keycode, t_env *env)
{
	if (keycode == XK_Escape || keycode == 'q')
		ft_mlx_destroy_window(env);
	else if (keycode == XK_Up || keycode == 'k')
		env->keys.up = 1;
	else if (keycode == XK_Down || keycode == 'j')
		env->keys.down = 1;
	else if (keycode == XK_Left || keycode == 'h')
		env->keys.left = 1;
	else if (keycode == XK_Right || keycode == 'l')
		env->keys.right = 1;
	return (0);
}

int ft_mlx_keyrelease(int keycode, t_env *env)
{
	if (keycode == XK_Up || keycode == 'k')
		env->keys.up = 0;
	else if (keycode == XK_Down || keycode == 'j')
		env->keys.down = 0;
	else if (keycode == XK_Left || keycode == 'h')
		env->keys.left = 0;
	else if (keycode == XK_Right || keycode == 'l')
		env->keys.right = 0;
	return (0);
}

int	ft_update_game(t_env *env)
{
	int	update_needed;

	update_needed = 0;
	if (env->keys.up)
	{
		env->map.player.x += env->map.player.dx * env->map.player.speed;
		env->map.player.y += env->map.player.dy * env->map.player.speed;
		update_needed = 1;
	}
	if (env->keys.down)
	{
		env->map.player.x -= env->map.player.dx * env->map.player.speed;
		env->map.player.y -= env->map.player.dy * env->map.player.speed;
		update_needed = 1;
	}
	if (env->keys.left)
	{
		env->map.player.direction -= 0.04;
		if (env->map.player.direction < 0)
			env->map.player.direction += 2.0f * M_PI;
		env->map.player.dx = cos(env->map.player.direction) * env->map.player.speed;
		env->map.player.dy = sin(env->map.player.direction) * env->map.player.speed;
		update_needed = 1;
	}
	if (env->keys.right)
	{
		env->map.player.direction += 0.04;
		if (env->map.player.direction > 2 * M_PI)
			env->map.player.direction -= 2.0f * M_PI;
		env->map.player.dx = cos(env->map.player.direction) * env->map.player.speed;
		env->map.player.dy = sin(env->map.player.direction) * env->map.player.speed;
		update_needed = 1;
	}
	if (update_needed)
		draw_map(env);
	return (0);
}
