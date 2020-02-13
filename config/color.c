/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   color.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cmorel-a <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/01/20 12:37:30 by cmorel-a          #+#    #+#             */
/*   Updated: 2020/02/13 11:07:37 by cmorel-a         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../cub3d.h"

static int	check_color_line(char *str, char c)
{
	int		i;
	int		j;

	if (!str || str[0] != c)
		return (0);
	i = 1;
	j = 0;
	while (str[i] == ' ')
		i++;
	while (ft_isdigit(str[i]) || str[i] == ',')
	{
		if (str[i] == ',')
			j++;
		i++;
	}
	while (str[i] == ' ')
		i++;
	if (str[i] != '\0')
		return (0);
	if (j != 2)
		return (0);
	return (1);
}

static int	one_color(char *line, int *i)
{
	int		color;

	color = ft_atoi(&line[*i]);
	if (color < 0 || color > 255)
		exit_error("Error:\nComponent color must be between 0 and 255");
	while (ft_isdigit(line[*i]))
		*i += 1;
	*i += 1;
	return (color);
}

static void	check_config_color(t_config *config, char c)
{
	if (c == 'F')
		if (config->floor[0] != -1)
			exit_error("Error:\nMore than one floor color");
	if (c == 'C')
		if (config->ceiling[0] != -1)
			exit_error("Error:\nMore than one ceiling color");
}

void		color(char *line, t_config *config, char c)
{
	int	i;

	i = 1;
	check_config_color(config, c);
	if (!check_color_line(line, c))
		exit_error("Error:\nWrong format color");
	while (line[i] == ' ')
		i++;
	if (c == 'F')
	{
		config->floor[0] = one_color(line, &i);
		config->floor[1] = one_color(line, &i);
		config->floor[2] = one_color(line, &i);
	}
	if (c == 'C')
	{
		config->ceiling[0] = one_color(line, &i);
		config->ceiling[1] = one_color(line, &i);
		config->ceiling[2] = one_color(line, &i);
	}
}
