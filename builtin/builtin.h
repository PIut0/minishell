/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtin.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ash <ash@student.42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/06/23 19:18:07 by sehyan            #+#    #+#             */
/*   Updated: 2021/06/25 16:16:27 by ash              ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef BUILTIN_H
# define BUILTIN_H

#include <unistd.h>
#include <stdio.h>
#include <dirent.h>
#include <stdlib.h>
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
void	m_pwd(void);
void	m_cd(char *s);
void	m_exit(void);
void	m_echo(int argc, char **argv);
int		check_flag(char *argv);

//builtin_utils
void	m_error(char *s);

//env
int		add_env(char *s, t_env *env);
void	init_env(char **arg_env);
t_node	*find_node(t_node *new);
int		check_key_val(char *key);
void	input_env(char *s, t_node *new);
void	rm_env(char *rm_key, t_env *env);

//debuging
void	print_env(t_node *node);
#endif