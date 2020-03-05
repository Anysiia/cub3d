/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   resolution.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cmorel-a <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/01/20 15:56:11 by cmorel-a          #+#    #+#             */
/*   Updated: 2020/02/27 14:03:45 by cmorel-a         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/cub3d.h"

static int	check_resolution_line(char *str)
{
	int		i;

	if (!str || str[0] != 'R' || str[1] != ' ')
		return (0);
	i = 1;
	while (str[i] == ' ')
		i++;
	if (!ft_isdigit(str[i]))
		return (0);
	while (ft_isdigit(str[i]))
		i++;
	if (str[i] != ' ')
		return (0);
	while (str[i] == ' ')
		i++;
	if (!ft_isdigit(str[i]))
		return (0);
	while (ft_isdigit(str[i]))
		i++;
	while (str[i] == ' ')
		i++;
	if (str[i] != '\0')
		return (0);
	return (1);
}

static int	get_number(char *str, int start)
{
	int		resolution;

	resolution = 0;
	while (ft_isdigit(str[start]))
		resolution = (resolution * 10) + (str[start++] - '0');
	return (resolution);
}

void		resolution(char *line, t_config *config)
{
	int		i;
	int		res;

	if (config->height != -1)
		exit_error("Error:\nMore than one resolution configuration");
	if (!check_resolution_line(line))
		exit_error("Error:\nWrong resolution");
	i = 1;
	while (line[i] == ' ')
		i++;
	res = get_number(line, i);
	res = (res > 2560 ? 2560 : res);
	if (res < 50)
		exit_error("Error:\nWidth resolution is too small");
	config->width = res;
	while (ft_isdigit(line[i]))
		i++;
	while (line[i] == ' ')
		i++;
	res = get_number(line, i);
	res = (res > 1440 ? 1440 : res);
	if (res < 50)
		exit_error("Error:\nHeight resolution is too small");
	config->height = res;
}
