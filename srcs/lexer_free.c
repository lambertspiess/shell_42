/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexer_free.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lspiess <lspiess@student.42.us.org>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/06/01 08:54:32 by lspiess           #+#    #+#             */
/*   Updated: 2020/06/30 07:39:24 by lspiess          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void			free_toklist(t_tok *list)
{
	t_tok		*head;
	t_tok		*to_free;

	if (!list)
		return ;
	head = list;
	while (head != NULL)
	{
		to_free = head;
		head = head->next;
		ft_free((void **)(&(to_free->s)));
		ft_free((void **)(&(to_free)));
	}
}

void			lexer_fatal_error(t_lexical_list *lex)
{
	free_toklist(lex->tok);
	ft_printf_fd(2, "minishell: fatal error : ");
	ft_printf_fd(2, "%s\n", strerror(errno));
	exit(EXIT_FAILURE);
}
