/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   raycasting3d.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: julio.formiga <julio.formiga@gmail.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/27 18:44:40 by julio.formiga     #+#    #+#             */
/*   Updated: 2025/04/27 18:44:40 by julio.formiga    ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

static double	calculate_ray_length_with_texture(t_env *env, double ray_angle,
		t_raycast *ray)

{
	double	max_dist;
	int		iterations;

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
	max_dist = 1000.0;
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
	iterations = 0;
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
		if (ray->map_x >= 0 && ray->map_y >= 0 && ray->map_x < env->map.width
			&& ray->map_y < env->map.height)
		{
			if (env->map.data[ray->map_y][ray->map_x] == 1
				|| env->map.data[ray->map_y][ray->map_x] == 2)
				ray->hit = 1;
		}
		else
			break ;
		iterations++;
	}
	if (ray->side == 0)
		ray->perp_wall_dist = (ray->map_x - env->map.player.x / env->map.size
				+ (1 - ray->step_x) / 2.0) / ray->ray_dir_x;
	else
		ray->perp_wall_dist = (ray->map_y - env->map.player.y / env->map.size
				+ (1 - ray->step_y) / 2.0) / ray->ray_dir_y;
	if (ray->perp_wall_dist < 0)
		ray->perp_wall_dist = 0;
	if (ray->side == 0)
		ray->wall_x = env->map.player.y / env->map.size + ray->perp_wall_dist
			* ray->ray_dir_y;
	else
		ray->wall_x = env->map.player.x / env->map.size + ray->perp_wall_dist
			* ray->ray_dir_x;
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
	if ((ray->side == 0 && ray->ray_dir_x > 0) || (ray->side == 1
			&& ray->ray_dir_y < 0))
		ray->tex_x = ray->texture->width - ray->tex_x - 1;
	return (ray->perp_wall_dist * env->map.size);
}

void	raycasting3d(t_env *env)
{
	double		angle;
	t_raycast	ray;
	double		ray_length;
	double		wall_height;
	double		draw_start;
	double		draw_end;
	int			line_width;
	int			line_x;
	double		step;
	double		tex_pos;
	int			tex_y;
	int			color;

	if (env->map.player.fov == 0)
		env->map.player.fov = 60.0;
	if (env->map.numrays == 0)
		env->map.numrays = WIN_WIDTH;
	angle = env->map.player.direction - env->map.player.fov * (M_PI / 180.0)
		/ 2.0;
	for (size_t i = 0; i < env->map.numrays; i++)
	{
		while (angle < 0)
			angle += 2 * M_PI;
		while (angle >= 2 * M_PI)
			angle -= 2 * M_PI;
		ray_length = calculate_ray_length_with_texture(env, angle, &ray);
		wall_height = (env->map.size * WIN_HEIGHT) / (ray_length * cos(angle
					- env->map.player.direction));
		draw_start = ((double)WIN_HEIGHT / 2) - (wall_height / 2);
		draw_end = ((double)WIN_HEIGHT / 2) + (wall_height / 2);
		if (draw_start < 0)
			draw_start = 0;
		if (draw_end >= WIN_HEIGHT)
			draw_end = WIN_HEIGHT - 1;
		line_width = ceil((double)WIN_WIDTH / env->map.numrays);
		line_x = i * ((double)WIN_WIDTH / env->map.numrays);
		step = (double)ray.texture->height / wall_height;
		tex_pos = (draw_start - WIN_HEIGHT / 2 + wall_height / 2) * step;
		for (int y = draw_start; y < draw_end; y++)
		{
			tex_y = (int)tex_pos & (ray.texture->height - 1);
			tex_pos += step;
			color = ray.texture->data[ray.texture->height * tex_y + ray.tex_x];
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
