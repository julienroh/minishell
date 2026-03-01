# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: mfumeaux <mfumeaux@student.42lausanne.ch>  +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2026/02/19 11:15:32 by mfumeaux          #+#    #+#              #
#    Updated: 2026/03/01 13:58:28 by mfumeaux         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #


################################################################################
## ARGUMENTS

NAME = executor
LIBFT_PATH = ../../libft
LIBFT = ../../libft/libft.a
CC = gcc 
CFLAGS = -Werror -Wall -Wextra -O3 -g3 -O0 -fno-omit-frame-pointer -fno-inline \
	-I ../../includes -I ../../libft -I ../../libft/get_next_line


################################################################################
## SOURCES

SRC =	executor.c executor_free_utils.c executor_assignment.c \
		

OBJS = $(SRC:.c=.o)
#Src's folders which are terminated by .o .

BONUSOBJS = $(BONUS:.c=.o)

################################################################################
## RULES

all: $(NAME)

$(NAME): $(OBJS) $(LIBFT)
	$(CC) $(CFLAGS) $(OBJS) $(LIBFT) -o $(NAME)

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
