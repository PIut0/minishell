/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: klim <klim@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/06/21 14:20:02 by klim              #+#    #+#             */
/*   Updated: 2021/06/23 16:53:55 by klim             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_H
# define MINISHELL_H

# include <unistd.h>
# include <stdio.h>
# include <stdlib.h>

# define WHITE_SPACE " \t\n\v\f\b"

typedef enum		e_token_type
{
	null,
	none,
	pipe,
	brackets,
	r_brackets,
	d_brackets,
	rd_brackets,
	semicolon
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
}					t_info;

int			get_next_line(int fd, char **line);
int			parsing(char *line, t_info *info);

t_argv		*init_node(char *data);
int			push_node(char *data, t_info *info);
void		print_node(t_argv *argv);

void	free_info(t_info *info);
t_info	*init_info(void);


#endif
