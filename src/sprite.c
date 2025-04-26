/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sprite.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tfalchi <tfalchi@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/15 14:46:20 by julio.formi       #+#    #+#             */
/*   Updated: 2025/04/26 11:27:00 by tfalchi          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

void	sprite_load(t_env *env, char *path)
{
	int	width;
	int	height;

	env->weapon.path = path;
	env->weapon.img = mlx_xpm_file_to_image(env->mlx, path, &width, &height);
	if (!env->weapon.img)
		ft_mlx_error("Failed to load sprite image\n");
	env->weapon.data = (int *)mlx_get_data_addr(env->weapon.img,
			&env->weapon.bpp, &env->weapon.size_line, &env->weapon.endian);
	env->weapon.width = width;
	env->weapon.height = height;
	env->weapon.frames_count = 3;
	env->weapon.frame_height = height / env->weapon.frames_count;
	env->weapon.current_frame = 0;
	env->weapon.visible = 1;
}

void	sprite_set_frame(t_sprite *sprite, int frame_index)
{
	if (frame_index >= 0 && frame_index < sprite->frames_count)
		sprite->current_frame = frame_index;
}
void	sprite_play(t_sprite *sprite)
{
	if (sprite->animating)
		return ;
	sprite_set_frame(sprite, 1);
	sprite->animating = 1;
	sprite->anim_start_time = clock();
	sprite->anim_duration = 200;
}

void	sprite_update_animation(t_sprite *sprite)
{
	clock_t	current_time;
	double	elapsed_ms;

	if (sprite->animating)
	{
		current_time = clock();
		elapsed_ms = (double)(current_time - sprite->anim_start_time)
			/ CLOCKS_PER_SEC * 1000;
		if (elapsed_ms >= sprite->anim_duration)
		{
			if (sprite->current_frame == 1)
				sprite_set_frame(sprite, 2);
			else
				sprite_set_frame(sprite, 1);
			sprite->anim_start_time = clock();
		}
	}
}

void	sprite_draw(t_env *env, t_sprite sprite, t_point position, double scale)
{
	int		x;
	int		y;
	int		color;
	int		sprite_x;
	int		sprite_y;
	t_point	draw_pos;
	int		frame_offset;

	frame_offset = sprite.current_frame * sprite.frame_height;
	if (!sprite.visible)
		return ;
	y = 0;
	while (y < (int)(sprite.frame_height * scale) && y
		+ position.y < WIN_HEIGHT)
	{
		if (position.y + y < 0)
		{
			y++;
			continue ;
		}
		x = 0;
		while (x < (int)(sprite.width * scale) && x + position.x < WIN_WIDTH)
		{
			if (position.x + x < 0)
			{
				x++;
				continue ;
			}
			sprite_x = x / scale;
			sprite_y = (y / scale) + frame_offset;
			if (sprite_x >= 0 && sprite_x < sprite.width && sprite_y >= 0
				&& sprite_y < sprite.height)
			{
				color = sprite.data[sprite_y * sprite.width + sprite_x];
				if ((color & 0x00FF00FF) != 0)
				{
					draw_pos.x = position.x + x;
					draw_pos.y = position.y + y;
					ft_draw_line_to_image(env, draw_pos.x - 75, draw_pos.y,
						color);
				}
			}
			x++;
		}
		y++;
	}
}
