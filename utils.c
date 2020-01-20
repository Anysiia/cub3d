/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cmorel-a <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/01/20 16:24:58 by cmorel-a          #+#    #+#             */
/*   Updated: 2020/01/20 16:26:09 by cmorel-a         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

int		ft_type_file(const char *file, const char *type)
{
	int		len_file;
	int		len_type;
	int		i;
	int		j;

	if (!file || !type)
		return (0);
	len_file = ft_strlen(file);
	len_type = ft_strlen(type);
	if (len_file <= len_type)
		return (0);
	i = len_file - len_type;
	j = 0;
	while (file[i] && j < len_type)
		if (file[i++] != type[j++])
			return (0);
	return (1);
}

int		player_init_posit(char c)
{
	if (c == 'N' || c == 'S' || c == 'E' || c == 'W')
		return (1);
	return (0);
}

int		check_char_map(char c)
{
	if (c == '1' || c == '2' || c == '0' || (player_init_posit(c) == 1))
		return (1);
	return (0);
}
