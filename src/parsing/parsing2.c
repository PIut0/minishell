/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing2.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: klim <klim@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/06/25 16:00:29 by klim              #+#    #+#             */
/*   Updated: 2021/07/01 16:55:34 by klim             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int			is_type_brackets(t_token_type t)
{
	if (t == _brackets || t == _r_brackets
		|| t == _d_brackets || t == _rd_brackets)
		return (1);
	return (0);
}

char		*get_brackets(t_token_type t)
{
	if (t == _brackets)
		return (">");
	else if (t == _r_brackets)
		return ("<");
	else if (t == _d_brackets)
		return (">>");
	else if (t == _rd_brackets)
		return ("<<");
	return ("");
}

int			join_brackets(t_token *t)
{
	t_token		*tmp;

	t = t->next;
	while (t)
	{
		if (is_type_brackets(t->token_type))
		{
			tmp = t->next;
			t->data = ft_strjoin_free(t->data, " ", 1);
			t->data = ft_strjoin_free(t->data, get_brackets(t->token_type), 1);
			if (tmp)
			{
				t->data = ft_strjoin_free(t->data, " ", 1);
				t->data = ft_strjoin_free(t->data, tmp->data, 3);
				t->next = tmp->next;
				t->token_type = tmp->token_type;
				free(tmp);
			}
			if (!t->data)
				return (1);
		}
		else
			t = t->next;
	}
	return (0);
}
