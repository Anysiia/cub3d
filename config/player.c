/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   player.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cmorel-a <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/01/30 10:26:13 by cmorel-a          #+#    #+#             */
/*   Updated: 2020/02/07 12:40:06 by cmorel-a         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../cub3d.h"

static void		init_player(t_config *config)
{
	if (!(config->player = malloc(sizeof(t_player))))
		exit_error("Error:\nMalloc initialisation player");
	config->player->find = 0;
	config->player->pos_x = 0.0;
	config->player->pos_y = 0.0;
	config->player->dir_x = 0.0;
	config->player->dir_y = -1.0;
	config->player->plane_x = 0.0;
	config->player->plane_y = 0.66;
	config->player->move_speed = 0.11;
	config->player->rotate_speed = 0.11;
}

static	void	set_camera(t_config *config, double pl_x, double pl_y)
{
	config->player->plane_x = pl_x;
	config->player->plane_y = pl_y;
}

static void		set_dir(t_config *config, double dirx, double diry)
{
	config->player->dir_x = dirx;
	config->player->dir_y = diry;
}

static void		set_player(t_config *config, int i, int j, char c)
{
	config->player->pos_x = (double)j + 0.5;
	config->player->pos_y = (double)i + 0.5;
	if (c == 'W')
	{
		set_dir(config, -1, 0);
		set_camera(config, 0, -0.66);
	}
	if (c == 'E')
	{
		set_dir(config, 1, 0);
		set_camera(config, 0, 0.66);
	}
	if (c == 'N')
	{
		set_dir(config, 0, -1);
		set_camera(config, 0.66, 0);
	}
	if (c == 'S')
	{
		set_dir(config, 0, 1);
		set_camera(config, -0.66, 0);
	}
}

void			find_player(t_config *config)
{
	int		i;
	int		j;

	init_player(config);
	i = 0;
	while (i < config->map->height)
	{
		j = 0;
		while (j < config->map->width)
		{
			if (test_set(config->map->map[i][j], "NSEW") == 1)
			{
				if (config->player->find == 1)
					exit_error("Error:\nThere is more than one player on map");
				config->player->find = 1;
				set_player(config, i, j, config->map->map[i][j]);
				config->map->map[i][j] = '0';
			}
			j++;
		}
		i++;
	}
	if (config->player->find != 1)
		exit_error("Error:\nPlayer not found");
}
