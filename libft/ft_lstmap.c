/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstmap_bonus.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cmorel-a <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/10/15 17:04:10 by cmorel-a          #+#    #+#             */
/*   Updated: 2019/10/22 13:53:51 by cmorel-a         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

t_list		*ft_lstmap(t_list *lst, void *(*f)(void*), void (*del)(void*))
{
	t_list	*newlst;
	t_list	*prev;
	t_list	*temp;

	if (!lst || !f)
		return (NULL);
	if (!(newlst = (t_list *)malloc(sizeof(t_list))))
		return (NULL);
	newlst->content = f(lst->content);
	lst = lst->next;
	prev = newlst;
	while (lst)
	{
		if (!(temp = (t_list *)malloc(sizeof(t_list))))
		{
			ft_lstclear(&newlst, del);
			return (NULL);
		}
		temp->content = f(lst->content);
		prev->next = temp;
		prev = temp;
		lst = lst->next;
	}
	prev->next = NULL;
	return (newlst);
}
