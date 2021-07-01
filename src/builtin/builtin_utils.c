/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtin_utils.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: klim <klim@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/06/23 19:33:27 by sehyan            #+#    #+#             */
/*   Updated: 2021/07/02 03:40:37 by klim             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int		max(int a, int b)
{
	if (a > b)
		return (a);
	else
		return (b);
}

void	print_export(t_env *env, int fd)
{
	t_node *now;

	now = env->head->next;
	while (now != env->tail)
	{
		write(fd, now->key, ft_strlen(now->key));
		if (now->value[0])
		{
			write(fd, "=\"", 2);
			write(fd, backup_nega_char(now->value), ft_strlen(now->value));
			write(fd, "\"", 1);
		}
		write(fd, "\n", 1);
		now = now->next;
	}
}

int		check_flag(char *argv)
{
	int j;

	if (argv[0] != '-')
		return (0);
	j = 1;
	while (argv[j])
	{
		if (argv[j] == 'n')
			j++;
		else
			return (0);
	}
	return (1);
}
