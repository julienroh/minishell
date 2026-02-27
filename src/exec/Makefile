# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: mfumeaux <mfumeaux@student.42lausanne.ch>  +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2026/01/28 12:14:16 by mfumeaux          #+#    #+#              #
#    Updated: 2026/02/19 12:06:13 by mfumeaux         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #


################################################################################
## ARGUMENTS

NAME = fdf
LIBFT_PATH = libft
LIBFT = $(LIBFT_PATH)/libft.a
CC = gcc 
CFLAGS = -Werror -Wall -Wextra -O3 -std=gnu11 -g3 -O0 -fno-omit-frame-pointer -fno-inline
MLX = libmlx_Linux.a
MLXFLAGS = -lXext -lX11 -lm

################################################################################
## SOURCES

SRC =	fdf.c fdf_utils1.c parse_map.c parse_map_utils.c camera.c draw.c \
		draw_utils.c draw_utils_2.c parse_map_error.c hook.c

OBJS = $(SRC:.c=.o)
#Src's folders which are terminated by .o .

BONUSOBJS = $(BONUS:.c=.o)

################################################################################
## RULES

all: $(NAME)

$(NAME): $(OBJS) $(LIBFT)
	$(CC) $(CFLAGS) $(OBJS) $(LIBFT) $(MLX) $(MLXFLAGS) -o $(NAME)

$(LIBFT):
	make -C $(LIBFT_PATH)
	
%.o: %.c
	$(CC) $(CFLAGS) -c $< -o $@

clean:
	rm -f *.o
	make -C $(LIBFT_PATH) clean

fclean: clean
	rm -f $(NAME)
	make -C $(LIBFT_PATH) fclean

re: fclean all

.PHONY: all clean fclean re
