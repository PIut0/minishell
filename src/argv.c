/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   argv.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: klim <klim@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/06/23 16:57:57 by klim              #+#    #+#             */
/*   Updated: 2021/06/27 16:28:57 by klim             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

void		print_token(t_token *head)
{
	t_token	*tmp;

	tmp = head->next;
	while (tmp)
	{
		print_argv(tmp->argv);
		tmp = tmp->next;
	}
}

void		print_argv(char **argv)
{
	int		i;

	i = -1;
	printf("| ");
	while (argv[++i])
		printf("%s ",argv[i]);
	printf("|\n");
}
