/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_free_s1_join.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cmorel-a <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/02/11 11:31:37 by cmorel-a          #+#    #+#             */
/*   Updated: 2020/02/11 11:32:18 by cmorel-a         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_free_s1_join(char *s1, char const *s2)
{
	int		len;
	int		i;
	char	*str;

	if (!s1 || !s2)
		return (NULL);
	i = ft_strlen(s1);
	len = ft_strlen(s2);
	len += i;
	i = 0;
	if (!(str = (char *)malloc(sizeof(*str) * (len + 1))))
		return (NULL);
	i = -1;
	while (s1[++i])
		str[i] = s1[i];
	len = -1;
	while (s2[++len])
		str[i + len] = s2[len];
	str[i + len] = '\0';
	free(s1);
	return (str);
}
