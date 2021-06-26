/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing4.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: klim <klim@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/06/25 16:16:46 by klim              #+#    #+#             */
/*   Updated: 2021/06/26 20:03:28 by klim             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

char	*change_dq_edq(char *str, int key)
{
	int		i;

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

char	*change_key_to_value(char *argv, int *i, int env_len, t_info *info)
{
	char	*key;
	char	*value;
	char	*ret;
	t_node	*node;

	key = ft_substr(argv, (*i) + 1, env_len);
	value = "";
	if ((node = find_node(key, info->shell->env)))
		value = node->value;
	argv[*i] = 0;
	value = change_dq_edq(value, 0);
	ret = ft_strjoin(argv, value);
	ret = ft_strjoin(ret, argv + *i + env_len + 1);
	free(argv);
	//printf("key: %s | value: %s\n",key, value);
	return (ret);
}

int		get_env_len(char *argv, int i)
{
	int		idx;

	idx = i + 1;
	if (!ft_isalpha(argv[idx]) && argv[idx] != '_')
		return (0);
	while (argv[++idx])
	{
		if ((!ft_isalpha(argv[idx]) || !ft_isalnum(argv[idx]))
				&& argv[idx] != '_')
			return (idx - i - 1);
	}
	return (idx - i - 1);
}

char	*replace_env(char *argv, t_info *info)
{
	int		i;
	int		env_len;

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

char	*remove_quote(char *str)
{
	char	**sp;
	char	*ret;

	sp = splice_str(str, "\'\"");
	ret = ft_sp_merge(sp);
	free(str);
	return (ret);
}

char	*remove_bs(char *str)
{
	char	**sp;
	char	*ret;

	sp = ft_split(str, BACK_SLASH);
	ret = ft_sp_merge(sp);
	free(str);
	return (ret);
}

char	*parse_data(char *argv, t_info *info)
{
	argv = replace_env(argv, info);
	argv = remove_quote(argv);
	argv = change_dq_edq(argv, 1);
	argv = remove_bs(argv);
	printf("argv: %s\n",argv);
	return (argv);
}

int		parse_argv(t_info *info, t_token *head)
{
	t_env		*env;
	t_token		*token;
	int			i;
	char		**tmp;

	env = info->shell->env;
	token = head->next;
	while (token)
	{
		token->argv = splice_str(token->data, WHITE_SPACE);
		tmp = token->argv;
		if (tmp[0])
			tmp[0] = parse_data(tmp[0], info);
		i = 0;
		while (tmp[++i])
			tmp[i] = parse_data(tmp[i], info);
		printf("*********\n");
		token = token->next;
	}
	return (0);
}
