/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   argv.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: klim <klim@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/06/23 16:57:57 by klim              #+#    #+#             */
/*   Updated: 2021/06/23 16:57:59 by klim             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

t_argv		*init_argv(char *data)
{
	t_argv	*new;

	if (!(new = (t_argv *)malloc(sizeof(t_argv))))
		return (0);
	new->next = 0;
	new->data = data;
	return (new);
}

int			push_argv(char *data, t_info *info)
{
	t_argv	*new;
	t_argv	*t;

	if (!(new = init_argv(data)))
		return (1);
	t = info->argv;
	while (t->next)
		t = t->next;
	t->next = new;
	return (0);
}

void		print_argv(t_argv *argv)
{
	t_argv	*t;

	t = argv->next;
	while (t)
	{
		printf("%s\n",t->data);
		t = t->next;
	}
}
