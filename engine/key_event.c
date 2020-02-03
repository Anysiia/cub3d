/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   key_event.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cmorel-a <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/02/03 15:06:26 by cmorel-a          #+#    #+#             */
/*   Updated: 2020/02/03 15:15:36 by cmorel-a         ###   ########.fr       */
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

int			keyboard_manager(t_config *config)
{
	if (config->keyboard->left == 1)
		move_left(config);
	if (config->keyboard->right == 1)
		move_right(config);
	if (config->keyboard->forward == 1)
		move_forward(config);
	if (config->keyboard->backward == 1)
		move_backward(config);
	if (config->keyboard->cam_left == 1)
		turn_left(config);
	if (config->keyboard->cam_right == 1)
		turn_right(config);
	return (1);
}

int			key_pressed(int key, void *param)
{
	t_config	*config;

	config = (t_config *)param;
	if (key == ESC)
		quit(config, "");
	else if (key == LEFT && config->keyboard->left == 0)
		config->keyboard->left = 1;
	else if (key == RIGHT && config->keyboard->right == 0)
		config->keyboard->right = 1;
	else if (key == FORWARD && config->keyboard->forward == 0)
		config->keyboard->forward = 1;
	else if (key == BACKWARD && config->keyboard->backward == 0)
		config->keyboard->backward = 1;
	else if (key == CAM_LEFT && config->keyboard->cam_left == 0)
		config->keyboard->cam_left = 1;
	else if (key == CAM_RIGHT && config->keyboard->cam_right == 0)
		config->keyboard->cam_right = 1;
	return (1);
}

int			key_released(int key, void *param)
{
	t_config	*config;

	config = (t_config *)param;
	if (key == LEFT && config->keyboard->left == 1)
		config->keyboard->left = 0;
	else if (key == RIGHT && config->keyboard->right == 1)
		config->keyboard->right = 0;
	else if (key == FORWARD && config->keyboard->forward == 1)
		config->keyboard->forward = 0;
	else if (key == BACKWARD && config->keyboard->backward == 1)
		config->keyboard->backward = 0;
	else if (key == CAM_LEFT && config->keyboard->cam_left == 1)
		config->keyboard->cam_left = 0;
	else if (key == CAM_RIGHT && config->keyboard->cam_right == 1)
		config->keyboard->cam_right = 0;
	return (1);
}
