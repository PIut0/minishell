/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtin.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ash <ash@student.42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/06/21 18:12:56 by sehyan            #+#    #+#             */
/*   Updated: 2021/07/03 04:11:36 by ash              ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	m_pwd(int fd)
{
	char	buf[PATH_MAX];

	if (!(getcwd(buf, sizeof(buf))))
		return; //error
	write(fd, buf, ft_strlen(buf));
	write(fd, "\n", 1);
	return ;
}

int		m_cd(char *s, t_info *info)
{
	int result;

	if (!s)
	{
		if (!find_node("HOME", info->shell->env))
			return (err_int("minishell : cd: HOME not set", 1));
		s = find_node("HOME", info->shell->env)->value;
	}
	result = chdir(s);
	if (result == 0)
		return (0);
	else
		return err_int("fail", 1);
}

void	m_exit(t_token *tmp)
{
	printf("exit\n");
	if (!tmp->argv[1])
		exit(0);
	if (ft_atoi(tmp->argv[1]) > 255)
		exit(255);
	exit(ft_atoi(tmp->argv[1]));
}

void	m_env(t_env *env, int fd)
{
	print_env(env, fd);
	return ;
}

int		is_bracket(char *argv)
{
	if (ft_strcmp(argv, ">") ||
		ft_strcmp(argv, ">>") ||
		ft_strcmp(argv, "<") ||
		ft_strcmp(argv, "<<"))
		return (1);
	return (0);
}

