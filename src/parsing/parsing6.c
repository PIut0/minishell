/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing6.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: klim <klim@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/07/06 16:43:39 by klim              #+#    #+#             */
/*   Updated: 2021/07/07 03:20:57 by klim             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

t_rd_in		*init_rd_in(char *target)
{
	t_rd_in		*ret;

	if (!(ret = (t_rd_in *)malloc(sizeof(t_rd_in))))
		return (0);
	ret->target = ft_strdup(target);
	ret->next = 0;
	return (ret);
}

void		add_rd_brackets(t_token *t, char *target)
{
	t_rd_in		*new;
	t_rd_in		*tmp;

	t->in = -1;
	new = init_rd_in(target);
	tmp = t->rd_in;
	while (tmp->next)
		tmp = tmp->next;
	tmp->next = new;
}
