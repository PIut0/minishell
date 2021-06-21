/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strmapi.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: klim <klim@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/12/25 06:05:09 by klim              #+#    #+#             */
/*   Updated: 2020/12/27 19:52:25 by klim             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char		*ft_strmapi(char const *s, char (*f)(unsigned int, char))
{
	char	*r;
	int		i;

	if (!s || !f || !(r = (char*)malloc(ft_strlen(s) + 1)))
		return (0);
	i = -1;
	while (s[++i])
		r[i] = f(i, s[i]);
	r[i] = 0;
	return (r);
}
