/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   libft.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cmorel-a <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/10/07 12:01:03 by cmorel-a          #+#    #+#             */
/*   Updated: 2020/02/08 11:57:56 by cmorel-a         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef LIBFT_H
# define LIBFT_H
# include <stdlib.h>
# include <unistd.h>

void		ft_bzero(void *s, size_t n);
size_t		ft_strlen(const char *str);
int			ft_isdigit(int c);
int			ft_isprint(int c);
int			ft_strcmp(const char *s1, const char *s2);
size_t		ft_strlcpy(char *dst, const char *src, size_t dstsize);
int			ft_atoi(const char *str);
char		*ft_strjoin(char const *s1, char const *s2);
char		*ft_strnew(size_t size);
char		**ft_split(char const *s, char c);
char		*ft_substr(char const *s, unsigned int start, size_t len);
char		*ft_free_strtrim(char *s1, char const *set);
int			get_next_line(int fd, char **line);

#endif
