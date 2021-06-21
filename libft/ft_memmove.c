/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memmove.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: klim <klim@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/12/22 15:58:06 by klim              #+#    #+#             */
/*   Updated: 2020/12/26 14:34:07 by klim             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	*ft_memmove(void *dst, const void *src, size_t len)
{
	size_t			i;
	unsigned char	*t1;
	unsigned char	*t2;

	if ((!dst && !src) || !len)
		return (dst);
	i = 0;
	t1 = (unsigned char *)dst;
	t2 = (unsigned char *)src;
	if (dst < src)
		while (i < len)
		{
			t1[i] = t2[i];
			i++;
		}
	else
		while (i < len)
		{
			t1[len - i - 1] = t2[len - i - 1];
			i++;
		}
	return (dst);
}
