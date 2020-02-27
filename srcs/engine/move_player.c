/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   move_player.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cmorel-a <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/01/30 16:29:12 by cmorel-a          #+#    #+#             */
/*   Updated: 2020/02/27 14:04:42 by cmorel-a         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/cub3d.h"

void	move_forward(t_config *config)
{
	if (config->map->map[(int)config->player->pos_y]
		[(int)(config->player->pos_x + config->player->dir_x
		* config->player->speed)] == '0')
		config->player->pos_x += config->player->dir_x * config->player->speed;
	if (config->map->map[(int)(config->player->pos_y
		+ config->player->dir_y * config->player->speed)]
		[(int)config->player->pos_x] == '0')
		config->player->pos_y += config->player->dir_y * config->player->speed;
}

void	move_backward(t_config *config)
{
	if (config->map->map[(int)config->player->pos_y]
		[(int)(config->player->pos_x - config->player->dir_x
		* config->player->speed)] == '0')
		config->player->pos_x -= config->player->dir_x * config->player->speed;
	if (config->map->map[(int)(config->player->pos_y
		- config->player->dir_y * config->player->speed)]
		[(int)config->player->pos_x] == '0')
		config->player->pos_y -= config->player->dir_y * config->player->speed;
}

void	move_left(t_config *config)
{
	if (config->map->map[(int)config->player->pos_y]
		[(int)(config->player->pos_x - config->player->plane_x
		* config->player->speed)] == '0')
		config->player->pos_x -= config->player->plane_x
		* config->player->speed;
	if (config->map->map[(int)(config->player->pos_y
		- config->player->plane_y * config->player->speed)]
		[(int)config->player->pos_x] == '0')
		config->player->pos_y -= config->player->plane_y
		* config->player->speed;
}

void	move_right(t_config *config)
{
	if (config->map->map[(int)config->player->pos_y]
		[(int)(config->player->pos_x + config->player->plane_x
		* config->player->speed)] == '0')
		config->player->pos_x += config->player->plane_x
		* config->player->speed;
	if (config->map->map[(int)(config->player->pos_y
		+ config->player->plane_y * config->player->speed)]
		[(int)config->player->pos_x] == '0')
		config->player->pos_y += config->player->plane_y
		* config->player->speed;
}
