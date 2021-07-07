/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env1.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: klim <klim@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/06/25 17:36:22 by klim              #+#    #+#             */
/*   Updated: 2021/07/07 16:48:49 by klim             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

t_node	*init_node(char *s)
{
	t_node	*n;
	char	*key;
	char	*value;
	int		i;
	int		len;

	if (!(n = (t_node*)ft_calloc(sizeof(t_node), 1)))
		return ((t_node *)err_ptr("malloc err", 0));
	i = -1;
	len = ft_strlen(s);
	while (s[++i] && (s[i] != '='))
		;
	if (!(key = (char *)malloc(i + 1)) ||
		!(value = (char *)malloc(len - i + 1)))
		return ((t_node *)err_ptr("malloc err", 0));
	ft_strlcpy(key, s, i + 1);
	ft_strlcpy(value, s + i + 1, (size_t)s + len);
	if (i >= len)
	{
		free(value);
		value = 0;
	}
	n->key = key;
	n->value = value;
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
