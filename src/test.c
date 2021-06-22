/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   test.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ash <ash@student.42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/06/21 18:18:34 by sehyan            #+#    #+#             */
/*   Updated: 2021/06/22 17:22:33 by ash              ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

int main()
{
	int d;

	scanf("%d", &d);
	if (d == 1)
		m_pwd();
	char s[100];
	scanf("%s", s);
	m_cd(s);
	while(1)
	{
		int k;
		scanf("%d", &k);
		if (k == 2)
			m_exit();
		if (k == 3)
		{
			char str[100];
			int f;
			scanf("%s%d", str, &f);
			m_echo(str, f);
		}
	}
	
	return 0;
}