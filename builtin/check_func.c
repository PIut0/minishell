/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check_func.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sehyan <sehyan@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/06/28 16:28:51 by sehyan            #+#    #+#             */
/*   Updated: 2021/06/28 22:28:00 by sehyan           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "builtin.h"

int		open_single(char *s)
{
	int fd;
	
	fd = open(s, O_RDWR | O_CREAT | O_TRUNC, 00777);
	if (fd == -1)
		fd = 0;
	return (fd);
}

int		open_double(char *s)
{
	int fd;
	
	fd = open(s, O_RDWR | O_CREAT | O_APPEND, 00777);
	if (fd == -1)
		fd = 0;
	return (fd);
}

void	check_func(t_token *tmp, t_info *info)
{
	char *cmd;
	t_node *home;
	int i;
	i = 0;

	while (tmp->argv[i])
	{
		if (ft_strcmp(tmp->argv[i], ">") == 1)
		{
			if (tmp->fd != 0)
				close(tmp->fd);
			tmp->fd = open_single(tmp->argv[i + 1]);
		}
		else if (ft_strcmp(tmp->argv[i], ">>") == 1)
		{
			if (tmp->fd != 0)
				close(tmp->fd);
			tmp->fd = open_double(tmp->argv[i + 1]);
		}
		i++;
	}
	cmd = tmp->argv[0];
	if (ft_strcmp("echo", cmd)== 1)
	{
		// write(1, "here!\n", 6);
		m_echo(tmp);
	}
	else if (ft_strcmp("exit", cmd) == 1){
		m_exit();
	}
	else if (ft_strcmp("pwd", cmd) == 1){
		m_pwd(1);
	}
	else if (ft_strcmp("cd", cmd) == 1){
		if (!tmp->argv[1])
		{
			home = find_node("HOME", info->shell->env);
			m_cd(home->value);
		}
		else
			m_cd(tmp->argv[1]);
	}
	else if (ft_strcmp("export", cmd) == 1){
		m_export(tmp->argv, info->shell->env);
	}
	else if (ft_strcmp("env", cmd) == 1){
		m_env(info->shell->env);
	}
	else if (ft_strcmp("unset", cmd) == 1){
		m_unset(tmp->argv[1], info->shell->env);
	}
	else
	{
		printf("exit");
		exit(0);
	}
}