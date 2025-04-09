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

void	ft_mlx_draw_square(t_env *env, t_point p, int width, int color)
{
	int	i;

	i = -1;
	while (i++, i < width)
		ft_mlx_draw_line(env,
			(t_point){p.x, p.y + i},
			(t_point){p.x + width, p.y + i},
			color);
}
