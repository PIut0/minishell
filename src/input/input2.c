/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   input2.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: klim <klim@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/07/02 20:13:13 by klim              #+#    #+#             */
/*   Updated: 2021/07/02 20:13:30 by klim             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

char	*reset_ret(char *ret, int *idx)
{
	*idx = 0;
	free(ret);
	ret = ft_strdup("");
	g_signal.sig = 0;
	return (ret);
}

char	*history_ret(int ch, char *ret, t_shell *shell, int *idx)
{
	int		i;
	int		len;

	if ((ch == _UP && shell->history->cur == shell->history->head)
		|| (ch == _DOWN && shell->history->cur == shell->history->tail))
		return (ret);
	i = -1;
	len = ft_strlen(ret);
	while (++i < len)
		write(0, "\b \b", 3);
	free(ret);
	if (ch == _UP)
		shell->history->cur = shell->history->cur->prev;
	else
		shell->history->cur = shell->history->cur->next;
	ret = ft_strdup(shell->history->cur->data);
	write(0, ret, ft_strlen(ret));
	*idx = ft_strlen(ret);
	return (ret);
}
