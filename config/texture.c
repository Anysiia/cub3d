/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   texture.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cmorel-a <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/01/20 13:11:53 by cmorel-a          #+#    #+#             */
/*   Updated: 2020/02/09 12:40:48 by cmorel-a         ###   ########.fr       */
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

/*static t_image	*create_texture(t_config *config, int witch_texture)
{
	t_image		*image;

	if (!(image = malloc(sizeof(t_image))))
		exit_error("Error:\nCannot malloc texture image");
	image->img_ptr = mlx_xpm_file_to_image(config->init, 
		config->path_tex[witch_texture], &image->width, &image->height);
	image->data = mlx_get_data_addr(image->img_ptr, &image->bpp, 
		&image->size_line, &image->endian);
	return (image);
}*/

static int		convert_texture(char *file, int witch_texture, t_config *config)
{
/*	int		fd;*/

	if (!ft_type_file(file, ".xpm"))
		exit_error("Error:\nTexture or sprite file is not an .xpm");
/*	if ((fd = open(file, O_RDONLY)) == -1)
	{
		close(fd);
		exit_error("Error:\nCannot open texture or sprite file");
	}
	close(fd);*/
	config->path_tex[witch_texture] = file;
//	config->texture[witch_texture] = create_texture(config, witch_texture);
	return (1);
}

void			texture_path(char *str, t_config *config, char c, char d)
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
	if (c == 'N' && d == 'O')
		convert_texture(path, TEX_NO, config);
	if (c == 'S' && d == 'O')
		convert_texture(path, TEX_SO, config);
	if (c == 'W' && d == 'E')
		convert_texture(path, TEX_WE, config);
	if (c == 'E' && d == 'A')
		convert_texture(path, TEX_EA, config);
	if (c == 'S' && d == ' ')
		convert_texture(path, TEX_S, config);
}
