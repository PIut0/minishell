/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ash <ash@student.42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/06/21 14:20:02 by klim              #+#    #+#             */
/*   Updated: 2021/07/03 00:57:17 by ash              ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_H
# define MINISHELL_H

# include <unistd.h>
# include <stdio.h>
# include <stdlib.h>
# include <dirent.h>
# include <limits.h>
# include <fcntl.h>
# include <errno.h>
# include <termios.h>
# include <signal.h>
# include "libft.h"

# define WHITE_SPACE " \t\n\v\f\b"
# define BACK_SLASH -1
# define ENV_D_QUOTE -2
# define NEGATIVE_CHAR "><~"

# define STDIN 0
# define STDOUT 1
# define STDERR 2

# define _UP 4283163
# define _DOWN 4348699
# define _LEFT 4479771
# define _RIGHT 4414235

char				**g_env;
typedef struct		termios	t_term;

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

typedef struct	s_sig
{
	int			in;
	int			out;
	int			sig;
}				t_sig;

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

typedef struct	s_his
{
	char			*data;
	struct s_his	*next;
	struct s_his	*prev;
}				t_his;

typedef struct	s_history
{
	t_his		*head;
	t_his		*tail;
	t_his		*cur;
}				t_history;
typedef	struct		s_shell
{
	t_env			*env;
	t_history		*history;
	char			*home;
	int				_stdin;
	int				_stdout;
}					t_shell;

typedef	struct		s_token
{
	char			*data;
	char			**argv;
	t_token_type	token_type;
	int				in;
	int				out;
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
char			*parse_data(char *argv, t_info *info);
char			*replace_env(char *argv, t_info *info);
char			*remove_quote(char *str);
char			*change_dq_edq(char *str, int key);
char			*remove_bs(char *str);
char			*backup_nega_char(char *data);
char			*backup_data(char *data, t_info *info);

int				process_info(t_info *info);

void			print_token(t_token *head);
void			print_argv(char **argv);

t_node			*init_node(char *s);
t_node			*find_node(char *key, t_env *env);
int				check_key_val(t_node *node);
int				add_env(char *s, t_env *env);
void			rm_env(t_node *node);
t_env			*init_env(char **arg_env);

int				err_int(char *s, int ret);
void			*err_ptr(char *s, void *ret);
char			**splice_str(char *str, char *charset);
char			*ft_sp_merge(char **sp);
char			*ft_sp_merge2(char **sp, char *c);
int				ft_strcmp(char *s1, char *s2);

char			*get_line(t_shell *shell);
void			sig_sigint(int sig);
void			sig_sigquit(int sig);
void			child_sig(int sig);


void			free_info(t_info *info);
t_info			*init_info(t_shell *shell);

t_history		*init_history();
t_his			*init_his(char *data);
void			add_history(t_shell *shell, char *line);

int				check_bracket(t_token *tmp);
int				check_btin_func(t_token *tmp, t_info *info);
void			check_func(t_token *tmp, t_info *info, int c);
char			**get_char_env(t_env *env);
char			*get_keyvalue(t_node *t);

char			**sort_str(char **env_s);
char			**sort_key(char **env_s, int n);

void			print_env(t_env *env, int fd);
void			do_echo(int i, int check, t_token *tmp, int flag);
int				is_bracket(char *argv);
void			m_pwd(int fd);
int				m_cd(char *s, t_info *info);
void			m_exit(t_token *tmp);
void			m_echo(t_token *tmp);
void			m_env(t_env *env, int fd);
void			m_unset(char **argv, t_env *env);
void			m_export(char **argv, t_env *env, int fd);

int				check_flag(char *argv);
int				max(int a, int b);
void			print_export(t_env *env, int fd);
void			double_g_s(char *str);
t_sig			g_signal;

#endif
