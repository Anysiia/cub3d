/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   key_event.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cmorel-a <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/02/03 15:06:26 by cmorel-a          #+#    #+#             */
/*   Updated: 2020/02/27 14:04:15 by cmorel-a         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/cub3d.h"

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

int		leave_window(t_config *config)
{
	mlx_destroy_window(config->init, config->window);
	exit(0);
}

int		key_pressed(int key, t_config *config)
{
	if (key == ESC)
		quit(config, "");
	else if (key == LEFT)
		move_left(config);
	else if (key == RIGHT)
		move_right(config);
	else if (key == FORWARD)
		move_forward(config);
	else if (key == BACKWARD)
		move_backward(config);
	else if (key == CAM_LEFT)
		turn_left(config);
	else if (key == CAM_RIGHT)
		turn_right(config);
	raycaster(config);
	return (1);
}
