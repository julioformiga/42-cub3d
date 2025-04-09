/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   player.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tfalchi <tfalchi@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/08 06:33:12 by julio.formi       #+#    #+#             */
/*   Updated: 2025/04/09 17:30:40 by tfalchi          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

static t_rect	rotate_rect(t_rect rect, t_point center, float angle)
{
	t_rect	rotated_rect;
	float	cos_angle;
	float	sin_angle;
	t_point	*src_points[4];
	t_point	*dst_points[4];

	cos_angle = cos(angle);
	sin_angle = sin(angle);
	src_points[0] = &rect.p0;
	src_points[1] = &rect.p1;
	src_points[2] = &rect.p2;
	src_points[3] = &rect.p3;
	dst_points[0] = &rotated_rect.p0;
	dst_points[1] = &rotated_rect.p1;
	dst_points[2] = &rotated_rect.p2;
	dst_points[3] = &rotated_rect.p3;
	for (int i = 0; i < 4; i++)
	{
		dst_points[i]->x = center.x + (src_points[i]->x - center.x) * cos_angle
			- (src_points[i]->y - center.y) * sin_angle;
		dst_points[i]->y = center.y + (src_points[i]->x - center.x) * sin_angle
			+ (src_points[i]->y - center.y) * cos_angle;
	}
	return (rotated_rect);
}

static float calculate_ray_length(t_env *env, float ray_angle)
{
    float ray_dir_x = cos(ray_angle);
    float ray_dir_y = sin(ray_angle);

	int map_size = 30;

    int map_x = (int)(env->map.player.x / map_size);
    int map_y = (int)(env->map.player.y / map_size);

    float delta_dist_x = fabs(1 / ray_dir_x);
    float delta_dist_y = fabs(1 / ray_dir_y);

    int step_x;
    int step_y;
    float side_dist_x;
    float side_dist_y;

    int hit = 0;
    int side = -1;
    float max_dist = 1000.0;
    float dist = 0;

    float perpendicular_wall_dist;

	if (ray_dir_x < 0)
    {
        step_x = -1;
        side_dist_x = (env->map.player.x / map_size - map_x) * delta_dist_x;
    }
    else
    {
        step_x = 1;
        side_dist_x = (map_x + 1.0 - env->map.player.x / map_size) * delta_dist_x;
    }

    if (ray_dir_y < 0)
    {
        step_y = -1;
        side_dist_y = (env->map.player.y / map_size - map_y) * delta_dist_y;
    }
    else
    {
        step_y = 1;
        side_dist_y = (map_y + 1.0 - env->map.player.y / map_size) * delta_dist_y;
    }

    while (hit == 0 && dist < max_dist)
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
        dist += 1.0;
    }
    if (side == 0)
        perpendicular_wall_dist = ((map_x - env->map.player.x / map_size + (1 - step_x) / 2) / ray_dir_x) / 1.5;
    else
        perpendicular_wall_dist = ((map_y - env->map.player.y / map_size + (1 - step_y) / 2) / ray_dir_y) / 1.5;
    return perpendicular_wall_dist * map_size;
}

void	player(t_env *env)
{
	int		x;
	int		y;
	int		width;
	float	ray_length;
	t_rect	rect;

	width = 20;

	x = env->map.player.x;
	y = env->map.player.y;
	rect = (t_rect){
		(t_point){x - 20, y - 20},
		(t_point){x - 20, y + 20},
		(t_point){x, y},
		(t_point){x, y},
	};
	rect = rotate_rect(rect, (t_point){x, y}, env->map.player.direction);
	ft_mlx_draw_rect(env, rect, BLUE, 1);
	ft_mlx_draw_rect(env, rect, RED, 0);

	ray_length = calculate_ray_length(env, env->map.player.direction);

	if (ray_length < 10)
		ray_length = 10;
	if (ray_length > 1000)
		ray_length = 1000;

	width = width / 2;
	ft_mlx_draw_line(env,
		(t_point){x, y},
		(t_point){
		x + env->map.player.dx * ray_length,
		y + env->map.player.dy * ray_length,
	},
		RED);
}
