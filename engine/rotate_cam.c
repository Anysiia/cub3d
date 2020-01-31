/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   rotate_cam.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cmorel-a <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/01/31 14:48:24 by cmorel-a          #+#    #+#             */
/*   Updated: 2020/01/31 15:03:06 by cmorel-a         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../cub3d.h"

void	turn_right(t_config *config)
{
	double	old_dirx;
	double	old_planex;
	double	rotate_speed;

	rotate_speed = config->player->rotate_speed;
	old_dirx = config->player->dir_x;
	old_planex = config->player->plane_x;
	config->player->dir_x = config->player->dir_x * cos(-rotate_speed)
		- config->player->dir_y * sin(-rotate_speed);
	config->player->dir_y = old_dirx * sin(-rotate_speed)
		+ config->player->dir_y * cos(-rotate_speed);
	config->player->plane_x = config->player->plane_x * cos(-rotate_speed)
		- config->player->plane_y * sin(-rotate_speed);
	config->player->plane_y = old_planex * sin(-rotate_speed)
		+ config->player->plane_y * cos(-rotate_speed);
}


void	turn_left(t_config *config)
{
	double	old_dirx;
	double	old_planex;
	double	rotate_speed;

	rotate_speed = config->player->rotate_speed;
	old_dirx = config->player->dir_x;
	old_planex = config->player->plane_x;
	config->player->dir_x = config->player->dir_x * cos(rotate_speed)
		- config->player->dir_y * sin(rotate_speed);
	config->player->dir_y = old_dirx * sin(rotate_speed)
		+ config->player->dir_y * cos(rotate_speed);
	config->player->plane_x = config->player->plane_x * cos(rotate_speed)
		- config->player->plane_y * sin(rotate_speed);
	config->player->plane_y = old_planex * sin(rotate_speed)
		+ config->player->plane_y * cos(rotate_speed);
}
