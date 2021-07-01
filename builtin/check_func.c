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

void	check_bracket(t_token *tmp)
{
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
		else if (ft_strcmp(tmp->argv[i], "<") == 1)
		{

		}
		i++;
	}
}

void	check_btin_func(t_token *tmp, t_info *info)
{
	char *cmd;
	t_node *home;
	int i;
	i = 0;

	// signal(SIGINT, child_sig);
	// signal(SIGQUIT, child_sig);
	check_bracket(tmp);
	cmd = tmp->argv[0];
	if (ft_strcmp("echo", cmd)== 1)
	{
		m_echo(tmp);
	}
	else if (ft_strcmp("exit", cmd) == 1){
		m_exit();
	}
	else if (ft_strcmp("pwd", cmd) == 1){
		m_pwd(tmp->fd);
	}
	else if (ft_strcmp("cd", cmd) == 1){
		if (!tmp->argv[1])
		{
			home = find_node("HOME", info->shell->env);
			if (!home){
				printf("cd: HOME not set");
				return ;
			}
			else
				m_cd(home->value);
		}
		else
			m_cd(tmp->argv[1]);
	}
	else if (ft_strcmp("export", cmd) == 1){
		m_export(tmp->argv, info->shell->env, tmp->fd);
	}
	else if (ft_strcmp("env", cmd) == 1){
		m_env(info->shell->env, tmp->fd);
	}
	else if (ft_strcmp("unset", cmd) == 1){
		while (tmp->argv[++i])
		{
			m_unset(tmp->argv[i], info->shell->env);
		}
	}
	else
	{
		printf("%s is not command\n", tmp->argv[0]);
		return ;
		// exit(0);
	}
	return ;
	// exit(0);
}

char	*get_keyvalue(t_node *t)
{
	char	*ret;

	ret = ft_strdup("");
	ret = ft_strjoin(ret, t->key);
	ret = ft_strjoin(ret, "=");
	ret = ft_strjoin(ret, t->value);
	return (ret);
}

char	**get_char_env(t_env *env)
{
	t_node	*t;
	int		cnt;
	int		i;
	char	**ret;

	cnt = 0;
	i = -1;
	t = env->head->next;
	while (t != env->tail && ++cnt)
		t = t->next;
	if (!(ret = (char **)malloc(sizeof(char *) * cnt + 1)))
		return (0);
	t = env->head->next;
	while (t != env->tail)
	{
		ret[++i] = get_keyvalue(t);
		t = t->next;
	}
	ret[i] = 0;
	return (ret);
}

void	check_func(t_token *tmp, t_info *info)
{
	pid_t pid;
	char **path;
	t_node *p_node;
	int		i;
	char	*s;

	i = 0;
	p_node = find_node("PATH", info->shell->env);
	path = ft_split(p_node->value, ':');
	pid = fork();
	if (pid == 0)
	{
		signal(SIGINT, child_sig);
		signal(SIGQUIT, child_sig);
		while (path[i])
		{
			s = ft_strjoin(path[i], "/");
			s = ft_strjoin(s, tmp->argv[0]);
			// printf("here\n");
			if (execve(s, tmp->argv, get_char_env(info->shell->env)))
				;
			i++;
		}
		printf("%s is not command\n", tmp->argv[0]);
		exit(0);
	}
	else
		wait(&pid);
}
