/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_mlx_color.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: julio.formiga <julio.formiga@gmail.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/05 06:25:05 by julio.formiga     #+#    #+#             */
/*   Updated: 2025/04/05 06:25:05 by julio.formiga    ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

int	ft_mlx_color(t_color color)
{
	return ((color.t << 24) | (color.r << 16) | (color.g << 8) | color.b);
}

int	ft_mlx_line_color(t_env *env, int i, int j, char type)
{
	t_color	color;
	t_range	r_in;
	t_range	r_out;
	int		c_color;

	r_in = (t_range){40, 255};
	r_out = (t_range){env->map.min, env->map.max};
	color = (t_color){0, 40, 100, 40};
	if (j > 0 && env->map.data[i][j] == env->map.data[i][j - 1] && type == 'h')
		color.g = ft_map_value(r_in, r_out, env->map.data[i][j]);
	if (i > 0 && env->map.data[i][j] == env->map.data[i - 1][j] && type == 'v')
		color.g = ft_map_value(r_in, r_out, env->map.data[i][j]);
	color.g = ft_map_value(r_in, r_out, env->map.data[i][j]);
	c_color = ft_mlx_color(color);
	return (c_color);
}
