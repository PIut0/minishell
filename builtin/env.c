/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ash <ash@student.42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/06/23 19:26:41 by sehyan            #+#    #+#             */
/*   Updated: 2021/06/24 17:33:55 by ash              ###   ########.fr       */
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

t_node	*find(t_node *new)
{
	char *str;
	char *val;

	if (!(str = (char *)malloc(sizeof(char) * ft_strlen(new->key))))
		m_error("malloc error");
	if (!(val = (char *)malloc(sizeof(char) * ft_strlen(new->value))))
		m_error("malloc error");
	str = ft_strlcpy(str, new->key, ft_strlen(new->key));
	val = ft_strlcpy(val, new->value, ft_strlen(new->value));
	//위로 올라가면서 찾기?
	while (new->prev)
	{
		if (ft_strncmp(str, new->key, ft_strlen(str)))
			return (new);
		new = new->prev;
	}
}

void	plus_value(t_node *new)
{
	//new의 키와 같은 값을 가진 node를 찾아서, 
	// 그 node의 value 뒤에 new의 value붙여넣기.
}

void	check_key_val(t_node *new)
{
	int i;

	i = 0;
	if (ft_isalpha(new->key[0]) == 0)
		//error, 오류 출력 후 shell 로 돌아가야함
	while (new->key[i])
	{
		if (!(('A' <= new->key[i] && new->key[i] <= 'Z')
				|| ('a' <= new->key[i] && new->key[i] <= 'z')
				|| ('0' <= new->key[i] && new->key[i] <= '9'))
				&& new->key[i] != '+')
			//error, 오류 출력 후 shell로 돌아가야함.
		if (new->key[i] == '+' && i == ft_strlen(new->key))
			plus_value(new);
		i++;
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