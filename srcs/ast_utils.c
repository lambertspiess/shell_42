/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ast_utils.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lspiess <lspiess@student.42.us.org>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/05/14 22:18:20 by lspiess           #+#    #+#             */
/*   Updated: 2020/07/01 17:27:16 by lspiess          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

t_ast_node			*ast_alloc_node(void)
{
	t_ast_node			*new;

	if (!(new = malloc(sizeof(t_ast_node))))
		return (NULL);
	new->type = -1;
	new->data = NULL;
	new->data2 = NULL;
	new->left = NULL;
	new->right = NULL;
	return (new);
}

char				*ast_free_tree(t_ast_node *node)
{
	if (node == NULL)
		return (NULL);
	if (node->left)
		ast_free_tree(node->left);
	if (node->right)
		ast_free_tree(node->right);
	if (node->data)
	{
		free(node->data);
		node->data = NULL;
	}
	if (node->data2)
	{
		free(node->data2);
		node->data2 = NULL;
	}
	free(node);
	node = NULL;
	return (NULL);
}
