/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing2.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: klim <klim@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/06/25 16:00:29 by klim              #+#    #+#             */
<<<<<<< HEAD
/*   Updated: 2021/06/25 16:03:29 by klim             ###   ########.fr       */
=======
/*   Updated: 2021/06/30 13:50:18 by klim             ###   ########.fr       */
>>>>>>> klim
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

int			join_brackets(t_token *head)
{
	t_token		*tmp;
	t_token		*t;

	t = head->next;
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
				free(tmp);
			}
			if (!t->data)
				return (1);
		}
		t = t->next;
	}
	return (0);
}
