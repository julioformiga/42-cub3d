/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_map_parse.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tfalchi <tfalchi@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/05 06:13:11 by julio.formi       #+#    #+#             */
/*   Updated: 2025/04/26 11:26:40 by tfalchi          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

static int	ft_count_map_width(char *line)
{
	int	i;
	int	width;

	width = 0;
	i = 0;
	while (line[i])
	{
		if (line[i] != '\n')
			width++;
		i++;
	}
	return (width);
}

static int	ft_count_map_lines(char *file)
{
	int		fd;
	char	*line;
	int		count;
	int		map_started;

	fd = open(file, O_RDONLY);
	if (fd < 0)
		ft_mlx_error("Could not open file\n");
	count = 0;
	map_started = 0;
	line = get_next_line(fd);
	while (line)
	{
		if (ft_is_map_line(line))
		{
			map_started = 1;
			count++;
		}
		else if (map_started)
		{
			free(line);
			close(fd);
			return (count);
		}
		free(line);
		line = get_next_line(fd);
	}
	close(fd);
	return (count);
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
	if (!map->data[y])
		ft_mlx_error("Memory allocation failed\n");
	x = 0;
	while (x < width)
	{
		map->data[y][x] = 0;
		x++;
	}
	map->data[y][x] = -1;
	x = 0;
	while (line[x] && line[x] != '\n')
	{
		if (line[x] == '0' || line[x] == ' ')
			map->data[y][x] = 0;
		else if (line[x] == '1')
			map->data[y][x] = 1;
		else if (line[x] == 'D')
			map->data[y][x] = 2;
		else if (ft_strchr("NSWE", line[x]))
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
		x++;
	}
}

t_map	ft_map_parse(char *file)
{
	t_map	map;
	int		fd;
	char	*line;
	int		y;
	int		config_done;

	ft_bzero(&map, sizeof(t_map));
	map.player.direction = 0;
	map.floor = (t_color){0, 100, 100, 100};
	map.ceiling = (t_color){0, 135, 206, 235};
	map.height = ft_count_map_lines(file);
	map.data = (int **)ft_calloc(map.height + 1, sizeof(int *));
	if (!map.data)
		ft_mlx_error("Memory allocation failed\n");
	fd = open(file, O_RDONLY);
	if (fd < 0)
		ft_mlx_error("Could not open file\n");
	line = get_next_line(fd);
	config_done = 0;
	y = 0;
	while (line)
	{
		if (!config_done && ft_parse_texture_color(&map, line))
		{
			free(line);
			line = get_next_line(fd);
			continue ;
		}
		if (ft_is_map_line(line))
		{
			config_done = 1;
			ft_parse_map_line(&map, line, y);
			y++;
		}
		else if (config_done && !ft_is_map_line(line)
			&& line[0] != '\n' && line[0] != 0)
			ft_mlx_error("Invalid map format\n");
		free(line);
		line = get_next_line(fd);
	}
	close(fd);
	ft_validate_map_textures(&map);
	return (map);
}
