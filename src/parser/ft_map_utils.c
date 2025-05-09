/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_map_utils.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tfalchi <tfalchi@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/05 05:21:39 by julio.formi       #+#    #+#             */
/*   Updated: 2025/05/05 15:26:06 by tfalchi          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

void	ft_validate_map_textures(t_map *map)
{
	if ((map->north.path && ft_file_exists(map->north.path))
		|| (map->south.path && ft_file_exists(map->south.path))
		|| (map->west.path && ft_file_exists(map->west.path))
		|| (map->east.path && ft_file_exists(map->east.path))
		|| (map->door.path && ft_file_exists(map->door.path)))
	{
		free_map(map, 1);
		ft_mlx_error("Invalid texture path\n");
	}
	if (!map->north.path || !map->south.path
		|| !map->west.path || !map->east.path || !map->door.path)
		map->error = 1;
}

t_color	ft_parse_color(char *color_str)
{
	t_color	color;
	char	**values;

	values = ft_split(color_str, ',');
	if (!values || !values[0] || !values[1] || !values[2] || values[3]
		|| ft_isnumber(values[0]) || ft_isnumber(values[1])
		|| ft_isnumber(values[2]))
	{
		color.r = -1;
		ft_free_array_char(values);
		return (color);
	}
	color.r = ft_atoi(values[0]);
	color.g = ft_atoi(values[1]);
	color.b = ft_atoi(values[2]);
	color.t = 0;
	if (color.r < 0 || color.r > 255 || color.g < 0 || color.g > 255
		|| color.b < 0 || color.b > 255)
		color.r = -1;
	ft_free_array_char(values);
	return (color);
}

int	ft_is_map_line(char *line)
{
	int	i;
	int	has_valid_char;

	i = 0;
	has_valid_char = 0;
	while (line[i])
	{
		if (!ft_strchr("01NESWD \n", line[i]))
			return (0);
		if (ft_strchr("01NESWD", line[i]))
			has_valid_char = 1;
		i++;
	}
	return (has_valid_char);
}

void	ft_check_double_keys(t_map *map, char *key)
{
	if ((!ft_strncmp(key, "NO", 3) && map->north.path)
		|| (!ft_strncmp(key, "SO", 3) && map->south.path)
		|| (!ft_strncmp(key, "WE", 3) && map->west.path)
		|| (!ft_strncmp(key, "EA", 3) && map->east.path)
		|| (!ft_strncmp(key, "D", 2) && map->door.path))
	{
		free_map(map, 1);
		ft_mlx_error("Duplicate texture key\n");
	}
	else if (!ft_strncmp(key, "F", 2) && map->floor.r >= 0)
	{
		free_map(map, 1);
		ft_mlx_error("Duplicate floor color\n");
	}
	else if (!ft_strncmp(key, "C", 2) && map->ceiling.r >= 0)
	{
		free_map(map, 1);
		ft_mlx_error("Duplicate ceiling color\n");
	}
}

int	ft_parse_texture_color(t_map *map, char *line)
{
	char	**elements;

	elements = ft_split(line, ' ');
	if (!elements || !elements[0])
		return (0);
	if (elements[1])
		ft_remove_newline(elements[1]);
	ft_check_double_keys(map, elements[0]);
	if (!ft_strncmp(elements[0], "NO", 3) && elements[1])
		map->north.path = ft_strdup(elements[1]);
	else if (!ft_strncmp(elements[0], "SO", 3) && elements[1])
		map->south.path = ft_strdup(elements[1]);
	else if (!ft_strncmp(elements[0], "WE", 3) && elements[1])
		map->west.path = ft_strdup(elements[1]);
	else if (!ft_strncmp(elements[0], "EA", 3) && elements[1])
		map->east.path = ft_strdup(elements[1]);
	else if (!ft_strncmp(elements[0], "D", 2) && elements[1])
		map->door.path = ft_strdup(elements[1]);
	else if (!ft_strncmp(elements[0], "F", 2) && elements[1])
		map->floor = ft_parse_color(elements[1]);
	else if (!ft_strncmp(elements[0], "C", 2) && elements[1])
		map->ceiling = ft_parse_color(elements[1]);
	else
		return (ft_free_array_char(elements), 1);
	return (ft_free_array_char(elements), 0);
}
