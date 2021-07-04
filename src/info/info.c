/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   info.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: klim <klim@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/06/21 17:33:52 by klim              #+#    #+#             */
/*   Updated: 2021/07/04 20:13:18 by klim             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

void	free_token(t_token *t)
{
	int		i;

	if (t->argv)
	{
		i = -1;
		while (t->argv[++i])
			free(t->argv[i]);
		free(t->argv);
	}
	if (t->data)
		free(t->data);
	free(t);
}

void	free_info(t_info *info)
{
	t_token	*tmp;
	t_token	*target;

	tmp = info->head;
	while (tmp)
	{
		target = tmp;
		tmp = tmp->next;
		free_token(target);
	}
	free(info->cmd);
	free(info);
}

t_info	*init_info(t_shell *shell)
{
	t_info	*ret;

	if (!(ret = (t_info *)malloc(sizeof(t_info))))
		return (0);
	ret->cmd = 0;
	ret->shell = shell;
	ret->head = 0;
	return (ret);
}
