/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_split.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: klim <klim@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/12/25 05:08:08 by klim              #+#    #+#             */
/*   Updated: 2021/06/26 20:02:19 by klim             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static int	block_count(char *str, char c)
{
	int count;

	count = 0;
	while (*str)
	{
		if (*str != c)
		{
			count++;
			while (*str && *str != c)
				str++;
		}
		else
			str++;
	}
	return (count);
}

static char	*worddup(const char *str, char c)
{
	size_t	len;
	char	*r;

	len = 0;
	while (str[len] && str[len] != c)
		len++;
	if (!(r = (char*)ft_calloc(len + 1, sizeof(char))))
		return (0);
	ft_strlcpy(r, str, len + 1);
	return (r);
}

static char	**ft_freeall(char **r)
{
	unsigned int i;

	i = 0;
	while (r[i] != NULL)
	{
		free(r[i]);
		i++;
	}
	free(r);
	return (0);
}

char		**ft_split(const char *str, char c)
{
	char	**result;
	int		i;
	int		j;
	int		len;

	i = 0;
	j = 0;
	if (!str)
		return (0);
	len = block_count((char *)str, c);
	if (!(result = (char**)ft_calloc((len + 1), sizeof(char*))))
		return (0);
	while (str[j] && i < len)
	{
		if (str[j] != c)
		{
			if (!(result[i++] = worddup(&(str[j]), c)))
				return (ft_freeall(result));
			while (str[j] && str[j] != c)
				j++;
		}
		else
			j++;
	}
	return (result);
}
