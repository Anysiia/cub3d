/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cub3d.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cmorel-a <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/01/20 11:08:47 by cmorel-a          #+#    #+#             */
/*   Updated: 2020/01/20 12:30:33 by cmorel-a         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"
#include <mlx.h>
#include <stdio.h>

static int	exit_with_error(const char *str)
{
	if (str)
		write(1, str, ft_strlen(str));
	return (0);
}

int		main(int ac, char **av)
{
	int			save;
	t_config	config;
	
	save = (ac == 3 && !ft_strcmp(av[2], "--save"));
	if (!check_arg(ac, av, save))
		return (0);
	if (read_cub(av[1], &config) == -1)
		return (exit_with_error("Error:\nInvalid config of .cub file\n"));
	return (0);
}

int		check_arg(int ac, char **av, int save)
{
	if (ac < 2)
		return (exit_with_error("Error:\nNo map indicated\n"));
	if (ac == 3 && save == 0)
		return (exit_with_error("Error:\nSecond argument is not --save.\n"));
	if (ac > 3)
		return (exit_with_error("Error:\nToo many arguments.\n"));
	if ((ft_type_file(av[1], ".cub")) == 0)
		return (exit_with_error("Error:\nMap file is not a .cub file.\n"));
	return (1);
}
