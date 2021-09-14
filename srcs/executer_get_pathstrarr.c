/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   executer_get_pathstrarr.c                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lspiess <lspiess@student.42.us.org>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/06/01 06:16:33 by lspiess           #+#    #+#             */
/*   Updated: 2020/06/18 17:38:32 by lspiess          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static int		count_toks(char *s, char c)
{
	int				i;
	int				j;
	int				count;

	i = 0;
	j = 0;
	count = 0;
	while (s[i])
	{
		if (s[i] == c)
		{
			if (i - j > 1)
				count++;
			j = i;
		}
		i++;
	}
	if (i - j > 1)
		count++;
	return (count);
}

static void		dup_path_strings(t_ast_node *astroot, t_cmd_info *io,
									char *pathstr)
{
	int				i;
	int				j;
	int				k;

	i = 0;
	j = 0;
	k = 0;
	while (pathstr[i])
	{
		j = i + 1;
		while (pathstr[j] && pathstr[j] != ':')
			j++;
		if (pathstr[i] == ':')
			i++;
		if (!(io->pathstrarr[k++] = ft_strndup(pathstr + i, j - i)))
			executer_exit_process(astroot, io, errno, 1);
		i = j;
	}
}

static void		build_pathstrarr(t_ast_node *astroot, t_cmd_info *io, \
									char *pathstr)
{
	int				tokcount;

	if ((tokcount = count_toks(pathstr, ':')) == 0)
		return ;
	if (!(io->pathstrarr = ft_memalloc(sizeof(char *) * (tokcount + 1))))
		executer_exit_process(astroot, io, errno, 1);
	dup_path_strings(astroot, io, pathstr);
}

static char		*get_pathstr(t_env *env)
{
	while (env)
	{
		if (ft_strequ(env->key, "PATH"))
			break ;
		env = env->next;
	}
	return (env->value);
}

/*
** If the user provided an explicit path, return.
** Otherwise create a string array of possible paths out of the PATH
** environment variable.
*/

void			get_pathstrarr(t_ast_node *astroot, t_cmd_info *io)
{
	char			*pathstr;

	if (io->av && ft_strchr(io->av[0], '\\'))
		return ;
	pathstr = get_pathstr(getstat()->env);
	build_pathstrarr(astroot, io, pathstr);
}
