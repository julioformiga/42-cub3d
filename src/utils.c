/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: julio.formiga <julio.formiga@gmail.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/24 17:08:54 by julio.formiga     #+#    #+#             */
/*   Updated: 2025/04/24 17:08:54 by julio.formiga    ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

int	ft_file_exists(char *path)
{
	int	fd;

	fd = open(path, O_RDONLY);
	if (fd < 0)
		return (1);
	close(fd);
	return (0);
}

int	ft_map_value(t_range range_in, t_range range_out, int value)
{
	if (range_out.max - range_out.min == 0)
		range_out.max = range_out.min + 1;
	return (range_in.min
		+ ((range_in.max - range_in.min) / (range_out.max - range_out.min))
		* (value - range_out.min));
}

void	free_map(t_map *map, int init_map)
{
	int	i;

	i = -1;
	while (i++, i < map->height)
		if (map->data[i])
			free(map->data[i]);
	free(map->data);
	if (init_map == 1)
	{
		if (map->line)
			free(map->line);
		if (map->north.path)
			free(map->north.path);
		if (map->south.path)
			free(map->south.path);
		if (map->west.path)
			free(map->west.path);
		if (map->east.path)
			free(map->east.path);
		if (map->door.path)
			free(map->door.path);
	}
}

void	map_error(t_map *map, char *msg)
{
	int	i;

	i = -1;
	while (i++, i < map->height)
		if (map->data[i])
			free(map->data[i]);
	free(map->data);
	while (map->line)
	{
		free(map->line);
		map->line = get_next_line(map->fd);
	}
	if (map->line)
		free(map->line);
	if (map->north.path)
		free(map->north.path);
	if (map->south.path)
		free(map->south.path);
	if (map->west.path)
		free(map->west.path);
	if (map->east.path)
		free(map->east.path);
	if (map->door.path)
		free(map->door.path);
	ft_mlx_error(msg);
}

/*
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
			else
				printf("? ");
		}
		printf("\n");
	}
}
*/

void	ft_remove_newline(char *str)
{
	int	len;

	if (!str)
		return ;
	len = ft_strlen(str);
	if (len > 0 && str[len - 1] == '\n')
		str[len - 1] = '\0';
}
