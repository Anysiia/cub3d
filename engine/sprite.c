/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sprite.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cmorel-a <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/02/20 12:42:07 by cmorel-a          #+#    #+#             */
/*   Updated: 2020/02/22 16:08:42 by cmorel-a         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../cub3d.h"

static void		calcul_sprite_values(t_config *config, t_draw *draw)
{
	double	inv_det;

	draw->sprite_x = config->sprite->x - config->player->pos_x - 0.5;
	draw->sprite_y = config->sprite->y - config->player->pos_y - 0.5;
	inv_det = 1.0 / (config->player->dir_y * config->player->plane_x
		- config->player->dir_x * config->player->plane_y);
	draw->mat_x = inv_det * (config->player->dir_y * draw->sprite_x
		- config->player->dir_x * draw->sprite_y);
	draw->mat_y = inv_det * (- config->player->plane_y * draw->sprite_x
		+ config->player->plane_x * draw->sprite_y);
	draw->screen_x = (config->width / 2) * (1 + draw->mat_x / draw->mat_y);
	draw->sprite_height = fabs(config->height / draw->mat_y);
	draw->draw_start_y = (int)(-draw->sprite_height / 2 + config->height / 2);
	draw->draw_start_y = (draw->draw_start_y < 0 ? 0 : draw->draw_start_y);
	draw->draw_stop_y = (int)(draw->sprite_height / 2 + config->height / 2);
	draw->draw_stop_y = (draw->draw_start_y < (config->height) ?
		draw->draw_stop_y : config->height - 1);
	draw->draw_start_x = (int)(-draw->sprite_width / 2 + draw->screen_x);
	draw->draw_start_x = (draw->draw_start_x < 0 ? 0 : draw->draw_start_x);
	draw->draw_stop_x = (int)(-draw->sprite_width / 2 + draw->screen_x);
	draw->draw_stop_x = (draw->draw_start_y < (config->width) ?
		draw->draw_stop_y : config->width - 1);
	draw->stripe = draw->draw_start_x;
}

static int		pixel_color_is_printable(t_config *config,
				t_image *sprite, t_draw *draw)
{
	int		tmp;
	int		color;

	tmp = draw->y * sprite->size_line
		- config->height * (sprite->size_line / 2)
		+ draw->sprite_height * sprite->size_line / 2;
	draw->tex_y = ((tmp * sprite->height) / draw->sprite_height)
		/ config->text[TEX_S]->size_line;
	color = sprite->data[draw->tex_y * sprite->size_line
		+ draw->tex_x * sprite->bpp / 8]
		+ sprite->data[draw->tex_y * sprite->size_line
		+ draw->tex_x * sprite->bpp / 8 + 1]
		+ sprite->data[draw->tex_y * sprite->size_line
		+ draw->tex_x * sprite->bpp / 8 + 2];
	return (color);
}

static void		put_sprite_pixel(t_config *config, t_draw *draw)
{
	int		color;

	color = pixel_color_is_printable(config, config->text[TEX_S], draw);
	if (color != 0)
	{
		config->scene->data[draw->y * config->scene->size_line + draw->stripe
		* config->scene->bpp / 8] = config->text[TEX_S]->data[draw->tex_y
		* config->text[TEX_S]->size_line + draw->tex_x
		* config->text[TEX_S]->bpp / 8];
		config->scene->data[draw->y * config->scene->size_line + draw->stripe
		* config->scene->bpp / 8 + 1] = config->text[TEX_S]->data[draw->tex_y
		* config->text[TEX_S]->size_line + draw->tex_x
		* config->text[TEX_S]->bpp / 8 + 1];
		config->scene->data[draw->y * config->scene->size_line + draw->stripe
		* config->scene->bpp / 8 + 2] = config->text[TEX_S]->data[draw->tex_y
		* config->text[TEX_S]->size_line + draw->tex_x
		* config->text[TEX_S]->bpp / 8 + 2];
	}
}

static void		draw_sprite(t_config *config, t_ray *ray, t_draw *draw)
{
	calcul_sprite_values(config, draw);
	while (draw->stripe < draw->draw_stop_x)
	{
		draw->tex_x = (int)(config->text[TEX_S]->size_line * (draw->stripe
			- (-draw->sprite_width / 2 + draw->screen_x))
			* config->text[TEX_S]->width / draw->sprite_width)
			/ config->text[TEX_S]->size_line;
		if (draw->mat_y > 0 && draw->stripe > 0 && draw->stripe < config->width
			&& draw->mat_y < ray->dist_buff[draw->stripe])
		{
			draw->y = draw->draw_start_y;
			while (draw->y < draw->draw_stop_y)
			{
				put_sprite_pixel(config, draw);
				draw->y++;
			}
		}
		draw->stripe++;
	}
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
		printf("[%i(x: %d, y:%d) d: %.1lf]	", i, config->sprite->x, config->sprite->y, config->sprite->dist);
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
