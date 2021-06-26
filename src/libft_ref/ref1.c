/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ref1.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: klim <klim@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/06/25 16:03:00 by klim              #+#    #+#             */
/*   Updated: 2021/06/26 19:26:03 by klim             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

char		*ft_strjoin_free(char *s1, char *s2, int n)
{
	char	*ret;

	ret = ft_strjoin(s1, s2);
	if (s1 && (n == 1 || n == 3))
		free(s1);
	if (s2 && (n == 2 || n == 3))
		free(s2);
	return (ret);
}

char		*ft_sp_merge(char **sp)
{
	int		i;
	char	*ret;

	if (!sp)
		return (0);
	ret = (char *)malloc(1);
	i = -1;
	while (sp[++i])
		ret = ft_strjoin_free(ret, sp[i], 3);
	free(sp);
	return (ret);
}
