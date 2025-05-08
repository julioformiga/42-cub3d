/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_mlx_draw_rect.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tfalchi <tfalchi@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/09 12:59:05 by julio.formi       #+#    #+#             */
/*   Updated: 2025/05/08 12:37:56 by tfalchi          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

void	ft_mlx_draw_square(t_env *env, t_point p, int width, int color)
{
	int	i;

	i = -1;
	if (color == 0)
		color = BLACK;
	else if (color == 1)
		color = WHITE;
	else if (color == 2)
		color = RED;
	else if (color == 3)
		color = GREEN;
	else
		return ;
	while (i++, i < width)
		ft_mlx_draw_line(env, (t_point){p.x, p.y + i}, (t_point){p.x + width,
			p.y + i}, color);
}

static int	ft_point_inside_rect(t_point p, t_rect rect)
{
	int	cross1;
	int	cross2;
	int	cross3;
	int	cross4;

	cross1 = (rect.p1.x - rect.p0.x) * (p.y - rect.p0.y) - (rect.p1.y
			- rect.p0.y) * (p.x - rect.p0.x);
	cross2 = (rect.p2.x - rect.p1.x) * (p.y - rect.p1.y) - (rect.p2.y
			- rect.p1.y) * (p.x - rect.p1.x);
	cross3 = (rect.p3.x - rect.p2.x) * (p.y - rect.p2.y) - (rect.p3.y
			- rect.p2.y) * (p.x - rect.p2.x);
	cross4 = (rect.p0.x - rect.p3.x) * (p.y - rect.p3.y) - (rect.p0.y
			- rect.p3.y) * (p.x - rect.p3.x);
	if ((cross1 >= 0 && cross2 >= 0 && cross3 >= 0 && cross4 >= 0)
		|| (cross1 <= 0 && cross2 <= 0 && cross3 <= 0 && cross4 <= 0))
		return (1);
	return (0);
}

static void	ft_mlx_draw_rect_fill(t_env *env, t_rect rect, int color)
{
	int		min_x;
	int		max_x;
	int		min_y;
	int		max_y;
	t_point	p;

	min_x = ft_min(ft_min(rect.p0.x, rect.p1.x), ft_min(rect.p2.x, rect.p3.x));
	max_x = ft_max(ft_max(rect.p0.x, rect.p1.x), ft_max(rect.p2.x, rect.p3.x));
	min_y = ft_min(ft_min(rect.p0.y, rect.p1.y), ft_min(rect.p2.y, rect.p3.y));
	max_y = ft_max(ft_max(rect.p0.y, rect.p1.y), ft_max(rect.p2.y, rect.p3.y));
	p.y = min_y;
	while (p.y <= max_y)
	{
		p.x = min_x;
		while (p.x <= max_x)
		{
			if (ft_point_inside_rect(p, rect))
				ft_draw_line_to_image(env, p.x, p.y, color);
			p.x++;
		}
		p.y++;
	}
}

void	ft_mlx_draw_rect(t_env *env, t_rect rect, int color, int fill)
{
	if (!env || !env->screen.addr)
		return ;
	ft_mlx_draw_line(env, rect.p0, rect.p1, color);
	ft_mlx_draw_line(env, rect.p1, rect.p2, color);
	ft_mlx_draw_line(env, rect.p2, rect.p3, color);
	ft_mlx_draw_line(env, rect.p3, rect.p0, color);
	if (fill)
		ft_mlx_draw_rect_fill(env, rect, color);
}
