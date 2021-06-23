/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtin.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sehyan <sehyan@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/06/21 18:12:56 by sehyan            #+#    #+#             */
/*   Updated: 2021/06/23 21:57:05 by sehyan           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"
#include "builtin.h"

void	m_pwd(void)
{
	char	buf[PATH_MAX];

	if (!(getcwd(buf, sizeof(buf))))
		return ; //error
	printf("%s\n", buf);
}

void	m_cd(char *s)
{
	int result;

	result = chdir(s);
	if(result == 0)
		m_pwd();
	else
		m_error("Fail...");
}

void	m_exit(void)
{
	exit(0);
}

void	m_echo(char **s, int flag, int argc)
{
	int i;

	i = 0;
	while (++i < argc)
    	printf("%s%s", s[i], (i < argc-1) ? " " : "");
  	printf("\n");
  return ;
}

void	m_exec(char **argv)
{
	if(execve("/usr/bin/env", argv, NULL) == -1)
		printf("프로그램 실행 error\n");
	return ;
}