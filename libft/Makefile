# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: cmorel-a <marvin@42.fr>                    +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2019/10/16 14:38:15 by cmorel-a          #+#    #+#              #
#    Updated: 2020/03/05 13:53:57 by cmorel-a         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME = libft.a
SRCS = ./ft_bzero.c \
	./ft_isdigit.c \
	./ft_isprint.c \
	./ft_split.c \
	./ft_strlcpy.c \
	./ft_strlen.c \
	./ft_strcmp.c \
	./ft_strnew.c \
	./ft_substr.c \
	./ft_test_set.c \
	./ft_type_file.c \
	./gnl.c

OBJS = ${SRCS:.c=.o}
CC = gcc
CFLAGS = -Wall -Wextra -Werror
LIBMAKER = ar rcs

.c.o:
		@${CC} ${CFLAGS} -c $< -o ${<:.c=.o}

all:	${NAME}

$(NAME):${OBJS}
		@${LIBMAKER} ${NAME} ${OBJS}

clean:
		@rm -f ${OBJS} ${BONUS_OBJS}

fclean: clean
		@rm -f ${NAME}

re: fclean all

.PHONY: all clean fclean re
