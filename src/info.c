/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   info.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: klim <klim@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/06/21 17:33:52 by klim              #+#    #+#             */
/*   Updated: 2021/07/01 16:58:02 by klim             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

void	free_info(t_info *info)
{
	t_token	*tmp;

	while (info->head)
	{
		tmp = info->head->next;
		free(info->head);
		info->head = tmp;
	}
	free(info);
}

t_info	*init_info(t_shell *shell)
{
	t_info	*ret;

	if (!(ret = (t_info *)malloc(sizeof(t_info))))
		return (0);
	ret->cmd = 0;
	ret->shell = shell;
	return (ret);
}
