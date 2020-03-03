/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   map_validity.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cmorel-a <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/02/26 18:15:27 by cmorel-a          #+#    #+#             */
/*   Updated: 2020/02/27 14:02:51 by cmorel-a         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/cub3d.h"

static size_t	index_last_one_in_line(const char *line)
{
	size_t	i;

	i = ft_strlen(line);
	i--;
	while (line[i] == ' ')
		i--;
	if (line[i] != '1')
		exit_error("Error:\nMap must be close by walls");
	return (i);
}

static size_t	index_first_one_in_line(const char *line)
{
	size_t	i;

	i = 0;
	while (line[i] && line[i] == ' ')
		i++;
	if (line[i] != '1')
		exit_error("Error:\nMap must be close by walls");
	return (i);
}

static int		previous_line(t_config *config, int line, int start, int end)
{
	int		i;

	i = start;
	while (i <= end)
	{
		if (config->map->map[line - 1][i] != '1')
			return (0);
		i++;
	}
	return (1);
}

static int		actual_line(t_config *config, int line, int start, int end)
{
	int		i;

	i = start;
	while (i <= end)
	{
		if (config->map->map[line][i] != '1')
			return (0);
		i++;
	}
	return (1);
}

int				check_line(t_config *config, int line)
{
	int		end_line;
	int		end_pr_line;
	int		start_line;
	int		start_pr_line;

	start_line = index_first_one_in_line(config->map->map[line]);
	start_pr_line = index_first_one_in_line(config->map->map[line - 1]);
	if (start_line < start_pr_line)
		if (!actual_line(config, line, start_line, start_pr_line))
			return (0);
	if (start_line > start_pr_line)
		if (!previous_line(config, line, start_pr_line, start_line))
			return (0);
	end_line = index_last_one_in_line(config->map->map[line]);
	end_pr_line = index_last_one_in_line(config->map->map[line - 1]);
	if (end_line < end_pr_line)
		if (!previous_line(config, line, end_line, end_pr_line))
			return (0);
	if (end_line > end_pr_line)
		if (!actual_line(config, line, end_pr_line, end_line))
			return (0);
	return (1);
}
