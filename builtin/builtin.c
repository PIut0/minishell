/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtin.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: klim <klim@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/06/21 18:12:56 by sehyan            #+#    #+#             */
/*   Updated: 2021/06/30 21:27:23 by klim             ###   ########.fr       */
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
	printf("bye!\n");
	kill(getppid(), SIGTERM);
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
			ft_putstr_fd(backup_nega_char(tmp->argv[i]), tmp->fd);
			if (tmp->argv[i + 1])
				write(tmp->fd, " ", 1);
		}
	}
	if (flag == 0)
		write(tmp->fd, "\n", 1);
}

void	m_env(t_env *env, int fd)
{
	print_env(env, fd);
}

void	m_unset(char *key, t_env *env)
{
	t_node *n;

	if (!key)
		return ;
	n = find_node(key, env);
	if (!n)
		return ;
	rm_env(n);
}

void	m_export(char **argv, t_env *env, int fd)
{
	int i;
	// t_node *tmp;

	i = 0;
	printf("test3: %p\n",env->tail);
	if (!argv[1])
		print_export(env, fd);
	while (argv[++i])
	{
		if (is_bracket(argv[i]))
		{
			print_export(env, fd);
			break ;
		}
		add_env(argv[i], env);
	}
}
