/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_config.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cmorel-a <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/01/21 13:06:54 by cmorel-a          #+#    #+#             */
/*   Updated: 2020/02/13 11:03:07 by cmorel-a         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../cub3d.h"

static void	init_map(t_config *config)
{
	if (!(config->map = malloc(sizeof(t_map))))
		exit_error("Error:\nMalloc initialisation map");
	config->map->width = 0;
	config->map->height = 0;
	config->map->map = NULL;
}

static void	check_config(t_config *config)
{
	if (config->map->map_found == 0)
		exit_error("Error:\nMap not found on .cub file");
	if (config->path_tex[TEX_NO] == NULL)
		exit_error("Error:\nTexture north not found on .cub file");
	if (config->path_tex[TEX_SO] == NULL)
		exit_error("Error:\nTexture south not found on .cub file");
	if (config->path_tex[TEX_WE] == NULL)
		exit_error("Error:\nTexture west not found on .cub file");
	if (config->path_tex[TEX_EA] == NULL)
		exit_error("Error:\nTexture east not found on .cub file");
	if (config->path_tex[4] == NULL)
		exit_error("Error:\nSprite not found on .cub file");
	if (config->width == -1 || config->height == -1)
		exit_error("Error:\nResolution not found on .cub file");
	if (config->floor[0] == -1)
		exit_error("Error:\nColor of floor not found on .cub file");
	if (config->ceiling[0] == -1)
		exit_error("Error:\nColor of ceiling not found on .cub file");
}

t_config	*init_config(int save)
{
	t_config	*config;
	int			i;

	if (!(config = malloc(sizeof(t_config))))
		exit_error("Error:\nMalloc initialisation configuration");
	config->width = -1;
	config->height = -1;
	config->save = save;
	i = 0;
	while (i < NB_TEX)
		config->path_tex[i++] = NULL;
	config->floor[0] = -1;
	config->ceiling[0] = -1;
	init_map(config);
	return (config);
}

void		init_game(t_config *config)
{
	int		i;

	check_config(config);
	if (!(config->init = mlx_init()))
		exit_error("Error:\nError on mlx_init");
	if (!(config->window = mlx_new_window(config->init, config->width,
			config->height, "cub3d")))
		exit_error("Error:\nCannot create window with mlx");
	i = 0;
	while (i < NB_TEX)
	{
		if (!(config->text[i] = malloc(sizeof(t_image))))
			exit_error("Error:\nCannot malloc texture image");
		if (!(config->text[i]->img = mlx_xpm_file_to_image(config->init,
			config->path_tex[i], &config->text[i]->width, 
			&config->text[i]->height)))
			exit_error("Error:\nConvert xmp texture file failed");
		if (!(config->text[i]->data = mlx_get_data_addr(config->text[i]->img,
			&config->text[i]->bpp, &config->text[i]->size_line,
			&config->text[i]->endian)))
			exit_error("Error:\nConvert xmp texture file failed");
		i++;
	}
}
