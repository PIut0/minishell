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

#include "minishell.h"

extern char **g_env;

int		open_file(char *s, int flag)
{
	int fd;

	if (!s || !*s)
		return (-1);
	if (flag)
		fd = open(s, O_RDWR | O_CREAT | O_TRUNC, 00777);
	else
		fd = open(s, O_RDWR | O_CREAT | O_APPEND, 00777);
	return (fd);
}

int		check_btin_func(t_token *tmp, t_info *info)
{
	char *cmd;
	int i;
	i = 0;

	//if (check_bracket(tmp))
	//	return (1);
	cmd = tmp->argv[0];
	if (ft_strcmp("echo", cmd))
		m_echo(tmp);
	else if (ft_strcmp("exit", cmd))
		m_exit(tmp);
	else if (ft_strcmp("pwd", cmd))
		m_pwd(STDOUT);
	else if (ft_strcmp("cd", cmd))
		m_cd(tmp->argv[1], info);
	else if (ft_strcmp("export", cmd) == 1)
		m_export(tmp->argv, info->shell->env, STDOUT);
	else if (ft_strcmp("env", cmd) == 1)
		m_env(info->shell->env, STDOUT);
	else if (ft_strcmp("unset", cmd) == 1)
		m_unset(tmp->argv, info->shell->env);
	return (0);
}

char	*get_keyvalue(t_node *t)
{
	char	*ret;

	ret = ft_strdup("");
	ret = ft_strjoin_free(ret, t->key, 1);
	ret = ft_strjoin_free(ret, "=", 1);
	if (t->value)
		ret = ft_strjoin_free(ret, t->value, 1);
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
	ret[++i] = 0;
	return (ret);
}

int		is_dir(char *argv)
{
	int		i;

	i = -1;
	while (argv[++i])
		if(argv[i] == '/')
			return (1);
	return (0);
}

void	check_func(t_token *tmp, t_info *info, int c)
{
	pid_t	pid;
	char	**path;
	int		i;
	char	*s;

	i = -1;
	c = 0;
	signal(SIGINT, child_sig);
	signal(SIGQUIT, child_sig);
	pid = fork();
	if (pid == 0)
	{
		if (!find_node("PATH", info->shell->env))
		{
			printf("bash: %s: No such file or directory\n", tmp->argv[0]);
			exit(1);
		}
		path = ft_split(find_node("PATH", info->shell->env)->value, ':');
		while(path[++i] && !is_dir(tmp->argv[0]))
		{
			s = ft_strjoin(path[i], "/");
			s = ft_strjoin(s, tmp->argv[0]);
			execve(s, tmp->argv, get_char_env(info->shell->env));
		}
		execve(tmp->argv[0], tmp->argv, get_char_env(info->shell->env));
		printf("bash: command not found: %s\n", tmp->argv[0]);
		exit(0);
	}
	else
		waitpid(pid, NULL, 0);
}
