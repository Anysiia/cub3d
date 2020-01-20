/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_split.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cmorel-a <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/10/11 11:36:29 by cmorel-a          #+#    #+#             */
/*   Updated: 2019/10/25 11:05:19 by cmorel-a         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static size_t	numb_lines(const char *s, char c)
{
	size_t	lines;
	size_t	i;

	i = 1;
	lines = 0;
	if (s[0] == '\0')
		return (0);
	if (s[1] == '\0' && s[0] != c)
		return (1);
	while (s[i] && s[i] == c)
		i++;
	while (s[i])
	{
		lines++;
		while (s[i] && s[i] == c)
			i++;
		while (s[i] && s[i] != c)
			i++;
	}
	if (s[--i] == c && lines != 0)
		lines--;
	return (lines);
}

static char		*fill_lines(const char *s, char c)
{
	size_t	len;
	size_t	i;
	char	*word;

	i = 0;
	len = 0;
	while (s[len] && s[len] != c)
		len++;
	if (!(word = (char *)malloc(sizeof(*word) * (len + 1))))
		return (NULL);
	i = 0;
	while (i < len)
	{
		word[i] = s[i];
		i++;
	}
	word[i] = '\0';
	return (word);
}

static void		free_tab(int i, char **tab)
{
	while (i-- >= 0)
		free(tab[i]);
	free(tab);
}

char			**ft_split(char const *s, char c)
{
	char	**tab;
	size_t	lines;
	size_t	i;

	if (!s)
		return (NULL);
	lines = numb_lines(s, c);
	if (!(tab = (char **)malloc(sizeof(*tab) * (lines + 1))))
		return (NULL);
	i = 0;
	while (i < lines)
	{
		while (*s && *s == c)
			s++;
		if ((tab[i] = fill_lines(s, c)) == NULL)
		{
			free_tab(i, tab);
			return (NULL);
		}
		while (*s && *s != c)
			s++;
		i++;
	}
	tab[i] = 0;
	return (tab);
}
