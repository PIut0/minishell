/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   test.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sehyan <sehyan@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/06/25 18:19:14 by sehyan            #+#    #+#             */
/*   Updated: 2021/06/25 20:01:39 by sehyan           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "builtin.h"

int main(int argc, char **argv, char **env)
{
	t_env	*g_env;

	g_env = init_env(env);
	while (1)
	{
		int k;
		scanf("%d", &k);
		if (k == 1)
		{
			printf("==pwd==\n");
			m_pwd();
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
	}
	return (0);
}