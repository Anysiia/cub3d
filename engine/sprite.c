/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sprite.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cmorel-a <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/02/20 12:42:07 by cmorel-a          #+#    #+#             */
/*   Updated: 2020/02/21 12:12:41 by cmorel-a         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../cub3d.h"

static void		calcul_sprite_values(t_config *config, t_draw *draw)
{
	double	inv_det;
	double	mat_x;
	double	mat_y;
	double	sprite_screen_x;

	draw->sprite_x = config->sprite->x - config->player->pos_x - 0.5;
	draw->sprite_y = config->sprite->y - config->player->pos_y - 0.5;
	inv_det = 1.0 / (config->player->dir_y * config->player->plane_x
		- config->player->dir_x * config->player->plane_y);
	mat_x = inv_det * (config->player->dir_y * draw->sprite_x
		- config->player->dir_x * draw->sprite_y);
	mat_y = inv_det * (- config->player->plane_y * draw->sprite_x
		+ config->player->plane_x * draw->sprite_y);
	sprite_screen_x = (config->width / 2) * (1 + mat_x / mat_y);
	draw->sprite_height = fabs(config->height / mat_y);
	draw->draw_start_y = (int)(-draw->sprite_height / 2 + config->height / 2);
	draw->draw_start_y = (draw->draw_start_y < 0 ? 0 : draw->draw_start_y);
	draw->draw_stop_y = (int)(draw->sprite_height / 2 + config->height / 2);
	draw->draw_stop_y = (draw->draw_start_y < (config->height) ?
		draw->draw_stop_y : config->height - 1);
	draw->draw_start_x = (int)(-draw->sprite_width / 2 + sprite_screen_x);
	draw->draw_start_x = (draw->draw_start_x < 0 ? 0 : draw->draw_start_x);
	draw->draw_stop_x = (int)(-draw->sprite_width / 2 + sprite_screen_x);
	draw->draw_stop_x = (draw->draw_start_y < (config->width) ?
		draw->draw_stop_y : config->width - 1);
}

static void		draw_sprite(t_config *config, t_ray *ray, t_draw *draw)
{
	int		x;

	calcul_sprite_values(config, draw);
	draw->stripe = draw->draw_start_x;

	x = ray->hit;
}






#include <stdio.h>

void		printlist(t_config *config)
{
	int		i;
	t_list	*top;

	i = 0;
	top = config->sprite;
	while (config->sprite)
	{
		printf("Chainon: %i, x: %d, y:%d, dist: %lf	", i, config->sprite->x, config->sprite->y, config->sprite->dist);
		config->sprite = config->sprite->next;
		i++;
	}
	config->sprite = top;
}

void			put_sprite(t_config *config, t_ray *ray)
{
	t_draw		*draw;

	if (!(draw = malloc(sizeof(t_draw))))
		quit(config, "Error\nMalloc draw sprite structure");
	ft_bzero(draw, sizeof(t_draw));
	printlist(config);
	draw_sprite(config, ray, draw);
/*	while (config->sprite->next)
	{
		draw_sprite(config, ray, draw);
		ft_lstdel_firstnode(config);
	}
	draw_sprite(config, ray, draw);
	config->sprite->x = -1;
	config->sprite->y = -1;
	config->sprite->dist = -1;
	config->sprite->next = NULL;
	free(draw);*/
}
