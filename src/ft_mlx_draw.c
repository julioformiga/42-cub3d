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

void print_square(t_env *env, int x, int y, int width, int color)
{
	int i;

	i = -1;
	while (i++, i < width)
	{
		ft_mlx_draw_line(env, (t_point){x, y + i}, (t_point){x + width, y + i}, color);
		// printf("x, y: %d, %d\n", x, y);
	}
}

void player(t_env *env)
{
	int x;
	int y;
	int width = 20;

	x = env->map.player_x;
	y = env->map.player_y;
	print_square(env, x, y, width, RED);
	ft_mlx_draw_line(env,
				  (t_point){x + (width/2), y + (width/2)},
				  (t_point){
					(x + ((float)width/2)) + env->map.pdx * 5,
					(y + ((float)width/2)) + env->map.pdy * 5
				  },
			YELLOW);
	// printf("Player x, y: %d, %d\n", x, y);
	// printf("Player direction: %f\n", env->map.player_direction);
	// printf("Player pdx, pdy: %f, %f\n", env->map.pdx, env->map.pdy);
}

void	ft_map_draw(t_env *env)
{
	int		i;
	int		j;
	int width = 100;

	if (!env->map.data)
	{
		printf("Map data is NULL\n");
		return ;
	}
	ft_bzero(env->screen.addr, WIN_WIDTH * WIN_HEIGHT * (env->screen.bpp / 8));
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
				print_square(env, j * width, i * width, width, WHITE);
			else
				print_square(env, j * width, i * width, width, BLACK);
			j++;
		}
		i++;
	}
	player(env);
	mlx_put_image_to_window(env->mlx, env->win, env->screen.img, 0, 0);
	// ft_mlx_put_image(env);
	// render_info(env);
	mlx_do_sync(env->mlx);
	ft_debug_map(&env->map);
}

void	render_info(t_env *env)
{
	char	*str;
	char	*tmp;

	str = ft_strdup("Projection: ");
	if (env->view.projection == 1)
		tmp = ft_strjoin(str, "Parallel");
	else
		tmp = ft_strjoin(str, "Isometric");
	mlx_string_put(env->mlx, env->win, 1140, 20, BLACK, tmp);
	free(tmp);
	free(str);
	str = ft_itoa(env->view.zoom);
	tmp = ft_strjoin("Zoom: ", str);
	mlx_string_put(env->mlx, env->win, 1140, 40, BLACK, tmp);
	free(tmp);
	free(str);
	str = ft_itoa(env->view.angle_rotate);
	tmp = ft_strjoin("Angle: ", str);
	mlx_string_put(env->mlx, env->win, 1140, 60, BLACK, tmp);
	free(tmp);
	free(str);
}
