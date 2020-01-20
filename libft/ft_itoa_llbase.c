/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_itoa_llbase.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cmorel-a <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/11/14 12:30:46 by cmorel-a          #+#    #+#             */
/*   Updated: 2019/11/14 12:55:36 by cmorel-a         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static size_t	len_number(long long int n, size_t size)
{
	size_t	i;

	i = (n < 0 ? 2 : 1);
	n = (n < 0 ? -n : n);
	while (n / size > 0)
	{
		i++;
		n = n / size;
	}
	return (i);
}

char			*ft_itoa_llbase(long long int n, char *base)
{
	char	*res;
	size_t	len;
	size_t	size;
	size_t	i;

	if (!(size = ft_check_base(base)) || !base)
		return (NULL);
	len = len_number(n, size);
	if (!(res = (char *)malloc(sizeof(*res) * (len + 1))))
		return (NULL);
	res[len] = '\0';
	i = (n < 0 ? 1 : 0);
	if (n < 0)
		res[0] = '-';
	n = (n < 0 ? -n : n);
	while (len-- > i)
	{
		res[len] = base[n % size];
		n = n / size;
	}
	return (res);
}
