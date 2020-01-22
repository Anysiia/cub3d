/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cub3d.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cmorel-a <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/01/20 11:08:47 by cmorel-a          #+#    #+#             */
/*   Updated: 2020/01/22 16:13:22 by cmorel-a         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"
#include <mlx.h>
#include <stdio.h>

void	error_config(const char *msg)
{
	if (msg)
		write(1, msg, ft_strlen(msg));
	write(1, "\n", 1);
	exit(0);
}

int		main(int ac, char **av)
{
	int			save;
	t_config	config;
	
	save = (ac == 3 && !ft_strcmp(av[2], "--save"));
	check_arg(ac, av, save);
	map_read_cub(av[1], &config);
	return (0);
}

int		check_arg(int ac, char **av, int save)
{
	if (ac < 2)
		error_config("Error:\nNo map indicated");
	if (ac == 3 && save == 0)
		error_config("Error:\nSecond argument is not --save.");
	if (ac > 3)
		error_config("Error:\nToo many arguments.");
	if ((ft_type_file(av[1], ".cub")) == 0)
		error_config("Error:\nMap file is not a .cub file.");
	return (1);
}
