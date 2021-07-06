/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing6.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: klim <klim@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/07/06 16:43:39 by klim              #+#    #+#             */
/*   Updated: 2021/07/07 05:06:10 by klim             ###   ########.fr       */
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

void	get_rd_input(int flag, char *target, t_info *info)
{
	char	*s;

	while (1)
	{
		ft_putstr_fd("> ", info->shell->std_out);
		if ((get_next_line(info->shell->std_in, &s) <= 0))
			break ;
		if (ft_strcmp(target, s))
		{
			free(s);
			break ;
		}
		if (flag)
		{
			s = replace_bs2(s);
			s = replace_env2(s, info);
			s = remove_bs(s);
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

void	set_fd_in_out(t_token *tmp, t_info *info)
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
				signal(SIGINT, db_sigint);
				get_rd_input(1, rd->target, info);
				exit(errno);
			}
			else
				waitpid(pid, &errno, 0);
			break ;
		}
		else
			get_rd_input(0, rd->target, info);
		rd = rd->next;
	}
	if (tmp->in > 0)
		dup3(tmp->in, STDIN);
}
