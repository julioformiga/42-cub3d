/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sprite_draw.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: julio.formiga <julio.formiga@gmail.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/27 03:29:34 by julio.formiga     #+#    #+#             */
/*   Updated: 2025/04/27 03:29:34 by julio.formiga    ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

static t_point	get_sprite_position(t_point pos_dest, double scale,
									int frame_offset)
{
	t_point	sprite_pos;

	sprite_pos.x = pos_dest.x / scale;
	sprite_pos.y = (pos_dest.y / scale) + frame_offset;
	return (sprite_pos);
}

static void	sprite_draw_pixel(t_sprite_context *ctx, t_point pos_dest)
{
	t_point	sprite_pos;
	t_point	draw_pos;
	int		color;

	sprite_pos = get_sprite_position(pos_dest, ctx->sprite.scale,
			ctx->frame_offset);
	if (sprite_pos.x >= 0 && sprite_pos.x < ctx->sprite.width
		&& sprite_pos.y >= 0 && sprite_pos.y < ctx->sprite.height)
	{
		color = ctx->sprite.data[sprite_pos.y * ctx->sprite.width
			+ sprite_pos.x];
		if ((color & 0x00FF00FF) != 0)
		{
			draw_pos.x = ctx->position.x + pos_dest.x;
			draw_pos.y = ctx->position.y + pos_dest.y;
			ft_draw_line_to_image(ctx->env, draw_pos.x - 75,
				draw_pos.y, color);
		}
	}
}

static void	sprite_draw_row(t_sprite_context *ctx, t_point pos_dest)
{
	pos_dest.x = 0;
	while (pos_dest.x < (int)(ctx->sprite.width * ctx->sprite.scale)
		&& pos_dest.x + ctx->position.x < WIN_WIDTH)
	{
		if (ctx->position.x + pos_dest.x < 0)
		{
			pos_dest.x++;
			continue ;
		}
		sprite_draw_pixel(ctx, pos_dest);
		pos_dest.x++;
	}
}

void	sprite_draw(t_env *env, t_sprite sprite, t_point position)
{
	t_sprite_context	ctx;
	t_point				pos_dest;

	ctx.env = env;
	ctx.sprite = sprite;
	ctx.position = position;
	ctx.frame_offset = sprite.current_frame * sprite.frame_height;
	if (!sprite.visible)
		return ;
	pos_dest.y = 0;
	while (pos_dest.y < (int)(sprite.frame_height * sprite.scale) && pos_dest.y
		+ position.y < WIN_HEIGHT)
	{
		if (position.y + pos_dest.y < 0)
		{
			pos_dest.y++;
			continue ;
		}
		sprite_draw_row(&ctx, pos_dest);
		pos_dest.y++;
	}
}
