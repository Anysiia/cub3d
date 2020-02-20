/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sprite.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cmorel-a <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/02/20 12:42:07 by cmorel-a          #+#    #+#             */
/*   Updated: 2020/02/20 14:46:26 by cmorel-a         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../cub3d.h"

static void		calcul_sprite_values(t_config *config, t_draw *draw)
{
	double	inv_det;
	double	mat_x;
	double	mat_y;
	int		sprite_screen_x;

	inv_det = 1.0 / (config->player->dir_y * config->player->plane_x
		- config->player->dir_x * config->player->plane_y);
	mat_x = inv_det * (config->player->dir_y * draw->sprite_x
		- config->player->dir_x * draw->sprite_y);
	mat_y = inv_det * (- config->player->plane_y * draw->sprite_x
		+ config->player->plane_x * draw->sprite_y);
	sprite_screen_x = (int)((config->width / 2) * (1 + mat_x / mat_y));
	draw->sprite_height = abs((int)(config->height / mat_y));
	draw->draw_start_y = -draw->sprite_height / 2 + config->height / 2;
	draw->draw_start_y = (draw->draw_start_y < 0 ? 0 : draw->draw_start_y);
	draw->draw_stop_y = draw->sprite_height / 2 + config->height / 2;
	draw->draw_stop_y = (draw->draw_start_y < (config->height) ?
		draw->draw_stop_y : config->height - 1);
	draw->draw_start_x = -draw->sprite_width / 2 + sprite_screen_x;
	draw->draw_start_x = (draw->draw_start_x < 0 ? 0 : draw->draw_start_x);
	draw->draw_stop_x = -draw->sprite_width / 2 + sprite_screen_x;
	draw->draw_stop_x = (draw->draw_start_y < (config->width) ?
		draw->draw_stop_y : config->width - 1);
	draw->stripe = draw->draw_start_x;
}

static void		draw_sprite(t_config *config, t_ray *ray, t_draw *draw)
{
	draw->sprite_x = config->sprite->x - config->player->pos_x - 0.5;
	draw->sprite_y = config->sprite->y - config->player->pos_y - 0.5;
	calcul_sprite_values(config, draw);
}

void			put_sprite(t_config *config, t_ray *ray)
{
	t_draw		*draw;

	if (!(draw = malloc(sizeof(t_draw))))
		quit(config, "Error\nMalloc draw sprite structure");
	ft_bzero(draw, sizeof(t_draw));
	sort_dist_sprite(config);
	while (config->sprite->next)
	{
		draw_sprite(config, ray, draw);
		ft_lstdel_firstnode(config);
	}
	free(draw);
}

