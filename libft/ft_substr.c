/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_substr.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sehyan <sehyan@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/12/23 18:18:09 by klim              #+#    #+#             */
/*   Updated: 2021/07/02 15:23:29 by sehyan           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_substr(char const *s, unsigned int start, size_t len)
{
	char	*t;

	if (!s || !(t = (char *)malloc(len + 1)))
		return (0);
	if (start >= ft_strlen(s) || !ft_strlcpy(t, s + start, len + 1))
		t[0] = 0;
	return (t);
}
