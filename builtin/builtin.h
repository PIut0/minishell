/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtin.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sehyan <sehyan@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/06/23 19:18:07 by sehyan            #+#    #+#             */
/*   Updated: 2021/06/28 14:20:56 by sehyan           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef BUILTIN_H
# define BUILTIN_H

#include <unistd.h>
#include <stdio.h>
#include <dirent.h>
#include <stdlib.h>
#include <limits.h>
#include <fcntl.h>
#include "../include/libft.h"

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

//builtin
void	m_pwd(int fd);
void	m_cd(char *s);
void	m_exit(void);
void	m_echo(int argc, char **argv);
void	m_env(t_env *env);
void	m_unset(char *key, t_env *env);
void	m_export(int argc, char **argv, t_env *env);
void	m_exec(char **argv);

//builtin_utils
void	*err_ptr(char *s, void *ptr);
int		err_int(char *s, int ret);
int		check_flag(char *argv);
int		max(int a, int b);

//env_util1
t_node	*init_node(char *s);
t_node	*find_node(char *key, t_env *env);
int		check_key_val(t_node *node);
int		add_env(char *s, t_env *env);
void	rm_env(t_node *node);
t_env	*init_env(char **arg_env);

void	print_env(t_env *env);

//greater_sign
void	double_g_s(char *str);
#endif