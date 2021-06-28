/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: klim <klim@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/06/21 14:20:02 by klim              #+#    #+#             */
/*   Updated: 2021/06/28 21:52:37 by klim             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_H
# define MINISHELL_H

# include <unistd.h>
# include <stdio.h>
# include <stdlib.h>
# include <errno.h>
# include "libft.h"

# define WHITE_SPACE " \t\n\v\f\b"
# define NEGATIVE_CHAR "><~"
# define BACK_SLASH -1
# define ENV_D_QUOTE -2

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

typedef struct	s_node
{
	struct s_node	*next;
	struct s_node	*prev;
	char			*key;
	char			*value;
}				t_node;

typedef struct	s_env
{
	t_node		*head;
	t_node		*tail;
}				t_env;

typedef	struct		s_shell
{
	t_env			*env;
}					t_shell;
typedef	struct		s_token
{
	char			*data;
	char			**argv;
	t_token_type	token_type;
	struct	s_token	*next;
}					t_token;
typedef	struct		s_info
{
	char			*cmd;
	t_token			*head;
	t_shell			*shell;
}					t_info;

int				get_next_line(int fd, char **line);
int				parsing(char *line, t_info *info);
char			*replace_bs(char *line, int len);
char			*backup_bs(char *line, int len);
int				parse_token(char *line, t_info *info, t_token *head, int len);
int				join_brackets(t_token *head);
char			*get_brackets(t_token_type t);
char			*ft_strjoin_free(char *s1, char *s2, int n);
int				is_type_brackets(t_token_type t);
int				add_new_token(t_token *head, char *line, int *i, int last);
char			*remove_space(char *str);
t_token_type	get_token(char *line, int i);
int				is_quote(char *line, int n);
t_token			*init_token(char *data);
int				is_space(char c);
int				parse_argv(t_info *info, t_token *head);
char	*parse_data(char *argv, t_info *info);
char	*replace_env(char *argv, t_info *info);
char	*remove_quote(char *str);
char	*change_dq_edq(char *str, int key);
char	*remove_bs(char *str);

char		*backup_data(char *data, t_info *info);
char		*backup_nega_char(char *data);


int		process_info(t_info *info);

void			print_token(t_token *head);
void		print_argv(char **argv);

t_node			*init_node(char *s);
t_node			*find_node(char *key, t_env *env);
int				check_key_val(t_node *node);
int				add_env(char *s, t_env *env);
void			rm_env(t_node *node);
t_env			*init_env(char **arg_env);

int		err_int(char *s, int ret);
void	*err_ptr(char *s, void *ret);
char	**splice_str(char *str, char *charset);
char		*ft_sp_merge(char **sp);


void	free_info(t_info *info);
t_info	*init_info(t_shell *shell);


#endif
