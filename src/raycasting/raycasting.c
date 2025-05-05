/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   raycasting.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tfalchi <tfalchi@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/10 09:58:29 by julio.formi       #+#    #+#             */
/*   Updated: 2025/04/26 11:26:57 by tfalchi          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

double	calculate_ray_length(t_env *env, double ray_angle, int visual)
{
	double	ray_dir_x;
	double	ray_dir_y;
	int		map_x;
	int		map_y;
	double	delta_dist_x;
	double	delta_dist_y;
	int		step_x;
	int		step_y;
	double	side_dist_x;
	double	side_dist_y;
	int		hit;
	int		side;
	double	max_dist;
	int		iterations;
	double	perpendicular_wall_dist;

	ray_dir_x = cos(ray_angle);
	ray_dir_y = sin(ray_angle);
	map_x = (int)(env->map.player.x / env->map.size);
	map_y = (int)(env->map.player.y / env->map.size);
	delta_dist_x = fabs(1 / ray_dir_x);
	delta_dist_y = fabs(1 / ray_dir_y);
	ray_dir_x = cos(ray_angle);
	ray_dir_y = sin(ray_angle);
	map_x = (int)(env->map.player.x / env->map.size);
	map_y = (int)(env->map.player.y / env->map.size);
	if (fabs(ray_dir_x) < 0.000001)
		ray_dir_x = 0.000001;
	if (fabs(ray_dir_y) < 0.000001)
		ray_dir_y = 0.000001;
	delta_dist_x = fabs(1 / ray_dir_x);
	delta_dist_y = fabs(1 / ray_dir_y);
	hit = 0;
	side = -1;
	max_dist = 1000.0;
	if (ray_dir_x < 0)
	{
		step_x = -1;
		side_dist_x = (env->map.player.x / env->map.size - map_x)
			* delta_dist_x;
	}
	else
	{
		step_x = 1;
		side_dist_x = (map_x + 1.0 - env->map.player.x / env->map.size)
			* delta_dist_x;
	}
	if (ray_dir_y < 0)
	{
		step_y = -1;
		side_dist_y = (env->map.player.y / env->map.size - map_y)
			* delta_dist_y;
	}
	else
	{
		step_y = 1;
		side_dist_y = (map_y + 1.0 - env->map.player.y / env->map.size)
			* delta_dist_y;
	}
	iterations = 0;
	while (hit == 0 && iterations < max_dist)
	{
		if (side_dist_x < side_dist_y)
		{
			side_dist_x += delta_dist_x;
			map_x += step_x;
			side = 0;
		}
		else
		{
			side_dist_y += delta_dist_y;
			map_y += step_y;
			side = 1;
		}
		if (map_x >= 0 && map_y >= 0 && map_x < env->map.width
			&& map_y < env->map.height)
		{
			if (visual == 1)
			{
				if (env->map.data[map_y][map_x] == 1
					|| env->map.data[map_y][map_x] == 2
					|| env->map.data[map_y][map_x] == 3)
					hit = 1;
			}
			else
			{
				if (env->map.data[map_y][map_x] == 1
					|| env->map.data[map_y][map_x] == 2)
					hit = 1;
			}
		}
		else
			break ;
		iterations++;
	}
	if (side == 0)
		perpendicular_wall_dist = (map_x - env->map.player.x / env->map.size
				+ (1 - step_x) / 2.01) / ray_dir_x;
	else
		perpendicular_wall_dist = (map_y - env->map.player.y / env->map.size
				+ (1 - step_y) / 2.01) / ray_dir_y;
	if (perpendicular_wall_dist < 0)
		perpendicular_wall_dist = 0;
	return (perpendicular_wall_dist * env->map.size);
}

void	raycasting(t_env *env)
{
	int		i;
	double	ray_angle;
	double	ray_length;
	double	angle;
	double	fov_start;
	double	fov_step;
	double	ray_dir_x;
	double	ray_dir_y;

	angle = env->map.player.fov * (M_PI / 180.0);
	fov_start = env->map.player.direction - (angle / 2.0);
	fov_step = angle / (double)(env->map.numrays - 1);
	i = -1;
	while (i++, i < env->map.numrays)
	{
		ray_angle = fov_start + (fov_step * i);
		while (ray_angle < 0)
			ray_angle += 2 * M_PI;
		while (ray_angle >= 2 * M_PI)
			ray_angle -= 2 * M_PI;
		ray_dir_x = cos(ray_angle);
		ray_dir_y = sin(ray_angle);
		ray_length = calculate_ray_length(env, ray_angle, 0);
		ft_mlx_draw_line(env, (t_point){env->map.player.x, env->map.player.y},
			(t_point){env->map.player.x + ray_dir_x * ray_length,
			env->map.player.y + ray_dir_y * ray_length}, RED);
	}
}
