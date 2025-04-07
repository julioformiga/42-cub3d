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
	mlx_hook(env->win, KeyPress, KeyPressMask, ft_mlx_keypress, env);
	mlx_hook(env->win, DestroyNotify, StructureNotifyMask,
			 ft_mlx_destroy_window, env);
}

int ft_mlx_keypress(int keycode, t_env *env)
{
	if (keycode == XK_Escape || keycode == 'q')
		ft_mlx_destroy_window(env);
	if (keycode == XK_Up || keycode == 'k')
	{
		env->map.player_x += env->map.pdx;
		env->map.player_y += env->map.pdy;
	}
	if (keycode == XK_Down || keycode == 'j')
	{
		env->map.player_x -= env->map.pdx;
		env->map.player_y -= env->map.pdy;
	}
	if (keycode == XK_Left || keycode == 'h')
	{
		env->map.player_direction -= 0.1;
		if (env->map.player_direction < 0)
		{
			env->map.player_direction += 2 * M_PI;
		}
		env->map.pdx = cos(env->map.player_direction) * 5;
		env->map.pdy = sin(env->map.player_direction) * 5;
	}
	if (keycode == XK_Right || keycode == 'l')
	{
		env->map.player_direction += 0.1;
		if (env->map.player_direction > 2 * M_PI)
		{
			env->map.player_direction -= 2 * M_PI;
		}
		env->map.pdx = cos(env->map.player_direction) * 5;
		env->map.pdy = sin(env->map.player_direction) * 5;
	}
	ft_map_draw(env);
	return (0);
}
