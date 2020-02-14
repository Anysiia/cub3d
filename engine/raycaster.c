/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   raycaster.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cmorel-a <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/01/31 11:49:59 by cmorel-a          #+#    #+#             */
/*   Updated: 2020/02/14 12:57:27 by cmorel-a         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../cub3d.h"

static void		ray_values(t_config *config, t_ray *ray, t_player *player)
{
	ray->cam = (2 * ray->stripe) / (double)config->width - 1;
	ray->ray_dir_x = player->dir_x + player->plane_x * ray->cam;
	ray->ray_dir_y = player->dir_y + player->plane_y * ray->cam;
	ray->map_x = (int)player->pos_x;
	ray->map_y = (int)player->pos_y;
	ray->delta_x = fabs(1 / ray->ray_dir_x);
	ray->delta_y = fabs(1 / ray->ray_dir_y);
	ray->hit = 0;
}

static void		step(t_ray *ray, t_player *player)
{
	if (ray->ray_dir_x < 0)
	{
		ray->step_x = -1;
		ray->side_dist_x = (player->pos_x - ray->map_x) * ray->delta_x;
	}
	else
	{
		ray->step_x = 1;
		ray->side_dist_x = (ray->map_x + 1.0 - player->pos_x) * ray->delta_x;
	}
	if (ray->ray_dir_y < 0)
	{
		ray->step_y = -1;
		ray->side_dist_y = (player->pos_y - ray->map_y) * ray->delta_y;
	}
	else
	{
		ray->step_y = 1;
		ray->side_dist_y = (ray->map_y + 1.0 - player->pos_y) * ray->delta_y;
	}
}

static void		side(t_ray *ray, t_config *config)
{
	while (ray->hit == 0)
	{
		if (ray->side_dist_x < ray->side_dist_y)
		{
			ray->side_dist_x += ray->delta_x;
			ray->map_x += ray->step_x;
			if (ray->step_x == 1)
				ray->side = TEX_NO;
			else if (ray->step_x == -1)
				ray->side = TEX_SO;
		}
		else
		{
			ray->side_dist_y += ray->delta_y;
			ray->map_y += ray->step_y;
			if (ray->step_y == 1)
				ray->side = TEX_WE;
			else if (ray->step_y == -1)
				ray->side = TEX_EA;
		}
		if (config->map->map[ray->map_y][ray->map_x] == '1')
			ray->hit = 1;
/*		else if (config->map->map[ray->map_x][ray->map_y] == '2')
			detect_sprite(ray, config);*/
	}
}

static void		dist_and_height(t_ray *ray, t_player *player, t_config *config)
{
	if (ray->side == TEX_NO || ray->side == TEX_SO)
		ray->distance = (ray->map_x - player->pos_x + (1 - ray->step_x) / 2)
		/ ray->ray_dir_x;
	else
		ray->distance = (ray->map_y - player->pos_y + (1 - ray->step_y) / 2)
		/ ray->ray_dir_y;
	ray->line_height = (int)(config->height / ray->distance);
	ray->draw_start = (-ray->line_height / 2) + (config->height / 2);
	if (ray->draw_start < 0)
		ray->draw_start = 0;
	ray->draw_stop = (ray->line_height / 2) + (config->height / 2);
	if (ray->draw_stop >= config->height)
		ray->draw_stop = config->height - 1;
}

void		stripe_caster(t_config *config, t_ray *ray)
{
	t_player	*player;

	player = config->player;
	ray_values(config, ray, player);
	step(ray, player);
	side(ray, config);
	dist_and_height(ray, player, config);
	ray->img_buff[ray->stripe] = ray->distance;
	put_texture(config, ray);
	ray->stripe++;
}
