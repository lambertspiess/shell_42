/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   executer_get_cmd_av.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lspiess <lspiess@student.42.us.org>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/06/03 12:37:50 by lspiess           #+#    #+#             */
/*   Updated: 2020/06/30 05:40:32 by lspiess          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void			print_argv(t_cmd_info *io)
{
	int i;

	i = 0;
	ft_printf_fd(getstat()->default_fd[1], "\t%d, ac = %d\n", \
		getpid(), io->ac);
	while (i < io->ac)
	{
		ft_printf_fd(getstat()->default_fd[1], "\t%d, io->av[%d] = |%s|\n",
						getpid(), i, io->av[i]);
		i++;
	}
}

/*
** Store the command string along with its potential args in a malloc'd array
** of strings.
*/

int				get_cmd_av(t_ast_node *astroot, t_cmd_info *io, \
							t_ast_node *node)
{
	t_ast_node			*argnode;
	int					i;

	if (node->type != EXECNAME)
		return (-1);
	io->ac = 1;
	argnode = node->right;
	while (argnode && argnode->type == ARG)
	{
		io->ac++;
		argnode = argnode->right;
	}
	if (!(io->av = ft_memalloc(sizeof(char *) * (io->ac + 1))))
		executer_exit_process(astroot, io, errno, 1);
	argnode = node;
	i = 0;
	while (argnode && (argnode->type == ARG || argnode->type == EXECNAME))
	{
		if (!(io->av[i] = ft_strdup(argnode->data)))
			executer_exit_process(astroot, io, errno, 1);
		if (check_dollar(astroot, io, io->av + i++) == -1)
			return (-1);
		argnode = argnode->right;
	}
	return (0);
}
