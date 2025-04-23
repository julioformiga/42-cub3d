/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_mlx_controls.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tfalchi <tfalchi@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/05 02:19:51 by julio.formi       #+#    #+#             */
/*   Updated: 2025/04/23 12:40:59 by tfalchi          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

void	handle_right_click(t_env *env)
{
	double	ray_angle;
	double	ray_dir_x;
	double	ray_dir_y;
	double	ray_length;
	int		hit_x;
	int		hit_y;

	ray_angle = env->map.player.direction;
	while (ray_angle < 0)
		ray_angle += 2 * M_PI;
	while (ray_angle >= 2 * M_PI)
		ray_angle -= 2 * M_PI;
	ray_dir_x = cos(ray_angle);
	ray_dir_y = sin(ray_angle);
	ray_length = calculate_ray_length(env, ray_angle, 1);
	hit_x = (int)((env->map.player.x + ray_dir_x * ray_length) / env->map.size);
	hit_y = (int)((env->map.player.y + ray_dir_y * ray_length) / env->map.size);
	
	if (hit_y >= 0 && hit_y < env->map.height && hit_x >= 0
		&& hit_x < env->map.width && env->map.data[hit_y][hit_x] == 2)
	{
		env->map.data[hit_y][hit_x] = 3;
	}
	else if (hit_y >= 0 && hit_y < env->map.height && hit_x >= 0
		&& hit_x < env->map.width && env->map.data[hit_y][hit_x] == 3)
	{
		env->map.data[hit_y][hit_x] = 2;
	}
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
	if (button == 3)
		handle_right_click(env);
	return (0);
}

int	ft_mouse_move(void *param)
{
	t_env	*env;
	int		x;
	int		y;
	int		delta_x;

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
		env->map.player.dx = cos(env->map.player.direction)
			* env->map.player.speed;
		env->map.player.dy = sin(env->map.player.direction)
			* env->map.player.speed;
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
