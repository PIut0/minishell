/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sehyan <sehyan@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/06/21 14:02:23 by klim              #+#    #+#             */
/*   Updated: 2021/07/02 21:48:42 by klim             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int		shell_start(t_shell *shell)
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
	g_signal.in = dup(STDIN);
	g_signal.out = dup(STDOUT);
	g_signal.sig = 0;
	if (!(shell = init_shell(env)))
		return (1);
	return (shell_start(shell));
}
