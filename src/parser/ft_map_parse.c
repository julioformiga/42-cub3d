/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_map_parse.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tfalchi <tfalchi@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/05 06:13:11 by julio.formi       #+#    #+#             */
/*   Updated: 2025/05/07 18:43:14 by tfalchi          ###   ########.fr       */
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
	if (line[x] == 'N')
		map->player.direction = 270 * M_PI / 180;
	else if (line[x] == 'S')
		map->player.direction = 90 * M_PI / 180;
	else if (line[x] == 'E')
		map->player.direction = 0.000001;
	else if (line[x] == 'W')
		map->player.direction = 180 * M_PI / 180;
}

static void	ft_parse_map_line(t_map *map, char *line, int y)
{
	int	x;
	int	width;

	map->size = 10;
	width = ft_count_map_width(line);
	if (width > map->width)
		map->width = width + 1;
	map->data[y] = (int *)ft_calloc(width + 1, sizeof(int));
	x = -1;
	while (x++, x < width)
		map->data[y][x] = 0;
	map->data[y][x] = -2;
	x = -1;
	while (x++, line[x] && line[x] != '\n')
	{
		if (line[x] == ' ')
			map->data[y][x] = -1;
		else if (line[x] == '0')
			map->data[y][x] = 0;
		else if (line[x] == '1')
			map->data[y][x] = 1;
		else if (line[x] == 'D')
			map->data[y][x] = 2;
		else if (ft_strchr("NSWE", line[x]))
			ft_parse_map_line_fill(map, line, x, y);
	}
}

static int	ft_process_line(t_map *map, char *line, int *config_done, int *y)
{
	if (!*config_done && ft_parse_texture_color(map, line))
		return (1);
	if (ft_is_map_line(line))
	{
		*config_done = 1;
		ft_parse_map_line(map, line, *y);
		(*y)++;
	}
	else if (*config_done && !ft_is_map_line(line)
		&& line[0] != '\n' && line[0] != 0)
		ft_mlx_error("Invalid map format\n");
	return (0);
}

t_map	ft_map_parse(char *file)
{
	t_map	map;
	int		fd;
	char	*line;
	int		y;
	int		config_done;

	ft_init_map(&map, file);
	fd = ft_open_file(file);
	line = get_next_line(fd);
	config_done = 0;
	y = 0;
	while (line)
	{
		if (ft_process_line(&map, line, &config_done, &y))
		{
			free(line);
			map.data = NULL;
			break;
		}
		free(line);
		line = get_next_line(fd);
	}
	close(fd);
	if(map.data != NULL)
		ft_validate_map(&map);
	return (map);
}
