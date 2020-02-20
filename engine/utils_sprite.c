/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils_sprite.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cmorel-a <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/02/20 14:33:42 by cmorel-a          #+#    #+#             */
/*   Updated: 2020/02/20 15:43:04 by cmorel-a         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../cub3d.h"

static double	distance_to_player(t_config *config, t_list *sprite)
{
	double	cube;
	double	distance;

	cube = (config->player->pos_x - sprite->x) 
		* (config->player->pos_x - sprite->x)
		+ (config->player->pos_y - sprite->y)
		* (config->player->pos_y - sprite->y);
	distance = sqrt(distance);
	return (distance);
}


static void		add_new_sprite(t_config *config, t_list *new)
{
	t_list	*top_list;
	t_list	*to_compare;
	double	dist_old;
	double	dist_new;

	dist_old = distance_to_player(config, config->sprite);
	dist_new = distance_to_player(config, new);
	if (dist_old < dist_new)
	{
		new->next = config->sprite;
		config->sprite = new;
	}
	if (dist_old == dist_new)
		free(new);
	else
	{
		top_list = config->sprite;
		to_compare = config->sprite->next;
		while (to_compare != NULL &&
			distance_to_player(config, to_compare) > dist_new)
		{
			config->sprite = config->sprite->next;
			to_compare = config->sprite;
		}
		new->next = config->sprite->next;
		config->sprite->next = new;
	}
}

void			handle_sprite(t_config *config, t_ray *ray)
{
	t_list	*new;
	t_list	*old;

	old = config->sprite;
	if (old->x == -1 && old->y == -1)
	{
		old->x = ray->map_x;
		old->y = ray->map_y;
		return ;
	}
	if (!(new = (t_list *)malloc(sizeof(t_list))))
	{
		free(ray->dist_buff);
		free(ray);
		quit(config, "Error:\nMalloc list of sprites");
	}
	new->next = NULL;
	new->x = ray->map_x;
	new->y = ray->map_y;
	add_new_sprite(config, new);
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
