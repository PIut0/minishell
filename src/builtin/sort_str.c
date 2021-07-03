/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sort_str.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sehyan <sehyan@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/07/02 17:55:14 by sehyan            #+#    #+#             */
/*   Updated: 2021/07/02 18:48:13 by sehyan           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

char	**sort_key(char **env_s, int n)
{
	int i;
	int j;
	char *tmp;

	i = 0;
	for( i=0; i<n-1; i++ )
	{
		for( j=0; j<n-1-i; j++ )
		{
			if( ft_strncmp( env_s[j], env_s[j+1], 
					max(ft_strlen(env_s[j]),ft_strlen(env_s[j+1]))) > 0 )
			{
				tmp = env_s[j];

				char **__tmp;
				__tmp = &env_s[j];
				*__tmp = env_s[j + 1];
				
				__tmp = &env_s[j + 1];
				*__tmp = tmp;
			}
		}
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
				break;
			}
			j++;
		}
		i++;
	}
	env_s = sort_key(env_s, i);
	return (env_s);
}