/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sehyan <sehyan@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/06/21 14:20:02 by klim              #+#    #+#             */
/*   Updated: 2021/07/03 15:56:47 by sehyan           ###   ########.fr       */
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

typedef struct termios	t_term;

typedef enum			e_token_type
{
	_null,
	_none,
	_pipe,
	_brackets,
	_r_brackets,
	_d_brackets,
	_rd_brackets,
	_semicolon
}						t_token_type;

typedef struct			s_node
{
	struct s_node		*next;
	struct s_node		*prev;
	char				*key;
	char				*value;
}						t_node;

typedef struct			s_env
{
	t_node				*head;
	t_node				*tail;
}						t_env;

typedef struct			s_his
{
	char				*data;
	struct s_his		*next;
	struct s_his		*prev;
}						t_his;

typedef struct			s_history
{
	t_his				*head;
	t_his				*tail;
	t_his				*cur;
}						t_history;
typedef	struct			s_shell
{
	t_env				*env;
	t_history			*history;
	char				*home;
	int					std_in;
	int					std_out;
}						t_shell;

typedef	struct			s_token
{
	char				*data;
	char				**argv;
	t_token_type		token_type;
	int					in;
	int					out;
	struct s_token		*next;
}						t_token;

typedef struct			s_sig
{
	int					in;
	int					out;
	int					sig;
}						t_sig;

typedef	struct			s_info
{
	char				*cmd;
	t_token				*head;
	t_shell				*shell;
}						t_info;

/*
**		builtin
*/
int						max(int a, int b);
void					print_env(t_env *env, int fd);
void					print_export(t_env *env, int fd);
int						check_flag(char *argv);

int						m_pwd(int fd);
int						m_cd(char *s, t_info *info);
int						m_exit(t_token *tmp, t_info *info);
int						m_env(t_env *env, int fd);
int						is_bracket(char *argv);
void					do_echo(int i, int check, t_token *tmp, int flag);
int						m_echo(t_token *tmp);
int						m_unset(char **argv, t_env *env);
int						m_export(char **argv, t_env *env, int fd);

int						check_btin_func(t_token *tmp, t_info *info);
char					*get_keyvalue(t_node *t);
char					**get_char_env(t_env *env);
int						check_func(t_token *tmp, t_info *info, int i);

char					**sort_key(char **env_s, int n);
char					**sort_str(char **env_s);

/*
**		env
*/
t_node					*init_node(char *s);
t_node					*find_node(char *key, t_env *env);
int						check_key_val(t_node *node);
void					add_env_back(t_node *tmp, char *s);
int						plus_env(t_node *n, t_env *env);
int						add_env(char *s, t_env *env);
void					rm_env(t_node *node);
t_env					*init_env(char **arg_env);

/*
**		gnl
*/
int						get_next_line(int fd, char **line);

/*
**		history
*/
t_his					*init_his(char *data);
void					add_history(t_shell *shell, char *line);
t_history				*init_history(void);

/*
**		info
*/
void					free_token(t_token *t);
void					free_info(t_info *info);
t_info					*init_info(t_shell *shell);

/*
**		input
*/
char					*add_char(char *str, int c);
char					*get_input(int idx, int ch, char *ret, t_shell *shell);
char					*get_line(t_shell *shell);

char					*reset_ret(char *ret, int *idx);
char					*history_ret(int ch, char *ret,
									t_shell *shell, int *idx);

/*
**		libft_ref
*/
int						ft_atoi2(const char *str);

char					*ft_strjoin_free(char *s1, char *s2, int n);
char					*ft_sp_merge(char **sp);
char					*ft_sp_merge2(char **sp, char *c);
int						ft_strcmp(char *s1, char *s2);

/*
**		parsing
*/
char					*backup_bs(char *line, int len);
char					*backup_nega_char(char *data);
char					*backup_data(char *data, t_info *info);

char					*replace_bs(char *line, int len);
char					*remove_space(char *str);
int						parsing(char *line, t_info *info);

int						is_type_brackets(t_token_type t);
char					*get_brackets(t_token_type t);
int						open_bracket(t_token *t, char *target);
int						join_brackets(t_token *t, int ret);

t_token					*init_token(char *data);
t_token_type			get_token(char *line, int i);
int						add_new_token(t_token *head,
									char *line, int *i, int last);
int						parse_token(char *line,
									t_info *info, t_token *head, int len);

char					*change_key_to_value(char *argv, int *i,
						int env_len, t_info *info);
int						get_env_len(char *argv, int i);
char					*replace_home(char *argv, t_info *info);
char					*parse_data(char *argv, t_info *info);
int						parse_argv(t_info *info, t_token *head);

char					*replace_env(char *argv, t_info *info);
char					*change_nega_char(char *argv);
char					*remove_quote(char *str);
char					*change_dq_edq(char *str, int key);
char					*remove_bs(char *str);

/*
**		process
*/
int						check_builtin(char *argv);
int						process_tmp(t_info *info, t_token *tmp);
int						get_pipe(void);
int						process_info(t_info *info, int is_child, int pid);

/*
**		signal
*/
void					sig_sigint(int sig);
void					child_sig(int sig);
void					sig_sigquit(int sig);

/*
**		util
*/
int						err_int(char *s, int ret);
void					*err_ptr(char *s, void *ret);

int						is_char_set(char *str, char *charset, char *start);
int						b_c(char *str, char *charset);
void					ft_strcpy(char *dest, char *from, char *to);
char					**splice_str(char *str, char *charset);

int						is_space(char c);
int						is_quote(char *line, int n);
char					*get_pid(void);
char					*get_errno(void);
int						open_file(char *s, int flag);

int						is_dir(char *argv);
int						parse_errno(int err);

t_sig					g_signal;

#endif
