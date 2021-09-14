/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexer.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lspiess <lspiess@student.42.us.org>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/05/01 19:30:10 by lspiess           #+#    #+#             */
/*   Updated: 2020/06/02 09:31:51 by lspiess          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef LEXER_H
# define LEXER_H

# include "minishell_structs.h"
# include "libft.h"
# include "ft_printf.h"
# include "lexer_struct.h"
# include "parser.h"

/*
** lexer_free.c
*/

void				lexer_fatal_error(t_lexical_list *lex);

/*
** lexer_misc.c
*/

void				count_tokens(t_lexical_list *lex);
t_tok				*alloc_token(int size);
int					return_char_type(char c);
void				null_terminate_token(t_lexer_util *lu);
void				print_tokens(t_lexical_list *lex);

/*
** lexer_remove_redundant_quotes.c
*/

int					check_for_redundant_quotes(t_tok *tok);

/*
** lexer.c
*/

void				tokenize_line(char *line, t_lexical_list *lex, \
									int linelen);

#endif
