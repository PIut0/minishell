/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env1.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sehyan <sehyan@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/06/25 17:36:22 by klim              #+#    #+#             */
/*   Updated: 2021/07/03 13:22:01 by sehyan           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

t_node	*init_node(char *s)
{
	t_node	*n;
	int		i;
	int		j;

	if (!(n = (t_node*)ft_calloc(sizeof(t_node), 1))
		|| !(n->key = (char *)ft_calloc(sizeof(char), ft_strlen(s)))
		|| !(n->value = (char *)ft_calloc(sizeof(char), ft_strlen(s))))
		return ((t_node *)err_ptr("malloc err", 0));
	i = -1;
	while ((s[++i] != '=') && s[i])
		n->key[i] = s[i];
	j = -1;
	if (s[i] == '=' && n->key)
	{
		while (s[++i])
			n->value[++j] = s[i];
		n->value[++j] = 0;
	}
	else
	{
		free(n->value);
		n->value = 0;
	}
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
