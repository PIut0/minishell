/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   history1.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: klim <klim@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/06/30 19:50:47 by klim              #+#    #+#             */
/*   Updated: 2021/07/02 20:14:39 by klim             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

t_his		*init_his(char *data)
{
	t_his		*ret;

	if (!(ret = (t_his *)malloc(sizeof(t_his))))
		return (0);
	ret->data = ft_strdup(data);
	ret->next = 0;
	ret->prev = 0;
	return (ret);
}

void		add_history(t_shell *shell, char *line)
{
	t_his		*his;

	if (line && ft_strlen(line) > 1)
	{
		his = init_his(line);
		shell->history->tail->prev->next = his;
		his->prev = shell->history->tail->prev;
		shell->history->tail->prev = his;
		his->next = shell->history->tail;
	}
	shell->history->cur = shell->history->tail;
}

t_history	*init_history(void)
{
	t_history	*ret;

	if (!(ret = (t_history *)malloc(sizeof(t_history))))
		return (0);
	ret->head = init_his("");
	ret->tail = init_his("");
	ret->head->next = ret->tail;
	ret->tail->prev = ret->head;
	ret->cur = ret->tail;
	return (ret);
}
