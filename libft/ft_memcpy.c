/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memcpy.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: klim <klim@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/12/22 15:19:25 by klim              #+#    #+#             */
/*   Updated: 2020/12/26 14:26:42 by klim             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	*ft_memcpy(void *dst, const void *src, size_t n)
{
	size_t			i;
	unsigned char	*t1;
	unsigned char	*t2;

	if ((!dst && !src) || !n)
		return (dst);
	i = 0;
	t1 = (unsigned char *)dst;
	t2 = (unsigned char *)src;
	while (i < n)
	{
		t1[i] = t2[i];
		i++;
	}
	return (dst);
}
