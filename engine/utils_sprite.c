/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils_sprite.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cmorel-a <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/02/20 14:33:42 by cmorel-a          #+#    #+#             */
/*   Updated: 2020/02/21 12:14:24 by cmorel-a         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../cub3d.h"

static double	dist_cub_to_player(t_config *config, t_list *sprite)
{
	double	cube;

	cube = (config->player->pos_x - sprite->x) 
		* (config->player->pos_x - sprite->x)
		+ (config->player->pos_y - sprite->y)
		* (config->player->pos_y - sprite->y);
	return (cube);
}

static void		sort_new_sprite(t_config *config, t_list *new)
{
	t_list	*top_list;

	if (config->sprite->dist < new->dist)
	{
		new->next = config->sprite;
		config->sprite = new;
	}
	else if (config->sprite->dist > new->dist)
	{
		top_list = config->sprite;
		while (config->sprite->next && config->sprite->next->dist > new->dist)
			config->sprite = config->sprite->next;
		if ((config->sprite->next && config->sprite->next->x == new->x
			&& config->sprite->next->y == new->y) 
			|| (config->sprite->x == new->x && config->sprite->y == new->y))
		{
			free(new);
			return ;
		}
		new->next = (config->sprite->next == NULL ? NULL
			: config->sprite->next);
		config->sprite->next = new;
		config->sprite = top_list;
	}
}

void			handle_sprite(t_config *config, t_ray *ray)
{
	t_list	*new;

	if (config->sprite->x == -1 && config->sprite->y == -1)
	{
		config->sprite->x = ray->map_x;
		config->sprite->y = ray->map_y;
		config->sprite->dist = dist_cub_to_player(config, config->sprite);
		return ;
	}
	if (config->sprite->x == ray->map_x && config->sprite->y == ray->map_y)
		return ;
	if (!(new = (t_list *)malloc(sizeof(t_list))))
	{
		free(ray->dist_buff);
		free(ray);
		quit(config, "Error:\nMalloc list of sprites");
	}
	new->next = NULL;
	new->x = ray->map_x;
	new->y = ray->map_y;
	new->dist = dist_cub_to_player(config, new);
	sort_new_sprite(config, new);
}

void			ft_lstdel_firstnode(t_config *config)
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
