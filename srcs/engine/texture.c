/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   texture.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cmorel-a <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/02/14 10:34:58 by cmorel-a          #+#    #+#             */
/*   Updated: 2020/02/27 14:05:57 by cmorel-a         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/cub3d.h"

static void		pixel_texturisation(t_config *config, t_ray *ray,
	t_image *text, t_stripe *stripe)
{
	double	tmp;

	tmp = stripe->y * text->size_line - config->height * text->size_line / 2
		+ ray->line_height * text->size_line / 2;
	stripe->text_y = ((tmp * text->height) / ray->line_height)
		/ text->size_line;
	config->scene->data[(int)(stripe->y * config->scene->size_line + stripe->x
		* config->scene->bpp / 8)] = text->data[(int)(stripe->text_y
		* text->size_line + stripe->text_x * (text->bpp / 8))];
	config->scene->data[(int)(stripe->y * config->scene->size_line + stripe->x
		* config->scene->bpp / 8 + 1)] = text->data[(int)(stripe->text_y
		* text->size_line + stripe->text_x * (text->bpp / 8) + 1)];
	config->scene->data[(int)(stripe->y * config->scene->size_line + stripe->x
		* config->scene->bpp / 8 + 2)] = text->data[(int)(stripe->text_y
		* text->size_line + stripe->text_x * (text->bpp / 8) + 2)];
}

static void		put_texture_on_scene(t_config *config, t_ray *ray,
	t_stripe *stripe, double wall_x)
{
	t_image		*texture;

	if (ray->side == TEX_WE)
		texture = config->text[TEX_WE];
	if (ray->side == TEX_EA)
		texture = config->text[TEX_EA];
	if (ray->side == TEX_NO)
		texture = config->text[TEX_NO];
	if (ray->side == TEX_SO)
		texture = config->text[TEX_SO];
	stripe->y = stripe->start;
	stripe->text_x = wall_x * (double)texture->width;
	while (stripe->y < stripe->stop)
	{
		pixel_texturisation(config, ray, texture, stripe);
		stripe->y++;
	}
}

void			put_texture(t_config *config, t_ray *ray)
{
	t_stripe	*stripe;
	double		wall_x;

	if (!(stripe = malloc(sizeof(t_stripe))))
		quit(config, "Error:\nMalloc stripe texture");
	ft_bzero(stripe, sizeof(t_stripe));
	if (ray->side == TEX_WE || ray->side == TEX_EA)
		wall_x = config->player->pos_x + ray->distance * ray->ray_dir_x;
	else
		wall_x = config->player->pos_y + ray->distance * ray->ray_dir_y;
	wall_x -= floor(wall_x);
	stripe->x = ray->stripe;
	stripe->start = ray->draw_start;
	stripe->stop = ray->draw_stop;
	if (config->map->map[ray->map_y][ray->map_x] == '1')
		put_texture_on_scene(config, ray, stripe, wall_x);
	free(stripe);
}
