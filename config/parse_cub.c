/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_cub.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cmorel-a <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/01/20 12:35:37 by cmorel-a          #+#    #+#             */
/*   Updated: 2020/01/20 13:32:14 by cmorel-a         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../cub3d.h"



#include <stdio.h>

int		read_cub(const char *cub, t_config *config)
{
	int		fd;
	int		res;
	int		height_map;
	char	*line;

	height_map = 0;
	if ((fd = open(cub, O_RDONLY)) == -1)
		return (-1);
	while ((get_next_line(fd, &line)) == 1)
	{
		if (line[0] == '1' || line[0] == ' ')
			height_map++;
		res = parse_config(line, config);
		free(line);
		if (res == -1)
			return (-1);
	}
	if ((get_next_line(fd, &line)) == -1)
		return (-1);
	close(fd);
	if (height_map < 3)
		return (-1);
/*	if ((parse_map(cub, config, height_map)) == -1)
		return (-1);*/
	return (1);
}

int		parse_config(char *line, t_config *config)
{
	if (line[0] == 'R')
		return (resolution(line, config));
	if (line[0] == 'N' && line[1] == 'O')
		return (texture_path(line, config, 'N', '0'));
	if (line[0] == 'S' && line[1] == 'O')
		return (texture_path(line, config, 'S', 'O'));
	if (line[0] == 'W' && line[1] == 'E')
		return (texture_path(line, config, 'W', 'E'));
	if (line[0] == 'E' && line[1] == 'A')
		return (texture_path(line, config, 'E', 'A'));
	if (line[0] == 'S' && line[1] == ' ')
		return (texture_path(line, config, 'S', ' '));
	if (line[0] == 'F' && line[1] == ' ')
		return (color(line, config, 'F'));
	if (line[0] == 'C' && line[1] == ' ')
		return (color(line, config, 'C'));
	if (line[0] == '\n')
		return (1);
	return (0);
}
