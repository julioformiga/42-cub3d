/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_check_file.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: julio.formiga <julio.formiga@gmail.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/05 06:12:05 by julio.formiga     #+#    #+#             */
/*   Updated: 2025/04/05 06:12:05 by julio.formiga    ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

void	ft_check_file(char *file)
{
	int	fd;
	int	len;

	len = ft_strlen(file);
	if (len < 5)
		ft_mlx_error("Invalid file name\n");
	if (ft_strncmp(file + len - 4, ".cub", 4) != 0)
		ft_mlx_error("File must have .cub extension\n");
	fd = open(file, O_RDONLY);
	if (fd < 0)
		ft_mlx_error("Could not open file\n");
	close(fd);
}

static int	ft_process_map_line(char *line, int *map_started, int *count)
{
	if (ft_is_map_line(line))
	{
		*map_started = 1;
		(*count)++;
		return (0);
	}
	else if (*map_started)
		return (1);
	return (0);
}

static int	ft_count_map_lines(char *file)
{
	int		fd;
	char	*line;
	int		count;
	int		map_started;

	fd = ft_open_file(file);
	count = 0;
	map_started = 0;
	line = get_next_line(fd);
	while (line)
	{
		if (ft_process_map_line(line, &map_started, &count))
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

int	ft_open_file(char *file)
{
	int	fd;

	fd = open(file, O_RDONLY);
	if (fd < 0)
		ft_mlx_error("Could not open file\n");
	return (fd);
}

void	ft_init_map(t_map *map, char *file)
{
	map = calloc(sizeof(t_map), 1);
	map->player.direction = 0;
	map->floor = (t_color){0, 100, 100, 100};
	map->ceiling = (t_color){0, 135, 206, 235};
	map->height = ft_count_map_lines(file);
	map->data = (int **)ft_calloc(map->height + 1, sizeof(int *));
	if (!map->data)
		ft_mlx_error("Memory allocation failed\n");
}
