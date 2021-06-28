/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   test.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sehyan <sehyan@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/06/21 14:02:23 by klim              #+#    #+#             */
/*   Updated: 2021/06/28 21:11:59 by sehyan           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include "minishell.h"

//void	processing(t_info *info)
//{
//	if (is_builtin(info->cmd))
//		builtin(info);
//	else if (is_path(info->cmd))
//		path(info);
//	else if (is_env(info->cmd))
//		env(info);
//	else if (is_execve(info))
//		run_execve(info);
//	else
//		err();
//	return ;
//}

void	print_env(t_env *env)
{
	t_node	*tmp;

	tmp = env->head->next;
	while (tmp != env->tail)
	{
		printf("%s=%s\n",tmp->key,tmp->value);
		tmp = tmp->next;
	}
	// printf("env suc\n");
}

int		shell_start(t_shell *shell)
{
	char	*line;
	t_info	*info;

	while (1)
	{
		if (!(info = init_info(shell)))
			continue ;
		ft_putstr_fd("minishell > ", 1);
		get_next_line(0, &line);
		if (parsing(line, info))
			continue ;
		if (process_info(info))
			continue ;
		free_info(info);
	}
}

t_shell		*init_shell(char **env_i)
{
	t_shell		*ret;

	if (!(ret = (t_shell*)malloc(sizeof(t_shell))))
		return (0);
	ret->env = init_env(env_i);
	return (ret);
}

int		main(int argc, char **argv, char **env)
{
	t_shell	*shell;
	argc = -1;

	(void) argv;
	if (!(shell = init_shell(env)))
		return (1);
	// print_env(shell->env);
	shell_start(shell);
}
