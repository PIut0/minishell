/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pwd.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sehyan <sehyan@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/06/21 18:12:56 by sehyan            #+#    #+#             */
/*   Updated: 2021/06/21 18:19:15 by sehyan           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

void	pwd(void)
{
	char	buf[PATH_MAX];

	if (!(getcwd(buf, sizeof(buf))))
		return ; //error
	printf("%s\n", buf);
}