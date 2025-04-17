/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_mlx_image.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tfalchi <tfalchi@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/05 02:19:51 by julio.formi       #+#    #+#             */
/*   Updated: 2025/04/15 17:33:10 by tfalchi          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

void	ft_mlx_xpm(t_env *env, char *filename)
{
	env->imgs = (t_img *)ft_calloc(1, sizeof(t_img));
	env->imgs->width = 1280;
	env->imgs->height = 90;
	env->imgs->image = mlx_xpm_file_to_image(env->mlx, filename,
			&env->imgs->width, &env->imgs->height);
}

void	ft_mlx_put_image(t_env *env)
{
	int	x_init;

	x_init = (WIN_WIDTH / 2) - ((double)env->imgs->width / 2);
	mlx_put_image_to_window(env->mlx, env->win, env->imgs->image, x_init, 0);
	mlx_do_sync(env->mlx);
}
