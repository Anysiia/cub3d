/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_itoa.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cmorel-a <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/10/11 16:00:07 by cmorel-a          #+#    #+#             */
/*   Updated: 2019/10/14 10:54:08 by cmorel-a         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static size_t	len_number(int n)
{
	size_t			i;
	unsigned int	nb;

	i = 1;
	if (n < 0)
	{
		i++;
		nb = -n;
	}
	else
		nb = n;
	while (nb / 10 > 0)
	{
		i++;
		nb = nb / 10;
	}
	return (i);
}

char			*ft_itoa(int n)
{
	char			*res;
	size_t			len;
	unsigned int	nb;
	size_t			i;

	len = len_number(n);
	i = 0;
	if (!(res = (char *)malloc(sizeof(*res) * (len + 1))))
		return (NULL);
	res[len] = '\0';
	if (n < 0)
	{
		res[0] = '-';
		nb = -n;
		i = 1;
	}
	else
		nb = n;
	while (len-- > i)
	{
		res[len] = nb % 10 + '0';
		nb = nb / 10;
	}
	return (res);
}
