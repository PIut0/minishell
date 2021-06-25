/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: klim <klim@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/06/21 14:20:02 by klim              #+#    #+#             */
/*   Updated: 2021/06/25 14:27:03 by klim             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_H
# define MINISHELL_H

# include <unistd.h>
# include <stdio.h>
# include <stdlib.h>

# define WHITE_SPACE " \t\n\v\f\b"
# define BACK_SLASH -1

typedef enum		e_token_type
{
	_null,
	_none,
	_pipe,
	_brackets,
	_r_brackets,
	_d_brackets,
	_rd_brackets,
	_semicolon
}					t_token_type;

typedef	struct		s_argv
{
	char			*data;
	struct	s_argv	*next;
}					t_argv;

typedef	struct		s_token
{
	char			*data;
	t_argv			*argv;
	t_token_type	token_type;
	struct	s_token	*next;
}					t_token;
typedef	struct		s_info
{
	char			*cmd;
	t_argv			*argv;
	t_token			*head;
}					t_info;

int			get_next_line(int fd, char **line);
int			parsing(char *line, t_info *info);

t_argv		*init_argv(char *data);
int			push_argv(char *data, t_info *info);
void		print_argv(t_argv *argv);
void		print_token(t_token *head);

void	free_info(t_info *info);
t_info	*init_info(void);


#endif
