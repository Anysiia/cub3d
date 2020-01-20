/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   texture.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cmorel-a <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/01/20 13:11:53 by cmorel-a          #+#    #+#             */
/*   Updated: 2020/01/20 16:29:36 by cmorel-a         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../cub3d.h"

static int	check_path_format(char *str)
{
	int		i;

	i = 1;
	if (str[i] != ' ')
		i++;
	while (str[i] == ' ')
		i++;
	if (str[i++] != '.')
		return (0);
	if (str[i++] != '/')
		return (0);
	while (ft_isprint(str[i]))
		i++;
	while (str[i] == ' ')
		i++;
	if (str[i] != '\0')
		return (0);
	return (1);
}

static int	path_size(char *str)
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

static void	check_path_file(char *file)
{
/*	int		fd;*/

	if (!ft_type_file(file, ".xpm"))
		error_config("Error:\nTexture file is not .xpm");
/*	if ((fd = open(file, O_RDONLY)) == -1)
	{
		close(fd);
		error_config("Error:\nCannot read texture file");
	}
	close(fd);*/
}

void		texture_path(char *str, t_config *config, char c, char d)
{
	char	*path;
	int		i;

	if (!check_path_format(str))
		error_config("Error:\nBad path format");
	i = (str[1] == ' ') ? 2 : 3;
	while (str[i] == ' ')
		i++;
	if (!(path = ft_substr(str, i, path_size(str))))
		error_config("Error:\nError on malloc path texture or sprite");
	check_path_file(path);
	if (c == 'N' && d == 'O')
		config->path_tex[TEX_NO] = path;
	if (c == 'S' && d == 'O')
		config->path_tex[TEX_SO] = path;
	if (c == 'W' && d == 'E')
		config->path_tex[TEX_WE] = path;
	if (c == 'E' && d == 'A')
		config->path_tex[TEX_EA] = path;
	if (c == 'S' && d == ' ')
		config->path_tex[TEX_S] = path;
}
