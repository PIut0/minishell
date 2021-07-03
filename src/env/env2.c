/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env2.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sehyan <sehyan@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/07/03 13:20:05 by sehyan            #+#    #+#             */
/*   Updated: 2021/07/03 14:50:10 by sehyan           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	add_env_back(t_node *tmp, char *s)
{
	int i;
	int j;

	i = 0;
	if (tmp->value)
	{
		j = ft_strlen(tmp->value);
		while (s[i])
		{
			tmp->value[j] = s[i];
			i++;
			j++;
		}
		tmp->value[j] = 0;
	}
	else
		tmp->value = ft_strdup(s);
}

int		plus_env(t_node *n, t_env *env)
{
	t_node	*tmp;
	int		i;

	i = -1;
	while (n->key[++i])
		if (n->key[i] == '+')
			n->key[i] = 0;
	if ((tmp = find_node(n->key, env)) && n->value)
	{
		add_env_back(tmp, n->value);
	}
	else
	{
		env->tail->prev->next = n;
		n->prev = env->tail->prev;
		n->next = env->tail;
		env->tail->prev = n;
		if (!(check_key_val(n)))
		{
			rm_env(n);
			return (1);
		}
	}
	return (0);
}

int		add_env(char *s, t_env *env)
{
	t_node	*n;
	t_node	*tmp;

	n = init_node(s);
	n->next = 0;
	if (n->key[ft_strlen(n->key) - 1] == '+')
		return (plus_env(n, env));
	else if ((tmp = find_node(n->key, env)))
		rm_env(tmp);
	env->tail->prev->next = n;
	n->prev = env->tail->prev;
	n->next = env->tail;
	env->tail->prev = n;
	if (!(check_key_val(n)))
	{
		printf("minishell: export: '%s': not a valid identifier\n", s);
		errno = 1;
		rm_env(n);
		return (1);
	}
	return (0);
}

void	rm_env(t_node *node)
{
	node->next->prev = node->prev;
	node->prev->next = node->next;
	if (node->key)
		free(node->key);
	node->key = 0;
	if (node->value)
		free(node->value);
	node->value = 0;
	free(node);
	node = 0;
}

t_env	*init_env(char **arg_env)
{
	t_env	*env;
	int		i;

	i = -1;
	if (!(env = (t_env *)malloc(sizeof(t_env))))
		return ((t_env *)err_ptr("malloc error", 0));
	env->head = init_node("");
	env->tail = init_node("");
	env->head->next = env->tail;
	env->tail->prev = env->head;
	while (arg_env[++i])
		add_env(arg_env[i], env);
	return (env);
}
