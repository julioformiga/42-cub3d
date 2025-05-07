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

t_map	transpose_map(t_map *map)
{
	t_map temp_map;
	int	i;
	int	j;
	int	**temp;
	int	*row_widths;
	int	temp_height;
	int	temp_width;
	int max_width;

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
	for (i = 0; i < temp_height; i++) {
		temp[i] = (int *)ft_calloc(temp_width + 1, sizeof(int));
		for (j = 0; j < temp_width; j++)
			temp[i][j] = -1;
	}
	for (i = 0; i < map->height; i++) {
		for (j = 0; j < row_widths[i]; j++) {
			temp[j][i] = map->data[i][j];
		}
	}
	temp_map.data = temp;
	temp_map.width = map->height;
	temp_map.height = max_width;
	free(row_widths);
	return (temp_map);
}

void	print_map(t_map *map)
{
	int		i;
	int		j;
	int		value;

	i = -1;
	while (i++, i < map->height)
	{
		j = -1;
		while (j++, j < map->width && map->data[i] && map->data[i][j] >= -1)
		{
			value = map->data[i][j];
			if (value == -1)
				printf(". ");
			else if (value == 0)
				printf("0 ");
			else if (value == 1)
				printf("1 ");
			else if (value == 2)
				printf("D ");
			else if (value >= 0 && value < 5)
				printf("%c ", "NSWED"[value]);
			else
				printf("? ");
		}
		printf("\n");
	}
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
			line = get_next_line(fd);
			continue ;
		}
		free(line);
		line = get_next_line(fd);
	}
	close(fd);
	ft_validate_map_textures(&map);
	t_map	map_transpose;
	printf("\nNormal map:\n");
	print_map(&map);
	printf("\nTranspose map:\n");
	map_transpose = transpose_map(&map);
	print_map(&map_transpose);
	for (int i = 0; i < map_transpose.height; i++)
		if (map_transpose.data[i])
			free(map_transpose.data[i]);
	free(map_transpose.data);
	return (map);
}
