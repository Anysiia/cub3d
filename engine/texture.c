/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   texture.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cmorel-a <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/02/11 15:26:41 by cmorel-a          #+#    #+#             */
/*   Updated: 2020/02/13 16:16:20 by cmorel-a         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../cub3d.h"

void	color_background(t_config *config)
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

void	init_scene(t_config *config)
{
	if (!(config->scene = malloc(sizeof(t_image))))
		exit_error("Error:\nMalloc initialisation background");
	config->scene->width = config->width;
	config->scene->height = config->height;
	if (!(config->scene->img = mlx_new_image(config->init, config->scene->width,
			config->scene->height)))
		exit_error("Error:\nMlx_new image failed");
	if (!(config->scene->data = mlx_get_data_addr(config->scene->img,
		&config->scene->bpp, &config->scene->size_line,
		&config->scene->endian)))
		exit_error("Error:\nConvert xmp texture file failed");
}

void	put_scene(t_config *config)
{
	mlx_clear_window(config->init, config->window);
	mlx_put_image_to_window(config->init, config->window,
		config->scene->img, 0, 0);
}
