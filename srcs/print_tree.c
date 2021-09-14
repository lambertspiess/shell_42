/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   print_tree.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lspiess <lspiess@student.42.us.org>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/05/18 01:50:13 by lspiess           #+#    #+#             */
/*   Updated: 2020/06/25 00:20:34 by lspiess          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	ft_print_type(int type)
{
	ft_printf("type = ");
	if (type == SEMICOLON)
		ft_printf("semicolon");
	else if (type == PIPE)
		ft_printf("pipe ");
	else if (type == REDIR_INPUT)
		ft_printf("redir < ");
	else if (type == REDIR_OUTPUT)
		ft_printf("redir > ");
	else if (type == REDIR_APPEND)
		ft_printf("append >> ");
	else if (type == EXECNAME)
		ft_printf("execpath");
	else if (type == ARG)
		ft_printf("arg");
	else if (type == REDIR_INPUT_AND_OUTPUT)
		ft_printf("redir < and >");
	else if (type == REDIR_INPUT_AND_APPEND)
		ft_printf("redir < and >>");
	ft_printf(", ");
}

void	ft_print_syntax_tree(t_ast_node *syntax_tree, int space)
{
	int		i;

	if (syntax_tree == NULL)
		return ;
	space += 15;
	ft_print_syntax_tree(syntax_tree->right, space);
	ft_printf("\n");
	i = 15;
	while (i < space)
	{
		ft_printf(" ");
		i++;
	}
	ft_print_type(syntax_tree->type);
	if (syntax_tree->data)
		ft_printf("data : {%s}", syntax_tree->data);
	if (syntax_tree->data2)
		ft_printf("data2 : {%s}", syntax_tree->data2);
	ft_printf("\n");
	ft_print_syntax_tree(syntax_tree->left, space);
}
