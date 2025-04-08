/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_mlx_draw.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: julio.formiga <julio.formiga@gmail.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/05 02:19:51 by julio.formiga     #+#    #+#             */
/*   Updated: 2025/04/05 02:19:51 by julio.formiga    ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

void ft_mlx_draw_square(t_env *env, t_point p, int width, int color)
{
	int	i;

	i = -1;
	while (i++, i < width)
		ft_mlx_draw_line(env,
				   (t_point){p.x, p.y + i},
				   (t_point){p.x + width, p.y + i},
				   color);
}

void draw_minimap(t_env *env)
{
	int		i;
	int		j;
	int width = 100;
	if (!env->map.data)
	{
		printf("Map data is NULL\n");
		return ;
	}
	i = 0;
	while (i < env->map.height)
	{
		j = 0;
		while (j < env->map.width)
		{
			if (!env->map.data[i])
			{
				printf("Map data[%d] is NULL\n", i);
				break ;
			}
			if (env->map.data[i][j] == 1)
				ft_mlx_draw_square(env, (t_point){j * width, i * width}, width, WHITE);
			else
				ft_mlx_draw_square(env, (t_point){j * width, i * width}, width, BLACK);
			j++;
		}
		i++;
	}
	player(env);
}

void	ft_map_draw(t_env *env)
{
	if (!env->map.data)
	{
		printf("Map data is NULL\n");
		return ;
	}
	ft_bzero(env->screen.addr, WIN_WIDTH * WIN_HEIGHT * (env->screen.bpp / 8));
	draw_minimap(env);
	// ft_mlx_put_image(env);
	mlx_put_image_to_window(env->mlx, env->win, env->screen.img, 0, 0);
	// mlx_do_sync(env->mlx);
	// ft_debug_map(&env->map);
}
