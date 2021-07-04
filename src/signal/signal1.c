/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   signal1.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: klim <klim@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/06/29 20:04:00 by klim              #+#    #+#             */
/*   Updated: 2021/07/04 21:20:27 by klim             ###   ########.fr       */
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
	g_signal.sig = sig;
}

void		sig_sigquit(int sig)
{
	g_signal.sig = sig;
	return ;
}
