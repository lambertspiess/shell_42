/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   executer_env.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lspiess <lspiess@student.42.us.org>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/06/14 17:52:44 by lspiess           #+#    #+#             */
/*   Updated: 2020/06/28 14:05:36 by lspiess          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int				execute_env(t_ast_node *astroot, t_ast_node *node, \
								t_cmd_info *io)
{
	t_env			*env;
	pid_t			pid;
	int				status;

	if ((pid = fork()) == -1)
		executer_exit_process(astroot, io, errno, 1);
	else if (pid == 0)
	{
		signal(SIGINT, SIG_DFL);
		signal(SIGQUIT, SIG_DFL);
		set_io_streams(astroot, io, node);
		env = getstat()->env;
		while (env)
		{
			ft_printf_fd(STDOUT_FILENO, "%s=", env->key);
			if (env->value)
				ft_printf_fd(STDOUT_FILENO, "%s", env->value);
			ft_printf_fd(STDOUT_FILENO, "\n");
			env = env->next;
		}
		executer_exit_process(astroot, io, EXIT_SUCCESS, 0);
	}
	wait(&status);
	return (status);
}
