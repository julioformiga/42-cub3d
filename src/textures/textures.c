/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   textures.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tfalchi <tfalchi@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/11 14:02:43 by julio.formi       #+#    #+#             */
/*   Updated: 2025/05/12 17:58:39 by tfalchi          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

static int	load_texture(t_env *env, t_texture *texture)
{
	int	width;
	int	height;

	texture->img = mlx_xpm_file_to_image(env->mlx, texture->path,
			&width, &height);
	if (!texture->img)
		return (0);
	texture->data = (int *)mlx_get_data_addr(texture->img,
			&texture->bpp, &texture->size_line, &texture->endian);
	texture->width = width;
	texture->height = height;
	return (1);
}

void	init_textures(t_env *env)
{
	if (!load_texture(env, &env->map.north)
		|| !load_texture(env, &env->map.south)
		|| !load_texture(env, &env->map.east)
		|| !load_texture(env, &env->map.west)
		|| !load_texture(env, &env->map.door))
	{
		free_map(&env->map, 1);
		ft_mlx_error("Failed to load textures images\n");
	}
}
