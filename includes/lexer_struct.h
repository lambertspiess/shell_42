/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexer_struct.h                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lspiess <lspiess@student.42.us.org>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/05/14 23:42:55 by lspiess           #+#    #+#             */
/*   Updated: 2020/05/25 20:08:57 by lspiess          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef LEXER_STRUCT_H
# define LEXER_STRUCT_H

typedef enum		e_tok_type {
	TYPE_PIPE = '|',
	TYPE_AMPERSAND = '&',
	TYPE_SINGLE_QUOTE = '\'',
	TYPE_DOUBLE_QUOTE = '\"',
	TYPE_SEMICOLON = ';',
	TYPE_SPACE = ' ',
	TYPE_ESCAPE_SEQUENCE = '\\',
	TYPE_TAB = '\t',
	TYPE_NEWLINE = '\n',
	TYPE_GREATER = '>',
	TYPE_LESSER = '<',
	TYPE_NULL = 0,
	REGULAR_CHARS = -1,
	UNSET = -2,
}					t_tok_type;

typedef enum		e_lexer_state {
	STATE_DEFAULT,
	STATE_INSIDE_SINGLE_QUOTES,
	STATE_INSIDE_DOUBLE_QUOTES,
}					t_lexer_state;

typedef struct		s_tok {
	char			*s;
	int				type;
	struct s_tok	*next;
}					t_tok;

typedef struct		s_lexical_list {
	t_tok			*tok;
	int				n;
}					t_lexical_list;

typedef struct		s_lexer_util {
	int				i;
	int				j;
	int				char_type;
	int				state;
	t_tok			*tok;
}					t_lexer_util;

#endif
