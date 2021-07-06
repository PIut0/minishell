/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   signal1.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: klim <klim@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/06/29 20:04:00 by klim              #+#    #+#             */
/*   Updated: 2021/07/07 05:07:54 by klim             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void		sig_sigint(int sig)
{
	g_signal.sig = sig;
	dup3(g_signal.in, STDIN);
	dup3(g_signal.out, STDOUT);
	errno = 1;
	ft_putstr_fd("\nminishell > ", STDOUT);
	return ;
}

void		sig_sigquit(int sig)
{
	g_signal.sig = sig;
	return ;
}

void		child_sig(int sig)
{
	g_signal.sig = sig;
}

void		db_sigint(int sig)
{
	g_signal.sig = sig;
	dup3(g_signal.in, STDIN);
	dup3(g_signal.out, STDOUT);
	errno = 1;
	exit(errno);
	return ;
}

void		sig_newline(int sig)
{
	ft_putstr_fd("\b\b  \b\b", STDOUT);
	if (sig == SIGINT)
		ft_putstr_fd("\n", STDOUT);
	g_signal.sig = sig;
}
