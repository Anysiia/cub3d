/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   map.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cmorel-a <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/01/30 12:25:52 by cmorel-a          #+#    #+#             */
/*   Updated: 2020/02/13 09:51:27 by cmorel-a         ###   ########.fr       */
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
		exit_error("Error:\nCannot malloc map");
	i = 0;
	j = config->map->width + 2;
	while (i < config->map->height + 1)
	{
		if (!(map[i] = (char *)malloc(sizeof(char *) * j)))
		{
			while (--i == 0)
				free(map[i]);
			free(*map);
			exit_error("Error:\nCannot malloc map");
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

static void		map_validity(t_config *config)
{
	int		i;
	int		len_line;
	int		len_previous_line;

	only_char_in_line(config->map->map[0], '1');
	i = 1;
	while (i < config->map->height - 1)
	{
		len_previous_line = ft_strlen(config->map->map[i - 1]);
		len_line = len_first_end_one(config->map->map[i]);
		if (len_previous_line < len_line)
			exit_error("Error:\nMap must be close by walls");
		if (len_previous_line > len_line)
		{
			len_line--;
			while (len_line < len_previous_line)
			{
				if (config->map->map[i - 1][len_line] != '1')
					exit_error("Error:\nMap must be close by walls");
				len_line++;
			}
		}
		i++;
	}
	check_last_line(config);
}

int				map_format(t_config *config, char *strmap)
{
	size_map(strmap, config);
	if (config->map->height < 3 || config->map->width < 3)
		exit_error("Error:\nMap is too small");
	if (config->map->height > 256 || config->map->width > 256)
		exit_error("Error:\nMap is too big");
	create_map(config);
	copy_map(config, strmap);
	free(strmap);
	map_validity(config);
	find_player(config);
	return (1);
}
