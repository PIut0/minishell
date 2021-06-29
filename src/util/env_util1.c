/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env_util1.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ash <ash@student.42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/06/25 17:36:22 by klim              #+#    #+#             */
/*   Updated: 2021/06/30 00:56:11 by ash              ###   ########.fr       */
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
	if (s[i] == '=')
	{
		j = 0;
		while (s[++i])
		{
			n->value[j] = s[i];
			j++;
		}
	}
	// else if (s[i] == '+')
	// {
	
	// }
	else
		n->value = 0;
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
		if (ft_strncmp(tmp->key, key, ft_strlen(tmp->key)) == 0)
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
	if ((ft_isalpha(key[0]) == 0) && key[0] != '_')
		return (0);
	while (key[i])
	{
		if ((ft_isalpha(key[i]) == 0 || ft_isalnum(key[i]) == 0)
				&& key[0] != '_')
			return (0);
		i++;
	}
	return (1);
}
int		add_env(char *s, t_env *env)
{
	t_node	*n;

	if (!(n = (t_node *)malloc(sizeof(t_node))))
		return (err_int("malloc error", 1));
	n = init_node(s);
	env->tail->prev->next = n;
	n->prev = env->tail->prev;
	n->next = env->tail;
	env->tail->prev = n;
	if (!(check_key_val(n)))
	{
		rm_env(n);
		return (1);
	}
	return (0);
}

void	rm_env(t_node *node)
{
	node->next->prev = node->prev;
	node->prev->next = node->next;
	free(node->key);
	free(node->value);
	free(node);
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
