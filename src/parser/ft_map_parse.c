/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_map_parse.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tfalchi <tfalchi@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/05 06:13:11 by julio.formi       #+#    #+#             */
/*   Updated: 2025/05/12 18:44:30 by tfalchi          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

static int	ft_count_map_width(char *line)
{
	int	i;
	int	width;

	width = 0;
	i = -1;
	while (i++, line[i])
		if (line[i] != '\n')
			width++;
	return (width);
}

static void	ft_parse_map_line_fill(t_map *map, char *line, int x, int y)
{
	map->data[y][x] = 0;
	map->player.x = x * map->size + (map->size / 2);
	map->player.y = y * map->size + (map->size / 2);
	if (map->player.direction != 0)
		map->player.direction = -1;
	else if (line[x] == 'N')
		map->player.direction = 270 * M_PI / 180;
	else if (line[x] == 'S')
		map->player.direction = 90 * M_PI / 180;
	else if (line[x] == 'E')
		map->player.direction = 0.000001;
	else if (line[x] == 'W')
		map->player.direction = 180 * M_PI / 180;
}

static void	ft_parse_map_line(t_map *map, int y)
{
	int	x;
	int	width;

	width = ft_count_map_width(map->line);
	if (width > map->width)
		map->width = width + 1;
	map->data[y] = (int *)ft_calloc(width + 1, sizeof(int));
	x = -1;
	while (x++, x < width)
		map->data[y][x] = 0;
	map->data[y][x] = -2;
	x = -1;
	while (x++, map->line[x] && map->line[x] != '\n')
	{
		if (map->line[x] == ' ')
			map->data[y][x] = -1;
		else if (map->line[x] == '0')
			map->data[y][x] = 0;
		else if (map->line[x] == '1')
			map->data[y][x] = 1;
		else if (map->line[x] == 'D')
			map->data[y][x] = 2;
		else if (ft_strchr("NSWE", map->line[x]))
			ft_parse_map_line_fill(map, map->line, x, y);
	}
}

static int	ft_process_line(t_map *map, int *config_done, int *y)
{
	if (!*config_done && !ft_parse_texture_color(map))
		return (1);
	if (ft_is_map_line(map->line) && map->north.path && map->south.path
		&& map->west.path && map->east.path && map->door.path)
	{
		*config_done = 1;
		ft_parse_map_line(map, *y);
		(*y)++;
	}
	else if (*config_done && !ft_is_map_line(map->line)
		&& map->line[0] != '\n' && map->line[0] != 0)
		ft_mlx_error("Invalid map format\n");
	else if (!*config_done && !ft_is_map_line(map->line)
		&& map->line[0] != '\n')
	{
		free_map(map, 1);
		ft_mlx_error("Wrong variables in fd\n");
	}
	return (0);
}

t_map	ft_map_parse(char *file)
{
	t_map	map;
	int		y;
	int		config_done;

	ft_init_map(&map, file);
	map.fd = ft_open_file(file);
	map.line = get_next_line(map.fd);
	config_done = 0;
	y = 0;
	while (map.line)
	{
		if (ft_process_line(&map, &config_done, &y))
		{
			free(map.line);
			map.line = get_next_line(map.fd);
			continue ;
		}
		free(map.line);
		map.line = get_next_line(map.fd);
	}
	close(map.fd);
	ft_validate_map(&map);
	return (map);
}
