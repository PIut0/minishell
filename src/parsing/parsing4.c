/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing4.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: klim <klim@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/06/25 16:16:46 by klim              #+#    #+#             */
/*   Updated: 2021/07/02 21:26:44 by klim             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

char	*change_key_to_value(char *argv, int *i, int env_len, t_info *info)
{
	char	*key;
	char	*value;
	char	*ret;
	t_node	*node;

	key = ft_substr(argv, (*i) + 1, env_len);
	value = "";
	if ((node = find_node(key, info->shell->env)))
		if (!ft_strncmp((value = node->value), "~", 2))
			value = find_node("HOME", info->shell->env)->value;
	if (!(ft_strncmp(key, "?", 2)))
		value = get_errno();
	if (!(ft_strncmp(key, "$", 2)))
		value = get_pid();
	argv[*i] = 0;
	value = change_dq_edq(value, 0);
	ret = ft_strjoin(argv, value);
	ret = ft_strjoin(ret, argv + *i + env_len + 1);
	free(argv);
	return (ret);
}

int		get_env_len(char *argv, int i)
{
	int		idx;

	idx = i + 1;
	if (!ft_isalpha(argv[idx]) && argv[idx] != '_'
		&& argv[idx] != '$' && argv[idx] != '?')
		return (0);
	while (argv[++idx])
	{
		if (!ft_isalnum(argv[idx]) && argv[idx] != '_')
			return (idx - i - 1);
	}
	return (idx - i - 1);
}

char	*replace_home(char *argv)
{
	char	*ret;

	ret = ft_strdup("$HOME");
	ret = ft_strjoin(ret, argv + 1);
	free(argv);
	return (ret);
}

char	*parse_data(char *argv, t_info *info)
{
	if (!ft_strncmp(argv, "~", 2) || !ft_strncmp(argv, "~/", 2))
		argv = replace_home(argv);
	argv = replace_env(argv, info);
	argv = change_nega_char(argv);
	argv = remove_quote(argv);
	argv = change_dq_edq(argv, 1);
	argv = remove_bs(argv);
	argv = backup_nega_char(argv);
	return (argv);
}

int		parse_argv(t_info *info, t_token *head)
{
	t_env		*env;
	t_token		*token;
	char		**tmp;

	env = info->shell->env;
	token = head->next;
	while (token)
	{
		token->argv = splice_str(token->data, WHITE_SPACE);
		tmp = token->argv;
		if (tmp[0])
			tmp[0] = parse_data(tmp[0], info);
		token = token->next;
	}
	return (0);
}
