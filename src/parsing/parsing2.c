/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing2.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: klim <klim@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/06/25 16:00:29 by klim              #+#    #+#             */
/*   Updated: 2021/07/07 17:21:16 by klim             ###   ########.fr       */
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

int			open_bracket(t_token *t, char *target, t_info *info)
{
	if (!target || !*target)
		return (err_int("minishell: syntax error", 1));
	if (t->token_type == _brackets || t->token_type == _d_brackets)
	{
		target = parse_data(target, info);
		if (t->out != STDOUT && (close(t->out)) == -1)
			exit(errno);
		if ((t->out = open_file(target, t->token_type)) == -1)
			return (err_int(strerror(errno),
				err_int2("minishell: ", free_ret(target, 1))));
	}
	else if (t->token_type == _r_brackets)
	{
		target = parse_data(target, info);
		if (t->in != STDIN && t->in > 0 && (close(t->in)) == -1)
			exit(errno);
		if ((t->in = open(target, O_RDONLY, 0644)) < 0)
			return (err_int(strerror(errno),
				err_int2("minishell: ", free_ret(target, 1))));
	}
	else if (t->token_type == _rd_brackets)
		add_rd_brackets(t, target);
	free(target);
	return (0);
}

int			join_brackets(t_token *t, int ret, t_info *info)
{
	t_token		*tmp;
	char		**target;

	t = t->next;
	while (t)
	{
		if (!ret && is_type_brackets(t->token_type))
		{
			tmp = t->next;
			if (!tmp || !tmp->data || !tmp->data[0])
				return (err_int("minishell: empty file name", 1));
			target = splice_str(tmp->data, WHITE_SPACE);
			ret = open_bracket(t, ft_strdup(target[0]), info);
			target[0][0] = 0;
			t->data = ft_strjoin_free(t->data, ft_sp_merge2(target, " "), 3);
			t->token_type = tmp->token_type;
			t->next = tmp->next;
			free_token(tmp);
		}
		else
			t = t->next;
	}
	return (ret);
}
