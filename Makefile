# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: sehyan <sehyan@student.42.fr>              +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2021/06/21 13:10:56 by klim              #+#    #+#              #
#    Updated: 2021/07/03 13:20:47 by sehyan           ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

CC			= 	gcc
CFLAGS		=	-Wextra -Wall -Werror -c -I include

SHELL		=	BASH

NAME		=	minishell
SRCS_DIR	=	./src/
SRCS_LIST	=	main.c \
				builtin/builtin.c \
				builtin/builtin2.c \
				builtin/builtin_utils.c \
				builtin/check_func.c \
				builtin/sort_str.c \
				env/env1.c \
				env/env2.c \
				gnl/get_next_line.c \
				gnl/get_next_line_utils.c \
				history/history1.c \
				info/info.c \
				input/input1.c \
				input/input2.c \
				libft_ref/ref1.c \
				libft_ref/atoi2.c \
				parsing/backup1.c \
				parsing/parsing1.c \
				parsing/parsing2.c \
				parsing/parsing3.c \
				parsing/parsing4.c \
				parsing/parsing5.c \
				process/process1.c \
				signal/signal1.c \
				util/util1.c \
				util/util2.c \
				util/parse_util1.c \
				util/err_util1.c \



SRCS		=	$(addprefix $(SRCS_DIR), $(SRCS_LIST))
OBJS		=	$(SRCS:.c=.o)
INCLS		=	include

all			: $(NAME)

%.o			: %.c
	@$(CC) $(CFLAGS) $< -o $@

$(NAME)		: $(OBJS)
	@make all -C libft/
	@cp libft/libft.a ./libft.a
	@$(CC) -g -I$(INCLS) $(OBJS) -L. -lft -o $(NAME)
	# @./loading.sh

leak		: $(OBJS)
	make all -C libft/
	cp libft/libft.a ./libft.a
	$(CC) -fsanitize=address -I$(INCLS) $(OBJS) -L. -lft -o $(NAME)

clean		:
	@rm -rf $(OBJS)
	@rm -rf libft.a
	@make clean -C libft

fclean		: clean
	@rm -rf $(NAME)
	@make fclean -C libft

re			: fclean all
