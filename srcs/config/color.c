/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   color.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cmorel-a <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/01/20 12:37:30 by cmorel-a          #+#    #+#             */
/*   Updated: 2020/03/05 13:44:19 by cmorel-a         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/cub3d.h"

static int	check_color_line(char *str, char c)
{
	int		i;
	int		j;

	if (!str || str[0] != c || str[1] != ' ')
		return (0);
	i = 1;
	j = 0;
	while (j < 3)
	{
		while (str[i] == ' ')
			i++;
		if (!(ft_isdigit(str[i])))
			return (0);
		while (ft_isdigit(str[i]))
			i++;
		if (j < 2 && str[i++] != ',')
			return (0);
		while (j == 2 && str[i] == ' ')
			i++;
		if (j == 2 && str[i] != '\0')
			return (0);
		j++;
	}
	return (1);
}

static int	one_color(char *line, int *i)
{
	int		color;

	color = 0;
	while (line[*i] == ' ')
		*i += 1;
	while (line[*i] >= '0' && line[*i] <= '9')
	{
		color = color * 10 + (line[*i] - 48);
		if (color > 255)
			exit_error("Error:\nComponent of color must be between 0 and 255");
		*i += 1;
	}
	*i += 1;
	return (color);
}

static int	rgb_color(int r, int g, int b)
{
	int		rgb;

	rgb = r;
	rgb = (rgb << 8) + g;
	rgb = (rgb << 8) + b;
	return (rgb);
}

void		color(char *line, t_config *config, char c)
{
	int	i;
	int	r;
	int	g;
	int	b;

	i = 1;
	if (c == 'F')
		if (config->floor != -1)
			exit_error("Error:\nMore than one floor color");
	if (c == 'C')
		if (config->ceiling != -1)
			exit_error("Error:\nMore than one ceiling color");
	if (!check_color_line(line, c))
		exit_error("Error:\nWrong format color");
	r = one_color(line, &i);
	g = one_color(line, &i);
	b = one_color(line, &i);
	if (c == 'F')
		config->floor = rgb_color(r, g, b);
	if (c == 'C')
		config->ceiling = rgb_color(r, g, b);
}
