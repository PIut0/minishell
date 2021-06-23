/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   test.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sehyan <sehyan@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/06/21 18:18:34 by sehyan            #+#    #+#             */
/*   Updated: 2021/06/23 15:07:53 by sehyan           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

int main(int argc, char *argv[])
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
			for (int i = 0; str[i] != '\n'; i++)
				scanf("%c", str[i]);
			m_echo(str, f);
		}
		if (k == 4){
			printf("here!\n");
			if (execve("/bin/env", argv, NULL) < 0)
				printf("error\n");
		}
	}
	
	return 0;
}