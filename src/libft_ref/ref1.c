/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ref1.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sehyan <sehyan@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/06/25 16:03:00 by klim              #+#    #+#             */
/*   Updated: 2021/07/03 15:51:35 by sehyan           ###   ########.fr       */
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
	ret = ft_strdup("");
	i = -1;
	while (sp[++i])
		ret = ft_strjoin_free(ret, sp[i], 3);
	free(sp);
	return (ret);
}

char		*ft_sp_merge2(char **sp, char *c)
{
	int		i;
	char	*ret;

	if (!sp)
		return (0);
	ret = ft_strdup("");
	i = -1;
	while (sp[++i])
	{
		ret = ft_strjoin_free(ret, c, 1);
		ret = ft_strjoin_free(ret, sp[i], 3);
	}
	free(sp);
	return (ret);
}

int			ft_strcmp(char *s1, char *s2)
{
	int		i;

	i = 0;
	if (!s1 || !s2)
		return (0);
	while (s1[i] == s2[i] && s1[i] && s2[i])
		i++;
	if (i == (int)ft_strlen(s1) && i == (int)ft_strlen(s2))
		return (1);
	return (0);
}
