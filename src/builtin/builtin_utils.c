/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtin_utils.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: klim <klim@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/06/23 19:33:27 by sehyan            #+#    #+#             */
/*   Updated: 2021/07/04 20:13:16 by klim             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int		max(int a, int b)
{
	if (a > b)
		return (a);
	else
		return (b);
}

void	print_env(t_env *env, int fd)
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

void	print_export(t_env *env, int fd)
{
	t_node	*now;
	char	**env_s;
	int		i;

	env_s = get_char_env(env);
	env_s = sort_str(env_s);
	i = -1;
	while (env_s[++i])
	{
		if ((now = find_node(env_s[i], env)))
		{
			ft_putstr_fd("declare -x ", fd);
			write(fd, now->key, ft_strlen(now->key));
			if (now->value)
			{
				write(fd, "=\"", 2);
				write(fd, backup_nega_char(now->value), ft_strlen(now->value));
				write(fd, "\"", 1);
			}
			write(fd, "\n", 1);
		}
		free(env_s[i]);
	}
	free(env_s);
}

int		check_flag(char *argv)
{
	int j;

	if (argv[0] != '-')
		return (0);
	j = 1;
	while (argv[j])
	{
		if (argv[j] == 'n')
			j++;
		else
			return (0);
	}
	return (1);
}
