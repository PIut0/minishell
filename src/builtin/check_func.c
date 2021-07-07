/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check_func.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sehyan <sehyan@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/07/03 11:31:59 by klim              #+#    #+#             */
<<<<<<< HEAD
/*   Updated: 2021/07/07 15:54:39 by klim             ###   ########.fr       */
=======
/*   Updated: 2021/07/07 15:36:06 by sehyan           ###   ########.fr       */
>>>>>>> f3af9a0cc2bae2685e4517d79a9f2d53565132a0
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int		check_btin_func(t_token *tmp, t_info *info)
{
	char	*cmd;
	int		i;

	i = 0;
	cmd = tmp->argv[0];
	if (ft_strcmp("echo", cmd))
		errno = m_echo(tmp);
	else if (ft_strcmp("exit", cmd))
		errno = m_exit(tmp, info);
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

int		run_execve(t_token *tmp, t_info *info, int i)
{
	char	**path;
	int		ret;
	char	*s;

	if (find_node("PATH", info->shell->env))
	{
		path = ft_split(find_node("PATH", info->shell->env)->value, ':');
		while (path[++i] && !is_dir(tmp->argv[0]))
		{
			s = ft_strjoin_free(path[i], "/", 1);
			s = ft_strjoin_free(s, tmp->argv[0], 1);
			ret = execve(s, tmp->argv, get_char_env(info->shell->env));
		}
	}
	ret = execve(tmp->argv[0], tmp->argv, get_char_env(info->shell->env));
	printf("minishell: %s: %s\n", tmp->argv[0], strerror(errno));
	return (errno);
}

int		check_func(t_token *tmp, t_info *info)
{
	pid_t	pid;
	int		ret;

	if ((pid = fork()) < 0)
		exit(errno);
	signal(SIGINT, child_sig);
	signal(SIGQUIT, child_sig);
	if (pid == 0)
	{
		ret = run_execve(tmp, info, -1);
		errno = 127;
		if (ret == 13)
			errno = 126;
		exit(errno);
	}
	else
	{
		if ((waitpid(pid, &errno, 0)) == -1)
			exit(errno);
		dup2(info->shell->std_out, STDOUT);
		if (errno && errno == g_signal.sig)
			errno += 128;
	}
	return (errno);
}
