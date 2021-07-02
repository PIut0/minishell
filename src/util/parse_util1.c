/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_util1.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: klim <klim@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/06/25 18:49:35 by klim              #+#    #+#             */
/*   Updated: 2021/07/02 06:17:51 by klim             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int		is_char_set(char *str, char *charset, char *start)
{
	int		q;

	q = is_quote(start, str - start);
	if (q && ((q == 1 && *str != '\'') || (q == 2 && *str != '\"')))
		return (0);
	while (*charset)
	{
		if (*str == *charset && *(str - 1) != BACK_SLASH)
			return (1);
		charset++;
	}
	return (0);
}

int		b_c(char *str, char *charset)
{
	int		count;
	char	*start;

	count = 0;
	start = str;
	while (*str)
	{
		if (!is_char_set(str, charset, start))
		{
			count++;
			while (*str && !is_char_set(str, charset, start))
				str++;
		}
		if (*str)
			str++;
	}
	return (count);
}

void	ft_strcpy(char *dest, char *from, char *to)
{
	while (from < to)
		*dest++ = *from++;
	*dest = 0;
}

char	**splice_str(char *str, char *charset)
{
	char	**result;
	char	*from;
	char	*start;
	int		i;

	i = 0;
	if (!(result = (char**)malloc(sizeof(char*) * (b_c(str, charset) + 1))))
		return (0);
	start = str;
	while (*str)
	{
		if (!is_char_set(str, charset, start))
		{
			from = str;
			while (*str && !is_char_set(str, charset, start))
				str++;
			result[i] = (char*)malloc(str - from + 1);
			ft_strcpy(result[i], from, str);
			i++;
		}
		if (*str)
			str++;
	}
	result[i] = 0;
	return (result);
}
