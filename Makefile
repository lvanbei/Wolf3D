# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: lvan-bei <marvin@42.fr>                    +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2019/06/02 19:24:04 by lvan-bei          #+#    #+#              #
#    Updated: 2019/06/02 19:24:06 by lvan-bei         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

OK_COLOR=\x1b[32;01m
RM_COLOR=\x1b[31;01m
NAME	= wolf3d

SRC =	srcs/main.c\
		srcs/hook.c\
		srcs/read.c\
		srcs/read_2.c\
		srcs/menu.c\
		srcs/textures.c\
		srcs/raycasting.c\
		srcs/tools.c\
		srcs/create_images.c\
		srcs/map_builder.c\
		srcs/map_builder_read.c\
		srcs/map_builder_lines.c\
		srcs/map_builder_hook.c\
		
OBJ		= $(SRC:.c=.o)

CC		= gcc
CFLAGS	= -Wall -Wextra -Werror

MLX		= ./miniLibx_macos/
MLX_LIB	= $(MLX)mlx.a
MLX_INC	= -I ./miniLibX
MLX_LNK	= -L $(MLX) -l mlx -framework OpenGL -framework AppKit

FT		= ./libft/
FT_LIB	= $(addprefix $(FT),libft.a)
FT_LNK	= -L ./libft -l ft

.SILENT:

all: $(FT_LIB) $(MLX_LIB) $(NAME)

$(FT_LIB):
	make -C $(FT)
	echo "$(OK_COLOR)libft [created]"
$(MLX_LIB):
	make -C $(MLX)
	echo "$(OK_COLOR)minilibx [created]"
$(NAME): $(OBJ)
	$(CC) $(CFLAGS) -I $(FT) -c $(SRC)
	mv *.o srcs
	$(CC) $(CFLAGS) $(OBJ) $(MLX_LNK) $(FT_LNK) -lm -o $(NAME)
	echo "$(OK_COLOR)objetcts [created]"
	echo "$(OK_COLOR)./wolf3d [created]"
clean:
	make -C $(FT) clean
	echo "$(RM_COLOR)libft [deleted]"
	make -C $(MLX) clean
	echo "$(RM_COLOR)minilibx [deleted]"
	rm -rf $(OBJ)
	echo "$(RM_COLOR)objetcts [deleted]"

fclean: clean
	rm -rf $(NAME)
	echo "$(RM_COLOR)./wolf3d [deleted]"
	make -C $(FT) fclean
	echo "$(RM_COLOR)libft [deleted]"
re: fclean all
