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

void	player(t_env *env)
{
	int		x;
	int		y;
	t_rect	rect;

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

	env->map.player.dx = cos(env->map.player.direction);
	env->map.player.dy = sin(env->map.player.direction);

	raycasting(env);
}
