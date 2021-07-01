/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   process1.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: klim <klim@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/06/27 15:17:14 by klim              #+#    #+#             */
/*   Updated: 2021/07/01 23:27:18 by klim             ###   ########.fr       */
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

	if (!(tmp->argv) || !(tmp->argv[0]))
		;
	else if (check_builtin(tmp->argv[0]))
	{
		i = -1;
		while (tmp->argv[++i])
			tmp->argv[i] = parse_data(tmp->argv[i], info);
		check_btin_func(tmp, info);
	}
	else
	{
		i = -1;
		while (tmp->argv[++i])
			backup_bs(tmp->argv[i], ft_strlen(tmp->argv[i]));
		check_func(tmp, info, c);
	}
	return (0);
}

int		get_pipe(int *pipefd[])
{
	pid_t	pid;

	pipe(*pipefd);
	pid = fork();
	if (pid == 0)
	{
		close((*pipefd)[1]);
		dup2((*pipefd)[0], STDIN_FILENO);
		return (-1);
	}
	else
	{
		close((*pipefd)[0]);
		dup2((*pipefd)[1], STDOUT_FILENO);
		return (pid);
	}
}

int		process_info(t_info *info)
{
	int		pid;
	int		exit_check;
	int		*pipefd;
	t_token	*tmp;

	tmp = info->head->next;
	exit_check = 0;
	while (tmp)
	{
		pid = 0;
		if (tmp->token_type == _pipe)
			pid = get_pipe(&pipefd);
		if (pid < 0)
			exit_check = 1;
		if (pid >= 0)
			process_tmp(info, tmp, exit_check);
		if (pid > 0)
			break;
		tmp = tmp->next;
	}
	if (pid > 0)
		wait(&pid);
	if (exit_check)
	{
		printf("test\n");
		exit(0);
	}
	dup2(info->shell->_stdout, STDOUT_FILENO);
	return (0);
}
