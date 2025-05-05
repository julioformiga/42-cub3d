/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   raycasting3d.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tfalchi <tfalchi@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/27 18:44:40 by julio.formi       #+#    #+#             */
/*   Updated: 2025/05/05 15:20:50 by tfalchi          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

static void	ray_texture(t_env *env, t_raycast *ray)
{
	if (ray->side == 0)
		ray->wall_x = env->map.player.y / env->map.size
			+ ray->perp_wall_dist * ray->dir_y;
	else
		ray->wall_x = env->map.player.x / env->map.size
			+ ray->perp_wall_dist * ray->dir_x;
	ray->wall_x -= floor(ray->wall_x);
	if (ray->map_value == 2)
	{
		ray->texture = &env->map.door;
	}
	else if (ray->side == 0)
	{
		if (ray->dir_x > 0)
			ray->texture = &env->map.east;
		else
			ray->texture = &env->map.west;
	}
	else
	{
		if (ray->dir_y > 0)
			ray->texture = &env->map.south;
		else
			ray->texture = &env->map.north;
	}
	ray->tex_x = (int)(ray->wall_x * (double)ray->texture->width);
	if ((ray->side == 0 && ray->dir_x > 0) || (ray->side == 1
			&& ray->dir_y < 0))
		ray->tex_x = ray->texture->width - ray->tex_x - 1;
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
	size_t		i;
	int			y;
	int			w;

	angle = env->map.player.direction - env->map.player.fov * (M_PI / 180.0)
		/ 2.0;
	i = -1;
	while (i++, i < env->map.numrays)
	{
		while (angle < 0)
			angle += 2 * M_PI;
		while (angle >= 2 * M_PI)
			angle -= 2 * M_PI;
		ray_length = ray_calc_length(env, &ray, angle);
		ray_texture(env, &ray);
		wall_height = (env->map.size * WIN_HEIGHT)
			/ (ray_length * cos(angle - env->map.player.direction));
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
		y = draw_start - 1;
		while (y++, y < draw_end)
		{
			tex_y = (int)tex_pos & (ray.texture->height - 1);
			tex_pos += step;
			color = ray.texture->data[ray.texture->height * tex_y + ray.tex_x];
			if (ray.side == 1)
				color = (color >> 1) & 8355711;
			w = -1;
			while (++w, w < line_width && line_x + w < WIN_WIDTH)
				ft_draw_line_to_image(env, line_x + w, y, color);
		}
		angle += (env->map.player.fov * (M_PI / 180.0)) / env->map.numrays;
	}
}
