/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   signal1.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: klim <klim@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/06/29 20:04:00 by klim              #+#    #+#             */
/*   Updated: 2021/06/30 13:50:34 by klim             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void		sig_sigint(int sig)
{
	g_sig = sig;
	ft_putstr_fd("\nminishell > ", 0);
	//printf("\nminishell > ");
	//printf("");
	return ;
}

void		sig_sigquit(int sig)
{
	sig = 0;
	return ;
}
