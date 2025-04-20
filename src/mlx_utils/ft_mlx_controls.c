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

void	ft_mlx_hooks(t_env *env)
{
	int	x;
	int	y;

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
	mlx_hook(env->win, ButtonRelease, ButtonReleaseMask, ft_mlx_button_release,
		env);
	mlx_hook(env->win, DestroyNotify, StructureNotifyMask,
		ft_mlx_destroy_window, env);
	mlx_loop_hook(env->mlx, ft_update_game, env);
}

int	ft_mlx_keypress(int keycode, t_env *env)
{
	if (keycode == XK_Escape || keycode == 'q')
		ft_mlx_destroy_window(env);
	else if (keycode == XK_Up || keycode == 'w')
		env->keys.up = 1;
	else if (keycode == XK_Down || keycode == 's')
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
	}
	else if (keycode == '+')
	{
		if (env->map.player.mouse_speed < 0.01)
			env->map.player.mouse_speed += 0.0002;
	}
	return (0);
}

int	ft_mlx_keyrelease(int keycode, t_env *env)
{
	if (keycode == XK_Up || keycode == 'w')
		env->keys.up = 0;
	else if (keycode == XK_Down || keycode == 's')
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
