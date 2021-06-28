/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   test.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sehyan <sehyan@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/06/25 18:19:14 by sehyan            #+#    #+#             */
/*   Updated: 2021/06/28 15:15:12 by sehyan           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "builtin.h"

int find_fd(char *str)
{
	int fd;

	fd = 0;
	printf("str = %s\n", str);
	fd = open(str,  O_RDWR | O_CREAT | O_TRUNC, 00777);
	return (fd);
}

int main(int argc, char **argv, char **env)
{
	t_env	*g_env;
	int		fd;
	int i = 0;
	while (i < argc)
	{
		if (i == 3){
			fd = find_fd(argv[i]);
			break;
		}
		i++;
	}
	g_env = init_env(env);
	while (1)
	{
		int k;
		ft_putstr_fd("minishell >> ", 0);
		scanf("%d", &k);
		if (k == 1)
		{
			// printf("==pwd==\n");
			m_pwd(fd);
		}
		else if (k == 2)
		{
			printf("==cd==\n");
			char str[PATH_MAX];
			scanf("%s", str);
			m_cd(str);
		}
		else if (k == 3)
		{
			m_env(g_env);
		}
		else if (k == 4)
		{
			m_exit();
		}
		else if (k == 5)
		{
			m_echo(argc, argv);
		}
		else if (k == 6)
		{
			char s[100];
			scanf("%s", s);
			m_unset(s, g_env);
		}
		else if (k == 7)
		{
			m_export(argc, argv, g_env);
		}
		else if (k == 8)
		{
			m_exec(argv);
		}
	}
	return (0);
}