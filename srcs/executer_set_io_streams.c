/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   executer_set_io_streams.c                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lspiess <lspiess@student.42.us.org>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/06/16 07:23:51 by lspiess           #+#    #+#             */
/*   Updated: 2020/07/01 15:58:11 by lspiess          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static void		redir_input(t_ast_node *astroot, t_cmd_info *io)
{
	check_dollar(astroot, io, &(io->input_file_name));
	if ((io->input_fd = open(io->input_file_name, O_RDONLY)) == -1)
		executer_exit_process(astroot, io, errno, 1);
	dup2(io->input_fd, STDIN_FILENO);
	close(io->input_fd);
}

static void		redir_output(t_ast_node *astroot, t_cmd_info *io)
{
	check_dollar(astroot, io, &(io->output_file_name));
	if ((io->output_fd = open(io->output_file_name, O_RDWR | O_CREAT \
			| O_TRUNC, S_IRUSR | S_IWUSR | S_IRGRP | S_IROTH)) == -1)
		executer_exit_process(astroot, io, errno, 1);
	dup2(io->output_fd, STDOUT_FILENO);
	close(io->output_fd);
}

static void		redir_append(t_ast_node *astroot, t_cmd_info *io)
{
	check_dollar(astroot, io, &(io->output_file_name));
	if ((io->output_fd = open(io->output_file_name, O_RDWR | O_CREAT \
			| O_APPEND, S_IRUSR | S_IWUSR | S_IRGRP | S_IROTH)) == -1)
		executer_exit_process(astroot, io, errno, 1);
	dup2(io->output_fd, STDOUT_FILENO);
	close(io->output_fd);
}

/*
** Open the applicable fds based on the node type and the filenames previously
** stored in the t_cmd_info struct (see func get_io_filenames)
*/

void			set_io_streams(t_ast_node *astroot, t_cmd_info *io, \
								t_ast_node *node)
{
	if (node->type == REDIR_INPUT)
		redir_input(astroot, io);
	else if (node->type == REDIR_OUTPUT)
		redir_output(astroot, io);
	else if (node->type == REDIR_APPEND)
		redir_append(astroot, io);
	else if (node->type == REDIR_INPUT_AND_OUTPUT)
	{
		redir_input(astroot, io);
		redir_output(astroot, io);
	}
	else if (node->type == REDIR_INPUT_AND_APPEND)
	{
		redir_input(astroot, io);
		redir_append(astroot, io);
	}
}
