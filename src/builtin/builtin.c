/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtin.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: klim <klim@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/06/21 18:12:56 by sehyan            #+#    #+#             */
/*   Updated: 2021/07/03 11:30:27 by klim             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int		m_pwd(int fd)
{
	char	buf[PATH_MAX];

	if (!(getcwd(buf, sizeof(buf))))
		return (0);
	write(fd, buf, ft_strlen(buf));
	write(fd, "\n", 1);
	return (0);
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
		return (err_int("fail", 1));
}

int		m_exit(t_token *tmp)
{
	int		ret;

	printf("exit\n");
	ret = ft_atoi2(tmp->argv[1]);
	if (!tmp->argv[1])
		exit(0);
	if (ret > 255 || ret < 0)
	{
		printf("minishell: exit: %s: numeric argument required\n",
			tmp->argv[1]);
		exit(255);
	}
	if (tmp->argv[2])
	{
		printf("minishell: exit: too many arguments\n");
		return (1);
	}
	exit(ret);
}

int		m_env(t_env *env, int fd)
{
	print_env(env, fd);
	return (0);
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
