/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   textures.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tfalchi <tfalchi@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/11 14:02:43 by julio.formi       #+#    #+#             */
/*   Updated: 2025/04/16 18:33:56 by tfalchi          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

void	init_textures(t_env *env)
{
	int	width;
	int	height;

	env->map.north.img = mlx_xpm_file_to_image(env->mlx, env->map.north.path, &width, &height);
	env->map.south.img = mlx_xpm_file_to_image(env->mlx, env->map.south.path, &width, &height);
	env->map.east.img = mlx_xpm_file_to_image(env->mlx, env->map.east.path, &width, &height);
	env->map.west.img = mlx_xpm_file_to_image(env->mlx, env->map.west.path, &width, &height);
	if (!env->map.north.img || !env->map.south.img || !env->map.east.img || !env->map.west.img)
		ft_mlx_error("Failed to load textures images\n");
	env->map.north.data = (int *)mlx_get_data_addr(env->map.north.img, &env->map.north.bpp,
		&env->map.north.size_line, &env->map.north.endian);
	env->map.south.data = (int *)mlx_get_data_addr(env->map.south.img, &env->map.south.bpp,
		&env->map.south.size_line, &env->map.south.endian);
	env->map.east.data = (int *)mlx_get_data_addr(env->map.east.img, &env->map.east.bpp,
		&env->map.east.size_line, &env->map.east.endian);
	env->map.west.data = (int *)mlx_get_data_addr(env->map.west.img, &env->map.west.bpp,
		&env->map.west.size_line, &env->map.west.endian);
	env->map.north.width = width;
	env->map.north.height = height;
	env->map.south.width = width;
	env->map.south.height = height;
	env->map.east.width = width;
	env->map.east.height = height;
	env->map.west.width = width;
	env->map.west.height = height;
}
