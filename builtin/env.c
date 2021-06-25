/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sehyan <sehyan@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/06/23 19:26:41 by sehyan            #+#    #+#             */
/*   Updated: 2021/06/25 13:16:09 by sehyan           ###   ########.fr       */
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
		new->key[i] = s[i];
	j = 0;
	while (s[++i])
	{
		new->value[j] = s[i];
		j++;
	}
}

t_node	*find_node(t_node *new)
{
	char *str;

	if (!(str = (char *)malloc(sizeof(char) * ft_strlen(new->key))))
		m_error("malloc error");
	str = ft_strlcpy(str, new->key, ft_strlen(new->key));
	//위로 올라가면서 찾기?
	while (new->prev)
	{
		if (ft_strncmp(str, new->key, ft_strlen(str)))
		{
			free(str);
			return (new);
		}
		new = new->prev;
	}
	return (0);
}

void	plus_value(t_node *new)
{
	char	*val;
	t_node	*node;

	if (!(val = (char *)malloc(sizeof(char) * ft_strlen(new->value))))
		m_error("malloc error");
	val = ft_strlcpy(val, new->value, ft_strlen(new->value));
	node = find_node(new);
	node->value = ft_strjoin(node->value, val); //free 문제
}

int		check_key_val(char *key)
{
	int i;

	i = 0;
	if (ft_isalpha(key[0]) == 0)
		return (0);
	while (key[i])
	{
		if (!(('A' <= key[i] && key[i] <= 'Z')
				|| ('a' <= key[i] && key[i] <= 'z')
				|| ('0' <= key[i] && key[i] <= '9'))
				&& key[i] != '+')
			return (0);
		// if (key[i] == '+' && i == ft_strlen(key))
		// 	plus_value(new);
		i++;
	}
	return (1);
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
	check_key_val(new);
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