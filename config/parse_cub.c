/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_cub.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cmorel-a <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/01/22 16:23:45 by cmorel-a          #+#    #+#             */
/*   Updated: 2020/02/26 18:08:29 by cmorel-a         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../cub3d.h"

static char	*clean_string(char *line)
{
	int		len;
	int		i;
	int		j;

	i = 0;
	j = 0;
	len = ft_strlen(line);
	while (line[i])
	{
		if (!(ft_test_set(line[i], " NSEW012")))
			exit_error("Error:\nInvalid character on map");
		if (line[i] == ' ')
			i++;
		else
			line[j++] = line[i++];
	}
	if (line[j - 1] != '1')
		return (NULL);
	while (j < len)
		line[j++] = '\0';
	return (line);
}

static void	line_map_save(char *line, char **map, t_config *config)
{
	char	*clean_map;

	if (config->map->map_found == 1 && config->map->empty_line == 1 && line[0])
		exit_error("Error:\nInvalid map : empty line");
	config->map->map_found = 1;
	if (!(clean_map = clean_string(line)))
		exit_error("Error:\nMap must be close by walls");
	if (!(*map = ft_free_s1_join(*map, clean_map)))
		exit_error("Error:\nMalloc map error");
	if (!(*map = ft_free_s1_join(*map, "\n")))
		exit_error("Error:\nMalloc map error");
}

static void	config_map(char *line, t_config *config, char **map)
{
	if (config->map->map_found == 1 && line[0] != '\0' && line[0] != '1')
		exit_error("Error:\nMap error");
	if (line[0] == 'R')
		resolution(line, config);
	if (ft_test_set(line[0], "NSWE"))
		texture_path(line, config);
	if (line[0] == 'F')
		color(line, config, 'F');
	if (line[0] == 'C')
		color(line, config, 'C');
	if (line[0] == '1')
		line_map_save(line, map, config);
	if ((ft_test_set(line[0], "RNSWESFC1") == 0) && line[0] != '\0')
		exit_error("Error:\nInvalid character on .cub file");
}

char		*map_read_cub(const char *cub, t_config *config)
{
	int		fd;
	char	*line;
	int		res;
	char	*map;

	if ((fd = open(cub, O_RDONLY)) == -1)
		exit_error("Error:\nCannot read .cub file");
	if (!(map = ft_strnew(1)))
		exit_error("Error:\nCannot malloc map string");
	while ((res = get_next_line(fd, &line)) >= 0)
	{
		line = ft_free_strtrim(line, " ");
		if (config->map->map_found == 1 && line[0] == '\0')
			config->map->empty_line = 1;
		config_map(line, config, &map);
		free(line);
		if (res == 0)
			break ;
	}
	if (res == -1)
		exit_error("Error:\nAn error occur when reading .cub file");
	close(fd);
	map_format(config, map);
	return (map);
}
