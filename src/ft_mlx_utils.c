/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_mlx_utils.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: julio.formiga <julio.formiga@gmail.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/05 06:15:34 by julio.formiga     #+#    #+#             */
/*   Updated: 2025/04/05 06:15:34 by julio.formiga    ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

void	ft_mlx_error(char *msg)
{
	ft_putstr_fd("Error: ", 2);
	ft_putstr_fd(msg, 2);
	ft_putstr_fd("\n", 2);
	exit(EXIT_FAILURE);
}

void	ft_free_array(int **ar)
{
	int	i;

	i = -1;
	while (i++, ar[i])
		free(ar[i]);
	free(ar);
}

void	ft_free_array_char(char **ar)
{
	int	i;

	i = -1;
	while (i++, ar[i])
		free(ar[i]);
	free(ar);
}

void	ft_check_dirfile(char *file)
{
	int	fd;

	fd = open(file, O_RDONLY | O_DIRECTORY);
	if (fd >= 0)
		ft_mlx_error("Is a directory");
	fd = open(file, O_RDONLY);
	if (fd < 0)
		ft_mlx_error("Opening file");
	close(fd);
}

int	ft_file_count_lines(int fd)
{
	char	*line;
	int		lines;

	lines = -1;
	line = get_next_line(fd);
	while (line)
	{
		lines++;
		free(line);
		line = get_next_line(fd);
	}
	free(line);
	return (lines);
}
