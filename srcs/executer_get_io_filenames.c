/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   executer_get_io_filenames.c                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lspiess <lspiess@student.42.us.org>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/06/24 22:49:24 by lspiess           #+#    #+#             */
/*   Updated: 2020/07/01 15:58:17 by lspiess          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

/*
** Checks a given AST node type for redirections.
** If applicable, store the relevant filenames in the t_cmd_info structure,
** in order to open the relevant fds later in a fork()
*/

void			get_io_filenames(t_ast_node *astroot, t_cmd_info *io, \
									t_ast_node *node)
{
	if (node->type == REDIR_INPUT || node->type == REDIR_INPUT_AND_OUTPUT \
		|| node->type == REDIR_INPUT_AND_APPEND)
	{
		if (!(io->input_file_name = ft_strdup(node->data)))
			executer_exit_process(astroot, io, errno, 1);
		io->cmdnode = node->right;
	}
	if (node->type == REDIR_OUTPUT || node->type == REDIR_APPEND)
	{
		if (!(io->output_file_name = ft_strdup(node->data)))
			executer_exit_process(astroot, io, errno, 1);
		io->cmdnode = node->right;
	}
	else if (node->type == REDIR_INPUT_AND_OUTPUT \
				|| node->type == REDIR_INPUT_AND_APPEND)
	{
		if (!(io->output_file_name = ft_strdup(node->data2)))
			executer_exit_process(astroot, io, errno, 1);
		io->cmdnode = node->right;
	}
}
