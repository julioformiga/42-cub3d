/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   debug.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: julio.formiga <julio.formiga@gmail.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/07 00:18:08 by julio.formiga     #+#    #+#             */
/*   Updated: 2025/04/07 00:18:08 by julio.formiga    ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

void ft_debug_map(t_map *map)
{
	int	i;
	int	j;
	i = 0;
	while (i < map->height)
	{
		j = 0;
		while (j < map->width)
		{
			// printf("%d ", map->data[i][j]);
			j++;
		}
		// printf("\n");
		i++;
	}
}
