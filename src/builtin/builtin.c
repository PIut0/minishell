/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtin.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: klim <klim@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/06/21 18:12:56 by sehyan            #+#    #+#             */
/*   Updated: 2021/07/01 16:48:18 by klim             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	m_pwd(int fd)
{
	char	buf[PATH_MAX];
	pid_t	pid_pwd;
	int		status;

	if ((pid_pwd = fork()) < 0)
		exit(1);
	else if (pid_pwd == 0)
	{
		if (!(getcwd(buf, sizeof(buf))))
			return; //error
		write(fd, buf, ft_strlen(buf));
		write(fd, "\n", 1);
		exit(0);
	}
	else
		if (waitpid(pid_pwd, &status, 0) < 0)
			err_ptr("error\n", 0);
}

int		m_cd(char *s, t_info *info)
{
	int result;

	if (!s)
	{
		if (!find_node("HOME", info->shell->env))
			return (err_int("cd: HOME not set", 1));
		s = find_node("HOME", info->shell->env)->value;
	}
	result = chdir(s);
	if (result == 0)
		return (0);
	else
		return err_int("fail", 1);
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

void	do_echo(int i, int check, t_token *tmp, int flag)
{
	while (tmp->argv[++i])
	{
		if (is_bracket(tmp->argv[i]))
		{
			if (!tmp->argv[++i])
				break;
			continue ;
		}
		if (!check && check_flag(tmp->argv[i]))
			flag = 1;
		else
			check = 1;
		if (check && tmp->argv[i])
		{
			ft_putstr_fd(backup_nega_char(tmp->argv[i]), tmp->out);
			if (tmp->argv[i + 1])
				write(tmp->out, " ", 1);
		}
	}
	if (flag == 0)
		write(tmp->out, "\n", 1);
	exit(0);
}

void	m_echo(t_token *tmp)
{
	pid_t	pid_pwd;
	int		status;

	if ((pid_pwd = fork()) < 0)
		err_ptr("fork error\n", 0);
	else if (!pid_pwd)
	{
		if (tmp->out == 0)
			tmp->out = 1;
		if (!tmp->argv[1])
		{
			write(tmp->out, "\n", 1);
			exit(1);
		}
		do_echo(0, 0, tmp, 0);
	}
	else
		if (waitpid(pid_pwd, &status, 0) < 0)
			err_ptr("wait error\n", 0);
}

void	m_env(t_env *env, int fd)
{
	pid_t	pid_pwd;
	int		status;

	if ((pid_pwd = fork()) < 0)
		exit(1);
	else if (pid_pwd == 0)
	{
		print_env(env, fd);
		exit(0);
	}
	else
		if (waitpid(pid_pwd, &status, 0) < 0)
			err_ptr("error\n", 0);
}

void	m_unset(char **argv, t_env *env)
{

	int		i;
	t_node	*n;
	char	*key;

	i = 0;
	if (!argv[1])
		return ;
	while (argv[++i])
	{
		key = argv[i];
		if (!key[0])
			continue ;
		n = find_node(key, env);
		if (!n)
			continue ;
		rm_env(n);
	}
	return ;
}

void	m_export(char **argv, t_env *env, int fd)
{
	int i;
	// t_node *tmp;

	i = 0;
	// printf("test3: %p\n",env->tail);
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
