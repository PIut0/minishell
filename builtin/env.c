/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sehyan <sehyan@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/06/23 19:26:41 by sehyan            #+#    #+#             */
/*   Updated: 2021/06/23 21:56:48 by sehyan           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "builtin.h"

void	input_env(char *s, t_node *new)
{
	int i;
	int j;

	if (!(new->key = (char *)ft_calloc(sizeof(char), ft_strlen(s)))
		|| !(new->value = (char *)ft_calloc(sizeof(char), ft_strlen(s))))
		m_error("malloc error");
	i = -1;
	while (s[++i] != '=')
	{
		new->key[i] = s[i];
	}
	j = 0;
	while (s[++i])
	{
		new->value[j] = s[i];
		j++;
	}
}

void	add_env(char *s, t_env *env)
{
	t_node	*new;

	if (!(new = (t_node *)malloc(sizeof(t_node))))
		m_error("malloc error");
	input_env(s, new);
	if (env->head == NULL)
	{
		env->head = new;
		env->head->prev = NULL;
		env->tail = new;
		env->tail->next = NULL;
	}
	else
	{
		env->tail->next = new;
		new->prev = env->tail;
		env->tail = new;
		env->tail->next = NULL;
	}
}

void	rm_env(char *rm_key, t_env *env)
{
	t_node	*node;

	node = env->head;	
	while (node)
	{
		if (ft_strncmp(rm_key, node->key, ft_strlen(rm_key)) == 0)
		{
			if (node->prev)
				node->prev->next = node->next;
			if (node->next)
				node->next->prev = node->prev;
			else
				env->tail = node->prev;
			node->next = NULL;
			node->prev = NULL;
			free(node->key);
			free(node->value);
			return ;
		}
		node = node->next;
	}
}

void	init_env(char **arg_env)
{
	t_env	*env;
	int		i;

	i = 0;
	if (!(env = (t_env *)malloc(sizeof(t_env))))
		m_error("malloc error");
	env->head = NULL;
	env->tail = NULL;
	while (arg_env[i])
	{
		add_env(arg_env[i], env);
		i++;
	}
	// add_env("HELLO=hello my world", env);
	// printf("==== %s=====\n", env->tail->key);
	// rm_env("HELLO", env);
	// printf("----%s----\n", env->tail->key);
	// print_stack(env->head);
}

int main(int argc, char *argv[], char **env)
{
	char *line;

	init_env(env);
	while (1)
	{
		ft_putstr_fd("minishell > ", 1);
		// get_next_line(0, &line);

		if(execve("/usr/bin/env", argv, NULL) == -1) {
			printf("프로그램 실행 error\n"); 
		}
		//printf("%s\n",info->cmd);
	}
	return (0);
}