/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   train_gnl.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cmorel-a <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/11/26 14:55:30 by cmorel-a          #+#    #+#             */
/*   Updated: 2020/02/03 15:34:30 by cmorel-a         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static size_t	str_char_len(const char *s, char c)
{
	size_t	i;

	if (!s)
		return (0);
	i = 0;
	while (s[i] && s[i] != c)
		i++;
	return (i);
}

static char		*newline(const char *s1, char c)
{
	int		i;
	char	*s2;

	i = 0;
	if (!(s2 = (char *)malloc(sizeof(*s2) * (str_char_len(s1, '\n') + 1))))
		return (NULL);
	while (s1[i] && s1[i] != c)
	{
		s2[i] = s1[i];
		i++;
	}
	s2[i] = '\0';
	return (s2);
}

static char		*join_to_char(char *s1, char *s2, char c)
{
	int		len_s1;
	int		len_s2;
	int		i;
	char	*s;

	if (!s1)
		return (newline(s2, '\n'));
	if (!s2)
		return (NULL);
	len_s1 = str_char_len(s1, '\0');
	len_s2 = str_char_len(s2, '\n');
	if (!(s = (char *)malloc(sizeof(*s) * (len_s1 + len_s2 + 1))))
		return (NULL);
	i = -1;
	while (s1[++i])
		s[i] = s1[i];
	i = -1;
	while (s2[++i] && s2[i] != c)
		s[len_s1 + i] = s2[i];
	s[len_s1 + i] = '\0';
	free(s1);
	return (s);
}

static int		cmpt(char *s)
{
	int		i;

	i = 0;
	while (s[i])
	{
		if (s[i] == '\n')
			return (i);
		i++;
	}
	return (-1);
}

int				get_next_line(int fd, char **line)
{
	static char	s[129];
	int			ret;

	if (!line || fd < 0 || read(fd, NULL, 0) == -1 || \
			!(*line = ft_strnew(1)))
		return (-1);
	while (cmpt(s) == -1)
	{
		if (!(*line = join_to_char(*line, s, '\n')))
			return (-1);
		ft_bzero(s, 129);
		ret = read(fd, s, 128);
		if (ret <= 0)
			return (ret);
	}
	if (!(*line = join_to_char(*line, s, '\n')))
		return (-1);
	ft_strlcpy(s, (s + cmpt(s) + 1), 128);
	return (1);
}
