/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing2.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: klim <klim@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/06/25 16:00:29 by klim              #+#    #+#             */
/*   Updated: 2021/07/05 21:05:32 by klim             ###   ########.fr       */
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
	return ("");
}

int			open_bracket(t_token *t, char *target)
{
	if (!target || !*target)
		return (err_int("bash: No such file or directory", 1));
	if (t->token_type == _brackets)
	{
		if (t->out != STDOUT && (close(t->out)) == -1)
			exit(errno);
		if ((t->out = open(target, O_RDWR | O_CREAT | O_TRUNC, 0644)) == -1)
			exit(errno);
	}
	if (t->token_type == _d_brackets)
	{
		if (t->out != STDOUT && (close(t->out)) == -1)
			exit(errno);
		if ((t->out = open(target, O_WRONLY | O_CREAT | O_APPEND, 0644)) == -1)
			exit(errno);
	}
	if (t->token_type == _r_brackets)
	{
		if (t->in != STDIN)
			close(t->in);
		if ((t->in = open(target, O_RDONLY, 0644)) < 0)
			return (err_int("bash: No such file or directory", 1));
	}
	return (0);
}

int			join_brackets(t_token *t, int ret)
{
	t_token		*tmp;
	char		**target;

	t = t->next;
	while (t)
	{
		if (is_type_brackets(t->token_type))
		{
			tmp = t->next;
			if (!tmp || !tmp->data || !tmp->data[0])
				return (err_int("empty file name", 1));
			target = splice_str(tmp->data, WHITE_SPACE);
			ret = open_bracket(t, target[0]);
			target[0][0] = 0;
			t->data = ft_strjoin_free(t->data, ft_sp_merge2(target, " "), 3);
			t->token_type = tmp->token_type;
			t->next = tmp->next;
			free(tmp->data);
			free(tmp);
		}
		else
			t = t->next;
	}
	return (ret);
}
