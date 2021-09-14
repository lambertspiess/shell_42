/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   executer_echo.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lspiess <lspiess@student.42.us.org>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/06/16 17:43:58 by lspiess           #+#    #+#             */
/*   Updated: 2020/06/28 14:27:34 by lspiess          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static void		echo(t_cmd_info *io)
{
	int				i;
	int				nl;

	i = 1;
	nl = 1;
	if (ft_strequ(io->av[1], "-n"))
	{
		i++;
		nl = 0;
	}
	while (i < io->ac)
	{
		ft_printf_fd(STDOUT_FILENO, "%s", io->av[i]);
		i++;
		if (i < io->ac)
			ft_printf_fd(STDOUT_FILENO, " ");
	}
	if (nl)
		ft_printf_fd(STDOUT_FILENO, "\n");
}

int				execute_echo(t_ast_node *astroot, t_ast_node *node, \
								t_cmd_info *io)
{
	pid_t			pid;
	int				status;

	(void)(astroot);
	(void)(node);
	if ((pid = fork()) == -1)
		executer_exit_process(astroot, io, EXIT_FAILURE, 1);
	else if (pid == 0)
	{
		set_io_streams(astroot, io, node);
		if (io->ac == 1)
			ft_printf_fd(STDOUT_FILENO, "\n");
		else
			echo(io);
		executer_exit_process(astroot, io, EXIT_SUCCESS, 0);
	}
	wait(&status);
	return (status);
}
