/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cub3d.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cmorel-a <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/01/20 16:22:48 by cmorel-a          #+#    #+#             */
/*   Updated: 2020/01/30 13:29:21 by cmorel-a         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef CUB3D_H
# define CUB3D_H
# include <stdlib.h>
# include <unistd.h>
# include <fcntl.h>
# include "mlx.h"
# include "libft/libft.h"

# define NB_TEX	5
# define TEX_NO	0
# define TEX_SO	1
# define TEX_WE	2
# define TEX_EA	3
# define TEX_S	4

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
}				t_config;

t_config		*init_config(void);
int				check_arg(int ac, char **av, int save);
void			exit_error(const char *msg);
char			*map_read_cub(const char *cub, t_config *config);
int				map_format(t_config *config, char *strmap);
void			find_player(t_config *config);
void			resolution(char *line, t_config *config);
void			color(char *line, t_config *config, char c);
void			texture_path(char *line, t_config *config, char c, char d);

int				get_next_line(int fd, char **line);
char			*ft_free_s1_join(char *s1, const char *s2);
int				ft_type_file(const char *file, const char *type);
int				len_to_no_one(char *str);
int				test_set(char c, char *charset);

#endif
