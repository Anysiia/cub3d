/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   texture.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cmorel-a <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/01/20 13:11:53 by cmorel-a          #+#    #+#             */
/*   Updated: 2020/02/11 15:31:24 by cmorel-a         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../cub3d.h"

static int		check_path_format(char *str)
{
	int		i;

	i = 1;
	if (str[i] != ' ')
		i++;
	while (str[i] == ' ')
		i++;
	if (str[i] != '/' && (str[i] != '.' && str[i + 1] != '/'))
		return (0);
	i++;
	while (ft_isprint(str[i]))
		i++;
	while (str[i] == ' ')
		i++;
	if (str[i] != '\0')
		return (0);
	return (1);
}

static int		path_size(char *str)
{
	int		i;
	int		len;

	i = (str[1] == ' ') ? 2 : 3;
	len = 0;
	while (str[i] == ' ')
		i++;
	while (ft_isprint(str[i]))
	{
		len++;
		i++;
	}
	return (len);
}

static int		convert_texture(char *file, int witch_texture, t_config *config)
{
	int		fd;

	if (!ft_type_file(file, ".xpm"))
		exit_error("Error:\nTexture or sprite file is not an .xpm");
	if ((fd = open(file, O_RDONLY)) == -1)
	{
		close(fd);
		exit_error("Error:\nCannot open texture or sprite file");
	}
	close(fd);
	config->path_tex[witch_texture] = file;
	return (1);
}

void			texture_path(char *str, t_config *config)
{
	char	*path;
	int		i;

	if (!check_path_format(str))
		exit_error("Error:\nBad path format");
	i = (str[1] == ' ') ? 2 : 3;
	while (str[i] == ' ')
		i++;
	if (!(path = ft_substr(str, i, path_size(str))))
		exit_error("Error:\nError on malloc path texture or sprite");
	if (str[0] == 'N' && str[1] == 'O')
		convert_texture(path, TEX_NO, config);
	else if (str[0] == 'S' && str[1] == 'O')
		convert_texture(path, TEX_SO, config);
	else if (str[0] == 'W' && str[1] == 'E')
		convert_texture(path, TEX_WE, config);
	else if (str[0] == 'E' && str[1] == 'A')
		convert_texture(path, TEX_EA, config);
	else if (str[0] == 'S' && str[1] == ' ')
		convert_texture(path, TEX_S, config);
	else if ((str[0] == 'N' && str[1] != 'O') 
		|| (str[0] == 'W' && str[1] != 'E') || (str[0] == 'E' && str[1] == 'A')
		|| (str[0] == 'S' && !(ft_test_set(str[1], " O"))))
		exit_error("Error:\nInvalid format on path texture");
}
