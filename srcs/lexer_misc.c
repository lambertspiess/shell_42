/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexer_misc.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lspiess <lspiess@student.42.us.org>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/06/18 05:05:39 by lspiess           #+#    #+#             */
/*   Updated: 2020/06/18 19:32:53 by lspiess          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int				return_char_type(char c)
{
	if (c == '\'')
		return (TYPE_SINGLE_QUOTE);
	else if (c == '\"')
		return (TYPE_DOUBLE_QUOTE);
	else if (c == '|')
		return (TYPE_PIPE);
	else if (c == '&')
		return (TYPE_AMPERSAND);
	else if (c == ' ')
		return (TYPE_SPACE);
	else if (c == ';')
		return (TYPE_SEMICOLON);
	else if (c == '\\')
		return (TYPE_ESCAPE_SEQUENCE);
	else if (c == '\t')
		return (TYPE_TAB);
	else if (c == '\n')
		return (TYPE_NEWLINE);
	else if (c == '>')
		return (TYPE_GREATER);
	else if (c == '<')
		return (TYPE_LESSER);
	else if (c == 0)
		return (TYPE_NULL);
	return (REGULAR_CHARS);
}

t_tok			*alloc_token(int size)
{
	t_tok			*new;

	if (!(new = ft_memalloc(sizeof(t_tok))))
		return (NULL);
	if (!(new->s = ft_memalloc(size + 1)))
	{
		free(new);
		return (NULL);
	}
	new->next = NULL;
	new->type = UNSET;
	return (new);
}

void			null_terminate_token(t_lexer_util *lu)
{
	lu->tok->s[lu->j] = '\0';
	lu->j = 0;
}

void			print_tokens(t_lexical_list *lex)
{
	t_tok		*tok;

	if (!lex)
		return ;
	tok = lex->tok;
	while (tok)
	{
		printf("|%s| type = %c (%d)\n", tok->s, tok->type, tok->type);
		tok = tok->next;
	}
	printf("Number of tokens : %d\n", lex->n);
}

void			count_tokens(t_lexical_list *lex)
{
	t_tok		*head;

	lex->n = 0;
	head = lex->tok;
	while (head)
	{
		lex->n++;
		if (head->next == NULL)
			break ;
		else if (head->next->type == UNSET || head->next->type == TYPE_NULL)
		{
			free(head->next->s);
			free(head->next);
			head->next = NULL;
			break ;
		}
		head = head->next;
	}
}
