/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing1.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: klim <klim@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/06/21 15:31:30 by klim              #+#    #+#             */
/*   Updated: 2021/06/23 16:57:26 by klim             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"
#include "../include/libft.h"

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

char		*remove_space(char *line)
{
	while (is_space(*line))
		line++;
	return (line);
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

t_token		*init_token()
{
	t_token		*ret;

	if (!(ret = (t_token *)malloc(sizeof(t_token))))
		return (0);
	ret->next = 0;
	ret->token_type = null;
}

int			parsing(char *line, t_info *info)
{
	t_token		*head;
	int			i;
	int			len;

	head = init_token();
	i = 0;
	len = ft_strlen(line);
	while (i < len)
	{

		line = remove_space(line);
		if (push_node(parse_param(&line), info))
			return (1);
		line = remove_space(line);
	}
	free(line);
	return 0;
}

//	> echo "test"
