/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser_build_command_tree.c                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lspiess <lspiess@student.42.us.org>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/06/18 05:21:30 by lspiess           #+#    #+#             */
/*   Updated: 2020/07/01 17:04:41 by lspiess          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

/*
** COMMAND TREE
*/

t_ast_node		*build_command_tree(void)
{
	t_ast_node		*commandtree;
	t_tok			*toksave;

	toksave = g_curtok;
	if ((commandtree = build_command_tree_1()) != NULL)
		return (commandtree);
	g_curtok = toksave;
	if ((commandtree = build_command_tree_2()) != NULL)
		return (commandtree);
	g_curtok = toksave;
	if ((commandtree = build_command_tree_3()) != NULL)
		return (commandtree);
	g_curtok = toksave;
	if ((commandtree = build_command_tree_4()) != NULL)
		return (commandtree);
	g_curtok = toksave;
	return (NULL);
}

t_ast_node		*build_command_tree_1(void)
{
	t_ast_node		*commandtree;
	t_ast_node		*builtintree;
	char			*filename;
	int				lastredirtype;

	if (!(builtintree = build_builtin_tree()))
		return (NULL);
	if (check_toktype(TYPE_GREATER, NULL) == FALSE)
		return ((t_ast_node *)(ast_free_tree(builtintree)));
	lastredirtype = -1;
	if (!(filename = get_filename(1, &lastredirtype)) \
		|| (lastredirtype != REDIR_OUTPUT))
	{
		ft_free((void **)(&filename));
		return ((t_ast_node *)(ast_free_tree(builtintree)));
	}
	if (!(commandtree = ast_alloc_node()))
	{
		ft_free((void **)(&filename));
		return ((t_ast_node *)(ast_free_tree(builtintree)));
	}
	commandtree->data = filename;
	commandtree->type = REDIR_OUTPUT;
	commandtree->right = builtintree;
	return (commandtree);
}

t_ast_node		*build_command_tree_2(void)
{
	t_ast_node		*commandtree;
	t_ast_node		*builtintree;
	char			*filename;
	char			*redirout;
	int				lastredirtype;

	if (!(builtintree = build_builtin_tree()))
		return (NULL);
	if (check_toktype(TYPE_LESSER, NULL) == FALSE)
		return ((t_ast_node *)(ast_free_tree(builtintree)));
	if (check_toktype(REGULAR_CHARS, &filename) == FALSE)
		return ((t_ast_node *)(ast_free_tree(builtintree)));
	redirout = get_filename(0, &lastredirtype);
	if (!(commandtree = ast_alloc_node()))
	{
		ft_free((void **)(&filename));
		ft_free((void **)(&redirout));
		return ((t_ast_node *)(ast_free_tree(builtintree)));
	}
	commandtree->data = filename;
	commandtree->data2 = redirout;
	parser_bcm_determine_redirtype(commandtree, redirout, lastredirtype);
	commandtree->right = builtintree;
	return (commandtree);
}

t_ast_node		*build_command_tree_3(void)
{
	t_ast_node		*commandtree;
	t_ast_node		*builtintree;
	char			*filename;
	int				lastredirtype;

	if (!(builtintree = build_builtin_tree()))
		return (NULL);
	lastredirtype = -1;
	if (!(filename = get_filename(0, &lastredirtype)) \
		|| (lastredirtype != REDIR_APPEND))
	{
		ft_free((void **)(&filename));
		return ((t_ast_node *)(ast_free_tree(builtintree)));
	}
	if (!(commandtree = ast_alloc_node()))
	{
		ft_free((void **)(&filename));
		return ((t_ast_node *)(ast_free_tree(builtintree)));
	}
	commandtree->data = filename;
	commandtree->type = REDIR_APPEND;
	commandtree->right = builtintree;
	return (commandtree);
}

t_ast_node		*build_command_tree_4(void)
{
	t_ast_node		*builtintree;

	if (!(builtintree = build_builtin_tree()))
		return (NULL);
	if (check_toktype(TYPE_GREATER, NULL) || check_toktype(TYPE_LESSER, NULL))
		return ((t_ast_node *)(ast_free_tree(builtintree)));
	return (builtintree);
}
