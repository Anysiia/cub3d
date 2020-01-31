/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils_caster.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cmorel-a <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/01/31 15:26:48 by cmorel-a          #+#    #+#             */
/*   Updated: 2020/01/31 15:26:52 by cmorel-a         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../cub3d.h"

void	side(t_ray *ray, t_config *config)
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
		if (config->map->map[ray->map_x][ray->map_y] == '1')
			ray->hit = 1;
/*		else if (config->map->map[ray->map_x][ray->map_y] == '2')
			detect_sprite(ray, config);*/
	}
}

void	dist_and_height(t_ray *ray, t_player *player, t_config *config)
{
	if (ray->side == TEX_NO || ray->side == TEX_SO)
		ray->distance = (ray->map_x - player->pos_x 
		+ (1 - ray->step_x) / 2) / ray->ray_dir_x;
	else
		ray->distance = (ray->map_y - player->pos_y
		+ (1 - ray->step_y) / 2) / ray->ray_dir_y;
	ray->line_height = (int)(config->height / ray->distance);
	ray->draw_start = (-ray->line_height / 2) + (config->height / 2);
	if (ray->draw_start < 0)
		ray->draw_start = 0;
	ray->draw_stop = (ray->line_height / 2) + (config->height / 2);
	if (ray->draw_stop >= config->height)
		ray->draw_stop = config->height - 1;
}
