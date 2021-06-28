/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check_func.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sehyan <sehyan@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/06/28 16:28:51 by sehyan            #+#    #+#             */
/*   Updated: 2021/06/28 20:34:14 by sehyan           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "builtin.h"

void	check_func(t_token *tmp, t_env *env)
{
	char *cmd;
	t_node *home;

	cmd = tmp->argv[0];
	if (ft_strcmp("echo", cmd)== 1)
	{
		m_echo(tmp->argv);
	}
	else if (ft_strcmp("exit", cmd) == 1){
		m_exit();
	}
	else if (ft_strcmp("pwd", cmd) == 1){
		m_pwd(1);
	}
	else if (ft_strcmp("cd", cmd) == 1){
		if (!tmp->argv[1])
		{
			home = find_node("HOME", env);
			m_cd(home->value);
		}
		else
			m_cd(tmp->argv[1]);
	}
	else if (ft_strcmp("export", cmd) == 1){
		m_export(tmp->argv, env);
	}
	else if (ft_strcmp("env", cmd) == 1){
		m_env(env);
	}
	else if (ft_strcmp("unset", cmd) == 1){
		m_unset(tmp->argv[1], env);
	}
	else
	{
		printf("exit");
		exit(0);
	}
}