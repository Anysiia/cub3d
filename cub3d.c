/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cub3d.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cmorel-a <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/01/20 11:08:47 by cmorel-a          #+#    #+#             */
/*   Updated: 2020/02/15 06:30:13 by cmorel-a         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

int		main(int ac, char **av)
{
	int			save;
	t_config	*config;
	
	save = (ac == 3 && !ft_strcmp(av[2], "--save"));
	check_arg(ac, av, save);
	config = init_config(save);
	map_read_cub(av[1], config);
	init_game(config);
	raycaster(config);
	mlx_hook(config->window, 2, 1L << 0, key_pressed, config);
	mlx_hook(config->window, 17, 1L << 17, leave_window, config);
	mlx_loop(config->init);
	return (0);
}

void	exit_error(const char *msg)
{
	if (msg)
		write(1, msg, ft_strlen(msg));
	write(1, "\n", 1);
	exit(0);
}

void	quit(t_config *config, const char *msg)
{
	if (msg)
		write(1, msg, ft_strlen(msg));
	write(1, "\n", 1);
	mlx_destroy_window(config->init, config->window);
	exit(0);
}

int		check_arg(int ac, char **av, int save)
{
	if (ac < 2)
		exit_error("Error:\nNo map indicated");
	if (ac == 3 && save == 0)
		exit_error("Error:\nSecond argument is not --save.");
	if (ac > 3)
		exit_error("Error:\nToo many arguments.");
	if ((ft_type_file(av[1], ".cub")) == 0)
		exit_error("Error:\nMap file is not a .cub file.");
	return (1);
}
