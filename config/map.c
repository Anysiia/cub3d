/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   map.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cmorel-a <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/01/20 15:11:48 by cmorel-a          #+#    #+#             */
/*   Updated: 2020/01/20 15:47:26 by cmorel-a         ###   ########.fr       */
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
		res = check_char_map(line[i]);
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

static int	line_copy(char *line, t_config *config, int index)
{
	char	*s;
	int		i;
	int		len;
	int		j;

	i = -1;
	j = 0;
	len = len_without_space(line);
	if (!(s = (char *)malloc(sizeof(*s) * (len + 1))))
		return (-1);
	while (line[++i])
	{
		if (check_char_map(line[i] == 1))
			s[j++] = s[i];
	}
	s[j] = '\0';
	if (s[j - 1] != '1' || s[0] != '1')
		return (-1);
	config->map->map[index] = s;
	return (1);
}

/*static int	check_top_and_bottom_map(t_config *config)
{
	int		i;
	int		height;

	i = 0;
	while (config->map->map[0][i])
	{
		if (config->map->map[0][i] != '1')
			return (-1);
		i++;
	}
	i = 0;
	height = config->map->height;
	while (config->map->map[height - 1][i])
	{
		if (config->map->map[height - 1][i] != '1')
			return (-1);
		i++;
	}
	i = 0;
	return (1);
}*/

int			copy_map(char *line, t_config *config, int fd)
{
	int		len_line;
	int		ret;

	len_line = 1;
	line_copy(line, config, 0);
	free(line);
	while ((ret = get_next_line(fd, &line)) >= 0)
	{
		if ((line_copy(line, config, len_line)) == -1)
		{
			free(line);
			return (-1);
		}
		free(line);
		len_line++;
		if (ret == 0)
			break;
	}
	config->map->map[len_line][0] = '\0';
	config->map->height = len_line -1;
	return (1);
}
