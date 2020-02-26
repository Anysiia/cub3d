/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   map_validity.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cmorel-a <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/02/26 18:15:27 by cmorel-a          #+#    #+#             */
/*   Updated: 2020/02/26 18:16:17 by cmorel-a         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../cub3d.h"

static void		only_char_in_line(const char *line, char c)
{
	int		i;

	i = 0;
	while (line[i] != '\0')
	{
		if (line[i] != c)
			exit_error("Error:\nMap must be close by walls");
		i++;
	}
}

static int		verify_smaller_line(t_config *config,
				int line, int len_line, int len_previous_line)
{
	int		i;

	i = len_line--;
	while (i < len_previous_line)
	{
		if (config->map->map[line - 1][i] != '1')
			return (0);
		i++;
	}
	return (1);
}

static int		verify_bigger_line(t_config *config,
				int line, int len_line, int len_previous_line)
{
	int		i;

	i = len_previous_line--;
	while (i < len_line)
	{
		if (config->map->map[line][i] != '1')
			return (0);
		i++;
	}
	return (1);
}

int				map_validity(t_config *config)
{
	int		line;
	int		len_line;
	int		len_pr_line;

	only_char_in_line(config->map->map[0], '1');
	only_char_in_line(config->map->map[config->map->height - 1], '1');
	line = 1;
	while (line < config->map->height - 1)
	{
		len_line = ft_strlen(config->map->map[line]);
		len_pr_line = ft_strlen(config->map->map[line]);
		if (len_line < len_pr_line)
			if (!verify_smaller_line(config, line, len_line, len_pr_line))
				return (0);
		if (len_line > len_pr_line)
			if (!verify_bigger_line(config, line, len_line, len_pr_line))
				return (0);
		line++;
	}
	return (1);
}
