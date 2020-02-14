/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cub3d.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cmorel-a <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/01/20 16:22:48 by cmorel-a          #+#    #+#             */
/*   Updated: 2020/02/14 12:23:25 by cmorel-a         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef CUB3D_H
# define CUB3D_H
# include <stdlib.h>
# include <unistd.h>
# include <fcntl.h>
# include <math.h>
# include "mlx.h"
# include "libft/libft.h"

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

typedef struct	s_image
{
	void		*img;
	int			width;
	int			height;
	char		*data;
	int			bpp;
	int			size_line;
	int			endian;
}				t_image;

typedef struct	s_ray
{
	double		cam;
	int			stripe;
	double		ray_dir_x;
	double		ray_dir_y;
	int			map_x;
	int			map_y;
	double		side_dist_x;
	double		side_dist_y;
	double		delta_x;
	double		delta_y;
	double		distance;
	int			step_x;
	int			step_y;
	int			hit;
	int			side;
	int			line_height;
	int			draw_start;
	int			draw_stop;
	double		*img_buff;
}				t_ray;

typedef struct	s_stripe
{
	int			x;
	int			y;
	int			start;
	int			stop;
	int			text_x;
	int			text_y;
}				t_stripe;

typedef struct	s_map
{
	char		**map;
	int			width;
	int			height;
	int			map_found;
	int			empty_line;
}				t_map;

typedef struct	s_player
{
	int			find;
	double		pos_x;
	double		pos_y;
	double		dir_x;
	double		dir_y;
	double		plane_x;
	double		plane_y;
	double		move_speed;
	double		rotate_speed;
}				t_player;

typedef struct	s_config
{
	void		*init;
	void		*window;
	int			save;
	int			width;
	int			height;
	char		*path_tex[NB_TEX];
	int			floor;
	int			ceiling;
	t_map		*map;
	t_player	*player;
	t_image		*text[NB_TEX];
	t_image		*scene;
}				t_config;

t_config		*init_config(int save);
int				check_arg(int ac, char **av, int save);
void			exit_error(const char *msg);
void			quit(t_config *config, const char *msg);
void			init_game(t_config *config);
void			init_scene(t_config *config);
char			*map_read_cub(const char *cub, t_config *config);
int				map_format(t_config *config, char *strmap);
int				len_first_end_one(const char *str);
void			only_char_in_line(const char *line, char c);
void			check_last_line(t_config *config);
void			find_player(t_config *config);
void			resolution(char *line, t_config *config);
void			color(char *line, t_config *config, char c);
void			texture_path(char *line, t_config *config);

int				raycaster(t_config *config);
void			stripe_caster(t_config *config, t_ray *ray);
void			put_pixel_to_image(t_image *img, int x, int y, int color);
void			put_texture(t_config *config, t_ray *ray);
void			move_forward(t_config *config);
void			move_backward(t_config *config);
void			move_left(t_config *config);
void			move_right(t_config *config);
void			turn_right(t_config *config);
void			turn_left(t_config *config);
int				key_pressed(int key, t_config *config);
int				leave_window(t_config *config);

void			create_bitmap(t_config *config);

#endif
