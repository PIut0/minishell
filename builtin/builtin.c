/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtin.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sehyan <sehyan@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/06/21 18:12:56 by sehyan            #+#    #+#             */
/*   Updated: 2021/06/28 20:25:18 by sehyan           ###   ########.fr       */
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
	write(fd, "\n", 1);
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

void	m_echo(char **argv)
{
	int i;
	int j;
	int flag;

	i = 0;
	j = 0;
	flag = 0;
	if (!argv[1])
	{
		write(1, "\n", 1);
		return ;
	}
	while (argv[++i][j] == '-')
	{
		if (check_flag(argv[i]) == 1)
			flag = 1;
		else
		{
			// i--;
			break;
		}
	}
	while (argv[i])
	{	
		ft_putstr_fd(argv[i], 1);
		i++;
		if (argv[i])
			write(1, " ", 1);
	}
	if (flag == 0)
		write(1, "\n", 1);
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

void	m_export(char **argv, t_env *env)
{
	int i;

	i = 0;
	if (!argv[1])
		print_export(env);
	while (argv[++i])
	{
		add_env(argv[i], env);
	}
}