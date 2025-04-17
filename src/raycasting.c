/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   raycasting.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tfalchi <tfalchi@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/10 09:58:29 by julio.formi       #+#    #+#             */
/*   Updated: 2025/04/17 11:24:51 by tfalchi          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

static double calculate_ray_length(t_env *env, double ray_angle)
{
    double ray_dir_x = cos(ray_angle);
    double ray_dir_y = sin(ray_angle);

    int map_x = (int)(env->map.player.x / env->map.size);
    int map_y = (int)(env->map.player.y / env->map.size);

    if (fabs(ray_dir_x) < 0.000001)
        ray_dir_x = 0.000001;
    if (fabs(ray_dir_y) < 0.000001)
        ray_dir_y = 0.000001;

    double delta_dist_x = fabs(1 / ray_dir_x);
    double delta_dist_y = fabs(1 / ray_dir_y);

    int step_x;
    int step_y;
    double side_dist_x;
    double side_dist_y;

    int hit = 0;
    int side = -1;
    double max_dist = 1000.0;

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
    double perpendicular_wall_dist;
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

static double calculate_ray_length_with_texture(t_env *env, double ray_angle, t_raycast *ray)
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
	double max_dist = 1000.0;

	if (ray->ray_dir_x < 0)
	{
		ray->step_x = -1;
		ray->side_dist_x = (env->map.player.x / env->map.size - ray->map_x) * ray->delta_dist_x;
	}
	else
	{
		ray->step_x = 1;
		ray->side_dist_x = (ray->map_x + 1.0 - env->map.player.x / env->map.size) * ray->delta_dist_x;
	}

	if (ray->ray_dir_y < 0)
	{
		ray->step_y = -1;
		ray->side_dist_y = (env->map.player.y / env->map.size - ray->map_y) * ray->delta_dist_y;
	}
	else
	{
		ray->step_y = 1;
		ray->side_dist_y = (ray->map_y + 1.0 - env->map.player.y / env->map.size) * ray->delta_dist_y;
	}

	int iterations = 0;
	while (ray->hit == 0 && iterations < max_dist)
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

		if (ray->map_x >= 0 && ray->map_y >= 0 && ray->map_x < env->map.width && ray->map_y < env->map.height)
		{
			if (env->map.data[ray->map_y][ray->map_x] == 1)
				ray->hit = 1;
		}
		else
			break;

		iterations++;
	}

	if (ray->side == 0)
		ray->perp_wall_dist = (ray->map_x - env->map.player.x / env->map.size +
						(1 - ray->step_x) / 2.0) / ray->ray_dir_x;
	else
		ray->perp_wall_dist = (ray->map_y - env->map.player.y / env->map.size +
						(1 - ray->step_y) / 2.0) / ray->ray_dir_y;

	if (ray->perp_wall_dist < 0)
		ray->perp_wall_dist = 0;

	if (ray->side == 0)
		ray->wall_x = env->map.player.y / env->map.size + ray->perp_wall_dist * ray->ray_dir_y;
	else
		ray->wall_x = env->map.player.x / env->map.size + ray->perp_wall_dist * ray->ray_dir_x;
	ray->wall_x -= floor(ray->wall_x);

	if (ray->side == 0)
	{
		if (ray->ray_dir_x > 0)
			ray->texture = &env->map.east;
		else
			ray->texture = &env->map.west;
	}
	else
	{
		if (ray->ray_dir_y > 0)
			ray->texture = &env->map.south;
		else
			ray->texture = &env->map.north;
	}
	ray->tex_x = (int)(ray->wall_x * (double)ray->texture->width);
	if ((ray->side == 0 && ray->ray_dir_x > 0) ||
		(ray->side == 1 && ray->ray_dir_y < 0))
		ray->tex_x = ray->texture->width - ray->tex_x - 1;

	return (ray->perp_wall_dist * env->map.size);
}

void	raycasting(t_env *env)
{
	int		i;
	double	ray_angle;
	double	ray_length;
	double	fov;
	double	fov_start;
	double	fov_step;
	int		ray_count;

	fov = 60.0 * (M_PI / 180.0);
	ray_count = 60;
	fov_start = env->map.player.direction - (fov / 2.0);
	fov_step = fov / (double)(ray_count - 1);
	i = 0;
	while (i < ray_count)
	{
		ray_angle = fov_start + (fov_step * i);
		while (ray_angle < 0)
			ray_angle += 2 * M_PI;
		while (ray_angle >= 2 * M_PI)
			ray_angle -= 2 * M_PI;

		double ray_dir_x = cos(ray_angle);
		double ray_dir_y = sin(ray_angle);
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

void	raycasting3d(t_env *env)
{
	double	angle;
	t_raycast ray;

	

	if (env->map.player.fov == 0)
		env->map.player.fov = 60.0;
	if (env->map.numrays == 0)
		env->map.numrays = WIN_WIDTH;

	angle = env->map.player.direction - env->map.player.fov * (M_PI / 180.0) / 2.0;

	for (size_t i = 0; i < env->map.numrays; i++)
	{
		while (angle < 0)
			angle += 2 * M_PI;
		while (angle >= 2 * M_PI)
			angle -= 2 * M_PI;

		double ray_length = calculate_ray_length_with_texture(env, angle, &ray);

		double wall_height = (env->map.size * WIN_HEIGHT) / (ray_length * cos(angle - env->map.player.direction));

		double draw_start = ((double)WIN_HEIGHT / 2) - (wall_height / 2);
		double draw_end = ((double)WIN_HEIGHT / 2) + (wall_height / 2);

		if (draw_start < 0)
			draw_start = 0;
		if (draw_end >= WIN_HEIGHT)
			draw_end = WIN_HEIGHT - 1;

		int line_width = ceil((double)WIN_WIDTH / env->map.numrays);
		int line_x = i * ((double)WIN_WIDTH / env->map.numrays);

		double step = (double)ray.texture->height / wall_height;
		double tex_pos = (draw_start - WIN_HEIGHT / 2 + wall_height / 2) * step;

		for (int y = draw_start; y < draw_end; y++)
		{
			int tex_y = (int)tex_pos & (ray.texture->height - 1);
			tex_pos += step;

			int color = ray.texture->data[ray.texture->height * tex_y + ray.tex_x];

			if (ray.side == 1)
				color = (color >> 1) & 8355711;

			for (int w = 0; w < line_width && line_x + w < WIN_WIDTH; w++)
			{
				ft_draw_line_to_image(env, line_x + w, y, color);
			}
		}
		angle += (env->map.player.fov * (M_PI / 180.0)) / env->map.numrays;
	}
}
