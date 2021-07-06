/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing6.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: klim <klim@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/07/06 16:43:39 by klim              #+#    #+#             */
/*   Updated: 2021/07/07 03:52:47 by klim             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

t_rd_in	*init_rd_in(char *target)
{
	t_rd_in		*ret;

	if (!(ret = (t_rd_in *)malloc(sizeof(t_rd_in))))
		return (0);
	ret->target = ft_strdup(target);
	ret->next = 0;
	return (ret);
}

void	add_rd_brackets(t_token *t, char *target)
{
	t_rd_in		*new;
	t_rd_in		*tmp;

	t->in = -1;
	new = init_rd_in(target);
	tmp = t->rd_in;
	while (tmp->next)
		tmp = tmp->next;
	tmp->next = new;
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

void	set_fd_in_out(t_token *tmp, int in, int out)
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
				get_rd_input(1, rd->target, out, in);
				exit(errno);
			}
			else
				waitpid(pid, &errno, 0);
			break ;
		}
		else
			get_rd_input(0, rd->target, out, in);
		rd = rd->next;
	}
	dup3(tmp->out, STDOUT);
	if (tmp->in > 0)
		dup3(tmp->in, STDIN);
}
