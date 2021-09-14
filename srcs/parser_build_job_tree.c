/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser_build_job_tree.c                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lspiess <lspiess@student.42.us.org>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/06/18 05:22:50 by lspiess           #+#    #+#             */
/*   Updated: 2020/07/01 16:57:25 by lspiess          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

/*
** JOB TREE
*/

t_ast_node		*build_job_tree(void)
{
	t_ast_node		*jobtree;
	t_tok			*toksave;

	toksave = g_curtok;
	if ((jobtree = build_job_tree_1()) != NULL)
		return (jobtree);
	g_curtok = toksave;
	if ((jobtree = build_job_tree_2()) != NULL)
		return (jobtree);
	return (NULL);
}

t_ast_node		*build_job_tree_1(void)
{
	t_ast_node		*commandtree;
	t_ast_node		*jobtree;
	t_ast_node		*pipenode;

	if (!(commandtree = build_command_tree()))
		return (NULL);
	if (check_toktype(TYPE_PIPE, NULL) == FALSE)
		return ((t_ast_node *)(ast_free_tree(commandtree)));
	if (!(jobtree = build_job_tree()))
		return ((t_ast_node *)(ast_free_tree(commandtree)));
	if (!(pipenode = ast_alloc_node()))
	{
		ast_free_tree(jobtree);
		return ((t_ast_node *)(ast_free_tree(commandtree)));
	}
	pipenode->type = PIPE;
	pipenode->left = commandtree;
	pipenode->right = jobtree;
	return (pipenode);
}

t_ast_node		*build_job_tree_2(void)
{
	t_ast_node		*commandtree;

	if (!(commandtree = build_command_tree()))
		return (NULL);
	if (check_toktype(TYPE_PIPE, NULL) == TRUE)
		return ((t_ast_node *)(ast_free_tree(commandtree)));
	return (commandtree);
}
