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

void	ft_map_draw(t_env *env)
{
	int		i;
	int		j;
	t_point	point;

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
			point = ft_select_projection(j, i, env->map.data[i][j], env->view);
			env->cursor_x = env->init.x + point.x;
			env->cursor_y = env->init.y + point.y;
			if (j < env->map.width - 1)
				ft_mlx_draw_lines(env, 'h', i, j);
			if (i < env->map.height - 1)
				ft_mlx_draw_lines(env, 'v', i, j);
			j++;
		}
		i++;
	}
	ft_mlx_scale(env);
	mlx_put_image_to_window(env->mlx, env->win, env->screen.img, 0, 0);
	ft_mlx_put_image(env);
	ft_mlx_info(env);
	mlx_do_sync(env->mlx);
}

void	ft_mlx_scale(t_env *env)
{
	int		i;
	int		x;
	int		y;

	i = -1;
	while (i++, i < WIN_WIDTH)
	{
		x = 10;
		ft_draw_line_to_image(env, i, WIN_HEIGHT - 1, GREEN);
		if (i % (int)env->view.zoom > -2 && i % (int)env->view.zoom < 2)
			while (x--, x > 2)
				ft_draw_line_to_image(env, i, WIN_HEIGHT - x, GREEN_DARK);
	}
	i = -1;
	while (i++, i < WIN_HEIGHT)
	{
		y = 10;
		ft_draw_line_to_image(env, 1, i, GREEN);
		if (i % (int)env->view.zoom > -2 && i % (int)env->view.zoom < 2)
			while (y--, y > 2)
				ft_draw_line_to_image(env, y, i, GREEN_DARK);
	}
}

void	ft_mlx_info(t_env *env)
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
