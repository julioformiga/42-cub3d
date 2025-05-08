/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_validate_map.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: julio.formiga <julio.formiga@gmail.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/07 15:01:47 by julio.formiga     #+#    #+#             */
/*   Updated: 2025/05/07 15:01:47 by julio.formiga    ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

int	check_map_holes(t_map *map)
{
	int	i;
	int	j;

	i = -1;
	while (i++, i < map->height)
	{
		j = -1;
		while (j++, j < map->width && map->data[i] && map->data[i][j] >= -1)
		{
			if (map->data[i][0] == 0)
				return (1);
			if (j > 0 && map->data[i][j - 1] == -1 && map->data[i][j] == 0)
				return (1);
			if (j == map->width - 1 && map->data[i][j] == 0)
				return (1);
			if (j <= map->width - 1 && map->data[i][j + 1] < 0
				&& map->data[i][j] == 0)
				return (1);
		}
	}
	return (0);
}

void	ft_validate_map(t_map *map)
{
	t_map	map_transpose;

	map_transpose = ft_map_transpose(map);
	if (check_map_holes(map) || check_map_holes(&map_transpose))
	{
		free_map(map, 1);
		free_map(&map_transpose, 0);
		ft_mlx_error("Map has holes\n");
	}
	free_map(&map_transpose, 0);
	ft_validate_map_textures(map);
}
