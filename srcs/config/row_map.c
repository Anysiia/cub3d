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

static size_t	index_last_one_in_row(t_config *config, int row)
{
	size_t	i;

	i = 0;

	while (i <config->map->height)
		if (config->map->map[i][row])
			i++;
	i--;
	while (config->map->map[i][row] == ' ')
		i--;
	if (config->map->map[i][row] != '1')
		exit_error("Error:\nMap must be close by walls");
	return (i);
}

static size_t	index_first_one_in_row(t_config *config, int row)
{
	size_t	i;

	i = 0;
	while (config->map->map[i][row] && config->map->map[i][row] == ' ')
		i++;
	if (config->map->map[i][row] != '1')
		exit_error("Error:\nMap must be close by walls");
	return (i);
}

static int		previous_row(t_config *config, int row, int start, int end)
{
	int		i;

	i = start;
	while (i <= end)
	{
		if (config->map->map[i][row - 1] != '1')
			return (0);
		i++;
	}
	return (1);
}

static int		actual_row(t_config *config, int row, int start, int end)
{
	int		i;

	i = start;
	while (i <= end)
	{
		if (config->map->map[i][row] != '1')
			return (0);
		i++;
	}
	return (1);
}

int				check_row(t_config *config, int row)
{
	int		end_row;
	int		end_pr_row;
	int		start_row;
	int		start_pr_row;

	start_row = index_first_one_in_row(config, row);
	start_pr_row = index_first_one_in_row(config, row - 1);
	if (start_row > start_pr_row)
		if (!previous_row(config, row, start_pr_row, start_row))
			return (0);
	if (start_row < start_pr_row)
		if (!actual_row(config, row, start_row, start_pr_row))
			return (0);
	end_row = index_last_one_in_row(config, row);
	end_pr_row = index_last_one_in_row(config, row - 1);
	if (end_row < end_pr_row)
		if (!previous_row(config, row, end_row, end_pr_row))
			return (0);
	if (end_row > end_pr_row)
		if (!actual_row(config, row, end_pr_row, end_row))
			return (0);
	return (1);
}
