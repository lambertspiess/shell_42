/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexer.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lspiess <lspiess@student.42.us.org>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/05/01 21:01:35 by lspiess           #+#    #+#             */
/*   Updated: 2020/06/18 22:32:01 by lspiess          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lexer.h"

static void			store_char_from_inside_double_quotes(t_lexer_util *lu, \
														char *line)
{
	lu->tok->s[(lu->j)++] = line[lu->i];
	if (lu->char_type == TYPE_DOUBLE_QUOTE)
		lu->state = STATE_DEFAULT;
}

static void			store_char_from_inside_single_quotes(t_lexer_util *lu, \
														char *line)
{
	lu->tok->s[(lu->j)++] = line[lu->i];
	if (lu->char_type == TYPE_SINGLE_QUOTE)
		lu->state = STATE_DEFAULT;
}

/*
** Store the special character (in command line context).
** If the current token isn't empty, null-terminate its string and open a
** fresh one.
** If the character is a space, return (no need to store spaces outside quotes)
*/

static int			handle_special_character(t_lexical_list *lex, \
												t_lexer_util *lu, int linelen)
{
	if (lu->j > 0)
	{
		lu->tok->s[lu->j] = 0;
		if (!(lu->tok->next = alloc_token(linelen - lu->i)))
			lexer_fatal_error(lex);
		lu->tok = lu->tok->next;
		lu->j = 0;
	}
	if (lu->char_type == TYPE_SPACE)
		return (1);
	lu->tok->s[0] = lu->char_type;
	lu->tok->s[1] = '\0';
	lu->tok->type = lu->char_type;
	if (!(lu->tok->next = alloc_token(linelen - lu->i)))
		lexer_fatal_error(lex);
	lu->tok = lu->tok->next;
	return (0);
}

/*
** if the current char is a backslash, store the escaped char.
** if the current char is a double or single quote mark, update state, and
** store quotation mark.
** otherwise just store the character.
*/

static int			store_char_from_default_state(t_lexical_list *lex, \
									t_lexer_util *lu, char *line, int linelen)
{
	if (lu->char_type == TYPE_SEMICOLON || lu->char_type == TYPE_GREATER \
		|| lu->char_type == TYPE_LESSER || lu->char_type == TYPE_AMPERSAND \
		|| lu->char_type == TYPE_PIPE || lu->char_type == TYPE_SPACE)
		return (handle_special_character(lex, lu, linelen));
	if (lu->char_type == TYPE_ESCAPE_SEQUENCE)
	{
		lu->tok->s[(lu->j)++] = line[++(lu->i)];
	}
	else if (lu->char_type == TYPE_DOUBLE_QUOTE \
		|| lu->char_type == TYPE_SINGLE_QUOTE)
	{
		if (lu->char_type == TYPE_DOUBLE_QUOTE)
			lu->state = STATE_INSIDE_DOUBLE_QUOTES;
		else
			lu->state = STATE_INSIDE_SINGLE_QUOTES;
		lu->tok->s[(lu->j)++] = lu->char_type;
	}
	else
		lu->tok->s[(lu->j)++] = line[(lu->i)];
	lu->tok->type = REGULAR_CHARS;
	return (0);
}

/*
**    DESCRIPTION :
** Split the command line into a linked list of tokens, each comprising
** of a string and an integer value indicating the type of the token
** (see lexer.h for the various type codes).
**
** Tokens are delimited by special chars (redirections, pipes, ampersands,
** semicolons, whitespaces), unless those chars are escaped or quoted-out.
** To account for this we read chars from one of three STATES :
** DEFAULT, INSIDE_SINGLE_QUOTES, INSIDE_DOUBLE_QUOTES
**
** This struct exists purely for coding norm reasons, sorry
**    VARIABLES :
** t_lexer_util {
**   int    i;           // char iterator of command line string
**   int    char_type;   // int code for the type of the current char
**   int    state;       // current STATE
**   t_tok  *tok;        // current token
**   int    j;           // char iterator of a given token string
** }
*/

void				tokenize_line(char *line, t_lexical_list *lex, int linelen)
{
	t_lexer_util		lu;

	lu.i = 0;
	lu.j = 0;
	if (!(lex->tok = alloc_token(linelen)))
		lexer_fatal_error(lex);
	lu.tok = lex->tok;
	lu.state = STATE_DEFAULT;
	while (lu.i < linelen)
	{
		lu.char_type = return_char_type(line[lu.i]);
		if (lu.char_type == UNSET && lu.j > 0)
			null_terminate_token(&lu);
		if (lu.state == STATE_DEFAULT)
			store_char_from_default_state(lex, &lu, line, linelen);
		else if (lu.state == STATE_INSIDE_DOUBLE_QUOTES)
			store_char_from_inside_double_quotes(&lu, line);
		else if (lu.state == STATE_INSIDE_SINGLE_QUOTES)
			store_char_from_inside_single_quotes(&lu, line);
		lu.i++;
	}
	if (check_for_redundant_quotes(lex->tok) == -1)
		lexer_fatal_error(lex);
	count_tokens(lex);
}
