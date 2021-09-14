/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   executer_pipeline.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lspiess <lspiess@student.42.us.org>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/06/21 21:58:33 by lspiess           #+#    #+#             */
/*   Updated: 2020/06/25 01:27:35 by lspiess          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static void		init_pipes(int *pipefds, int pipecount, int *pipepids)
{
	int				i;

	i = 0;
	while (i < pipecount)
	{
		pipe(pipefds + i);
		i += 2;
	}
	i = 0;
	while (i <= pipecount)
		pipepids[i++] = -1;
}

static void		close_pipes(int *pipefds, int pipecount)
{
	int				i;
	int				fdcount;

	i = 0;
	fdcount = pipecount * 2;
	while (i < fdcount)
		close(pipefds[i++]);
}

static void		wait_pipeline_pids(int *pipepids, int pipecount)
{
	int				i;
	int				status;

	i = 0;
	while (i <= pipecount)
	{
		waitpid(pipepids[i], &status, 0);
		get_exit_code(status, -1);
		i++;
	}
}

static void		inside_forked_process(int *pipefds, int pipecount, \
						t_ast_node *node, t_cmd_info io)
{
	close_pipes(pipefds, pipecount);
	signal(SIGINT, SIG_DFL);
	signal(SIGQUIT, SIG_DFL);
	execute_command(getstat()->astroot, io, \
			node->type == PIPE ? node->left : node);
	executer_exit_process(getstat()->astroot, &io, getstat()->exitcode, 0);
}

void			execute_pipeline(t_ast_node *astroot, t_cmd_info io, \
									t_ast_node *node)
{
	int				pipefds[count_pipes(node) * 2];
	int				pipepids[count_pipes(node) + 1];
	int				i;
	int				pipecount;

	pipecount = count_pipes(node);
	init_pipes(pipefds, pipecount, pipepids);
	i = 0;
	while (i <= pipecount)
	{
		if ((pipepids[i] = fork()) == -1)
			executer_exit_process(astroot, &io, errno, 1);
		else if (pipepids[i] == 0)
		{
			if (node->type == PIPE)
				dup2(pipefds[i * 2 + 1], 1);
			if (i > 0)
				dup2(pipefds[(i - 1) * 2], 0);
			inside_forked_process(pipefds, pipecount, node, io);
		}
		node = node->right;
		i++;
	}
	close_pipes(pipefds, pipecount);
	wait_pipeline_pids(pipepids, pipecount);
}
