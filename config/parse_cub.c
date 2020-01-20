/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_cub.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cmorel-a <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/01/20 12:35:37 by cmorel-a          #+#    #+#             */
/*   Updated: 2020/01/20 16:30:41 by cmorel-a         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../cub3d.h"

int		read_cub(const char *cub, t_config *config)
{
	int		fd;
	int		height_map;
	char	*line;

	height_map = 0;
	if ((fd = open(cub, O_RDONLY)) == -1)
		return (-1);
	while ((get_next_line(fd, &line)) == 1)
	{
		if (line[0] == '1' || line[0] == ' ')
			height_map++;
		parse_config(line, config);
		free(line);
	}
	if ((get_next_line(fd, &line)) == -1)
		return (-1);
	close(fd);
	if (height_map < 3)
		return (-1);
/*	if ((read_map(cub, config, height_map)) == -1)
		return (-1);*/
	return (1);
}

void	parse_config(char *line, t_config *config)
{
	if (line[0] == 'R')
		resolution(line, config);
	if (line[0] == 'N' && line[1] == 'O')
		texture_path(line, config, 'N', '0');
	if (line[0] == 'S' && line[1] == 'O')
		texture_path(line, config, 'S', 'O');
	if (line[0] == 'W' && line[1] == 'E')
		texture_path(line, config, 'W', 'E');
	if (line[0] == 'E' && line[1] == 'A')
		texture_path(line, config, 'E', 'A');
	if (line[0] == 'S' && line[1] == ' ')
		texture_path(line, config, 'S', ' ');
	if (line[0] == 'F' && line[1] == ' ')
		color(line, config, 'F');
	if (line[0] == 'C' && line[1] == ' ')
		color(line, config, 'C');
}

int		read_map(const char *cub, t_config *config, int height)
{
	int		fd;
	int		res;
	char	*line;

	if (!(config->map->map = (char **)malloc(sizeof(char *) * (height + 1))))
		return (-1);
	if ((fd = open(cub, O_RDONLY)) == -1)
		return (-1);
	while ((get_next_line(fd, &line)) >= 0)
	{
		if (line[0] == '1' || line[0] == ' ')
		{
			if (!(copy_map(line, config, fd)))
				res = -1;
		}
		else
			free(line);
	}
	close(fd);
	if (res == -1)
		return (-1);
	free(line);
	return (1);
}
