/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   player.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: julio.formiga <julio.formiga@gmail.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/08 06:33:12 by julio.formiga     #+#    #+#             */
/*   Updated: 2025/04/08 06:33:12 by julio.formiga    ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

static t_rect rotate_rect(t_rect rect, t_point center, float angle)
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

void	player(t_env *env)
{
	int		x;
	int		y;
	int		width;
	int		ray_length;
	t_rect	rect;

	width = 20;
	ray_length = 150;
	x = env->map.player.x;
	y = env->map.player.y;
	rect = (t_rect){
		(t_point){x + 10, y - 10},
		(t_point){x + 10, y - 10},
		(t_point){x + 27, y + 27},
		(t_point){x - 10, y + 27},
	};
	ft_mlx_draw_square(env, (t_point){x, y}, width, RED);
	rect = rotate_rect(rect, (t_point){x + 10, y + 13}, env->map.player.direction);
	ft_mlx_draw_rect(env, rect, BLUE, 1);
	width = width / 2;
	ft_mlx_draw_line(env,
		(t_point){x + (width), y + (width)},
		(t_point){
		(x + ((float)width)) + env->map.player.dx * ray_length,
		(y + ((float)width)) + env->map.player.dy * ray_length,
	},
		YELLOW);
}
