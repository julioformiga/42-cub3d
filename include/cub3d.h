/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cub3d.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tfalchi <tfalchi@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/05 06:12:05 by julio.formi       #+#    #+#             */
/*   Updated: 2025/05/12 18:31:11 by tfalchi          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef CUB3D_H
# define CUB3D_H

# define WIN_TITLE "Cub3D"
# define WIN_HEIGHT 768.0
# define WIN_WIDTH 1280.0

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

# include "libft.h"
# include "mlx.h"
# include "mlx_int.h"
# include <X11/X.h>
# include <X11/Xlib.h>
# include <X11/extensions/Xfixes.h>
# include <X11/keysym.h>
# include <math.h>
# include <stdbool.h>
# include <stdio.h>
# include <string.h>
# include <time.h>
# include <unistd.h>

typedef struct s_sprite
{
	char		*path;
	void		*img;
	int			*data;
	int			width;
	int			height;
	int			bpp;
	int			size_line;
	int			endian;
	int			current_frame;
	int			frames_count;
	int			frame_height;
	int			animating;
	double		anim_duration;
	double		scale;
	clock_t		anim_start_time;
	int			visible;
}				t_sprite;

typedef struct s_color
{
	int			t;
	int			r;
	int			g;
	int			b;
}				t_color;

typedef struct s_point
{
	int			x;
	int			y;
}				t_point;

typedef struct s_rect
{
	t_point		p0;
	t_point		p1;
	t_point		p2;
	t_point		p3;
}				t_rect;

typedef struct s_texture
{
	char		*path;
	void		*img;
	int			*data;
	int			width;
	int			height;
	int			bpp;
	int			size_line;
	int			endian;
}				t_texture;

typedef struct s_raycast
{
	double		dir_x;
	double		dir_y;
	int			map_x;
	int			map_y;
	double		side_dist_x;
	double		side_dist_y;
	double		delta_dist_x;
	double		delta_dist_y;
	int			step_x;
	int			step_y;
	int			hit;
	int			side;
	double		perp_wall_dist;
	double		wall_x;
	int			tex_x;
	t_texture	*texture;
	int			map_value;
}				t_raycast;

typedef struct s_raycast3d
{
	double	angle;
	double	ray_length;
	double	wall_height;
	double	draw_start;
	double	draw_end;
	int		line_width;
	int		line_x;
	double	step;
	double	tex_pos;
	int		tex_y;
	int		color;
	size_t	i;
	int		y;
	int		w;
}	t_raycast3d;

typedef struct s_keys
{
	int			up;
	int			down;
	int			left;
	int			right;
	int			arrow_left;
	int			arrow_right;
}				t_keys;

typedef struct s_player
{
	double		x;
	double		y;
	double		dx;
	double		dy;
	double		speed;
	double		direction;
	double		fov;
	double		max_ray_distance;
	double		mouse_speed;
	int			mouse_x;
}				t_player;

typedef struct s_map
{
	int			error;
	int			**data;
	char		*line;
	int			fd;
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
	t_texture	door;
	t_color		floor;
	t_color		ceiling;
	t_player	player;
}				t_map;

typedef struct s_wall
{
	double		left;
	double		right;
	double		top;
	double		bottom;
}				t_wall;

typedef struct s_view
{
	int			projection;
	double		zoom;
	double		angle;
	double		angle_rotate;
	double		height;
	double		rotation_angle_x;
	double		rotation_angle_y;
	double		rotation_angle_z;
}				t_view;

typedef struct s_point3d
{
	int			x;
	int			y;
	int			z;
}				t_point3d;

typedef struct s_size
{
	int			w;
	int			h;
}				t_size;

typedef struct s_scr
{
	void		*img;
	char		*addr;
	int			bpp;
	int			line;
	int			endian;
}				t_scr;

typedef struct s_env
{
	t_xvar		*mlx;
	t_win_list	*win;
	t_img		*img;
	int			cursor_x;
	int			cursor_y;
	t_scr		screen;
	t_img		*imgs;
	t_map		map;
	t_view		view;
	t_point		init;
	t_keys		keys;
	t_sprite	weapon;
}				t_env;

typedef struct s_line
{
	int			color;
	t_point		p0;
	t_point		p1;
}				t_line;

typedef struct s_range
{
	int			min;
	int			max;
}				t_range;

typedef struct s_sprite_context
{
	t_env		*env;
	t_sprite	sprite;
	t_point		position;
	int			frame_offset;
}				t_sprite_context;

int				ft_open_file(char *file);
int				ft_file_exists(char *path);
void			ft_init_map(t_map *map, char *file);
void			ft_remove_newline(char *str);
void			ft_validate_map_textures(t_map *map);
void			ft_validate_map(t_map *map);
t_color			ft_parse_color(char *color_str);
int				ft_parse_texture_color(t_map *map);
int				ft_is_map_line(char *line);
void			free_map(t_map *map, int init_map);
t_map			ft_map_transpose(t_map *map);
void			map_error(t_map *map, char *msg);

void			ft_mlx_put_image(t_env *env);
void			ft_mlx_error(char *msg);
void			ft_debug_map(t_map *map);
void			ft_check_file(char *file);
t_env			*ft_mlx_create_env(void);
void			ft_mlx_hooks(t_env *env);
int				ft_mlx_keypress(int keycode, t_env *env);
int				ft_mlx_keyrelease(int keycode, t_env *env);
int				ft_update_game(t_env *env);
int				ft_mlx_destroy_window(t_env *env);
int				ft_mlx_color(t_color color);
void			ft_mlx_draw_line(t_env *env, t_point p0, t_point p1, int color);
void			ft_mlx_draw_square(t_env *env, t_point p, int width, int color);
int				ft_mlx_line_color(t_env *env, int i, int j, char type);
int				ft_map_value(t_range range_in, t_range range_out, int value);
void			ft_mouse_hide(t_xvar *xvar, t_win_list *win);
int				ft_mlx_button_release(int button, int x, int y, t_env *env);
int				ft_mlx_button(int button, int x, int y, t_env *env);
int				ft_mouse_move(t_env *env);
void			init_textures(t_env *env);
void			ray_calc_walls(t_env *env, t_raycast *ray);
void			ray_calc_iterations(t_env *env, t_raycast *ray, int iterations,
					int v);
void			ray_calc_perpendicular_distance(t_env *env, t_raycast *ray);
double			calculate_ray_length(t_env *env, t_raycast *ray,
					double ray_angle, int visual);
double			ray_calc_length(t_env *env, t_raycast *ray, double ray_angle);
void			raycasting(t_env *env);
void			raycasting3d(t_env *env);
void			ft_draw_line_to_image(t_env *env, int x, int y, int color);
void			ft_mlx_draw_rect(t_env *env, t_rect rect, int color, int fill);
void			ft_check_dirfile(char *file);
int				ft_file_count_lines(int fd);
void			ft_free_array(int **ar);
void			ft_free_array_char(char **ar);
void			ft_mlx_xpm(t_env *env, char *filename);
t_map			ft_map_parse(char *file);
void			draw_map(t_env *env);
void			map_render_info(t_env *env);
void			player(t_env *env);
void			free_all(t_env *env);

/* Sprite functions */
void			sprite_load(t_env *env, char *path);
void			sprite_set_frame(t_sprite *sprite, int frame_index);
void			sprite_draw(t_env *env, t_sprite sprite, t_point position);
void			sprite_play(t_sprite *sprite);
void			sprite_update_animation(t_sprite *sprite);

#endif
