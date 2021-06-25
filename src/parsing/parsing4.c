/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing4.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: klim <klim@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/06/25 16:16:46 by klim              #+#    #+#             */
/*   Updated: 2021/06/25 19:56:30 by klim             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

//char	**split_space(char *data)
//{
//	return (&data);
//}

int		parse_argv(t_info *info, t_token *head)
{
	t_env		*env;
	t_token		*token;
	int			i;
	char		**tmp;

	env = info->shell->env;
	token = head->next;
	while (token)
	{
		token->argv = splice_space(token->data, WHITE_SPACE);
		tmp = token->argv;
		i = -1;
		while (tmp[++i])
			printf("argv: %s\n",tmp[i]);
			//tmp[i] = parse_env(tmp[i]);
		token = token->next;
	}
	return (0);
}
