/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing3.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: klim <klim@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/06/25 16:01:37 by klim              #+#    #+#             */
/*   Updated: 2021/06/25 18:16:08 by klim             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

t_token		*init_token(char *data)
{
	t_token		*ret;

	if (!(ret = (t_token *)malloc(sizeof(t_token))))
		return (0);
	if (!data)
		return (0);
	ret->next = 0;
	ret->token_type = _null;
	ret->data = data;
	return (ret);
}

t_token_type	get_token(char *line, int i)
{
	if (is_quote(line, i))
		return (_null);
	if (i > 0 && line[i - 1] == BACK_SLASH)
		return (_null);
	else if (line[i] == 0)
		return (_none);
	else if (line[i] == '|')
		return (_pipe);
	else if (line[i] == '>' && line[i + 1] == '>')
		return (_d_brackets);
	else if (line[i] == '>' && line[i + 1] != '>')
		return (_brackets);
	else if (line[i] == '<' && line[i + 1] == '<')
		return (_r_brackets);
	else if (line[i] == '<' && line[i + 1] != '<')
		return (_rd_brackets);
	else if (line[i] == ';')
		return (_semicolon);
	return (_null);
}

int			add_new_token(t_token *head, char *line, int *i, int last)
{
	t_token_type	type;
	t_token			*tmp;
	t_token			*n;
	char			*data;

	tmp = head;
	type = get_token(line, *i);
	data = ft_substr(line, last, (size_t)(*i - last));
	data = remove_space(data);
	if (!(n = init_token(data)))
		return (1);
	n->token_type = type;
	if (type == _d_brackets || type == _rd_brackets)
		(*i)++;
	while (tmp->next)
		tmp = tmp->next;
	tmp->next = n;
	return (0);
}

int			parse_token(char *line, t_info *info, t_token *head, int len)
{
	int				i;
	int				last;

	i = -1;
	last = 0;
	while (++i < len)
	{
		if (get_token(line, i) != _null)
		{
			if (add_new_token(head, line, &i, last))
				return (1);
			last = i + 1;
		}
	}
	if (add_new_token(head, line, &i, last))
		return (1);
	if (join_brackets(head))
		return (1);
	//if (parse_argv(head))
	//	return (1);
	info->head = head;
	return (0);
}
