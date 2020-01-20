/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   color.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cmorel-a <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/01/20 12:37:30 by cmorel-a          #+#    #+#             */
/*   Updated: 2020/01/20 16:15:57 by cmorel-a         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../cub3d.h"

static int	check_color_line(char *str, char c)
{
	int		i;

	if (!str || str[0] != c)
		return (0);
	i = 1;
	while (str[i] == ' ')
		i++;
	while (ft_isdigit(str[i]) || str[i] == ',')
		i++;
	while (str[i] == ' ')
		i++;
	if (str[i] != '\0')
		return (0);
	return (1);
}

static int	one_color(char *line, int *i)
{
	int		color;

	color = ft_atoi(&line[*i]);
	if (color < 0 || color > 255)
		return (-1);
	while (ft_isdigit(line[*i]))
		*i += 1;
	*i += 1;
	return (color);
}

static int	rgb_color(int r, int g, int b)
{
	int rgb;

	rgb = r;
	rgb = (rgb << 8) + g;
	rgb = (rgb << 8) + b;
	return (rgb);
}

void		color(char *line, t_config *config, char c)
{
	int	rgb;
	int	r;
	int	g;
	int	b;
	int	i;

	i = 1;
	if (!check_color_line(line, c))
		error_config("Error:\nWrong format color");
	while (line[i] == ' ')
		i++;
	r = one_color(line, &i);
	g = one_color(line, &i);
	b = one_color(line, &i);
	if (r < 0 || g < 0 || b < 0)
		error_config("Error:\nR, G and B color must be between 0 and 255");
	rgb = rgb_color(r, g, b);
	if (c == 'F')
		config->floor = rgb;
	if (c == 'C')
		config->ceiling = rgb;
}
