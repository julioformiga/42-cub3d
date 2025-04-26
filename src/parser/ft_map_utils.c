/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_map_utils.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: julio.formiga <julio.formiga@gmail.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/05 05:21:39 by julio.formiga     #+#    #+#             */
/*   Updated: 2025/04/05 05:21:39 by julio.formiga    ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

void	ft_map_init(t_map *map, int n)
{
	int	i;

	map->width = 0;
	map->height = 0;
	map->min = 0;
	map->max = 0;
	map->data = (int **)malloc(n * sizeof(int *));
	if (!map->data)
		return ;
	i = 0;
	while (i < n)
	{
		map->data[i] = NULL;
		i++;
	}
}

void	ft_validate_map_textures(t_map *map)
{
	if (!map->north.path)
		map->north.path = ft_strdup("./assets/textures/north_default.xpm");
	if (!map->south.path)
		map->south.path = ft_strdup("./assets/textures/south_default.xpm");
	if (!map->west.path)
		map->west.path = ft_strdup("./assets/textures/west_default.xpm");
	if (!map->east.path)
		map->east.path = ft_strdup("./assets/textures/east_default.xpm");
	if (map->player.direction == 0)
		ft_mlx_error("No player position found in map\n");
}

t_color	ft_parse_color(char *color_str)
{
	t_color	color;
	char	**values;

	values = ft_split(color_str, ',');
	if (!values || !values[0] || !values[1] || !values[2] || values[3])
		ft_mlx_error("Invalid color format\n");
	color.r = ft_atoi(values[0]);
	color.g = ft_atoi(values[1]);
	color.b = ft_atoi(values[2]);
	color.t = 0;
	if (color.r < 0 || color.r > 255 || color.g < 0 || color.g > 255
		|| color.b < 0 || color.b > 255)
		ft_mlx_error("Color values must be between 0 and 255\n");
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

int	ft_parse_texture_color(t_map *map, char *line)
{
	char	**elements;

	elements = ft_split(line, ' ');
	if (!elements || !elements[0])
		return (0);
	if (elements[1])
		ft_remove_newline(elements[1]);
	if (!ft_strncmp(elements[0], "NO", 3) && elements[1])
		map->north.path = ft_strdup(elements[1]);
	else if (!ft_strncmp(elements[0], "SO", 3) && elements[1])
		map->south.path = ft_strdup(elements[1]);
	else if (!ft_strncmp(elements[0], "WE", 3) && elements[1])
		map->west.path = ft_strdup(elements[1]);
	else if (!ft_strncmp(elements[0], "EA", 3) && elements[1])
		map->east.path = ft_strdup(elements[1]);
	else if (!ft_strncmp(elements[0], "F", 2) && elements[1])
		map->floor = ft_parse_color(elements[1]);
	else if (!ft_strncmp(elements[0], "C", 2) && elements[1])
		map->ceiling = ft_parse_color(elements[1]);
	else
		return (ft_free_array_char(elements), 0);
	return (ft_free_array_char(elements), 1);
}
