/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   info.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: klim <klim@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/06/21 17:33:52 by klim              #+#    #+#             */
/*   Updated: 2021/06/23 17:02:40 by klim             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

void	free_info(t_info *info)
{
	t_argv	*tmp;

	free(info->cmd);
	while (info->argv)
	{
		tmp = info->argv->next;
		free(info->argv);
		info->argv = tmp;
	}
	free(info);
}

t_info	*init_info(void)
{
	t_info	*ret;

	if (!(ret = (t_info *)malloc(sizeof(t_info))))
		return (0);
	ret->cmd = 0;
	if (!(ret->argv = init_argv(0)))
		return (0);
	return (ret);
}
