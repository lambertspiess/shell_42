/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   executer_exit.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lspiess <lspiess@student.42.us.org>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/06/17 18:15:44 by lspiess           #+#    #+#             */
/*   Updated: 2020/06/25 01:30:51 by lspiess          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static int		is_valid_numstr(char *s)
{
	int				i;

	i = 0;
	while (s[i])
	{
		if (!('0' <= s[i] && s[i] <= '9'))
			return (0);
		i++;
	}
	return (1);
}

int				execute_exit(t_ast_node *astroot, t_ast_node *node, \
								t_cmd_info *io)
{
	int				ret;

	(void)(node);
	if (io->ac == 1)
		executer_exit_process(astroot, io, EXIT_SUCCESS, 0);
	if (!is_valid_numstr(io->av[1]))
	{
		ft_printf_fd(STDERR_FILENO,
			"minishell: exit: numeric argument required\n");
		executer_exit_process(astroot, io, 2, 0);
	}
	if (io->ac > 2)
	{
		ft_printf_fd(STDERR_FILENO,
			"minishell: exit: too many arguments\n");
		executer_exit_process(astroot, io, 2, 0);
	}
	ret = ft_atoi(io->av[1]);
	ft_printf_fd(STDOUT_FILENO, "exit\n");
	getstat()->exitcode = ret;
	executer_exit_process(astroot, io, ret, 0);
	return (ret);
}
