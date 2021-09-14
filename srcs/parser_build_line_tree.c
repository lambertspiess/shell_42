/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser_build_line_tree.c                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lspiess <lspiess@student.42.us.org>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/06/18 05:23:45 by lspiess           #+#    #+#             */
/*   Updated: 2020/06/24 20:14:04 by lspiess          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

/*
** LINE_TREE
*/

t_ast_node		*build_line_tree(void)
{
	t_ast_node		*linetree;
	t_tok			*toksave;

	toksave = g_curtok;
	if ((linetree = build_line_tree_1()) != NULL)
		return (linetree);
	g_curtok = toksave;
	if ((linetree = build_line_tree_2()) != NULL)
		return (linetree);
	g_curtok = toksave;
	if ((linetree = build_line_tree_3()) != NULL)
		return (linetree);
	return (NULL);
}

t_ast_node		*build_line_tree_1(void)
{
	t_ast_node		*jobtree;
	t_ast_node		*linetree;
	t_ast_node		*semicolon;

	if (!(jobtree = build_job_tree()))
		return (NULL);
	if (check_toktype(TYPE_SEMICOLON, NULL) == FALSE)
		return ((t_ast_node *)(ast_free_tree(jobtree)));
	if (check_toktype(TYPE_SEMICOLON, NULL) == TRUE)
		return ((t_ast_node *)(ast_free_tree(jobtree)));
	if (!(linetree = build_line_tree()))
		return ((t_ast_node *)(ast_free_tree(jobtree)));
	if (!(semicolon = ast_alloc_node()))
	{
		ast_free_tree(jobtree);
		ast_free_tree(linetree);
		return (NULL);
	}
	semicolon->type = SEMICOLON;
	semicolon->left = jobtree;
	semicolon->right = linetree;
	return (semicolon);
}

t_ast_node		*build_line_tree_2(void)
{
	t_ast_node		*jobtree;
	t_ast_node		*semicolon;

	if (!(jobtree = build_job_tree()))
		return (NULL);
	if (check_toktype(TYPE_SEMICOLON, NULL) == FALSE)
		return ((t_ast_node *)(ast_free_tree(jobtree)));
	if (!(semicolon = ast_alloc_node()))
		return ((t_ast_node *)(ast_free_tree(jobtree)));
	if (check_toktype(TYPE_SEMICOLON, NULL) == TRUE)
	{
		ft_free((void **)(&semicolon));
		return ((t_ast_node *)(ast_free_tree(jobtree)));
	}
	semicolon->type = SEMICOLON;
	semicolon->left = jobtree;
	return (semicolon);
}

t_ast_node		*build_line_tree_3(void)
{
	t_ast_node		*jobtree;

	if (!(jobtree = build_job_tree()))
		return (NULL);
	if (g_curtok == NULL)
		return (jobtree);
	else
		return ((t_ast_node *)(ast_free_tree(jobtree)));
}
