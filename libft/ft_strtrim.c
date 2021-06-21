/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strtrim.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: klim <klim@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/12/23 23:48:22 by klim              #+#    #+#             */
/*   Updated: 2020/12/25 05:49:11 by klim             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strtrim(char const *s1, char const *set)
{
	char	*t;
	size_t	i;
	size_t	end;

	if (!s1 || !set)
		return (0);
	i = 0;
	while (s1[i] && ft_strchr(set, s1[i]))
		i++;
	end = ft_strlen(s1 + i);
	while (end && s1[i + end - 1] && ft_strchr(set, s1[i + end - 1]))
		end--;
	if (!(t = (char *)malloc(end + 1)))
		return (0);
	ft_strlcpy(t, s1 + i, end + 1);
	return (t);
}
