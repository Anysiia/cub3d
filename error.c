/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   error.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cmorel-a <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/01/23 11:26:15 by cmorel-a          #+#    #+#             */
/*   Updated: 2020/01/23 11:28:06 by cmorel-a         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

void	error_config(const char *msg)
{
	if (msg)
		write(1, msg, ft_strlen(msg));
	write(1, "\n", 1);
	exit(0);
}

void	free_error(char *line, const char *msg)
{
	if (msg)
		write(1, msg, ft_strlen(msg));
	write(1, "\n", 1);
	free(line);
	exit(0);
}

void	free_line_map_error(char *line, char *map, const char *msg)
{
	if (msg)
		write(1, msg, ft_strlen(msg));
	write(1, "\n", 1);
	free(line);
	free(map);
	exit(0);
}
