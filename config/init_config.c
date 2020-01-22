/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_config.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cmorel-a <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/01/21 13:06:54 by cmorel-a          #+#    #+#             */
/*   Updated: 2020/01/21 13:36:40 by cmorel-a         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

void		init_map(t_map *map)
{
	map->width = 0;
	map->height = 0;
	map->map = NULL;
}

void		init_config(t_config *config)
{
	int			i;

	config->width = 800;
	config->height = 400;
	i = 0;
	while (i < NB_TEX)
		config->path_tex[i] = NULL;
	config->color[TEX_NO] = 16763135;
	config->color[TEX_SO] = 13158655;
	config->color[TEX_WE] = 13158600;
	config->color[TEX_EA] = 15124710;
	config->floor = 15792383;
	config->ceiling = 16775388;
}
