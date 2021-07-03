/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sort_str.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sehyan <sehyan@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/07/02 17:55:14 by sehyan            #+#    #+#             */
/*   Updated: 2021/07/03 13:11:26 by sehyan           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

char	**sort_key(char **env_s, int n)
{
	int		i;
	int		j;
	char	*tmp;
	char	**t;

	i = 0;
	while (i < n - 1)
	{
		while (j < n - 1 - i)
		{
			if (ft_strncmp(env_s[j], env_s[j + 1],
					max(ft_strlen(env_s[j]), ft_strlen(env_s[j + 1]))) > 0)
			{
				tmp = env_s[j];
				t = &env_s[j];
				*t = env_s[j + 1];
				t = &env_s[j + 1];
				*t = tmp;
			}
			j++;
		}
		i++;
	}
	return (env_s);
}

char	**sort_str(char **env_s)
{
	int		i;
	int		j;

	i = 0;
	while (env_s[i])
	{
		j = 0;
		while (env_s[i][j])
		{
			if (env_s[i][j] == '=')
			{
				env_s[i][j] = 0;
				break ;
			}
			j++;
		}
		i++;
	}
	env_s = sort_key(env_s, i);
	return (env_s);
}
