/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing1.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: klim <klim@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/06/21 15:31:30 by klim              #+#    #+#             */
/*   Updated: 2021/06/30 13:50:18 by klim             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

char		*replace_bs(char *line, int len)
{
	int		i;

	i = -1;
	while (++i < len)
	{
		if ((i > 0 && line[i-1] == BACK_SLASH) || is_quote(line, i) == 1)
			;
		else if (line[i] == '\\')
		{
			if (is_quote(line, i) != 2 ||
				(line[i + 1] == '"' || line[i + 1] == '\\'))
				line[i] = BACK_SLASH;
		}
	}
	return (line);
}

char		*remove_space(char *str)
{
	char	*t;
	size_t	i;
	size_t	end;

	if (!str)
		return (0);
	i = 0;
	while (str[i] && ft_strchr(WHITE_SPACE, str[i]))
		i++;
	end = ft_strlen(str + i);
	while (end && str[i + end - 1] && ft_strchr(WHITE_SPACE, str[i + end - 1]))
		end--;
	if (!(t = (char *)malloc(end + 1)))
		return (0);
	if (str[i + end - 1] == BACK_SLASH && ft_strchr(WHITE_SPACE, str[i + end]))
		end++;
	ft_strlcpy(t, str + i, end + 1);
	free(str);
	return (t);
}

int			parsing(char *line, t_info *info)
{
	t_token		*head;
	int			len;

	len = ft_strlen(line);
	line = replace_bs(line, len);
	if (is_quote(line, len))
		return (err_int("minishell: unexpected quote", 1));
	head = init_token("");
	if (parse_token(line, info, head, len))
		return (1);
	info->head = head;
	free(line);
	return 0;
}
