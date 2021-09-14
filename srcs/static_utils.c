/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   static_utils.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lspiess <lspiess@student.42.us.org>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/06/30 05:51:24 by lspiess           #+#    #+#             */
/*   Updated: 2020/06/30 18:42:45 by lspiess          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int			reset_stat(void)
{
	ft_free((void **)(&(getstat()->line)));
	if (getstat()->lex.tok)
		free_toklist(getstat()->lex.tok);
	getstat()->astroot = NULL;
	getstat()->line = NULL;
	getstat()->tmp = NULL;
	getstat()->swap = NULL;
	getstat()->stoprdline = 0;
	ft_printf(ANSI_COLOR_RED"minishell42%%> "ANSI_COLOR_RESET);
	return (1);
}

t_static	*getstat(void)
{
	static t_static		stat;

	return (&stat);
}
