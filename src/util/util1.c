/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   util1.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: klim <klim@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/06/25 16:00:44 by klim              #+#    #+#             */
/*   Updated: 2021/06/26 18:50:19 by klim             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

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