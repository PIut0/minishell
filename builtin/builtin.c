/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtin.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sehyan <sehyan@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/06/21 18:12:56 by sehyan            #+#    #+#             */
/*   Updated: 2021/06/25 15:46:10 by sehyan           ###   ########.fr       */
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

int		check_flag(char *argv)
{
	int j;

	j = 1;
	while (argv[j])
	{
		if (argv[j] == 'n')
			j++;
		else
			return (0);
	}
	return (1);
}

void	m_echo(int argc, char **argv)
{
	int i;
	int j;
	int flag;
	
	i = 0;
	j = 0;
	flag = 0;
	while (argv[++i][j] == '-')
	{
		if (check_flag(argv[i]) == 1)
			flag = 1;
		else
		{
			i--;
			break;
		}
	}
	while (i < argc)
	{
		printf("%s", argv[i]);
		i++;
		if (argv[i])
			printf(" ");
	}
	if (flag == 0)
		printf("\n");
}

void	m_exec(char **argv)
{
	if(execve("/usr/bin/env", argv, NULL) == -1)
		printf("프로그램 실행 error\n");
	return ;
}

void	m_env(t_env *env)
{
	print_env(env->head);
}