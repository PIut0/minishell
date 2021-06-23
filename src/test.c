/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   test.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ash <ash@student.42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/06/21 18:18:34 by sehyan            #+#    #+#             */
/*   Updated: 2021/06/23 15:24:05 by ash              ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

int main(void)
{
	// char s[100];
	// scanf("%s", s);
	// m_cd(s);
	while(1)
	{
		int k;
		scanf("%d", &k);
		if (k == 1)
			m_pwd();
		if (k == 2)
			m_exit();
		if (k == 3)
		{
			char str[100];
			int f;
			f = 0;
			scanf("%s", str);
			m_echo(str, f);
		}
		if (k == 4){
			char argv[100];
			scanf("%s", argv);
			m_exec(argv);
		}
	}
	
	return 0;
}