/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memset.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: klim <klim@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/12/22 12:21:44 by klim              #+#    #+#             */
/*   Updated: 2020/12/26 14:23:49 by klim             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	*ft_memset(void *b, int c, size_t len)
{
	size_t			i;
	unsigned char	*tmp;

	if (!len)
		return (b);
	tmp = (unsigned char *)b;
	i = -1;
	while (++i < len)
		*(tmp + i) = (unsigned char)c;
	return (b);
}
