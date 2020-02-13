/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   raycaster.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cmorel-a <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/01/31 11:49:59 by cmorel-a          #+#    #+#             */
/*   Updated: 2020/02/13 14:14:52 by cmorel-a         ###   ########.fr       */
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

static void		colorisation(t_config *config, t_ray *ray)
{
	int		i;

	i = ray->draw_start;
	while (i < ray->draw_stop)
	{
		if (ray->side == 0)
			mlx_pixel_put(config->init, config->window, ray->stripe, i, 16711680);
		if (ray->side == 1)
			mlx_pixel_put(config->init, config->window, ray->stripe, i, 255);
		if (ray->side == 2)
			mlx_pixel_put(config->init, config->window, ray->stripe, i, 13648805);
		if (ray->side == 3)
			mlx_pixel_put(config->init, config->window, ray->stripe, i, 2788906);
		i++;
	}
}

static void		stripe_caster(t_config *config, t_ray *ray)
{
	t_player	*player;

	player = config->player;
	ray_values(config, ray, player);
	step(ray, player);
	side(ray, config);
	dist_and_height(ray, player, config);
	ray->img_buff[ray->stripe] = ray->distance;
	colorisation(config, ray);
	ray->stripe++;
//	put_texture(ray, config);
}

int				raycaster(t_config *config)
{
	t_ray		*ray;

	if (!(ray = malloc(sizeof(t_ray))))
		return (-1);
	ft_bzero(ray, sizeof(t_ray));
	if (!(ray->img_buff = malloc(sizeof(double) * config->width)))
		return (-1);
	ft_bzero(ray->img_buff, sizeof(double) * config->width);
	put_background(config);
	while (ray->stripe < config->width)
		stripe_caster(config, ray);
//	draw_sprite(ray, config);
	free(ray->img_buff);
	free(ray);
	return (1);
}
