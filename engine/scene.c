/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   scene.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cmorel-a <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/02/14 10:30:19 by cmorel-a          #+#    #+#             */
/*   Updated: 2020/02/14 14:14:33 by cmorel-a         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../cub3d.h"

static void		put_pixel_to_image(t_image *img, int x, int y, int color)
{
	unsigned char *src;
	unsigned char r;
	unsigned char g;
	unsigned char b;

	src = (unsigned char *)&color;
	r = src[0];
	g = src[1];
	b = src[2];
	img->data[y * img->size_line + x * img->bpp / 8] = r;
	img->data[y * img->size_line + x * img->bpp / 8 + 1] = g;
	img->data[y * img->size_line + x * img->bpp / 8 + 2] = b;
}

static void		color_background(t_config *config)
{
	int		i;
	int		j;

	i = 0;
	while (i < (config->height) / 2)
	{
		j = 0;
		while (j < config->width)
		{
			put_pixel_to_image(config->scene, j, i, config->ceiling);
			j++;
		}
		i++;
	}
	while (i < config->height)
	{
		j = 0;
		while (j < config->width)
		{
			put_pixel_to_image(config->scene, j, i, config->floor);
			j++;
		}
		i++;
	}
}

static void		put_scene(t_config *config)
{
	mlx_clear_window(config->init, config->window);
	mlx_put_image_to_window(config->init, config->window,
		config->scene->img, 0, 0);
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
	color_background(config);
	while (ray->stripe < config->width)
		stripe_caster(config, ray);
//	draw_sprite(ray, config);
	put_scene(config);
	free(ray->img_buff);
	free(ray);
	return (1);
}
