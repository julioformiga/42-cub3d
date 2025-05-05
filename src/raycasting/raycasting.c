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

double	calculate_ray_length(t_env *env, t_raycast *ray, double ray_angle,
							int visual)
{
	ray->dir_x = cos(ray_angle);
	ray->dir_y = sin(ray_angle);
	ray->map_x = (int)(env->map.player.x / env->map.size);
	ray->map_y = (int)(env->map.player.y / env->map.size);
	ray->delta_dist_x = fabs(1 / ray->dir_x);
	ray->delta_dist_y = fabs(1 / ray->dir_y);
	ray->dir_x = cos(ray_angle);
	ray->dir_y = sin(ray_angle);
	ray->map_x = (int)(env->map.player.x / env->map.size);
	ray->map_y = (int)(env->map.player.y / env->map.size);
	if (fabs(ray->dir_x) < 0.000001)
		ray->dir_x = 0.000001;
	if (fabs(ray->dir_y) < 0.000001)
		ray->dir_y = 0.000001;
	ray->delta_dist_x = fabs(1 / ray->dir_x);
	ray->delta_dist_y = fabs(1 / ray->dir_y);
	ray->hit = 0;
	ray->side = -1;
	ray_calc_walls(env, ray);
	ray_calc_iterations(env, ray, 0, visual);
	ray_calc_perpendicular_distance(env, ray);
	return (ray->perp_wall_dist * env->map.size);
}

void	raycasting(t_env *env)
{
	int		i;
	t_raycast	ray;
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
		ray_length = calculate_ray_length(env, &ray, ray_angle, 0);
		ft_mlx_draw_line(env, (t_point){env->map.player.x, env->map.player.y},
			(t_point){env->map.player.x + ray_dir_x * ray_length,
			env->map.player.y + ray_dir_y * ray_length}, RED);
	}
}
