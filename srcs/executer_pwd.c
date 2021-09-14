/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   executer_pwd.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lspiess <lspiess@student.42.us.org>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/05/26 00:14:39 by lspiess           #+#    #+#             */
/*   Updated: 2020/06/18 20:47:57 by lspiess          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

/*
** open() flags :
** O_RDWR, O_CREAT
** O_TRUNC : if file exists, it is truncated to 0 length (overwritten)
** S_IWUSR : write permission bit for the owner of the file (0200)
** S_IRUSR : read permission bit for the owner of the file (0400)
** S_IRGRP : read permission bit for the group owner of the file (040)
** S_IROTH : read permission bit for other users (04)
*/

int				execute_pwd(t_ast_node *astroot, t_ast_node *node, \
								t_cmd_info *io)
{
	char		cwd_name[1028];
	pid_t		pid;
	int			status;

	if ((pid = fork()) == -1)
		executer_exit_process(astroot, io, EXIT_FAILURE, 1);
	else if (pid == 0)
	{
		signal(SIGINT, SIG_DFL);
		signal(SIGQUIT, SIG_DFL);
		set_io_streams(astroot, io, node);
		if (!(getcwd(cwd_name, sizeof(cwd_name))))
			executer_exit_process(astroot, io, EXIT_FAILURE, 1);
		ft_printf_fd(STDOUT_FILENO, "%s\n", cwd_name);
		close(io->output_fd);
		executer_exit_process(astroot, io, EXIT_SUCCESS, 0);
	}
	wait(&status);
	return (status);
}
