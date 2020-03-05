/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_cub.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cmorel-a <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/01/22 16:23:45 by cmorel-a          #+#    #+#             */
/*   Updated: 2020/03/05 12:45:00 by cmorel-a         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/cub3d.h"

static char		*join_map(char *s1, char const *s2)
{
	int		len;
	int		i;
	char	*str;

	if (!s1 || !s2)
		return (NULL);
	i = ft_strlen(s1);
	len = ft_strlen(s2);
	len += i;
	i = 0;
	if (!(str = (char *)malloc(sizeof(*str) * (len + 2))))
		return (NULL);
	i = -1;
	while (s1[++i])
		str[i] = s1[i];
	len = -1;
	while (s2[++len])
		str[i + len] = s2[len];
	str[i + len] = '\n';
	i++;
	str[i + len] = '\0';
	free(s1);
	return (str);
}

static void		line_map_save(char *line, char **map, t_config *config)
{
	int		width;
	int		i;

	if (config->map->map_found == 1 && config->map->empty_line == 1 && line[0])
		exit_error("Error:\nInvalid map : empty line");
	config->map->map_found = 1;
	i = 0;
	while (line[i])
	{
		if (!(ft_test_set(line[i], " NSEW012")))
			exit_error("Error:\nInvalid character on map");
		i++;
	}
	config->map->height++;
	width = ft_strlen(line);
	if (config->map->height > 128 || width > 128)
		exit_error("Error:\nMap is too big");
	if (width > config->map->width)
		config->map->width = width;
	if (!(*map = join_map(*map, line)))
		exit_error("Error:\nMalloc map error");
}

static void		config_map(char *line, t_config *config, char **map)
{
	if (config->map->map_found == 1 && line[0] != '\0' && line[0] != '1'
		&& line[0] != ' ')
		exit_error("Error:\nInvalid character in map");
	if (line[0] == 'R')
		resolution(line, config);
	if (ft_test_set(line[0], "NSWE"))
		texture_path(line, config);
	if (line[0] == 'F')
		color(line, config, 'F');
	if (line[0] == 'C')
		color(line, config, 'C');
	if (ft_test_set(line[0], "1 "))
		line_map_save(line, map, config);
	if ((ft_test_set(line[0], "RNSWESFC1 ") == 0) && line[0] != '\0')
		exit_error("Error:\nInvalid map or invalid caracter on .cub file");
}

char			*map_read_cub(const char *cub, t_config *config)
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
