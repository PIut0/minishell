/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtin.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sehyan <sehyan@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/06/23 19:18:07 by sehyan            #+#    #+#             */
/*   Updated: 2021/06/23 20:09:43 by sehyan           ###   ########.fr       */
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
void	m_echo(char *s, int flag);

//builtin_utils
void	m_error(char *s);

//env
void	add_env(char *s, t_env *env);
void	init_env(char **arg_env);
void	input_env(char *s, t_node *new);

//debuging
void	print_stack(t_node *node);
#endif