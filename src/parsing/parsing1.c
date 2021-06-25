/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing1.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: klim <klim@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/06/21 15:31:30 by klim              #+#    #+#             */
/*   Updated: 2021/06/25 15:13:05 by klim             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"
#include "libft.h"

int			is_space(char c)
{
	int		i;

	i = -1;
	while (++i < 6)
	{
		if (c == WHITE_SPACE[i])
			return (1);
	}
	return (0);
}

char		get_param_split(char **str)
{
	if (**str == '"')
	{
		(*str)++;
		return ('"');
	}
	else if (**str == '\'')
	{
		(*str)++;
		return ('\'');
	}
	else
		return (' ');
}

char		*parse_param(char **line)
{
	int		i;
	int		check;
	char	*ret;
	char	c;

	c = get_param_split(line);
	i = -1;
	check = 0;
	while (!check && (*line)[++i] && (*line)[i] != c)
	{
		if (c == ' ' && ((*line)[i] == '\'' || (*line)[i] == '"'))
			check = 1;
	}
	ret = ft_substr(*line, 0, i);
	*line = (*line + i + !(check));
	return (ret);
}

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

int			is_quote(char *line, int n)
{
	int		quote;
	int		i;

	quote = 0;
	i = 0;
	while (line[i] && i < n)
	{
		if (i > 0 && line[i - 1] == BACK_SLASH)
			;
		else if (quote == 0 && line[i] == '\'')
			quote = 1;
		else if (quote == 0 && line[i] == '\"')
			quote = 2;
		else if (quote == 1 && line[i] == '\'')
			quote = 0;
		else if (quote == 2 && line[i] == '\"')
			quote = 0;
		i++;
	}
	return (quote);
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

char		*join_bs(char *str, int len)
{
	int		i;
	int		bs_cnt;
	char	*ret;

	if (!str)
		return (0);
	if (!(ret = (char *)malloc(len)))
		return (0);
	i = -1;
	bs_cnt = 0;
	while (++i < len)
	{
		if (str[i] != BACK_SLASH)
			ret[i - bs_cnt] = str[i];
		else
			bs_cnt++;
	}
	ret[i - bs_cnt] = 0;
	free(str);
	return (ret);
}

char	*remove_space(char *str)
{
	char	*t;
	size_t	i;
	size_t	end;

	if (!str)
		return (0);
	i = 0;
	while (str[i] && ft_strchr(WHITE_SPACE, str[i]))
		i++;
	end = ft_strlen(str + i);
	while (end && str[i + end - 1] && ft_strchr(WHITE_SPACE, str[i + end - 1]))
		end--;
	if (!(t = (char *)malloc(end + 1)))
		return (0);
	if (str[i + end - 1] == BACK_SLASH && ft_strchr(WHITE_SPACE, str[i + end]))
		end++;
	ft_strlcpy(t, str + i, end + 1);
	free(str);
	return (t);
}
//   abcd
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
	if (!(n = init_token(join_bs(data, (*i - last)))))
		return (1);
	n->token_type = type;
	if (type == _d_brackets || type == _rd_brackets)
		(*i)++;
	while (tmp->next)
		tmp = tmp->next;
	tmp->next = n;
	return (0);
}

int				parse_token(char *line, t_info *info, t_token *head, int len)
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
	info->head = head;
	return (0);
}

int			remove_bs(char *line, int len)
{
	int		i;
	int		count;

	i = -1;
	count = 0;
	while (++i < len)
	{
		if (i > 0 && line[i-1] == BACK_SLASH)
			;
		else if (line[i] == '\\')
		{
			line[i] = BACK_SLASH;
			count++;
		}
	}
	return (count);
}

int			parsing(char *line, t_info *info)
{
	t_token		*head;
	int			len;
	int			bs_cnt;

	len = ft_strlen(line);
	bs_cnt = remove_bs(line, len);
	if (is_quote(line, len))
		return (1);
	head = init_token("");
	if (parse_token(line, info, head, len))
		return (1);
	free(line);
	return 0;
}
