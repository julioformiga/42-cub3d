/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_mlx_controls_mouse.c                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tfalchi <tfalchi@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/05 02:19:51 by julio.formi       #+#    #+#             */
/*   Updated: 2025/05/08 12:50:23 by tfalchi          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

int	ft_mlx_button_release(int button, int x, int y, t_env *env)
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

void	handle_right_click(t_env *env)
{
	t_raycast	ray;
	double		ray_angle;
	double		ray_length;
	t_point		hit;

	ray_angle = env->map.player.direction;
	while (ray_angle < 0)
		ray_angle += 2 * M_PI;
	while (ray_angle >= 2 * M_PI)
		ray_angle -= 2 * M_PI;
	ray.dir_x = cos(ray_angle);
	ray.dir_y = sin(ray_angle);
	ray_length = calculate_ray_length(env, &ray, ray_angle, 1);
	hit.x = (int)((env->map.player.x + ray.dir_x * ray_length) / env->map.size);
	hit.y = (int)((env->map.player.y + ray.dir_y * ray_length) / env->map.size);
	if (hit.y >= 0 && hit.y < env->map.height && hit.x >= 0
		&& hit.x < env->map.width && env->map.data[hit.y][hit.x] == 2)
		env->map.data[hit.y][hit.x] = 3;
	else if (hit.y >= 0 && hit.y < env->map.height && hit.x >= 0
		&& hit.x < env->map.width && env->map.data[hit.y][hit.x] == 3)
		env->map.data[hit.y][hit.x] = 2;
}

int	ft_mlx_button(int button, int x, int y, t_env *env)
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

int	ft_mouse_move(t_env *env)
{
	int	x;
	int	y;
	int	delta_x;

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
	if (x < 100 || x > WIN_WIDTH - 100 || y < 100
		|| y > WIN_HEIGHT - 100)
	{
		mlx_mouse_move(env->mlx, env->win, WIN_WIDTH / 2, WIN_HEIGHT / 2);
		env->map.player.mouse_x = WIN_WIDTH / 2;
	}
	return (0);
}
