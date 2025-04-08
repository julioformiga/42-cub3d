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

void player(t_env *env)
{
	int x;
	int y;
	int width = 20;

	x = env->map.player.x;
	y = env->map.player.y;
	ft_mlx_draw_square(env, (t_point){x, y}, width, RED);
	width = width / 2;
	ft_mlx_draw_line(env,
				  (t_point){x + (width), y + (width)},
				  (t_point){
					(x + ((float)width)) + env->map.player.dx * 5,
					(y + ((float)width)) + env->map.player.dy * 5
				  },
			YELLOW);
	// printf("Player x, y: %d, %d\n", x, y);
	// printf("Player direction: %f\n", env->map.player_direction);
	// printf("Player pdx, pdy: %f, %f\n", env->map.pdx, env->map.pdy);
}

