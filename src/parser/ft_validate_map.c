/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_validate_map.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tfalchi <tfalchi@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/07 15:01:47 by julio.formi       #+#    #+#             */
/*   Updated: 2025/05/12 18:35:51 by tfalchi          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

static int	check_map_holes(t_map *map)
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

static void	ft_validate_map_colors(t_map *map)
{
	if (map->ceiling.r < 0 || map->ceiling.g < 0 || map->ceiling.b < 0
		|| map->floor.r < 0 || map->floor.g < 0 || map->floor.b < 0)
	{
		free_map(map, 1);
		ft_mlx_error("Invalid color values\n");
	}
	if (map->ceiling.r > 255 || map->ceiling.g > 255 || map->ceiling.b > 255
		|| map->floor.r > 255 || map->floor.g > 255 || map->floor.b > 255)
	{
		free_map(map, 1);
		ft_mlx_error("Color value must be between 0 and 255\n");
	}
}

static void	ft_validate_map_multiple_player_location(t_map *map)
{
	if (map->player.direction <= 0)
		free_map(map, 1);
	if (map->player.direction == 0)
		ft_mlx_error("No player position found in map\n");
	if (map->player.direction == -1)
		ft_mlx_error("Multiple player positions found\n");
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
	if (map->north.path == NULL
		|| map->south.path == NULL || map->west.path == NULL
		|| map->east.path == NULL || map->door.path == NULL)
	{
		free_map(map, 1);
		ft_mlx_error("Missing texture path\n");
	}
	ft_validate_map_colors(map);
	ft_validate_map_multiple_player_location(map);
	ft_validate_map_textures(map);
}
