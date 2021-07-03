/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   signal1.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sehyan <sehyan@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/06/29 20:04:00 by klim              #+#    #+#             */
/*   Updated: 2021/07/03 15:10:42 by sehyan           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void		sig_sigint(int sig)
{
	g_signal.sig = sig;
	errno = 1;
	ft_putstr_fd("\nminishell > ", STDOUT);
	return ;
}

void		child_sig(int sig)
{
	dup2(g_signal.in, STDIN);
	dup2(g_signal.out, STDOUT);
	if (sig == SIGINT)
		ft_putstr_fd("\n", STDOUT);
	else
		ft_putstr_fd("Quit: 3\n", STDOUT);
	return ;
}

void		sig_sigquit(int sig)
{
	sig = 0;
	return ;
}
