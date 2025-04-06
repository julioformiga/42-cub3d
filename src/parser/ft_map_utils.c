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
