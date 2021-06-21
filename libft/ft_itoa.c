/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_itoa.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: klim <klim@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/12/25 05:30:15 by klim              #+#    #+#             */
/*   Updated: 2020/12/28 18:51:44 by klim             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static char	*rev_data(char *t, int n)
{
	char	*r;
	int		i;

	if (!(r = (char *)malloc(n + 1)))
		return (0);
	i = -1;
	while (++i < n)
		r[i] = t[n - i - 1];
	r[i] = 0;
	return (r);
}

char		*ft_itoa(int n)
{
	char	t[12];
	int		i;
	int		np;

	i = 0;
	if (!n && ++i)
		t[0] = '0';
	np = (n < 0) ? -1 : 1;
	while (n)
	{
		t[i] = (n % 10) * np + '0';
		n /= 10;
		i++;
	}
	if (np < 0)
		t[i++] = '-';
	return (rev_data(t, i));
}
