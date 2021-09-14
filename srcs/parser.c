/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lspiess <lspiess@student.42.us.org>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/05/14 15:04:30 by lspiess           #+#    #+#             */
/*   Updated: 2020/07/01 14:44:26 by lspiess          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

/*
** Recursive Descent Parsing algorithm for a subset of bash grammar
**
** DESCRIPTION
** Using backtracking, recursively test a linked list of bash-style tokens
** for all supported grammars, and organize them into an abstract syntax tree.
**
**    BNF :                                           HANDLER FUNCTION :
**    line     ::=       <job> ';' <line>             build_line_tree_1
**               |       <job> ';'                    build_line_tree_2
**               |       <job>                        build_line_tree_3
**
**    job      ::=       <command> '|' <job>          build_job_tree_1
**               |       <command>                    build_job_tree_2
**
**    command  ::=       <builtin> '>'  <filename>    build_command_tree_1
**               |       <builtin> '<'  <filename>    build_command_tree_2
**               |       <builtin> '>>' <filename>    build_command_tree_3
**               |       <builtin>                    build_command_tree_4
**
**    filename ::=       <filename> '>' <filename>
**               |       <filename> '>>' <filename>
**
**    builtin  ::=       <execname> <args>            build_builtin_tree
**               |       <execname>                   build_builtin_tree
**
**    args      ::=      <arg> <args>                 build_arg_tree
**               |       <nothing>                    build_arg_tree
*/

t_tok				*g_curtok;

/*
** To reset the token-list pointer when backtracking
*/

int				reset(t_tok *tok)
{
	g_curtok = tok;
	return (1);
}

int				check_toktype(int checktype, char **data_store)
{
	if (g_curtok == NULL)
		return (FALSE);
	if (g_curtok->type == checktype)
	{
		if (checktype == REGULAR_CHARS && data_store != NULL)
			*data_store = ft_strdup(g_curtok->s);
		g_curtok = g_curtok->next;
		return (TRUE);
	}
	return (FALSE);
}

/*
** parser
*/

t_ast_node		*parse_tokens(t_lexical_list *lex)
{
	t_ast_node		*tree;

	if (!lex)
		return (NULL);
	if (!(lex->tok))
		return (NULL);
	g_curtok = lex->tok;
	if (!(tree = build_line_tree()))
	{
		ft_printf("minishell: syntax error\n");
		getstat()->exitcode = 2;
	}
	return (tree);
}
