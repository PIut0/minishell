/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   input1.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: klim <klim@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/06/29 16:10:17 by klim              #+#    #+#             */
/*   Updated: 2021/06/30 13:50:12 by klim             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	set_input_mode(t_term *new_term, t_term *org_term)
{
	tcgetattr(STDIN_FILENO, org_term);
	tcgetattr(STDIN_FILENO, new_term);
	new_term->c_lflag &= ~(ICANON | ECHO);
	new_term->c_cc[VMIN] = 1;
	new_term->c_cc[VTIME] = 0;
	tcsetattr(STDIN_FILENO, TCSANOW, new_term);
}

void	reset_input_mode(t_term *org_term)
{
	tcsetattr(STDIN_FILENO, TCSANOW, org_term);
}

char	*add_char(char *str, char c)
{
	char	*ret;
	char	*tmp;

	if (c == 127)
	{
		ret = ft_substr(str, 0, ft_strlen(str) - 1);
		free(str);
	}
	else
	{
		if (!(tmp = (char *)malloc(2)))
			return (0);
		tmp[0] = c;
		tmp[1] = 0;
		ret = ft_strjoin_free(str, tmp, 3);
	}
	return (ret);
}

char	*reset_ret(char *ret)
{
	free(ret);
	ret = ft_strdup("");
	g_sig = 0;
	return (ret);
}

char	*get_input(int idx, char ch, char *ret)
{
	while (read(0, &ch, 1) > 0)
	{
		if (g_sig == SIGINT)
			ret = reset_ret(ret);
		if (ch == 4 && !idx)
			exit(0);
		else if (ch == 4 && idx)
			continue ;
		else if (ch == 127 && idx-- > 0)
			write(0, "\b \b", 3);
		else if (ch == 127)
			idx++;
		else if (ch == '\n')
			break ;
		else
		{
			++idx;
			write(0, &ch, 1);
		}
		if (!(ret = add_char(ret, ch)))
			return (0);
		ch = 0;
	}
	return (ret);
}

char	*get_line(void)
{
	char			*ret;
	t_term			org_term;
	t_term			new_term;

	set_input_mode(&new_term, &org_term);
	ret = ft_strdup("");
	ret = get_input(0, 0, ret);
	reset_input_mode(&org_term);
	return (ret);
}
