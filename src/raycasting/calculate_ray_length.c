/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   calculate_ray_length.c                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: julio.formiga <julio.formiga@gmail.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/05 03:05:41 by julio.formiga     #+#    #+#             */
/*   Updated: 2025/05/05 03:05:41 by julio.formiga    ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

void	ray_calc_walls(t_env *env, t_raycast *ray)
{
	if (ray->ray_dir_x < 0)
	{
		ray->step_x = -1;
		ray->side_dist_x = (env->map.player.x / env->map.size - ray->map_x)
			* ray->delta_dist_x;
	}
	else
	{
		ray->step_x = 1;
		ray->side_dist_x = (ray->map_x + 1.0 - env->map.player.x
				/ env->map.size) * ray->delta_dist_x;
	}
	if (ray->ray_dir_y < 0)
	{
		ray->step_y = -1;
		ray->side_dist_y = (env->map.player.y / env->map.size - ray->map_y)
			* ray->delta_dist_y;
	}
	else
	{
		ray->step_y = 1;
		ray->side_dist_y = (ray->map_y + 1.0 - env->map.player.y
				/ env->map.size) * ray->delta_dist_y;
	}
}

void	ray_calc_iterations(t_env *env, t_raycast *ray, int iterations, int visual)
{
	while (ray->hit == 0 && iterations < env->map.player.max_ray_distance)
	{
		if (ray->side_dist_x < ray->side_dist_y)
		{
			ray->side_dist_x += ray->delta_dist_x;
			ray->map_x += ray->step_x;
			ray->side = 0;
		}
		else
		{
			ray->side_dist_y += ray->delta_dist_y;
			ray->map_y += ray->step_y;
			ray->side = 1;
		}
		if (ray->map_x >= 0 && ray->map_y >= 0 && ray->map_x < env->map.width
			&& ray->map_y < env->map.height)
		{
			if (visual == 1)
			{
				if (env->map.data[ray->map_y][ray->map_x] == 1
					|| env->map.data[ray->map_y][ray->map_x] == 2
					|| env->map.data[ray->map_y][ray->map_x] == 3)
					ray->hit = 1;
			}
			else
			{
				if (env->map.data[ray->map_y][ray->map_x] == 1
					|| env->map.data[ray->map_y][ray->map_x] == 2)
					ray->hit = 1;
			}
		}
		else
			break ;
		iterations++;
	}
}

void	ray_calc_perpendicular_distance(t_env *env, t_raycast *ray)
{
	if (ray->side == 0)
		ray->perp_wall_dist = (ray->map_x - env->map.player.x / env->map.size
				+ (1 - ray->step_x) / 2.01) / ray->ray_dir_x;
	else
		ray->perp_wall_dist = (ray->map_y - env->map.player.y / env->map.size
				+ (1 - ray->step_y) / 2.01) / ray->ray_dir_y;
	if (ray->perp_wall_dist < 0)
		ray->perp_wall_dist = 0;
}

double	ray_calc_length(t_env *env, t_raycast *ray, double ray_angle)
{
	ray->ray_dir_x = cos(ray_angle);
	ray->ray_dir_y = sin(ray_angle);
	ray->map_x = (int)(env->map.player.x / env->map.size);
	ray->map_y = (int)(env->map.player.y / env->map.size);
	if (fabs(ray->ray_dir_x) < 0.000001)
		ray->ray_dir_x = 0.000001;
	if (fabs(ray->ray_dir_y) < 0.000001)
		ray->ray_dir_y = 0.000001;
	ray->delta_dist_x = fabs(1 / ray->ray_dir_x);
	ray->delta_dist_y = fabs(1 / ray->ray_dir_y);
	ray->hit = 0;
	ray->side = -1;
	ray_calc_walls(env, ray);
	ray_calc_iterations(env, ray, 0, 0);
	ray_calc_perpendicular_distance(env, ray);
	return (ray->perp_wall_dist * env->map.size);
}
