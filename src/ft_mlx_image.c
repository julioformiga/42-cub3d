/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_mlx_image.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: julio.formiga <julio.formiga@gmail.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/05 02:19:51 by julio.formiga     #+#    #+#             */
/*   Updated: 2025/04/05 02:19:51 by julio.formiga    ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

void	ft_mlx_xpm(t_env *env, char *filename)
{
	env->imgs = (t_img *)malloc(sizeof(t_img));
	env->imgs->size.w = 1280;
	env->imgs->size.h = 90;
	env->imgs->img = mlx_xpm_file_to_image(env->mlx, filename,
			&env->imgs->size.w, &env->imgs->size.h);
}

void	ft_mlx_put_image(t_env *env)
{
	int	x_init;

	x_init = (WIN_WIDTH / 2) - (env->imgs->size.w / 2);
	mlx_put_image_to_window(env->mlx, env->win, env->imgs->img, x_init, 0);
	mlx_do_sync(env->mlx);
}
