/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sprite.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cmorel-a <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/02/20 12:42:07 by cmorel-a          #+#    #+#             */
/*   Updated: 2020/02/26 13:01:52 by cmorel-a         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../cub3d.h"

static void		calcul_sprite_values(t_config *config, t_draw *draw)
{
	double		inv_det;

	draw->sprite_x = config->sprite->x - (config->player->pos_x - 0.5);
	draw->sprite_y = config->sprite->y - (config->player->pos_y - 0.5);
	inv_det = 1.0 / (config->player->plane_x * config->player->dir_y
		- config->player->dir_x * config->player->plane_y);
	draw->mat_x = inv_det * (config->player->dir_y * draw->sprite_x
		- config->player->dir_x * draw->sprite_y);
	draw->mat_y = inv_det * (-config->player->plane_y * draw->sprite_x
		+ config->player->plane_x * draw->sprite_y);
	draw->screen_x = (int)((config->width / 2) * (1 + draw->mat_x
		/ draw->mat_y));
	draw->sprite_height = abs((int)(config->height / draw->mat_y));
	draw->draw_start_y = -draw->sprite_height / 2 + (config->height / 2);
	draw->draw_start_y = (draw->draw_start_y < 0 ? 0 : draw->draw_start_y);
	draw->draw_stop_y = draw->sprite_height / 2 + (config->height / 2);
	if (draw->draw_stop_y >= config->height)
		draw->draw_stop_y = config->height;
	draw->sprite_width = abs((int)(config->height / draw->mat_y));
	draw->draw_start_x = -draw->sprite_width / 2 + draw->screen_x;
	draw->draw_start_x = (draw->draw_start_x < 0 ? 0 : draw->draw_start_x);
	draw->draw_stop_x = draw->sprite_width / 2 + draw->screen_x;
	if (draw->draw_stop_x >= config->width)
		draw->draw_stop_x = config->width;
	draw->stripe = draw->draw_start_x;
}

static void		put_sprite_pixel(t_config *config, t_draw *draw)
{
	int		tmp;
	int		xy_text;
	int		xy_scene;
	int		tex_x;
	int		tex_y;

	tex_x = (int)(config->text[TEX_S]->size_line * (draw->stripe
		- (-draw->sprite_width / 2 + draw->screen_x))
		* config->text[TEX_S]->width / draw->sprite_width)
		/ config->text[TEX_S]->size_line;
	tmp = draw->y * config->text[TEX_S]->size_line
		- config->height * (config->text[TEX_S]->size_line / 2)
		+ draw->sprite_height * config->text[TEX_S]->size_line / 2;
	tex_y = ((tmp * config->text[TEX_S]->height) / draw->sprite_height)
		/ config->text[TEX_S]->size_line;
	xy_text = tex_y * config->text[TEX_S]->size_line + tex_x
		* config->text[TEX_S]->bpp / 8;
	xy_scene = draw->y * config->scene->size_line + draw->stripe
		* config->scene->bpp / 8;
	if ((int)(config->text[TEX_S]->data[xy_text + 3]) != 0)
		return ;
	config->scene->data[xy_scene] = config->text[TEX_S]->data[xy_text];
	config->scene->data[xy_scene + 1] = config->text[TEX_S]->data[xy_text + 1];
	config->scene->data[xy_scene + 2] = config->text[TEX_S]->data[xy_text + 2];
}

static void		draw_sprite(t_config *config, t_ray *ray, t_draw *draw)
{
	calcul_sprite_values(config, draw);
	while (draw->stripe < draw->draw_stop_x)
	{
		if (draw->mat_y > 0 && draw->stripe >= 0 && draw->stripe < config->width
			&& draw->mat_y < ray->dist_buff[draw->stripe])
		{
			draw->y = (draw->draw_start_y == 0 ? 0 : draw->draw_start_y + 1);
			while (draw->y < draw->draw_stop_y)
			{
				put_sprite_pixel(config, draw);
				draw->y++;
			}
		}
		draw->stripe++;
	}
}

void			put_sprite(t_config *config, t_ray *ray)
{
	t_draw		*draw;

	if (!(draw = malloc(sizeof(t_draw))))
		quit(config, "Error\nMalloc draw sprite structure");
	ft_bzero(draw, sizeof(t_draw));
	while (config->sprite)
	{
		draw_sprite(config, ray, draw);
		ft_lstdel_firstnode(config);
	}
	init_sprite(config);
	free(draw);
}
