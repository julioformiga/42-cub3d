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

t_map	transpose_map(t_map *map)
{
	t_map	temp_map;
	int		i;
	int		j;
	int		**temp;
	int		*row_widths;
	int		temp_height;
	int		temp_width;
	int		max_width;

	row_widths = (int *)ft_calloc(map->height, sizeof(int));
	max_width = 0;
	for (i = 0; i < map->height; i++) {
		j = 0;
		while (map->data[i] && map->data[i][j] != -2)
			j++;
		row_widths[i] = j;
		if (j > max_width)
			max_width = j;
	}
	temp_height = max_width;
	temp_width = map->height;
	temp = (int **)ft_calloc(temp_height + 1, sizeof(int *));
	i = -1;
	while (i++, i < temp_height)
	{
		temp[i] = (int *)ft_calloc(temp_width + 1, sizeof(int));
		j = -1;
		while (j++, j < temp_width)
			temp[i][j] = -1;
	}
	i = -1;
	while (i++, i < map->height)
	{
		j = -1;
		while (j++, j < row_widths[i])
			temp[j][i] = map->data[i][j];
	}
	temp_map.data = temp;
	temp_map.width = map->height;
	temp_map.height = max_width;
	free(row_widths);
	return (temp_map);
}

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

	map_transpose = transpose_map(map);
	if (check_map_holes(map) || check_map_holes(&map_transpose))
	{
		free_map(map, 1);
		free_map(&map_transpose, 0);
		ft_mlx_error("Map has holes\n");
	}
	free_map(&map_transpose, 0);
	ft_validate_map_textures(map);
}
