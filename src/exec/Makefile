# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: mfumeaux <mfumeaux@student.42lausanne.ch>  +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2026/02/19 11:15:32 by mfumeaux          #+#    #+#              #
#    Updated: 2026/03/05 12:05:48 by mfumeaux         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #


################################################################################
## ARGUMENTS

NAME = exec
LIBFT_PATH = ../../libft
LIBFT = ../../libft/libft.a
CC = gcc 
CFLAGS = -Werror -Wall -Wextra -O3 -g3 -O0 -fno-omit-frame-pointer -fno-inline \
	-I ../../includes -I ../../libft -I ../../libft/get_next_line


################################################################################
## SOURCES

SRC =	exec.c exec_free_utils.c exec_assign_utils.c \
		exec_assign_utils2.c exec_assign_utils3.c \
		exec_dup_env.c exec_env_to_envp.c \
		#exec_utils.c exec_utils2.c \
		

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
