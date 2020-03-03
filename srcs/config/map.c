/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   map.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cmorel-a <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/01/30 12:25:52 by cmorel-a          #+#    #+#             */
/*   Updated: 2020/02/29 14:01:57 by cmorel-a         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/cub3d.h"

static int		create_map(t_config *config)
{
	int		i;
	int		j;
	char	**map;

	if (!(map = (char **)malloc(sizeof(char *) * config->map->height + 1)))
		return (0);
	i = 0;
	j = config->map->width + 1;
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

static void		space_to_zero(t_config *config)
{
	int		line;
	int		row;

	line = 0;
	while (line < config->map->height)
	{
		row = 0;
		while (row < config->map->width)
		{
			if (config->map->map[line][row] == ' ')
				config->map->map[line][row] = '0';
			row++;
		}
		line++;
	}
}

static int		map_validity(t_config *config)
{
	int		line;
	int		row;

	line = 1;
	while (line < config->map->height)
	{
		if (!check_line(config, line))
			return (0);
		line++;
	}
	row = 1;
	while (row < config->map-> height)
	{
		if (!check_row(config, row))
			return (0);
		row++;
	}
	space_to_zero(config);
	return (1);
}

int				map_format(t_config *config, char *strmap)
{
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
