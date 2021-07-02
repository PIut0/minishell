/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: klim <klim@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/06/21 14:02:23 by klim              #+#    #+#             */
/*   Updated: 2021/07/02 20:50:07 by klim             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void		print_env(t_env *env, int fd)
{
	t_node	*tmp;

	tmp = env->head->next;
	while (tmp != env->tail)
	{
		if (tmp->value)
		{
			write(fd, tmp->key, ft_strlen(tmp->key));
			write(fd, "=", 1);
			write(fd, tmp->value, ft_strlen(tmp->value));
			write(fd, "\n", 1);
		}
		tmp = tmp->next;
	}
}

int			shell_start(t_shell *shell)
{
	char	*line;
	t_info	*info;

	while (1)
	{
		signal(SIGINT, sig_sigint);
		signal(SIGQUIT, sig_sigquit);
		if (!(info = init_info(shell)))
			continue ;
		ft_putstr_fd("minishell > ", 1);
		line = get_line(shell);
		add_history(shell, line);
		if (parsing(line, info))
			continue ;
		if (process_info(info, 0, 0))
			continue ;
		free_info(info);
	}
	return (0);
}

t_shell		*init_shell(char **env_i)
{
	t_shell		*ret;

	if (!(ret = (t_shell*)malloc(sizeof(t_shell))))
		return (0);
	ret->env = init_env(env_i);
	ret->history = init_history();
	ret->std_in = dup(STDIN_FILENO);
	ret->std_out = dup(STDOUT_FILENO);
	return (ret);
}

int			main(int argc, char **argv, char **env)
{
	t_shell		*shell;

	argc = -1;
	(void)argv;
	g_signal.in = dup(STDIN);
	g_signal.out = dup(STDOUT);
	g_signal.sig = 0;
	if (!(shell = init_shell(env)))
		return (1);
	return (shell_start(shell));
}
