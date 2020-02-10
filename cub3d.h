/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cub3d.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cmorel-a <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/01/20 16:22:48 by cmorel-a          #+#    #+#             */
/*   Updated: 2020/02/09 13:25:12 by cmorel-a         ###   ########.fr       */
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
	void		*img_ptr;
	int			width;
	int			height;
	char		*data;
	int			bpp;
	int			size_line;
	int			endian;
}				t_image;

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
	char		*path_tex[NB_TEX];
	int			color[NB_TEX];;
	int			floor;
	int			ceiling;
	int			map_found;
	int			empty_line;
	t_map		*map;
	t_player	*player;
	t_image		*texture[NB_TEX];
}				t_config;

t_config		*init_config(int save);
int				check_arg(int ac, char **av, int save);
void			exit_error(const char *msg);
void			quit(t_config *config, const char *msg);
void			init_game(t_config *config);
char			*map_read_cub(const char *cub, t_config *config);
int				map_format(t_config *config, char *strmap);
void			only_char_in_line(const char *line, char c);
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
int				key_pressed(int key, t_config *config);
int				leave_window(t_config *config);

//to add in libft
int				get_next_line(int fd, char **line);
char			*ft_free_s1_join(char *s1, const char *s2);
int				ft_type_file(const char *file, const char *type);
int				test_set(char c, char *charset);

//utils
int				len_first_end_one(char *str);

#endif
