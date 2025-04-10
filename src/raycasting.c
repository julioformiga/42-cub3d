/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   raycasting.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tfalchi <tfalchi@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/10 09:58:29 by julio.formi       #+#    #+#             */
/*   Updated: 2025/04/10 15:25:36 by tfalchi          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

static float calculate_ray_length(t_env *env, float ray_angle)
{
	float ray_dir_x = cos(ray_angle);
	float ray_dir_y = sin(ray_angle);

	int map_x = (int)(env->map.player.x / env->map.size);
	int map_y = (int)(env->map.player.y / env->map.size);

	if (fabs(ray_dir_x) < 0.000001)
		ray_dir_x = 0.000001;
	if (fabs(ray_dir_y) < 0.000001)
		ray_dir_y = 0.000001;

	float delta_dist_x = fabs(1 / ray_dir_x);
	float delta_dist_y = fabs(1 / ray_dir_y);

	int step_x;
	int step_y;
	float side_dist_x;
	float side_dist_y;

	int hit = 0;
	int side = -1;
	float max_dist = 1000.0;

	if (ray_dir_x < 0)
	{
		step_x = -1;
		side_dist_x = (env->map.player.x / env->map.size - map_x) * delta_dist_x;
	}
	else
	{
		step_x = 1;
		side_dist_x = (map_x + 1.0 - env->map.player.x / env->map.size) * delta_dist_x;
	}

	if (ray_dir_y < 0)
	{
		step_y = -1;
		side_dist_y = (env->map.player.y / env->map.size - map_y) * delta_dist_y;
	}
	else
	{
		step_y = 1;
		side_dist_y = (map_y + 1.0 - env->map.player.y / env->map.size) * delta_dist_y;
	}

	int iterations = 0;
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

		if (map_x >= 0 && map_y >= 0 && map_x < env->map.width && map_y < env->map.height)
		{
			if (env->map.data[map_y][map_x] == 1)
				hit = 1;
		}
		else
			break;
		iterations++;
	}
	float perpendicular_wall_dist;
	if (side == 0)
		perpendicular_wall_dist = (map_x - env->map.player.x / env->map.size +
								(1 - step_x) / 2.0) / ray_dir_x;
	else
		perpendicular_wall_dist = (map_y - env->map.player.y / env->map.size +
								(1 - step_y) / 2.0) / ray_dir_y;

	if (perpendicular_wall_dist < 0)
		perpendicular_wall_dist = 0;

	return (perpendicular_wall_dist * env->map.size);
}

void draw_3d_map(t_env *env, float ray_length, int x_position)
{
    int wall_height = (int)(WIN_HEIGHT / (ray_length));
    int wall_top = (WIN_HEIGHT - wall_height) / 2;
    int wall_bottom = wall_top + wall_height;
    t_rect wall_rect = {
        (t_point){x_position, wall_top},
        (t_point){x_position, wall_bottom},
        (t_point){x_position + env->map.size, wall_bottom},
        (t_point){x_position + env->map.size, wall_top}
    };
    ft_mlx_draw_rect(env, wall_rect, YELLOW, 1);
}

void	raycasting(t_env *env)
{
	int		i;
	float	ray_angle;
	float	ray_length;
	float	fov;
	float	fov_start;
	float	fov_step;
	int		ray_count;

	fov = 60.0f * (M_PI / 180.0f);
	ray_count = 60;
	fov_start = env->map.player.direction - (fov / 2.0f);
	fov_step = fov / (float)(ray_count - 1);
	i = 0;
	while (i < ray_count)
	{
		ray_angle = fov_start + (fov_step * i);
		while (ray_angle < 0)
			ray_angle += 2 * M_PI;
		while (ray_angle >= 2 * M_PI)
			ray_angle -= 2 * M_PI;

		float ray_dir_x = cos(ray_angle);
		float ray_dir_y = sin(ray_angle);
		ray_length = calculate_ray_length(env, ray_angle);
		int x_position = i * (WIN_WIDTH / ray_count);
		draw_3d_map(env, ray_length, x_position);
		ft_mlx_draw_line(
			env,
			(t_point){env->map.player.x, env->map.player.y},
			(t_point){
				env->map.player.x + ray_dir_x * ray_length,
				env->map.player.y + ray_dir_y * ray_length
			},
			RED
		);
		i++;
	}
}
