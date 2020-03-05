/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   map_validity.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cmorel-a <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/02/26 18:15:27 by cmorel-a          #+#    #+#             */
/*   Updated: 2020/03/05 11:12:25 by cmorel-a         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/cub3d.h"

static int		check_first_end_line(const char *line)
{
	int		i;

	i = 0;
	while (line[i] != '\0')
	{
		if (line[i] != '1' && line[i] != ' ')
			return (0);
		i++;
	}
	return (1);
}

static int		check_first_row(t_config *config)
{
	int		i;

	i = 0;
	while (i < config->map->height)
	{
		if (config->map->map[i][0] != '1' && config->map->map[i][0] != ' ')
			return (0);
		i++;
	}
	return (1);
}

static int		check_char_around(t_config *config, int line, int row)
{
	if (!(ft_test_set(config->map->map[line - 1][row], "012NSWE"))
		|| !(ft_test_set(config->map->map[line + 1][row], "012NSWE"))
		|| !(ft_test_set(config->map->map[line][row - 1], "012NSWE"))
		|| !(ft_test_set(config->map->map[line][row + 1], "012NSWE")))
		return (0);
	return (1);
}

int				map_validity(t_config *config)
{
	int		line;
	int		row;

	if (!(check_first_end_line(config->map->map[0]))
		|| !(check_first_end_line(config->map->map[config->map->height - 1]))
		|| !(check_first_row(config)))
		return (0);
	line = 1;
	while (line < config->map->height - 1)
	{
		row = 1;
		while (row < config->map->width)
		{
			if (ft_test_set(config->map->map[line][row], "02NSWE"))
				if (!check_char_around(config, line, row))
					exit_error("Error:\nMap must be close by walls");
			row++;
		}
		line++;
	}
	return (1);
}
