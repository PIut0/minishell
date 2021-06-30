# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: ash <ash@student.42.fr>                    +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2021/06/21 13:10:56 by klim              #+#    #+#              #
#    Updated: 2021/06/29 15:14:33 by ash              ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

CC			= 	gcc
CFLAGS		=	-Wextra -Wall -Werror -c -I include

NAME		=	minishell
SRCS_DIR	=	./src/
SRCS_LIST	=	test.c \
				gnl/get_next_line.c \
				gnl/get_next_line_utils.c \
				libft_ref/ref1.c \
				parsing/parsing1.c \
				parsing/parsing2.c \
				parsing/parsing3.c \
				parsing/parsing4.c \
				process/process1.c \
				util/util1.c \
				util/parse_util1.c \
				util/err_util1.c \
				util/env_util1.c \
				argv.c \
				info.c \
				../builtin/builtin.c \
				../builtin/builtin_utils.c \
				../builtin/check_func.c \
				


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

leak		: $(OBJS)
	make all -C libft/
	cp libft/libft.a ./libft.a
#$(CC) -I$(INCLS) $(OBJS) -L. -lft -o $(NAME)
	$(CC) -fsanitize=address -I$(INCLS) $(OBJS) -L. -lft -o $(NAME)

clean		:
	rm -rf $(OBJS)
	rm -rf libft.a
	make clean -C libft

fclean		: clean
	rm -rf $(NAME)
	make fclean -C libft

re			: fclean all
	./$(NAME)
