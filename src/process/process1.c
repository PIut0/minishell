/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   process1.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: klim <klim@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/06/27 15:17:14 by klim              #+#    #+#             */
/*   Updated: 2021/07/02 05:24:28 by klim             ###   ########.fr       */
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

	i = c;
	dup2(tmp->in, STDIN);
	dup2(tmp->out, STDOUT);
	//if (!(tmp->argv) || !(tmp->argv[0]))
	//	;
	//else if (check_builtin(tmp->argv[0]))
	//{
	//	i = -1;
	//	while (tmp->argv[++i])
	//		tmp->argv[i] = parse_data(tmp->argv[i], info);
	//	check_btin_func(tmp, info);
	//}
	//else
	//{
	//	i = -1;
	//	while (tmp->argv[++i])
	//		tmp->argv[i] = backup_data(tmp->argv[i], info);
	//	check_func(tmp, info, c);
	//}

	if (!(tmp->argv) || !(tmp->argv[0]))
		;
	else if (check_builtin(tmp->argv[0]))
	{
		i = -1;
		while (tmp->argv[++i])
			tmp->argv[i] = parse_data(tmp->argv[i], info);
		check_btin_func(tmp, info);
		//ft_putstr_fd(tmp->argv[1], STDOUT_FILENO);
		//ft_putstr_fd("\n", STDOUT_FILENO);
		//dup2(info->shell->_stdout, STDOUT_FILENO);
		//write(STDOUT_FILENO, "end\n",4);
	}
	else
	{
		i = -1;
		while (tmp->argv[++i])
			tmp->argv[i] = backup_data(tmp->argv[i], info);
		check_func(tmp, info, c);
		//int pid2;
		//pid2 = fork();
		//if (pid2)
		//{
		//	dup2(info->shell->_stdout, STDOUT_FILENO);
		//	write(STDOUT, "wait start\n",11);
		//	wait(NULL);
		//	write(STDOUT, "wait end\n",9);
		//}
		//else
		//	execve("/bin/cat", NULL, NULL);
	}
	dup2(info->shell->_stdout, STDOUT);
	dup2(info->shell->_stdin, STDIN);
	return (0);
}

int		get_pipe()
{
	pid_t	pid;
	int		pipefd[2];

	pipe(pipefd);
	//fcntl((*pipefd)[0], F_SETFL, O_NONBLOCK);
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

int		process_info(t_info *info)
{
	int		pid;
	int		is_child;
	t_token	*tmp;

	tmp = info->head->next;
	is_child = 0;
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
