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

int	ft_map_value(t_range range_in, t_range range_out, int value)
{
	if (range_out.max - range_out.min == 0)
		range_out.max = range_out.min + 1;
	return (range_in.min + ((range_in.max - range_in.min) / (range_out.max
				- range_out.min)) * (value - range_out.min));
}

static t_color	ft_parse_color(char *color_str)
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

static void	ft_remove_newline(char *str)
{
	int	len;

	if (!str)
		return ;
	len = ft_strlen(str);
	if (len > 0 && str[len - 1] == '\n')
		str[len - 1] = '\0';
}

static int	ft_parse_texture_color(t_map *map, char *line)
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

static int	ft_is_map_line(char *line)
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

static void	ft_validate_map_textures(t_map *map)
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
		else if (config_done && !ft_is_map_line(line) && line[0] != '\n'
			&& line[0] != 0)
			ft_mlx_error("Invalid map format\n");
		free(line);
		line = get_next_line(fd);
	}
	close(fd);
	ft_validate_map_textures(&map);
	return (map);
}
