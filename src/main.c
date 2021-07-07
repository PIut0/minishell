/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: klim <klim@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/06/21 14:02:23 by klim              #+#    #+#             */
/*   Updated: 2021/07/07 15:45:03 by klim             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int			shell_start(t_shell *shell)
{
	char	*line;
	t_info	*info;

	while (shell->eof)
	{
		dup3(shell->std_out, STDOUT);
		dup3(shell->std_in, STDIN);
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
		process_info(info, info->head->next, 0, 0);
		free_info(info);
	}
	return (errno);
}

t_shell		*init_shell(char **env_i)
{
	t_shell		*ret;
	t_node		*tmp;
	int			shell_lvl;

	if (!(ret = (t_shell*)malloc(sizeof(t_shell))))
		return (0);
	if (!(ret->env = init_env(env_i)))
		return (0);
	tmp = find_node("HOME", ret->env);
	ret->home = tmp->value;
	ret->pid = getpid();
	if ((tmp = find_node("SHLVL", ret->env)))
	{
		shell_lvl = ft_atoi2(tmp->value) + 1;
		free(tmp->value);
		tmp->value = ft_itoa(shell_lvl);
	}
	else
		add_env("SHLVL=1", ret->env);
	ret->history = init_history();
	ret->home = ft_strdup(find_node("HOME", ret->env)->value);
	ret->std_in = dup(STDIN_FILENO);
	ret->std_out = dup(STDOUT_FILENO);
	ret->eof = 1;
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
