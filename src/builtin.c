/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtin.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ash <ash@student.42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/06/21 18:12:56 by sehyan            #+#    #+#             */
/*   Updated: 2021/06/23 15:41:34 by ash              ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

void	m_pwd(void)
{
	char	buf[PATH_MAX];

	if (!(getcwd(buf, sizeof(buf))))
		return ; //error
	printf("%s\n", buf);
}

void	m_cd(char *s)
{
	int result;

	result = chdir(s);
	if(result == 0)
		m_pwd();
	else
		perror("Fail...\n");
}

void	m_exit(void)
{
	exit(0);
}

// void	m_export(char *s)
// {
// 	// example : JAVAHOME=/user/lib/java-7-openjdk-amd64/
// 	//			 ENV=hello
// 	//			 ENV="Hello, World!"
	
// }

// void	m_env(void)
// {
// 	execve("/usr/bin/env", "env", NULL);
// }

// void	m_exec(char *argv)
// {
// 	if(execve("/bin", &argv, NULL) == -1) {
// 		printf("프로그램 실행 error\n"); 
// 		return ; 
// 	}
// }

void	m_echo(char *s, int flag)
{
	if (flag == 0)
		printf("%s\n", s);
	else
		printf("%s", s);
}