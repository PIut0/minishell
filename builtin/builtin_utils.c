/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtin_utils.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ash <ash@student.42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/06/23 19:33:27 by sehyan            #+#    #+#             */
/*   Updated: 2021/06/30 00:57:43 by ash              ###   ########.fr       */
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

void	print_export(t_env *env)
{
	t_node *now;

	now = env->head->next;
	while (now != env->tail)
	{
		write(1, now->key, ft_strlen(now->key));
		if (now->value[0])
		{
			write(1, "=\"", 2);
			write(1, now->value, ft_strlen(now->value));
			write(1, "\"", 1);
		}
		write(1, "\n", 1);
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

// void	*err_ptr(char *s, void *ptr)
// {
// 	printf("%s\n", s);
// 	return (ptr);
// }

// int		err_int(char *s, int ret)
// {
// 	printf("%s\n", s);
// 	return (ret);
// }