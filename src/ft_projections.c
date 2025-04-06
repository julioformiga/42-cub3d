/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_projections.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: julio.formiga <julio.formiga@gmail.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/05 02:19:51 by julio.formiga     #+#    #+#             */
/*   Updated: 2025/04/05 02:19:51 by julio.formiga    ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

t_point	ft_select_projection(int x, int y, int z, t_view view)
{
	if (view.projection == 1)
		return (ft_parallel_transform(x, y, z, view));
	return (ft_iso_transform(x, y, z, view));
}

t_point	ft_parallel_transform(int x, int y, int z, t_view view)
{
	t_point	point;

	point.x = x * view.zoom;
	point.y = y * view.zoom - (int)z * (int)view.height;
	return (point);
}

t_point	ft_iso_transform(int x, int y, int z, t_view view)
{
	t_point		point;
	t_point3d	rotated;
	float		iso_x;
	float		iso_y;

	rotated = ft_map_rotate3d(x, y, z, view);
	iso_x = (rotated.x - rotated.y) * cos(view.angle);
	iso_y = (rotated.x + rotated.y) * sin(view.angle) - rotated.z * view.height;
	point.x = (int)(iso_x * view.zoom);
	point.y = (int)(iso_y * view.zoom);
	return (point);
}
