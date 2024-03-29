/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cub3d.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cmorel-a <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/01/20 16:22:48 by cmorel-a          #+#    #+#             */
/*   Updated: 2020/03/05 15:09:30 by cmorel-a         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef CUB3D_H
# define CUB3D_H
# include <stdlib.h>
# include <unistd.h>
# include <fcntl.h>
# include <math.h>
# include "mlx.h"
# include "../libft/libft.h"

# define ESC		53
# define LEFT		0
# define BACKWARD	1
# define FORWARD	13
# define RIGHT		2
# define CAM_LEFT	124
# define CAM_RIGHT	123

# define NB_TEX		5
# define TEX_WE		0
# define TEX_EA		1
# define TEX_NO		2
# define TEX_SO		3
# define TEX_S		4

# define SPRITE_MAX	256

typedef struct		s_list
{
	int				x;
	int				y;
	double			dist;
	struct s_list	*next;
}					t_list;

typedef struct		s_image
{
	void			*img;
	int				width;
	int				height;
	char			*data;
	int				bpp;
	int				size_line;
	int				endian;
}					t_image;

typedef struct		s_ray
{
	double			cam;
	int				stripe;
	double			ray_dir_x;
	double			ray_dir_y;
	int				map_x;
	int				map_y;
	double			side_dist_x;
	double			side_dist_y;
	double			delta_x;
	double			delta_y;
	double			distance;
	int				step_x;
	int				step_y;
	int				hit;
	int				side;
	int				line_height;
	int				draw_start;
	int				draw_stop;
	double			*dist_buff;
}					t_ray;

typedef struct		s_draw
{
	double			sprite_x;
	double			sprite_y;
	double			mat_x;
	double			mat_y;
	double			sprite_height;
	double			sprite_width;
	double			screen_x;
	int				draw_start_x;
	int				draw_stop_x;
	int				draw_start_y;
	int				draw_stop_y;
	int				stripe;
	int				y;
}					t_draw;

typedef struct		s_stripe
{
	int				x;
	int				y;
	int				start;
	int				stop;
	int				text_x;
	int				text_y;
}					t_stripe;

typedef struct		s_map
{
	char			**map;
	int				width;
	int				height;
	int				map_found;
	int				empty_line;
}					t_map;

typedef struct		s_player
{
	int				find;
	double			pos_x;
	double			pos_y;
	double			dir_x;
	double			dir_y;
	double			plane_x;
	double			plane_y;
	double			speed;
	double			rotate_speed;
}					t_player;

typedef struct		s_keyboard
{
	int				backward;
	int				forward;
	int				left;
	int				right;
	int				cam_left;
	int				cam_right;
}					t_keyboard;

typedef struct		s_config
{
	void			*init;
	void			*window;
	int				save;
	int				width;
	int				height;
	char			*path_tex[NB_TEX];
	int				floor;
	int				ceiling;
	t_map			*map;
	t_player		*player;
	t_keyboard		*key;
	t_image			*text[NB_TEX];
	t_image			*scene;
	t_list			*sprite;
}					t_config;

t_config			*init_config(int save);
int					check_arg(int ac, char **av, int save);
void				exit_error(const char *msg);
void				quit(t_config *config, const char *msg);
void				init_sprite(t_config *config);
void				init_key(t_config *config);
void				init_game(t_config *config);
void				init_scene(t_config *config);
char				*map_read_cub(const char *cub, t_config *config);
int					map_format(t_config *config, char *strmap);
int					map_validity(t_config *config);
void				find_player(t_config *config);
void				resolution(char *line, t_config *config);
void				color(char *line, t_config *config, char c);
void				texture_path(char *line, t_config *config);

int					raycaster(t_config *config);
void				stripe_caster(t_config *config, t_ray *ray);
void				put_texture(t_config *config, t_ray *ray);
void				handle_sprite(t_config *config, t_ray *ray);
void				sort_sprite(t_config *config, int lst_size);
void				put_sprite(t_config *config, t_ray *ray);
int					save_bitmap(t_config *config, t_ray *ray);
void				move_forward(t_config *config);
void				move_backward(t_config *config);
void				move_left(t_config *config);
void				move_right(t_config *config);
void				turn_right(t_config *config);
void				turn_left(t_config *config);
int					key_pressed(int key, t_config *config);
int					key_released(int key, t_config *config);
int					leave_window(t_config *config);
int					loop(t_config *config);

void				create_bitmap(t_config *config);

#endif
