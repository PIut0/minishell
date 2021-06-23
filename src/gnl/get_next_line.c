/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: klim <klim@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/01/01 21:08:23 by klim              #+#    #+#             */
/*   Updated: 2021/06/21 14:58:21 by klim             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/get_next_line.h"
#include "../include/minishell.h"

int		is_newline(char *buf)
{
	int i;

	i = 0;
	while (buf[i])
	{
		if (buf[i] == '\n')
			return (i);
		i++;
	}
	return (-1);
}

char	*ft_strmerge(char *s1, char *s2)
{
	char	*ret;

	if (!s1)
		return (ft_strdup(s2));
	ret = ft_strjoin(s1, s2);
	free(s1);
	return (ret);
}

int		split_line(char **backup, char **line, int nl)
{
	char	*temp;

	(*backup)[nl] = 0;
	*line = ft_strdup(*backup);
	if (!ft_strlen(*backup + nl + 1))
	{
		free(*backup);
		*backup = 0;
		return (1);
	}
	temp = ft_strdup(*backup + nl + 1);
	free(*backup);
	*backup = temp;
	return (1);
}

int		return_all(char **backup, char **line, int status)
{
	int		nl;

	if (status < 0)
		return (-1);
	if (*backup && (nl = is_newline(*backup)) >= 0)
		return (split_line(backup, line, nl));
	else if (*backup)
	{
		*line = *backup;
		*backup = 0;
		return (0);
	}
	*line = ft_strdup("");
	return (0);
}

int		get_next_line(int fd, char **line)
{
	static char	*backup;
	char		*buf;
	int			status;
	int			nl;

	if ((fd < 0) || (line == 0) || (BUFFER_SIZE <= 0))
		return (-1);
	buf = malloc(BUFFER_SIZE + 1);
	while ((status = read(fd, buf, BUFFER_SIZE)) > 0)
	{
		buf[status] = 0;
		backup = ft_strmerge(backup, buf);
		if ((nl = is_newline(backup)) >= 0)
			break ;
	}
	free(buf);
	return (return_all(&backup, line, status));
}
