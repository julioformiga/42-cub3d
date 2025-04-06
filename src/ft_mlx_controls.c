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

static int	ft_mlx_mouse(int button, int x, int y, t_env *env)
{
	(void)x;
	(void)y;
	if (button == 5)
		ft_mlx_keypress('w', env);
	if (button == 4)
		ft_mlx_keypress('s', env);
	return (0);
}

void	ft_mlx_hooks(t_env *env)
{
	mlx_hook(env->win, KeyPress, KeyPressMask, ft_mlx_keypress, env);
	mlx_hook(env->win, ButtonPress, ButtonPressMask, ft_mlx_mouse, env);
	mlx_hook(env->win, DestroyNotify, StructureNotifyMask,
		ft_mlx_destroy_window, env);
}

void	ft_mlx_map_zoom(t_env *env, char zoom)
{
	float	zoom_value;

	zoom_value = 0.1;
	if (zoom == '-')
	{
		env->view.zoom += zoom_value;
		env->init.x--;
		env->init.y--;
	}
	if (zoom == '+' && env->view.zoom > zoom_value + 1)
	{
		env->view.zoom -= zoom_value;
		env->init.x++;
		env->init.y++;
	}
}

void	ft_mlx_map_rotate(t_env *env, char rotate)
{
	if (rotate == 'a')
	{
		env->init.y -= 2;
		env->view.angle += 0.01;
		env->view.angle_rotate += 0.1;
	}
	if (rotate == 'd')
	{
		env->init.y += 2;
		env->view.angle -= 0.01;
		env->view.angle_rotate -= 0.1;
	}
	if (rotate == 'p')
	{
		if (env->view.projection == 2)
			env->view.projection = 1;
		else
			env->view.projection = 2;
		ft_map_draw(env);
	}
}

int	ft_mlx_keypress(int keycode, t_env *env)
{
	if (keycode == XK_Escape || keycode == 'q')
		ft_mlx_destroy_window(env);
	if (keycode == 'w')
		ft_mlx_map_zoom(env, '-');
	if (keycode == 's')
		ft_mlx_map_zoom(env, '+');
	if (ft_strchr("adzxcp", keycode))
		ft_mlx_map_rotate(env, keycode);
	if (keycode == XK_Up || keycode == 'k')
		env->init.y -= 10;
	if (keycode == XK_Down || keycode == 'j')
		env->init.y += 10;
	if (keycode == XK_Left || keycode == 'h')
		env->init.x -= 10;
	if (keycode == XK_Right || keycode == 'l')
		env->init.x += 10;
	if (keycode == 'r')
		env->view.height += 0.05;
	if (keycode == 'f')
		env->view.height -= 0.05;
	ft_map_draw(env);
	return (0);
}
