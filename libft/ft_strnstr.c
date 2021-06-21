/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strnstr.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: klim <klim@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/12/22 22:23:31 by klim              #+#    #+#             */
/*   Updated: 2020/12/28 18:50:59 by klim             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strnstr(const char *haystack, const char *needle, size_t len)
{
	size_t	i;
	size_t	j;
	char	*t;

	if (!needle[0])
		return ((char *)haystack);
	i = -1;
	t = (char *)haystack;
	while (++i < len && haystack[i])
	{
		j = 0;
		while (haystack[i + j] && needle[j] &&
			i + j <= len && haystack[i + j] == needle[j])
			j++;
		if (!needle[j])
			return (t + i);
	}
	return (0);
}
