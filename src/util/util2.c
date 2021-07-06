/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   util2.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: klim <klim@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/07/03 11:51:01 by klim              #+#    #+#             */
/*   Updated: 2021/07/07 05:05:20 by klim             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int		is_dir(char *argv)
{
	int		i;

	i = -1;
	while (argv[++i])
		if (argv[i] == '/')
			return (1);
	return (0);
}

int		parse_errno(int err)
{
	if ((int)err > 255)
		err = err >> 8;
	return (err);
}

void	dup3(int a, int b)
{
	if ((dup2(a, b)) == -1)
		exit(errno);
}

char	*replace_env2(char *argv, t_info *info)
{
	int		i;
	int		env_len;

	if (!argv || !info)
		return (0);
	i = -1;
	while (argv[++i])
	{
		if (i > 0 && argv[i - 1] == BACK_SLASH)
			continue ;
		if (argv[i] == '$' && (env_len = get_env_len(argv, i)))
		{
			if (!(argv = change_key_to_value(argv, &i, env_len, info)))
				return (0);
		}
	}
	return (argv);
}

char	*replace_bs2(char *line)
{
	int		i;

	i = -1;
	while (line[++i])
	{
		if ((i > 0 && line[i - 1] == BACK_SLASH) || is_quote(line, i) == 1)
			;
		else if (line[i] == '\\')
		{
			if (is_quote(line, i) != 2 ||
				(line[i + 1] == '$' || line[i + 1] == '\\'))
				line[i] = BACK_SLASH;
		}
	}
	return (line);
}
