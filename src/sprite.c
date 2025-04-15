/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sprite.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: julio.formiga <julio.formiga@gmail.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/15 14:46:20 by julio.formiga     #+#    #+#             */
/*   Updated: 2025/04/15 14:46:20 by julio.formiga    ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"
#include <unistd.h>

t_sprite	load_sprite(t_env *env, char *path)
{
	t_sprite	sprite;
	int			width;
	int			height;

	sprite.path = path;
	sprite.img = mlx_xpm_file_to_image(env->mlx, path, &width, &height);
	if (!sprite.img)
		ft_mlx_error("Failed to load sprite image\n");
	sprite.data = (int *)mlx_get_data_addr(sprite.img, &sprite.bpp,
		&sprite.size_line, &sprite.endian);
	sprite.width = width;
	sprite.height = height;
	sprite.frames_count = 3;
	sprite.frame_height = height / sprite.frames_count;
	sprite.current_frame = 0;
	sprite.visible = 1;
	return (sprite);
}

void	set_sprite_frame(t_sprite *sprite, int frame_index)
{
	if (frame_index >= 0 && frame_index < sprite->frames_count)
		sprite->current_frame = frame_index;
}

void	next_sprite_frame(t_sprite *sprite)
{
	sprite->current_frame = (sprite->current_frame + 1) % sprite->frames_count;
}

void	play_sprite_animation(t_env *env)
{
	next_sprite_frame(&env->weapon);
	// next_sprite_frame(&env->weapon);
	// next_sprite_frame(&env->weapon);
}
void	draw_sprite_first_person(t_env *env, t_sprite sprite,
								t_point position, double scale)
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
	while (y < (int)(sprite.frame_height * scale) &&
		y + position.y < WIN_HEIGHT)
	{
		if (position.y + y < 0)
		{
			y++;
			continue;
		}
		x = 0;
		while (x < (int)(sprite.width * scale) &&
			x + position.x < WIN_WIDTH)
		{
			if (position.x + x < 0)
			{
				x++;
				continue;
			}
			sprite_x = x / scale;
			sprite_y = (y / scale) + frame_offset;
			if (sprite_x >= 0 && sprite_x < sprite.width &&
				sprite_y >= 0 && sprite_y < sprite.height)
			{
				color = sprite.data[sprite_y * sprite.width + sprite_x];
				if ((color & 0x00FF00FF) != 0)
				{
					draw_pos.x = position.x + x;
					draw_pos.y = position.y + y;
					ft_draw_line_to_image(env, draw_pos.x, draw_pos.y, color);
				}
			}
			x++;
		}
		y++;
	}
}

void	free_sprite(t_env *env, t_sprite *sprite)
{
	if (sprite && sprite->img)
		mlx_destroy_image(env->mlx, sprite->img);
}
