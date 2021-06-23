/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtin_utils.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sehyan <sehyan@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/06/23 19:33:27 by sehyan            #+#    #+#             */
/*   Updated: 2021/06/23 20:09:35 by sehyan           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "builtin.h"

void	print_stack(t_node *node)
{
	t_node *now;

	now = node;
	while (now)
	{
		printf(">>%s\n", now->key);
		now = now->next;
	}
	printf("\n");
}

void	m_error(char *s)
{
	printf("%s\n", s);
	exit(1);
}