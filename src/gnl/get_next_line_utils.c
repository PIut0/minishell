/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line_utils.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: klim <klim@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/01/04 20:32:47 by klim              #+#    #+#             */
/*   Updated: 2021/06/23 17:00:40 by klim             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"

int		ft_strlen(char *s)
{
	int	i;

	i = 0;
	while (s[i])
		i++;
	return (i);
}

char	*ft_strdup(const char *s1)
{
	size_t	n;
	size_t	i;
	char	*t;

	n = ft_strlen((char *)s1);
	if (!(t = (char*)malloc(n + 1)))
		return (0);
	i = -1;
	while (++i < n)
		t[i] = s1[i];
	t[i] = 0;
	return (t);
}

char	*ft_strjoin(char const *s1, char const *s2)
{
	char	*r;
	char	*tmp;
	char	*t1;
	char	*t2;

	if (!s1 || !s2)
		return (0);
	t1 = (char *)s1;
	t2 = (char *)s2;
	if (!(r = (char *)malloc(ft_strlen(t1) + ft_strlen(t2) + 2)))
		return (0);
	tmp = r;
	while (*t1)
		*tmp++ = *t1++;
	while (*t2)
		*tmp++ = *t2++;
	*tmp = 0;
	return (r);
}

size_t	ft_strlcpy(char *dst, const char *src, size_t dstsize)
{
	size_t	i;

	if (!src)
		return (0);
	if (!dstsize)
		return (ft_strlen((char *)src));
	i = 0;
	while (i + 1 < dstsize && src[i])
	{
		dst[i] = src[i];
		i++;
	}
	dst[i] = 0;
	return (ft_strlen((char *)src));
}
