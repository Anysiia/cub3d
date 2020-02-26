/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   map.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cmorel-a <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/01/30 12:25:52 by cmorel-a          #+#    #+#             */
/*   Updated: 2020/02/26 18:06:04 by cmorel-a         ###   ########.fr       */
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

static int		create_map(t_config *config)
{
	int		i;
	int		j;
	char	**map;

	if (!(map = (char **)malloc(sizeof(char *) * config->map->height + 1)))
		return (0);
	i = 0;
	j = config->map->width + 2;
	while (i < config->map->height + 1)
	{
		if (!(map[i] = (char *)malloc(sizeof(char *) * j)))
		{
			while (--i == 0)
				free(map[i]);
			free(*map);
			return (0);
		}
		ft_bzero(map[i], j);
		i++;
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
		while (str_map[i] != '\n')
		{
			config->map->map[line][c] = str_map[i];
			c++;
			i++;
		}
		if (str_map[i] == '\n')
		{
			i++;
			line++;
			c = 0;
		}
	}
}

int				map_format(t_config *config, char *strmap)
{
	size_map(strmap, config);
	if (config->map->height < 3 || config->map->width < 3
		|| config->map->height > 128 || config->map->width > 128)
	{
		free(strmap);
		exit_error("Error:\nMap is too small");
	}
	if (!create_map(config))
	{
		free(strmap);
		exit_error("Error:\nMalloc map");
	}
	copy_map(config, strmap);
	free(strmap);
	if (!map_validity(config))
		exit_error("Error:\nMap must be close by walls");
	find_player(config);
	return (1);
}
