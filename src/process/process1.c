/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   process1.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: klim <klim@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/06/27 15:17:14 by klim              #+#    #+#             */
/*   Updated: 2021/07/02 21:27:48 by klim             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int		check_builtin(char *argv)
{
	int		len;

	len = ft_strlen(argv);
	if (!len)
		return (0);
	if (!ft_strncmp(argv, "echo", len) ||
		!ft_strncmp(argv, "cd", len) ||
		!ft_strncmp(argv, "pwd", len) ||
		!ft_strncmp(argv, "export", len) ||
		!ft_strncmp(argv, "unset", len) ||
		!ft_strncmp(argv, "env", len) ||
		!ft_strncmp(argv, "exit", len))
		return (1);
	return (0);
}

int		process_tmp(t_info *info, t_token *tmp, int c)
{
	int		i;

	i = -1;
	while (tmp->argv[++i])
		tmp->argv[i] = parse_data(tmp->argv[i], info);
	dup2(tmp->in, STDIN);
	dup2(tmp->out, STDOUT);
	if (!(tmp->argv) || !(tmp->argv[0]))
		;
	else if (check_builtin(tmp->argv[0]))
		check_btin_func(tmp, info);
	else
		check_func(tmp, info, c);
	dup2(info->shell->std_out, STDOUT);
	dup2(info->shell->std_in, STDIN);
	return (0);
}

int		get_pipe(void)
{
	pid_t	pid;
	int		pipefd[2];

	pipe(pipefd);
	pid = fork();
	if (pid == 0)
	{
		close(pipefd[1]);
		dup2(pipefd[0], STDIN_FILENO);
		dup2(STDOUT, STDOUT_FILENO);
		close(pipefd[0]);
	}
	else
	{
		close(pipefd[0]);
		dup2(STDIN, STDIN_FILENO);
		dup2(pipefd[1], STDOUT_FILENO);
		close(pipefd[1]);
	}
	return (pid);
}

int		process_info(t_info *info, int is_child, int pid)
{
	t_token	*tmp;

	tmp = info->head->next;
	while (tmp)
	{
		pid = 0;
		if (tmp->token_type != _pipe)
			process_tmp(info, tmp, is_child);
		else
		{
			pid = get_pipe();
			if (pid)
			{
				process_tmp(info, tmp, is_child);
				waitpid(pid, NULL, 0);
				break ;
			}
			else
				is_child = 1;
		}
		tmp = tmp->next;
	}
	if (is_child)
		exit(0);
	return (0);
}
