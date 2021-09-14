/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser_build_arg_tree.c                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lspiess <lspiess@student.42.us.org>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/06/18 05:25:38 by lspiess           #+#    #+#             */
/*   Updated: 2020/06/18 05:34:49 by lspiess          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

t_ast_node		*build_arg_tree(void)
{
	t_ast_node		*argtree;
	char			*argstring;

	if (check_toktype(REGULAR_CHARS, &argstring) == FALSE)
		return (NULL);
	if (!(argtree = ast_alloc_node()))
		return (NULL);
	argtree->data = argstring;
	argtree->type = ARG;
	argtree->right = build_arg_tree();
	return (argtree);
}
