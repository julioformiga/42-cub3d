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
		ray->texture = &env->map.door;
	else if (ray->side == 0)
	{
		if (ray->dir_x > 0)
			ray->texture = &env->map.east;
		else
			ray->texture = &env->map.west;
	}
	else if (ray->dir_y > 0)
		ray->texture = &env->map.south;
	else
		ray->texture = &env->map.north;
	ray->tex_x = (int)(ray->wall_x * (double)ray->texture->width);
	if ((ray->side == 0 && ray->dir_x > 0) || (ray->side == 1
			&& ray->dir_y < 0))
		ray->tex_x = ray->texture->width - ray->tex_x - 1;
}

static void	raycasting3d_setup(t_env *env, t_raycast3d *r3)
{
	r3->wall_height = (env->map.size * WIN_HEIGHT)
		/ (r3->ray_length * cos(r3->angle - env->map.player.direction));
	r3->draw_start = ((double)WIN_HEIGHT / 2) - (r3->wall_height / 2);
	r3->draw_end = ((double)WIN_HEIGHT / 2) + (r3->wall_height / 2);
	if (r3->draw_start < 0)
		r3->draw_start = 0;
	if (r3->draw_end >= WIN_HEIGHT)
		r3->draw_end = WIN_HEIGHT - 1;
	r3->line_width = ceil((double)WIN_WIDTH / env->map.numrays);
	r3->line_x = r3->i * ((double)WIN_WIDTH / env->map.numrays);
	r3->y = r3->draw_start - 1;
}

static void	raycasting3d_drawline(t_env *env, t_raycast *ray, t_raycast3d *r3)
{
	r3->tex_y = (int)r3->tex_pos & (ray->texture->height - 1);
	r3->tex_pos += r3->step;
	r3->color = ray->texture->data[ray->texture->height
		* r3->tex_y + ray->tex_x];
	if (ray->side == 1)
		r3->color = (r3->color >> 1) & 8355711;
	r3->w = -1;
	while (r3->w++, r3->w < r3->line_width && r3->line_x + r3->w < WIN_WIDTH)
		ft_draw_line_to_image(env, r3->line_x + r3->w, r3->y, r3->color);
}

void	raycasting3d(t_env *env)
{
	t_raycast3d	r3;
	t_raycast	ray;

	r3.angle = env->map.player.direction - env->map.player.fov * (M_PI / 180.0)
		/ 2.0;
	r3.i = -1;
	while (r3.i++, r3.i < env->map.numrays)
	{
		while (r3.angle < 0)
			r3.angle += 2 * M_PI;
		while (r3.angle >= 2 * M_PI)
			r3.angle -= 2 * M_PI;
		r3.ray_length = ray_calc_length(env, &ray, r3.angle);
		ray_texture(env, &ray);
		raycasting3d_setup(env, &r3);
		r3.step = (double)ray.texture->height / r3.wall_height;
		r3.tex_pos = (r3.draw_start - WIN_HEIGHT / 2 + r3.wall_height / 2)
			* r3.step;
		while (r3.y++, r3.y < r3.draw_end)
			raycasting3d_drawline(env, &ray, &r3);
		r3.angle += (env->map.player.fov * (M_PI / 180.0)) / env->map.numrays;
	}
}
