# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: klim <klim@student.42.fr>                  +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2021/06/21 13:10:56 by klim              #+#    #+#              #
#    Updated: 2021/06/21 14:29:08 by klim             ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

CC			= 	gcc
CFLAGS		=	-Wextra -Wall -Werror -c

NAME		=	minishell
SRCS_DIR	=	./src/
SRCS_LIST	=	test.c \

SRCS		=	$(addprefix $(SRCS_DIR), $(SRCS_LIST))
OBJS		=	$(SRCS:.c=.o)
INCLS		=	include

all			: $(NAME)

%.o			: %.c
	$(CC) $(CFLAGS) $< -o $@

$(NAME)		: $(OBJS)
	make all -C libft/
	cp libft/libft.a ./libft.a
	$(CC) -I$(INCLS) $(OBJS) -L. -lft -o $(NAME)

clean		:
	rm -rf $(OBJS)
	rm -rf libft.a
	make clean -C libft

fclean		: clean
	rm -rf $(NAME)
	make fclean -C libft

re			: fclean all
