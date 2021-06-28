/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtin.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sehyan <sehyan@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/06/21 18:12:56 by sehyan            #+#    #+#             */
/*   Updated: 2021/06/28 14:24:59 by sehyan           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"
#include "builtin.h"

void	m_pwd(int fd)
{
	char	buf[PATH_MAX];

	if (!(getcwd(buf, sizeof(buf))))
		return ; //error
	write(fd, buf, ft_strlen(buf));
}

void	m_cd(char *s)
{
	int result;

	result = chdir(s);
	if(result == 0)
		;
	else
		err_int("fail", 0);
}

void	m_exit(void)
{
	exit(0);
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
}

void	m_env(t_env *env)
{
	print_env(env);
}

void	m_unset(char *key, t_env *env)
{
	t_node *n;

	n = find_node(key, env);
	rm_env(n);
}

void	m_export(int argc, char **argv, t_env *env)
{
	int i;

	i = 1;
	while (++i < argc)
	{
		add_env(argv[i], env);
	}
}