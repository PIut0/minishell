/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   backup1.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: klim <klim@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/06/28 21:03:37 by klim              #+#    #+#             */
/*   Updated: 2021/07/03 10:59:55 by klim             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

char		*backup_bs(char *line, int len)
{
	int		i;

	i = -1;
	while (++i < len)
	{
		if (line[i] == BACK_SLASH)
			line[i] = '\\';
	}
	return (line);
}

char		*backup_nega_char(char *data)
{
	int		i;

	i = -1;
	while (data[++i])
		if (data[i] < 0)
			data[i] = -data[i];
	return (data);
}

char		*backup_data(char *data, t_info *info)
{
	data = replace_env(data, info);
	data = backup_bs(data, ft_strlen(data));
	data = backup_nega_char(data);
	return (data);
}
