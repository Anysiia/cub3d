/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   map2.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cmorel-a <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/01/22 14:52:40 by cmorel-a          #+#    #+#             */
/*   Updated: 2020/01/23 14:23:46 by cmorel-a         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../cub3d.h"

static void		size_map(char *map, t_config *config)
{
	int		i;
	int		height;
	int		width;

	i = 0;
	height = 0;
	width = 0;
	while (map[i++])
	{
		if (map[i] == '\n')
		{
			height++;
			if (config->map->width < width)
				config->map->width = width;
			width = -1;
		}
		width++;
	}
	config->map->height = height;
}

static int		create_map(t_config *config, char *str_map)
{
	int		i;
	int		j;
	char	**map;

	if (!(map = (char **)malloc(sizeof(char *) * config->map->height)))
		free_error(str_map, "Error:\nMalloc map");
	i = 0;
	while (i < config->map->height)
	{
		if (!(map[i] = (char *)malloc(sizeof(char *) * j)))
		{
			while (--i == 0)
				free(map[i]);
			free(*map);
			error_config("Error:\nMalloc map");
		}
		i++;
		ft_bzero(map[i], j);
	}
	config->map->map = map;
	return (1);
}

static void		copy_map(t_config *config, char *str_map)
{
	int		i;
	int		line;
	int		c;

	i = 0;
	line = 0;
	c = 0;
	while (str_map[i])
	{
		while (str_map[i++] != '\n')
		{
			config->map->map[line][c] = str_map[i];
			c++;
		}
		line++;
		c = 0;
	}
}

char			**map(t_config *config, char *strmap)
{
	size_map(strmap, config);
	if (config->map->height < 3 || config->map->width < 3)
		free_error(strmap, "Error:\nInvalid map");
	create_map(config, strmap);
	copy_map(config, strmap);
}
