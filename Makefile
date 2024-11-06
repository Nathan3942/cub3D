# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: njeanbou <njeanbou@student.42.fr>          +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2024/04/24 04:13:09 by ichpakov          #+#    #+#              #
#    Updated: 2024/11/06 17:09:48 by njeanbou         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

.PHONY: all clean fclean re make norm

NAME = cub3d
LIBFT = libft/libft.a
LIBMLX = mlx/libmlx.a

#//////////////////////////////////////////////////////////////////////////////
#		ALL FILES
#//////////////////////////////////////////////////////////////////////////////

SRCS =	$(wildcard c3d_src/*.c c3d_src/check_map/*.c c3d_src/free/*.c c3d_src/moov/*.c c3d_src/parsing/*.c c3d_src/render/*.c) #c3d_src/cub3d.c			\

HEAD =	c3d_inc/cub3d.h			c3d_inc/c3d_keys.h

#//////////////////////////////////////////////////////////////////////////////
#		COMMAND SHORTCUTS
#//////////////////////////////////////////////////////////////////////////////

CC = gcc
CF = -fsanitize=address -static-libasan #-Wall -Werror -Wextra -g
SL = -Imlx -Imlx_linux -lXext -lX11 -lm -lz
CI = -I ./c3d_inc/


AR = ar rcs
RM = rm -rf

#//////////////////////////////////////////////////////////////////////////////
#		RULES
#//////////////////////////////////////////////////////////////////////////////

all: ${NAME}

# Binary creation

${NAME}: ${SRCS} ${HEAD} ${LIBFT} ${LIBMLX}
	${CC} ${CF} ${CI} ${SRCS} ${LIBFT} ${LIBMLX} ${SL} -o ${NAME}

${LIBFT}:
	make -C libft/

${LIBMLX}:
	make -C mlx/

# Mandatory rules

clean:
	${RM} libft/libft.a
	${RM} mlx/*.o mlx/test/*.o

fclean: clean
	${RM} ${NAME}
	${RM} libft/libft.a
	${RM} mlx/libmlx_Linux.a
	make fclean -C libft
	make clean -C mlx

re: fclean all