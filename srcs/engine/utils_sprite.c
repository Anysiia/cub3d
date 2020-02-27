/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils_sprite.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cmorel-a <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/02/20 14:33:42 by cmorel-a          #+#    #+#             */
/*   Updated: 2020/02/27 14:06:16 by cmorel-a         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/cub3d.h"

static double	dist_cub_to_player(t_config *config, t_list *sprite)
{
	double	cube;

	cube = (config->player->pos_x - sprite->x)
		* (config->player->pos_x - sprite->x)
		+ (config->player->pos_y - sprite->y)
		* (config->player->pos_y - sprite->y);
	return (cube);
}

static int		is_sprite_in_list(t_config *config, t_list *sprite)
{
	t_list	*the_list;

	the_list = config->sprite;
	while (the_list)
	{
		if (the_list->x == sprite->x && the_list->y == sprite->y)
			return (1);
		the_list = the_list->next;
	}
	return (0);
}

static void		sort_new_sprite(t_config *config, t_list *new)
{
	t_list	*working_list;
	t_list	*previous_list;

	working_list = config->sprite;
	previous_list = NULL;
	if (is_sprite_in_list(config, new))
	{
		free(new);
		return ;
	}
	while (working_list && working_list->dist > new->dist)
	{
		previous_list = working_list;
		working_list = working_list->next;
	}
	new->next = working_list;
	if (previous_list)
		previous_list->next = new;
	else
		config->sprite = new;
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