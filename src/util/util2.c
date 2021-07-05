/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   util2.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: klim <klim@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/07/03 11:51:01 by klim              #+#    #+#             */
/*   Updated: 2021/07/03 13:31:34 by klim             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int		is_dir(char *argv)
{
	int		i;

	i = -1;
	while (argv[++i])
		if (argv[i] == '/')
			return (1);
	return (0);
}

int		parse_errno(int err)
{
	if ((int)err > 255)
		err = err >> 8;
	return (err);
}