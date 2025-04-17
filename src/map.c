/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   map.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tfalchi <tfalchi@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/09 12:09:11 by julio.formi       #+#    #+#             */
/*   Updated: 2025/04/11 16:43:54 by tfalchi          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

void draw_minimap(t_env *env)
{
	int		i;
	int		j;
	double	size;

	size = env->map.size;
	if (!env->map.data)
	{
		printf("Map data is NULL\n");
		return ;
	}
	i = 0;
	env->map.player.dx = cos(env->map.player.direction);
	env->map.player.dy = sin(env->map.player.direction);
	raycasting3d(env);
	while (i < env->map.height)
	{
		j = 0;
		while (j < env->map.width)
		{
			if (!env->map.data[i])
			{
				printf("Map data[%d] is NULL\n", i);
				break ;
			}
			if (env->map.data[i][j] == 1)
				ft_mlx_draw_square(env, (t_point){j * size, i * size}, size, WHITE);
			else
				ft_mlx_draw_square(env, (t_point){j * size, i * size}, size, BLACK);
			j++;
		}
		i++;
	}
	player(env);
}

void	draw_map(t_env *env)
{
	int	floor;
	int	celing;
	t_point position;

	if (!env->map.data)
	{
		printf("Map data is NULL\n");
		return ;
	}
	ft_bzero(env->screen.addr, WIN_WIDTH * WIN_HEIGHT * ((float)env->screen.bpp / 8));
	if (env->map.ceiling.r)
		celing = ft_mlx_color(env->map.ceiling);
	else
		celing = ft_mlx_color((t_color){0, 135, 206, 235});
	if (env->map.floor.r)
		floor = ft_mlx_color(env->map.floor);
	else
		floor = ft_mlx_color((t_color){0, 100, 100, 100});
	ft_mlx_draw_rect(env, (t_rect){
		(t_point){0, 0},
		(t_point){0, WIN_HEIGHT/2},
		(t_point){WIN_WIDTH, WIN_HEIGHT/2},
		(t_point){WIN_WIDTH, 0},
	}, celing, 1);
	ft_mlx_draw_rect(env, (t_rect){
		(t_point){0, WIN_HEIGHT/2},
		(t_point){0, WIN_HEIGHT},
		(t_point){WIN_WIDTH, WIN_HEIGHT},
		(t_point){WIN_WIDTH, WIN_HEIGHT/2},
	}, floor, 1);
	draw_minimap(env);
	mlx_put_image_to_window(env->mlx, env->win, env->screen.img, 0, 0);
	map_render_info(env);
	position.x = (WIN_WIDTH / 2) - ((double)env->weapon.width / 2);
	position.y = WIN_HEIGHT - (env->weapon.frame_height * 1.2);
	sprite_draw(env, env->weapon, position, 1.2);
	mlx_do_sync(env->mlx);
	// ft_debug_map(&env->map);
}

void	map_render_info(t_env *env)
{
	char	*str;
	int		y_pos;
	int		x_pos;
	int		border_color;

	y_pos = 10;
	x_pos = WIN_WIDTH - 200;
	border_color = WHITE;

	ft_mlx_draw_line(env, (t_point){0, 0}, (t_point){WIN_WIDTH, 0}, border_color);
	ft_mlx_draw_line(env, (t_point){0, WIN_HEIGHT - 1}, (t_point){WIN_WIDTH, WIN_HEIGHT - 1}, border_color);
	ft_mlx_draw_line(env, (t_point){0, 0}, (t_point){0, WIN_HEIGHT}, border_color);
	ft_mlx_draw_line(env, (t_point){WIN_WIDTH - 1, 0}, (t_point){WIN_WIDTH - 1, WIN_HEIGHT}, border_color);

	y_pos += 20;
	mlx_string_put(env->mlx, env->win, x_pos, y_pos, GREEN, "Player Position:");

	y_pos += 20;
	str = ft_itoa(env->map.player.x);
	mlx_string_put(env->mlx, env->win, x_pos + 10, y_pos, WHITE, "X: ");
	mlx_string_put(env->mlx, env->win, x_pos + 30, y_pos, WHITE, str);
	free(str);

	y_pos += 20;
	str = ft_itoa(env->map.player.y);
	mlx_string_put(env->mlx, env->win, x_pos + 10, y_pos, WHITE, "Y: ");
	mlx_string_put(env->mlx, env->win, x_pos + 30, y_pos, WHITE, str);
	free(str);

	y_pos += 30;
	mlx_string_put(env->mlx, env->win, x_pos, y_pos, GREEN, "Player Direction:");

	y_pos += 20;
	str = ft_itoa((int)(env->map.player.direction * 180 / M_PI));
	mlx_string_put(env->mlx, env->win, x_pos + 10, y_pos, WHITE, "Angle: ");
	mlx_string_put(env->mlx, env->win, x_pos + 70, y_pos, WHITE, str);
	mlx_string_put(env->mlx, env->win, x_pos + 90, y_pos, WHITE, "degrees");
	free(str);

	y_pos += 20;
	char dx_str[10];
	sprintf(dx_str, "%.2f", env->map.player.dx);
	mlx_string_put(env->mlx, env->win, x_pos + 10, y_pos, WHITE, "DX: ");
	mlx_string_put(env->mlx, env->win, x_pos + 40, y_pos, WHITE, dx_str);

	y_pos += 20;
	char dy_str[10];
	sprintf(dy_str, "%.2f", env->map.player.dy);
	mlx_string_put(env->mlx, env->win, x_pos + 10, y_pos, WHITE, "DY: ");
	mlx_string_put(env->mlx, env->win, x_pos + 40, y_pos, WHITE, dy_str);

	y_pos += 20;
	char speed_str[10];
	sprintf(speed_str, "%.2f", env->map.player.speed);
	mlx_string_put(env->mlx, env->win, x_pos + 10, y_pos, WHITE, "Speed: ");
	mlx_string_put(env->mlx, env->win, x_pos + 70, y_pos, WHITE, speed_str);

	y_pos += 20;
	char mouse_speed_str[10];
	sprintf(mouse_speed_str, "%.4f", env->map.player.mouse_speed);
	mlx_string_put(env->mlx, env->win, x_pos + 10, y_pos, WHITE, "Mouse Speed: ");
	mlx_string_put(env->mlx, env->win, x_pos + 120, y_pos, WHITE, mouse_speed_str);

	y_pos += 30;
	mlx_string_put(env->mlx, env->win, x_pos, y_pos, CYAN, "Map Information:");

	y_pos += 20;
	str = ft_itoa(env->map.width);
	mlx_string_put(env->mlx, env->win, x_pos + 10, y_pos, WHITE, "Width: ");
	mlx_string_put(env->mlx, env->win, x_pos + 70, y_pos, WHITE, str);
	free(str);

	y_pos += 20;
	str = ft_itoa(env->map.height);
	mlx_string_put(env->mlx, env->win, x_pos + 10, y_pos, WHITE, "Height: ");
	mlx_string_put(env->mlx, env->win, x_pos + 70, y_pos, WHITE, str);
	free(str);

	y_pos += 20;
	char size_str[10];
	sprintf(size_str, "%.2f", env->map.size);
	mlx_string_put(env->mlx, env->win, x_pos + 10, y_pos, WHITE, "Size: ");
	mlx_string_put(env->mlx, env->win, x_pos + 70, y_pos, WHITE, size_str);

	y_pos += 30;
	mlx_string_put(env->mlx, env->win, x_pos, y_pos, YELLOW, "Raycasting Info:");

	y_pos += 20;
	str = ft_itoa(env->map.numrays);
	mlx_string_put(env->mlx, env->win, x_pos + 10, y_pos, WHITE, "Ray Count: ");
	mlx_string_put(env->mlx, env->win, x_pos + 100, y_pos, WHITE, str);
	free(str);

	y_pos += 20;
	str = ft_itoa(env->map.player.fov);
	mlx_string_put(env->mlx, env->win, x_pos + 10, y_pos, WHITE, "FOV: ");
	mlx_string_put(env->mlx, env->win, x_pos + 100, y_pos, WHITE, str);
	mlx_string_put(env->mlx, env->win, x_pos + 120, y_pos, WHITE, "degrees");
	free(str);

	y_pos += 20;
	float fov_rad = 60.0f * (M_PI / 180.0f);
	float left_angle = env->map.player.direction - (fov_rad / 2.0f);
	while (left_angle < 0)
		left_angle += 2 * M_PI;
	while (left_angle >= 2 * M_PI)
		left_angle -= 2 * M_PI;

	str = ft_itoa((int)(left_angle * 180 / M_PI));
	mlx_string_put(env->mlx, env->win, x_pos + 10, y_pos, WHITE, "FOV Left: ");
	mlx_string_put(env->mlx, env->win, x_pos + 100, y_pos, WHITE, str);
	mlx_string_put(env->mlx, env->win, x_pos + 130, y_pos, WHITE, "degrees");
	free(str);

	y_pos += 20;
	float right_angle = env->map.player.direction + (fov_rad / 2.0f);
	while (right_angle < 0)
		right_angle += 2 * M_PI;
	while (right_angle >= 2 * M_PI)
		right_angle -= 2 * M_PI;

	str = ft_itoa((int)(right_angle * 180 / M_PI));
	mlx_string_put(env->mlx, env->win, x_pos + 10, y_pos, WHITE, "FOV Right: ");
	mlx_string_put(env->mlx, env->win, x_pos + 100, y_pos, WHITE, str);
	mlx_string_put(env->mlx, env->win, x_pos + 130, y_pos, WHITE, "degrees");
	free(str);

	y_pos += 20;
	float fov_step = fov_rad / (60.0f - 1.0f);
	char angle_str[10];
	sprintf(angle_str, "%.2f", fov_step * 180 / M_PI);
	mlx_string_put(env->mlx, env->win, x_pos + 10, y_pos, WHITE, "Ray Step: ");
	mlx_string_put(env->mlx, env->win, x_pos + 100, y_pos, WHITE, angle_str);
	mlx_string_put(env->mlx, env->win, x_pos + 130, y_pos, WHITE, "degrees");

	y_pos += 40;

	mlx_string_put(env->mlx, env->win, x_pos, y_pos, MAGENTA, "Controls:");

	y_pos += 20;
	mlx_string_put(env->mlx, env->win, x_pos + 10, y_pos, env->keys.up ? YELLOW : WHITE, "UP");

	y_pos += 20;
	mlx_string_put(env->mlx, env->win, x_pos + 10, y_pos, env->keys.down ? YELLOW : WHITE, "DOWN");

	y_pos += 20;
	mlx_string_put(env->mlx, env->win, x_pos + 10, y_pos, env->keys.left ? YELLOW : WHITE, "LEFT");

	y_pos += 20;
	mlx_string_put(env->mlx, env->win, x_pos + 10, y_pos, env->keys.right ? YELLOW : WHITE, "RIGHT");
}
