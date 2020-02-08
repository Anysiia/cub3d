/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strtrim.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cmorel-a <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/10/11 10:37:42 by cmorel-a          #+#    #+#             */
/*   Updated: 2020/02/08 11:58:06 by cmorel-a         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static int	test_set(char c, char const *set)
{
	while (*set)
	{
		if (*set++ == c)
			return (1);
	}
	return (0);
}

char		*ft_free_strtrim(char *s1, char const *set)
{
	char	*s2;
	int		len;
	int		i;
	int		size;

	if (!s1)
		return (NULL);
	len = ft_strlen(s1);
	i = len - 1;
	while (i >= 0 && (test_set(s1[i], set)))
	{
		len--;
		i--;
	}
	i = 0;
	while (s1[i] && (test_set(s1[i], set)))
		i++;
	size = (i > len ? 0 : len - i);
	s2 = ft_substr(s1, i, size);
	free(s1);
	return (s2);
}
