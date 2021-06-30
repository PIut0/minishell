/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtin_utils.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sehyan <sehyan@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/06/23 19:33:27 by sehyan            #+#    #+#             */
/*   Updated: 2021/06/30 13:05:44 by sehyan           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "builtin.h"

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
			write(fd, now->value, ft_strlen(now->value));
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
