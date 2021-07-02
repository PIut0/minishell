/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing5.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: klim <klim@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/07/02 20:26:26 by klim              #+#    #+#             */
/*   Updated: 2021/07/02 20:28:21 by klim             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

char	*replace_env(char *argv, t_info *info)
{
	int		i;
	int		env_len;

	if (!argv || !info)
		return (0);
	i = -1;
	while (argv[++i])
	{
		if ((i > 0 && argv[i - 1] == BACK_SLASH) || is_quote(argv, i) == 1)
			continue ;
		if (argv[i] == '$' && (env_len = get_env_len(argv, i)))
		{
			if (!(argv = change_key_to_value(argv, &i, env_len, info)))
				return (0);
		}
	}
	return (argv);
}

char	*change_nega_char(char *argv)
{
	int		i;

	if (!argv)
		return (0);
	i = -1;
	while (argv[++i])
	{
		if (is_quote(argv, i) && ft_strchr(NEGATIVE_CHAR, argv[i]))
			argv[i] = -argv[i];
	}
	return (argv);
}

char	*remove_quote(char *str)
{
	char	**sp;
	char	*ret;

	if (!str)
		return (0);
	sp = splice_str(str, "\'\"");
	ret = ft_sp_merge(sp);
	free(str);
	return (ret);
}

char	*change_dq_edq(char *str, int key)
{
	int		i;

	if (!str)
		return (0);
	i = -1;
	while (str[++i])
	{
		if (!key && str[i] == '"')
			str[i] = ENV_D_QUOTE;
		if (key && str[i] == ENV_D_QUOTE)
			str[i] = '"';
	}
	return (str);
}

char	*remove_bs(char *str)
{
	char	**sp;
	char	*ret;

	if (!str)
		return (0);
	sp = ft_split(str, BACK_SLASH);
	ret = ft_sp_merge(sp);
	free(str);
	return (ret);
}
