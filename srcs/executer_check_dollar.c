/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   executer_check_dollar.c                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lspiess <lspiess@student.42.us.org>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/06/05 13:05:43 by lspiess           #+#    #+#             */
/*   Updated: 2020/06/30 05:39:40 by lspiess          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

/*
** All characters inside singlequotes are printed literally.
*/

static void		check_singlequotes(int *ip, int *jp, char *s, char *buf)
{
	(*ip)++;
	while (s[*ip] && s[*ip] != '\'')
	{
		buf[*jp] = s[*ip];
		(*jp)++;
		(*ip)++;
	}
	if (s[*ip] && s[*ip] == '\'')
		(*ip)++;
}

/*
** If a backslash is present inside double quotes and the following char is a
** "special char" (either singlequote, doublequote, an 'n' or a backslash)
** the following char will be printed but the backslash itself won't.
** If the following char isn't special, both the backslash and the
** following char will be printed.
*/

static void		escape_sequence_from_inside_dquotes(int *ip, int *jp, \
														char *s, char *buf)
{
	if (ft_strchr("$\'\"\n\\", s[*ip + 1]) != NULL)
	{
		buf[(*jp)++] = s[++(*ip)];
		(*ip)++;
	}
	else
	{
		buf[(*jp)++] = s[(*ip)++];
		buf[(*jp)++] = s[(*ip)++];
	}
}

/*
** If the dollar sign is followed by a '?', print the last exit code.
** If the dollar sign is followd by nullterm or whitespace, print '$'
** Otherwise look for an environment variables with a corresponding key.
*/

static void		insert_env_value(int *ip, int *jp, char *s, char *buf)
{
	t_env			*head;
	char			key[256];
	int				keylen;

	ft_bzero((char *)(&key), 256);
	(*ip)++;
	if (s[*ip] == '?')
	{
		get_exit_status(ip, jp, buf);
		return ;
	}
	keylen = get_key_length(s, ip);
	ft_strncpy(key, s + *ip - keylen, (keylen > 256 ? 256 : keylen));
	head = getstat()->env;
	while (head)
	{
		if (ft_strequ(head->key, key))
			break ;
		head = head->next;
	}
	if (!head)
		return ;
	*jp = ((int)(ft_strlcat(buf, head->value, ARG_MAX)));
}

/*
** Inside doublequotes, all characters are written literally, except dollars
** (which are expanded), and backslashes when they precede a special character
*/

static int		check_doublequotes(int *ip, int *jp, char *s, char *buf)
{
	int				dquote;

	if ((dquote = 1) != 0 && s[*ip] == '\0')
		return (0);
	if (s[*ip] == '\"')
	{
		(*ip)++;
		while (s[*ip] && s[*ip] != '\"')
		{
			if (s[*ip] == '$')
				insert_env_value(ip, jp, s, buf);
			else if (s[*ip] == '\\')
				escape_sequence_from_inside_dquotes(ip, jp, s, buf);
			else
				buf[(*jp)++] = s[(*ip)++];
		}
		if (s[*ip] == '\"')
		{
			dquote = 0;
			(*ip)++;
		}
	}
	if (dquote)
		ft_printf_fd(2, "minishell: syntax error: multi-line\n");
	return (dquote);
}

/*
** Parse a command's argv for dollar signs, performs substitutions accordingly
*/

int				check_dollar(t_ast_node *astroot, t_cmd_info *io, char **sp)
{
	t_check_dollar_util	u;

	ft_bzero(u.buf, ARG_MAX);
	u.i = 0;
	u.j = 0;
	while ((*sp) && (*sp)[u.i])
	{
		if ((*sp)[u.i] == '\'')
			check_singlequotes(&(u.i), &(u.j), (*sp), u.buf);
		else if ((*sp)[u.i] == '\"' && ((u.ret = check_doublequotes(\
					&(u.i), &(u.j), (*sp), u.buf)) > -1))
		{
			if (u.ret == 1)
				return (-1);
		}
		else if ((*sp)[u.i] == '\\')
			u.buf[u.j++] = (*sp)[u.i++];
		else if ((*sp)[u.i] == '$' && (ft_isalpha((*sp)[u.i + 1]) \
				|| (*sp)[u.i + 1] == '?'))
			insert_env_value(&(u.i), &(u.j), (*sp), u.buf);
		else
			u.buf[(u.j)++] = (*sp)[(u.i)++];
	}
	swap_tok(astroot, io, ft_strdup(u.buf), sp);
	return (0);
}
