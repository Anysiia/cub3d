/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   libft.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cmorel-a <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/10/07 12:01:03 by cmorel-a          #+#    #+#             */
/*   Updated: 2020/03/05 13:53:38 by cmorel-a         ###   ########.fr       */
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
char		*ft_strnew(size_t size);
char		**ft_split(char const *s, char c);
char		*ft_substr(char const *s, unsigned int start, size_t len);
int			get_next_line(int fd, char **line);
int			ft_type_file(const char *file, const char *type);
int			ft_test_set(const char c, const char *charset);

#endif
