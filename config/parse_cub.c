/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_cub.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cmorel-a <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/01/22 16:23:45 by cmorel-a          #+#    #+#             */
/*   Updated: 2020/01/30 12:38:11 by cmorel-a         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../cub3d.h"

static int	len_without_space(char *line)
{
	int		i;
	int		len;
	int		res;

	i = 0;
	len = 0;
	while (line && line[i])
	{
		if (line[i] == ' ')
			i++;
		res = test_set(line[i], "NSEW012");
		if (res == 1)
		{
			len++;
			i++;
		}
		if (res == 0)
			return (-1);
	}
	return (len);
}

static char	*clean_string(char *line)
{
	char	*s;
	int		len;
	int		i;
	int		j;

	i = 0;
	j = 0;
	len = len_without_space(line);
	if (!(s = (char *)malloc(sizeof(*s) * (len + 1))))
		return (NULL);
	while (line[i])
	{
		if (test_set(line[i], "NSWE012"))
			s[j++] = line[i++];
		else
			i++;
	}
	if (s[j - 1] != '1')
		return (NULL);
	s[j] = '\0';
	return (s);
}

static void	line_map_save(char *line, char **map, t_config *config)
{
	char	*clean_map;
	int		len_map;

	config->map_found = 1;
	if ((len_map = len_without_space(line)) == -1)
		exit_error("Error:\nInvalid character on map");
	if (!(clean_map = clean_string(line)))
		exit_error("Error:\nMap must be close by walls");
	if (!(*map = ft_free_s1_join(*map, clean_map)))
		exit_error("Error:\nMalloc map error");
	free(clean_map);
	if (!(*map = ft_free_s1_join(*map, "\n")))
		exit_error("Error:\nMalloc map error");
}

static void	config_map(char *line, t_config *config, char **map)
{
	if (config->map_found == 1 && line[0] != '\0' && line[0] != '1'
			&& line[1] != ' ')
		exit_error("Error:\nMap error");
	if (config->map_found == 1 && config->empty_line == 1 &&
			(line[0] == '1' || line[0] == ' '))
		exit_error("Error:\nInvalid map : empty line");
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
	if (line[0] == '1' || line[0] == ' ')
		line_map_save(line, map, config);
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
		if (config->map_found == 1 && line[0] == '\0')
			config->empty_line = 1;
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
