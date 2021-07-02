/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtin.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sehyan <sehyan@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/06/21 18:12:56 by sehyan            #+#    #+#             */
/*   Updated: 2021/07/02 12:55:11 by sehyan           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	m_pwd(int fd)
{
	char	buf[PATH_MAX];

	if (!(getcwd(buf, sizeof(buf))))
		return; //error
	write(fd, buf, ft_strlen(buf));
	write(fd, "\n", 1);
	return ;
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

void	m_exit(t_token *tmp)
{
	printf("exit\n");
	if (!tmp->argv[1])
		exit(0);
	if (ft_atoi(tmp->argv[1]) > 255)
		exit(255);
	exit(ft_atoi(tmp->argv[1]));
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
		if (!check && check_flag(tmp->argv[i]))
			flag = 1;
		else
			check = 1;
		if (check && tmp->argv[i])
		{
			ft_putstr_fd(backup_nega_char(tmp->argv[i]), STDOUT);
			if (tmp->argv[i + 1])
				write(STDOUT, " ", 1);
		}
	}
	if (flag == 0)
		write(STDOUT, "\n", 1);
	return ;
}

void	m_echo(t_token *tmp)
{
	if (!tmp->argv[1])
	{
		write(STDOUT, "\n", 1);
		return ;
	}
	do_echo(0, 0, tmp, 0);
}

void	m_env(t_env *env, int fd)
{
	print_env(env, fd);
	return ;
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
	if (!argv[1])
		print_export(env, fd);
	while (argv[++i])
		add_env(argv[i], env);
}
