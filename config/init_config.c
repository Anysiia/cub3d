/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_config.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cmorel-a <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/01/21 13:06:54 by cmorel-a          #+#    #+#             */
/*   Updated: 2020/02/04 13:56:24 by cmorel-a         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../cub3d.h"

static void	init_map_and_keyboard(t_config *config)
{
	if (!(config->map = malloc(sizeof(t_map))))
		exit_error("Error:\nMalloc initialisation map");
	if (!(config->keyboard = malloc(sizeof(t_keyboard))))
		exit_error("Error:\nMalloc initialisation keyboard manager");
	config->map->width = 0;
	config->map->height = 0;
	config->map->map = NULL;
	config->keyboard->right = 0;
	config->keyboard->left = 0;
	config->keyboard->backward = 0;
	config->keyboard->forward = 0;
	config->keyboard->cam_left = 0;
	config->keyboard->cam_right = 0;
}

static void	init_texture_and_sprite(t_config *config)
{
	int		i;

	i = 0;
	while (i < NB_TEX)
	{
		if (!(config->texture[i] = malloc(sizeof(t_texture))))
			exit_error("Error:\nMalloc initialisation texture");
		ft_bzero(config->texture[i], sizeof(t_texture));
		i++;
	}
	config->texture[TEX_NO]->no_text = 16763135;
	config->texture[TEX_SO]->no_text = 13158655;
	config->texture[TEX_WE]->no_text = 13158600;
	config->texture[TEX_EA]->no_text = 15124710;
	if (!(config->sprite = malloc(sizeof(t_sprite))))
		exit_error("Error:\nMalloc initialisation sprite");
	ft_bzero(config->sprite, sizeof(t_sprite));
}

t_config	*init_config(void)
{
	t_config	*config;
	int			i;

	if (!(config = malloc(sizeof(t_config))))
		exit_error("Error:\nMalloc initialisation configuration");
	config->width = -1;
	config->height = -1;
	config->save = 0;
	i = 0;
	while (i < NB_TEX)
		config->path_tex[i++] = NULL;
	config->floor = -1;
	config->ceiling = -1;
	init_map_and_keyboard(config);
	init_texture_and_sprite(config);
	return (config);
}

void	check_config(t_config *config)
{
	if (config->map_found == 0)
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
	if (config->floor == -1)
		exit_error("Error:\nColor of floor not found on .cub file");
	if (config->ceiling == -1)
		exit_error("Error:\nColor of ceiling not found on .cub file");
}
