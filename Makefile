# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: cmorel-a <marvin@42.fr>                    +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2020/01/21 09:57:43 by cmorel-a          #+#    #+#              #
#    Updated: 2020/02/28 10:42:16 by cmorel-a         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME =		cub3d

CFLAGS = 	-Wall -Werror -Wextra

MLX =		-lmlx -lm -framework OpenGL -framework AppKit -L $(MLX_PATH)

MLX_PATH =	mlx/

INCLUDE = 	-I $(MLX_PATH) -I ./includes/

LIBFT_DIR =	libft/

SRCS =		srcs/cub3d.c \
			srcs/config/init_config.c \
			srcs/config/color.c \
			srcs/config/parse_cub.c \
			srcs/config/map.c \
			srcs/config/player.c \
			srcs/config/resolution.c \
			srcs/config/texture.c \
			srcs/config/line_map.c \
			srcs/config/row_map.c \
			srcs/engine/move_player.c \
			srcs/engine/key_event.c \
			srcs/engine/raycaster.c \
			srcs/engine/scene.c \
			srcs/engine/texture.c \
			srcs/engine/sprite.c \
			srcs/engine/utils_sprite.c \
			srcs/engine/save_bitmap.c

OBJS = 		${SRCS:.c=.o}

.c.o:
		gcc ${CFLAGS} -c $< -o ${<:.c=.o}

all:	$(NAME)

$(NAME):$(OBJS)
		@$(MAKE) -C ./libft/
		@$(MAKE) -C ./mlx/
		@gcc $(OBJS) $(INCLUDE) -O3 $(CFLAGS) $(MLX) ./libft/libft.a -o $(NAME)

clean:
		@rm -rf $(OBJS)
		@$(MAKE) clean -C ./libft/
		@$(MAKE) clean -C ./mlx/

fclean: clean
		@$(MAKE) fclean -C ./libft/
		@$(MAKE) clean -C ./mlx/
		@rm -rf $(NAME)
		@rm -rf cub3d.bmp

re: fclean all

.PHONY: all clean fclean re
