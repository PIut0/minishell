/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtin2.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: klim <klim@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/07/03 00:54:39 by ash               #+#    #+#             */
/*   Updated: 2021/07/04 20:13:20 by klim             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	do_echo(int i, int check, t_token *tmp, int flag)
{
	while (tmp->argv[++i])
	{
		if (!check && check_flag(tmp->argv[i]))
			flag = 1;
		else
			check = 1;
		if (check && tmp->argv[i])
		{
			ft_putstr_fd(backup_nega_char(tmp->argv[i]), STDOUT);
			if (tmp->argv[i + 1])
				write(STDOUT, " ", 1);
		}
	}
	if (flag == 0)
		write(STDOUT, "\n", 1);
	return ;
}

int		m_echo(t_token *tmp)
{
	if (!tmp->argv[1])
	{
		write(STDOUT, "\n", 1);
		return (0);
	}
	do_echo(0, 0, tmp, 0);
	return (0);
}

int		m_unset(char **argv, t_env *env)
{
	int		i;
	t_node	*n;
	char	*key;

	i = 0;
	errno = 0;
	if (!argv[1])
		return (0);
	while (argv[++i])
	{
		key = argv[i];
		if (!key[0])
			continue ;
		if (get_env_len(key, 0) + 1 != (int)ft_strlen(key))
		{
			printf("minishell: export: '%s': not a valid identifier\n", key);
			errno = 1;
			continue ;
		}
		n = find_node(key, env);
		if (!n)
			continue ;
		rm_env(n);
	}
	return (errno);
}

int		m_export(char **argv, t_env *env, int fd)
{
	int i;

	i = 0;
	errno = 0;
	if (!argv[1])
		print_export(env, fd);
	while (argv[++i])
		add_env(argv[i], env);
	return (errno);
}
