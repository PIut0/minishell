/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sehyan <sehyan@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/06/21 14:20:02 by klim              #+#    #+#             */
/*   Updated: 2021/06/23 14:13:56 by sehyan           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_H
# define MINISHELL_H

# include <unistd.h>
# include <stdio.h>
# include <limits.h>
# include <stdlib.h>

int		get_next_line(int fd, char **line);

void	m_pwd(void);
void	m_cd(char *s);
void    m_exit(void);
void    m_echo(char *s, int flag);
// void	m_env(void);
void	m_exec(char *s);
#endif
