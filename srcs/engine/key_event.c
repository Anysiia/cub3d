/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   key_event.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cmorel-a <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/02/03 15:06:26 by cmorel-a          #+#    #+#             */
/*   Updated: 2020/03/05 15:15:23 by cmorel-a         ###   ########.fr       */
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

int		key_pressed(int key, t_config *config)
{
	if (key == ESC)
		quit(config, "");
	else if (key == LEFT && config->key->left == 0)
		config->key->left = 1;
	else if (key == RIGHT && config->key->right == 0)
		config->key->right = 1;
	else if (key == FORWARD && config->key->forward == 0)
		config->key->forward = 1;
	else if (key == BACKWARD && config->key->backward == 0)
		config->key->backward = 1;
	else if (key == CAM_LEFT && config->key->cam_left == 0)
		config->key->cam_left = 1;
	else if (key == CAM_RIGHT && config->key->cam_right == 0)
		config->key->cam_right = 1;
	return (1);
}

int		key_released(int key, t_config *config)
{
	if (key == ESC)
		quit(config, "");
	else if (key == LEFT && config->key->left == 1)
		config->key->left = 0;
	else if (key == RIGHT && config->key->right == 1)
		config->key->right = 0;
	else if (key == FORWARD && config->key->forward == 1)
		config->key->forward = 0;
	else if (key == BACKWARD && config->key->backward == 1)
		config->key->backward = 0;
	else if (key == CAM_LEFT && config->key->cam_left == 1)
		config->key->cam_left = 0;
	else if (key == CAM_RIGHT && config->key->cam_right == 1)
		config->key->cam_right = 0;
	return (1);
}
