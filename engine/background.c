/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   background.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cmorel-a <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/02/13 11:27:59 by cmorel-a          #+#    #+#             */
/*   Updated: 2020/02/13 14:19:21 by cmorel-a         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../cub3d.h"

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
			put_pixel_to_image(config->background, j, i, config->ceiling);
			j++;
		}
		i++;
	}
	while (i < config->height)
	{
		j = 0;
		while (j < config->width)
		{
			put_pixel_to_image(config->background, j, i, config->floor);
			j++;
		}
		i++;
	}
}

void			init_background(t_config *config)
{
	if (!(config->background = malloc(sizeof(t_image))))
		exit_error("Error:\nMalloc initialisation background");
	if (!(config->background->img = mlx_new_image(config->init, config->width,
			config->height)))
		exit_error("Error:\nMlx_new image failed");
	if (!(config->background->data = mlx_get_data_addr(config->background->img,
		&config->background->bpp, &config->background->size_line,
		&config->background->endian)))
		exit_error("Error:\nConvert xmp texture file failed");
}

void			put_background(t_config *config)
{
	color_background(config);
	mlx_put_image_to_window(config->init, config->window, 
		config->background->img, 0, 0);
}

void			put_pixel_to_image(t_image *img, int x, int y, int color)
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
