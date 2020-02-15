/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   save_bitmap.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cmorel-a <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/02/15 06:17:33 by cmorel-a          #+#    #+#             */
/*   Updated: 2020/02/15 11:04:18 by cmorel-a         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../cub3d.h"

static void	dib_header(t_image *scene, int fd)
{
	int		dib_size;
	int		plane;
	int		full;
	int		i;

	dib_size = 40;
	plane = 1;
	write(fd, &dib_size, 4);
	write(fd, &scene->width, 4);
	write(fd, &scene->height, 4);
	write(fd, &plane, 2);
	write(fd, &scene->bpp, 2);
	full = 28;
	i = 0; 
	while (i++ < full)
		write(fd, "\0", 1);
}

static void	reverse_into_line(t_image *scene, int line, int *pix, int end)
{
	char	tmp;
	int		i;

	i = 3;
	while (i >= 0)
	{
		tmp = scene->data[*pix + (line * scene->size_line)];
		scene->data[*pix + (line * scene->size_line)] =
			scene->data[end - i + (line * scene->size_line - 1)];
		scene->data[end - i + (line * scene->size_line - 1)] = tmp;
		i--;
		*pix = *pix + 1;
	}
}

static int	reverse_line(t_image *scene)
{
	int		line;
	int		pix;
	int		end;

	line = 0;
	while (line < scene->height)
	{
		pix = 0;
		end = scene->size_line;
		while (pix < end && pix != end)
		{
			reverse_into_line(scene, line, &pix, end);
			end -= 4;
		}
		line++;
	}
	return (1);
}

static int	copy_data_to_bitmap(t_image *scene, int fd)
{
	int		i;

	i = scene->width * scene->height - 1;
	while (i >= 0)
	{
		write(fd, &scene->data[i * scene->bpp / 8], 4);
		i--;
	}
	return (1);
}

int			save_bitmap(t_config *config, t_ray *ray)
{
	int		fd;
	int		size_file;
	int		first_pix;

	if (!(fd = open("cub3d.bmp", O_CREAT | O_RDWR, S_IRWXU)))
		quit(config, "Error:\nCannot create bitmap file");
	first_pix = 14 + 40 + 4;
	size_file = first_pix + (config->scene->width * config->scene->height) * 4;
	write(fd, "BM", 2);
	write(fd, &size_file, 4);
	write(fd, "\0\0\0\0", 4);
	write(fd, &first_pix, 4);
	dib_header(config->scene, fd);
	reverse_line(config->scene);
	copy_data_to_bitmap(config->scene, fd);
	close(fd);
	free(ray->img_buff);
	free(ray);
	quit(config, "Bitmap file created, name : cub3d.bmp");
	return (1);
}
