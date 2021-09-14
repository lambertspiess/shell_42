/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   executer_execve.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lspiess <lspiess@student.42.us.org>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/06/11 15:42:46 by lspiess           #+#    #+#             */
/*   Updated: 2020/06/28 14:26:59 by lspiess          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

/*
** void			print_io_status(t_cmd_info *io)
** {
** ft_printf_fd(io->default_fd[0],
**	ANSI_COLOR_CYAN"--------------print_io_status\n"ANSI_COLOR_RESET);
** ft_printf_fd(io->default_fd[0], "reads_from_pipe = %d,
**	writes_to_pipe = %d, pipe write fd %d, pipe read fd %d\n",
** 	io->reads_input_from_pipe, io->writes_output_to_pipe,
** 	io->pipe_write_fd, io->pipe_read_fd);
** ft_printf_fd(io->default_fd[0],
** 	"input fd = %d, output fd = %d, input file name %s, output file name %s\n",
** 	io->input_fd, io->output_fd, io->input_file_name, io->output_file_name);
** ft_printf_fd(io->default_fd[0],
**	"STDIN_FILENO = %d, STDOUT_FILENO = %d\n",
** 	STDIN_FILENO, STDOUT_FILENO);
** ft_printf_fd(io->default_fd[0],
**	ANSI_COLOR_CYAN"--------------\n"ANSI_COLOR_RESET);
** }
*/

static void		execve_with_given_path(t_ast_node *astroot, t_cmd_info *io)
{
	int				ret;

	ret = execve(io->av[0], io->av, io->envstrarr);
	errmsg_no_such_file_or_directory(io->av[0], NULL);
	executer_exit_process(astroot, io, ret, 0);
}

static void		execve_with_default_path(t_ast_node *astroot, t_cmd_info *io)
{
	char			*path;
	char			*pathcmd;
	int				i;

	i = 0;
	while (io->pathstrarr[i])
	{
		if (!(path = ft_strjoin(io->pathstrarr[i], "/")))
			executer_exit_process(astroot, io, errno, 1);
		if (!(pathcmd = ft_strjoin(path, io->av[0])))
		{
			free(path);
			executer_exit_process(astroot, io, errno, 1);
		}
		free(path);
		execve(pathcmd, io->av, io->envstrarr);
		free(pathcmd);
		i++;
	}
	errmsg_command_not_found(io->av[0]);
	executer_exit_process(astroot, io, 127, 0);
}

void			executer_execve(t_ast_node *astroot, t_cmd_info *io)
{
	if (ft_strchr(io->av[0], '/'))
		execve_with_given_path(astroot, io);
	else
		execve_with_default_path(astroot, io);
}
