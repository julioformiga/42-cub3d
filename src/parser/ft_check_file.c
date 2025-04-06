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
