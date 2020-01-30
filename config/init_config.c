/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_config.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cmorel-a <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/01/21 13:06:54 by cmorel-a          #+#    #+#             */
/*   Updated: 2020/01/30 12:35:49 by cmorel-a         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../cub3d.h"

void		init_map(t_config *config)
{
	if (!(config->map = malloc(sizeof(t_map))))
		exit_error("Error:\nMalloc initialisation map");
	config->map->width = 0;
	config->map->height = 0;
	config->map->map = NULL;
}

t_config	*init_config(void)
{
	t_config	*config;
	int			i;

	if (!(config = malloc(sizeof(t_config))))
		exit_error("Error:\nMalloc initialisation configuration");
	config->width = 800;
	config->height = 400;
	i = 0;
	while (i < NB_TEX)
		config->path_tex[i++] = NULL;
	config->color[TEX_NO] = 16763135;
	config->color[TEX_SO] = 13158655;
	config->color[TEX_WE] = 13158600;
	config->color[TEX_EA] = 15124710;
	config->floor = 15792383;
	config->ceiling = 16775388;
	init_map(config);
	return (config);
}
