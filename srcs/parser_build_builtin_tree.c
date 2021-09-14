/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser_build_builtin_tree.c                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lspiess <lspiess@student.42.us.org>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/06/18 05:24:50 by lspiess           #+#    #+#             */
/*   Updated: 2020/06/18 05:42:11 by lspiess          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

t_ast_node		*build_builtin_tree(void)
{
	t_ast_node		*builtintree;
	char			*execname;

	if (check_toktype(REGULAR_CHARS, &execname) == FALSE)
		return (NULL);
	if (!(builtintree = ast_alloc_node()))
	{
		free(execname);
		return (NULL);
	}
	builtintree->data = execname;
	builtintree->type = EXECNAME;
	builtintree->right = build_arg_tree();
	return (builtintree);
}
