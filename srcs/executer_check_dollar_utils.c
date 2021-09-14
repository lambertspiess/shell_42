/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   executer_check_dollar_utils.c                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lspiess <lspiess@student.42.us.org>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/06/10 14:57:59 by lspiess           #+#    #+#             */
/*   Updated: 2020/06/30 05:41:18 by lspiess          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int			get_key_length(char *s, int *ip)
{
	int			length;

	if (!s)
		return (0);
	if (s[*ip] == '$')
		(*ip)++;
	length = 0;
	while (s[*ip] && (ft_isalpha(s[*ip]) || s[*ip] == '_'))
	{
		(*ip)++;
		length++;
	}
	return (length);
}

void		get_exit_status(int *ip, int *jp, char *buf)
{
	char		*statusstr;

	statusstr = ft_itoa(getstat()->exitcode);
	(*ip)++;
	*jp = ((int)ft_strlcat(buf, statusstr, ARG_MAX));
	free(statusstr);
}

void		swap_tok(t_ast_node *astroot, t_cmd_info *io, \
							char *buf, char **sp)
{
	if (*sp)
		free(*sp);
	if (!(*sp = buf))
		executer_exit_process(astroot, io, errno, 1);
}
