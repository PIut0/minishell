/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   process1.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: klim <klim@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/06/27 15:17:14 by klim              #+#    #+#             */
/*   Updated: 2021/07/01 16:57:23 by klim             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int		check_builtin(char *argv)
{
	int		len;

	len = ft_strlen(argv);
	if (!len)
		return (0);
	if (!ft_strncmp(argv, "echo", len) ||
		!ft_strncmp(argv, "cd", len) ||
		!ft_strncmp(argv, "pwd", len) ||
		!ft_strncmp(argv, "export", len) ||
		!ft_strncmp(argv, "unset", len) ||
		!ft_strncmp(argv, "env", len) ||
		!ft_strncmp(argv, "exit", len))
		return (1);
	return (0);
}

int		process_info(t_info *info)
{
	int		i;
	t_token	*tmp;

	tmp = info->head->next;
	while (tmp)
	{
		if (!(tmp->argv) || !(tmp->argv[0]))
			;
		else if (check_builtin(tmp->argv[0]))
		{
			i = -1;
			while (tmp->argv[++i])
				tmp->argv[i] = parse_data(tmp->argv[i], info);
			check_btin_func(tmp, info);
		}
		else
		{
			i = -1;
			while (tmp->argv[++i])
				backup_bs(tmp->argv[i], ft_strlen(tmp->argv[i]));
			check_func(tmp, info);
		}
		tmp = tmp->next;
	}
	return (0);
}
