/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   input1.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: klim <klim@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/06/29 16:10:17 by klim              #+#    #+#             */
/*   Updated: 2021/07/07 15:54:08 by klim             ###   ########.fr       */
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

char	*add_char(char *str, int c)
{
	char	*ret;
	char	*tmp;

	if (c == 127)
	{
		ret = ft_substr(str, 0, ft_strlen(str) - 1);
		free(str);
	}
	else if (c == _UP || c == _DOWN || c == _LEFT || c == _RIGHT)
		return (str);
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

char	*get_input(int idx, int ch, char *ret, t_shell *shell)
{
	while ((shell->eof = read(0, &ch, sizeof(int))) > 0)
	{
		if (g_signal.sig == SIGINT)
			ret = reset_ret(ret, &idx);
		if (ch == 4 && !idx)
			return (err_ptr("exit", 0));
		else if ((ch == 4 && idx) || ch == '\t' || ch == _LEFT || ch == _RIGHT)
			continue ;
		else if (ch == _UP || ch == _DOWN)
			ret = history_ret(ch, ret, shell, &idx);
		else if (ch == 127 && idx-- > 0)
			write(0, "\b \b", 3);
		else if (ch == 127)
			idx++;
		else if (ch == '\n' || ch == _LEFT - 17 || ch == _RIGHT - 17)
			break ;
		else if (++idx)
			write(0, &ch, 1);
		if (!(ret = add_char(ret, ch)))
			return (err_ptr("malloc err", 0));
		ch = 0;
	}
	write(0, "\n", 1);
	return (ret);
}

char	*get_line(t_shell *shell)
{
	char			*ret;
	t_term			org_term;
	t_term			new_term;

	set_input_mode(&new_term, &org_term);
	ret = ft_strdup("");
	ret = get_input(0, 0, ret, shell);
	reset_input_mode(&org_term);
	if (!ret)
		exit(0);
	return (ret);
}
