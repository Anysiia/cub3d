/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cmorel-a <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/01/20 16:24:58 by cmorel-a          #+#    #+#             */
/*   Updated: 2020/01/27 10:56:59 by cmorel-a         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../cub3d.h"

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

int		len_to_no_one(char *str)
{
	int		i;

	i = ft_strlen(str);
	i--;
	while (str[i] == '1')
		i--;
	return (i);
}

int		test_set(char c, char *charset)
{
	int		i;

	i = 0;
	while (charset[i])
	{
		if (charset[i] == c)
			return (1);
		i++;
	}
	return (0);
}
