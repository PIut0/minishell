/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: klim <klim@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/06/21 14:02:23 by klim              #+#    #+#             */
/*   Updated: 2021/07/04 16:27:19 by klim             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

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
		{
			free_info(info);
			continue ;
		}
		process_info(info, 0, 0);
		free_info(info);
	}
	return (0);
}

t_shell		*init_shell(char **env_i)
{
	t_shell		*ret;
	t_node		*tmp;

	if (!(ret = (t_shell*)malloc(sizeof(t_shell))))
		return (0);
	ret->env = init_env(env_i);
	tmp = find_node("HOME", ret->env);
	ret->home = tmp->value;
	ret->history = init_history();
	ret->home = ft_strdup(find_node("HOME", ret->env)->value);
	ret->std_in = dup(STDIN_FILENO);
	ret->std_out = dup(STDOUT_FILENO);
	return (ret);
}

int			main(int argc, char **argv, char **env)
{
	t_shell		*shell;

	argc = -1;
	(void)argv;
	if (!(shell = init_shell(env)))
		return (1);
	g_signal.in = dup(STDIN);
	g_signal.out = dup(STDOUT);
	g_signal.sig = 0;
	return (shell_start(shell));
}
