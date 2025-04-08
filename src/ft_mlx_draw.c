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
	render_info(env);
	// mlx_do_sync(env->mlx);
	// ft_debug_map(&env->map);
}

void	render_info(t_env *env)
{
	char	*str;
	int		y_pos;
	int		x_pos;
	int		border_color;

	y_pos = 10;
	x_pos = WIN_WIDTH - 200;
	border_color = WHITE;

	ft_mlx_draw_line(env, (t_point){0, 0}, (t_point){WIN_WIDTH, 0}, border_color);
	ft_mlx_draw_line(env, (t_point){0, WIN_HEIGHT - 1}, (t_point){WIN_WIDTH, WIN_HEIGHT - 1}, border_color);
	ft_mlx_draw_line(env, (t_point){0, 0}, (t_point){0, WIN_HEIGHT}, border_color);
	ft_mlx_draw_line(env, (t_point){WIN_WIDTH - 1, 0}, (t_point){WIN_WIDTH - 1, WIN_HEIGHT}, border_color);

	y_pos += 20;
	mlx_string_put(env->mlx, env->win, x_pos, y_pos, GREEN, "Player Position:");

	y_pos += 20;
	str = ft_itoa(env->map.player.x);
	mlx_string_put(env->mlx, env->win, x_pos + 10, y_pos, WHITE, "X: ");
	mlx_string_put(env->mlx, env->win, x_pos + 30, y_pos, WHITE, str);
	free(str);

	y_pos += 20;
	str = ft_itoa(env->map.player.y);
	mlx_string_put(env->mlx, env->win, x_pos + 10, y_pos, WHITE, "Y: ");
	mlx_string_put(env->mlx, env->win, x_pos + 30, y_pos, WHITE, str);
	free(str);

	y_pos += 30;
	mlx_string_put(env->mlx, env->win, x_pos, y_pos, GREEN, "Player Direction:");

	y_pos += 20;
	str = ft_itoa((int)(env->map.player.direction * 180 / M_PI));
	mlx_string_put(env->mlx, env->win, x_pos + 10, y_pos, WHITE, "Angle: ");
	mlx_string_put(env->mlx, env->win, x_pos + 70, y_pos, WHITE, str);
	mlx_string_put(env->mlx, env->win, x_pos + 90, y_pos, WHITE, "degrees");
	free(str);

	y_pos += 20;
	str = ft_itoa(env->map.player.dx);
	mlx_string_put(env->mlx, env->win, x_pos + 10, y_pos, WHITE, "DX: ");
	mlx_string_put(env->mlx, env->win, x_pos + 40, y_pos, WHITE, str);
	free(str);

	y_pos += 20;
	str = ft_itoa(env->map.player.dy);
	mlx_string_put(env->mlx, env->win, x_pos + 10, y_pos, WHITE, "DY: ");
	mlx_string_put(env->mlx, env->win, x_pos + 40, y_pos, WHITE, str);
	free(str);

	y_pos += 30;
	mlx_string_put(env->mlx, env->win, x_pos, y_pos, CYAN, "Map Information:");

	y_pos += 20;
	str = ft_itoa(env->map.width);
	mlx_string_put(env->mlx, env->win, x_pos + 10, y_pos, WHITE, "Width: ");
	mlx_string_put(env->mlx, env->win, x_pos + 70, y_pos, WHITE, str);
	free(str);

	y_pos += 20;
	str = ft_itoa(env->map.height);
	mlx_string_put(env->mlx, env->win, x_pos + 10, y_pos, WHITE, "Height: ");
	mlx_string_put(env->mlx, env->win, x_pos + 70, y_pos, WHITE, str);
	free(str);

	y_pos += 40;
	mlx_string_put(env->mlx, env->win, x_pos, y_pos, MAGENTA, "Controls:");

	y_pos += 20;
	mlx_string_put(env->mlx, env->win, x_pos + 10, y_pos, env->keys.up ? YELLOW : WHITE, "UP");

	y_pos += 20;
	mlx_string_put(env->mlx, env->win, x_pos + 10, y_pos, env->keys.down ? YELLOW : WHITE, "DOWN");

	y_pos += 20;
	mlx_string_put(env->mlx, env->win, x_pos + 10, y_pos, env->keys.left ? YELLOW : WHITE, "LEFT");

	y_pos += 20;
	mlx_string_put(env->mlx, env->win, x_pos + 10, y_pos, env->keys.right ? YELLOW : WHITE, "RIGHT");
}
