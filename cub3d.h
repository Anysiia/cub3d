/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cub3d.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cmorel-a <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/01/20 16:22:48 by cmorel-a          #+#    #+#             */
/*   Updated: 2020/02/06 13:45:29 by cmorel-a         ###   ########.fr       */
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
# define CAM_LEFT	123
# define CAM_RIGHT	124

# define NB_TEX		4
# define TEX_NO		0
# define TEX_SO		1
# define TEX_WE		2
# define TEX_EA		3

typedef struct	s_texture
{
	int			width;
	int			height;
	int			size_line;
	int			bpp;
	int			endian;
	void		*img_ptr;
	char		*data;
}				t_texture;

typedef struct	s_sprite
{
	int			width;
	int			height;
	int			size_line;
	int			bpp;
	int			endian;
	void		*img_ptr;
	char		*data;
	int			no_sprite;
}				t_sprite;

typedef struct	s_ray
{
	double		camera_x;
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
	int			camera_height;
	double		*img_buff;
}				t_ray;

typedef struct	s_keyboard
{
	int			left;
	int			right;
	int			backward;
	int			forward;
	int			cam_left;
	int			cam_right;
}				t_keyboard;

typedef struct	s_map
{
	char		**map;
	int			width;
	int			height;
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
	char		*path_tex[NB_TEX + 1];
	int			color[NB_TEX];;
	int			floor;
	int			ceiling;
	int			map_found;
	int			empty_line;
	t_map		*map;
	t_player	*player;
	t_keyboard	*keyboard;
	t_texture	*texture[NB_TEX];
	t_sprite	*sprite;
}				t_config;

t_config		*init_config(void);
int				check_arg(int ac, char **av, int save);
void			exit_error(const char *msg);
void			quit(t_config *config, const char *msg);
void			init_game(t_config *config);
char			*map_read_cub(const char *cub, t_config *config);
int				map_format(t_config *config, char *strmap);
void			find_player(t_config *config);
void			resolution(char *line, t_config *config);
void			color(char *line, t_config *config, char c);
void			texture_path(char *line, t_config *config, char c, char d);

int				raycaster(t_config *config);
void			side(t_ray *ray, t_config *config);
void			dist_and_height(t_ray *ray, t_player *player, t_config *config);
void			move_forward(t_config *config);
void			move_backward(t_config *config);
void			move_left(t_config *config);
void			move_right(t_config *config);
void			turn_right(t_config *config);
void			turn_left(t_config *config);
int				keyboard_manager(t_config *config);
int				key_pressed(int key, t_config *config);
int				key_released(int key, t_config *config);
int				leave_window(t_config *config);
int				loop(t_config *config);

int				get_next_line(int fd, char **line);
char			*ft_free_s1_join(char *s1, const char *s2);
int				ft_type_file(const char *file, const char *type);
int				len_to_no_one(char *str);
int				test_set(char c, char *charset);

#endif
