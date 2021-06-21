/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memccpy.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: klim <klim@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/12/22 15:38:47 by klim              #+#    #+#             */
/*   Updated: 2020/12/26 14:27:33 by klim             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	*ft_memccpy(void *dst, const void *src, int c, size_t n)
{
	size_t			i;
	unsigned char	*t1;
	unsigned char	*t2;

	i = -1;
	t1 = (unsigned char *)dst;
	t2 = (unsigned char *)src;
	while (++i < n)
	{
		t1[i] = t2[i];
		if (t2[i] == (unsigned char)c)
			return (dst + i + 1);
	}
	return (0);
}
