/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   err_util1.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: klim <klim@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/06/25 18:18:54 by klim              #+#    #+#             */
/*   Updated: 2021/07/07 17:13:20 by klim             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int		err_int(char *s, int ret)
{
	printf("%s\n", s);
	return (ret);
}

int		err_int2(char *s, int ret)
{
	printf("%s", s);
	return (ret);
}

void	*err_ptr(char *s, void *ret)
{
	printf("%s\n", s);
	return (ret);
}

void	err_print(t_info *info)
{
	if (getpid() == info->shell->pid)
	{
		if (errno == 130 && g_signal.sig == 2)
			ft_putstr_fd("\n", STDOUT);
		if (errno == 131 && g_signal.sig == 3)
			ft_putstr_fd("Quit: 3\n", STDOUT);
	}
}

int		free_ret(void *ptr, int ret)
{
	free(ptr);
	return (ret);
}
