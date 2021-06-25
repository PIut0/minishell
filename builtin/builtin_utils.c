/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtin_utils.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sehyan <sehyan@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/06/23 19:33:27 by sehyan            #+#    #+#             */
/*   Updated: 2021/06/25 19:50:55 by sehyan           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "builtin.h"

void	print_env(t_env *env)
{
	t_node *now;

	now = env->head->next;
	while (now != env->tail)
	{
		printf("%s", now->key);
		if (now->value)
			printf("=\"%s\"", now->value);
		printf("\n");
		now = now->next;
	}
}

int		check_flag(char *argv)
{
	int j;

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

void	*err_ptr(char *s, void *ptr)
{
	printf("%s\n", s);
	return (ptr);
}

int		err_int(char *s, int ret)
{
	printf("%s\n", s);
	return (ret);
}