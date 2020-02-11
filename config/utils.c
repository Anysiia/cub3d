/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cmorel-a <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/01/20 16:24:58 by cmorel-a          #+#    #+#             */
/*   Updated: 2020/02/11 11:34:38 by cmorel-a         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../cub3d.h"

int		len_first_end_one(const char *str)
{
	int		i;

	i = ft_strlen(str) - 1;
	while (i > 0 && str[i] == '1')
		i--;
	if (str[i] != '1')
		i += 1;
	i += 1;
	return (i);
}

void	only_char_in_line(const char *line, char c)
{
	int		i;

	i = 0;
	while (line[i] != '\0')
	{
		if (line[i] != c)
			exit_error("Error:\nMap must be close by walls");
		i++;
	}
}

void	check_last_line(t_config *config)
{
	int		len;
	int		len_previous;
	char	*line;
	char	*previous_line;

	line = config->map->map[config->map->height - 1];
	previous_line = config->map->map[config->map->height - 2];
	only_char_in_line(line, '1');
	len = ft_strlen(line);
	len_previous = len_first_end_one(previous_line);
	if (len < len_previous)
		exit_error("Error:\nMap must be close by walls");
}
