/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   player.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tfalchi <tfalchi@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/08 06:33:12 by julio.formi       #+#    #+#             */
/*   Updated: 2025/04/15 12:38:08 by tfalchi          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

static t_rect	rotate_rect(t_rect rect, t_point center, double angle)
{
	int		i;
	t_rect	rotated_rect;
	t_point	*src_points[4];
	t_point	*dst_points[4];

	src_points[0] = &rect.p0;
	src_points[1] = &rect.p1;
	src_points[2] = &rect.p2;
	src_points[3] = &rect.p3;
	dst_points[0] = &rotated_rect.p0;
	dst_points[1] = &rotated_rect.p1;
	dst_points[2] = &rotated_rect.p2;
	dst_points[3] = &rotated_rect.p3;
	i = -1;
	while (i++, i < 4)
	{
		dst_points[i]->x = center.x + (src_points[i]->x - center.x) * cos(angle)
			+ (src_points[i]->y - center.y) * sin(angle);
		dst_points[i]->y = center.y - (src_points[i]->x - center.x) * sin(angle)
			+ (src_points[i]->y - center.y) * cos(angle);
	}
	return (rotated_rect);
}

void	player(t_env *env)
{
	int		x;
	int		y;
	t_rect	rect;

	x = env->map.player.x;
	y = env->map.player.y;
	rect = (t_rect){
		(t_point){x - 20, y - 10},
		(t_point){x - 20, y + 10},
		(t_point){x, y},
		(t_point){x, y},
	};
	rect = rotate_rect(rect, (t_point){x, y}, env->map.player.direction);
	ft_mlx_draw_rect(env, rect, BLUE, 1);
	ft_mlx_draw_rect(env, rect, RED, 0);
	raycasting(env);
}
