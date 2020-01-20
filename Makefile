# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: cmorel-a <marvin@42.fr>                    +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2019/10/16 14:38:15 by cmorel-a          #+#    #+#              #
#    Updated: 2020/01/20 11:23:59 by cmorel-a         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME =		cub3d

CFLAGS = 	-Wall -Werror -Wextra

MLX =		-lmlx -lm -framework OpenGL -framework AppKit

INCLUDE = 	-I ./includes -I ./usr/include

LIBFT_DIR =	libft/

SRCS =		cub3d.c \
			config/color.c \
			config/map.c \
			config/parse_cub.c \
			config/resolution.c \
			config/texture.c \
			gnl.c \
			utils.c

OBJS = 		${SRCS:.c=.o}

.c.o:
		gcc ${CFLAGS} -c $< -o ${<:.c=.o}

all:	$(NAME)

$(NAME):$(OBJS)
		@$(MAKE) -C ./libft/
		@gcc $(OBJS) $(INCLUDE) $(CFLAGS) $(MLX) ./libft/libft.a -o $(NAME)

clean:
		@rm -rf $(OBJS)
		@$(MAKE) clean -C ./libft/

fclean: clean
		@$(MAKE) fclean -C ./libft/
		@rm -rf $(NAME)
		@rm -rf cub3d.bmp

re: fclean all

.PHONY: all clean fclean re
