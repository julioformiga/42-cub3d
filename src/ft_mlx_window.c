/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_mlx_window.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: julio.formiga <julio.formiga@gmail.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/05 02:19:51 by julio.formiga     #+#    #+#             */
/*   Updated: 2025/04/05 02:19:51 by julio.formiga    ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

t_env	*ft_mlx_create_env(void)
{
	t_env	*env;

	env = (t_env *)malloc(sizeof(t_env));
	if (!env)
		ft_mlx_error("malloc() failed");
	env->mlx = mlx_init();
	if (!env->mlx)
		ft_mlx_error("mlx_init() failed");
	env->win = mlx_new_window(env->mlx, WIN_WIDTH, WIN_HEIGHT, "Cub3D");
	if (!env->win)
		ft_mlx_error("mlx_new_window() failed");
	env->cursor_x = WIN_WIDTH / 2;
	env->cursor_y = WIN_HEIGHT / 2;
	env->init = (t_point){0, 0};
	ft_mlx_xpm(env, "./assets/header.xpm");
	return (env);
}

int	ft_mlx_destroy_window(t_env *env)
{
	if (env->mlx)
	{
		while (env->map.height--)
			free(env->map.data[env->map.height]);
		free(env->map.data);
		if (env->imgs->img)
		{
			mlx_destroy_image(env->mlx, env->imgs->img);
			free(env->imgs);
		}
		mlx_destroy_image(env->mlx, env->screen.img);
		if (env->win)
			mlx_destroy_window(env->mlx, env->win);
		mlx_destroy_display(env->mlx);
		free(env->mlx);
		free(env);
	}
	exit(EXIT_SUCCESS);
	return (0);
}
