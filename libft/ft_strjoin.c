/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strjoin.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: klim <klim@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/12/23 18:26:31 by klim              #+#    #+#             */
/*   Updated: 2020/12/27 19:27:25 by klim             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

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
	if (!(r = (char *)malloc(ft_strlen(t1) + ft_strlen(t2) + 1)))
		return (0);
	tmp = r;
	while (*t1)
		*tmp++ = *t1++;
	while (*t2)
		*tmp++ = *t2++;
	*tmp = 0;
	return (r);
}
