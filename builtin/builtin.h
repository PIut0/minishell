/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtin.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sehyan <sehyan@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/06/23 19:18:07 by sehyan            #+#    #+#             */
/*   Updated: 2021/06/30 13:06:45 by sehyan           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef BUILTIN_H
# define BUILTIN_H

#include "../include/minishell.h"

// typedef struct	s_node
// {
// 	struct s_node	*next;
// 	struct s_node	*prev;
// 	char			*key;
// 	char			*value;
// }				t_node;

// typedef struct	s_env
// {
// 	t_node		*head;
// 	t_node		*tail;
// }				t_env;

//builtin
void	m_pwd(int fd);
void	m_cd(char *s);
void	m_exit(void);
void	m_echo(t_token *tmp);
void	m_env(t_env *env, int fd);
void	m_unset(char *key, t_env *env);
void	m_export(char **argv, t_env *env, int fd);
void	m_exec(char **argv);

//builtin_utils
// void	*err_ptr(char *s, void *ptr);
// int		err_int(char *s, int ret);
int		check_flag(char *argv);
int		max(int a, int b);

//env_util1
// t_node	*init_node(char *s);
// t_node	*find_node(char *key, t_env *env);
// int		check_key_val(t_node *node);
// int		add_env(char *s, t_env *env);
// void	rm_env(t_node *node);
// t_env	*init_env(char **arg_env);

void	print_export(t_env *env, int fd);

//greater_sign
void	double_g_s(char *str);

//check_btin_func

#endif

