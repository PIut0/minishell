/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ash <ash@student.42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/06/23 19:26:41 by sehyan            #+#    #+#             */
/*   Updated: 2021/06/25 16:20:07 by ash              ###   ########.fr       */
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
		if (ft_isalpha(key[i]) == 0 || ft_isalnum(key[i]) == 0)
			return (0);
		i++;
	}
	return (1);
}

int		add_env(char *s, t_env *env)
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
	if (!(check_key_val(new)))
	{
		rm_env(new->key, env);
		return (0);
	}
	return (1);
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
}

int main(int argc, char *argv[], char **env)
{
	char *line;

	init_env(env);
	while (1)
	{
		ft_putstr_fd("minishell > ", 1);
		int cmd;
		scanf("%d", &cmd);
		if (cmd == 1)
		{
			printf()
		}
		//printf("%s\n",info->cmd);
	}
	return (0);
}