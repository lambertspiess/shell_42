/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexer_check_for_redundant_quotes.c                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lspiess <lspiess@student.42.us.org>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/05/05 00:06:20 by lspiess           #+#    #+#             */
/*   Updated: 2020/06/18 19:56:53 by lspiess          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static int		remove_redundant_quotation_marks(t_tok **tokp, int len)
{
	int				i;
	int				j;
	char			*new;
	char			quotemark;

	new = NULL;
	if (!(new = ft_memalloc(len + 1)))
		return (-1);
	i = 0;
	j = 0;
	while ((*tokp)->s[i])
	{
		if (((*tokp)->s[i] == '\'' || (*tokp)->s[i] == '\"') && quotemark == 0)
			quotemark = (*tokp)->s[i];
		else if (quotemark != 0 && (*tokp)->s[i] == quotemark)
			quotemark = 0;
		else
			new[j++] = (*tokp)->s[i];
		i++;
	}
	new[j] = '\0';
	free((*tokp)->s);
	(*tokp)->s = new;
	return (0);
}

int				check_for_redundant_quotes(t_tok *tok)
{
	while (tok)
	{
		if (tok->type != REGULAR_CHARS)
		{
			if (remove_redundant_quotation_marks(&tok, ft_istrlen(tok->s)) \
					== -1)
				return (-1);
		}
		tok = tok->next;
	}
	return (0);
}
