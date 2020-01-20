/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cub3d.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cmorel-a <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/01/20 16:22:48 by cmorel-a          #+#    #+#             */
/*   Updated: 2020/01/20 16:24:33 by cmorel-a         ###   ########.fr       */
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

typedef struct	s_config
{
	int		width;
	int		height;
	char	*path_tex[NB_TEX];
	int		floor;
	int		ceiling;
	t_map	*map;
}				t_config;

int				check_arg(int ac, char **av, int save);
void			error_config(const char *msg);
int				read_cub(const char *cub, t_config *config);
void			parse_config(char *line, t_config *config);
int				read_map(const char *line, t_config *config, int height_map);
int				copy_map(char *line, t_config *config, int fd);
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
int				player_init_posit(char c);
int				check_char_map(char c);

#endif
