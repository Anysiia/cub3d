/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   texture.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cmorel-a <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/02/11 15:26:41 by cmorel-a          #+#    #+#             */
/*   Updated: 2020/02/11 15:34:43 by cmorel-a         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../cub3d.h"

static t_image	*create_texture(t_config *config, int witch_texture)
{
	t_image		*image;

	if (!(image = malloc(sizeof(t_image))))
		exit_error("Error:\nCannot malloc texture image");
	image->img_ptr = mlx_xpm_file_to_image(config->init,
		config->path_tex[witch_texture], &image->width, &image->height);
	image->data = mlx_get_data_addr(image->img_ptr, &image->bpp,
		&image->size_line, &image->endian);
	return (image);
}

