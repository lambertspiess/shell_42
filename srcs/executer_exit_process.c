/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   executer_exit_process.c                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lspiess <lspiess@student.42.us.org>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/06/07 15:26:45 by lspiess           #+#    #+#             */
/*   Updated: 2020/06/25 01:31:48 by lspiess          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static void		free_io(t_cmd_info *io)
{
	free_cmd_av(io);
	free_str_arr(io->pathstrarr);
	io->pathstrarr = 0;
	free_str_arr(io->envstrarr);
	io->envstrarr = 0;
	if (io->input_file_name != NULL)
		close(io->input_fd);
	if (io->output_file_name != NULL)
		close(io->output_fd);
	ft_free((void **)(&(io->input_file_name)));
	ft_free((void **)(&(io->output_file_name)));
	if (io->reads_input_from_pipe)
		close(io->pipe_read_fd);
	if (io->writes_output_to_pipe)
		close(io->pipe_write_fd);
}

static void		close_fds(int fd1, int fd2, int fd3, int fd4)
{
	if (fd1 > -1)
		close(fd1);
	if (fd2 > -1)
		close(fd2);
	if (fd3 > -1)
		close(fd3);
	if (fd4 > -1)
		close(fd4);
}

/*
** Free all the dynamically allocated memory of the current process and exit
*/

void			executer_exit_process(t_ast_node *astree, t_cmd_info *io, \
										int ret, int print)
{
	if (io)
		free_io(io);
	if (astree)
	{
		free_ast(astree);
		astree = NULL;
	}
	if (print)
	{
		ft_printf_fd(getstat()->default_fd[2],
		ANSI_COLOR_RED"minishell: %s\n"ANSI_COLOR_RESET, strerror(ret));
	}
	if (getstat() != NULL)
	{
		if (getstat()->env != NULL)
			free_env_list(getstat()->env);
		close_fds(getstat()->default_fd[0], getstat()->default_fd[1], \
					getstat()->default_fd[2], -1);
	}
	exit(getstat()->exitcode);
}

/*
** If the executable was a built-in, the exit code will the the return value
** of that function. If the executable was not a built-in, the exit code will
** be interpreted from the process status set by wait().
**
** WIFEXITED returns true if the process was terminated by a call to exit()
**     WEXITSTATUS returns the exit code of the process, equal to the 8 least
**     significant bits of the exit() value.
** WIFSIGNALED returns true if the process was terminated by a signal.
**     WTERMSIG returns the signal numbers that terminated the process.
**     In most  shells, when a process is terminated by a signal, the exit
**     value is the signal value + 128
*/

void			get_exit_code(int process_status, int ret)
{
	if (ret == -1)
	{
		if (WIFEXITED(process_status))
			getstat()->exitcode = WEXITSTATUS(process_status);
		else if (WIFSIGNALED(process_status))
			getstat()->exitcode = 128 + WTERMSIG(process_status);
		else
			getstat()->exitcode = process_status;
	}
	else
		getstat()->exitcode = ret;
}
