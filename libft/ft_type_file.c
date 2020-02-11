/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_type_file.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cmorel-a <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/02/11 11:29:25 by cmorel-a          #+#    #+#             */
/*   Updated: 2020/02/11 11:30:02 by cmorel-a         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

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
