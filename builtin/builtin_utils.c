/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtin_utils.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ash <ash@student.42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/06/23 19:33:27 by sehyan            #+#    #+#             */
/*   Updated: 2021/06/24 16:39:55 by ash              ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "builtin.h"

void	print_env(t_node *node)
{
	t_node *now;

	now = node;
	while (now)
	{
		printf("%s", now->key);
		printf("\"%s\"\n", now->value);
		now = now->next;
	}
	printf("\n");
}

void	m_error(char *s)
{
	printf("%s\n", s);
	exit(1);
}