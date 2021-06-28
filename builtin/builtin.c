/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtin.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sehyan <sehyan@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/06/21 18:12:56 by sehyan            #+#    #+#             */
/*   Updated: 2021/06/28 22:28:27 by sehyan           ###   ########.fr       */
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

int		is_bracket(char *argv)
{
	if (ft_strcmp(argv, ">") ||
		ft_strcmp(argv, ">>") ||
		ft_strcmp(argv, "<") ||
		ft_strcmp(argv, "<<"))
		return (1);
	return (0);
}

void	m_echo(t_token *tmp)
{
	int i;
	int j;
	int check;
	int flag;

	i = 0;
	j = 0;
	check = 0;
	flag = 0;
	if (tmp->fd == 0)
		tmp->fd = 1;
	if (!tmp->argv[1])
	{
		write(1, "\n", 1);
		return ;
	}
	while (tmp->argv[++i])
	{
		if (is_bracket(tmp->argv[i]))
		{
			// printf("test2: %s\n",tmp->argv[i]);
			if (tmp->argv[++i])
				++i;
			if (!tmp->argv[i])
				break ;
		}
		if (!check && check_flag(tmp->argv[i]))
			flag = 1;
		else
			check = 1;
		if (check && tmp->argv[i])
		{
			ft_putstr_fd(tmp->argv[i], tmp->fd);
			if (tmp->argv[i + 1])
				write(tmp->fd, " ", 1);
		}
	}
	// while (tmp->argv[++i][j] == '-')
	// {
	// 	if (check_flag(tmp->argv[i]) == 1)
	// 		flag = 1;
	// 	else
	// 	{
	// 		// i--;
	// 		break;
	// 	}
	// }
	if (flag == 0)
		write(tmp->fd, "\n", 1);
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