/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check_btin_func.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ash <ash@student.42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/06/28 16:28:51 by sehyan            #+#    #+#             */
/*   Updated: 2021/06/29 15:01:16 by ash              ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "builtin.h"

extern char **g_env;

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

void	check_btin_func(t_token *tmp, t_info *info)
{
	char *cmd;
	t_node *home;
	int i;
	i = 0;

	while (tmp->argv[i])
	{
		printf("argv[i] = %s\n", tmp->argv[i]);
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
		else if (ft_strcmp(tmp->argv[i], "<") == 1)
		{
			
		}
		i++;
	}
	cmd = tmp->argv[0];
	if (ft_strcmp("echo", cmd)== 1)
		m_echo(tmp);
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
		for (int i = 1; tmp->argv[i]; i++)
			m_unset(tmp->argv[i], info->shell->env);
	}
	else
	{
		printf("%s is not command\n", tmp->argv[0]);
		return ;
	}
}

void	check_func(t_token *tmp, t_info *info)
{
	info->shell->env->head->prev = 0;
	//fork해서 자식프로세스로 실행해야 안끝남. 
	if (ft_strcmp(tmp->argv[0], "cat") == 1)
	{
		if (execve("/bin/cat", tmp->argv, g_env) == -1)
		{
			printf("ERROR\n");
			return ;
		}
	}
	else
	{
		printf("exec here\n");
		return ;
	}
}