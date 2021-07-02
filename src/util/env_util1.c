/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env_util1.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ash <ash@student.42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/06/25 17:36:22 by klim              #+#    #+#             */
/*   Updated: 2021/07/03 00:57:09 by ash              ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

t_node	*init_node(char *s)
{
	t_node	*n;

	int i;
	int j;
	if (!(n = (t_node*)ft_calloc(sizeof(t_node), 1))
		|| !(n->key = (char *)ft_calloc(sizeof(char), ft_strlen(s)))
		|| !(n->value = (char *)ft_calloc(sizeof(char), ft_strlen(s))))
		return ((t_node *)err_ptr("malloc err", 0));
	i = -1;
	while ((s[++i] != '=') && s[i])
		n->key[i] = s[i];
	if (s[i] == '=' && n->key)
	{
		j = -1;
		while (s[++i])
			n->value[++j] = s[i];
		n->value[++j] = 0;
	}
	else
	{
		free(n->value);
		n->value = 0;

	}
	n->next = 0;
	n->prev = 0;
	return (n);
}

t_node	*find_node(char *key, t_env *env)
{
	t_node		*tmp;

	tmp = env->head->next;
	while (tmp != env->tail)
	{
		if (ft_strcmp(key, tmp->key) == 1)
			return (tmp);
		tmp = tmp->next;
	}
	return (0);
}

int		check_key_val(t_node *node)
{
	char	*key;
	int		i;

	key = node->key;
	i = 0;
	if (!ft_isalpha(key[i]) && key[i] != '_')
		return (0);
	while (key[i])
	{
		if (!ft_isalnum(key[i]) && key[i] != '_')
			return (0);
		i++;
	}
	return (1);
}

void	add_env_back(t_node *tmp, char *s)
{
	int i;
	int j;

	i = 0;
	j = ft_strlen(tmp->value);
	while (s[i])
	{
		tmp->value[j] = s[i];
		i++;
		j++;
	}
	tmp->value[j] = 0;
}

int		plus_env(t_node *n, t_env *env)
{
	t_node	*tmp;

	n->key[ft_strlen(n->key) - 1] = 0;
	if ((tmp = find_node(n->key, env)))
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
