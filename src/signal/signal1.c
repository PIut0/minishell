/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   signal1.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: klim <klim@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/06/29 20:04:00 by klim              #+#    #+#             */
/*   Updated: 2021/07/02 01:56:41 by klim             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void		sig_sigint(int sig)
{
	g_sig = sig;
	ft_putstr_fd("\nminishell2 > ", STDOUT);
	//printf("\nminishell > ");
	//printf("");
	return ;
}

void		child_sig(int sig)
{
	if (sig == SIGINT)
		ft_putstr_fd("\n",STDOUT);
	else
		ft_putstr_fd("QUIT: 3\n", STDOUT);
	return ;
}

void		sig_sigquit(int sig)
{
	sig = 0;
	return ;
}
