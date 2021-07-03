/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check_func.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: klim <klim@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/07/03 11:31:59 by klim              #+#    #+#             */
/*   Updated: 2021/07/03 11:44:29 by klim             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

extern char **g_env;

int		check_btin_func(t_token *tmp, t_info *info)
{
	char	*cmd;
	int		i;

	i = 0;
	cmd = tmp->argv[0];
	if (ft_strcmp("echo", cmd))
		errno = m_echo(tmp);
	else if (ft_strcmp("exit", cmd))
		errno = m_exit(tmp);
	else if (ft_strcmp("pwd", cmd))
		errno = m_pwd(STDOUT);
	else if (ft_strcmp("cd", cmd))
		errno = m_cd(tmp->argv[1], info);
	else if (ft_strcmp("export", cmd) == 1)
		errno = m_export(tmp->argv, info->shell->env, STDOUT);
	else if (ft_strcmp("env", cmd) == 1)
		errno = m_env(info->shell->env, STDOUT);
	else if (ft_strcmp("unset", cmd) == 1)
		errno = m_unset(tmp->argv, info->shell->env);
	return (errno);
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
		if (argv[i] == '/')
			return (1);
	return (0);
}

int		check_func(t_token *tmp, t_info *info, int i)
{
	pid_t	pid;
	char	**path;
	char	*s;

	signal(SIGINT, child_sig);
	signal(SIGQUIT, child_sig);
	pid = fork();
	if (pid == 0)
	{
		if (find_node("PATH", info->shell->env))
		{
			path = ft_split(find_node("PATH", info->shell->env)->value, ':');
			while (path[++i] && !is_dir(tmp->argv[0]))
			{
				s = ft_strjoin(path[i], "/");
				s = ft_strjoin(s, tmp->argv[0]);
				execve(s, tmp->argv, get_char_env(info->shell->env));
			}
		}
		execve(tmp->argv[0], tmp->argv, get_char_env(info->shell->env));
		if (is_dir(tmp->argv[0]))
			printf("minishell: %s: No such file or directory\n", tmp->argv[0]);
		else
			printf("minishell: %s: command not found\n", tmp->argv[0]);
		exit(127);
	}
	else
		waitpid(pid, &errno, 0);
	return (errno);
}
