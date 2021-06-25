# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: klim <klim@student.42.fr>                  +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2021/06/21 13:10:56 by klim              #+#    #+#              #
#    Updated: 2021/06/23 17:24:16 by klim             ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

CC			= 	gcc
CFLAGS		=	-Wextra -Wall -Werror -c -I include

NAME		=	minishell
SRCS_DIR	=	./src/
SRCS_LIST	=	test.c \
				gnl/get_next_line.c \
				gnl/get_next_line_utils.c \
				parsing/parsing1.c \
				argv.c \
				info.c

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
	./$(NAME)
