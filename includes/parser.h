/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lspiess <lspiess@student.42.us.org>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/05/08 12:22:57 by lspiess           #+#    #+#             */
/*   Updated: 2020/07/01 09:32:38 by lspiess          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PARSER_H
# define PARSER_H
# include "minishell_structs.h"

extern t_tok			*g_curtok;

int						reset(t_tok *tok);

int						check_toktype(int checktype, char **data_store);

void					parser_fatal_error(t_lexical_list *lex, \
												t_ast_node *tree);

void					count_node(t_ast_node *tree, int *countp);

void					ft_print_syntax_tree(t_ast_node *syntax_tree, \
												int space);

t_ast_node				*ast_alloc_node();
char					*ast_free_tree(t_ast_node *node);

/*
** parser_build_line_tree.c
*/

t_ast_node				*build_line_tree();
t_ast_node				*build_line_tree_1();
t_ast_node				*build_line_tree_2();
t_ast_node				*build_line_tree_3();

/*
** parser_build_job_tree.c
*/

t_ast_node				*build_job_tree();
t_ast_node				*build_job_tree_1();
t_ast_node				*build_job_tree_2();

/*
** parser_build_command_tree.c
*/

t_ast_node				*build_command_tree();
t_ast_node				*build_command_tree_1();
t_ast_node				*build_command_tree_2();
t_ast_node				*build_command_tree_3();
t_ast_node				*build_command_tree_4();

/*
** parser_build_command_tree_get_filename.c
*/

char					*get_filename(int gtsigncount, int *redirtype);
void					parser_bcm_determine_redirtype(t_ast_node \
								*commandtree, char *redirout, int redirtype);

t_ast_node				*build_builtin_tree();

t_ast_node				*build_arg_tree();

void					ft_print_syntax_tree(t_ast_node *syntax_tree, int level);
t_ast_node				*parse_tokens(t_lexical_list *lex);

#endif
