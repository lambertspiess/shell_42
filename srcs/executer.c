/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   executer.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lspiess <lspiess@student.42.us.org>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/05/19 03:41:27 by lspiess           #+#    #+#             */
/*   Updated: 2020/06/28 14:25:33 by lspiess          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static t_builtin_tab	g_tab[] = {
	{"pwd", &execute_pwd},
	{"env", &execute_env},
	{"export", &execute_export},
	{"unset", &execute_unset},
	{"echo", &execute_echo},
	{"cd", &execute_cd},
	{"exit", &execute_exit},
	{NULL, NULL},
};

/*
** In a fork, set up the input/output fds', and launch an execve routine.
*/

int				launch_host_bin(t_ast_node *astroot, t_ast_node *node,
							t_cmd_info *io)
{
	pid_t			pid;
	int				status;

	if ((pid = fork()) == -1)
		executer_exit_process(astroot, io, errno, 1);
	if (pid == 0)
	{
		signal(SIGINT, SIG_DFL);
		signal(SIGQUIT, SIG_DFL);
		get_envstrarr(astroot, io, getstat()->env);
		get_pathstrarr(astroot, io);
		set_io_streams(astroot, io, node);
		executer_execve(astroot, io);
		executer_exit_process(astroot, io, EXIT_SUCCESS, 0);
	}
	waitpid(pid, &status, 0);
	return (status);
}

/*
** Look for built-ins to launch. If not found, will launch an execve routine.
*/

void			launch(t_ast_node *astroot, t_ast_node *node, t_cmd_info *io)
{
	int					i;

	i = 0;
	while (g_tab[i].execname != NULL)
	{
		if (ft_strequ(io->cmdnode->data, g_tab[i].execname))
		{
			get_exit_code(-1, g_tab[i].execute_exec(astroot, node, io));
			return ;
		}
		i++;
	}
	get_exit_code(launch_host_bin(astroot, node, io), -1);
}

/*
** Store redirection information, build the command's argv, and launch.
*/

void			execute_command(t_ast_node *astroot, t_cmd_info io, \
								t_ast_node *node)
{
	if (node->type == REDIR_INPUT || node->type == REDIR_OUTPUT \
		|| node->type == REDIR_APPEND || node->type == REDIR_INPUT_AND_OUTPUT \
		|| node->type == REDIR_INPUT_AND_APPEND)
		get_io_filenames(astroot, &io, node);
	else
		io.cmdnode = node;
	if (io.cmdnode != NULL && get_cmd_av(astroot, &io, io.cmdnode) == 0)
		launch(astroot, node, &io);
	free_cmd_av(&io);
	ft_free((void **)(&(io.input_file_name)));
	ft_free((void **)(&(io.output_file_name)));
}

void			execute_job(t_ast_node *astroot, t_ast_node *node)
{
	t_cmd_info		io;

	ft_bzero(&io, sizeof(t_cmd_info));
	if (!node)
		return ;
	if (node->type == PIPE)
		execute_pipeline(astroot, io, node);
	else
		execute_command(astroot, io, node);
}

void			execute_line(t_ast_node *root, t_ast_node *node)
{
	static t_ast_node	*astroot;

	if (!root || !node)
		return ;
	(void)(root);
	astroot = node;
	getstat()->busy_executing = 1;
	if (node->type == SEMICOLON)
	{
		execute_job(astroot, node->left);
		execute_line(astroot, node->right);
	}
	else
		execute_job(astroot, node);
	getstat()->busy_executing = 0;
}
