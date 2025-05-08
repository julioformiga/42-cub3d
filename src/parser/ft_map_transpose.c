/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_map_transpose.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tfalchi <tfalchi@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/08 02:15:19 by julio.formi       #+#    #+#             */
/*   Updated: 2025/05/08 12:48:29 by tfalchi          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

static int	*get_row_widths_and_max(t_map *map, int *max_width)
{
	int	*row_widths;
	int	i;
	int	j;

	row_widths = (int *)ft_calloc(map->height, sizeof(int));
	*max_width = 0;
	i = -1;
	while (i++, i < map->height)
	{
		j = 0;
		while (map->data[i] && map->data[i][j] != -2)
			j++;
		row_widths[i] = j;
		if (j > *max_width)
			*max_width = j;
	}
	return (row_widths);
}

static int	**allocate_transpose_map(int temp_height, int temp_width)
{
	int	**temp;
	int	i;
	int	j;

	temp = (int **)ft_calloc(temp_height + 1, sizeof(int *));
	i = -1;
	while (i++, i < temp_height)
	{
		temp[i] = (int *)ft_calloc(temp_width + 1, sizeof(int));
		j = -1;
		while (j++, j < temp_width)
			temp[i][j] = -1;
	}
	return (temp);
}

static void	fill_transpose_map(int **temp, t_map *map, int *row_widths)
{
	int	i;
	int	j;

	i = -1;
	while (i++, i < map->height)
	{
		j = -1;
		while (j++, j < row_widths[i])
			temp[j][i] = map->data[i][j];
	}
}

t_map	ft_map_transpose(t_map *map)
{
	t_map	temp_map;
	int		**temp;
	int		*row_widths;
	int		max_width;

	row_widths = get_row_widths_and_max(map, &max_width);
	temp = allocate_transpose_map(max_width, map->height);
	fill_transpose_map(temp, map, row_widths);
	temp_map.data = temp;
	temp_map.width = map->height;
	temp_map.height = max_width;
	free(row_widths);
	return (temp_map);
}
