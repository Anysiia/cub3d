/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   key_management.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cmorel-a <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/03/05 14:55:00 by cmorel-a          #+#    #+#             */
/*   Updated: 2020/03/05 15:19:28 by cmorel-a         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/cub3d.h"

static void		keyboard_manager(t_config *config)
{
	if (config->key->left == 1)
		move_left(config);
	if (config->key->right == 1)
		move_right(config);
	if (config->key->forward == 1)
		move_forward(config);
	if (config->key->backward == 1)
		move_backward(config);
	if (config->key->cam_left == 1)
		turn_left(config);
	if (config->key->cam_right == 1)
		turn_right(config);
}

void			init_key(t_config *config)
{
	if (!(config->key = malloc(sizeof(t_keyboard))))
		exit_error("Error:\nMalloc initialisation keyboard");
	config->key->backward = 0;
	config->key->forward = 0;
	config->key->left = 0;
	config->key->right = 0;
	config->key->cam_left = 0;
	config->key->cam_right = 0;
}

int				loop(t_config *config)
{
	if (!raycaster(config))
		quit(config, "Error:\nRaycasting error");
	keyboard_manager(config);
	return (1);
}

int				leave_window(t_config *config)
{
	mlx_destroy_window(config->init, config->window);
	exit(0);
}
