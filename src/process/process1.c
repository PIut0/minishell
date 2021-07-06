/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   process1.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: klim <klim@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/06/27 15:17:14 by klim              #+#    #+#             */
/*   Updated: 2021/07/07 02:30:19 by klim             ###   ########.fr       */
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

void	get_rd_input(int flag, char *target, int out, int in)
{
	char	*s;

	s = 0;
	while (1)
	{
		ft_putstr_fd("> ", out);
		if ((get_next_line(in, &s) < 0))
			break ;
		if (ft_strcmp(target, s))
		{
			free(s);
			break ;
		}
		if (flag)
		{
			ft_putstr_fd(s, STDOUT);
			ft_putstr_fd("\n", STDOUT);
		}
		free(s);
	}
}

int		get_pipe2(void)
{
	pid_t	pid;
	int		pipefd[2];

	if ((pipe(pipefd)) == -1 || (pid = fork()) == -1)
		exit(errno);
	if (pid == 0)
	{
		close(pipefd[0]);
		dup3(STDIN, STDIN_FILENO);
		dup3(pipefd[1], STDOUT_FILENO);
		close(pipefd[1]);
	}
	else
	{
		close(pipefd[1]);
		dup3(pipefd[0], STDIN_FILENO);
		dup3(STDOUT, STDOUT_FILENO);
		close(pipefd[0]);
	}
	return (pid);
}

void	set_fd_in_out(t_info *info, t_token *tmp)
{
	t_rd_in		*rd;
	int			pid;

	rd = tmp->rd_in->next;
	while (rd)
	{
		if (!rd->next)
		{
			pid = get_pipe2();
			if (!pid)
			{
				get_rd_input(1, rd->target, info->shell->std_out, info->shell->std_in);
				exit(errno);
			}
			else
				waitpid(pid, &errno, 0);
			break ;
		}
		else
			get_rd_input(0, rd->target, info->shell->std_out, info->shell->std_in);
		rd = rd->next;
	}
	dup3(tmp->out, STDOUT);
	if (tmp->in > 0)
		dup3(tmp->in, STDIN);
}

int		process_tmp(t_info *info, t_token *tmp)
{
	int		i;

	i = -1;
	while (tmp->argv[++i])
		tmp->argv[i] = parse_data(tmp->argv[i], info);
	set_fd_in_out(info, tmp);
	//dup3(tmp->in, STDIN);
	//dup3(tmp->out, STDOUT);
	if (!(tmp->argv) || !(tmp->argv[0]))
		;
	else if (check_builtin(tmp->argv[0]))
		errno = check_btin_func(tmp, info);
	else
		errno = check_func(tmp, info);
	dup3(info->shell->std_out, STDOUT);
	dup3(info->shell->std_in, STDIN);
	err_print(info);
	return (errno);
}

int		get_pipe(void)
{
	pid_t	pid;
	int		pipefd[2];

	if ((pipe(pipefd)) == -1 || (pid = fork()) == -1)
		exit(errno);
	if (pid == 0)
	{
		close(pipefd[1]);
		dup3(pipefd[0], STDIN_FILENO);
		dup3(STDOUT, STDOUT_FILENO);
		close(pipefd[0]);
	}
	else
	{
		close(pipefd[0]);
		dup3(STDIN, STDIN_FILENO);
		dup3(pipefd[1], STDOUT_FILENO);
		close(pipefd[1]);
	}
	return (pid);
}

int		process_info(t_info *info, t_token *tmp, int is_child, int pid)
{
	while (tmp)
	{
		pid = 0;
		if (tmp->token_type != _pipe)
			errno = process_tmp(info, tmp);
		else
		{
			pid = get_pipe();
			if (pid)
			{
				process_tmp(info, tmp);
				waitpid(pid, &errno, 0);
				break ;
			}
			else
				is_child = 1;
		}
		tmp = tmp->next;
	}
	if (is_child)
		exit(errno);
	return (0);
}
