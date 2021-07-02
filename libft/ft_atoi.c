/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_atoi.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sehyan <sehyan@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/12/23 15:19:59 by klim              #+#    #+#             */
/*   Updated: 2021/07/02 16:04:39 by sehyan           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static int	is_np(char c)
{
	if (c == '-' || c == '+')
		return (1);
	else
		return (0);
}

static int	is_space(char c)
{
	if (c == '\t' || c == '\n' || c == '\v'
		|| c == '\f' || c == '\r' || c == ' ')
		return (1);
	else
		return (0);
}

static int	is_overflow(long long n, char s, int c)
{
	if ((n != 0) && ((n >= 0 != ((n * 10) + (s - '0') * c) >= 0) ||
		(n >= 0 != (n << 3) >= 0) ||
		(n >= 0 != (n << 2) >= 0) ||
		(n >= 0 != (n << 1) >= 0)))
		return (1);
	return (0);
}

int			ft_isdigit(int c)
{
	if (c >= '0' && c <= '9')
		return (1);
	return (0);
}

int			ft_atoi(const char *str)
{
	long long	n;
	int			c;
	char		*s;

	n = 0;
	c = 1;
	s = (char *)str;
	while (is_space(*s))
		s++;
	if (is_np(*s))
	{
		c = (*s == '-') ? -1 : 1;
		s++;
	}
	while (ft_isdigit(*s))
	{
		if (is_overflow(n, *s, c) && n)
		{
			c = (c > 0) ? -1 : 0;
			return (c);
		}
		n = (n * 10) + (*s - '0') * c;
		s++;
	}
	return (n);
}
