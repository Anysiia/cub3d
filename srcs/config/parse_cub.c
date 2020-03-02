/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_cub.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cmorel-a <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/01/22 16:23:45 by cmorel-a          #+#    #+#             */
/*   Updated: 2020/02/29 14:04:29 by cmorel-a         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/cub3d.h"

static char	*clean_string(char *line)
{
	char	*clean;
	int		len;
	int		i;
	int		j;

	i = 0;
	j = 0;
	len = ft_strlen(line);
	if (!(clean = (char *)malloc(sizeof(clean) * (len / 2 + 1))))
		exit_error("Error:\nMalloc clean line of map");
	while (line[i])
	{
		if (!(ft_test_set(line[i], " NSEW012")))
			exit_error("Error:\nInvalid character on map");
		if (line[i + 1] != ' ' && line[i + 1] != '\0')
			exit_error("Error:\nElement of map must be separated by one space");
		clean[j] = line[i];
		i += 2;
		j++;
	}
	clean[i] = '\0';
	free(line);
	return (line);
}

static void	line_map_save(char *line, char **map, t_config *config)
{
	char	*clean_map;
	int		width;

	if (config->map->map_found == 1 && config->map->empty_line == 1 && line[0])
		exit_error("Error:\nInvalid map : empty line");
	config->map->map_found = 1;
	if (!(clean_map = clean_string(line)))
		exit_error("Error:\nMap must be close by walls");
	config->map->height++;
	width = ft_strlen(clean_map);
	if (config->map->height > 128 || width > 128)
		exit_error("Error:\nMap is bigger than 128 * 128");
	if (width > config->map->width)
		config->map->width = width;
	if (!(*map = ft_free_s1_join(*map, clean_map)))
		exit_error("Error:\nMalloc map error");
	if (!(*map = ft_free_s1_join(*map, "\n")))
		exit_error("Error:\nMalloc map error");
}

static void	config_map(char *line, t_config *config, char **map)
{
	int		i;

	i = 0;
	if (config->map->map_found == 1 && line[0] != '\0' && line[0] != '1'
		&& line[0] != ' ')
		exit_error("Error:\nInvalid character in map");
	while (line[i] == ' ')
		i++;
	if (ft_test_set(line[i], "RNSWEFC"))
		line = ft_free_strtrim(line, " ");
	if (line[i] == 'R')
		resolution(line, config);
	if (ft_test_set(line[i], "NSWE"))
		texture_path(line, config);
	if (line[i] == 'F')
		color(line, config, 'F');
	if (line[i] == 'C')
		color(line, config, 'C');
	if (line[i] == '1')
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
