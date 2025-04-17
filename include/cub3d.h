/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cub3d.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tfalchi <tfalchi@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/05 06:12:05 by julio.formi       #+#    #+#             */
/*   Updated: 2025/04/15 17:52:20 by tfalchi          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef CUB3D
# define CUB3D

# define WIN_TITLE "Cub3D"
// # define WIN_WIDTH 1024
# define WIN_HEIGHT 768.0
# define WIN_WIDTH 1280.0
// # define WIN_HEIGHT 1024

# define BLACK 0
# define BLUE 255
# define GREEN_DARK 32768
# define GREEN 65280
# define CYAN 65535
# define GRAY 8421504
# define GRAY_DARK 2631720
# define RED 16711680
# define MAGENTA 16711935
# define YELLOW 16776960
# define WHITE 16777215

# include <stdio.h>
# include <math.h>
# include <unistd.h>
# include <time.h>
# include <string.h>
# include <X11/keysym.h>
# include <X11/X.h>
# include <stdbool.h>
# include "libft.h"
# include "mlx.h"

typedef struct s_sprite
{
	char	*path;
	void	*img;
	int		*data;
	int		width;
	int		height;
	int		bpp;
	int		size_line;
	int		endian;
	int		current_frame;
	int		frames_count;
	int		frame_height;
	int		visible;
}	t_sprite;

typedef struct s_color
{
	int	t;
	int	r;
	int	g;
	int	b;
}	t_color;

typedef struct s_point
{
	int	x;
	int	y;
}	t_point;

typedef struct s_rect
{
	t_point	p0;
	t_point	p1;
	t_point	p2;
	t_point	p3;
}	t_rect;

typedef struct s_texture
{
	char	*path;
	void	*img;
	int		*data;
	int		width;
	int		height;
	int		bpp;
	int		size_line;
	int		endian;
}	t_texture;

typedef struct s_raycast
{
	double	ray_dir_x;
	double	ray_dir_y;
	int		map_x;
	int		map_y;
	double	side_dist_x;
	double	side_dist_y;
	double	delta_dist_x;
	double	delta_dist_y;
	int		step_x;
	int		step_y;
	int		hit;
	int		side;
	double	perp_wall_dist;
	double	wall_x;
	int		tex_x;
	t_texture *texture;
} t_raycast;

typedef struct s_keys
{
	int	up;
	int	down;
	int	left;
	int	right;
	int	arrow_left;
	int	arrow_right;
}	t_keys;

typedef struct s_player
{
	double	x;
	double	y;
	double	dx;
	double	dy;
	double	speed;
	double	direction;
	double	fov;
	double	mouse_speed;
	int		mouse_x;
}	t_player;

typedef struct s_map
{
	int			**data;
	int			width;
	int			height;
	int			min;
	int			max;
	double		size;
	double		numrays;
	t_texture	north;
	t_texture	south;
	t_texture	west;
	t_texture	east;
	t_color		floor;
	t_color		ceiling;
	t_player	player;
}	t_map;

typedef struct s_view
{
	int		projection;
	double	zoom;
	double	angle;
	double	angle_rotate;
	double	height;
	double	rotation_angle_x;
	double	rotation_angle_y;
	double	rotation_angle_z;
}	t_view;

typedef struct s_point3d
{
	int	x;
	int	y;
	int	z;
}	t_point3d;

typedef struct s_size
{
	int	w;
	int	h;
}	t_size;

typedef struct s_img
{
	void	*img;
	t_size	size;
}	t_img;

typedef struct s_scr
{
	void	*img;
	char	*addr;
	int		bpp;
	int		line;
	int		endian;
}	t_scr;

typedef struct s_env
{
	void		*mlx;
	void		*win;
	void		*img;
	int			cursor_x;
	int			cursor_y;
	t_scr		screen;
	t_img		*imgs;
	t_map		map;
	t_view		view;
	t_point		init;
	t_keys		keys;
	t_sprite	weapon;
}	t_env;

typedef struct s_line
{
	int		color;
	t_point	p0;
	t_point	p1;
}	t_line;

typedef struct s_range
{
	int	min;
	int	max;
}	t_range;

void		ft_mlx_put_image(t_env *env);
void		ft_mlx_error(char *msg);
void		ft_debug_map(t_map *map);
void		ft_check_file(char *file);
t_env		*ft_mlx_create_env(void);
void		ft_mlx_hooks(t_env *env);
int			ft_mlx_keypress(int keycode, t_env *env);
int			ft_mlx_keyrelease(int keycode, t_env *env);
int			ft_update_game(t_env *env);
int			ft_mlx_destroy_window(t_env *env);
int			ft_mlx_color(t_color color);
void		ft_mlx_draw_line(t_env *env, t_point p0, t_point p1, int color);
void		ft_mlx_draw_square(t_env *env, t_point p, int width, int color);
int			ft_mlx_line_color(t_env *env, int i, int j, char type);
int			ft_map_value(t_range range_in, t_range range_out, int value);
void		ft_map_init(t_map *map, int n);

void		init_textures(t_env *env);
void		raycasting(t_env *env);
void		raycasting3d(t_env *env);
void		ft_draw_line_to_image(t_env *env, int x, int y, int color);
void		ft_mlx_draw_rect(t_env *env, t_rect rect, int color, int fill);
void		ft_check_dirfile(char *file);
int			ft_file_count_lines(int fd);
void		ft_free_array(int **ar);
void		ft_free_array_char(char **ar);
void		ft_mlx_xpm(t_env *env, char *filename);
t_map		ft_map_parse(char *file);
void		draw_map(t_env *env);
void		map_render_info(t_env *env);
void		player(t_env *env);
void		free_all(t_env *env);

/* Sprite functions */
void		sprite_load(t_env *env, char *path);
void		sprite_set_frame(t_sprite *sprite, int frame_index);
void		sprite_draw(t_env *env, t_sprite sprite,
							   t_point position, double scale);
void		free_sprite(t_env *env, t_sprite *sprite);

#endif
