# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: cmorel-a <marvin@42.fr>                    +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2020/01/21 09:57:43 by cmorel-a          #+#    #+#              #
#    Updated: 2020/02/03 15:33:38 by cmorel-a         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME =		cub3d

CFLAGS = 	-Wall -Werror -Wextra

MLX =		-lmlx -lm -framework OpenGL -framework AppKit -L $(MLX_PATH)

MLX_PATH =	/Users/cmorel-a/cub3d

INCLUDE = 	-I ./include -I $(MLX_PATH)

LIBFT_DIR =	libft/

SRCS =		cub3d.c \
			config/init_config.c \
			config/color.c \
			config/parse_cub.c \
			config/map.c \
			config/player.c \
			config/resolution.c \
			config/texture.c \
			config/utils.c \
			engine/move_player.c \
			engine/key_event.c \
			engine/raycaster.c \
			engine/utils_caster.c

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
