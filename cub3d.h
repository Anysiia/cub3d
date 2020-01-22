/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cub3d.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cmorel-a <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/01/20 16:22:48 by cmorel-a          #+#    #+#             */
/*   Updated: 2020/01/22 16:26:13 by cmorel-a         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef CUB3D_H
# define CUB3D_H
# include <stdlib.h>
# include <unistd.h>
# include <fcntl.h>
# include <mlx.h>

# define NB_TEX	5
# define TEX_NO	0
# define TEX_SO	1
# define TEX_WE	2
# define TEX_EA	3
# define TEX_S	4

typedef struct	s_img
{
	int			width;
	int			height;
	int			size_line;
	int			bpp;
	int			endian;
	void		*img_ptr;
	char		*data;
}				t_img;

typedef struct	s_map
{
	char		**map;
	int			width;
	int			height;
}				t_map;

typedef struct	s_player
{
	double		pos_x;
	double		pos_y;
	double		dir_x;
	double		dir_y;
	double		move_speed;
	double		rotate_speed;
}				t_player;

typedef struct	s_config
{
	int			width;
	int			height;
	char		*path_tex[NB_TEX];
	int			color[NB_TEX];;
	int			floor;
	int			ceiling;
	int			map_found;
	t_map		*map;
	t_player	player;
}				t_config;

int				check_arg(int ac, char **av, int save);
void			error_config(const char *msg);
void			free_error(char *line, const char *msg);
void			read_cub(const char *cub, t_config *config);
char			*map_read_cub(const char *cub, t_config *config);
void			config_map(char *line, t_config *config, char **map, int res);
void			map_save(char *line, char *map, t_config *config, int res);
void			resolution(char *line, t_config *config);
void			color(char *line, t_config *config, char c);
void			texture_path(char *line, t_config *config, char c, char d);

int				get_next_line(int fd, char **line);

int				ft_strlen(const char *s);
int				ft_isdigit(char c);
int				ft_isprint(char c);
char			*ft_strjoin(const char *s1, const char *s2);
int				ft_atoi(const char *s);
size_t			ft_strlcpy(char *dst, const char *src, size_t size);
void			ft_bzero(void *s, size_t n);
char			*ft_strnew(size_t size);
char			*ft_substr(char const *s, unsigned int start, size_t len);
char			**ft_split(const char *s, char c);
int				ft_strcmp(const char *s1, const char *s2);
char			*ft_substr(char const *s, unsigned int start, size_t len);
int				ft_type_file(const char *file, const char *type);
int				len_to_no_one(char *str);
int				test_set(char c, char *charset);

#endif
