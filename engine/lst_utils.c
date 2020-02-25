/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lst_utils.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cmorel-a <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/02/22 12:38:56 by cmorel-a          #+#    #+#             */
/*   Updated: 2020/02/25 11:48:30 by cmorel-a         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../cub3d.h"

int		ft_lstsize(t_config *config)
{
	int		i;
	t_list	*top;

	top = config->sprite;
	i = 0;
	while (config->sprite)
	{
		config->sprite = config->sprite->next;
		i++;
	}
	config->sprite = top;
	return (i);
}

void	ft_lstdel_firstnode(t_config *config)
{
	t_list		*todelete;

	if (config->sprite)
	{
		todelete = config->sprite;
		config->sprite = config->sprite->next;
		todelete->next = NULL;
		free(todelete);
	}
}
