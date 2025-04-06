/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_mlx_map_rotate.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: julio.formiga <julio.formiga@gmail.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/05 02:19:51 by julio.formiga     #+#    #+#             */
/*   Updated: 2025/04/05 02:19:51 by julio.formiga    ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

t_point3d	rotate_x(float x, float y, float z, float angle)
{
	t_point3d	point;
	float		rad_angle;

	rad_angle = angle * (M_PI / 180.0);
	point.x = x;
	point.y = y * cos(rad_angle) - z * sin(rad_angle);
	point.z = y * sin(rad_angle) + z * cos(rad_angle);
	return (point);
}

t_point3d	rotate_y(float x, float y, float z, float angle)
{
	t_point3d	point;
	float		rad_angle;

	rad_angle = angle * (M_PI / 180.0);
	point.x = x * cos(rad_angle) + z * sin(rad_angle);
	point.y = y;
	point.z = -x * sin(rad_angle) + z * cos(rad_angle);
	return (point);
}

t_point3d	rotate_z(float x, float y, float z, float angle)
{
	t_point3d	point;
	float		rad_angle;

	rad_angle = angle * (M_PI / 180.0);
	point.x = x * cos(rad_angle) - y * sin(rad_angle);
	point.y = x * sin(rad_angle) + y * cos(rad_angle);
	point.z = z;
	return (point);
}

t_point3d	ft_map_rotate3d(int x, int y, int z, t_view view)
{
	t_point3d	point;

	point = rotate_x(x, y, z, view.rotation_angle_x);
	point = rotate_y(point.x, point.y, point.z, view.rotation_angle_y);
	point = rotate_z(point.x, point.y, point.z, view.rotation_angle_z);
	return (point);
}
