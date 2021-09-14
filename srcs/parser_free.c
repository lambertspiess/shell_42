/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser_free.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lspiess <lspiess@student.42.us.org>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/05/11 16:18:02 by lspiess           #+#    #+#             */
/*   Updated: 2020/07/01 17:27:51 by lspiess          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void		free_ast(t_ast_node *node)
{
	if (!node)
		return ;
	if (node->left)
		free_ast(node->left);
	if (node->right)
		free_ast(node->right);
	if (node)
	{
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
	}
}

void		parser_fatal_error(t_lexical_list *lex, t_ast_node *tree)
{
	free_toklist(lex->tok);
	free_ast(tree);
	ft_printf_fd(2, "minishell: fatal error : ");
	ft_printf_fd(2, "%s\n", strerror(errno));
	exit(EXIT_FAILURE);
}
